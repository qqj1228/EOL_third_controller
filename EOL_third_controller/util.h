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

static int GetOSVer()
{
	OSVERSIONINFO   osver;
	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osver);
	if (osver.dwPlatformId == 2)
	{
		if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
		{
			//cout << "OS Version: XP" << endl;
			return(2);
		}
		if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
		{
			//cout << "OS Version: windows 2003" << endl;
			return(3);
		}
		if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
		{
			//cout << "OS Version: vista or 2008" << endl;
			return(4);
		}
		if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
		{
			//cout << "OS Version: 2008 R2 or Windows 7" << endl;
			return(5);
		}
	}
	return 0;
}

static string Normalize(string strSouce, size_t iMaxlen)
{
	string strResult;
	// 去除首尾空格
	strSouce.erase(0, strSouce.find_first_not_of(" "));
	strSouce.erase(strSouce.find_last_not_of(" ") + 1);
	// 将非法字符替换为_
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
	// 截短到指定长度
	if (strResult.size() > iMaxlen)
	{
		strResult.resize(iMaxlen);
	}
	return strResult;
}

// 从左到右依次判断文件夹是否存在, 不存在就创建, 只适用于Windows平台
// example: D:/mkdir/1/2/3/4/
// 注意:最后一个如果是文件夹的话,需要加上 '\\' 或者 '/'
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