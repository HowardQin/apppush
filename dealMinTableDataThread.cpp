#include "dealMinTableDataThread.h"
#include <qdatetime.h>

#include "SQLFuncPublic.h"


DealMinTableDataThread::DealMinTableDataThread()
{
	m_bPause = false;
	m_iCommitedLine = 0 ;
	m_iCommitedSize = 0 ; 
}

DealMinTableDataThread::~DealMinTableDataThread()
{

}

void DealMinTableDataThread::stop()
{

}

void DealMinTableDataThread::run()
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
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]��������ODBC���������Ӽ�SQL�������������[%2]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		return ;
	}

	rc = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) (SQL_OV_ODBC3), SQL_IS_UINTEGER);
	if (!SQL_SUCCEEDED(rc)) 
	{
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetEnvAttr����������[%2]�����̽��˳�")
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
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc_dre)����������[%2]�����̽��˳�")
			.arg(m_iProcessID)
			.arg(rc);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return ;
	}

 	rc = SQLConnect(hdbc_dre, (SQLWCHAR*) CGlobalDataSaver::GetInstance()->m_sDbService.unicode(), SQL_NTS, 
  		(SQLWCHAR*) CGlobalDataSaver::GetInstance()->m_sDbUserName.unicode(), SQL_NTS, (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbUserPass.unicode(), SQL_NTS);
	if (!SQL_SUCCEEDED(rc)) 
	{
		sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���̽������ݿ����ӳ���������[%2][%3]�����̽��˳�")
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
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLSetConnectAttr����������[%2][%3]�����̽��˳�")
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
		m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]����SQLAllocHandle����������[%2][%3]�����̽��˳�")
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
		statement = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("%1 INTO E_MIN_TABLE_P (vol_cur_id, meter_id, data_date, metering_time,PAP_E) VALUES "
			"(?, ?, ?, ?, ?)").arg(CGlobalDataSaver::GetInstance()->GetInsertString());

		crm_mnp_npdb_min *po = (crm_mnp_npdb_min *)malloc(CGlobalDataSaver::GetInstance()->m_iDCSL * sizeof(crm_mnp_npdb_min));
		SQLUSMALLINT *param_status = (SQLUSMALLINT *)malloc(CGlobalDataSaver::GetInstance()->m_iDCSL * sizeof(SQLUSMALLINT));
		SQLINTEGER params_processed = 0;

		rc = SQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER) sizeof(crm_mnp_npdb_min), 0);
		if (!SQL_SUCCEEDED(rc))
		{
			sErrorMsg = diagnostic(SQL_HANDLE_STMT, &hstmt_dre);
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			free(po);
			free(param_status);
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ����������[%2][%3]�����̽��˳�")
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
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ����������[%2][%3]�����̽��˳�")
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
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ����������[%2][%3]�����̽��˳�")
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
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLSetStmtAttr ����������[%2][%3]�����̽��˳�")
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
		rc = SQLBindParameter(hstmt_dre, 5, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V1, 0, &po[0].V1, sizeof(po[0].V1), &po[0].len_V1);


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
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]���� SQLPrepare ����������[%2][%3]�����̽��˳�")
				.arg(m_iProcessID)
				.arg(rc)
				.arg(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode((char *)sErrorMsg));
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}
		/* ��㰴�����ڵ���ѭ�� [2016-3-4 by zzg] */
		for (iCurrDay = 0;
			CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(iCurrDay) <= CGlobalDataSaver::GetInstance()->m_dtDataEnd;
			iCurrDay++)
		{
			dtCurrent = CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(iCurrDay);

			for (iCurrMeter = 0; iCurrMeter + m_iMeterIDStart <= m_iMeterIDEnd; iCurrMeter++)
			{
				m_iCurrlLine++;
				m_iIDCurrent = m_iCurrlLine + m_iIDStart - 1;
				//generating data
				po[m_iTickCount].metering_time.year = po[m_iTickCount].data_date.year = dtCurrent.year();
				po[m_iTickCount].metering_time.month = po[m_iTickCount].data_date.month = dtCurrent.month();
				po[m_iTickCount].metering_time.day = po[m_iTickCount].data_date.day = dtCurrent.day();

				po[m_iTickCount].vol_cur_id = m_iIDCurrent;
				po[m_iTickCount].meter_id = iCurrMeter + m_iMeterIDStart;
				po[m_iTickCount].V1 = (rand() % 41) + 1000;

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

				po[m_iTickCount].len_V1 = SQL_NTS;

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
					m_iCommitedSize = (m_iCurrlLine * (sizeof(crm_mnp_npdb_min) + sizeof(SQLUSMALLINT)) / (1024 * 1024));
					m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("��[%1]�����Ѿ�д��[%2]�����ݣ�ʣ��[%3]��д��")
						.arg(m_iProcessID)
						.arg(m_iCommitedLine)
						.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1);
					CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
					CGlobalDataSaver::GetInstance()->m_pTableOut->item(m_iProcessID - 1, 2)->setText(QString("%1").arg(m_iCurrlLine));
					rc = SQLPrepare(hstmt_dre, (SQLWCHAR*)statement.unicode(), SQL_NTS);
					iCommitCount = 0;
				}

				if (m_iIDCurrent >= m_iIDEnd)
					break;
			}
			if (m_iIDCurrent >= m_iIDEnd)
				break;
		}

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
		m_iCommitedSize = (LONG64)((m_iCurrlLine * (sizeof(crm_mnp_npdb_min) + sizeof(SQLUSMALLINT))) / (1024 * 1024));

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


