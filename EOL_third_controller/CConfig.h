#pragma once
#include <iostream>
#include <fstream>
#include "util.h"

// INI节信息
struct SECTION
{
	string strName;
	int start;
	int end;
};

// INI文件描述
struct INIFILE
{
	// 工作站名
	string strName;
	string strFilePath;
	int section_num;
	vector<SECTION> vSection;
};

struct SERIALPORT
{
	DWORD dwPort; // 串口序号
	DWORD dwBaudRate; // 波特率
	BYTE btParity; // 奇偶校验
	BYTE btByteSize; // 数据位数
	BYTE btStopBits; // 停止位数
};

struct SOCKETCFG {
	int iProtocol; // 协议类型，1：TCP，2：UDP
	int iPort; // 端口号
};

struct INIVIN {
	string fullName;
	string section;
	string key;
};

struct DIRINFO {
	string m_strDirPath;
	int m_iMaxFileNum;
};

class CConfig
{
private:
	string m_strCfgFile;
	string m_strINICfgFile;
	string m_strVIN;
	Logger *m_lpLog;
	SERIALPORT m_SerialPort;
	SOCKETCFG m_SocketCfg;
	INIVIN m_INIVIN;
	int m_iType; // 接收VIN码方式，1：串口，2：Socket，3：文件
	int m_iSleepTime; // 轮询间隔时间，毫秒
	int m_iTimeout; // 工作站处理超时时间，秒

	/**
	 * m_iWorkStation == 0, Invalid
	 *                   1, NCA
	 *                   2, HLA
	 *                   3, SideSlip
	 *                   4, Brake
	**/
	int m_iWorkStation;

	DIRINFO m_SendDir, m_ReceDir;

	/**
	 * m_SendFile[0] - NCA
	 * m_SendFile[1] - HLA
	 * m_SendFile[2] - SideSlip
	 * m_SendFile[3] - Brake
	**/
	INIFILE m_SendFile[4];

	/**
	 * m_ReceFile[0] - NCAToeCamber
	 * m_ReceFile[1] - NCACaster
	 * m_ReceFile[2] - NCATurningAngle
	 * m_ReceFile[3] - HLA
	 * m_ReceFile[4] - SideSlip
	 * m_ReceFile[5] - Brake
	**/
	INIFILE m_ReceFile[6];

	string m_strIP;
	string m_strPort;
	string m_strUser;
	string m_strPwd;
	string m_strDBName;

public:
	CConfig(string strVIN, Logger *lpLog);
	~CConfig();

	string getVIN();
	int getWorkStation();

	/**
	 * outSendFile[0] - NCA
	 * outSendFile[1] - HLA
	 * outSendFile[2] - SideSlip
	 * outSendFile[3] - Brake
	**/
	void getSendFile(INIFILE *outSendFile);
	int getSendFileCount();

	/**
	 * outReceFile[0] - NCAToeCamber
	 * outReceFile[1] - NCACaster
	 * outReceFile[2] - NCATurningAngle
	 * outReceFile[3] - HLA
	 * outReceFile[4] - SideSlip
	 * outReceFile[5] - Brake
	**/
	void getReceFile(INIFILE *outReceFile);
	int getReceFileCount();
	void doReplace();
	string getIP();
	string getPort();
	string getUser();
	string getPwd();
	string getDBName();
	void getINIConfig();
	SERIALPORT getSerialPort();
	SOCKETCFG getSocketCfg();
	INIVIN getINIVIN();
	int getSleepTime();
	int getTimeout();
	int getType();
	DIRINFO getDirInfo(bool bSend);
};
