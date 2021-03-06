// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: 在此处引用程序需要的其他头文件
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "Logger.h"
using namespace std;

#define LOG_DIR _T(".\\log")
#define LOG_FILE_QTY 100
#define CONFIG_FILE _T("config.ini")
#define CONFIG_PATH _T(".\\config")
#define CALIPROC_PATH _T("\\CaliProc\\")
#define CALIPROC_FILE _T("EPSCaliProc.exe")
#define NORMAL_RET "O"
#define ERROR_RET "X"
