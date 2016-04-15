#include "dealMainServiceThread.h"

DealMainServiceThread::DealMainServiceThread()
{
	m_bPause = false;
	m_iCommitedLine = 0 ;
	m_iCommitedSize = 0 ; 
}

DealMainServiceThread::~DealMainServiceThread()
{

}

void DealMainServiceThread::stop()
{

}

void DealMainServiceThread::run()
{ 	
 
}

void DealMainServiceThread::mySQLSetStmtAttr(SQLHSTMT StatementHandle, SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength)
{
	SQLRETURN rc = SQLSetStmtAttr(StatementHandle, Attribute, ValuePtr, StringLength);
	if (!SQL_SUCCEEDED(rc))
	{
		SQLWCHAR * sErrorMsg = diagnostic(SQL_HANDLE_STMT, StatementHandle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ����������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));;
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLAllocHandle(SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE * OutputHandlePtr)
{
	SQLRETURN rc = SQLAllocHandle(HandleType, InputHandle, OutputHandlePtr);
	if (!SQL_SUCCEEDED(rc))
	{
		SQLWCHAR * sErrorMsg = diagnostic(HandleType, InputHandle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLAllocHandle����������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));;
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLSetConnectAttr(SQLHDBC ConnectionHandle, SQLINTEGER Attribute,  SQLPOINTER ValuePtr, SQLINTEGER StringLength)
{
	SQLRETURN rc = SQLSetConnectAttr(ConnectionHandle, Attribute, ValuePtr, StringLength);
	if (!SQL_SUCCEEDED(rc))
	{
		SQLWCHAR * sErrorMsg = diagnostic(SQL_HANDLE_DBC, ConnectionHandle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetConnectAttr����������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc).arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));;
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLConnect(SQLHDBC ConnectionHandle,
																	  SQLWCHAR * ServerName,
																	  SQLSMALLINT NameLength1,
																	  SQLWCHAR * UserName,
																	  SQLSMALLINT NameLength2,
																	  SQLWCHAR * Authentication,
																	  SQLSMALLINT NameLength3)
{
	SQLRETURN rc = SQLConnect(ConnectionHandle, ServerName, NameLength1,
		                                                                           UserName, NameLength2,
															                       Authentication, NameLength3);
	if (!SQL_SUCCEEDED(rc))
	{
		SQLWCHAR * sErrorMsg = diagnostic(SQL_HANDLE_DBC, ConnectionHandle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���̽������ݿ����ӳ���������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLPrepare(SQLHSTMT StatementHandle,	SQLWCHAR * StatementText, SQLINTEGER TextLength)
{
	SQLRETURN rc = SQLPrepare(StatementHandle, (SQLWCHAR*)StatementText, TextLength);
	if (!SQL_SUCCEEDED(rc))
	{
		SQLWCHAR * sErrorMsg = diagnostic(SQL_HANDLE_STMT, StatementHandle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLPrepare ����������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLExecute(SQLHSTMT StatementHandle)
{
	SQLRETURN rc = SQLExecute(StatementHandle);
	if (rc != SQL_SUCCESS)
	{
		SQLWCHAR * sErrorMsg = diagnostic(SQL_HANDLE_STMT, StatementHandle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLExecute�쳣�˳����Ѿ�д��[%2]�����ݣ�ʣ��[%3]��д��[%4]")
			.arg(m_iProcessID)
			.arg(m_iCurrlLine)
			.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLEndTran(SQLSMALLINT HandleType, SQLHANDLE Handle, SQLSMALLINT CompletionType)
{
	SQLRETURN rc = SQLEndTran(HandleType, Handle, CompletionType);
	if (!SQL_SUCCEEDED(rc))
	{
		SQLWCHAR * sErrorMsg = diagnostic(SQL_HANDLE_DBC, Handle);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLEndTran�쳣�˳����Ѿ�д��[%2]�����ݣ�ʣ��[%3]��д��[%4]")
			.arg(m_iProcessID)
			.arg(m_iCurrlLine)
			.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLSetEnvAttr(SQLHENV EnvironmentHandle,SQLINTEGER Attribute,SQLPOINTER ValuePtr,SQLINTEGER StringLength)
{
	SQLRETURN rc = SQLSetEnvAttr(EnvironmentHandle, Attribute, ValuePtr, StringLength);
	if (!SQL_SUCCEEDED(rc))
	{
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetEnvAttr����������[%2]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc);
		throw m_sMsg;
	}
}

void DealMainServiceThread::mySQLBindParameter(	SQLHSTMT StatementHandle, SQLUSMALLINT ParameterNumber,
                                                                                SQLSMALLINT InputOutputType, SQLSMALLINT ValueType,
                                                                                SQLSMALLINT ParameterType, SQLULEN ColumnSize,
                                                                                SQLSMALLINT DecimalDigits, SQLPOINTER ParameterValuePtr,
                                                                                SQLLEN BufferLength, SQLLEN * StrLen_or_IndPtr)
{
	SQLRETURN rc = SQLBindParameter(StatementHandle, ParameterNumber, 
		                                                      InputOutputType, ValueType,
		                                                      ParameterType, ColumnSize, 
															  DecimalDigits, ParameterValuePtr,
															  BufferLength, StrLen_or_IndPtr);
}