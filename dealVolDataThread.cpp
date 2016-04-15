#include "dealVolDataThread.h"
#include <qdatetime.h>

#include "SQLFuncPublic.h"


DealVolDataThread::DealVolDataThread()
{
	m_bPause = false;
	m_iCommitedLine = 0 ;
	m_iCommitedSize = 0 ; 
}

DealVolDataThread::~DealVolDataThread()
{

}

void DealVolDataThread::stop()
{

}

void DealVolDataThread::run()
{ 
	if (reTryCount > 0)//sleep 1 sec, if failed and restarted
		sleep(reTryCount);
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

		mySQLAllocHandle(SQL_HANDLE_STMT, hdbc_dre, &hstmt_dre);

		//purge table if required, 
		//only purge once if there're multiple threads.
		QMutexLocker locker(&m_mutex);
		if (CGlobalDataSaver::GetInstance()->m_bCleanTable){
			QString cmd = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("PURGEDATA %1")
				.arg(CGlobalDataSaver::GetInstance()->m_sDataTable);
			try {
				mySQLExecDirect(hstmt_dre, (SQLWCHAR*)cmd.unicode(), SQL_NTS);
			}
			catch (...)
			{
				CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
			}
			CGlobalDataSaver::GetInstance()->m_bCleanTable = false;
		}
		locker.unlock();

		mySQLSetConnectAttr(hdbc_dre, SQL_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);
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
	if (RunState::insert == m_iJobflag)
	{
		statement = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("%1 INTO E_MP_VOL_CURVE_P (vol_cur_id, meter_id, phase, data_date, metering_time,"
			"V1, V2, V3, V4, V5, V6, V7, V8, V9, V10, V11, V12, V13, V14, V15, V16, V17, V18, V19, V20, V21,"
			"V22, V23, V24, V25, V26, V27, V28, V29, V30, V31, V32, V33, V34, V35, V36, V37, V38, V39, V40, "
			"V41, V42, V43, V44, V45, V46, V47, V48, V49, V50, V51, V52, V53, V54, V55, V56, V57, V58, V59, "
			"V60, V61, V62, V63, V64, V65, V66, V67, V68, V69, V70, V71, V72, V73, V74, V75, V76, V77, V78, "
			"V79, V80, V81, V82, V83, V84, V85, V86, V87, V88, V89, V90, V91, V92, V93, V94, V95, V96) VALUES "
			"(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
			"?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
			.arg(CGlobalDataSaver::GetInstance()->GetInsertString());
			crm_mnp_npdb_esvf *po = (crm_mnp_npdb_esvf *)malloc(CGlobalDataSaver::GetInstance()->m_iDCSL * sizeof(crm_mnp_npdb_esvf));
			SQLUSMALLINT *param_status = (SQLUSMALLINT *)malloc(CGlobalDataSaver::GetInstance()->m_iDCSL * sizeof(SQLUSMALLINT));
			SQLINTEGER params_processed = 0;
			try {

				mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_BIND_TYPE, (SQLPOINTER) sizeof(crm_mnp_npdb_esvf), 0);

				mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMSET_SIZE, (SQLPOINTER)CGlobalDataSaver::GetInstance()->m_iDCSL, 0);

				mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAM_STATUS_PTR, param_status, 0);

				mySQLSetStmtAttr(hstmt_dre, SQL_ATTR_PARAMS_PROCESSED_PTR, &params_processed, 0);

				mySQLBindParameter(hstmt_dre, 1, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_vol_cur_id, 0, &po[0].vol_cur_id, sizeof(po[0].vol_cur_id), &po[0].len_vol_cur_id);
				mySQLBindParameter(hstmt_dre, 2, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_meter_id, 0, &po[0].meter_id, sizeof(po[0].meter_id), &po[0].len_meter_id);
				mySQLBindParameter(hstmt_dre, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, po[0].len_phase, 0, po[0].phase, sizeof(po[0].phase), &po[0].len_phase);
				mySQLBindParameter(hstmt_dre, 4, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TIMESTAMP, po[0].len_data_date, 0, &po[0].data_date, sizeof(po[0].data_date), &po[0].len_data_date);
				mySQLBindParameter(hstmt_dre, 5, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TIMESTAMP, po[0].len_metering_time, 0, &po[0].metering_time, sizeof(po[0].metering_time), &po[0].len_metering_time);
				mySQLBindParameter(hstmt_dre, 6, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V1, 0, &po[0].V1, sizeof(po[0].V1), &po[0].len_V1);
				mySQLBindParameter(hstmt_dre, 7, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V2, 0, &po[0].V2, sizeof(po[0].V2), &po[0].len_V2);
				mySQLBindParameter(hstmt_dre, 8, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V3, 0, &po[0].V3, sizeof(po[0].V3), &po[0].len_V3);
				mySQLBindParameter(hstmt_dre, 9, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V4, 0, &po[0].V4, sizeof(po[0].V4), &po[0].len_V4);
				mySQLBindParameter(hstmt_dre, 10, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V5, 0, &po[0].V5, sizeof(po[0].V5), &po[0].len_V5);
				mySQLBindParameter(hstmt_dre, 11, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V6, 0, &po[0].V6, sizeof(po[0].V6), &po[0].len_V6);
				mySQLBindParameter(hstmt_dre, 12, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V7, 0, &po[0].V7, sizeof(po[0].V7), &po[0].len_V7);
				mySQLBindParameter(hstmt_dre, 13, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V8, 0, &po[0].V8, sizeof(po[0].V8), &po[0].len_V8);
				mySQLBindParameter(hstmt_dre, 14, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V9, 0, &po[0].V9, sizeof(po[0].V9), &po[0].len_V9);
				mySQLBindParameter(hstmt_dre, 15, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V10, 0, &po[0].V10, sizeof(po[0].V10), &po[0].len_V10);
				mySQLBindParameter(hstmt_dre, 16, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V11, 0, &po[0].V11, sizeof(po[0].V11), &po[0].len_V11);
				mySQLBindParameter(hstmt_dre, 17, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V12, 0, &po[0].V12, sizeof(po[0].V12), &po[0].len_V12);
				mySQLBindParameter(hstmt_dre, 18, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V13, 0, &po[0].V13, sizeof(po[0].V13), &po[0].len_V13);
				mySQLBindParameter(hstmt_dre, 19, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V14, 0, &po[0].V14, sizeof(po[0].V14), &po[0].len_V14);
				mySQLBindParameter(hstmt_dre, 20, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V15, 0, &po[0].V15, sizeof(po[0].V15), &po[0].len_V15);
				mySQLBindParameter(hstmt_dre, 21, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V16, 0, &po[0].V16, sizeof(po[0].V16), &po[0].len_V16);
				mySQLBindParameter(hstmt_dre, 22, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V17, 0, &po[0].V17, sizeof(po[0].V17), &po[0].len_V17);
				mySQLBindParameter(hstmt_dre, 23, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V18, 0, &po[0].V18, sizeof(po[0].V18), &po[0].len_V18);
				mySQLBindParameter(hstmt_dre, 24, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V19, 0, &po[0].V19, sizeof(po[0].V19), &po[0].len_V19);
				mySQLBindParameter(hstmt_dre, 25, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V20, 0, &po[0].V20, sizeof(po[0].V20), &po[0].len_V20);
				mySQLBindParameter(hstmt_dre, 26, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V21, 0, &po[0].V21, sizeof(po[0].V21), &po[0].len_V21);
				mySQLBindParameter(hstmt_dre, 27, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V22, 0, &po[0].V22, sizeof(po[0].V22), &po[0].len_V22);
				mySQLBindParameter(hstmt_dre, 28, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V23, 0, &po[0].V23, sizeof(po[0].V23), &po[0].len_V23);
				mySQLBindParameter(hstmt_dre, 29, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V24, 0, &po[0].V24, sizeof(po[0].V24), &po[0].len_V24);
				mySQLBindParameter(hstmt_dre, 30, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V25, 0, &po[0].V25, sizeof(po[0].V25), &po[0].len_V25);
				mySQLBindParameter(hstmt_dre, 31, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V26, 0, &po[0].V26, sizeof(po[0].V26), &po[0].len_V26);
				mySQLBindParameter(hstmt_dre, 32, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V27, 0, &po[0].V27, sizeof(po[0].V27), &po[0].len_V27);
				mySQLBindParameter(hstmt_dre, 33, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V28, 0, &po[0].V28, sizeof(po[0].V28), &po[0].len_V28);
				mySQLBindParameter(hstmt_dre, 34, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V29, 0, &po[0].V29, sizeof(po[0].V29), &po[0].len_V29);
				mySQLBindParameter(hstmt_dre, 35, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V30, 0, &po[0].V30, sizeof(po[0].V30), &po[0].len_V30);
				mySQLBindParameter(hstmt_dre, 36, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V31, 0, &po[0].V31, sizeof(po[0].V31), &po[0].len_V31);
				mySQLBindParameter(hstmt_dre, 37, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V32, 0, &po[0].V32, sizeof(po[0].V32), &po[0].len_V32);
				mySQLBindParameter(hstmt_dre, 38, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V33, 0, &po[0].V33, sizeof(po[0].V33), &po[0].len_V33);
				mySQLBindParameter(hstmt_dre, 39, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V34, 0, &po[0].V34, sizeof(po[0].V34), &po[0].len_V34);
				mySQLBindParameter(hstmt_dre, 40, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V35, 0, &po[0].V35, sizeof(po[0].V35), &po[0].len_V35);
				mySQLBindParameter(hstmt_dre, 41, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V36, 0, &po[0].V36, sizeof(po[0].V36), &po[0].len_V36);
				mySQLBindParameter(hstmt_dre, 42, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V37, 0, &po[0].V37, sizeof(po[0].V37), &po[0].len_V37);
				mySQLBindParameter(hstmt_dre, 43, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V38, 0, &po[0].V38, sizeof(po[0].V38), &po[0].len_V38);
				mySQLBindParameter(hstmt_dre, 44, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V39, 0, &po[0].V39, sizeof(po[0].V39), &po[0].len_V39);
				mySQLBindParameter(hstmt_dre, 45, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V40, 0, &po[0].V40, sizeof(po[0].V40), &po[0].len_V40);
				mySQLBindParameter(hstmt_dre, 46, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V41, 0, &po[0].V41, sizeof(po[0].V41), &po[0].len_V41);
				mySQLBindParameter(hstmt_dre, 47, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V42, 0, &po[0].V42, sizeof(po[0].V42), &po[0].len_V42);
				mySQLBindParameter(hstmt_dre, 48, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V43, 0, &po[0].V43, sizeof(po[0].V43), &po[0].len_V43);
				mySQLBindParameter(hstmt_dre, 49, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V44, 0, &po[0].V44, sizeof(po[0].V44), &po[0].len_V44);
				mySQLBindParameter(hstmt_dre, 50, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V45, 0, &po[0].V45, sizeof(po[0].V45), &po[0].len_V45);
				mySQLBindParameter(hstmt_dre, 51, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V46, 0, &po[0].V46, sizeof(po[0].V46), &po[0].len_V46);
				mySQLBindParameter(hstmt_dre, 52, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V47, 0, &po[0].V47, sizeof(po[0].V47), &po[0].len_V47);
				mySQLBindParameter(hstmt_dre, 53, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V48, 0, &po[0].V48, sizeof(po[0].V48), &po[0].len_V48);
				mySQLBindParameter(hstmt_dre, 54, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V49, 0, &po[0].V49, sizeof(po[0].V49), &po[0].len_V49);
				mySQLBindParameter(hstmt_dre, 55, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V50, 0, &po[0].V50, sizeof(po[0].V50), &po[0].len_V50);
				mySQLBindParameter(hstmt_dre, 56, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V51, 0, &po[0].V51, sizeof(po[0].V51), &po[0].len_V51);
				mySQLBindParameter(hstmt_dre, 57, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V52, 0, &po[0].V52, sizeof(po[0].V52), &po[0].len_V52);
				mySQLBindParameter(hstmt_dre, 58, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V53, 0, &po[0].V53, sizeof(po[0].V53), &po[0].len_V53);
				mySQLBindParameter(hstmt_dre, 59, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V54, 0, &po[0].V54, sizeof(po[0].V54), &po[0].len_V54);
				mySQLBindParameter(hstmt_dre, 60, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V55, 0, &po[0].V55, sizeof(po[0].V55), &po[0].len_V55);
				mySQLBindParameter(hstmt_dre, 61, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V56, 0, &po[0].V56, sizeof(po[0].V56), &po[0].len_V56);
				mySQLBindParameter(hstmt_dre, 62, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V57, 0, &po[0].V57, sizeof(po[0].V57), &po[0].len_V57);
				mySQLBindParameter(hstmt_dre, 63, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V58, 0, &po[0].V58, sizeof(po[0].V58), &po[0].len_V58);
				mySQLBindParameter(hstmt_dre, 64, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V59, 0, &po[0].V59, sizeof(po[0].V59), &po[0].len_V59);
				mySQLBindParameter(hstmt_dre, 65, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V60, 0, &po[0].V60, sizeof(po[0].V60), &po[0].len_V60);
				mySQLBindParameter(hstmt_dre, 66, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V61, 0, &po[0].V61, sizeof(po[0].V61), &po[0].len_V61);
				mySQLBindParameter(hstmt_dre, 67, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V62, 0, &po[0].V62, sizeof(po[0].V62), &po[0].len_V62);
				mySQLBindParameter(hstmt_dre, 68, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V63, 0, &po[0].V63, sizeof(po[0].V63), &po[0].len_V63);
				mySQLBindParameter(hstmt_dre, 69, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V64, 0, &po[0].V64, sizeof(po[0].V64), &po[0].len_V64);
				mySQLBindParameter(hstmt_dre, 70, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V65, 0, &po[0].V65, sizeof(po[0].V65), &po[0].len_V65);
				mySQLBindParameter(hstmt_dre, 71, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V66, 0, &po[0].V66, sizeof(po[0].V66), &po[0].len_V66);
				mySQLBindParameter(hstmt_dre, 72, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V67, 0, &po[0].V67, sizeof(po[0].V67), &po[0].len_V67);
				mySQLBindParameter(hstmt_dre, 73, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V68, 0, &po[0].V68, sizeof(po[0].V68), &po[0].len_V68);
				mySQLBindParameter(hstmt_dre, 74, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V69, 0, &po[0].V69, sizeof(po[0].V69), &po[0].len_V69);
				mySQLBindParameter(hstmt_dre, 75, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V70, 0, &po[0].V70, sizeof(po[0].V70), &po[0].len_V70);
				mySQLBindParameter(hstmt_dre, 76, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V71, 0, &po[0].V71, sizeof(po[0].V71), &po[0].len_V71);
				mySQLBindParameter(hstmt_dre, 77, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V72, 0, &po[0].V72, sizeof(po[0].V72), &po[0].len_V72);
				mySQLBindParameter(hstmt_dre, 78, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V73, 0, &po[0].V73, sizeof(po[0].V73), &po[0].len_V73);
				mySQLBindParameter(hstmt_dre, 79, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V74, 0, &po[0].V74, sizeof(po[0].V74), &po[0].len_V74);
				mySQLBindParameter(hstmt_dre, 80, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V75, 0, &po[0].V75, sizeof(po[0].V75), &po[0].len_V75);
				mySQLBindParameter(hstmt_dre, 81, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V76, 0, &po[0].V76, sizeof(po[0].V76), &po[0].len_V76);
				mySQLBindParameter(hstmt_dre, 82, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V77, 0, &po[0].V77, sizeof(po[0].V77), &po[0].len_V77);
				mySQLBindParameter(hstmt_dre, 83, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V78, 0, &po[0].V78, sizeof(po[0].V78), &po[0].len_V78);
				mySQLBindParameter(hstmt_dre, 84, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V79, 0, &po[0].V79, sizeof(po[0].V79), &po[0].len_V79);
				mySQLBindParameter(hstmt_dre, 85, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V80, 0, &po[0].V80, sizeof(po[0].V80), &po[0].len_V80);
				mySQLBindParameter(hstmt_dre, 86, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V81, 0, &po[0].V81, sizeof(po[0].V81), &po[0].len_V81);
				mySQLBindParameter(hstmt_dre, 87, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V82, 0, &po[0].V82, sizeof(po[0].V82), &po[0].len_V82);
				mySQLBindParameter(hstmt_dre, 88, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V83, 0, &po[0].V83, sizeof(po[0].V83), &po[0].len_V83);
				mySQLBindParameter(hstmt_dre, 89, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V84, 0, &po[0].V84, sizeof(po[0].V84), &po[0].len_V84);
				mySQLBindParameter(hstmt_dre, 90, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V85, 0, &po[0].V85, sizeof(po[0].V85), &po[0].len_V85);
				mySQLBindParameter(hstmt_dre, 91, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V86, 0, &po[0].V86, sizeof(po[0].V86), &po[0].len_V86);
				mySQLBindParameter(hstmt_dre, 92, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V87, 0, &po[0].V87, sizeof(po[0].V87), &po[0].len_V87);
				mySQLBindParameter(hstmt_dre, 93, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V88, 0, &po[0].V88, sizeof(po[0].V88), &po[0].len_V88);
				mySQLBindParameter(hstmt_dre, 94, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V89, 0, &po[0].V89, sizeof(po[0].V89), &po[0].len_V89);
				mySQLBindParameter(hstmt_dre, 95, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V90, 0, &po[0].V90, sizeof(po[0].V90), &po[0].len_V90);
				mySQLBindParameter(hstmt_dre, 96, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V91, 0, &po[0].V91, sizeof(po[0].V91), &po[0].len_V91);
				mySQLBindParameter(hstmt_dre, 97, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V92, 0, &po[0].V92, sizeof(po[0].V92), &po[0].len_V92);
				mySQLBindParameter(hstmt_dre, 98, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V93, 0, &po[0].V93, sizeof(po[0].V93), &po[0].len_V93);
				mySQLBindParameter(hstmt_dre, 99, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V94, 0, &po[0].V94, sizeof(po[0].V94), &po[0].len_V94);
				mySQLBindParameter(hstmt_dre, 100, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V95, 0, &po[0].V95, sizeof(po[0].V95), &po[0].len_V95);
				mySQLBindParameter(hstmt_dre, 101, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, po[0].len_V96, 0, &po[0].V96, sizeof(po[0].V96), &po[0].len_V96);

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

				if (m_iIDStart > m_iIDEnd)
				{
					m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程 m_iIDStart = %2 m_iIDEnd = %3")
						.arg(m_iIDStart)
						.arg(m_iIDEnd);
					throw m_sMsg;
				}

				mySQLPrepare(hstmt_dre, (SQLWCHAR*)statement.unicode(), SQL_NTS);

				/* 外层按照日期递增循环 [2016-3-4 by zzg] */
				for (iCurrDay = 0; CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(iCurrDay) <= CGlobalDataSaver::GetInstance()->m_dtDataEnd; iCurrDay++)
				{
					dtCurrent = CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(iCurrDay);

					for (iCurrMeter = 0; iCurrMeter + m_iMeterIDStart <= m_iMeterIDEnd; iCurrMeter++)
					{
						m_iCurrlLine++;
						m_iIDCurrent = m_iCurrlLine + m_iIDStart - 1;

						po[m_iTickCount].metering_time.year = po[m_iTickCount].data_date.year = dtCurrent.year();
						po[m_iTickCount].metering_time.month = po[m_iTickCount].data_date.month = dtCurrent.month();
						po[m_iTickCount].metering_time.day = po[m_iTickCount].data_date.day = dtCurrent.day();
						po[m_iTickCount].phase[0] = 'A';
						po[m_iTickCount].phase[1] = 0;

						po[m_iTickCount].vol_cur_id = m_iIDCurrent;
						po[m_iTickCount].meter_id = iCurrMeter + m_iMeterIDStart;
						po[m_iTickCount].V10 = po[m_iTickCount].V11 = po[m_iTickCount].V12 = po[m_iTickCount].V13 = po[m_iTickCount].V14 = po[m_iTickCount].V15 = po[m_iTickCount].V16 = po[m_iTickCount].V17 = po[m_iTickCount].V18 = po[m_iTickCount].V19 = po[m_iTickCount].V1 = (rand() % 41) + 200;
						po[m_iTickCount].V20 = po[m_iTickCount].V21 = po[m_iTickCount].V22 = po[m_iTickCount].V23 = po[m_iTickCount].V24 = po[m_iTickCount].V25 = po[m_iTickCount].V26 = po[m_iTickCount].V27 = po[m_iTickCount].V28 = po[m_iTickCount].V29 = po[m_iTickCount].V2 = (rand() % 41) + 200;
						po[m_iTickCount].V30 = po[m_iTickCount].V31 = po[m_iTickCount].V32 = po[m_iTickCount].V33 = po[m_iTickCount].V34 = po[m_iTickCount].V35 = po[m_iTickCount].V36 = po[m_iTickCount].V37 = po[m_iTickCount].V38 = po[m_iTickCount].V39 = po[m_iTickCount].V3 = (rand() % 41) + 200;
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
						po[m_iTickCount].len_phase = SQL_NTS;
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
							m_iCommitedSize = (m_iCurrlLine * (sizeof(crm_mnp_npdb_esvf) + sizeof(SQLUSMALLINT)) / (1024 * 1024));
							if (!CGlobalDataSaver::GetInstance()->m_bDetailLogOff){
								m_sMsg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("第[%1]进程已经写入[%2]行数据，剩余[%3]待写入")
									.arg(m_iProcessID)
									.arg(m_iCommitedLine)
									.arg(m_iIDEnd - m_iIDStart - m_iCurrlLine + 1);
								CGlobalDataSaver::GetInstance()->PrintMsg(m_sMsg);
							}
							//CGlobalDataSaver::GetInstance()->m_pTableOut->item(m_iProcessID - 1, 2)->setText(QString("%1").arg(m_iCurrlLine));
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


