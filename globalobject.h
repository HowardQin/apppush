#ifndef HEADERS_H_2008_01_01
#define HEADERS_H_2008_01_01

#include <QtGui>
#include <QLabel>
#include <QTextEdit>
#include <QTableWidget>
//#include <BASETSD.H>  //处理 64 位整数

#define INT_LEVEL_IMPORTMENTMSG 9  /* 重要消息 2011/07/14 by zzg */
#define INT_LEVEL_NORMALMSG     6  /* 次要消息 2011/07/14 by zzg */
#define INT_LEVEL_LOWLEVELMSG   3  /* 普通消息 2011/07/14 by zzg */
#define INT_LEVEL_DEBUGMSG      1  /* 调试消息 2011/07/14 by zzg */
#define INT_LEVEL_TESTMSG       0  /* 测试消息 2011/07/14 by zzg */

#define SQLTIMEFORMAT		"YYYY-MM-DD HH24:MI:SS"

#define QT_DRIVERNAME_ORACLE QString("QOCI8")
#define QT_DRIVERNAME_MYSQL  QString("QMYSQL3")

#define STATE_PURGE   5
#define STATE_INSERT   0
#define STATE_EXCEPT   9
#define STATE_DONE_PURGE    6
#define STATE_DONE_INERT     1

enum RunState{
	insert,
	doneInsert,
	except
};

enum InsertType{
	INSERT_INTO,
	UPSERT_INTO,
	UPSERT_USING_LOAD,
};
/*!
\brief 保存全局变量的类  
*/
class CGlobalDataSaver : public QObject
{
public:
	static CGlobalDataSaver * GetInstance();
public :
	CGlobalDataSaver();
	~CGlobalDataSaver();
	//INSERT, UPSERT, UPSERT USING LOAD
	const char* GetInsertString();
	//logging
	void PrintMsg(const QString & sMsg);

public:
	QString m_sDbUserName    ;
	QString m_sDbUserPass    ;
	QString m_sDbService     ;
	int     m_iProcessNUM    ;
    bool    m_bCleanTable    ;
	bool   m_bAllLogOff;
	bool   m_bDetailLogOff;
	int m_retryCount;
	int     m_iDCSL          ;
	int     m_iDataGM        ;
	int     m_iDataZQ        ;
	QString m_sDataTable	 ;
	LONG64    m_iTotalLine     ;
	LONG64    m_iCurrentLine   ;

	LONG64  m_iMeterNumber      ;
	LONG64  m_iMeterIDStart     ;
	LONG64  m_iDataIDStart     ;
	InsertType m_InsertType;

	QDate m_dtDataStart  ;
	QDate m_dtDataEnd    ;

	QDateTime m_dtProcessStart ;

	QMap <int,QThread *> m_lThreads ;

	static QTextCodec * m_pTextCode ;
	static QTextEdit * m_pTxtOut    ;
	static QTableWidget * m_pTableOut    ;

	QString m_sMAC ;
	QString m_sCustomerID    ;

	QString m_sIPAddress     ;
	QLabel * m_pLblAlarmStatus   ;		/* 告警状态提示，位于主界面 2011/07/19 by zzg */

	int     m_iTimeTurnBaseStep ;       /*  时间循环基本步长，单位为秒，计算方法为 程序设置步长 * 基础步长 [2012-10-24 by zzg] */
	int m_connTimeOut;
	static QStringList m_lMsgs ;

	bool  m_bCloseMainWindow ;

	static int m_iNeedReboot ;   /* 重启标志 [2012-9-14 by zzg] */
	static void* m_pManagedPoint ;
private:
	static CGlobalDataSaver * m_pGlobal ;
/* 互斥锁 2011/07/14 by zzg */
private:
	QMutex m_mutexRandom;
	QMutex m_mutexPrintMsg;
	static QMutex m_mutexWriteRunLog;
	QMutex m_mutexPageOut ;
};

#endif //HEADERS_H_2008_01_01
