#include "StdAfx.h"
#include "CModel.h"
#include "util.h"


CModel::CModel(CConfig *lpCfg, Logger *lpLog)
{
	m_bDBOK = false;
	m_lpCfg = lpCfg;
	m_lpLog = lpLog;

	m_lpADO = new CADOConn(
		(m_lpCfg->getIP()).c_str(),
		(m_lpCfg->getPort()).c_str(),
		(m_lpCfg->getUser()).c_str(),
		(m_lpCfg->getPwd()).c_str(),
		(m_lpCfg->getDBName()).c_str(),
		lpLog
	);
	if (!m_lpADO->OnInitADOConn())
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "Open DataBase failed!" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_FATAL("Open DataBase failed!");
		return;
	}
	else
	{
		m_bDBOK = true;
	}

	if (m_lpCfg->getVIN() != "")
	{
		InitINIFile();
	}
	InitMapDBTable();
}

CModel::CModel(CConfig *lpCfg, map<string, vector<FIELD>> &mapDBTable, Logger *lpLog)
{
	m_bDBOK = false;
	m_lpCfg = lpCfg;
	m_lpLog = lpLog;

	m_lpADO = new CADOConn(
		(m_lpCfg->getIP()).c_str(),
		(m_lpCfg->getPort()).c_str(),
		(m_lpCfg->getUser()).c_str(),
		(m_lpCfg->getPwd()).c_str(),
		(m_lpCfg->getDBName()).c_str(),
		lpLog
	);
	if (!m_lpADO->OnInitADOConn())
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "Open DataBase failed!" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_FATAL("Open DataBase failed!");
		return;
	}
	else
	{
		m_bDBOK = true;
	}

	if (m_lpCfg->getVIN() != "")
	{
		InitINIFile();
	}
	m_mapDBTable = mapDBTable;
}


CModel::~CModel()
{
	if (m_bDBOK)
	{
		m_lpADO->ExitConnect();
	}
}

bool CModel::WriteSendFile()
{
	DWORD dwResult = 0;
	bool flag = true;
	int length = 0;
	int iStart = 0;
	int iEnd = 0;
	string strSQL;
	string strVehicleType;
	string strSection;
	string strKey;
	string strValue;
	string strTableName;
	vector<FIELD> vFields;

	if (!m_bDBOK)
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "No DataBase connection!" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_FATAL("No DataBase connection!");
		return false;
	}
	string strVIN = m_lpCfg->getVIN();
	m_lpLog->TRACE_INFO("WriteSendFile -- VIN code: %s", strVIN.c_str());
	// 通过VIN码，在VehicleInfo表中，获取到VehicleType
	strSQL = "select * from VehicleInfo where VIN = '" + strVIN + "'";
	m_lpADO->GetRecordSet(strSQL.c_str());
	strVehicleType = m_lpADO->GetRecord("VehicleType", 0);
	if (strVehicleType == "")
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "Get VehicleType from VehicleInfo failed, VIN code: " << strVIN << " is wrong!" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_FATAL("Get VehicleType from VehicleInfo failed, VIN code: %s is wrong!", strVIN.c_str());
		return false;
	}

	dwResult = WritePrivateProfileString(m_SendFile.vSection[0].strName.c_str(), "VIN", strVIN.c_str(), m_SendFile.strFilePath.c_str());
	if (!dwResult)
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "Write VIN failed" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_ERR("Write VIN failed");
		flag = false;
	}

	strTableName = m_SendFile.strName + "Config";
	// 从m_mapDBTable中获取字段信息vector
	vFields = m_mapDBTable.at(strTableName);
	// 执行数据库查询,得到结果记录集
	strSQL = "select * from " + strTableName + " where VehicleType = '" + strVehicleType + "'";
	m_lpADO->GetRecordSet(strSQL.c_str());

	length = m_SendFile.section_num;
	for (int i = 0; i < length; i++)
	{
		strSection = m_SendFile.vSection[i].strName;
		iStart = m_SendFile.vSection[i].start;
		iEnd = m_SendFile.vSection[i].end;
		if (iEnd == -1)
		{
			iEnd = vFields.size() - 1;
		}
		for (int j = iStart; j <= iEnd; j++)
		{
			if (j == 0)
			{
				// Config表，有ID无VIN
				// 故需要跳过第一个字段（ID）
				continue;
			}
			strKey = vFields[j].name;
			// 根据字段名获取记录值
			strValue = string(m_lpADO->GetRecord(strKey.c_str(), 0));
			if (strValue == "")
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Get " << strKey << " from " << strTableName << " failed, VehicleType: " << strVehicleType << " is wrong!" << endl;
				setConsoleColor(wOrigin);
				m_lpLog->TRACE_FATAL("Get %s from %s failed, VehicleType: %s is wrong!", strKey.c_str(), strTableName.c_str(), strVehicleType.c_str());
				return false;
			}
			m_lpLog->TRACE_INFO("WriteSendFile -- Get %s: %s", strKey.c_str(), strValue.c_str());
			dwResult = WritePrivateProfileString(strSection.c_str(), strKey.c_str(), strValue.c_str(), m_SendFile.strFilePath.c_str());
			if (!dwResult)
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Write " << strKey << " : " << strValue << " failed" << endl;
				setConsoleColor(wOrigin);
				m_lpLog->TRACE_ERR("Write %s : %s failed", strKey.c_str(), strValue.c_str());
				flag = false;
			}
		}
	}
	m_lpADO->RecordSetClose();

	UpdateDeleteFileMap(m_multimapDeleteSendFile, true);
	return flag;
}

