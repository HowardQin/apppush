#ifndef MAINFORMIMPL_H
#define MAINFORMIMPL_H
#include "globalobject.h"
#include <qtimer.h>

namespace Ui
{
	class mainform;
}

class mainformImpl : public QWidget
{
    Q_OBJECT

public:
    mainformImpl( QWidget* parent = 0);
    ~mainformImpl();
	Ui::mainform * ui;

public slots:
	virtual void OnTimerOut2();
	virtual void OnBtnStartClicked();
    virtual void OnBtnPauseClicked();
    virtual void OnBtnStopClicked();
	void on_cbMeterNo_toggled();
	void on_cbDays_toggled();


private:
	void SetTableName();
	void SetDataJS();
private:
	bool    m_bPause;
	QTime   m_timeCheck ;
	QTimer * m_pTimer2;
	int      m_iCounter ; //循环次数计数
	uint     m_iMsgPos  ;
	QStringList m_MsgList ;
	QString m_msg ;
	LONG64		m_iLasteInster ; /* 十分钟统计用 [2016-3-6 by zzg] */
	LONG64		m_iMax10 ; 
	QDateTime	m_dtLasteTime  ;
};

#endif // MAINFORMIMPL_H
