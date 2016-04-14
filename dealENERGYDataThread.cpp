#include "dealENERGYDataThread.h"
#include <qdatetime.h>

#include "SQLFuncPublic.h"


DealENERGYDataThread::DealENERGYDataThread()
{
	m_bPause = false;
	m_iCommitedLine = 0 ;
	m_iCommitedSize = 0 ; 
}

DealENERGYDataThread::~DealENERGYDataThread()
{

}

void DealENERGYDataThread::stop()
{

}

void DealENERGYDataThread::run()
{ 
	SQLWCHAR * sErrorMsg = NULL; 
	//����ʼ
	m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]������������׼���������ݿ�[%2]")
		.arg(m_iProcessID)
		.arg(CGlobalDataSaver::GetInstance()->m_sDbService);
	CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);

	SQLHENV henv;
	SQLHDBC hdbc_dre;
	SQLHSTMT hstmt_dre;
	SQLRETURN rc;
	//����ODBC���������Ӽ�SQL���������
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if (!SQL_SUCCEEDED(rc)) 
	{
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]��������ODBC���������Ӽ�SQL���������������[%2]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		return ;
	}

	rc = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) (SQL_OV_ODBC3), SQL_IS_UINTEGER);
	if (!SQL_SUCCEEDED(rc)) 
	{
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetEnvAttr������������[%2]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return ;
	}

	rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc_dre); 
	if (!SQL_SUCCEEDED(rc))  
	{
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc_dre)������������[%2]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return ;
	}

 	rc = SQLConnect(hdbc_dre, (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbService.unicode(), SQL_NTS, 
		                                        (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbUserName.unicode(), SQL_NTS,
		                                        (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbUserPass.unicode(), SQL_NTS);
	if (!SQL_SUCCEEDED(rc)) 
	{
		sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���̽������ݿ����ӳ�����������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char * )sErrorMsg));
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc_dre);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return ;
	}

	rc = SQLSetConnectAttr(hdbc_dre, SQL_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0 );
	if (!SQL_SUCCEEDED(rc)) 
	{
		sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetConnectAttr������������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc).arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char * )sErrorMsg));;
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		SQLDisconnect(hdbc_dre);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc_dre);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return ;
	}

	rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc_dre, &hstmt_dre); 
	if (!SQL_SUCCEEDED(rc)) 
	{
		sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLAllocHandle������������[%2][%3]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc)
			.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char * )sErrorMsg));;
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		SQLDisconnect(hdbc_dre);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc_dre);
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return ;
	}

	m_dtPick = QDateTime::currentDateTime();
	m_dtStartJob = m_dtPick;
	QString statement;
	if (RunState::insert == m_iJobflag )
	{
		statement = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode(
			"%1 INTO E_MP_ENERGY_CURVE_P (ene_cur_id, meter_id, data_date, metering_time,"
			"E96, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16, E17, E18, E19, E20, E21,"
			"E22, E23, E24, E25, E26, E27, E28, E29, E30, E31, E32, E33, E34, E35, E36, E37, E38, E39, E40, "
			"E41, E42, E43, E44, E45, E46, E47, E48, E49, E50, E51, E52, E53, E54, E55, E56, E57, E58, E59, "
			"E60, E61, E62, E63, E64, E65, E66, E67, E68, E69, E70, E71, E72, E73, E74, E75, E76, E77, E78, "
			"E79, E80, E81, E82, E83, E84, E85, E86, E87, E88, E89, E90, E91, E92, E93, E94, E95) VALUES "
			"(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
			.arg(CGlobalDataSaver::GetInstance()->GetInsertString());
		crm_mnp_npdb_energy *po = (crm_mnp_npdb_energy *)malloc(CGlobalDataSaver::GetInstance()->m_iDCSL * sizeof(crm_mnp_npdb_energy));
		SQLUSMALLINT *param_status = (SQLUSMALLINT *)malloc(CGlobalDataSaver::GetInstance()->m_iDCSL * sizeof(SQLUSMALLINT));
		SQLINTEGER params_processed = 0;

		rc = SQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER) sizeof(crm_mnp_npdb_energy), 0);
		if (!SQL_SUCCEEDED(rc))
		{
			sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ������������[%2][%3]�����̽��˳�")
				.arg(m_iProcessID)
				.arg(rc)
				.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));;
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}
		rc = SQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)CGlobalDataSaver::GetInstance()->m_iDCSL, 0);
		if (!SQL_SUCCEEDED(rc))
		{
			sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);

			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ������������[%2][%3]�����̽��˳�")
				.arg(m_iProcessID)
				.arg(rc)
				.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));;
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}
		rc = SQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_STATUS_PTR, param_status, 0);
		if (!SQL_SUCCEEDED(rc))
		{
			sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ������������[%2][%3]�����̽��˳�")
				.arg(m_iProcessID)
				.arg(rc)
				.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}
		rc = SQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMS_PROCESSED_PTR, &params_processed, 0);
		if (!SQL_SUCCEEDED(rc))
		{
			sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);

			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ������������[%2][%3]�����̽��˳�")
				.arg(m_iProcessID)
				.arg(rc)
				.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}

		rc = SQLBindParameter(hstmt_dre, 1, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_vol_cur_id, 0, &po[0].vol_cur_id, sizeof(po[0].vol_cur_id), &po[0].len_vol_cur_id);
		rc = SQLBindParameter(hstmt_dre, 2, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_meter_id, 0, &po[0].meter_id, sizeof(po[0].meter_id), &po[0].len_meter_id);
		rc = SQLBindParameter(hstmt_dre, 3, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TIMESTAMP, po[0].len_data_date, 0, &po[0].data_date, sizeof(po[0].data_date), &po[0].len_data_date);
		rc = SQLBindParameter(hstmt_dre, 4, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TIMESTAMP, po[0].len_metering_time, 0, &po[0].metering_time, sizeof(po[0].metering_time), &po[0].len_metering_time);
		rc = SQLBindParameter(hstmt_dre, 5, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V96, 0, &po[0].V96, sizeof(po[0].V96), &po[0].len_V96);
		rc = SQLBindParameter(hstmt_dre, 6, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V1, 0, &po[0].V1, sizeof(po[0].V1), &po[0].len_V1);
		rc = SQLBindParameter(hstmt_dre, 7, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V2, 0, &po[0].V2, sizeof(po[0].V2), &po[0].len_V2);
		rc = SQLBindParameter(hstmt_dre, 8, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V3, 0, &po[0].V3, sizeof(po[0].V3), &po[0].len_V3);
		rc = SQLBindParameter(hstmt_dre, 9, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V4, 0, &po[0].V4, sizeof(po[0].V4), &po[0].len_V4);
		rc = SQLBindParameter(hstmt_dre, 10, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V5, 0, &po[0].V5, sizeof(po[0].V5), &po[0].len_V5);
		rc = SQLBindParameter(hstmt_dre, 11, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V6, 0, &po[0].V6, sizeof(po[0].V6), &po[0].len_V6);
		rc = SQLBindParameter(hstmt_dre, 12, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V7, 0, &po[0].V7, sizeof(po[0].V7), &po[0].len_V7);
		rc = SQLBindParameter(hstmt_dre, 13, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V8, 0, &po[0].V8, sizeof(po[0].V8), &po[0].len_V8);
		rc = SQLBindParameter(hstmt_dre, 14, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V9, 0, &po[0].V9, sizeof(po[0].V9), &po[0].len_V9);
		rc = SQLBindParameter(hstmt_dre, 15, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V10, 0, &po[0].V10, sizeof(po[0].V10), &po[0].len_V10);
		rc = SQLBindParameter(hstmt_dre, 16, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V11, 0, &po[0].V11, sizeof(po[0].V11), &po[0].len_V11);
		rc = SQLBindParameter(hstmt_dre, 17, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V12, 0, &po[0].V12, sizeof(po[0].V12), &po[0].len_V12);
		rc = SQLBindParameter(hstmt_dre, 18, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V13, 0, &po[0].V13, sizeof(po[0].V13), &po[0].len_V13);
		rc = SQLBindParameter(hstmt_dre, 19, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V14, 0, &po[0].V14, sizeof(po[0].V14), &po[0].len_V14);
		rc = SQLBindParameter(hstmt_dre, 20, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V15, 0, &po[0].V15, sizeof(po[0].V15), &po[0].len_V15);
		rc = SQLBindParameter(hstmt_dre, 21, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V16, 0, &po[0].V16, sizeof(po[0].V16), &po[0].len_V16);
		rc = SQLBindParameter(hstmt_dre, 22, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V17, 0, &po[0].V17, sizeof(po[0].V17), &po[0].len_V17);
		rc = SQLBindParameter(hstmt_dre, 23, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V18, 0, &po[0].V18, sizeof(po[0].V18), &po[0].len_V18);
		rc = SQLBindParameter(hstmt_dre, 24, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V19, 0, &po[0].V19, sizeof(po[0].V19), &po[0].len_V19);
		rc = SQLBindParameter(hstmt_dre, 25, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V20, 0, &po[0].V20, sizeof(po[0].V20), &po[0].len_V20);
		rc = SQLBindParameter(hstmt_dre, 26, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V21, 0, &po[0].V21, sizeof(po[0].V21), &po[0].len_V21);
		rc = SQLBindParameter(hstmt_dre, 27, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V22, 0, &po[0].V22, sizeof(po[0].V22), &po[0].len_V22);
		rc = SQLBindParameter(hstmt_dre, 28, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V23, 0, &po[0].V23, sizeof(po[0].V23), &po[0].len_V23);
		rc = SQLBindParameter(hstmt_dre, 29, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V24, 0, &po[0].V24, sizeof(po[0].V24), &po[0].len_V24);
		rc = SQLBindParameter(hstmt_dre, 30, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V25, 0, &po[0].V25, sizeof(po[0].V25), &po[0].len_V25);
		rc = SQLBindParameter(hstmt_dre, 31, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V26, 0, &po[0].V26, sizeof(po[0].V26), &po[0].len_V26);
		rc = SQLBindParameter(hstmt_dre, 32, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V27, 0, &po[0].V27, sizeof(po[0].V27), &po[0].len_V27);
		rc = SQLBindParameter(hstmt_dre, 33, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V28, 0, &po[0].V28, sizeof(po[0].V28), &po[0].len_V28);
		rc = SQLBindParameter(hstmt_dre, 34, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V29, 0, &po[0].V29, sizeof(po[0].V29), &po[0].len_V29);
		rc = SQLBindParameter(hstmt_dre, 35, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V30, 0, &po[0].V30, sizeof(po[0].V30), &po[0].len_V30);
		rc = SQLBindParameter(hstmt_dre, 36, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V31, 0, &po[0].V31, sizeof(po[0].V31), &po[0].len_V31);
		rc = SQLBindParameter(hstmt_dre, 37, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V32, 0, &po[0].V32, sizeof(po[0].V32), &po[0].len_V32);
		rc = SQLBindParameter(hstmt_dre, 38, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V33, 0, &po[0].V33, sizeof(po[0].V33), &po[0].len_V33);
		rc = SQLBindParameter(hstmt_dre, 39, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V34, 0, &po[0].V34, sizeof(po[0].V34), &po[0].len_V34);
		rc = SQLBindParameter(hstmt_dre, 40, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V35, 0, &po[0].V35, sizeof(po[0].V35), &po[0].len_V35);
		rc = SQLBindParameter(hstmt_dre, 41, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V36, 0, &po[0].V36, sizeof(po[0].V36), &po[0].len_V36);
		rc = SQLBindParameter(hstmt_dre, 42, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V37, 0, &po[0].V37, sizeof(po[0].V37), &po[0].len_V37);
		rc = SQLBindParameter(hstmt_dre, 43, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V38, 0, &po[0].V38, sizeof(po[0].V38), &po[0].len_V38);
		rc = SQLBindParameter(hstmt_dre, 44, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V39, 0, &po[0].V39, sizeof(po[0].V39), &po[0].len_V39);
		rc = SQLBindParameter(hstmt_dre, 45, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V40, 0, &po[0].V40, sizeof(po[0].V40), &po[0].len_V40);
		rc = SQLBindParameter(hstmt_dre, 46, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V41, 0, &po[0].V41, sizeof(po[0].V41), &po[0].len_V41);
		rc = SQLBindParameter(hstmt_dre, 47, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V42, 0, &po[0].V42, sizeof(po[0].V42), &po[0].len_V42);
		rc = SQLBindParameter(hstmt_dre, 48, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V43, 0, &po[0].V43, sizeof(po[0].V43), &po[0].len_V43);
		rc = SQLBindParameter(hstmt_dre, 49, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V44, 0, &po[0].V44, sizeof(po[0].V44), &po[0].len_V44);
		rc = SQLBindParameter(hstmt_dre, 50, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V45, 0, &po[0].V45, sizeof(po[0].V45), &po[0].len_V45);
		rc = SQLBindParameter(hstmt_dre, 51, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V46, 0, &po[0].V46, sizeof(po[0].V46), &po[0].len_V46);
		rc = SQLBindParameter(hstmt_dre, 52, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V47, 0, &po[0].V47, sizeof(po[0].V47), &po[0].len_V47);
		rc = SQLBindParameter(hstmt_dre, 53, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V48, 0, &po[0].V48, sizeof(po[0].V48), &po[0].len_V48);
		rc = SQLBindParameter(hstmt_dre, 54, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V49, 0, &po[0].V49, sizeof(po[0].V49), &po[0].len_V49);
		rc = SQLBindParameter(hstmt_dre, 55, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V50, 0, &po[0].V50, sizeof(po[0].V50), &po[0].len_V50);
		rc = SQLBindParameter(hstmt_dre, 56, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V51, 0, &po[0].V51, sizeof(po[0].V51), &po[0].len_V51);
		rc = SQLBindParameter(hstmt_dre, 57, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V52, 0, &po[0].V52, sizeof(po[0].V52), &po[0].len_V52);
		rc = SQLBindParameter(hstmt_dre, 58, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V53, 0, &po[0].V53, sizeof(po[0].V53), &po[0].len_V53);
		rc = SQLBindParameter(hstmt_dre, 59, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V54, 0, &po[0].V54, sizeof(po[0].V54), &po[0].len_V54);
		rc = SQLBindParameter(hstmt_dre, 60, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V55, 0, &po[0].V55, sizeof(po[0].V55), &po[0].len_V55);
		rc = SQLBindParameter(hstmt_dre, 61, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V56, 0, &po[0].V56, sizeof(po[0].V56), &po[0].len_V56);
		rc = SQLBindParameter(hstmt_dre, 62, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V57, 0, &po[0].V57, sizeof(po[0].V57), &po[0].len_V57);
		rc = SQLBindParameter(hstmt_dre, 63, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V58, 0, &po[0].V58, sizeof(po[0].V58), &po[0].len_V58);
		rc = SQLBindParameter(hstmt_dre, 64, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V59, 0, &po[0].V59, sizeof(po[0].V59), &po[0].len_V59);
		rc = SQLBindParameter(hstmt_dre, 65, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V60, 0, &po[0].V60, sizeof(po[0].V60), &po[0].len_V60);
		rc = SQLBindParameter(hstmt_dre, 66, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V61, 0, &po[0].V61, sizeof(po[0].V61), &po[0].len_V61);
		rc = SQLBindParameter(hstmt_dre, 67, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V62, 0, &po[0].V62, sizeof(po[0].V62), &po[0].len_V62);
		rc = SQLBindParameter(hstmt_dre, 68, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V63, 0, &po[0].V63, sizeof(po[0].V63), &po[0].len_V63);
		rc = SQLBindParameter(hstmt_dre, 69, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V64, 0, &po[0].V64, sizeof(po[0].V64), &po[0].len_V64);
		rc = SQLBindParameter(hstmt_dre, 70, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V65, 0, &po[0].V65, sizeof(po[0].V65), &po[0].len_V65);
		rc = SQLBindParameter(hstmt_dre, 71, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V66, 0, &po[0].V66, sizeof(po[0].V66), &po[0].len_V66);
		rc = SQLBindParameter(hstmt_dre, 72, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V67, 0, &po[0].V67, sizeof(po[0].V67), &po[0].len_V67);
		rc = SQLBindParameter(hstmt_dre, 73, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V68, 0, &po[0].V68, sizeof(po[0].V68), &po[0].len_V68);
		rc = SQLBindParameter(hstmt_dre, 74, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V69, 0, &po[0].V69, sizeof(po[0].V69), &po[0].len_V69);
		rc = SQLBindParameter(hstmt_dre, 75, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V70, 0, &po[0].V70, sizeof(po[0].V70), &po[0].len_V70);
		rc = SQLBindParameter(hstmt_dre, 76, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V71, 0, &po[0].V71, sizeof(po[0].V71), &po[0].len_V71);
		rc = SQLBindParameter(hstmt_dre, 77, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V72, 0, &po[0].V72, sizeof(po[0].V72), &po[0].len_V72);
		rc = SQLBindParameter(hstmt_dre, 78, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V73, 0, &po[0].V73, sizeof(po[0].V73), &po[0].len_V73);
		rc = SQLBindParameter(hstmt_dre, 79, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V74, 0, &po[0].V74, sizeof(po[0].V74), &po[0].len_V74);
		rc = SQLBindParameter(hstmt_dre, 80, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V75, 0, &po[0].V75, sizeof(po[0].V75), &po[0].len_V75);
		rc = SQLBindParameter(hstmt_dre, 81, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V76, 0, &po[0].V76, sizeof(po[0].V76), &po[0].len_V76);
		rc = SQLBindParameter(hstmt_dre, 82, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V77, 0, &po[0].V77, sizeof(po[0].V77), &po[0].len_V77);
		rc = SQLBindParameter(hstmt_dre, 83, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V78, 0, &po[0].V78, sizeof(po[0].V78), &po[0].len_V78);
		rc = SQLBindParameter(hstmt_dre, 84, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V79, 0, &po[0].V79, sizeof(po[0].V79), &po[0].len_V79);
		rc = SQLBindParameter(hstmt_dre, 85, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V80, 0, &po[0].V80, sizeof(po[0].V80), &po[0].len_V80);
		rc = SQLBindParameter(hstmt_dre, 86, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V81, 0, &po[0].V81, sizeof(po[0].V81), &po[0].len_V81);
		rc = SQLBindParameter(hstmt_dre, 87, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V82, 0, &po[0].V82, sizeof(po[0].V82), &po[0].len_V82);
		rc = SQLBindParameter(hstmt_dre, 88, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V83, 0, &po[0].V83, sizeof(po[0].V83), &po[0].len_V83);
		rc = SQLBindParameter(hstmt_dre, 89, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V84, 0, &po[0].V84, sizeof(po[0].V84), &po[0].len_V84);
		rc = SQLBindParameter(hstmt_dre, 90, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V85, 0, &po[0].V85, sizeof(po[0].V85), &po[0].len_V85);
		rc = SQLBindParameter(hstmt_dre, 91, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V86, 0, &po[0].V86, sizeof(po[0].V86), &po[0].len_V86);
		rc = SQLBindParameter(hstmt_dre, 92, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V87, 0, &po[0].V87, sizeof(po[0].V87), &po[0].len_V87);
		rc = SQLBindParameter(hstmt_dre, 93, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V88, 0, &po[0].V88, sizeof(po[0].V88), &po[0].len_V88);
		rc = SQLBindParameter(hstmt_dre, 94, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V89, 0, &po[0].V89, sizeof(po[0].V89), &po[0].len_V89);
		rc = SQLBindParameter(hstmt_dre, 95, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V90, 0, &po[0].V90, sizeof(po[0].V90), &po[0].len_V90);
		rc = SQLBindParameter(hstmt_dre, 96, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V91, 0, &po[0].V91, sizeof(po[0].V91), &po[0].len_V91);
		rc = SQLBindParameter(hstmt_dre, 97, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V92, 0, &po[0].V92, sizeof(po[0].V92), &po[0].len_V92);
		rc = SQLBindParameter(hstmt_dre, 98, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V93, 0, &po[0].V93, sizeof(po[0].V93), &po[0].len_V93);
		rc = SQLBindParameter(hstmt_dre, 99, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V94, 0, &po[0].V94, sizeof(po[0].V94), &po[0].len_V94);
		rc = SQLBindParameter(hstmt_dre, 100, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V95, 0, &po[0].V95, sizeof(po[0].V95), &po[0].len_V95);

		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]�������ݿ�׼����ϣ�׼��������������ѭ��")
			.arg(m_iProcessID)
			.arg(CGlobalDataSaver::GetInstance()->m_sDbService);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);

		int iCurrDay;
		int iCurrMeter;
		QDate dtCurrent;

		m_iTickCount /*�������������ж��Ƿ���Ҫ�ύ*/ = iCurrDay = iCurrMeter = 0;

		LONG64 iCommitCount;
		iCommitCount = 0;
		m_iCurrlLine = 0;


		if (m_iIDStart > m_iIDEnd)  //���ID�Ǽ�¼ID �����ǵ��ID
		{
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			m_iJobflag = RunState::doneInsert;
			return;
		}
		rc = SQLPrepare(hstmt_dre, (SQLWCHAR*)statement.unicode(), SQL_NTS);
		if (!SQL_SUCCEEDED(rc))
		{
			sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLPrepare ������������[%2][%3]�����̽��˳�")
				.arg(m_iProcessID)
				.arg(rc)
				.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}
		/* ��㰴�����ڵ���ѭ�� [2016-3-4 by zzg] */
		for (iCurrDay = 0;	CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(iCurrDay) <= CGlobalDataSaver::GetInstance()->m_dtDataEnd;iCurrDay++)
		{
			dtCurrent = CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(iCurrDay);

			for (iCurrMeter = 0; iCurrMeter + m_iMeterIDStart <= m_iMeterIDEnd; iCurrMeter++)
			{
				m_iCurrlLine++;
				m_iIDCurrent = m_iCurrlLine + m_iIDStart - 1;

				po[m_iTickCount].metering_time.year = po[m_iTickCount].data_date.year = dtCurrent.year();
				po[m_iTickCount].metering_time.month = po[m_iTickCount].data_date.month = dtCurrent.month();
				po[m_iTickCount].metering_time.day = po[m_iTickCount].data_date.day = dtCurrent.day();

				po[m_iTickCount].vol_cur_id = m_iIDCurrent;
				po[m_iTickCount].meter_id = iCurrMeter + m_iMeterIDStart;
				po[m_iTickCount].V10 = po[m_iTickCount].V11 = po[m_iTickCount].V12 = po[m_iTickCount].V13 = po[m_iTickCount].V14 = po[m_iTickCount].V15 = po[m_iTickCount].V16 = po[m_iTickCount].V17 = po[m_iTickCount].V18 = po[m_iTickCount].V19 = po[m_iTickCount].V1 = (rand() % 41) + 1000;
				po[m_iTickCount].V20 = po[m_iTickCount].V21 = po[m_iTickCount].V22 = po[m_iTickCount].V23 = po[m_iTickCount].V24 = po[m_iTickCount].V25 = po[m_iTickCount].V26 = po[m_iTickCount].V27 = po[m_iTickCount].V28 = po[m_iTickCount].V29 = po[m_iTickCount].V2 = (rand() % 41) + 1000;
				po[m_iTickCount].V30 = po[m_iTickCount].V31 = po[m_iTickCount].V32 = po[m_iTickCount].V33 = po[m_iTickCount].V34 = po[m_iTickCount].V35 = po[m_iTickCount].V36 = po[m_iTickCount].V37 = po[m_iTickCount].V38 = po[m_iTickCount].V39 = po[m_iTickCount].V3 = (rand() % 41) + 1000;
				po[m_iTickCount].V40 = po[m_iTickCount].V41 = po[m_iTickCount].V42 = po[m_iTickCount].V43 = po[m_iTickCount].V44 = po[m_iTickCount].V45 = po[m_iTickCount].V46 = po[m_iTickCount].V47 = po[m_iTickCount].V48 = po[m_iTickCount].V49 = po[m_iTickCount].V4 = po[m_iTickCount].V1;
				po[m_iTickCount].V50 = po[m_iTickCount].V51 = po[m_iTickCount].V52 = po[m_iTickCount].V53 = po[m_iTickCount].V54 = po[m_iTickCount].V55 = po[m_iTickCount].V56 = po[m_iTickCount].V57 = po[m_iTickCount].V58 = po[m_iTickCount].V59 = po[m_iTickCount].V5 = po[m_iTickCount].V2;
				po[m_iTickCount].V60 = po[m_iTickCount].V61 = po[m_iTickCount].V62 = po[m_iTickCount].V63 = po[m_iTickCount].V64 = po[m_iTickCount].V65 = po[m_iTickCount].V66 = po[m_iTickCount].V67 = po[m_iTickCount].V68 = po[m_iTickCount].V69 = po[m_iTickCount].V6 = po[m_iTickCount].V3;
				po[m_iTickCount].V70 = po[m_iTickCount].V71 = po[m_iTickCount].V72 = po[m_iTickCount].V73 = po[m_iTickCount].V74 = po[m_iTickCount].V75 = po[m_iTickCount].V76 = po[m_iTickCount].V77 = po[m_iTickCount].V78 = po[m_iTickCount].V79 = po[m_iTickCount].V7 = po[m_iTickCount].V1;
				po[m_iTickCount].V80 = po[m_iTickCount].V81 = po[m_iTickCount].V82 = po[m_iTickCount].V83 = po[m_iTickCount].V84 = po[m_iTickCount].V85 = po[m_iTickCount].V86 = po[m_iTickCount].V87 = po[m_iTickCount].V88 = po[m_iTickCount].V89 = po[m_iTickCount].V8 = po[m_iTickCount].V2;
				po[m_iTickCount].V90 = po[m_iTickCount].V91 = po[m_iTickCount].V92 = po[m_iTickCount].V93 = po[m_iTickCount].V94 = po[m_iTickCount].V95 = po[m_iTickCount].V96 = po[m_iTickCount].V9 = po[m_iTickCount].V3;

				po[m_iTickCount].data_date.hour = 12;
				po[m_iTickCount].data_date.minute = 0;
				po[m_iTickCount].data_date.second = 0;
				po[m_iTickCount].data_date.fraction = 0;

				po[m_iTickCount].metering_time.hour = 12;
				po[m_iTickCount].metering_time.minute = 0;
				po[m_iTickCount].metering_time.second = 0;
				po[m_iTickCount].metering_time.fraction = 0;

				po[m_iTickCount].len_vol_cur_id = SQL_NTS;
				po[m_iTickCount].len_meter_id = SQL_NTS;

				po[m_iTickCount].len_V10 = po[m_iTickCount].len_V11 = po[m_iTickCount].len_V12 = po[m_iTickCount].len_V13 = po[m_iTickCount].len_V14 = po[m_iTickCount].len_V15 = po[m_iTickCount].len_V16 = po[m_iTickCount].len_V17 = po[m_iTickCount].len_V18 = po[m_iTickCount].len_V19 = po[m_iTickCount].len_V1 = SQL_NTS;
				po[m_iTickCount].len_V20 = po[m_iTickCount].len_V21 = po[m_iTickCount].len_V22 = po[m_iTickCount].len_V23 = po[m_iTickCount].len_V24 = po[m_iTickCount].len_V25 = po[m_iTickCount].len_V26 = po[m_iTickCount].len_V27 = po[m_iTickCount].len_V28 = po[m_iTickCount].len_V29 = po[m_iTickCount].len_V2 = SQL_NTS;
				po[m_iTickCount].len_V30 = po[m_iTickCount].len_V31 = po[m_iTickCount].len_V32 = po[m_iTickCount].len_V33 = po[m_iTickCount].len_V34 = po[m_iTickCount].len_V35 = po[m_iTickCount].len_V36 = po[m_iTickCount].len_V37 = po[m_iTickCount].len_V38 = po[m_iTickCount].len_V39 = po[m_iTickCount].len_V3 = SQL_NTS;
				po[m_iTickCount].len_V40 = po[m_iTickCount].len_V41 = po[m_iTickCount].len_V42 = po[m_iTickCount].len_V43 = po[m_iTickCount].len_V44 = po[m_iTickCount].len_V45 = po[m_iTickCount].len_V46 = po[m_iTickCount].len_V47 = po[m_iTickCount].len_V48 = po[m_iTickCount].len_V49 = po[m_iTickCount].len_V4 = SQL_NTS;
				po[m_iTickCount].len_V50 = po[m_iTickCount].len_V51 = po[m_iTickCount].len_V52 = po[m_iTickCount].len_V53 = po[m_iTickCount].len_V54 = po[m_iTickCount].len_V55 = po[m_iTickCount].len_V56 = po[m_iTickCount].len_V57 = po[m_iTickCount].len_V58 = po[m_iTickCount].len_V59 = po[m_iTickCount].len_V5 = SQL_NTS;
				po[m_iTickCount].len_V60 = po[m_iTickCount].len_V61 = po[m_iTickCount].len_V62 = po[m_iTickCount].len_V63 = po[m_iTickCount].len_V64 = po[m_iTickCount].len_V65 = po[m_iTickCount].len_V66 = po[m_iTickCount].len_V67 = po[m_iTickCount].len_V68 = po[m_iTickCount].len_V69 = po[m_iTickCount].len_V6 = SQL_NTS;
				po[m_iTickCount].len_V70 = po[m_iTickCount].len_V71 = po[m_iTickCount].len_V72 = po[m_iTickCount].len_V73 = po[m_iTickCount].len_V74 = po[m_iTickCount].len_V75 = po[m_iTickCount].len_V76 = po[m_iTickCount].len_V77 = po[m_iTickCount].len_V78 = po[m_iTickCount].len_V79 = po[m_iTickCount].len_V7 = SQL_NTS;
				po[m_iTickCount].len_V80 = po[m_iTickCount].len_V81 = po[m_iTickCount].len_V82 = po[m_iTickCount].len_V83 = po[m_iTickCount].len_V84 = po[m_iTickCount].len_V85 = po[m_iTickCount].len_V86 = po[m_iTickCount].len_V87 = po[m_iTickCount].len_V88 = po[m_iTickCount].len_V89 = po[m_iTickCount].len_V8 = SQL_NTS;
				po[m_iTickCount].len_V90 = po[m_iTickCount].len_V91 = po[m_iTickCount].len_V92 = po[m_iTickCount].len_V93 = po[m_iTickCount].len_V94 = po[m_iTickCount].len_V95 = po[m_iTickCount].len_V96 = po[m_iTickCount].len_V9 = SQL_NTS;

				po[m_iTickCount].len_data_date = sizeof(po[0].data_date);
				po[m_iTickCount].len_metering_time = sizeof(po[0].metering_time);

				m_iTickCount++;
				iCommitCount++;

				/* ����ﵽ�ύ������������������������ϣ����ύ [2016-3-4 by zzg] */
				if (m_iTickCount >= CGlobalDataSaver::GetInstance()->m_iDCSL || m_iIDCurrent >= m_iIDEnd)
				{
					/* �ύһ�� [2016-3-4 by zzg] */
					rc = 0;
					rc = SQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)m_iTickCount, 0);
					if (rc != SQL_SUCCESS)
					{
						sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
						CleanDBConnect(hstmt_dre, hdbc_dre, henv);
						free(po);
						free(param_status);
						m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetStmtAttr�쳣�˳����Ѿ�д��[%2]�����ݣ�ʣ��[%3]��д��[%4]")
							.arg(m_iProcessID)
							.arg(m_iCurrlLine)
							.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1)
							.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
						CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
						m_iJobflag = RunState::except;
						return;
					}

					rc = SQLExecute(hstmt_dre);

					if (rc != SQL_SUCCESS)
					{
						sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
						CleanDBConnect(hstmt_dre, hdbc_dre, henv);
						free(po);
						free(param_status);
						m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLExecute�쳣�˳����Ѿ�д��[%2]�����ݣ�ʣ��[%3]��д��[%4]")
							.arg(m_iProcessID)
							.arg(m_iCurrlLine)
							.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1)
							.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
						CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
						m_iJobflag = RunState::except;
						return;
					}

					m_iTickCount = 0;
					/* �ύ���ﲢ�������� [2016-3-4 by zzg] */
					rc = SQLEndTran(SQL_HANDLE_DBC, hdbc_dre, SQL_COMMIT);
					if (!SQL_SUCCEEDED(rc))
					{
						CleanDBConnect(hstmt_dre, hdbc_dre, henv);
						free(po);
						free(param_status);
						m_iJobflag = RunState::except;
						return;
					}
					m_iCommitedLine = m_iCurrlLine;
					m_iCommitedSize = (m_iCurrlLine * (sizeof(crm_mnp_npdb_energy) + sizeof(SQLUSMALLINT)) / (1024 * 1024));
					m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]�����Ѿ�д��[%2]�����ݣ�ʣ��[%3]��д��")
						.arg(m_iProcessID)
						.arg(m_iCommitedLine)
						.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1);
					CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
					CGlobalDataSaver::GetInstance()->m_pTableOut->item(m_iProcessID - 1, 2)->setText(QString("%1").arg(m_iCurrlLine));
					iCommitCount = 0;
				}
				if (m_iIDCurrent >= m_iIDEnd)
					break;
			}//for
			if (m_iIDCurrent >= m_iIDEnd)
				break;
		}//for

		/* �ύ���񲢷������� [2016-3-4 by zzg] */
		rc = SQLEndTran(SQL_HANDLE_DBC, hdbc_dre, SQL_COMMIT);
		if (!SQL_SUCCEEDED(rc))
		{
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_iJobflag = RunState::except;
			return;
		}
		m_iCommitedLine = m_iCurrlLine;
		m_iCommitedSize = (LONG64)((m_iCurrlLine * (sizeof(crm_mnp_npdb_energy) + sizeof(SQLUSMALLINT))) / (1024 * 1024));

		CleanDBConnect(hstmt_dre, hdbc_dre, henv);

		free(po);
		free(param_status);
	}

	if (RunState::insert == m_iJobflag)
	{
		m_iJobflag = RunState::doneInsert ;
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]�����Ѿ�д����ϣ���д��[%2]�����ݣ���ʱ[%3]��")
			.arg(m_iProcessID)
			.arg(m_iCurrlLine)
			.arg(m_dtPick.secsTo(QDateTime::currentDateTime()));
	}
	CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
}

