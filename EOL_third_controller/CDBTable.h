#pragma once
#include <string>
#include <vector>
using namespace std;

class CDBTable
{
	string m_strName;
	vector<string> m_vColumns;

public:
	CDBTable();
	~CDBTable();
};

