#pragma once
#include "CConfig.h"
#include "CADOConn.h"
#include <map>

// 字段信息
struct FIELD
{
	string name; // 字段名
	long length; // 字段长度
};

class CModel
{
	bool m_bDBOK;
	CConfig *m_lpCfg;
	CADOConn *m_lpADO;
	Logger *m_lpLog;

	// map<表名，vector<字段信息>
	map<string, vector<FIELD>> m_mapDBTable;

	INIFILE m_SendFile;
	// 若m_ReceFile数组中的3个元素都一样，则表示只有一个元素
	INIFILE m_ReceFile[3];

public:
	CModel(CConfig *lpCfg, Logger *lpLog);
	CModel(CConfig *lpCfg, map<string, vector<FIELD>> &mapDBTable, Logger *lpLog);
	~CModel();
	map<string, vector<FIELD>> GetMapDBTable();
	bool WriteSendFile();
	// 不存在ReceFile文件时返回false, 否则返回true
	bool ReadReceFile();
	// 不存在ReceFile文件时返回false, 否则返回true
	bool ReadReceFileSingle(int iIndex);
	void GetTableName(vector<string> *lpvTableName);
	void GetColumns(string strTableName, vector<FIELD> *lpvColumns);
	void InitMapDBTable();
	void InitINIFile();
};

