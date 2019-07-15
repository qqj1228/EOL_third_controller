#pragma once
#include <iostream>
#include <fstream>
#include "util.h"

// INI����Ϣ
struct SECTION {
    string strName;
    int start;
    int end;
};

// INI�ļ�����
struct INIFILE {
    // ����վ��
    string strName;
    string strFilePath;
    int section_num;
    vector<SECTION> vSection;
};

struct SERIALPORT {
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
    string VIN_key;
    string Result_key;
};

struct DIRINFO {
    string strDirPath;
    int iMaxFileNum;
};

// ���ں͹�λ����·��������������һ������ʵ�ʽ�����һ�����ڱ���
# define DIR_NUM 2

class CConfig {
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

    string m_strNCAStateFile; // ָʾNCA�궨����ʼ���е�״̬�ļ�
    DIRINFO m_SendDir[DIR_NUM], m_ReceDir[DIR_NUM]; // ���ں͹�λ������2��Ŀ¼

    /**
     * m_SendFile[0][DIR_NUM] - NCA
     * m_SendFile[1][DIR_NUM] - HLA
     * m_SendFile[2][DIR_NUM] - SideSlip
     * m_SendFile[3][DIR_NUM] - Brake
    **/
    INIFILE m_SendFile[4][DIR_NUM];

    /**
     * m_ReceFile[0][DIR_NUM] - NCA
     * m_ReceFile[1][DIR_NUM] - HLA
     * m_ReceFile[2][DIR_NUM] - SideSlip
     * m_ReceFile[3][DIR_NUM] - Brake
    **/
    INIFILE m_ReceFile[4][DIR_NUM];

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
    void getSendFile(INIFILE *outSendFile, int index);
    int getSendFileCount();

    /**
     * outReceFile[0] - NCA
     * outReceFile[1] - HLA
     * outReceFile[2] - SideSlip
     * outReceFile[3] - Brake
    **/
    void getReceFile(INIFILE *outReceFile, int index);
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
    DIRINFO getDirInfo(bool bSend, int index);
    int getDirCount(bool bSend);
};
