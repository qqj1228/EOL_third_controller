#include "StdAfx.h"
#include "CConfig.h"

CConfig::CConfig(string strVIN, Logger *lpLog)
{
	TCHAR buf[BUFSIZ];
	int length = 0;

	m_strVIN = strVIN;
	m_strCfgFile = CONFIG_PATH;
	m_strCfgFile += "\\";
	m_strCfgFile += CONFIG_FILE;
	m_lpLog = lpLog;

	bool bFile = false;
	if (_access(m_strCfgFile.c_str(), 0) == 0)
	{
		bFile = true;
	}
	else
	{
		bFile = false;
	}

	m_SendFile[0].strName = "NCA";
	m_SendFile[1].strName = "HLA";
	m_SendFile[2].strName = "SideSlip";
	m_SendFile[3].strName = "Brake";

	m_ReceFile[0].strName = "NCAToeCamber";
	m_ReceFile[1].strName = "NCACaster";
	m_ReceFile[2].strName = "NCATurningAngle";
	m_ReceFile[3].strName = "HLA";
	m_ReceFile[4].strName = "SideSlip";
	m_ReceFile[5].strName = "Brake";

	if (bFile) // 读INI文件
	{
		m_iWorkStation = GetPrivateProfileInt(TEXT("Work_Station"), TEXT("Work_Station"), 0, m_strCfgFile.c_str());
		if (m_iWorkStation > 4 && m_iWorkStation <= 0)
		{
			cout << "Read Work_Station failed, using default value" << endl;
			m_lpLog->TRACE_ERR("Read Work_Station failed, using default value");
			m_iWorkStation = 1;
		}

		length= this->getSendFileCount();
		for (int i = 0; i < length; i++)
		{
			GetPrivateProfileString(TEXT("Send_File_Path"), m_SendFile[i].strName.c_str(), TEXT(""), buf, BUFSIZ, m_strCfgFile.c_str());
			m_SendFile[i].strFilePath = buf;
			if (!strcmp(buf, ""))
			{
				cout << "Read " << m_SendFile[i].strName << " in Send_File_Path failed, using default value" << endl;
				m_lpLog->TRACE_ERR("Read %s in Send_File_Path failed, using default value", m_SendFile[i].strName.c_str());
				m_SendFile[i].strFilePath = "Send_" + m_SendFile[i].strName + "_%VIN%.ini";
			}
		}

		length = this->getReceFileCount();
		for (int i = 0; i < length; i++)
		{
			GetPrivateProfileString(TEXT("Rece_File_Path"), m_ReceFile[i].strName.c_str(), TEXT(""), buf, BUFSIZ, m_strCfgFile.c_str());
			m_ReceFile[i].strFilePath = buf;
			if (!strcmp(buf, ""))
			{
				cout << "Read " << m_ReceFile[i].strName << " in Rece_File_Path failed, using default value" << endl;
				m_lpLog->TRACE_ERR("Read %s in Rece_File_Path failed, using default value", m_ReceFile[i].strName.c_str());
				m_ReceFile[i].strFilePath = "Rece_" + m_ReceFile[i].strName + "_%VIN%.ini";
			}
		}

		GetPrivateProfileString(TEXT("DataBase"), TEXT("IP"), TEXT("127.0.0.1"), buf, BUFSIZ, m_strCfgFile.c_str());
		m_strIP = buf;

		GetPrivateProfileString(TEXT("DataBase"), TEXT("Port"), TEXT("2272"), buf, BUFSIZ, m_strCfgFile.c_str());
		m_strPort = buf;

		GetPrivateProfileString(TEXT("DataBase"), TEXT("User"), TEXT("sa"), buf, BUFSIZ, m_strCfgFile.c_str());
		m_strUser = buf;

		GetPrivateProfileString(TEXT("DataBase"), TEXT("Pwd"), TEXT("sh49"), buf, BUFSIZ, m_strCfgFile.c_str());
		m_strPwd = buf;

		GetPrivateProfileString(TEXT("DataBase"), TEXT("DBName"), TEXT("JAC"), buf, BUFSIZ, m_strCfgFile.c_str());
		m_strDBName = buf;

		GetPrivateProfileString(TEXT("Communication"), TEXT("INI_Config"), TEXT("./config/INI_config.ini"), buf, BUFSIZ, m_strCfgFile.c_str());
		m_strINICfgFile = buf;

		m_iSleepTime = GetPrivateProfileInt(TEXT("Communication"), TEXT("Sleep_Time"), 500, m_strCfgFile.c_str());

		m_iTimeout = GetPrivateProfileInt(TEXT("Communication"), TEXT("Timeout"), 600, m_strCfgFile.c_str());

		m_SerialPort.dwPort = (DWORD)GetPrivateProfileInt(TEXT("Serial_Port"), TEXT("Port"), 2, m_strCfgFile.c_str());

		m_SerialPort.dwBaudRate = (DWORD)GetPrivateProfileInt(TEXT("Serial_Port"), TEXT("Baud_Rate"), 9600, m_strCfgFile.c_str());

		m_SerialPort.btParity = (BYTE)GetPrivateProfileInt(TEXT("Serial_Port"), TEXT("Parity"), NOPARITY, m_strCfgFile.c_str());

		m_SerialPort.btByteSize = (BYTE)GetPrivateProfileInt(TEXT("Serial_Port"), TEXT("Byte_Size"), 8, m_strCfgFile.c_str());

		m_SerialPort.btStopBits = (BYTE)GetPrivateProfileInt(TEXT("Serial_Port"), TEXT("Stop_Bits"), ONESTOPBIT, m_strCfgFile.c_str());

	}
	else // 生成默认INI文件
	{
		cout << "Didn't find config.ini, creating default file" << endl;
		m_lpLog->TraceInfo("Didn't find config.ini, creating default file");
		// 建立config文件夹
		string strCfgPath = CONFIG_PATH;
		strCfgPath += "\\";
		mkMultiDir(strCfgPath);

		DWORD dwResult = 0;
		dwResult = WritePrivateProfileString(TEXT("Work_Station"), TEXT("Work_Station"), TEXT("1"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Work_Station failed" << endl;
			m_lpLog->TRACE_ERR("Writing Work_Station failed");
		}
		m_iWorkStation = 1;

		ofstream outfs;
		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; work_station = 0, Invalid" << endl;
			outfs << "; work_station = 1, NCA" << endl;
			outfs << "; work_station = 2, HLA" << endl;
			outfs << "; work_station = 3, SideSlip" << endl;
			outfs << "; work_station = 4, Brake" << endl << endl;
		}
		else
		{
			cout << "Writing work_station comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing work_station comment failed");
		}
		outfs.close();

		length = this->getSendFileCount();
		for (int i = 0; i < length; i++)
		{
			m_SendFile[i].strFilePath = "./SendFile/Send_" + m_SendFile[i].strName + "_%VIN%.ini";
			dwResult = WritePrivateProfileString(TEXT("Send_File_Path"), m_SendFile[i].strName.c_str(), m_SendFile[i].strFilePath.c_str(), m_strCfgFile.c_str());
			if (!dwResult)
			{
				cout << "Writing " << m_SendFile[i].strName << " in Send_File_Path failed" << endl;
				m_lpLog->TRACE_ERR("Writing %s in Send_File_Path failed", m_SendFile[i].strName.c_str());
			}
		}

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; %VIN% - VIN Code" << endl << endl;
		}
		else
		{
			cout << "Writing Send_File_Path comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing Send_File_Path comment failed");
		}
		outfs.close();

		length = this->getReceFileCount();
		for (int i = 0; i < length; i++)
		{
			m_ReceFile[i].strFilePath = "./ReceFile/Rece_" + m_ReceFile[i].strName + "_%VIN%.ini";
			dwResult = WritePrivateProfileString(TEXT("Rece_File_Path"), m_ReceFile[i].strName.c_str(), m_ReceFile[i].strFilePath.c_str(), m_strCfgFile.c_str());
			if (!dwResult)
			{
				cout << "Writing " << m_ReceFile[i].strName << " in Rece_File_Path failed" << endl;
				m_lpLog->TRACE_ERR("Writing %s in Rece_File_Path failed", m_ReceFile[i].strName.c_str());
			}
		}

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; %VIN% - VIN Code" << endl << endl;
		}
		else
		{
			cout << "Writing Rece_File_Path comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing Rece_File_Path comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(TEXT("DataBase"), TEXT("IP"), TEXT("127.0.0.1"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing IP of DataBase failed" << endl;
			m_lpLog->TRACE_ERR("Writing IP of DataBase failed");
		}
		m_strIP = "127.0.0.1";

		dwResult = WritePrivateProfileString(TEXT("DataBase"), TEXT("Port"), TEXT("2272"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Port of DataBase failed" << endl;
			m_lpLog->TRACE_ERR("Writing Port of DataBase failed");
		}
		m_strPort = "2272";

		dwResult = WritePrivateProfileString(TEXT("DataBase"), TEXT("User"), TEXT("sa"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing User of DataBase failed" << endl;
			m_lpLog->TRACE_ERR("Writing User of DataBase failed");
		}
		m_strUser = "sa";

		dwResult = WritePrivateProfileString(TEXT("DataBase"), TEXT("Pwd"), TEXT("sh49"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Pwd of DataBase failed" << endl;
			m_lpLog->TRACE_ERR("Writing Pwd of DataBase failed");
		}
		m_strPwd = "sh49";

		dwResult = WritePrivateProfileString(TEXT("DataBase"), TEXT("DBName"), TEXT("JAC"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing DBName of DataBase failed" << endl;
			m_lpLog->TRACE_ERR("Writing DBName of DataBase failed");
		}
		m_strDBName = "JAC";

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << endl;
		}
		outfs.close();

		dwResult = WritePrivateProfileString(TEXT("Communication"), TEXT("INI_Config"), TEXT("./config/INI_config.ini"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing INI_Config of Communication failed" << endl;
			m_lpLog->TRACE_ERR("Writing INI_Config of Communication failed");
		}
		m_strINICfgFile = "./config/INI_config.ini";

		dwResult = WritePrivateProfileString(TEXT("Communication"), TEXT("Sleep_Time"), TEXT("500"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Sleep_Time of Communication failed" << endl;
			m_lpLog->TRACE_ERR("Writing Sleep_Time in Communication failed");
		}
		m_iSleepTime = 500;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; Unit - millisecond" << endl << endl;
		}
		else
		{
			cout << "Writing Sleep_Time comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing Sleep_Time comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(TEXT("Communication"), TEXT("Timeout"), TEXT("600"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Timeout of Communication failed" << endl;
			m_lpLog->TRACE_ERR("Writing Timeout in Communication failed");
		}
		m_iTimeout = 600;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; Unit - second" << endl << endl;
		}
		else
		{
			cout << "Writing Timeout comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing Timeout comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(TEXT("Serial_Port"), TEXT("Port"), TEXT("2"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Port of Serial_Port failed" << endl;
			m_lpLog->TRACE_ERR("Writing Port of Serial_Port failed");
		}
		m_SerialPort.dwPort = 2;

		dwResult = WritePrivateProfileString(TEXT("Serial_Port"), TEXT("Baud_Rate"), TEXT("9600"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Baud_Rate of Serial_Port failed" << endl;
			m_lpLog->TRACE_ERR("Writing Baud_Rate of Serial_Port failed");
		}
		m_SerialPort.dwBaudRate = 9600;

		dwResult = WritePrivateProfileString(TEXT("Serial_Port"), TEXT("Parity"), TEXT("NOPARITY"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Parity of Serial_Port failed" << endl;
			m_lpLog->TRACE_ERR("Writing Parity of Serial_Port failed");
		}
		m_SerialPort.btParity = NOPARITY;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; Parity - NOPARITY" << endl;
			outfs << "; Parity - ODDPARITY" << endl;
			outfs << "; Parity - EVENPARITY" << endl;
			outfs << "; Parity - MARKPARITY" << endl;
			outfs << "; Parity - SPACEPARITY" << endl << endl;
		}
		else
		{
			cout << "Writing Parity comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing Parity comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(TEXT("Serial_Port"), TEXT("Byte_Size"), TEXT("8"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Byte_Size of Serial_Port failed" << endl;
			m_lpLog->TRACE_ERR("Writing Byte_Size of Serial_Port failed");
		}
		m_SerialPort.btByteSize = 8;

		dwResult = WritePrivateProfileString(TEXT("Serial_Port"), TEXT("Stop_Bits"), TEXT("ONESTOPBIT"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			cout << "Writing Stop_Bits of Serial_Port failed" << endl;
			m_lpLog->TRACE_ERR("Writing Stop_Bits of Serial_Port failed");
		}
		m_SerialPort.btStopBits = ONESTOPBIT;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << "; Stop_Bits - ONESTOPBIT" << endl;
			outfs << "; Stop_Bits - ONE5STOPBITS" << endl;
			outfs << "; Stop_Bits - TWOSTOPBITS" << endl << endl;
		}
		else
		{
			cout << "Writing Stop_Bits comment failed" << endl;
			m_lpLog->TRACE_ERR("Writing Stop_Bits comment failed");
		}
		outfs.close();
	}
	this->doReplace();
	this->getINIConfig();
}

CConfig::~CConfig()
{
}

string CConfig::getVIN()
{
	return m_strVIN;
}

int CConfig::getWorkStation()
{
	return m_iWorkStation;
}

void CConfig::getSendFile(INIFILE *outSendFile)
{
	*outSendFile = m_SendFile[m_iWorkStation - 1];
}

int CConfig::getSendFileCount()
{
	return sizeof(m_SendFile) / sizeof(m_SendFile[0]);
}

void CConfig::getReceFile(INIFILE *outReceFile)
{
	switch (m_iWorkStation)
	{
	case 1:
		outReceFile[0] = m_ReceFile[0];
		outReceFile[1] = m_ReceFile[1];
		outReceFile[2] = m_ReceFile[2];
		break;
	case 2:
		outReceFile[0] = m_ReceFile[3];
		outReceFile[1] = m_ReceFile[3];
		outReceFile[2] = m_ReceFile[3];
		break;
	case 3:
		outReceFile[0] = m_ReceFile[4];
		outReceFile[1] = m_ReceFile[4];
		outReceFile[2] = m_ReceFile[4];
		break;
	case 4:
		outReceFile[0] = m_ReceFile[5];
		outReceFile[1] = m_ReceFile[5];
		outReceFile[2] = m_ReceFile[5];
		break;
	default:
		break;
	}
}

int CConfig::getReceFileCount()
{
	return sizeof(m_ReceFile) / sizeof(m_ReceFile[0]);
}

void CConfig::doReplace()
{
	int length = this->getSendFileCount();
	int iPos = 0;
	int iCount = 0;
	for (int i = 0; i < length; i++)
	{
		iPos = m_SendFile[i].strFilePath.find("%VIN%", 0);
		if (iPos < 0)
		{
			continue;
		}
		m_SendFile[i].strFilePath.replace(iPos, 5, m_strVIN);
	}

	length = this->getReceFileCount();
	for (int i = 0; i < length; i++)
	{
		iPos = m_ReceFile[i].strFilePath.find("%VIN%", 0);
		if (iPos < 0)
		{
			continue;
		}
		m_ReceFile[i].strFilePath.replace(iPos, 5, m_strVIN);
	}
}

string CConfig::getIP()
{
	return m_strIP;
}

string CConfig::getPort()
{
	return m_strPort;
}

string CConfig::getUser()
{
	return m_strUser;
}

string CConfig::getPwd()
{
	return m_strPwd;
}

string CConfig::getDBName()
{
	return m_strDBName;
}

void CConfig::getINIConfig()
{
	SECTION section;
	string strSection;
	string strKey;
	TCHAR buf[BUFSIZ];
	int length;

	length = this->getSendFileCount();
	for (int i = 0; i < length; i++)
	{
		strSection = "Send_" + m_SendFile[i].strName;
		m_SendFile[i].section_num = GetPrivateProfileInt(strSection.c_str(), TEXT("section_num"), 0, m_strINICfgFile.c_str());
		for (int j = 0; j < m_SendFile[i].section_num; j++)
		{
			strKey = "section" + to_string(j + 1) + "_name";
			GetPrivateProfileString(strSection.c_str(), strKey.c_str(), TEXT(""), buf, BUFSIZ, m_strINICfgFile.c_str());
			section.strName = buf;

			strKey = "section" + to_string(j + 1) + "_start";
			section.start = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), 0, m_strINICfgFile.c_str());

			strKey = "section" + to_string(j + 1) + "_end";
			section.end = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), 0, m_strINICfgFile.c_str());

			m_SendFile[i].vSection.push_back(section);
		}
	}

	length = this->getReceFileCount();
	for (int i = 0; i < length; i++)
	{
		strSection = "Rece_" + m_ReceFile[i].strName;
		m_ReceFile[i].section_num = GetPrivateProfileInt(strSection.c_str(), TEXT("section_num"), 0, m_strINICfgFile.c_str());
		for (int j = 0; j < m_ReceFile[i].section_num; j++)
		{
			strKey = "section" + to_string(j + 1) + "_name";
			GetPrivateProfileString(strSection.c_str(), strKey.c_str(), TEXT(""), buf, BUFSIZ, m_strINICfgFile.c_str());
			section.strName = buf;

			strKey = "section" + to_string(j + 1) + "_start";
			section.start = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), 0, m_strINICfgFile.c_str());

			strKey = "section" + to_string(j + 1) + "_end";
			section.end = GetPrivateProfileInt(strSection.c_str(), strKey.c_str(), 0, m_strINICfgFile.c_str());

			m_ReceFile[i].vSection.push_back(section);
		}
	}
}

SERIALPORT CConfig::getSerialPort()
{
	return m_SerialPort;
}

int CConfig::getSleepTime()
{
	return m_iSleepTime;
}

int CConfig::getTimeout()
{
	return m_iTimeout;
}
