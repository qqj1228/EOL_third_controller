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
		m_iWorkStation = GetPrivateProfileInt(_T("Work_Station"), _T("Work_Station"), 0, m_strCfgFile.c_str());
		if (m_iWorkStation > 4 && m_iWorkStation <= 0)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Read Work_Station failed, using default value" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Read Work_Station failed, using default value");
			m_iWorkStation = 1;
		}

		GetPrivateProfileString(_T("Send_File_Path"), _T("Dir"), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
		m_SendDir.strDirPath = buf;
		if (!strcmp(buf, "")) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Read Dir in Send_File_Path failed, using default value" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Read Dir in Send_File_Path failed, using default value");
			m_SendDir.strDirPath = "./SendFile/";
		}

		m_SendDir.iMaxFileNum = GetPrivateProfileInt(_T("Send_File_Path"), _T("MaxFileNum"), 100, m_strCfgFile.c_str());

		length= this->getSendFileCount();
		for (int i = 0; i < length; i++)
		{
			GetPrivateProfileString(_T("Send_File_Path"), m_SendFile[i].strName.c_str(), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
			m_SendFile[i].strFilePath = m_SendDir.strDirPath + "/" + buf;
			if (!strcmp(buf, ""))
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Read " << m_SendFile[i].strName << " in Send_File_Path failed, using default value" << endl;
				setConsoleColor(wOrigin);
				m_lpLog->TRACE_ERR("Read %s in Send_File_Path failed, using default value", m_SendFile[i].strName.c_str());
				m_SendFile[i].strFilePath = m_SendDir.strDirPath + "/Send_" + m_SendFile[i].strName + "_%VIN%.ini";
			}
		}

		GetPrivateProfileString(_T("Rece_File_Path"), _T("Dir"), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
		m_ReceDir.strDirPath = buf;
		if (!strcmp(buf, "")) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Read Dir in Rece_File_Path failed, using default value" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Read Dir in Rece_File_Path failed, using default value");
			m_ReceDir.strDirPath = "./ReceFile/";
		}

		m_ReceDir.iMaxFileNum = GetPrivateProfileInt(_T("Rece_File_Path"), _T("MaxFileNum"), 100, m_strCfgFile.c_str());

		length = this->getReceFileCount();
		for (int i = 0; i < length; i++)
		{
			GetPrivateProfileString(_T("Rece_File_Path"), m_ReceFile[i].strName.c_str(), _T(""), buf, BUFSIZ, m_strCfgFile.c_str());
			m_ReceFile[i].strFilePath = m_ReceDir.strDirPath + "/" + buf;
			if (!strcmp(buf, ""))
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Read " << m_ReceFile[i].strName << " in Rece_File_Path failed, using default value" << endl;
				setConsoleColor(wOrigin);
				m_lpLog->TRACE_ERR("Read %s in Rece_File_Path failed, using default value", m_ReceFile[i].strName.c_str());
				m_ReceFile[i].strFilePath = m_ReceDir.strDirPath + "/Rece_" + m_ReceFile[i].strName + "_%VIN%.ini";
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

		m_SerialPort.dwPort = (DWORD)GetPrivateProfileInt(_T("Serial_Port"), _T("Port"), 2, m_strCfgFile.c_str());

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
		dwResult = WritePrivateProfileString(_T("Work_Station"), _T("Work_Station"), _T("1"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Work_Station failed" << endl;
			setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing work_station comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing work_station comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Send_File_Path"), _T("Dir"), _T("./SendFile/"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Dir in Send_File_Path failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Dir in Send_File_Path failed");
		}
		m_SendDir.strDirPath = "./SendFile/";

		dwResult = WritePrivateProfileString(_T("Send_File_Path"), _T("MaxFileNum"), _T("100"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing MaxFileNum in Send_File_Path failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing MaxFileNum in Send_File_Path failed");
		}
		m_SendDir.iMaxFileNum = 100;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open()) {
			outfs << "; <=0, no limit" << endl << endl;
		} else {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing MaxFileNum in Send_File_Path comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing MaxFileNum in Send_File_Path comment failed");
		}
		outfs.close();

		length = this->getSendFileCount();
		for (int i = 0; i < length; i++)
		{
			string strFileName = "Send_" + m_SendFile[i].strName + "_%VIN%.ini";
			dwResult = WritePrivateProfileString(_T("Send_File_Path"), m_SendFile[i].strName.c_str(), strFileName.c_str(), m_strCfgFile.c_str());
			m_SendFile[i].strFilePath = m_SendDir.strDirPath + "/" + strFileName;
			if (!dwResult)
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Writing " << m_SendFile[i].strName << " in Send_File_Path failed" << endl;
				setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Send_File_Path comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Send_File_Path comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Rece_File_Path"), _T("Dir"), _T("./ReceFile/"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Dir in Rece_File_Path failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Dir in Rece_File_Path failed");
		}
		m_ReceDir.strDirPath = "./ReceFile/";

		dwResult = WritePrivateProfileString(_T("Rece_File_Path"), _T("MaxFileNum"), _T("100"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing MaxFileNum in Rece_File_Path failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing MaxFileNum in Rece_File_Path failed");
		}
		m_ReceDir.iMaxFileNum = 100;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open()) {
			outfs << "; <=0, no limit" << endl << endl;
		} else {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing MaxFileNum in Rece_File_Path comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing MaxFileNum in Rece_File_Path comment failed");
		}
		outfs.close();

		length = this->getReceFileCount();
		for (int i = 0; i < length; i++)
		{
			string strFileName = "Rece_" + m_ReceFile[i].strName + "_%VIN%.ini";
			dwResult = WritePrivateProfileString(_T("Rece_File_Path"), m_ReceFile[i].strName.c_str(), strFileName.c_str(), m_strCfgFile.c_str());
			m_ReceFile[i].strFilePath = m_ReceDir.strDirPath + "/" + strFileName;
			if (!dwResult)
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Writing " << m_ReceFile[i].strName << " in Rece_File_Path failed" << endl;
				setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Rece_File_Path comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Rece_File_Path comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("DataBase"), _T("IP"), _T("127.0.0.1"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing IP of DataBase failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing IP of DataBase failed");
		}
		m_strIP = "127.0.0.1";

		dwResult = WritePrivateProfileString(_T("DataBase"), _T("Port"), _T("1433"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Port of DataBase failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Port of DataBase failed");
		}
		m_strPort = "1433";

		dwResult = WritePrivateProfileString(_T("DataBase"), _T("User"), _T("sa"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing User of DataBase failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing User of DataBase failed");
		}
		m_strUser = "sa";

		dwResult = WritePrivateProfileString(_T("DataBase"), _T("Pwd"), _T("sh49"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Pwd of DataBase failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Pwd of DataBase failed");
		}
		m_strPwd = "sh49";

		dwResult = WritePrivateProfileString(_T("DataBase"), _T("DBName"), _T("JAC"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing DBName of DataBase failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing DBName of DataBase failed");
		}
		m_strDBName = "JAC";

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open())
		{
			outfs << endl;
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Communication"), _T("INI_Config"), _T("./config/INI_config.ini"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing INI_Config of Communication failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing INI_Config of Communication failed");
		}
		m_strINICfgFile = "./config/INI_config.ini";

		dwResult = WritePrivateProfileString(_T("Communication"), _T("Type"), _T("1"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Type of Communication failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Type of Communication failed");
		}
		m_iType = 1;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open()) {
			outfs << "; Type = 0, Invalid" << endl;
			outfs << "; Type = 1, Serial_Port" << endl;
			outfs << "; Type = 2, Socket" << endl;
			outfs << "; Type = 3, INIVIN File" << endl << endl;
		} else {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Type comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Type comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Communication"), _T("Sleep_Time"), _T("500"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Sleep_Time of Communication failed" << endl;
			setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Sleep_Time comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Sleep_Time comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Communication"), _T("Timeout"), _T("600"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Timeout of Communication failed" << endl;
			setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Timeout comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Timeout comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Serial_Port"), _T("Port"), _T("2"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Port of Serial_Port failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Port of Serial_Port failed");
		}
		m_SerialPort.dwPort = 2;

		dwResult = WritePrivateProfileString(_T("Serial_Port"), _T("Baud_Rate"), _T("9600"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Baud_Rate of Serial_Port failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Baud_Rate of Serial_Port failed");
		}
		m_SerialPort.dwBaudRate = 9600;

		dwResult = WritePrivateProfileString(_T("Serial_Port"), _T("Parity"), _T("NOPARITY"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Parity of Serial_Port failed" << endl;
			setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Parity comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Parity comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Serial_Port"), _T("Byte_Size"), _T("8"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Byte_Size of Serial_Port failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Byte_Size of Serial_Port failed");
		}
		m_SerialPort.btByteSize = 8;

		dwResult = WritePrivateProfileString(_T("Serial_Port"), _T("Stop_Bits"), _T("ONESTOPBIT"), m_strCfgFile.c_str());
		if (!dwResult)
		{
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Stop_Bits of Serial_Port failed" << endl;
			setConsoleColor(wOrigin);
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
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Stop_Bits comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Stop_Bits comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("Socket"), _T("Port"), _T("10001"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Protocol of Socket failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Protocol of Socket failed");
		}
		m_SocketCfg.iPort = 10001;

		dwResult = WritePrivateProfileString(_T("Socket"), _T("Protocol"), _T("1"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Protocol of Socket failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Protocol of Socket failed");
		}
		m_SocketCfg.iProtocol = 1;

		outfs.open(m_strCfgFile.c_str(), ios::app);
		if (outfs.is_open()) {
			outfs << "; Protocol = 0, Invalid" << endl;
			outfs << "; Protocol = 1, TCP" << endl;
			outfs << "; Protocol = 2, UDP" << endl << endl;
		} else {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Protocol comment failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Protocol comment failed");
		}
		outfs.close();

		dwResult = WritePrivateProfileString(_T("INIVIN"), _T("FullName"), _T("./ReceFile/Rece_VIN.ini"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing FullName of INIVIN failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing FullName of INIVIN failed");
		}
		m_INIVIN.fullName = "./ReceFile/Rece_VIN.ini";

		dwResult = WritePrivateProfileString(_T("INIVIN"), _T("Section"), _T("Data"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Section of INIVIN failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Section of INIVIN failed");
		}
		m_INIVIN.section = "Data";

		dwResult = WritePrivateProfileString(_T("INIVIN"), _T("VIN_Key"), _T("VIN"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing VIN_Key of INIVIN failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing VIN_Key of INIVIN failed");
		}
		m_INIVIN.VIN_key = "VIN";

		dwResult = WritePrivateProfileString(_T("INIVIN"), _T("Result_Key"), _T("Result"), m_strCfgFile.c_str());
		if (!dwResult) {
			WORD wOrigin = setConsoleColor(12, 14);
			cout << "Writing Result_Key of INIVIN failed" << endl;
			setConsoleColor(wOrigin);
			m_lpLog->TRACE_ERR("Writing Result_Key of INIVIN failed");
		}
		m_INIVIN.Result_key = "Result";
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
		m_SendFile[i].section_num = GetPrivateProfileInt(strSection.c_str(), _T("section_num"), 0, m_strINICfgFile.c_str());
		for (int j = 0; j < m_SendFile[i].section_num; j++)
		{
			strKey = "section" + to_string(j + 1) + "_name";
			GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T(""), buf, BUFSIZ, m_strINICfgFile.c_str());
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
		m_ReceFile[i].section_num = GetPrivateProfileInt(strSection.c_str(), _T("section_num"), 0, m_strINICfgFile.c_str());
		for (int j = 0; j < m_ReceFile[i].section_num; j++)
		{
			strKey = "section" + to_string(j + 1) + "_name";
			GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T(""), buf, BUFSIZ, m_strINICfgFile.c_str());
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

SOCKETCFG CConfig::getSocketCfg()
{
	return m_SocketCfg;
}

INIVIN CConfig::getINIVIN() {
	return m_INIVIN;
}

int CConfig::getSleepTime()
{
	return m_iSleepTime;
}

int CConfig::getTimeout()
{
	return m_iTimeout;
}

int CConfig::getType()
{
	return m_iType;
}

DIRINFO CConfig::getDirInfo(bool bSend) {
	if (bSend) {
		return m_SendDir;
	} else {
		return m_ReceDir;
	}
}
