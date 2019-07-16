#include "StdAfx.h"
#include "CModel.h"
#include "util.h"


CModel::CModel(CConfig *lpCfg, Logger *lpLog) {
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
    if (!m_lpADO->OnInitADOConn()) {
        WORD wOrigin = setConsoleColor(12, 14);
        cout << "Open DataBase failed!" << endl;
        setConsoleColor(wOrigin);
        m_lpLog->TRACE_FATAL("Open DataBase failed!");
        return;
    } else {
        m_bDBOK = true;
    }

    if (m_lpCfg->getVIN() != "") {
        InitINIFile();
    }
    InitMapDBTable();
    InitDeleteFileMap();
}

CModel::CModel(CConfig *lpCfg, map<string, vector<FIELD>> &mapDBTable, Logger *lpLog) {
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
    if (!m_lpADO->OnInitADOConn()) {
        WORD wOrigin = setConsoleColor(12, 14);
        cout << "Open DataBase failed!" << endl;
        setConsoleColor(wOrigin);
        m_lpLog->TRACE_FATAL("Open DataBase failed!");
        return;
    } else {
        m_bDBOK = true;
    }

    if (m_lpCfg->getVIN() != "") {
        InitINIFile();
    }
    m_mapDBTable = mapDBTable;
    InitDeleteFileMap();
}


CModel::~CModel() {
    if (m_bDBOK) {
        m_lpADO->ExitConnect();
    }
}

