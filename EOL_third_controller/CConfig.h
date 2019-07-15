#pragma once
#include <iostream>
#include <fstream>
#include "util.h"

// INI节信息
struct SECTION {
    string strName;
    int start;
    int end;
};

// INI文件描述
struct INIFILE {
    // 工作站名
    string strName;
    string strFilePath;
    int section_num;
    vector<SECTION> vSection;
};

struct SERIALPORT {
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
    string VIN_key;
    string Result_key;
};

struct DIRINFO {
    string strDirPath;
    int iMaxFileNum;
};

// 用于和工位交互路径的数量，其中一个用于实际交互，一个用于备份
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

    string m_strNCAStateFile; // 指示NCA标定程序开始运行的状态文件
    DIRINFO m_SendDir[DIR_NUM], m_ReceDir[DIR_NUM]; // 用于和工位交互的2类目录

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
