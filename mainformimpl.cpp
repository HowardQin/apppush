#include "mainformimpl.h"
#include <qlineedit.h>
#include <qstringlist.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qfile.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qcheckbox.h>
#include <QMessageBox>
#include "dealVolDataThread.h"
#include "dealENERGYDataThread.h"
#include "dealDayENERGYDataThread.h"
#include "dealMinTableDataThread.h"
#include "ui_mainform.h"

#if defined(Q_OS_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

void mainformImpl::SetDataJS()
{
	LONG64 iIdBase = 100000000000001 ;
	switch (ui->cbDataJS->currentIndex())
	{
	case 0 :
		iIdBase = 100000000000001 ;
		break ;
	case 1:
		iIdBase = 200000000000001 ;
		break ;
	case 2:
		iIdBase = 300000000000001 ;
		break ;
	case 3:
		iIdBase = 400000000000001 ;
		break ;
	case 4:
		iIdBase = 500000000000001 ;
		break ;
	case 5:
		iIdBase = 600000000000001 ;
		break ;
	case 6:
		iIdBase = 700000000000001 ;
		break ;
	case 7:
		iIdBase = 800000000000001 ;
		break ;
	case 8:
		iIdBase = 900000000000001 ;
		break ;
	case 9:
		iIdBase = 110000000000001 ;
		break ;
	case 10:
		iIdBase = 120000000000001 ;
		break ;
	case 11:
		iIdBase = 130000000000001 ;
		break ;
	case 12:
		iIdBase = 140000000000001 ;
		break ;
	case 13:
		iIdBase = 150000000000001 ;
		break ;
	case 14:
		iIdBase = 160000000000001 ;
		break ;
	case 15:
		iIdBase = 170000000000001 ;
		break ;
	case 16:
		iIdBase = 180000000000001 ;
		break ;
	case 17:
		iIdBase = 190000000000001 ;
	}
	CGlobalDataSaver::GetInstance()->m_iDataIDStart = CGlobalDataSaver::GetInstance()->m_iMeterIDStart = iIdBase ;
}

void mainformImpl::SetTableName()
{
	CGlobalDataSaver::GetInstance()->m_iDataTable = ui->cbYLMC->currentIndex();  //这个要想用上就需要设计 DealMainServiceThread 的重载函数，或者在 DealMainServiceThread 中进行判断
	switch (CGlobalDataSaver::GetInstance()->m_iDataTable)
	{
	case 0 : //日测量点电压曲线表
		CGlobalDataSaver::GetInstance()->m_sDataTable = "E_MP_VOL_CURVE_P" ;
		break ;
	case 1 : // 日测量点总电能量曲线表
		CGlobalDataSaver::GetInstance()->m_sDataTable = "E_MP_ENERGY_CURVE_P" ;
		break ;
	case 2 : // 测量点日冻结电能量表
		CGlobalDataSaver::GetInstance()->m_sDataTable = "E_MP_DAY_ENERGY_P" ;
		break ;
	case 3 : //测试用最小化表
		CGlobalDataSaver::GetInstance()->m_sDataTable = "E_MIN_TABLE_P" ;
		break ;
	}
}
void mainformImpl::OnBtnPauseClicked()
{

}

void mainformImpl::OnBtnStopClicked()
{

}

mainformImpl::mainformImpl( QWidget* parent)
	: QWidget(parent), ui (new Ui::mainform)
{
	ui->setupUi(this);
	CGlobalDataSaver::GetInstance()->m_pTxtOut = ui->txtMsg ;
	CGlobalDataSaver::GetInstance()->m_pTableOut = ui->lblFileList;
	CGlobalDataSaver::GetInstance()->m_iDataIDStart = CGlobalDataSaver::GetInstance()->m_iMeterIDStart = 100000000000001 ;
	CGlobalDataSaver::GetInstance()->m_iMeterNumber  = 0 ;
	m_iMax10 = 0;
	m_iLasteInster = 0;
	m_iCounter = 0;
	m_bPause = false ;
	m_pTimer2 = new QTimer(this);

	qApp->connect( m_pTimer2, SIGNAL(timeout()),this, SLOT(OnTimerOut2()) );
	
	ui->txtPass->setFocus();
	ui->leMeterNo->setEnabled(false);
	ui->leDays->setEnabled(false);
	QRegExp regx("[0-9]+$");
	QValidator *validator = new QRegExpValidator(regx, this);
	ui->leMeterNo->setValidator(validator);
	ui->leDays->setValidator(validator);
	ui->version_info->setText(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("ODBC 写入测试 编译时间: %1 %2").arg(__DATE__).arg(__TIME__));
	QFile file("conf.dat");
	if (file.exists())
	{
		file.open(QIODevice::ReadOnly);
		QDataStream in(&file);    // read the data serialized from the file
		QString str;
		in >> str;   // read username
		ui->txtName->setText(str);
		in >> str;        // read password
		ui->txtPass->setText(str);
		in >> str; //read odbc connection name
		ui->txtConnName->setText(str);
	}
}

