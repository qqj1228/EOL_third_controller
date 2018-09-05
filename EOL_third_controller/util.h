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

// ���ÿ���̨����ǰ���ͱ���ɫ, ����ԭ������ɫ����
// 0-��		1-��		2-��		3-ǳ��		4-��		5-��		6-��		7-��
// 8-��		9-����	10-����	11-��ǳ��	12-����	13-����	14-����	15-����
static WORD setConsoleColor(int iForeColor, int iBackColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) {
		return 0;
	}
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	WORD wAttributes = info.wAttributes;
	bool bResult = SetConsoleTextAttribute(hConsole, iForeColor + iBackColor * 0x10);
	if (!bResult) {
		return 0;
	}
	return wAttributes;
}

// ���ÿ���̨��ɫ����, ����ԭ������ɫ����
// ǰ��ɫ��ϣ�
// FOREGROUND_BLUE-0x0001	FOREGROUND_GREEN-0x0002		FOREGROUND_RED-0x0004	FOREGROUND_INTENSITY-0x0008
// ����ɫ��ϣ���ʵ����ǰ��ɫ*0x10����
// BACKGROUND_BLUE-0x0010	BACKGROUND_GREEN-0x0020		BACKGROUND_RED-0x0040	BACKGROUND_INTENSITY-0x0080
static WORD setConsoleColor(WORD wAttributes) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) {
		return 0;
	}
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	WORD wOrigin = info.wAttributes;
	bool bResult = SetConsoleTextAttribute(hConsole, wAttributes);
	if (!bResult) {
		return 0;
	}
	return wOrigin;
}