void CModel::GetTableName(vector<string> *lpvTableName)
{
	_variant_t var;
	string strTableName;
	string strTableType;

	_RecordsetPtr rs = m_lpADO->GetSchemaTables();
	try
	{
		while (!(rs->adoEOF))
		{
			var = rs->Fields->GetItem("TABLE_NAME")->Value;
			strTableName = string(_bstr_t(var));
			var = rs->Fields->GetItem("TABLE_TYPE")->Value;
			strTableType = string(_bstr_t(var));

			if (strTableType == "TABLE")
			{
				lpvTableName->push_back(strTableName);
				m_lpLog->TRACE_INFO("GetTableName: %s", strTableName.c_str());
			}
			rs->MoveNext();
		}
		m_lpADO->RecordSetClose();
	}
	catch (_com_error e)
	{
		WORD wOrigin = setConsoleColor(12, 14);
		if (e.Description() == _bstr_t("")) {
			cout << "COM Error: " << e.ErrorMessage() << endl;
			m_lpLog->TRACE_ERR("COM Error: %s", e.ErrorMessage());
		} else {
			cout << "COM Error: " << e.Description() << endl;
			m_lpLog->TRACE_ERR("COM Error: %s", (char *)e.Description());
		}
		setConsoleColor(wOrigin);
	}
	cout << "GetTableName finished" << endl;
	m_lpLog->TRACE_INFO("GetTableName finished");
}

void CModel::GetColumns(string strTableName, vector<FIELD> *lpvColumns)
{
	string strSQL;
	_bstr_t bstrColName;
	string strColName;
	long nColCount;
	Field *field = NULL;
	Fields *fields = NULL;
	FIELD column;

	strSQL = "select * from " + strTableName;
	try
	{
		m_lpADO->m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_lpADO->m_pRecordset->Open(strSQL.c_str(), m_lpADO->m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		m_lpADO->m_pRecordset->get_Fields(&fields);

		fields->get_Count(&nColCount);
		for (long i = 0; i < nColCount; i++)
		{
			fields->Item[i]->get_Name(bstrColName.GetAddress());
			fields->Item[i]->get_DefinedSize(&column.length);
			column.name = string(bstrColName);
			lpvColumns->push_back(column);
			m_lpLog->TRACE_INFO("Table Name: %s, Column Name: %s, Column length: %d", strTableName.c_str(), column.name.c_str(), column.length);
		}
		fields->Release();
		m_lpADO->RecordSetClose();
	}
	catch (_com_error e)
	{
		WORD wOrigin = setConsoleColor(12, 14);
		if (e.Description() == _bstr_t("")) {
			cout << "COM Error: " << e.ErrorMessage() << endl;
			m_lpLog->TRACE_ERR("COM Error: %s", e.ErrorMessage());
		} else {
			cout << "COM Error: " << e.Description() << endl;
			m_lpLog->TRACE_ERR("COM Error: %s", (char *)e.Description());
		}
		setConsoleColor(wOrigin);
	}
}

void CModel::InitMapDBTable()
{
	if (!m_bDBOK)
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "No DataBase connection!" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_FATAL("No DataBase connection!");
		return;
	}
	vector<string> vTableName;
	vector<FIELD> vFields;

	m_lpLog->TRACE_INFO("Start InitMapDBTable");

	GetTableName(&vTableName);

	vector<string>::iterator iter;
	vector<string>::iterator end = vTableName.end();
	for (iter = vTableName.begin(); iter != end; ++iter)
	{
		vector<FIELD> vColumns;
		GetColumns(*iter, &vColumns);
		m_mapDBTable.insert(pair<string, vector<FIELD>>(*iter, vColumns));
	}
	m_lpLog->TRACE_INFO("Finish InitMapDBTable");
}

void CModel::InitINIFile()
{
	m_lpCfg->getSendFile(&m_SendFile);
	cout << "Send File Path: " << m_SendFile.strFilePath << endl;
	m_lpLog->TRACE_INFO("Send File Path: %s", m_SendFile.strFilePath.c_str());
	m_lpCfg->getReceFile(m_ReceFile);
	cout << "Receive File Path " << 1 << ": " << m_ReceFile[0].strFilePath << endl;
	m_lpLog->TRACE_INFO("Receive File Path %d: %s", 1, m_ReceFile[0].strFilePath.c_str());
	for (int i = 1; i < 3; i++)
	{
		if (m_ReceFile[i].strFilePath != m_ReceFile[0].strFilePath)
		{
			cout << "Receive File Path " << i + 1 << ": " << m_ReceFile[i].strFilePath << endl;
			m_lpLog->TRACE_INFO("Receive File Path %d: %s", i + 1, m_ReceFile[i].strFilePath.c_str());
		}
	}
}