bool CModel::WriteSendFile() {
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

    if (!m_bDBOK) {
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
    if (strVehicleType == "") {
        WORD wOrigin = setConsoleColor(12, 14);
        cout << "Get VehicleType from VehicleInfo failed, VIN code: " << strVIN << " is wrong!" << endl;
        setConsoleColor(wOrigin);
        m_lpLog->TRACE_FATAL("Get VehicleType from VehicleInfo failed, VIN code: %s is wrong!", strVIN.c_str());
        return false;
    }

    for (int k = 0; k < m_lpCfg->getDirCount(true); k++) {
        dwResult = WritePrivateProfileString(m_SendFile[k].vSection[0].strName.c_str(), "VIN", strVIN.c_str(), m_SendFile[k].strFilePath.c_str());
        if (!dwResult) {
            WORD wOrigin = setConsoleColor(12, 14);
            cout << "Write VIN failed" << endl;
            setConsoleColor(wOrigin);
            m_lpLog->TRACE_ERR("Write VIN failed");
            flag = false;
        }

        strTableName = m_SendFile[k].strName + "Config";
        // 从m_mapDBTable中获取字段信息vector
        vFields = m_mapDBTable.at(strTableName);
        // 执行数据库查询,得到结果记录集
        strSQL = "select * from " + strTableName + " where VehicleType = '" + strVehicleType + "'";
        m_lpADO->GetRecordSet(strSQL.c_str());

        length = m_SendFile[k].section_num;
        for (int i = 0; i < length; i++) {
            strSection = m_SendFile[k].vSection[i].strName;
            iStart = m_SendFile[k].vSection[i].start;
            iEnd = m_SendFile[k].vSection[i].end;
            if (iEnd == -1) {
                iEnd = vFields.size() - 1;
            }
            for (int j = iStart; j <= iEnd; j++) {
                if (j == 0) {
                    // Config表，有ID无VIN
                    // 故需要跳过第一个字段（ID）
                    continue;
                }
                strKey = vFields[j].name;
                // 根据字段名获取记录值
                strValue = string(m_lpADO->GetRecord(strKey.c_str(), 0));
                if (strValue == "") {
                    WORD wOrigin = setConsoleColor(12, 14);
                    cout << "Get " << strKey << " from " << strTableName << " failed, VehicleType: " << strVehicleType << " is wrong!" << endl;
                    setConsoleColor(wOrigin);
                    m_lpLog->TRACE_FATAL("Get %s from %s failed, VehicleType: %s is wrong!", strKey.c_str(), strTableName.c_str(), strVehicleType.c_str());
                    return false;
                }
                m_lpLog->TRACE_INFO("WriteSendFile -- Get %s: %s", strKey.c_str(), strValue.c_str());
                dwResult = WritePrivateProfileString(strSection.c_str(), strKey.c_str(), strValue.c_str(), m_SendFile[k].strFilePath.c_str());
                if (!dwResult) {
                    WORD wOrigin = setConsoleColor(12, 14);
                    cout << "Write " << strKey << " : " << strValue << " failed" << endl;
                    setConsoleColor(wOrigin);
                    m_lpLog->TRACE_ERR("Write %s : %s failed", strKey.c_str(), strValue.c_str());
                    flag = false;
                }
            }
        }
    }
    m_lpADO->RecordSetClose();

    for (int i = 0; i < m_lpCfg->getDirCount(true); i++) {
        UpdateDeleteFileMap(m_multimapDeleteSendFile[i], i, true);
    }
    return flag;
}

void CModel::GetTableName(vector<string> *lpvTableName) {
    _variant_t var;
    string strTableName;
    string strTableType;

    _RecordsetPtr rs = m_lpADO->GetSchemaTables();
    try {
        while (!(rs->adoEOF)) {
            var = rs->Fields->GetItem("TABLE_NAME")->Value;
            strTableName = string(_bstr_t(var));
            var = rs->Fields->GetItem("TABLE_TYPE")->Value;
            strTableType = string(_bstr_t(var));

            if (strTableType == "TABLE") {
                lpvTableName->push_back(strTableName);
                m_lpLog->TRACE_INFO("GetTableName: %s", strTableName.c_str());
            }
            rs->MoveNext();
        }
        m_lpADO->RecordSetClose();
    } catch (_com_error e) {
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

void CModel::GetColumns(string strTableName, vector<FIELD> *lpvColumns) {
    string strSQL;
    _bstr_t bstrColName;
    string strColName;
    long nColCount;
    Field *field = NULL;
    Fields *fields = NULL;
    FIELD column;

    strSQL = "select * from " + strTableName;
    try {
        m_lpADO->m_pRecordset.CreateInstance(__uuidof(Recordset));
        m_lpADO->m_pRecordset->Open(strSQL.c_str(), m_lpADO->m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
        m_lpADO->m_pRecordset->get_Fields(&fields);

        fields->get_Count(&nColCount);
        for (long i = 0; i < nColCount; i++) {
            fields->Item[i]->get_Name(bstrColName.GetAddress());
            fields->Item[i]->get_DefinedSize(&column.length);
            column.name = string(bstrColName);
            lpvColumns->push_back(column);
            m_lpLog->TRACE_INFO("Table Name: %s, Column Name: %s, Column length: %d", strTableName.c_str(), column.name.c_str(), column.length);
        }
        fields->Release();
        m_lpADO->RecordSetClose();
    } catch (_com_error e) {
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

void CModel::InitMapDBTable() {
    if (!m_bDBOK) {
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
    for (iter = vTableName.begin(); iter != end; ++iter) {
        vector<FIELD> vColumns;
        GetColumns(*iter, &vColumns);
        m_mapDBTable.insert(pair<string, vector<FIELD>>(*iter, vColumns));
    }
    m_lpLog->TRACE_INFO("Finish InitMapDBTable");
}

void CModel::InitINIFile() {
    for (int i = 0; i < m_lpCfg->getDirCount(true); i++) {
        m_lpCfg->getSendFile(&m_SendFile[i], i);
        cout << "Send File Path" << i + 1 << ": " << m_SendFile[i].strFilePath << endl;
        m_lpLog->TRACE_INFO("Send File Path%d: %s", i + 1, m_SendFile[i].strFilePath.c_str());
    }
    for (int i = 0; i < m_lpCfg->getDirCount(false); i++) {
        m_lpCfg->getReceFile(&m_ReceFile[i], i);
        cout << "Receive File Path" << i + 1 << ": " << m_ReceFile[i].strFilePath << endl;
        m_lpLog->TRACE_INFO("Receive File Path%d: %s", i + 1, m_ReceFile[i].strFilePath.c_str());
    }
    cout << "Work Station: \"" << m_SendFile[0].strName << "\"" << endl;
    cout << "----------------------------------------------------------" << endl;
}

bool CModel::ReadReceFile() {
    bool flag = true;
    if (!m_bDBOK) {
        WORD wOrigin = setConsoleColor(12, 14);
        cout << "No DataBase connection!" << endl;
        setConsoleColor(wOrigin);
        m_lpLog->TRACE_FATAL("No DataBase connection!");
        return false;
    }
    if (!ReadReceFileSingle()) {
        flag = false;
    }
    if (flag) {
        for (int i = 0; i < m_lpCfg->getDirCount(false); i++) {
            UpdateDeleteFileMap(m_multimapDeleteReceFile[i], i, false);
        }
    }
    return flag;
}

bool CModel::ReadReceFileSingle() {
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
    struct _stat statBuf;
    time_t time = 0;

    if (_access(m_ReceFile[0].strFilePath.c_str(), 0) != 0) {
        return false;
    }
    // 确认INI文件已经写完，可以读取了
    int counter = 0;
    while (counter < 5) {
        if (_stat(m_ReceFile[0].strFilePath.c_str(), &statBuf) == 0) {
            if (time == statBuf.st_mtime) {
                break;
            } else {
                time = statBuf.st_mtime;
            }
        } else {
            return false;
        }
        Sleep(1000);
        ++counter;
    }
    strTableName = m_ReceFile[0].strName + "Result";
    // 从m_mapDBTable中获取字段信息vector
    vFields = m_mapDBTable.at(strTableName);
    strSQL = "insert " + strTableName + " values (";

    length = m_ReceFile[0].section_num;
    for (int i = 0; i < length; i++) {
        strSection = m_ReceFile[0].vSection[i].strName;
        // Result表，有ID有VIN
        // 故需要在得到的位置上加1
        iStart = m_ReceFile[0].vSection[i].start + 1;
        iEnd = m_ReceFile[0].vSection[i].end + 1;
        if (iEnd == 0) {
            iEnd = vFields.size() - 1;
        }
        for (int j = iStart; j <= iEnd; j++) {
            strKey = vFields[j].name;
            // 因FORUI的冈峦程序员生成的INI文件value有可能为空故使用"^"表示读取失败
            GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T("^"), buf, BUFSIZ, m_ReceFile[0].strFilePath.c_str());
            if (!strcmp(buf, "^")) {
                // 因FORUI的冈峦程序员生成的INI文件key命名规则极不规范，故需要做特殊处理
                int pos = strKey.find("Inten");
                if (pos > -1) {
                    // 将"Inten"替换成"Iten"
                    strKey.replace(strKey.begin() + pos, strKey.begin() + pos + 5, "Iten");
                }
                pos = strKey.find("_");
                if (pos > -1) {
                    // 将"_"替换成"-"
                    strKey.replace(strKey.begin() + pos, strKey.begin() + pos + 1, "-");
                }
                GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T("^"), buf, BUFSIZ, m_ReceFile[0].strFilePath.c_str());
                if (!strcmp(buf, "^")) {
                    pos = strKey.find("-");
                    if (pos > -1) {
                        // 将已经替换成"-"的key名再替换成空格
                        strKey.replace(strKey.begin() + pos, strKey.begin() + pos + 1, " ");
                    }
                    GetPrivateProfileString(strSection.c_str(), strKey.c_str(), _T("^"), buf, BUFSIZ, m_ReceFile[0].strFilePath.c_str());
                    if (!strcmp(buf, "^")) {
                        WORD wOrigin = setConsoleColor(12, 14);
                        cout << "Read key \"" << strKey << "\" under section \"" << strSection << "\" in file \"" << m_ReceFile[0].strFilePath << "\" failed" << endl;
                        setConsoleColor(wOrigin);
                        m_lpLog->TRACE_ERR("Read key \"%s\" under section \"%s\" in file \"%s\" failed", strKey.c_str(), strSection.c_str(), m_ReceFile[0].strFilePath.c_str());
                        m_lpLog->TRACE_ERR("GetLastError: %d", GetLastError());
                    }
                }
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

    // 把结果INI文件拷贝到备份目录内
    for (int i = 1; i < m_lpCfg->getDirCount(false); i++) {
        if (!CopyFile(m_ReceFile[0].strFilePath.c_str(), m_ReceFile[i].strFilePath.c_str(), false)) {
            WORD wOrigin = setConsoleColor(12, 14);
            cout << "CopyFile() Failed! From \"" << m_ReceFile[0].strFilePath << "\" to \"" << m_ReceFile[i].strFilePath << "\"" << endl;
            setConsoleColor(wOrigin);
            m_lpLog->TRACE_ERR("CopyFile() Failed! From \"%s\" to \"%s\"", m_ReceFile[0].strFilePath.c_str(), m_ReceFile[i].strFilePath.c_str());
        }
    }
    return true;
}

map<string, vector<FIELD>> CModel::GetMapDBTable() {
    return m_mapDBTable;
}

void CModel::InitDeleteFileMap(multimap<time_t, string> &deleteFile, int index, bool bSend) {
    long handle;
    struct _finddata_t fileInfo;

    string strDir = m_lpCfg->getDirInfo(bSend, index).strDirPath + "/*";
    handle = _findfirst(strDir.c_str(), &fileInfo);
    if (handle != -1) {
        do {
            // 去除文件夹
            if (!(fileInfo.attrib & _A_SUBDIR)) {
                deleteFile.insert(pair<time_t, string>(fileInfo.time_write, m_lpCfg->getDirInfo(bSend, index).strDirPath + "/" + fileInfo.name));
            }
        } while (!_findnext(handle, &fileInfo));
        _findclose(handle);

#ifdef _DEBUG
        multimap<time_t, string>::iterator iter;
        multimap<time_t, string>::iterator end = deleteFile.end();
        for (iter = deleteFile.begin(); iter != end; ++iter) {
            cout << iter->first << " - " << iter->second << endl;
        }
        cout << "--------------------------------------" << endl;
#endif // _DEBUG

    } else {
        char err[BUFSIZ];
        _strerror_s(err, nullptr);
        WORD wOrigin = setConsoleColor(12, 14);
        cout << "_findfirst " << m_lpCfg->getDirInfo(bSend, index).strDirPath << " error: " << err << endl;
        setConsoleColor(wOrigin);
    }
}

void CModel::InitDeleteFileMap() {
    for (int i = 0; i < m_lpCfg->getDirCount(true); i++) {
        InitDeleteFileMap(m_multimapDeleteSendFile[i], i, true);
    }
    for (int i = 0; i < m_lpCfg->getDirCount(false); i++) {
        InitDeleteFileMap(m_multimapDeleteReceFile[i], i, false);
    }
}

void CModel::UpdateDeleteFileMap(multimap<time_t, string> &deleteFile, int index, bool bSend) {
    struct _stat buf;
    int result = 0;
    char err[BUFSIZ];

    if ((m_lpCfg->getDirInfo(bSend, index)).iMaxFileNum > 0) {
        if (bSend) {
            result = _stat(m_SendFile[index].strFilePath.c_str(), &buf);
            if (result == 0) {
                string value = m_SendFile[index].strFilePath;
                auto find_item = find_if(deleteFile.begin(), deleteFile.end(),
                    [value](const map<time_t, string>::value_type item) { return item.second == value; }
                );
                if (find_item == deleteFile.end()) {
                    deleteFile.insert(pair<time_t, string>(buf.st_mtime, m_SendFile[index].strFilePath));
                }
            } else {
                _strerror_s(err, nullptr);
                WORD wOrigin = setConsoleColor(12, 14);
                cout << "_stat() \"" << m_SendFile[index].strFilePath << "\" error: " << err << endl;
                setConsoleColor(wOrigin);
                m_lpLog->TRACE_ERR("_stat() \"%s\" error: %s", m_SendFile[index].strFilePath.c_str(), err);
            }
        } else {
            result = _stat(m_ReceFile[index].strFilePath.c_str(), &buf);
            if (result == 0) {
                string value = m_ReceFile[index].strFilePath;
                auto find_item = find_if(deleteFile.begin(), deleteFile.end(),
                    [value](const map<time_t, string>::value_type item) { return item.second == value; }
                );
                if (find_item == deleteFile.end()) {
                    deleteFile.insert(pair<time_t, string>(buf.st_mtime, m_ReceFile[index].strFilePath));
                }
            } else {
                _strerror_s(err, nullptr);
                WORD wOrigin = setConsoleColor(12, 14);
                cout << "_stat() \"" << m_ReceFile[index].strFilePath << "\" error: " << err << endl;
                setConsoleColor(wOrigin);
                m_lpLog->TRACE_ERR("_stat() \"%s\" error: %s", m_ReceFile[index].strFilePath.c_str(), err);
            }
        }
        int count = deleteFile.size() - (m_lpCfg->getDirInfo(bSend, index)).iMaxFileNum;
        if (count > 0) {
            for (int j = 0; j < count; j++) {
                if (remove(deleteFile.begin()->second.c_str()) == 0) {
                    deleteFile.erase(deleteFile.begin());
                } else {
                    WORD wOrigin = setConsoleColor(12, 14);
                    cout << "Can't delete file: \"" << deleteFile.begin()->second << "\"" << endl;
                    setConsoleColor(wOrigin);
                    m_lpLog->TRACE_ERR("Can't delete file: \"%s\"", deleteFile.begin()->second.c_str());
                }
            }
        }
    }
}

bool CModel::GetCaliSignal() {
    if (_access(m_lpCfg->getNCAStateFile().c_str(), 0) != 0) {
        return false;
    }
    // 一旦有了StateFile文件，就可以开始标定了
    string strSQL = "insert CaliProcStatus values ('" + m_lpCfg->getVIN() + "', '2')";
    if (!m_lpADO->ExecuteSQL(strSQL.c_str())) {
        m_lpLog->TRACE_ERR("Error SQL: %s", strSQL.c_str());
    }
    return true;
}

bool CModel::CheckCaliDone() {
    string strSQL = "select Status from CaliProcStatus where VIN = '" + m_lpCfg->getVIN() + "'";
    m_lpADO->GetRecordSet(strSQL.c_str());
    if (m_lpADO->GetRecord("Status", 0) == "") {
        remove(m_lpCfg->getNCAStateFile().c_str());
        m_lpADO->RecordSetClose();
        return true;
    }
    m_lpADO->RecordSetClose();
    return false;
}