/*  
 *  Destroys the object and frees any allocated resources
 */
mainformImpl::~mainformImpl()
{
	if (m_pTimer2)
	{
		delete m_pTimer2;
		m_pTimer2 = NULL;
	}
	QFile file("conf.dat");
	file.remove();
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);   // we will serialize the data into the file
	out << ui->txtName->text();   // serialize username
	out << ui->txtPass->text();        // serialize password
	out << ui->txtConnName->text(); //odbc connection name
	delete ui;
}

void mainformImpl::OnTimerOut2()
{
	/* 计算各个任务的进度啥的 [2016-3-6 by zzg] */
	LONG64 iCurrLineSum = 0;
	LONG64 iCurrSizeSum = 0;
	LONG64 iSecPass = 0;
	int iActiveProcess = 0;
	for (int iT = 0; iT < CGlobalDataSaver::GetInstance()->m_lThreads.count(); iT++)
	{
		DealMainServiceThread * pCurrThread = (DealMainServiceThread *)CGlobalDataSaver::GetInstance()->m_lThreads[iT];
		if (pCurrThread == NULL)
			continue;
		if (pCurrThread->m_iProcessID <= 0)
			continue;

		ui->lblFileList->item(iT, 0)->setText(QString::number(pCurrThread->m_iMeterIDStart));
		if (pCurrThread->m_iJobflag == RunState::insert)
		{
			ui->lblFileList->item(iT, 1)->setText(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("进行中"));
			iActiveProcess++;
		}
		else if (pCurrThread->m_iJobflag == RunState::doneInsert)
		{
			ui->lblFileList->item(iT, 1)->setText(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("结束"));
		}
		else
		{
			ui->lblFileList->item(iT, 1)->setText(CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("异常"));
		}
		iCurrLineSum += pCurrThread->m_iCommitedLine;
		iCurrSizeSum += pCurrThread->m_iCommitedSize;
		ui->lblFileList->item(iT, 2)->setText(QString::number(pCurrThread->m_iCommitedLine));
		ui->lblFileList->item(iT, 3)->setText(QString::number(pCurrThread->m_iCommitedSize));
		ui->lblFileList->item(iT, 4)->setText(pCurrThread->m_dtStartJob.toString("yyyy-MM-dd hh:ss:mi"));
	}

	ui->pbJD->setValue(iCurrLineSum);
	ui->txtOUT1->setText(QString::number(iCurrLineSum));
	ui->txtOUT2->setText(QString::number(iCurrSizeSum));

	if (iActiveProcess > 0){
		QDateTime dtCurr = QDateTime::currentDateTime();
		iSecPass = CGlobalDataSaver::GetInstance()->m_dtProcessStart.secsTo(dtCurr);
		ui->txtOUTs->setText(QString::number(iSecPass));
		ui->txtOUT3->setText(QString::number((LONG64)(iCurrLineSum / iSecPass)));
		ui->txtOUT4->setText(QString::number((double)(iCurrSizeSum / iSecPass)));

		int iPassSec = m_dtLasteTime.secsTo(dtCurr);
		if (iPassSec >= 10 * 60/* 十分钟 [2016-3-6 by zzg] */)
		{
			LONG64 iCol10 = (iCurrLineSum - m_iLasteInster) / iPassSec;
			ui->txtOUT5->setText(QString::number(iCol10));
			m_iLasteInster = iCurrLineSum;
			if (iCol10 > m_iMax10)
			{
				m_iMax10 = iCol10;
			}
			m_dtLasteTime = dtCurr;
			ui->txtOUT7->setText(QString::number(m_iMax10));

			/* 写到日志里 [2016-3-6 by zzg] */
			if (iSecPass % 10 == 0)  /* 10 秒钟写一次 [2016-3-6 by zzg] */
			{
				m_msg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("当前进度[%1%],用时[%6]s \r\n合计产生[%2],"
					"占用空间[%3],总平均[%4]条／s，[%5]M／s \r\n"
					"10分钟平均[%7]条／s，10分钟最大[%8]条／s")
					.arg((int)((iCurrLineSum * 100) / CGlobalDataSaver::GetInstance()->m_iTotalLine))
					.arg(QString::number(iCurrLineSum))
					.arg(QString::number(iCurrSizeSum))
					.arg((LONG64)(iCurrLineSum / iSecPass))
					.arg((double)(iCurrSizeSum / iSecPass))
					.arg(QString::number(iSecPass))
					.arg(QString::number(iCol10))
					.arg(QString::number(m_iMax10));
				CGlobalDataSaver::GetInstance()->PrintMsg(m_msg);
			}
		}
    }
	else
	{
		ui->btnStart->setEnabled(true);
		m_pTimer2->stop();
	}
}


