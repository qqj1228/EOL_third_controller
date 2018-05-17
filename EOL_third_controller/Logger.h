#pragma once
#include <Windows.h>
#include <stdio.h>

/**
 * ������Logger
 * ���ã��ṩд��־���ܣ�֧�ֶ��̣߳�֧�ֿɱ��β���������֧��д��־���������
 * �ӿڣ�SetLogLevel��  ����д��־����
 *       TraceKeyInfo�� ������־����д�ؼ���Ϣ
 *       TraceError��   д������Ϣ
 *       TraceWarning�� д������Ϣ
 *       TraceInfo��    дһ����Ϣ
 *
 * ʹ�ã�
 * #include "Logger.h"
 * Logger log;
 * log.SetLogLevel(LogLevelAll);
 * log.TraceInfo("Ready Go");
 * log.TraceKeyInfo("KeyInfo");
 * log.TraceWarning("Warning");
 * log.TraceError("Error");
**/

//��־�������ʾ��Ϣ
static const char * FATALPREFIX = " [Fatal]: ";
static const char * ERRORPREFIX = " [Error]: ";
static const char * WARNINGPREFIX = " [Warning]: ";
static const char * INFOPREFIX = " [Info]: ";

static const int MAX_STR_LEN = 1024;
//��־����ö��
enum EnumLogLevel
{
	LogLevelAll = 0,    //������Ϣ��д��־
	LogLevelMid,        //д���󡢾�����Ϣ
	LogLevelNormal,     //ֻд������Ϣ
	LogLevelStop        //��д��־
};

class Logger
{
public:
	//Ĭ�Ϲ��캯��
	Logger();
	//���캯��
	Logger(const char * strLogPath, EnumLogLevel nLogLevel = EnumLogLevel::LogLevelNormal);
	//��������
	virtual ~Logger();
public:
	//д�ؼ���Ϣ
	void TraceFatal(const char * strInfo, ...);
	//д������Ϣ
	void TraceError(const char* strInfo, ...);
	//д������Ϣ
	void TraceWarning(const char * strInfo, ...);
	//дһ����Ϣ
	void TraceInfo(const char * strInfo, ...);
	//����д��־����
	void SetLogLevel(EnumLogLevel nLevel);
private:
	//д�ļ�����
	void Trace(const char * strInfo);
	//��ȡ��ǰϵͳʱ��
	void GetDateTime(char *pTemp, int length);
	//������־�ļ�����
	void GenerateLogName();
	//������־·��
	void CreateLogPath();
	// �ر��ļ���
	void CloseFile();
private:
	//д��־�ļ���
	FILE * m_pFileStream;
	//д��־����
	EnumLogLevel m_nLogLevel;
	//��־��·��
	char m_strLogPath[MAX_STR_LEN];
	//��־������
	char m_strCurLogName[MAX_STR_LEN];
	//�߳�ͬ�����ٽ�������
	CRITICAL_SECTION m_cs;
};