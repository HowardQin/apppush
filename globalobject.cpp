#include "globalobject.h"
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlibrary.h>
//Added by qt3to4:
//#include <Q3TextStream>
#include "dealMainServiceThread.h"
#include <QTextEdit>
#include <QTableWidget>
#if defined(Q_OS_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <QPushButton>

CGlobalDataSaver * CGlobalDataSaver::m_pGlobal;
int CGlobalDataSaver::m_iNeedReboot = 0 ;
void* CGlobalDataSaver::m_pManagedPoint = NULL ;
QMutex CGlobalDataSaver::m_mutexWriteRunLog ;
QTextEdit * CGlobalDataSaver::m_pTxtOut = NULL ;
QTableWidget *CGlobalDataSaver::m_pTableOut = NULL;
QStringList CGlobalDataSaver::m_lMsgs ;
QTextCodec * CGlobalDataSaver::m_pTextCode = QTextCodec::codecForName("GBK");

CGlobalDataSaver::~CGlobalDataSaver()
{

};

CGlobalDataSaver::CGlobalDataSaver()
{
	m_pGlobal = NULL;
	m_pTextCode = NULL;	
	m_pTextCode = QTextCodec::codecForName("GBK");
	m_pTxtOut = NULL;
	m_sDbUserName = ""    ;
	m_sDbUserPass = ""    ;
	m_sDbService  = ""    ;
	m_bCloseMainWindow = false ;
};


CGlobalDataSaver * CGlobalDataSaver::GetInstance()
{
	if( NULL == m_pGlobal)
	{
		m_pGlobal = new CGlobalDataSaver ;
	}
	return m_pGlobal ;	
}

const char* CGlobalDataSaver::GetInsertString()
{
	switch (CGlobalDataSaver::GetInstance()->m_InsertType)
	{
	    case InsertType::INSERT_INTO :
			return "INSERT";
		case InsertType::UPSERT_INTO:
			return "UPSERT";
		case InsertType::UPSERT_USING_LOAD:
			return "UPSERT USING LOAD";
		default:
			Q_ASSERT(0);
			return "";
	}
	return "";
}

void CGlobalDataSaver::PrintMsg(const QString & sMsg)
{
	if (m_bAllLogOff)
		return;
	QMutexLocker locker(&m_mutexWriteRunLog);
	QString sBuf;
	char FileName[255];
	QDateTime time = QDateTime::currentDateTime();
	sBuf.sprintf("[%04d-%02d-%02d %02d:%02d:%02d.%03d] : ",
		time.date().year(), time.date().month(), time.date().day(),
		time.time().hour(), time.time().minute(), time.time().second(), time.time().msec());
	sprintf(FileName, "app_%04d-%02d-%02d.log", time.date().year(), time.date().month(), time.date().day());
	QFile file(FileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		QTextStream stream(&file);
		//stream.setEncoding(QTextStream::Latin1);
		stream << sBuf + sMsg + "\r\n";
		file.close();
	}
};