void mainformImpl::on_cbMeterNo_toggled()
{
	if (ui->cbMeterNo->isChecked())
	{
		ui->leMeterNo->setEnabled(true);
		ui->cbDataGM->setEnabled(false);
	}
	else
	{
		ui->leMeterNo->setEnabled(false);
		ui->cbDataGM->setEnabled(true);
	}
}

void mainformImpl::on_cbDays_toggled()
{
	if (ui->cbDays->isChecked())
	{
		ui->leDays->setEnabled(true);
		ui->cbDataZQ->setEnabled(false);
	}
	else{
		ui->leDays->setEnabled(false);
		ui->cbDataZQ->setEnabled(true);
	}
}

void mainformImpl::OnBtnStartClicked()
{
	ui->btnStart->setEnabled(false);
	int iProcessNum ;
	CGlobalDataSaver::GetInstance()->m_sDbUserName = ui->txtName->text().simplified();
	CGlobalDataSaver::GetInstance()->m_sDbUserPass = ui->txtPass->text().simplified();
	CGlobalDataSaver::GetInstance()->m_sDbService = ui->txtConnName->text().simplified();
	CGlobalDataSaver::GetInstance()->m_iProcessNUM = iProcessNum = ui->sbConnNum->value();
	CGlobalDataSaver::GetInstance()->m_iDCSL = ui->cbDCSL->currentText().toInt();
	CGlobalDataSaver::GetInstance()->m_iDataGM = ui->cbDataGM->currentIndex();
	CGlobalDataSaver::GetInstance()->m_iDataZQ = ui->cbDataZQ->currentIndex();
	CGlobalDataSaver::GetInstance()->m_bLogOff = ui->logOff->isChecked();
	if (ui->rbInsert->isChecked())
		CGlobalDataSaver::GetInstance()->m_InsertType = InsertType::INSERT_INTO;
	else if (ui->rbUpsert->isChecked())
		CGlobalDataSaver::GetInstance()->m_InsertType = InsertType::UPSERT_INTO;
	else if (ui->rbUpUsing->isChecked())
		CGlobalDataSaver::GetInstance()->m_InsertType = InsertType::UPSERT_USING_LOAD;

	QString infoTitle = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("提示");
	QString msgPositive = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("请输入大于1的值");
	QString msgConv = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("无法转换为整数");

	QString sDBS ;
	if (ui->cbDataGM->isEnabled())
	{
		if (3 == CGlobalDataSaver::GetInstance()->m_iDataGM)
		{
			CGlobalDataSaver::GetInstance()->m_iMeterNumber = 1000;
			sDBS = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("DX（1000电表）");
		}
		if (4 == CGlobalDataSaver::GetInstance()->m_iDataGM)
		{
			CGlobalDataSaver::GetInstance()->m_iMeterNumber = 10000;
			sDBS = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("DX（1万电表）");
		}
		else if (0 == CGlobalDataSaver::GetInstance()->m_iDataGM)
		{
			/* 数据规模 D1 ，电表中有200 万电表 [2016-3-4 by zzg] */
			CGlobalDataSaver::GetInstance()->m_iMeterNumber = 2080000;
			sDBS = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("D1（200万电表）");
		}
		else if (1 == CGlobalDataSaver::GetInstance()->m_iDataGM)
		{
			CGlobalDataSaver::GetInstance()->m_iMeterNumber = 20800000;
			sDBS = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("D2（2000万电表）");
		}
		else if (2 == CGlobalDataSaver::GetInstance()->m_iDataGM)
		{
			CGlobalDataSaver::GetInstance()->m_iMeterNumber = 100;
			sDBS = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("Dx（100电表）");
		}
	}
	else
	{
		bool ok;
		int meters = ui->leMeterNo->text().toInt(&ok, 10);
		CGlobalDataSaver::GetInstance()->m_iMeterNumber = meters;
		if (ok == false){
			QMessageBox::information(this, infoTitle, msgConv);
			return;
		}
		if (meters < 1)
		{
			QMessageBox::information(this, infoTitle, msgPositive);
			ui->btnStart->setEnabled(true);
			return;
		}
		sDBS = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode(QString("%1 电表").arg(meters).toLatin1());
	}
	QString sSJZ ;
	CGlobalDataSaver::GetInstance()->m_dtDataStart = QDate(2015, 1, 1);
	if (ui->cbDataZQ->isEnabled())
	{
		if (3 == CGlobalDataSaver::GetInstance()->m_iDataZQ)
		{
			/* 数据周期为  1年（2015-01-01 ～ 2015-12-31） [2016-3-4 by zzg] */
			CGlobalDataSaver::GetInstance()->m_dtDataEnd = QDate(2015, 12, 31);
			sSJZ = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("1年（2015-01-01 ～ 2015-12-31）");
		}
		else if (4 == CGlobalDataSaver::GetInstance()->m_iDataZQ)
		{
			CGlobalDataSaver::GetInstance()->m_dtDataEnd = QDate(2021, 12, 31);
			sSJZ = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("7年（2015-01-01 ～ 2021-12-31）");
		}
		else if (0 == CGlobalDataSaver::GetInstance()->m_iDataZQ)
		{
			CGlobalDataSaver::GetInstance()->m_dtDataEnd = QDate(2015, 1, 2);
			sSJZ = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("2天（2015-01-01 ～ 2015-01-02）");
		}
		else if (1 == CGlobalDataSaver::GetInstance()->m_iDataZQ)
		{
			CGlobalDataSaver::GetInstance()->m_dtDataEnd = QDate(2015, 1, 10);
			sSJZ = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("10天（2015-01-01 ～ 2015-01-10）");
		}
		else if (2 == CGlobalDataSaver::GetInstance()->m_iDataZQ)
		{
			CGlobalDataSaver::GetInstance()->m_dtDataEnd = QDate(2015, 2, 1);
			sSJZ = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("1个月（2015-01-01 ～ 2015-02-01）");
		}
	}
	else
	{
		bool ok;
		int days = ui->leDays->text().toInt(&ok, 10);
		if (ok == false){
			QMessageBox::information(this, infoTitle, msgConv);
			ui->btnStart->setEnabled(true);
			return;
		}
		if (days < 1)
		{
			QMessageBox::information(this, infoTitle, msgPositive);
			ui->btnStart->setEnabled(true);
			return;
		}
		CGlobalDataSaver::GetInstance()->m_dtDataEnd = CGlobalDataSaver::GetInstance()->m_dtDataStart.addDays(days-1);
		sSJZ = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode(QString("%1 天").arg(days).toLatin1());
	}
	/* start [2016-3-6 by zzg] */
	/* ID 基数， [2016-3-6 by zzg] */
	SetDataJS();
	SetTableName();
	/* end [2016-3-6 by zzg] */

	/* 计算出总日期数 [2016-3-4 by zzg] */
	LONG64 iDaySum = 0;
	iDaySum = CGlobalDataSaver::GetInstance()->m_dtDataStart.daysTo(CGlobalDataSaver::GetInstance()->m_dtDataEnd) + 1 ;
	/* 计算出总记录数 [2016-3-4 by zzg] */
	CGlobalDataSaver::GetInstance()->m_iTotalLine = iDaySum * CGlobalDataSaver::GetInstance()->m_iMeterNumber ;

	m_msg = CGlobalDataSaver::GetInstance()->m_pTextCode->toUnicode("正在准备数据库导入…… \r\n 并发连接数[%1]，单次提交数量[%2]，数据规模[%3]，"
		"执行前清空数据表？[%4]，数据周期[%5]，存入目标[%6],总数据量[%7]")
		.arg(CGlobalDataSaver::GetInstance()->m_iProcessNUM)
		.arg(CGlobalDataSaver::GetInstance()->m_iDCSL)
		.arg(sDBS)
		.arg(CGlobalDataSaver::GetInstance()->m_bCleanTable)
		.arg(sSJZ)
		.arg(CGlobalDataSaver::GetInstance()->m_sDataTable)
		.arg(QString::number(CGlobalDataSaver::GetInstance()->m_iTotalLine) );
	CGlobalDataSaver::GetInstance()->PrintMsg(m_msg);

	ui->txtOUT1->setText("0");
	ui->txtOUT2->setText("0");
	ui->txtOUTt->setText(QString::number(CGlobalDataSaver::GetInstance()->m_iTotalLine));
	/* 根据设置的线程数初始化各个线程
	计算每个线程的MeterID范围 [2016-3-4 by zzg] */

	LONG64 iMeterNUMPerProcess = 0 ;  //每个线程中的电表ID数量
	LONG64 iMeterIDStartCurr = 0 ; 
	LONG64 iLineTotalUsed = 0 ;
	LONG64 iLineCurrProcessUsed = 0 ;
	iMeterNUMPerProcess = (LONG64)(CGlobalDataSaver::GetInstance()->m_iMeterNumber / iProcessNum);

	ui->lblFileList->setRowCount(iProcessNum);

	CGlobalDataSaver::GetInstance()->m_lThreads.clear();

	ui->pbJD->setMaximum(CGlobalDataSaver::GetInstance()->m_iTotalLine);
	iMeterIDStartCurr = CGlobalDataSaver::GetInstance()->m_iMeterIDStart;

	CGlobalDataSaver::GetInstance()->m_dtProcessStart = QDateTime::currentDateTime();
	m_dtLasteTime = CGlobalDataSaver::GetInstance()->m_dtProcessStart; 
	m_iLasteInster = 0 ;
	for (int iT = 0 ; iT < iProcessNum ; iT++)
	{
		DealMainServiceThread * pCurrThread = NULL ;
		if (0 == CGlobalDataSaver::GetInstance()->m_iDataTable)
		{
			pCurrThread = (DealMainServiceThread * )new DealVolDataThread();
		}
		else if (1 == CGlobalDataSaver::GetInstance()->m_iDataTable)
		{
			pCurrThread = (DealMainServiceThread * )new DealENERGYDataThread();
		}
		else if (2 == CGlobalDataSaver::GetInstance()->m_iDataTable)
		{
			pCurrThread = (DealMainServiceThread * )new DealDayENERGYDataThread();
		}
		else if (3 == CGlobalDataSaver::GetInstance()->m_iDataTable)
		{
			pCurrThread = (DealMainServiceThread * )new DealMinTableDataThread();
		}
		else
		{
			return;
		}

		pCurrThread->m_iProcessID = iT + 1;

 	    pCurrThread->m_iJobflag = RunState::insert;

		pCurrThread->m_iMeterIDStart = iMeterIDStartCurr;
	
		if (iT == iProcessNum - 1)
		{
			pCurrThread->m_iMeterIDEnd = CGlobalDataSaver::GetInstance()->m_iMeterIDStart + CGlobalDataSaver::GetInstance()->m_iMeterNumber -1;
			iMeterNUMPerProcess = pCurrThread->m_iMeterIDEnd - iMeterIDStartCurr + 1  ;
		}	
		pCurrThread->m_iMeterIDEnd = iMeterIDStartCurr + iMeterNUMPerProcess - 1;
		iMeterIDStartCurr += iMeterNUMPerProcess ;
		iLineCurrProcessUsed = iMeterNUMPerProcess * iDaySum ;  //每个线程中的总记录数
		
		pCurrThread->m_iTotalLine = iLineCurrProcessUsed ;
		pCurrThread->m_iIDStart = CGlobalDataSaver::GetInstance()->m_iDataIDStart + iLineTotalUsed ;
		pCurrThread->m_iIDEnd = pCurrThread->m_iIDStart + iLineCurrProcessUsed -1 ;
		iLineTotalUsed += iLineCurrProcessUsed ;
	
		CGlobalDataSaver::GetInstance()->m_lThreads[iT] = pCurrThread ;

		/* 写到table 里 [2016-3-4 by zzg] */
		ui->lblFileList->setItem(iT, 0, new QTableWidgetItem(QString::number(pCurrThread->m_iIDStart)));
		ui->lblFileList->setItem(iT, 1, new QTableWidgetItem(""));
		ui->lblFileList->setItem(iT, 2, new QTableWidgetItem(""));
		ui->lblFileList->setItem(iT, 3, new QTableWidgetItem(""));
		ui->lblFileList->setItem(iT, 4, new QTableWidgetItem(""));
		pCurrThread->start();

#ifdef Q_OS_WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}//for
	m_pTimer2->start(800);
}
