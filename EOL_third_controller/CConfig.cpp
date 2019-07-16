#include "StdAfx.h"
#include "CConfig.h"

CConfig::CConfig(string strVIN, Logger *lpLog) {
    TCHAR buf[BUFSIZ];
    int length = 0;

    m_strVIN = strVIN;
    m_strCfgFile = CONFIG_PATH;
    m_strCfgFile += "\\";
    m_strCfgFile += CONFIG_FILE;
    m_lpLog = lpLog;

    bool bFile = false;
    if (_access(m_strCfgFile.c_str(), 0) == 0) {
        bFile = true;
    } else {
        bFile = false;
    }

    for (size_t i = 0; i < DIR_NUM; i++) {
        m_SendFile[0][i].strName = "NCA";
        m_SendFile[1][i].strName = "HLA";
        m_SendFile[2][i].strName = "SideSlip";
        m_SendFile[3][i].strName = "Brake";

        m_ReceFile[0][i].strName = "NCA";
        m_ReceFile[1][i].strName = "HLA";
        m_ReceFile[2][i].strName = "SideSlip";
        m_ReceFile[3][i].strName = "Brake";
    }

    // ¶ÁINIÎÄ¼þ
    if (bFile) {
        m_iWorkStation = GetPrivateProfileInt(_T("Work_Station"), _T("Work_Station"), 0, m_strCfgFile.c_str());
        if (m_iWorkStation > 4 && m_iWorkStation <= 0) {
            WORD wOrigin = setConsoleColor(12, 14);
            cout << "Read Work_Station failed, using default value" << endl;
            setConsoleColor(wOrigin);
            m_lpLog->TRACE_ERR("Read Work_Station failed, using default value");
            m_iWorkStation = 1;
        }
        GetPrivateProfileString(_T("Work_Station"), _T("NCAStateFile"), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strNCAStateFile = buf;
        if (!strcmp(buf, "")) {
            WORD wOrigin = setConsoleColor(12, 14);
            cout << "Read NCAStateFile in Work_Station failed, using default value" << endl;
            setConsoleColor(wOrigin);
            m_lpLog->TRACE_ERR("Read NCAStateFile in Work_Station failed, using default value");
            m_strNCAStateFile = "./NCAStateFile/State.ini";
        }

        string strKey = "";
        for (int i = 0; i < getDirCount(true); i++) {
            strKey = "Dir" + IntToString(i + 1);
            GetPrivateProfileString(_T("Send_File_Path"), strKey.c_str(), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
            m_SendDir[i].strDirPath = buf;
            if (!strcmp(buf, "")) {
                WORD wOrigin = setConsoleColor(12, 14);
                cout << "Read " << strKey << " in Send_File_Path failed, using default value" << endl;
                setConsoleColor(wOrigin);
                m_lpLog->TRACE_ERR("Read %s in Send_File_Path failed, using default value", strKey.c_str());
                m_SendDir[i].strDirPath = string("./SendFile%d", i + 1);
            }
            strKey = "MaxFileNum" + IntToString(i + 1);
            m_SendDir[i].iMaxFileNum = GetPrivateProfileInt(_T("Send_File_Path"), strKey.c_str(), 100, m_strCfgFile.c_str());

            length = this->getSendFileCount();
            for (int j = 0; j < length; j++) {
                GetPrivateProfileString(_T("Send_File_Path"), m_SendFile[j][i].strName.c_str(), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
                m_SendFile[j][i].strFilePath = m_SendDir[i].strDirPath + "/" + buf;
                if (!strcmp(buf, "")) {
                    WORD wOrigin = setConsoleColor(12, 14);
                    cout << "Read " << m_SendFile[j][i].strName << " in Send_File_Path failed, using default value" << endl;
                    setConsoleColor(wOrigin);
                    m_lpLog->TRACE_ERR("Read %s in Send_File_Path failed, using default value", m_SendFile[j][i].strName.c_str());
                    m_SendFile[j][i].strFilePath = m_SendDir[i].strDirPath + "/Send_" + m_SendFile[j][i].strName + "_%VIN%.ini";
                }
            }
        }

        for (int i = 0; i < getDirCount(false); i++) {
            strKey = "Dir" + IntToString(i + 1);
            GetPrivateProfileString(_T("Rece_File_Path"), strKey.c_str(), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
            m_ReceDir[i].strDirPath = buf;
            if (!strcmp(buf, "")) {
                WORD wOrigin = setConsoleColor(12, 14);
                cout << "Read " << strKey << " in Rece_File_Path failed, using default value" << endl;
                setConsoleColor(wOrigin);
                m_lpLog->TRACE_ERR("Read %s in Rece_File_Path failed, using default value", strKey.c_str());
                m_ReceDir[i].strDirPath = string("./ReceFile%d", i + 1);
            }
            strKey = "MaxFileNum" + IntToString(i + 1);
            m_ReceDir[i].iMaxFileNum = GetPrivateProfileInt(_T("Rece_File_Path"), strKey.c_str(), 100, m_strCfgFile.c_str());

            length = this->getReceFileCount();
            for (int j = 0; j < length; j++) {
                GetPrivateProfileString(_T("Rece_File_Path"), m_ReceFile[j][i].strName.c_str(), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
                m_ReceFile[j][i].strFilePath = m_ReceDir[i].strDirPath + "/" + buf;
                if (!strcmp(buf, "")) {
                    WORD wOrigin = setConsoleColor(12, 14);
                    cout << "Read " << m_ReceFile[j][i].strName << " in Rece_File_Path failed, using default value" << endl;
                    setConsoleColor(wOrigin);
                    m_lpLog->TRACE_ERR("Read %s in Rece_File_Path failed, using default value", m_ReceFile[j][i].strName.c_str());
                    m_ReceFile[j][i].strFilePath = m_ReceDir[i].strDirPath + "/Rece_" + m_ReceFile[j][i].strName + "_%VIN%.ini";
                }
            }
        }

        GetPrivateProfileString(_T("DataBase"), _T("IP"), _T("127.0.0.1"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strIP = buf;

        GetPrivateProfileString(_T("DataBase"), _T("Port"), _T("1433"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strPort = buf;

        GetPrivateProfileString(_T("DataBase"), _T("User"), _T("sa"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strUser = buf;

        GetPrivateProfileString(_T("DataBase"), _T("Pwd"), _T("sh49"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strPwd = buf;

        GetPrivateProfileString(_T("DataBase"), _T("DBName"), _T("JAC"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strDBName = buf;

        GetPrivateProfileString(_T("Communication"), _T("INI_Config"), _T("./config/INI_config.ini"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_strINICfgFile = buf;

        m_iType = GetPrivateProfileInt(_T("Communication"), _T("Type"), 1, m_strCfgFile.c_str());

        m_iSleepTime = GetPrivateProfileInt(_T("Communication"), _T("Sleep_Time"), 500, m_strCfgFile.c_str());

        m_iTimeout = GetPrivateProfileInt(_T("Communication"), _T("Timeout"), 600, m_strCfgFile.c_str());

        m_SerialPort.dwPort = (DWORD)GetPrivateProfileInt(_T("Serial_Port"), _T("Port"), 0, m_strCfgFile.c_str());

        m_SerialPort.dwBaudRate = (DWORD)GetPrivateProfileInt(_T("Serial_Port"), _T("Baud_Rate"), 9600, m_strCfgFile.c_str());

        m_SerialPort.btParity = (BYTE)GetPrivateProfileInt(_T("Serial_Port"), _T("Parity"), NOPARITY, m_strCfgFile.c_str());

        m_SerialPort.btByteSize = (BYTE)GetPrivateProfileInt(_T("Serial_Port"), _T("Byte_Size"), 8, m_strCfgFile.c_str());

        m_SerialPort.btStopBits = (BYTE)GetPrivateProfileInt(_T("Serial_Port"), _T("Stop_Bits"), ONESTOPBIT, m_strCfgFile.c_str());

        m_SocketCfg.iPort = GetPrivateProfileInt(_T("Socket"), _T("Port"), 10001, m_strCfgFile.c_str());

        m_SocketCfg.iProtocol = GetPrivateProfileInt(_T("Socket"), _T("Protocol"), 1, m_strCfgFile.c_str());

        GetPrivateProfileString(_T("INIVIN"), _T("FullName"), _T("./ReceFile/Rece_VIN.ini"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_INIVIN.fullName = buf;

        GetPrivateProfileString(_T("INIVIN"), _T("Section"), _T("Data"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_INIVIN.section = buf;

        GetPrivateProfileString(_T("INIVIN"), _T("VIN_Key"), _T("VIN"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_INIVIN.VIN_key = buf;

        GetPrivateProfileString(_T("INIVIN"), _T("Result_Key"), _T("Result"), buf, BUFSIZ, m_strCfgFile.c_str());
        m_INIVIN.Result_key = buf;

    } else {
        WORD wOrigin = setConsoleColor(12, 14);
        cout << "!!Can not access " << m_strCfgFile << "\", Please check this config file!!" << endl;
        setConsoleColor(wOrigin);
        m_lpLog->TRACE_FATAL("!!Can not access \"%s\", Please check this config file!!", m_strCfgFile.c_str());
    }
    this->doReplace();
    this->getINIConfig();
}

CConfig::~CConfig() {}

string CConfig::getVIN() {
    return m_strVIN;
}

int CConfig::getWorkStation() {
    return m_iWorkStation;
}

void CConfig::getSendFile(INIFILE *outSendFile, int index) {
    *outSendFile = m_SendFile[m_iWorkStation - 1][index];
}

int CConfig::getSendFileCount() {
    return sizeof(m_SendFile) / sizeof(m_SendFile[0]);
}

void CConfig::getReceFile(INIFILE *outReceFile, int index) {
    *outReceFile = m_ReceFile[m_iWorkStation - 1][index];
}

int CConfig::getReceFileCount() {
    return sizeof(m_ReceFile) / sizeof(m_ReceFile[0]);
}

void CConfig::doReplace() {
    int length = this->getSendFileCount();
    int iPos = 0;
    int iCount = 0;
    const string pattern = "%VIN%";
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < this->getDirCount(true); j++) {
            iPos = m_SendFile[i][j].strFilePath.find(pattern, 0);
            if (iPos < 0) {
                continue;
            }
            m_SendFile[i][j].strFilePath.replace(iPos, pattern.length(), m_strVIN);
        }
    }

    length = this->getReceFileCount();
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < this->getDirCount(false); j++) {
            iPos = m_ReceFile[i][j].strFilePath.find(pattern, 0);
            if (iPos < 0) {
                continue;
            }
            m_ReceFile[i][j].strFilePath.replace(iPos, pattern.length(), m_strVIN);
        }
    }
}

string CConfig::getIP() {
    return m_strIP;
}

string CConfig::getPort() {
    return m_strPort;
}

string CConfig::getUser() {
    return m_strUser;
}

string CConfig::getPwd() {
    return m_strPwd;
}

string CConfig::getDBName() {
    return m_strDBName;
}

void CConfig::getINIConfig() {
    SECTION section;
    string strSection;
    string strKey;
    TCHAR buf[BUFSIZ];
    int length;

    length = this->getSendFileCount();
    for (int i = 0; i < length; i++) {
        for (int k = 0; k < this->getDirCount(true); k++) {
            strSection = "Send_" + m_SendFile[i][k].strName;
            m_SendFile[i][k].section_num = GetPrivateProfileInt(strSection.c_str(), _T("section_num"), 1, m_strINICfgFile.c_str());
            for (int j = 0; j < m_SendFile[i][k].section_num; j++) {
                strKey = "section" + to_string(j + 1) + "_name";
                GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T(""), buf, BUFSIZ, m_strINICfgFile.c_str());
                section.strName = buf;

                strKey = "section" + to_string(j + 1) + "_start";
                section.start = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), 0, m_strINICfgFile.c_str());

                strKey = "section" + to_string(j + 1) + "_end";
                section.end = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), -1, m_strINICfgFile.c_str());

                m_SendFile[i][k].vSection.push_back(section);
            }
        }
    }

    length = this->getReceFileCount();
    for (int i = 0; i < length; i++) {
        for (int k = 0; k < this->getDirCount(false); k++) {
            strSection = "Rece_" + m_ReceFile[i][k].strName;
            m_ReceFile[i][k].section_num = GetPrivateProfileInt(strSection.c_str(), _T("section_num"), 1, m_strINICfgFile.c_str());
            for (int j = 0; j < m_ReceFile[i][k].section_num; j++) {
                strKey = "section" + to_string(j + 1) + "_name";
                GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T(""), buf, BUFSIZ, m_strINICfgFile.c_str());
                section.strName = buf;

                strKey = "section" + to_string(j + 1) + "_start";
                section.start = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), 0, m_strINICfgFile.c_str());

                strKey = "section" + to_string(j + 1) + "_end";
                section.end = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), -1, m_strINICfgFile.c_str());

                m_ReceFile[i][k].vSection.push_back(section);
            }
        }
    }
}

SERIALPORT CConfig::getSerialPort() {
    return m_SerialPort;
}

SOCKETCFG CConfig::getSocketCfg() {
    return m_SocketCfg;
}

INIVIN CConfig::getINIVIN() {
    return m_INIVIN;
}

int CConfig::getSleepTime() {
    return m_iSleepTime;
}

int CConfig::getTimeout() {
    return m_iTimeout;
}

int CConfig::getType() {
    return m_iType;
}

DIRINFO CConfig::getDirInfo(bool bSend, int index) {
    if (bSend) {
        return m_SendDir[index];
    } else {
        return m_ReceDir[index];
    }
}

int CConfig::getDirCount(bool bSend) {
    if (bSend) {
        return sizeof(m_SendDir) / sizeof(m_SendDir[0]);
    } else {
        return sizeof(m_ReceDir) / sizeof(m_ReceDir[0]);
    }
}

string CConfig::getNCAStateFile() {
    return m_strNCAStateFile;
}
