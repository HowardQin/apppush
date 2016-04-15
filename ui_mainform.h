/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainform
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1_2_5_3_2;
    QComboBox *cbDataJS;
    QCheckBox *usingInputId;
    QLineEdit *idBaseInput;
    QSpacerItem *spacer2_2;
    QLabel *version_info;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabel1_2_4;
    QLabel *textLabel1_2;
    QLineEdit *txtName;
    QLabel *textLabel1_2_2;
    QLineEdit *txtPass;
    QLabel *textLabel1_2_3;
    QLineEdit *txtConnName;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabel1_2_4_2;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabel1_2_5;
    QSpinBox *sbConnNum;
    QLabel *textLabel1_2_5_2_2;
    QComboBox *cbDCSL;
    QCheckBox *allLogOff;
    QCheckBox *detailLogOff;
    QCheckBox *emptyTable;
    QLabel *label_5;
    QSpinBox *retryCount;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabel1_2_5_3;
    QComboBox *cbDataGM;
    QCheckBox *cbMeterNo;
    QLineEdit *leMeterNo;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *hboxLayout6;
    QLabel *textLabel1_2_5_2;
    QComboBox *cbDataZQ;
    QCheckBox *cbDays;
    QLineEdit *leDays;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *hboxLayout7;
    QLabel *textLabel1_2_5_2_3;
    QComboBox *cbYLMC;
    QRadioButton *rbInsert;
    QRadioButton *rbUpsert;
    QRadioButton *rbUpUsing;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *spacer2_2_2;
    QVBoxLayout *vboxLayout3;
    QPushButton *btnStart;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QHBoxLayout *hboxLayout8;
    QLabel *textLabel1_2_4_2_2;
    QLabel *txtOUT1;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QLabel *textLabel1_2_4_2_2_2;
    QLabel *txtOUT2;
    QLabel *textLabel1_2_4_2_2_2_2;
    QSpacerItem *horizontalSpacer_7;
    QLabel *textLabel1_2_4_2_2_3_4;
    QLabel *txtOUTt;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *hboxLayout9;
    QLabel *textLabel1_2_4_2_2_3;
    QLabel *txtOUT3;
    QLabel *textLabel1_2_4_2_2_2_3;
    QLabel *txtOUT4;
    QLabel *textLabel1_2_4_2_2_2_2_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *textLabel1_2_4_2_2_3_2;
    QLabel *txtOUTs;
    QLabel *textLabel1_2_4_2_2_2_3_2;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *hboxLayout10;
    QLabel *textLabel1_2_4_2_2_3_3;
    QLabel *txtOUT5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *textLabel1_2_4_2_2_2_3_3;
    QLabel *txtOUT7;
    QLabel *textLabel1_2_4_2_2_2_3_3_2;
    QSpacerItem *horizontalSpacer_11;
    QProgressBar *pbJD;
    QHBoxLayout *horizontalLayout;
    QTableWidget *lblFileList;

    void setupUi(QWidget *mainform)
    {
        if (mainform->objectName().isEmpty())
            mainform->setObjectName(QStringLiteral("mainform"));
        mainform->resize(835, 490);
        vboxLayout = new QVBoxLayout(mainform);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        textLabel1_2_5_3_2 = new QLabel(mainform);
        textLabel1_2_5_3_2->setObjectName(QStringLiteral("textLabel1_2_5_3_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textLabel1_2_5_3_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_5_3_2->setSizePolicy(sizePolicy);
        textLabel1_2_5_3_2->setWordWrap(false);

        hboxLayout->addWidget(textLabel1_2_5_3_2);

        cbDataJS = new QComboBox(mainform);
        cbDataJS->setObjectName(QStringLiteral("cbDataJS"));

        hboxLayout->addWidget(cbDataJS);

        usingInputId = new QCheckBox(mainform);
        usingInputId->setObjectName(QStringLiteral("usingInputId"));

        hboxLayout->addWidget(usingInputId);

        idBaseInput = new QLineEdit(mainform);
        idBaseInput->setObjectName(QStringLiteral("idBaseInput"));
        idBaseInput->setEnabled(false);

        hboxLayout->addWidget(idBaseInput);

        spacer2_2 = new QSpacerItem(190, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacer2_2);

        version_info = new QLabel(mainform);
        version_info->setObjectName(QStringLiteral("version_info"));
        sizePolicy.setHeightForWidth(version_info->sizePolicy().hasHeightForWidth());
        version_info->setSizePolicy(sizePolicy);
        version_info->setWordWrap(false);

        hboxLayout->addWidget(version_info);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        textLabel1_2_4 = new QLabel(mainform);
        textLabel1_2_4->setObjectName(QStringLiteral("textLabel1_2_4"));
        sizePolicy.setHeightForWidth(textLabel1_2_4->sizePolicy().hasHeightForWidth());
        textLabel1_2_4->setSizePolicy(sizePolicy);
        textLabel1_2_4->setWordWrap(false);

        hboxLayout2->addWidget(textLabel1_2_4);

        textLabel1_2 = new QLabel(mainform);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        sizePolicy.setHeightForWidth(textLabel1_2->sizePolicy().hasHeightForWidth());
        textLabel1_2->setSizePolicy(sizePolicy);
        textLabel1_2->setWordWrap(false);

        hboxLayout2->addWidget(textLabel1_2);

        txtName = new QLineEdit(mainform);
        txtName->setObjectName(QStringLiteral("txtName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtName->sizePolicy().hasHeightForWidth());
        txtName->setSizePolicy(sizePolicy1);
        txtName->setMaximumSize(QSize(32767, 32767));

        hboxLayout2->addWidget(txtName);

        textLabel1_2_2 = new QLabel(mainform);
        textLabel1_2_2->setObjectName(QStringLiteral("textLabel1_2_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_2->setSizePolicy(sizePolicy);
        textLabel1_2_2->setWordWrap(false);

        hboxLayout2->addWidget(textLabel1_2_2);

        txtPass = new QLineEdit(mainform);
        txtPass->setObjectName(QStringLiteral("txtPass"));
        sizePolicy1.setHeightForWidth(txtPass->sizePolicy().hasHeightForWidth());
        txtPass->setSizePolicy(sizePolicy1);
        txtPass->setMaximumSize(QSize(32767, 32767));
        txtPass->setEchoMode(QLineEdit::Password);

        hboxLayout2->addWidget(txtPass);

        textLabel1_2_3 = new QLabel(mainform);
        textLabel1_2_3->setObjectName(QStringLiteral("textLabel1_2_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_3->setSizePolicy(sizePolicy);
        textLabel1_2_3->setWordWrap(false);

        hboxLayout2->addWidget(textLabel1_2_3);

        txtConnName = new QLineEdit(mainform);
        txtConnName->setObjectName(QStringLiteral("txtConnName"));
        sizePolicy1.setHeightForWidth(txtConnName->sizePolicy().hasHeightForWidth());
        txtConnName->setSizePolicy(sizePolicy1);
        txtConnName->setMaximumSize(QSize(32767, 32767));

        hboxLayout2->addWidget(txtConnName);


        vboxLayout1->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        textLabel1_2_4_2 = new QLabel(mainform);
        textLabel1_2_4_2->setObjectName(QStringLiteral("textLabel1_2_4_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2->setWordWrap(false);

        hboxLayout3->addWidget(textLabel1_2_4_2);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QStringLiteral("hboxLayout4"));
        textLabel1_2_5 = new QLabel(mainform);
        textLabel1_2_5->setObjectName(QStringLiteral("textLabel1_2_5"));
        sizePolicy.setHeightForWidth(textLabel1_2_5->sizePolicy().hasHeightForWidth());
        textLabel1_2_5->setSizePolicy(sizePolicy);
        textLabel1_2_5->setWordWrap(false);

        hboxLayout4->addWidget(textLabel1_2_5);

        sbConnNum = new QSpinBox(mainform);
        sbConnNum->setObjectName(QStringLiteral("sbConnNum"));
        sizePolicy.setHeightForWidth(sbConnNum->sizePolicy().hasHeightForWidth());
        sbConnNum->setSizePolicy(sizePolicy);
        sbConnNum->setMinimum(1);
        sbConnNum->setMaximum(1000000);

        hboxLayout4->addWidget(sbConnNum);

        textLabel1_2_5_2_2 = new QLabel(mainform);
        textLabel1_2_5_2_2->setObjectName(QStringLiteral("textLabel1_2_5_2_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_5_2_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_5_2_2->setSizePolicy(sizePolicy);
        textLabel1_2_5_2_2->setWordWrap(false);

        hboxLayout4->addWidget(textLabel1_2_5_2_2);

        cbDCSL = new QComboBox(mainform);
        cbDCSL->setObjectName(QStringLiteral("cbDCSL"));

        hboxLayout4->addWidget(cbDCSL);

        allLogOff = new QCheckBox(mainform);
        allLogOff->setObjectName(QStringLiteral("allLogOff"));

        hboxLayout4->addWidget(allLogOff);

        detailLogOff = new QCheckBox(mainform);
        detailLogOff->setObjectName(QStringLiteral("detailLogOff"));
        detailLogOff->setChecked(true);

        hboxLayout4->addWidget(detailLogOff);

        emptyTable = new QCheckBox(mainform);
        emptyTable->setObjectName(QStringLiteral("emptyTable"));

        hboxLayout4->addWidget(emptyTable);

        label_5 = new QLabel(mainform);
        label_5->setObjectName(QStringLiteral("label_5"));

        hboxLayout4->addWidget(label_5);

        retryCount = new QSpinBox(mainform);
        retryCount->setObjectName(QStringLiteral("retryCount"));
        retryCount->setValue(5);

        hboxLayout4->addWidget(retryCount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(horizontalSpacer);


        vboxLayout2->addLayout(hboxLayout4);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QStringLiteral("hboxLayout5"));
        textLabel1_2_5_3 = new QLabel(mainform);
        textLabel1_2_5_3->setObjectName(QStringLiteral("textLabel1_2_5_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_5_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_5_3->setSizePolicy(sizePolicy);
        textLabel1_2_5_3->setWordWrap(false);

        hboxLayout5->addWidget(textLabel1_2_5_3);

        cbDataGM = new QComboBox(mainform);
        cbDataGM->setObjectName(QStringLiteral("cbDataGM"));

        hboxLayout5->addWidget(cbDataGM);

        cbMeterNo = new QCheckBox(mainform);
        cbMeterNo->setObjectName(QStringLiteral("cbMeterNo"));

        hboxLayout5->addWidget(cbMeterNo);

        leMeterNo = new QLineEdit(mainform);
        leMeterNo->setObjectName(QStringLiteral("leMeterNo"));

        hboxLayout5->addWidget(leMeterNo);

        label_3 = new QLabel(mainform);
        label_3->setObjectName(QStringLiteral("label_3"));

        hboxLayout5->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(horizontalSpacer_2);


        vboxLayout2->addLayout(hboxLayout5);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QStringLiteral("hboxLayout6"));
        textLabel1_2_5_2 = new QLabel(mainform);
        textLabel1_2_5_2->setObjectName(QStringLiteral("textLabel1_2_5_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_5_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_5_2->setSizePolicy(sizePolicy);
        textLabel1_2_5_2->setWordWrap(false);

        hboxLayout6->addWidget(textLabel1_2_5_2);

        cbDataZQ = new QComboBox(mainform);
        cbDataZQ->setObjectName(QStringLiteral("cbDataZQ"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cbDataZQ->sizePolicy().hasHeightForWidth());
        cbDataZQ->setSizePolicy(sizePolicy2);
        cbDataZQ->setMinimumSize(QSize(0, 0));

        hboxLayout6->addWidget(cbDataZQ);

        cbDays = new QCheckBox(mainform);
        cbDays->setObjectName(QStringLiteral("cbDays"));

        hboxLayout6->addWidget(cbDays);

        leDays = new QLineEdit(mainform);
        leDays->setObjectName(QStringLiteral("leDays"));

        hboxLayout6->addWidget(leDays);

        label_4 = new QLabel(mainform);
        label_4->setObjectName(QStringLiteral("label_4"));

        hboxLayout6->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout6->addItem(horizontalSpacer_3);


        vboxLayout2->addLayout(hboxLayout6);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QStringLiteral("hboxLayout7"));
        textLabel1_2_5_2_3 = new QLabel(mainform);
        textLabel1_2_5_2_3->setObjectName(QStringLiteral("textLabel1_2_5_2_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_5_2_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_5_2_3->setSizePolicy(sizePolicy);
        textLabel1_2_5_2_3->setWordWrap(false);

        hboxLayout7->addWidget(textLabel1_2_5_2_3);

        cbYLMC = new QComboBox(mainform);
        cbYLMC->setObjectName(QStringLiteral("cbYLMC"));
        cbYLMC->setEnabled(true);

        hboxLayout7->addWidget(cbYLMC);

        rbInsert = new QRadioButton(mainform);
        rbInsert->setObjectName(QStringLiteral("rbInsert"));
        rbInsert->setChecked(true);

        hboxLayout7->addWidget(rbInsert);

        rbUpsert = new QRadioButton(mainform);
        rbUpsert->setObjectName(QStringLiteral("rbUpsert"));

        hboxLayout7->addWidget(rbUpsert);

        rbUpUsing = new QRadioButton(mainform);
        rbUpUsing->setObjectName(QStringLiteral("rbUpUsing"));

        hboxLayout7->addWidget(rbUpUsing);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout7->addItem(horizontalSpacer_4);


        vboxLayout2->addLayout(hboxLayout7);


        hboxLayout3->addLayout(vboxLayout2);

        spacer2_2_2 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacer2_2_2);


        vboxLayout1->addLayout(hboxLayout3);


        hboxLayout1->addLayout(vboxLayout1);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QStringLiteral("vboxLayout3"));
        btnStart = new QPushButton(mainform);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        sizePolicy.setHeightForWidth(btnStart->sizePolicy().hasHeightForWidth());
        btnStart->setSizePolicy(sizePolicy);
        btnStart->setMinimumSize(QSize(40, 23));
        btnStart->setMaximumSize(QSize(40, 23));

        vboxLayout3->addWidget(btnStart);

        btnPause = new QPushButton(mainform);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        btnPause->setEnabled(false);
        sizePolicy.setHeightForWidth(btnPause->sizePolicy().hasHeightForWidth());
        btnPause->setSizePolicy(sizePolicy);
        btnPause->setMinimumSize(QSize(40, 23));
        btnPause->setMaximumSize(QSize(40, 23));

        vboxLayout3->addWidget(btnPause);

        btnStop = new QPushButton(mainform);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setEnabled(false);
        sizePolicy.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
        btnStop->setSizePolicy(sizePolicy);
        btnStop->setMinimumSize(QSize(40, 23));
        btnStop->setMaximumSize(QSize(40, 23));

        vboxLayout3->addWidget(btnStop);


        hboxLayout1->addLayout(vboxLayout3);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QStringLiteral("hboxLayout8"));
        textLabel1_2_4_2_2 = new QLabel(mainform);
        textLabel1_2_4_2_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2->setWordWrap(false);

        hboxLayout8->addWidget(textLabel1_2_4_2_2);

        txtOUT1 = new QLabel(mainform);
        txtOUT1->setObjectName(QStringLiteral("txtOUT1"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(txtOUT1->sizePolicy().hasHeightForWidth());
        txtOUT1->setSizePolicy(sizePolicy3);
        txtOUT1->setWordWrap(false);

        hboxLayout8->addWidget(txtOUT1);

        label = new QLabel(mainform);
        label->setObjectName(QStringLiteral("label"));

        hboxLayout8->addWidget(label);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(horizontalSpacer_6);

        textLabel1_2_4_2_2_2 = new QLabel(mainform);
        textLabel1_2_4_2_2_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2->setWordWrap(false);

        hboxLayout8->addWidget(textLabel1_2_4_2_2_2);

        txtOUT2 = new QLabel(mainform);
        txtOUT2->setObjectName(QStringLiteral("txtOUT2"));
        sizePolicy3.setHeightForWidth(txtOUT2->sizePolicy().hasHeightForWidth());
        txtOUT2->setSizePolicy(sizePolicy3);
        txtOUT2->setWordWrap(false);

        hboxLayout8->addWidget(txtOUT2);

        textLabel1_2_4_2_2_2_2 = new QLabel(mainform);
        textLabel1_2_4_2_2_2_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2_2->setWordWrap(false);

        hboxLayout8->addWidget(textLabel1_2_4_2_2_2_2);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(horizontalSpacer_7);

        textLabel1_2_4_2_2_3_4 = new QLabel(mainform);
        textLabel1_2_4_2_2_3_4->setObjectName(QStringLiteral("textLabel1_2_4_2_2_3_4"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_3_4->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_3_4->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_3_4->setWordWrap(false);

        hboxLayout8->addWidget(textLabel1_2_4_2_2_3_4);

        txtOUTt = new QLabel(mainform);
        txtOUTt->setObjectName(QStringLiteral("txtOUTt"));
        sizePolicy3.setHeightForWidth(txtOUTt->sizePolicy().hasHeightForWidth());
        txtOUTt->setSizePolicy(sizePolicy3);
        txtOUTt->setWordWrap(false);

        hboxLayout8->addWidget(txtOUTt);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout8->addItem(horizontalSpacer_9);


        vboxLayout->addLayout(hboxLayout8);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QStringLiteral("hboxLayout9"));
        textLabel1_2_4_2_2_3 = new QLabel(mainform);
        textLabel1_2_4_2_2_3->setObjectName(QStringLiteral("textLabel1_2_4_2_2_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_3->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_3->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1_2_4_2_2_3);

        txtOUT3 = new QLabel(mainform);
        txtOUT3->setObjectName(QStringLiteral("txtOUT3"));
        sizePolicy3.setHeightForWidth(txtOUT3->sizePolicy().hasHeightForWidth());
        txtOUT3->setSizePolicy(sizePolicy3);
        txtOUT3->setWordWrap(false);

        hboxLayout9->addWidget(txtOUT3);

        textLabel1_2_4_2_2_2_3 = new QLabel(mainform);
        textLabel1_2_4_2_2_2_3->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2_3->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2_3->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1_2_4_2_2_2_3);

        txtOUT4 = new QLabel(mainform);
        txtOUT4->setObjectName(QStringLiteral("txtOUT4"));
        sizePolicy3.setHeightForWidth(txtOUT4->sizePolicy().hasHeightForWidth());
        txtOUT4->setSizePolicy(sizePolicy3);
        txtOUT4->setWordWrap(false);

        hboxLayout9->addWidget(txtOUT4);

        textLabel1_2_4_2_2_2_2_2 = new QLabel(mainform);
        textLabel1_2_4_2_2_2_2_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2_2_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2_2_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2_2_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2_2_2->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1_2_4_2_2_2_2_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout9->addItem(horizontalSpacer_5);

        textLabel1_2_4_2_2_3_2 = new QLabel(mainform);
        textLabel1_2_4_2_2_3_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2_3_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_3_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_3_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_3_2->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1_2_4_2_2_3_2);

        txtOUTs = new QLabel(mainform);
        txtOUTs->setObjectName(QStringLiteral("txtOUTs"));
        sizePolicy3.setHeightForWidth(txtOUTs->sizePolicy().hasHeightForWidth());
        txtOUTs->setSizePolicy(sizePolicy3);
        txtOUTs->setWordWrap(false);

        hboxLayout9->addWidget(txtOUTs);

        textLabel1_2_4_2_2_2_3_2 = new QLabel(mainform);
        textLabel1_2_4_2_2_2_3_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2_3_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2_3_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2_3_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2_3_2->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1_2_4_2_2_2_3_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout9->addItem(horizontalSpacer_8);


        vboxLayout->addLayout(hboxLayout9);

        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QStringLiteral("hboxLayout10"));
        textLabel1_2_4_2_2_3_3 = new QLabel(mainform);
        textLabel1_2_4_2_2_3_3->setObjectName(QStringLiteral("textLabel1_2_4_2_2_3_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_3_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_3_3->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_3_3->setWordWrap(false);

        hboxLayout10->addWidget(textLabel1_2_4_2_2_3_3);

        txtOUT5 = new QLabel(mainform);
        txtOUT5->setObjectName(QStringLiteral("txtOUT5"));
        sizePolicy3.setHeightForWidth(txtOUT5->sizePolicy().hasHeightForWidth());
        txtOUT5->setSizePolicy(sizePolicy3);
        txtOUT5->setWordWrap(false);

        hboxLayout10->addWidget(txtOUT5);

        label_2 = new QLabel(mainform);
        label_2->setObjectName(QStringLiteral("label_2"));

        hboxLayout10->addWidget(label_2);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout10->addItem(horizontalSpacer_10);

        textLabel1_2_4_2_2_2_3_3 = new QLabel(mainform);
        textLabel1_2_4_2_2_2_3_3->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2_3_3"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2_3_3->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2_3_3->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2_3_3->setWordWrap(false);

        hboxLayout10->addWidget(textLabel1_2_4_2_2_2_3_3);

        txtOUT7 = new QLabel(mainform);
        txtOUT7->setObjectName(QStringLiteral("txtOUT7"));
        sizePolicy3.setHeightForWidth(txtOUT7->sizePolicy().hasHeightForWidth());
        txtOUT7->setSizePolicy(sizePolicy3);
        txtOUT7->setWordWrap(false);

        hboxLayout10->addWidget(txtOUT7);

        textLabel1_2_4_2_2_2_3_3_2 = new QLabel(mainform);
        textLabel1_2_4_2_2_2_3_3_2->setObjectName(QStringLiteral("textLabel1_2_4_2_2_2_3_3_2"));
        sizePolicy.setHeightForWidth(textLabel1_2_4_2_2_2_3_3_2->sizePolicy().hasHeightForWidth());
        textLabel1_2_4_2_2_2_3_3_2->setSizePolicy(sizePolicy);
        textLabel1_2_4_2_2_2_3_3_2->setWordWrap(false);

        hboxLayout10->addWidget(textLabel1_2_4_2_2_2_3_3_2);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout10->addItem(horizontalSpacer_11);


        vboxLayout->addLayout(hboxLayout10);

        pbJD = new QProgressBar(mainform);
        pbJD->setObjectName(QStringLiteral("pbJD"));
        pbJD->setValue(0);

        vboxLayout->addWidget(pbJD);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        lblFileList = new QTableWidget(mainform);
        if (lblFileList->columnCount() < 5)
            lblFileList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        lblFileList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        lblFileList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        lblFileList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        lblFileList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        lblFileList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        lblFileList->setObjectName(QStringLiteral("lblFileList"));
        lblFileList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        lblFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(lblFileList);


        vboxLayout->addLayout(horizontalLayout);


        retranslateUi(mainform);
        QObject::connect(btnStart, SIGNAL(clicked()), mainform, SLOT(OnBtnStartClicked()));
        QObject::connect(btnPause, SIGNAL(clicked()), mainform, SLOT(OnBtnPauseClicked()));
        QObject::connect(btnStop, SIGNAL(clicked()), mainform, SLOT(OnBtnStopClicked()));

        QMetaObject::connectSlotsByName(mainform);
    } // setupUi

    void retranslateUi(QWidget *mainform)
    {
        mainform->setWindowTitle(QApplication::translate("mainform", "ODBC\346\216\245\345\217\243\347\232\204\346\225\260\346\215\256\345\272\223\346\265\213\350\257\225\345\267\245\345\205\267", 0));
        textLabel1_2_5_3_2->setText(QApplication::translate("mainform", "ID\345\237\272\346\225\260", 0));
        cbDataJS->clear();
        cbDataJS->insertItems(0, QStringList()
         << QApplication::translate("mainform", "100000000000000", 0)
         << QApplication::translate("mainform", "200000000000000", 0)
         << QApplication::translate("mainform", "300000000000000", 0)
         << QApplication::translate("mainform", "400000000000000", 0)
         << QApplication::translate("mainform", "500000000000000", 0)
         << QApplication::translate("mainform", "600000000000000", 0)
         << QApplication::translate("mainform", "700000000000000", 0)
         << QApplication::translate("mainform", "800000000000000", 0)
         << QApplication::translate("mainform", "900000000000000", 0)
         << QApplication::translate("mainform", "110000000000000", 0)
         << QApplication::translate("mainform", "120000000000000", 0)
         << QApplication::translate("mainform", "130000000000000", 0)
         << QApplication::translate("mainform", "140000000000000", 0)
         << QApplication::translate("mainform", "150000000000000", 0)
         << QApplication::translate("mainform", "160000000000000", 0)
         << QApplication::translate("mainform", "170000000000000", 0)
         << QApplication::translate("mainform", "180000000000000", 0)
         << QApplication::translate("mainform", "190000000000000", 0)
        );
        usingInputId->setText(QApplication::translate("mainform", "\344\275\277\347\224\250\350\276\223\345\205\245", 0));
        version_info->setText(QApplication::translate("mainform", "ODBC \345\206\231\345\205\245\346\265\213\350\257\225", 0));
        textLabel1_2_4->setText(QApplication::translate("mainform", "\346\225\260\346\215\256\350\277\236\346\216\245\344\277\241\346\201\257 ", 0));
        textLabel1_2->setText(QApplication::translate("mainform", "\347\224\250\346\210\267\345\220\215", 0));
        txtName->setText(QString());
        textLabel1_2_2->setText(QApplication::translate("mainform", "\345\257\206\347\240\201", 0));
        txtPass->setText(QString());
        textLabel1_2_3->setText(QApplication::translate("mainform", "\350\277\236\346\216\245\345\220\215", 0));
        txtConnName->setText(QString());
        textLabel1_2_4_2->setText(QApplication::translate("mainform", "\346\265\213\350\257\225\350\256\276\347\275\256    ", 0));
        textLabel1_2_5->setText(QApplication::translate("mainform", "\345\271\266\345\217\221\350\277\236\346\216\245\346\225\260\357\274\232", 0));
        textLabel1_2_5_2_2->setText(QApplication::translate("mainform", "\345\215\225\346\254\241\346\217\220\344\272\244\346\225\260\351\207\217\357\274\232", 0));
        cbDCSL->clear();
        cbDCSL->insertItems(0, QStringList()
         << QApplication::translate("mainform", "10", 0)
         << QApplication::translate("mainform", "20", 0)
         << QApplication::translate("mainform", "50", 0)
         << QApplication::translate("mainform", "100", 0)
         << QApplication::translate("mainform", "200", 0)
         << QApplication::translate("mainform", "500", 0)
         << QApplication::translate("mainform", "1000", 0)
         << QApplication::translate("mainform", "3000", 0)
         << QApplication::translate("mainform", "10000", 0)
         << QApplication::translate("mainform", "30000", 0)
        );
        allLogOff->setText(QApplication::translate("mainform", "\345\205\263\351\227\255\346\211\200\346\234\211\346\227\245\345\277\227", 0));
        detailLogOff->setText(QApplication::translate("mainform", "\345\205\263\351\227\255\350\257\246\347\273\206\346\227\245\345\277\227", 0));
        emptyTable->setText(QApplication::translate("mainform", "\346\270\205\347\251\272\350\241\250", 0));
        label_5->setText(QApplication::translate("mainform", "\351\207\215\350\257\225\346\254\241\346\225\260", 0));
        textLabel1_2_5_3->setText(QApplication::translate("mainform", "\346\225\260\346\215\256\350\247\204\346\250\241\357\274\232", 0));
        cbDataGM->clear();
        cbDataGM->insertItems(0, QStringList()
         << QApplication::translate("mainform", "D1\357\274\210200\344\270\207\347\224\265\350\241\250\357\274\211", 0)
         << QApplication::translate("mainform", "D2\357\274\2102000\344\270\207\347\224\265\350\241\250\357\274\211", 0)
         << QApplication::translate("mainform", "DX ( 100\347\224\265\350\241\250\357\274\214\346\265\213\350\257\225\347\224\250 )", 0)
         << QApplication::translate("mainform", "DX ( 1000\347\224\265\350\241\250\357\274\214\346\265\213\350\257\225\347\224\250 )", 0)
         << QApplication::translate("mainform", "DX\357\274\2101\344\270\207\347\224\265\350\241\250\357\274\214\346\265\213\350\257\225\347\224\250\357\274\211", 0)
        );
        cbMeterNo->setText(QApplication::translate("mainform", "\344\275\277\347\224\250\350\276\223\345\205\245", 0));
        label_3->setText(QApplication::translate("mainform", "\347\224\265\350\241\250", 0));
        textLabel1_2_5_2->setText(QApplication::translate("mainform", "\346\225\260\346\215\256\345\221\250\346\234\237\357\274\232", 0));
        cbDataZQ->clear();
        cbDataZQ->insertItems(0, QStringList()
         << QApplication::translate("mainform", "2\345\244\251\357\274\210\346\265\213\350\257\225\347\224\250\357\274\211", 0)
         << QApplication::translate("mainform", "10\345\244\251 \357\274\210\346\265\213\350\257\225\347\224\250\357\274\211", 0)
         << QApplication::translate("mainform", "1\344\270\252\346\234\210 \357\274\210\346\265\213\350\257\225\347\224\250\357\274\211", 0)
         << QApplication::translate("mainform", "1\345\271\264\357\274\2102015-01-01 \357\275\236 2015-12-31\357\274\211", 0)
         << QApplication::translate("mainform", "7\345\271\264\357\274\2102015-01-01 \357\275\236 2021-12-31\357\274\211", 0)
        );
        cbDays->setText(QApplication::translate("mainform", "\344\275\277\347\224\250\350\276\223\345\205\245", 0));
        label_4->setText(QApplication::translate("mainform", "\345\244\251", 0));
        textLabel1_2_5_2_3->setText(QApplication::translate("mainform", "\345\255\230\345\205\245\347\233\256\346\240\207\357\274\232", 0));
        cbYLMC->clear();
        cbYLMC->insertItems(0, QStringList()
         << QApplication::translate("mainform", "E_MP_VOL_CURVE_P", 0)
         << QApplication::translate("mainform", "E_MP_ENERGY_CURVE_P", 0)
         << QApplication::translate("mainform", "E_MP_DAY_ENERGY_P", 0)
         << QApplication::translate("mainform", "E_MIN_TABLE_P", 0)
        );
        rbInsert->setText(QApplication::translate("mainform", "INSERT", 0));
        rbUpsert->setText(QApplication::translate("mainform", "UPSERT INTO", 0));
        rbUpUsing->setText(QApplication::translate("mainform", "UPSERT USING LOAD", 0));
        btnStart->setText(QApplication::translate("mainform", "\346\211\247\350\241\214", 0));
        btnPause->setText(QApplication::translate("mainform", "\346\232\202\345\201\234", 0));
        btnStop->setText(QApplication::translate("mainform", "\345\201\234\346\255\242", 0));
        textLabel1_2_4_2_2->setText(QApplication::translate("mainform", "\345\220\210\350\256\241\344\272\247\347\224\237\357\274\232", 0));
        txtOUT1->setText(QApplication::translate("mainform", "0", 0));
        label->setText(QApplication::translate("mainform", "\346\235\241", 0));
        textLabel1_2_4_2_2_2->setText(QApplication::translate("mainform", "\345\215\240\347\224\250\347\251\272\351\227\264", 0));
        txtOUT2->setText(QApplication::translate("mainform", "0", 0));
        textLabel1_2_4_2_2_2_2->setText(QApplication::translate("mainform", "M", 0));
        textLabel1_2_4_2_2_3_4->setText(QApplication::translate("mainform", "\346\200\273\346\225\260\357\274\232", 0));
        txtOUTt->setText(QApplication::translate("mainform", "0", 0));
        textLabel1_2_4_2_2_3->setText(QApplication::translate("mainform", "\346\200\273\345\271\263\345\235\207\357\274\232", 0));
        txtOUT3->setText(QApplication::translate("mainform", "0", 0));
        textLabel1_2_4_2_2_2_3->setText(QApplication::translate("mainform", "\346\235\241/s\357\274\214", 0));
        txtOUT4->setText(QApplication::translate("mainform", "0", 0));
        textLabel1_2_4_2_2_2_2_2->setText(QApplication::translate("mainform", "M/s", 0));
        textLabel1_2_4_2_2_3_2->setText(QApplication::translate("mainform", "\347\224\250\346\227\266\357\274\232", 0));
        txtOUTs->setText(QApplication::translate("mainform", "0", 0));
        textLabel1_2_4_2_2_2_3_2->setText(QApplication::translate("mainform", "\347\247\222", 0));
        textLabel1_2_4_2_2_3_3->setText(QApplication::translate("mainform", "10\345\210\206\351\222\237\345\271\263\345\235\207\357\274\232", 0));
        txtOUT5->setText(QApplication::translate("mainform", "0", 0));
        label_2->setText(QApplication::translate("mainform", "\346\235\241/s", 0));
        textLabel1_2_4_2_2_2_3_3->setText(QApplication::translate("mainform", "10 \345\210\206\351\222\237\346\234\200\345\244\247\345\200\274", 0));
        txtOUT7->setText(QApplication::translate("mainform", "0", 0));
        textLabel1_2_4_2_2_2_3_3_2->setText(QApplication::translate("mainform", "\346\235\241/s", 0));
        QTableWidgetItem *___qtablewidgetitem = lblFileList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("mainform", "ID\350\265\267\345\247\213\345\200\274", 0));
        QTableWidgetItem *___qtablewidgetitem1 = lblFileList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("mainform", "\347\212\266\346\200\201", 0));
        QTableWidgetItem *___qtablewidgetitem2 = lblFileList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("mainform", "\345\267\262\344\272\247\347\224\237\350\256\260\345\275\225\346\225\260", 0));
        QTableWidgetItem *___qtablewidgetitem3 = lblFileList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("mainform", "\345\267\262\344\272\247\347\224\237\345\255\227\350\212\202(M)", 0));
        QTableWidgetItem *___qtablewidgetitem4 = lblFileList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("mainform", "\344\273\273\345\212\241\350\265\267\345\247\213\346\227\266\351\227\264", 0));
    } // retranslateUi

};

namespace Ui {
    class mainform: public Ui_mainform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
