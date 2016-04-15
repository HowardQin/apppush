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
	//任务开始
	m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程已启动，准备连接数据库[%2]")
		.arg(m_iProcessID)
		.arg(CGlobalDataSaver::GetInstance()->m_sDbService);
	CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);

	SQLHENV henv = 0;
	SQLHDBC hdbc_dre = 0;
	SQLHSTMT hstmt_dre = 0;

	//申请ODBC环境、连接及SQL句柄并设置
	try {
		mySQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

		mySQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)(SQL_OV_ODBC3), SQL_IS_UINTEGER);

		mySQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc_dre);

		//5秒连接超时
		mySQLSetConnectAttr(hdbc_dre, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

		mySQLConnect(hdbc_dre, (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbService.unicode(), SQL_NTS,
			                                     (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbUserName.unicode(), SQL_NTS, 
												 (SQLWCHAR*)CGlobalDataSaver::GetInstance()->m_sDbUserPass.unicode(), SQL_NTS);

		mySQLSetConnectAttr(hdbc_dre, SQL_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);

		mySQLAllocHandle(SQL_HANDLE_STMT, hdbc_dre, &hstmt_dre);
	}
	catch (...)
	{
		CleanDBConnect(hstmt_dre, hdbc_dre, henv);
		CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		m_iJobflag = RunState::except;
		return;
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
		try {
			mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER) sizeof(crm_mnp_npdb_min), 0);

			mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)CGlobalDataSaver::GetInstance()->m_iDCSL, 0);

			mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_STATUS_PTR, param_status, 0);

			mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMS_PROCESSED_PTR, &params_processed, 0);

			mySQLBindParameter(hstmt_dre, 1, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_vol_cur_id, 0, &po[0].vol_cur_id, sizeof(po[0].vol_cur_id), &po[0].len_vol_cur_id);
			mySQLBindParameter(hstmt_dre, 2, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_meter_id, 0, &po[0].meter_id, sizeof(po[0].meter_id), &po[0].len_meter_id);
			mySQLBindParameter(hstmt_dre, 3, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TIMESTAMP, po[0].len_data_date, 0, &po[0].data_date, sizeof(po[0].data_date), &po[0].len_data_date);
			mySQLBindParameter(hstmt_dre, 4, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TIMESTAMP, po[0].len_metering_time, 0, &po[0].metering_time, sizeof(po[0].metering_time), &po[0].len_metering_time);
			mySQLBindParameter(hstmt_dre, 5, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V1, 0, &po[0].V1, sizeof(po[0].V1), &po[0].len_V1);

			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程数据库准备完毕，准备进入数据生成循环")
				.arg(m_iProcessID)
				.arg(CGlobalDataSaver::GetInstance()->m_sDbService);
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);

			int iCurrDay;
			int iCurrMeter;
			QDate dtCurrent;

			m_iTickCount /*计数器，用来判定是否需要提交*/ = iCurrDay = iCurrMeter = 0;

			LONG64 iCommitCount;
			iCommitCount = 0;
			m_iCurrlLine = 0;

			if (m_iIDStart > m_iIDEnd)  //这个ID是记录ID ，不是电表ID
			{
				m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程 m_iIDStart = %2 m_iIDEnd = %3")
					.arg(m_iIDStart)
					.arg(m_iIDEnd);
				throw m_sMsg;
			}
			
			mySQLPrepare(hstmt_dre, (SQLWCHAR*)statement.unicode(), SQL_NTS);

			/* 外层按照日期递增循环 [2016-3-4 by zzg] */
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

					/* 如果达到提交量，或者所有数据已生成完毕，就提交 [2016-3-4 by zzg] */
					if (m_iTickCount >= CGlobalDataSaver::GetInstance()->m_iDCSL || m_iIDCurrent >= m_iIDEnd)
					{
						/* 提交一次 [2016-3-4 by zzg] */
						mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)m_iTickCount, 0);

						mySQLExecute(hstmt_dre);

						/* 提交事物并发出提醒 [2016-3-4 by zzg] */
						mySQLEndTran(SQL_HANDLE_DBC, hdbc_dre, SQL_COMMIT);
						m_iTickCount = 0;
						m_iCommitedLine = m_iCurrlLine;
						m_iCommitedSize = (m_iCurrlLine * (sizeof(crm_mnp_npdb_min) + sizeof(SQLUSMALLINT)) / (1024 * 1024));
						m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程已经写入[%2]行数据，剩余[%3]待写入")
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

			/* 提交事务并发出提醒 [2016-3-4 by zzg] */
			mySQLEndTran(SQL_HANDLE_DBC, hdbc_dre, SQL_COMMIT);
			m_iCommitedLine = m_iCurrlLine;
			m_iCommitedSize = (LONG64)((m_iCurrlLine * (sizeof(crm_mnp_npdb_min) + sizeof(SQLUSMALLINT))) / (1024 * 1024));
			free(po);
			free(param_status);
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			m_iJobflag = RunState::doneInsert;
			m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程已经写入完毕，共写入[%2]行数据，用时[%3]秒")
				.arg(m_iProcessID)
				.arg(m_iCurrlLine)
				.arg(m_dtPick.secsTo(QDateTime::currentDateTime()));
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
		}
		catch (...)
		{
			free(po);
			free(param_status);
			CleanDBConnect(hstmt_dre, hdbc_dre, henv);
			CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			m_iJobflag = RunState::except;
			return;
		}
	}//if(RunState::insert == m_iJobflag)
}


