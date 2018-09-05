#pragma once
#include "CConfig.h"
#include "CADOConn.h"
#include <map>

// �ֶ���Ϣ
struct FIELD
{
	string name; // �ֶ���
	long length; // �ֶγ���
};

class CModel
{
	bool m_bDBOK;
	CConfig *m_lpCfg;
	CADOConn *m_lpADO;
	Logger *m_lpLog;

	// map<������vector<�ֶ���Ϣ>>
	map<string, vector<FIELD>> m_mapDBTable;

	// multimap<�޸�ʱ�䣬�ļ�ȫ·��>
	multimap<time_t, string> m_multimapDeleteSendFile;
	multimap<time_t, string> m_multimapDeleteReceFile;

	INIFILE m_SendFile;
	// ��m_ReceFile�����е�3��Ԫ�ض�һ�������ʾֻ��һ��Ԫ��
	INIFILE m_ReceFile[3];

public:
	CModel(CConfig *lpCfg, Logger *lpLog);
	CModel(CConfig *lpCfg, map<string, vector<FIELD>> &mapDBTable, Logger *lpLog);
	~CModel();
	map<string, vector<FIELD>> GetMapDBTable();
	bool WriteSendFile();
	// ������ReceFile�ļ�ʱ����false, ���򷵻�true
	bool ReadReceFile();
	// ������ReceFile�ļ�ʱ����false, ���򷵻�true
	bool ReadReceFileSingle(int iIndex);
	void GetTableName(vector<string> *lpvTableName);
	void GetColumns(string strTableName, vector<FIELD> *lpvColumns);
	void InitMapDBTable();
	void InitINIFile();
	void InitDeleteFileMap(multimap<time_t, string> &deleteFile, bool bSend);
	void InitDeleteFileMap();
	void UpdateDeleteFileMap(multimap<time_t, string> &deleteFile, bool bSend);
};