bool CModel::ReadReceFile()
{
	bool flag = true;
	if (!m_bDBOK)
	{
		WORD wOrigin = setConsoleColor(12, 14);
		cout << "No DataBase connection!" << endl;
		setConsoleColor(wOrigin);
		m_lpLog->TRACE_FATAL("No DataBase connection!");
		return false;
	}
	if (!ReadReceFileSingle(0))
	{
		flag = false;
	}
	for (int i = 1; i < 3; i++)
	{
		if (m_ReceFile[0].strName != m_ReceFile[i].strName)
		{
			// 处理NCACaster和NCATurningAngle结果文件
			// 这两个检测项目是抽检项目，不一定每次都有，故不处理返回值
			// FORI没有发送这两个项目的结果文件，程序就跳过不处理
			ReadReceFileSingle(i);
		}
	}

	UpdateDeleteFileMap(m_multimapDeleteReceFile, false);
	return flag;
}

bool CModel::ReadReceFileSingle(int iIndex)
{
	int length = 0;
	int iStart = 0;
	int iEnd = 0;
	string strSQL;
	string strTableName;
	string strColumns;
	string strSection;
	string strKey;
	vector<FIELD> vFields;
	TCHAR buf[BUFSIZ];
	string strNor;

	if (_access(m_ReceFile[iIndex].strFilePath.c_str(), 0) != 0)
	{
		return false;
	}
	strTableName = m_ReceFile[iIndex].strName + "Result";
	// 从m_mapDBTable中获取字段信息vector
	vFields = m_mapDBTable.at(strTableName);
	strSQL = "insert " + strTableName + " values (";

	length = m_ReceFile[iIndex].section_num;
	for (int i = 0; i < length; i++)
	{
		strSection = m_ReceFile[iIndex].vSection[i].strName;
		// Result表，有ID有VIN
		// 故需要在得到的位置上加1
		iStart = m_ReceFile[iIndex].vSection[i].start + 1;
		iEnd = m_ReceFile[iIndex].vSection[i].end + 1;
		if (iEnd == 0)
		{
			iEnd = vFields.size() - 1;
		}
		for (int j = iStart; j <= iEnd; j++)
		{
			strKey = vFields[j].name;
			GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T(""), buf, BUFSIZ, m_ReceFile[iIndex].strFilePath.c_str());
			if (!strcmp(buf, ""))
			{
				WORD wOrigin = setConsoleColor(12, 14);
				cout << "Read " << strKey << " in " << strSection << " failed" << endl;
				setConsoleColor(wOrigin);
				m_lpLog->TRACE_ERR("Read %s in %s failed", strKey.c_str(), strSection.c_str());
			}
			strNor = Normalize(buf, (size_t)vFields[j].length);
			m_lpLog->TRACE_INFO("ReadReceFileSingle -- Get %s: %s", strKey.c_str(), strNor.c_str());
			strSQL += "'";
			strSQL += strNor;
			strSQL += "',";
		}
	}
	strSQL += ")";
	strSQL.erase(strSQL.rfind(","), 1);
	m_lpADO->ExecuteSQL(strSQL.c_str());
	return true;
}

map<string, vector<FIELD>> CModel::GetMapDBTable()
{
	return m_mapDBTable;
}

void CModel::InitDeleteFileMap(multimap<time_t, string> &deleteFile, bool bSend) {
	long handle;
	struct _finddata_t fileInfo;

	string strDir = m_lpCfg->getDirInfo(bSend).m_strDirPath + "/*";
	handle = _findfirst(strDir.c_str(), &fileInfo);
	if (handle != -1) {
		do {
			// 去除文件夹
			if (!(fileInfo.attrib & _A_SUBDIR)) {
				deleteFile.insert(pair<time_t, string>(fileInfo.time_write, m_lpCfg->getDirInfo(bSend).m_strDirPath + fileInfo.name));
			}
		} while (!_findnext(handle, &fileInfo));
		_findclose(handle);

#ifdef _DEBUG
		multimap<time_t, string>::iterator iter;
		multimap<time_t, string>::iterator end = deleteFile.end();
		for (iter = deleteFile.begin(); iter != end; ++iter) {
			cout << iter->first << " - " << iter->second << endl;
		}
		cout << "============================" << endl;
#endif // _DEBUG

	} else {
		char err[BUFSIZ];
		_strerror_s(err, nullptr);
		cout << "_findfirst " << m_lpCfg->getDirInfo(bSend).m_strDirPath << " error: " << err << endl;
	}
}

void CModel::InitDeleteFileMap() {
	InitDeleteFileMap(m_multimapDeleteSendFile, true);
	InitDeleteFileMap(m_multimapDeleteReceFile, false);
}

void CModel::UpdateDeleteFileMap(multimap<time_t, string> &deleteFile, bool bSend) {
	InitDeleteFileMap(deleteFile, bSend);
	int count = deleteFile.size() - (m_lpCfg->getDirInfo(bSend)).m_iMaxFileNum;
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			remove(deleteFile.begin()->second.c_str());
			deleteFile.erase(deleteFile.begin());
		}
	}
}