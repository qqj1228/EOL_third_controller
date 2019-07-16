#pragma once
#include "CConfig.h"
#include "CADOConn.h"
#include <map>

// 字段信息
struct FIELD {
    string name; // 字段名
    long length; // 字段长度
};

class CModel {
    bool m_bDBOK;
    CConfig *m_lpCfg;
    CADOConn *m_lpADO;
    Logger *m_lpLog;

    // map<表名，vector<字段信息>>
    map<string, vector<FIELD>> m_mapDBTable;

    // multimap<修改时间，文件全路径>
    multimap<time_t, string> m_multimapDeleteSendFile[DIR_NUM];
    multimap<time_t, string> m_multimapDeleteReceFile[DIR_NUM];

    INIFILE m_SendFile[DIR_NUM];
    INIFILE m_ReceFile[DIR_NUM];

public:
    CModel(CConfig *lpCfg, Logger *lpLog);
    CModel(CConfig *lpCfg, map<string, vector<FIELD>> &mapDBTable, Logger *lpLog);
    ~CModel();
    map<string, vector<FIELD>> GetMapDBTable();
    bool WriteSendFile();
    // 不存在ReceFile文件时返回false, 否则返回true
    bool ReadReceFile();
    // 不存在ReceFile文件时返回false, 否则返回true
    bool ReadReceFileSingle();
    void GetTableName(vector<string> *lpvTableName);
    void GetColumns(string strTableName, vector<FIELD> *lpvColumns);
    void InitMapDBTable();
    void InitINIFile();
    void InitDeleteFileMap(multimap<time_t, string> &deleteFile, int index, bool bSend);
    void InitDeleteFileMap();
    void UpdateDeleteFileMap(multimap<time_t, string> &deleteFile, int index, bool bSend);
    bool GetCaliSignal();
    bool CheckCaliDone();
};

