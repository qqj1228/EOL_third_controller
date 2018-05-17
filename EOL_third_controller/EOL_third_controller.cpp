// EOL_third_contrller.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include "CConfig.h"
#include "CModel.h"
#include "CnComm.h"
#include <Windows.h>
using namespace std;

class MyComm : public CnComm
{
public:
	// 接受串口发送过来的VIN码
	void OnReceive()
	{
		TCHAR buffer[MAX_STR_LEN];
		ReadString(buffer, MAX_STR_LEN);
		m_strVIN = buffer;
		cout << "Serial Port -- Received data: " << m_strVIN << endl;
	}
	string m_strVIN;
};

int main(int argc, TCHAR *argv[])
{
	string strVIN;
	map<string, vector<FIELD>> mapDBTable;
	SERIALPORT serialPort;
	int iSleepTime;

	Logger log(".\\log", LogLevelAll);
	cout << "Start EOL_third_controller" << endl;
	log.TraceInfo("Start EOL_third_controller");

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

	// 默认模式 重叠IO 监视线程
	MyComm comm;
	if (!comm.Open(serialPort.dwPort, serialPort.dwBaudRate, serialPort.btParity, serialPort.btByteSize, serialPort.btStopBits))
	{
		cout << "Serial Port Initialization failed!" << endl;
		log.TraceFatal("Serial Port Initialization failed!");
		system("pause");
		return 0;
	}
	cout << "Waiting to receive VIN code..." << endl;
	log.TraceInfo("Waiting to receive VIN code...");

	time_t tStart, tEnd;
	double dCost;
	while (true)
	{
		strVIN = comm.m_strVIN;
		if (strVIN != "")
		{
			if (strVIN.length() > 17)
			{
				cout << "The length of VIN code is longer than 17" << endl;
				cout << "VIN code will be cutted" << endl;
				cout << "Original VIN code: " << strVIN << endl;
				log.TraceError("The length of VIN code is longer than 17");
				log.TraceError("Original VIN code: %s", strVIN.c_str());
				strVIN.resize(17);
			}
			cout << "Received VIN code: " << strVIN << endl;
			log.TraceInfo("Received VIN code: ", strVIN.c_str());

			CConfig *lpConfig = new CConfig(strVIN, &log);
			CModel *lpModel = new CModel(lpConfig, mapDBTable, &log);

			cout << "Start processing..." << endl;
			log.TraceInfo("Start processing...");
			lpModel->WriteSendFile();
			time(&tStart);
			while (true)
			{
				if (lpModel->ReadReceFile())
				{
					cout << "Finished processing" << endl;
					log.TraceInfo("Finished processing");
					break;
				}
				time(&tEnd);
				dCost = difftime(tEnd, tStart);
				if (dCost > (double)lpConfig->getTimeout())
				{
					cout << "Timeout occurred, turning into next period!" << endl;
					log.TraceError("Timeout occurred, turning into next period!");
					break;
				}
				Sleep(lpConfig->getTimeout());
			}

			delete lpModel;
			lpModel = NULL;
			delete lpConfig;
			lpConfig = NULL;

			comm.m_strVIN = "";
		}
		Sleep(iSleepTime);
	}

	return 0;
}
