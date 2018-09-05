#pragma once
#include <iostream>
#include <fstream>
#include "util.h"

// INI����Ϣ
struct SECTION
{
	string strName;
	int start;
	int end;
};

// INI�ļ�����
struct INIFILE
{
	// ����վ��
	string strName;
	string strFilePath;
	int section_num;
	vector<SECTION> vSection;
};

struct SERIALPORT
{
	DWORD dwPort; // �������
	DWORD dwBaudRate; // ������
	BYTE btParity; // ��żУ��
	BYTE btByteSize; // ����λ��
	BYTE btStopBits; // ֹͣλ��
};

struct SOCKETCFG {
	int iProtocol; // Э�����ͣ�1��TCP��2��UDP
	int iPort; // �˿ں�
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
	int m_iType; // ����VIN�뷽ʽ��1�����ڣ�2��Socket��3���ļ�
	int m_iSleepTime; // ��ѯ���ʱ�䣬����
	int m_iTimeout; // ����վ����ʱʱ�䣬��

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
