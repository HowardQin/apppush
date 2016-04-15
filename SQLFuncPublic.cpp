#include "SQLFuncPublic.h"

static SQLWCHAR message[SQL_MAX_MESSAGE_LENGTH];

SQLWCHAR *diagnostic(short type,  SQLHANDLE handle) 
{
	SQLWCHAR state[8];
	SQLINTEGER error;
	SQLSMALLINT TextLength;
	SQLRETURN rc;
	rc = SQLGetDiagRec(type, handle, 1, state, &error, message, SQL_MAX_MESSAGE_LENGTH, &TextLength);
	if (SQL_SUCCEEDED(rc)) {
		return message;
	} else {
		return (SQLWCHAR *)"SQLGetDiagRec fail !!!";
	}
}


void CleanDBConnect(SQLHSTMT & hstmt_dre,SQLHDBC & hdbc_dre,SQLHENV & henv)
{
	if (hstmt_dre)
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt_dre);
	if (hdbc_dre != SQL_NULL_HDBC)
	{
		SQLDisconnect(hdbc_dre);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc_dre);
	}
	if (henv != SQL_NULL_HENV)
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
}
