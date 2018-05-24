#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <regex>
#include <io.h>
#include <direct.h> 

using namespace std;

static string IntToString(int n)
{
	ostringstream stream;
	stream << n;
	return stream.str();
}

static string Normalize(string strSouce, size_t iMaxlen)
{
	string strResult;
	// ȥ����β�ո�
	strSouce.erase(0, strSouce.find_first_not_of(" "));
	strSouce.erase(strSouce.find_last_not_of(" ") + 1);
	// ���Ƿ��ַ��滻Ϊ_
	try
	{
		regex rgx("[/\\ _]+");
		string strFmt("_");
		strResult = regex_replace(strSouce, rgx, strFmt);
	}
	catch (regex_error &e)
	{
		cout << "regex error code: " << e.code() << endl;
	}
	// �ض̵�ָ������
	if (strResult.size() > iMaxlen)
	{
		strResult.resize(iMaxlen);
	}
	return strResult;
}

// �����������ж��ļ����Ƿ����, �����ھʹ���, ֻ������Windowsƽ̨
// example: D:/mkdir/1/2/3/4/
// ע��:���һ��������ļ��еĻ�,��Ҫ���� '\\' ���� '/'
static int32_t mkMultiDir(const std::string &directoryPath)
{
	uint32_t dirPathLen = directoryPath.length();
	if (dirPathLen > MAX_PATH)
	{
		return -1;
	}
	char tmpDirPath[MAX_PATH] = { 0 };
	for (uint32_t i = 0; i < dirPathLen; ++i)
	{
		tmpDirPath[i] = directoryPath[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (_access(tmpDirPath, 0) != 0)
			{
				int32_t ret = _mkdir(tmpDirPath);
				if (ret != 0)
				{
					return ret;
				}
			}
		}
	}
	return 0;
}