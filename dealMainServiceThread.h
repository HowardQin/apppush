#if !defined(DealMainServiceThread_H_ZZG)
#define DealMainServiceThread_H_ZZG

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "globalobject.h"
#include "SQLFuncPublic.h"
#include <qthread.h>
#include <qlabel.h>
#include <qstringlist.h>

#define  TIME_OF_3_SLEEP 5000
#define  DEF_COMMIT_LINE_Print 100000

class DealMainServiceThread : public QThread  
{
public:
	DealMainServiceThread();
	virtual ~DealMainServiceThread();
	void stop();
	//封装ODBC API，增加错误处理，出错时生成信息并抛出异常
	void mySQLSetEnvAttr(SQLHENV EnvironmentHandle, SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength);
	void mySQLSetStmtAttr(SQLHSTMT StatementHandle, SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength);
	void mySQLSetConnectAttr(SQLHDBC ConnectionHandle, SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength);
	void mySQLAllocHandle(SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE * OutputHandlePtr);
	void mySQLConnect(SQLHDBC ConnectionHandle,
		                             SQLWCHAR * ServerName,
		                             SQLSMALLINT NameLength1,
		                             SQLWCHAR * UserName,
		                             SQLSMALLINT NameLength2,
		                             SQLWCHAR * Authentication,
		                             SQLSMALLINT NameLength3);
	void mySQLPrepare(SQLHSTMT StatementHandle, SQLWCHAR * StatementText, SQLINTEGER TextLength);
	void mySQLExecDirect(SQLHSTMT StatementHandle, SQLWCHAR * StatementText, SQLINTEGER TextLength);
	void mySQLExecute(SQLHSTMT StatementHandle);
	void mySQLEndTran( SQLSMALLINT HandleType, SQLHANDLE Handle, SQLSMALLINT CompletionType);
	void mySQLBindParameter(SQLHSTMT StatementHandle, SQLUSMALLINT ParameterNumber,
                                                                                    SQLSMALLINT InputOutputType, SQLSMALLINT ValueType,
                                                                                    SQLSMALLINT ParameterType, SQLULEN ColumnSize,
                                                                                    SQLSMALLINT DecimalDigits, SQLPOINTER ParameterValuePtr,
                                                                                    SQLLEN BufferLength, SQLLEN * StrLen_or_IndPtr);

public:
	virtual void run();
	bool m_bPause ;  /* 标志位，控制循环是否继续进行 2011/07/19 by zzg */
	int    m_iProcessID ;
	LONG64 m_iIDStart ;
	LONG64 m_iIDEnd;
	LONG64 m_iIDCurrent;
	LONG64 m_iTotalLine;
	LONG64 m_iCurrlLine;
	LONG64 m_iCommitedLine;
	LONG64 m_iCommitedSize;
	LONG64 m_iMeterIDStart ;
	LONG64 m_iMeterIDEnd;
	QDateTime m_dtStartJob ;
	RunState	m_iJobflag = except;
	int m_iTickCount;
	int reTryCount = 0;
	QString m_sMsg;
	QDateTime m_dtPick;
	static QMutex m_mutex;
};

#endif // DealMainServiceThread_H_ZZG
