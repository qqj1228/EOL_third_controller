#pragma once
#include "CConfig.h"
#include "CADOConn.h"
#include <map>

// �ֶ���Ϣ
struct FIELD {
    string name; // �ֶ���
    long length; // �ֶγ���
};

class CModel {
    bool m_bDBOK;
    CConfig *m_lpCfg;
    CADOConn *m_lpADO;
    Logger *m_lpLog;

    // map<������vector<�ֶ���Ϣ>>
    map<string, vector<FIELD>> m_mapDBTable;

    // multimap<�޸�ʱ�䣬�ļ�ȫ·��>
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
    // ������ReceFile�ļ�ʱ����false, ���򷵻�true
    bool ReadReceFile();
    // ������ReceFile�ļ�ʱ����false, ���򷵻�true
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

