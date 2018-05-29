// EOL_third_contrller.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <algorithm>
#include "CConfig.h"
#include "CModel.h"
#include "CnComm.h"
#include <Windows.h>
using namespace std;

class MyComm : public CnComm
{
public:
	// 接受串口发送过来的VIN码
	// VIN码数据可能不止一个数据包，每个数据包以'\x02'开头, '\x03'结尾
	// "\x0D\x0A"表示VIN码结束
	void OnReceive()
	{
		//TCHAR buffer[BUFSIZ];
		char buffer[BUFSIZ];
		string strBuf;
		size_t pos = -1;
		//ReadString(buffer, BUFSIZ);
		if (getData(buffer, BUFSIZ, '\x02', '\x03') > 0) {
			strBuf = buffer;
			m_strTemp += strBuf;
			pos = strBuf.find("\x0D\x0A");
			if (pos != string::npos) {
				m_strTemp.pop_back();
				m_strTemp.pop_back();
				m_strVIN = m_strTemp;
				m_strTemp.clear();
			}
		}
		//cout << "Serial Port -- Received data: " << m_strVIN << endl;
	}

	// 每个数据包以chStart开头，chEnd结尾，获取数据包的实际数据放在pBuf里
	// 返回值为实际数据的长度，失败时为负数，表示缓冲区pBuf的size太小，将要溢出的字节数
	// 返回值为0表示未找到以chStart开头chEnd结尾的数据
	int getData(char *pBuf, int size, const char chStart, const char chEnd) {
		char buffer[BUFSIZ];
		int leng = Read(buffer, BUFSIZ);
		char *pStart = find(buffer, buffer + leng, chStart);
		if (pStart != buffer + leng) {
			char *pEnd = find(pStart, buffer + leng, chEnd);
			if (pEnd != buffer + leng) {
				int lenDate = pEnd - pStart;
				if (lenDate > size) {
					return size - lenDate;
				}
				copy(pStart + 1, pEnd, pBuf);
				pBuf[lenDate - 1] = '\0';
				return lenDate;
			}
		}
		return 0;
	}

	string m_strTemp;
	string m_strVIN;
};

struct RECE_OBJ
{
	// VIN码接收方式，1: 串口, 2: 文件
	int iType = 0;
	// 串口对象指针
	MyComm *lpComm;
};

string getVIN(RECE_OBJ &receObj)
{
	string strVIN;
	switch (receObj.iType)
	{
	case 1:
		strVIN = receObj.lpComm->m_strVIN;
		break;
	case 2:
		break;
	default:
		break;
	}
	return strVIN;
}

void setVIN(RECE_OBJ &receObj, string strVIN)
{
	switch (receObj.iType)
	{
	case 1:
		receObj.lpComm->m_strVIN = strVIN;
		break;
	case 2:
		break;
	default:
		break;
	}
}

int main(int argc, TCHAR *argv[])
{
	// 串口对象, 默认模式, 重叠IO, 监视线程
	MyComm comm;

	RECE_OBJ receObj;
	receObj.iType = 1;
	receObj.lpComm = &comm;

	// VIN码全局变量
	string strVIN;
	map<string, vector<FIELD>> mapDBTable;
	SERIALPORT serialPort;
	int iSleepTime;

	Logger log(".\\log", LogLevelAll);
	cout << "==================== Start EOL_third_controller ====================" << endl;
	log.TRACE_INFO("==================== Start EOL_third_controller ====================");

	CConfig *lpConfig = new CConfig(strVIN, &log);
	serialPort = lpConfig->getSerialPort();
	iSleepTime = lpConfig->getSleepTime();
	CModel *lpModel = new CModel(lpConfig, &log);
	// 获取数据库中的表信息放入mapDBTable
	mapDBTable = lpModel->GetMapDBTable();
	delete lpModel;
	lpModel = NULL;
	delete lpConfig;
	lpConfig = NULL;
	if (mapDBTable.size() == 0)
	{
		cout << "Get DataBase Table failed, Application will exit!" << endl;
		log.TRACE_FATAL("Get DataBase Table failed, Application will exit!");
		system("pause");
		return 0;
	}

	switch (receObj.iType)
	{
	case 1: // 串口接收VIN码
		if (!comm.Open(serialPort.dwPort, serialPort.dwBaudRate, serialPort.btParity, serialPort.btByteSize, serialPort.btStopBits))
		{
			cout << "Serial Port Initialization failed!" << endl;
			log.TRACE_FATAL("Serial Port Initialization failed!");
			system("pause");
			return 0;
		}
		break;
	case 2: // 文件接收VIN码
		break;
	default:
		break;
	}
	cout << "Waiting to receive VIN code..." << endl;
	log.TRACE_INFO("Waiting to receive VIN code...");

	time_t tStart, tEnd;
	double dCost;
	while (true)
	{
		strVIN = getVIN(receObj);
		if (strVIN != "")
		{
			cout << "-------------------- Start processing --------------------" << endl;
			log.TRACE_INFO("-------------------- Start processing --------------------");

			if (strVIN.length() > 17)
			{
				cout << "The length of VIN code is longer than 17" << endl;
				cout << "VIN code will be cutted" << endl;
				cout << "Original VIN code: " << strVIN << endl;
				log.TRACE_ERR("The length of VIN code is longer than 17");
				log.TRACE_ERR("Original VIN code: %s", strVIN.c_str());
				strVIN.resize(17);
			}
			cout << "Received VIN code: " << strVIN << endl;
			log.TRACE_INFO("Received VIN code: %s", strVIN.c_str());

			CConfig *lpConfig = new CConfig(strVIN, &log);
			CModel *lpModel = new CModel(lpConfig, mapDBTable, &log);

			if (!lpModel->WriteSendFile())
			{
				cout << "WriteSendFile failed, turning into next period!" << endl;
				log.TRACE_ERR("WriteSendFile failed, turning into next period!");
				setVIN(receObj, "");
				continue;
			}
			time(&tStart);
			while (true)
			{
				if (lpModel->ReadReceFile())
				{
					cout << "Finished processing" << endl;
					log.TRACE_INFO("Finished processing");
					break;
				}
				time(&tEnd);
				dCost = difftime(tEnd, tStart);
				if (dCost > (double)lpConfig->getTimeout())
				{
					cout << "Timeout occurred, turning into next period!" << endl;
					log.TRACE_ERR("Timeout occurred, turning into next period!");
					break;
				}
				Sleep(iSleepTime);
			}

			delete lpModel;
			lpModel = NULL;
			delete lpConfig;
			lpConfig = NULL;

			// 将VIN码置空字符串, 准备接收下一个VIN码
			setVIN(receObj, "");
		}
		Sleep(iSleepTime);
	}

	return 0;
}
