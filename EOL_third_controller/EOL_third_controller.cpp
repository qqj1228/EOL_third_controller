// EOL_third_contrller.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <algorithm>
#include "CConfig.h"
#include "CModel.h"
#include "CnComm.h"
#include <Windows.h>
#include "Socket.h"
#include "util.h"

using namespace std;

class MyComm : public CnComm {
public:
	// 接受串口发送过来的VIN码
	// VIN码数据可能不止一个数据包，每个数据包以'\x02'开头, '\x03'结尾
	// "\x0D\x0A"表示VIN码结束
	void OnReceive() {
		//TCHAR buffer[BUFSIZ];
		char buffer[BUFSIZ];
		string strBuf;
		size_t pos = -1;
		//ReadString(buffer, BUFSIZ);
		if (getData(buffer, BUFSIZ, '\x02', '\x03') > 0) {
			strBuf = buffer;
			m_strTemp += strBuf;
			// 从第一个找到的回车符开始至结尾都过滤掉
			pos = m_strTemp.find("\x0D\x0A", m_offset);
			m_offset = m_strTemp.length();
			if (pos != string::npos) {
				m_strTemp.resize(pos);
				m_strVIN = m_strTemp;
				m_strTemp.clear();
				m_offset = 0;
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

	// 一轮处理结束后返回给客户端的数据，数据包仍是以'\x02'开头, '\x03'结尾
	// "\x0D\x0A"表示传输数据结束
	void response(bool bNormal) {
		char buffer[BUFSIZ] = {0};
		buffer[0] = '\x02';
		if (bNormal) {
			strcat_s(buffer, NORMAL_RET);
		} else {
			strcat_s(buffer, ERROR_RET);
		}
		strcat_s(buffer, "\x0D\x0A\x03");
		Write(buffer);
	}

	string m_strVIN = "";
private:
	string m_strTemp = "";
	size_t m_offset = 0;
};

class MySocket {
public:
	Logger * lpLog = nullptr;
	string m_strVIN = "";
	SocketServer m_server;
	Socket_Base *lpClient = nullptr;

	MySocket(Logger *lpLog, int port, const bool bTCP = true, int connections = 10, TypeSocket type = BlockingSocket) :m_server(port, bTCP, connections, type) {
		this->lpLog = lpLog;
		if (bTCP) {
			cout << "Receive VIN code via TCP port: " << port << endl;
			lpLog->TRACE_INFO("Receive VIN code via TCP port: %d", port);
		} else {
			cout << "Receive VIN code via UDP port: " << port << endl;
			lpLog->TRACE_INFO("Receive VIN code via UDP port: %d", port);
		}
	}

	~MySocket() {
		// 断开客户端连接
		if (nullptr != lpClient) {
			delete lpClient;
			lpClient = nullptr;
		}
	}

	void getData() {
		if (nullptr == lpClient) {
			// 接受客户端连接请求
			lpClient = m_server.Accept();
		}

		// 接收的VIN码以\n表示结束
		m_strVIN = lpClient->ReceiveLine();

		// 去除结尾的\r\n或者\n
		size_t pos = -1;
		pos = m_strVIN.find("\x0D\x0A");
		if (pos != string::npos) {
			m_strVIN.pop_back();
			m_strVIN.pop_back();
		} else {
			pos = m_strVIN.find("\x0A");
			if (pos != string::npos) {
				m_strVIN.pop_back();
			}
		}
	}

	// 一轮处理结束后返回给客户端的数据
	// "\x0D\x0A"表示传输数据结束
	void response(bool bNormal) {
		if (bNormal) {
			lpClient->SendLine(NORMAL_RET);
		} else {
			lpClient->SendLine(ERROR_RET);
		}
	}
};

class MyINIVIN {
public:
	string m_strVIN = "";
	INIVIN m_INIVIN;

	MyINIVIN(INIVIN ini) :m_INIVIN(ini) {
	}

	void getData() {
		TCHAR buf[BUFSIZ];
		GetPrivateProfileString(m_INIVIN.section.c_str(), m_INIVIN.VIN_key.c_str(), _T(""), buf, BUFSIZ, m_INIVIN.fullName.c_str());
		m_strVIN = buf;
		if (m_strVIN != "") {
			// 已获取到VIN，再把INI文件里的VIN_key和Result_key置空字符串
			WritePrivateProfileString(m_INIVIN.section.c_str(), m_INIVIN.VIN_key.c_str(), _T(""), m_INIVIN.fullName.c_str());
			WritePrivateProfileString(m_INIVIN.section.c_str(), m_INIVIN.Result_key.c_str(), _T(""), m_INIVIN.fullName.c_str());
		}
	}

	void response(bool bNormal) {
		if (bNormal) {
			WritePrivateProfileString(m_INIVIN.section.c_str(), m_INIVIN.Result_key.c_str(), _T("O"), m_INIVIN.fullName.c_str());
		} else {
			WritePrivateProfileString(m_INIVIN.section.c_str(), m_INIVIN.Result_key.c_str(), _T("X"), m_INIVIN.fullName.c_str());
		}
	}
};

class ReceObj {
public:
	// VIN码接收方式，1: 串口, 2: socket, 3: 文件
	int iType = 0;
	// 串口对象指针, 默认模式, 重叠IO, 监视线程
	MyComm *lpComm = nullptr;
	// Socket对象指针, 默认阻塞模式
	MySocket *lpSocket = nullptr;

	MyINIVIN *lpINIVIN = nullptr;

	~ReceObj() {
		if (nullptr != lpComm) {
			delete lpComm;
			lpComm = nullptr;
		}
		if (nullptr != lpSocket) {
			delete lpSocket;
			lpSocket = nullptr;
		}
		if (nullptr != lpINIVIN) {
			delete lpINIVIN;
			lpINIVIN = nullptr;
		}
	}

	string getVIN() {
		string strVIN;
		switch (this->iType) {
		case 1:
			strVIN = this->lpComm->m_strVIN;
			break;
		case 2:
			this->lpSocket->getData();
			strVIN = this->lpSocket->m_strVIN;
			break;
		case 3:
			this->lpINIVIN->getData();
			strVIN = this->lpINIVIN->m_strVIN;
			break;
		default:
			break;
		}
		return strVIN;
	}

	void resetVIN() {
		switch (this->iType) {
		case 1:
			this->lpComm->m_strVIN = "";
			break;
		case 2:
			this->lpSocket->m_strVIN = "";
			break;
		case 3:
			this->lpINIVIN->m_strVIN = "";
			break;
		default:
			break;
		}
	}

	void response(bool bNormal) {
		switch (this->iType) {
		case 1:
			this->lpComm->response(bNormal);
			break;
		case 2:
			this->lpSocket->response(bNormal);
			break;
		case 3:
			this->lpINIVIN->response(bNormal);
			break;
		default:
			break;
		}
	}
};

int main(int argc, TCHAR *argv[]) {
	ReceObj receObj;

	// VIN码全局变量
	string strVIN;
	string strWorkDir;
	map<string, vector<FIELD>> mapDBTable;
	SERIALPORT serialPort;
	SOCKETCFG socketCfg;
	INIVIN ini;
	int iSleepTime;
	const string strLogPath = LOG_DIR;
	const int iMaxFileNum = LOG_FILE_QTY;

	Logger log(strLogPath.c_str(), iMaxFileNum, LogLevelAll);
	updateFileNum(strLogPath, iMaxFileNum);
	TCHAR buffer[BUFSIZ];
	DWORD dwRet = GetCurrentDirectory(BUFSIZ, buffer);
	if (dwRet > 0) {
		strWorkDir = buffer;
	} else {
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "GetCurrentDirectory failed: " << GetLastError() << endl;
		setConsoleColor(wOrigin);
		log.TRACE_ERR("GetCurrentDirectory failed: %d", GetLastError());
	}
	cout << "==================== Start EOL_third_controller ====================" << endl;
	log.TRACE_INFO("==================== Start EOL_third_controller ====================");

	CConfig *lpConfig = new CConfig(strVIN, &log);
	serialPort = lpConfig->getSerialPort();
	socketCfg = lpConfig->getSocketCfg();
	ini = lpConfig->getINIVIN();
	iSleepTime = lpConfig->getSleepTime();
	receObj.iType = lpConfig->getType();
	CModel *lpModel = new CModel(lpConfig, &log);
	// 获取数据库中的表信息放入mapDBTable
	mapDBTable = lpModel->GetMapDBTable();
	delete lpModel;
	lpModel = nullptr;
	delete lpConfig;
	lpConfig = nullptr;
	if (mapDBTable.size() == 0) {
		cout << "Get DataBase Table failed, Application will exit!" << endl;
		log.TRACE_FATAL("Get DataBase Table failed, Application will exit!");
		system("pause");
		return 0;
	}

	switch (receObj.iType) {
	case 1: // 串口接收VIN码
		receObj.lpComm = new MyComm();
		if (!receObj.lpComm->Open(serialPort.dwPort, serialPort.dwBaudRate, serialPort.btParity, serialPort.btByteSize, serialPort.btStopBits)) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Serial Port Initialization failed!" << endl;
			setConsoleColor(wOrigin);
			log.TRACE_FATAL("Serial Port Initialization failed!");
			system("pause");
			return 0;
		}
		cout << "Receive VIN code via COM" << serialPort.dwPort << endl;
		log.TRACE_INFO("Receive VIN code via COM%d", serialPort.dwPort);
		break;
	case 2: // socket接收VIN码
		try {
			receObj.lpSocket = new MySocket(&log, socketCfg.iPort, socketCfg.iProtocol == 1 ? true : false);
		} catch (const string& e) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Socket Initialization failed! Error Info: " << e << endl;
			setConsoleColor(wOrigin);
			log.TRACE_FATAL("Socket Initialization failed! Error Info: %s", e.c_str());
			system("pause");
			return 0;
		}
		break;
	case 3: // INI文件接收VIN码
		cout << "Receive VIN code via INI File: " << ini.fullName << endl;
		log.TRACE_INFO("Receive VIN code via INI File: %s", ini.fullName.c_str());
		receObj.lpINIVIN = new MyINIVIN(ini);
		break;
	default:
		break;
	}
	WORD wOrigin = setConsoleColor(10);
	cout << "Finished initialization, Waiting to receive first VIN code..." << endl;
	log.TRACE_INFO("Finished initialization, Waiting to receive first VIN code...");
	setConsoleColor(wOrigin);

	time_t tStart, tEnd;
	double dCost;
	while (true) {
		strVIN = receObj.getVIN();
		if (strVIN != "") {
			cout << "-------------------- Start processing --------------------" << endl;
			log.TRACE_INFO("-------------------- Start processing --------------------");

			if (strVIN.length() > 17) {
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "The length of VIN code is longer than 17" << endl;
				cout << "VIN code will be cutted" << endl;
				cout << "Original VIN code: " << strVIN << endl;
				setConsoleColor(wOrigin);
				log.TRACE_ERR("The length of VIN code is longer than 17");
				log.TRACE_ERR("Original VIN code: %s", strVIN.c_str());
				strVIN.resize(17);
			}
			cout << "Received VIN code: " << strVIN << endl;
			log.TRACE_INFO("Received VIN code: %s", strVIN.c_str());

			CConfig *lpConfig = new CConfig(strVIN, &log);
			CModel *lpModel = new CModel(lpConfig, mapDBTable, &log);

			if (!lpModel->WriteSendFile()) {
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "WriteSendFile failed, turning into next period!" << endl;
				setConsoleColor(wOrigin);
				log.TRACE_ERR("WriteSendFile failed, turning into next period!");
				receObj.resetVIN();
				receObj.response(false);
				continue;
			}
			time(&tStart);
			while (true) {
				if (lpModel->ReadReceFile()) {
					if (lpConfig->getWorkStation() == 1) {
						// 在定位仪工作站内含有EPS标定内容
						string cmd = strWorkDir + CALIPROC_PATH;
						SetCurrentDirectory(cmd.c_str());
						cmd = strWorkDir + CALIPROC_PATH + CALIPROC_FILE + " " + strVIN;
						system(cmd.c_str());
						SetCurrentDirectory(strWorkDir.c_str());
					}
					receObj.response(true);
					WORD wOrigin = setConsoleColor(10);
					cout << "Finished processing, Waiting to receive next VIN code..." << endl;
					setConsoleColor(wOrigin);
					log.TRACE_INFO("Finished processing, Waiting to receive next VIN code...");
					break;
				}
				time(&tEnd);
				dCost = difftime(tEnd, tStart);
				if (dCost > (double)lpConfig->getTimeout()) {
					WORD wOrigin = setConsoleColor(12, 14);
					cout << "Timeout occurred, turning into next period!" << endl;
					setConsoleColor(wOrigin);
					log.TRACE_ERR("Timeout occurred, turning into next period!");
					receObj.response(false);
					break;
				}
				Sleep(iSleepTime);
			}

			delete lpModel;
			lpModel = nullptr;
			delete lpConfig;
			lpConfig = nullptr;

			// 将VIN码置空字符串, 准备接收下一个VIN码
			receObj.resetVIN();
		}
		Sleep(iSleepTime);
	}
	return 0;
}
