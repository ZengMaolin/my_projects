/********************************************************************************
** Form generated from reading UI file 'ctp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTP_H
#define UI_CTP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ctpClass
{
public:
    QAction *action_cd;
    QAction *action_delete_hy;
    QWidget *centralWidget1;
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabWidget;
    QWidget *tab_main;
    QVBoxLayout *verticalLayout_13;
    QSplitter *splitter;
    QTabWidget *tables;
    QWidget *tab;
    QVBoxLayout *verticalLayout_12;
    QTableWidget *HQTable;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *WTtable;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *CJtable;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *CCtable;
    QTableWidget *ZJtable;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *HYtable;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_addInst;
    QPushButton *pushButton_addinst;
    QSpacerItem *verticalSpacer;
    QWidget *widget_single_trading;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_6;
    QLineEdit *lineEdit_code;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_7;
    QLineEdit *lineEdit_xdsl;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioPJ;
    QRadioButton *radioPZ;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_15;
    QRadioButton *radioXJ;
    QLineEdit *lineEdit_xj;
    QHBoxLayout *horizontalLayout_16;
    QRadioButton *radioSJ;
    QComboBox *comboBox_xd;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QLabel *label_ask;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QLabel *label_last;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_12;
    QLabel *label_bid;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLabel *label_up;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_14;
    QLabel *label_down;
    QPushButton *pushButton_xd;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_17;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_pairA;
    QLineEdit *lineEdit_pairB;
    QLineEdit *lineEdit_pairBeta;
    QComboBox *comboBox_pairTrading;
    QPushButton *pushButton_add_pairTrading;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *comboBox_config_file_name;
    QPushButton *pushButton_load_config_file;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_4;
    QListWidget *listWidget;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_5;
    QTableView *tableView_all_position;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ctpClass)
    {
        if (ctpClass->objectName().isEmpty())
            ctpClass->setObjectName(QString::fromUtf8("ctpClass"));
        ctpClass->resize(1476, 992);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ctp/temp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ctpClass->setWindowIcon(icon);
        ctpClass->setLayoutDirection(Qt::LeftToRight);
        ctpClass->setStyleSheet(QString::fromUtf8(""));
        action_cd = new QAction(ctpClass);
        action_cd->setObjectName(QString::fromUtf8("action_cd"));
        action_delete_hy = new QAction(ctpClass);
        action_delete_hy->setObjectName(QString::fromUtf8("action_delete_hy"));
        centralWidget1 = new QWidget(ctpClass);
        centralWidget1->setObjectName(QString::fromUtf8("centralWidget1"));
        centralWidget1->setEnabled(true);
        centralWidget1->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_7 = new QVBoxLayout(centralWidget1);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        tabWidget = new QTabWidget(centralWidget1);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabsClosable(false);
        tab_main = new QWidget();
        tab_main->setObjectName(QString::fromUtf8("tab_main"));
        verticalLayout_13 = new QVBoxLayout(tab_main);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        splitter = new QSplitter(tab_main);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tables = new QTabWidget(splitter);
        tables->setObjectName(QString::fromUtf8("tables"));
        tables->setMinimumSize(QSize(0, 0));
        tables->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_12 = new QVBoxLayout(tab);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        HQTable = new QTableWidget(tab);
        HQTable->setObjectName(QString::fromUtf8("HQTable"));

        verticalLayout_12->addWidget(HQTable);

        tables->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_3 = new QHBoxLayout(tab_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        WTtable = new QTableWidget(tab_3);
        WTtable->setObjectName(QString::fromUtf8("WTtable"));

        horizontalLayout_3->addWidget(WTtable);

        tables->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_8 = new QVBoxLayout(tab_4);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        CJtable = new QTableWidget(tab_4);
        CJtable->setObjectName(QString::fromUtf8("CJtable"));

        verticalLayout_8->addWidget(CJtable);

        tables->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_10 = new QVBoxLayout(tab_2);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        CCtable = new QTableWidget(tab_2);
        CCtable->setObjectName(QString::fromUtf8("CCtable"));

        verticalLayout_10->addWidget(CCtable);

        ZJtable = new QTableWidget(tab_2);
        ZJtable->setObjectName(QString::fromUtf8("ZJtable"));
        ZJtable->setMaximumSize(QSize(16777215, 100));

        verticalLayout_10->addWidget(ZJtable);

        tables->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_9 = new QVBoxLayout(tab_5);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        HYtable = new QTableWidget(tab_5);
        HYtable->setObjectName(QString::fromUtf8("HYtable"));

        verticalLayout_9->addWidget(HYtable);

        tables->addTab(tab_5, QString());
        splitter->addWidget(tables);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMaximumSize(QSize(400, 16777215));
        verticalLayout_6 = new QVBoxLayout(widget_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        frame_6 = new QFrame(widget_2);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_6);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_addInst = new QLineEdit(frame_6);
        lineEdit_addInst->setObjectName(QString::fromUtf8("lineEdit_addInst"));

        horizontalLayout->addWidget(lineEdit_addInst);

        pushButton_addinst = new QPushButton(frame_6);
        pushButton_addinst->setObjectName(QString::fromUtf8("pushButton_addinst"));

        horizontalLayout->addWidget(pushButton_addinst);


        verticalLayout_6->addWidget(frame_6);

        verticalSpacer = new QSpacerItem(20, 139, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        widget_single_trading = new QWidget(widget_2);
        widget_single_trading->setObjectName(QString::fromUtf8("widget_single_trading"));
        widget_single_trading->setStyleSheet(QString::fromUtf8("#widget_single_trading\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(widget_single_trading);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(widget_single_trading);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        frame_4 = new QFrame(widget_single_trading);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_6 = new QLabel(frame_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_14->addWidget(label_6);

        lineEdit_code = new QLineEdit(frame_4);
        lineEdit_code->setObjectName(QString::fromUtf8("lineEdit_code"));

        horizontalLayout_14->addWidget(lineEdit_code);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_7 = new QLabel(frame_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_13->addWidget(label_7);

        lineEdit_xdsl = new QLineEdit(frame_4);
        lineEdit_xdsl->setObjectName(QString::fromUtf8("lineEdit_xdsl"));

        horizontalLayout_13->addWidget(lineEdit_xdsl);


        verticalLayout_4->addLayout(horizontalLayout_13);

        frame = new QFrame(frame_4);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        radioPJ = new QRadioButton(frame);
        radioPJ->setObjectName(QString::fromUtf8("radioPJ"));
        radioPJ->setChecked(true);

        horizontalLayout_7->addWidget(radioPJ);

        radioPZ = new QRadioButton(frame);
        radioPZ->setObjectName(QString::fromUtf8("radioPZ"));

        horizontalLayout_7->addWidget(radioPZ);


        verticalLayout_4->addWidget(frame);

        frame_2 = new QFrame(frame_4);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        radioXJ = new QRadioButton(frame_2);
        radioXJ->setObjectName(QString::fromUtf8("radioXJ"));
        radioXJ->setChecked(true);

        horizontalLayout_15->addWidget(radioXJ);

        lineEdit_xj = new QLineEdit(frame_2);
        lineEdit_xj->setObjectName(QString::fromUtf8("lineEdit_xj"));

        horizontalLayout_15->addWidget(lineEdit_xj);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        radioSJ = new QRadioButton(frame_2);
        radioSJ->setObjectName(QString::fromUtf8("radioSJ"));

        horizontalLayout_16->addWidget(radioSJ);

        comboBox_xd = new QComboBox(frame_2);
        comboBox_xd->addItem(QString());
        comboBox_xd->addItem(QString());
        comboBox_xd->addItem(QString());
        comboBox_xd->addItem(QString());
        comboBox_xd->setObjectName(QString::fromUtf8("comboBox_xd"));

        horizontalLayout_16->addWidget(comboBox_xd);


        verticalLayout_3->addLayout(horizontalLayout_16);


        verticalLayout_4->addWidget(frame_2);


        horizontalLayout_2->addWidget(frame_4);

        frame_3 = new QFrame(widget_single_trading);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_8 = new QLabel(frame_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_8->addWidget(label_8);

        label_ask = new QLabel(frame_3);
        label_ask->setObjectName(QString::fromUtf8("label_ask"));

        horizontalLayout_8->addWidget(label_ask);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_11 = new QLabel(frame_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_9->addWidget(label_11);

        label_last = new QLabel(frame_3);
        label_last->setObjectName(QString::fromUtf8("label_last"));

        horizontalLayout_9->addWidget(label_last);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_12 = new QLabel(frame_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_10->addWidget(label_12);

        label_bid = new QLabel(frame_3);
        label_bid->setObjectName(QString::fromUtf8("label_bid"));

        horizontalLayout_10->addWidget(label_bid);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_13 = new QLabel(frame_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_11->addWidget(label_13);

        label_up = new QLabel(frame_3);
        label_up->setObjectName(QString::fromUtf8("label_up"));

        horizontalLayout_11->addWidget(label_up);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_14 = new QLabel(frame_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_12->addWidget(label_14);

        label_down = new QLabel(frame_3);
        label_down->setObjectName(QString::fromUtf8("label_down"));

        horizontalLayout_12->addWidget(label_down);


        verticalLayout_2->addLayout(horizontalLayout_12);


        horizontalLayout_2->addWidget(frame_3);


        verticalLayout_5->addLayout(horizontalLayout_2);

        pushButton_xd = new QPushButton(widget_single_trading);
        pushButton_xd->setObjectName(QString::fromUtf8("pushButton_xd"));

        verticalLayout_5->addWidget(pushButton_xd);


        verticalLayout_6->addWidget(widget_single_trading);

        splitter->addWidget(widget_2);

        verticalLayout_13->addWidget(splitter);

        widget = new QWidget(tab_main);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        frame_5 = new QFrame(widget);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_11 = new QVBoxLayout(frame_5);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_pairA = new QLineEdit(frame_5);
        lineEdit_pairA->setObjectName(QString::fromUtf8("lineEdit_pairA"));
        lineEdit_pairA->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setPointSize(12);
        lineEdit_pairA->setFont(font1);

        verticalLayout->addWidget(lineEdit_pairA);

        lineEdit_pairB = new QLineEdit(frame_5);
        lineEdit_pairB->setObjectName(QString::fromUtf8("lineEdit_pairB"));
        lineEdit_pairB->setMinimumSize(QSize(0, 30));
        lineEdit_pairB->setFont(font1);

        verticalLayout->addWidget(lineEdit_pairB);

        lineEdit_pairBeta = new QLineEdit(frame_5);
        lineEdit_pairBeta->setObjectName(QString::fromUtf8("lineEdit_pairBeta"));

        verticalLayout->addWidget(lineEdit_pairBeta);

        comboBox_pairTrading = new QComboBox(frame_5);
        comboBox_pairTrading->addItem(QString());
        comboBox_pairTrading->setObjectName(QString::fromUtf8("comboBox_pairTrading"));
        comboBox_pairTrading->setMinimumSize(QSize(0, 30));
        comboBox_pairTrading->setFont(font1);
        comboBox_pairTrading->setEditable(false);
        comboBox_pairTrading->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        verticalLayout->addWidget(comboBox_pairTrading);


        verticalLayout_11->addLayout(verticalLayout);

        pushButton_add_pairTrading = new QPushButton(frame_5);
        pushButton_add_pairTrading->setObjectName(QString::fromUtf8("pushButton_add_pairTrading"));
        pushButton_add_pairTrading->setMinimumSize(QSize(0, 40));

        verticalLayout_11->addWidget(pushButton_add_pairTrading);


        verticalLayout_17->addWidget(frame_5);

        verticalSpacer_2 = new QSpacerItem(20, 205, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_2);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(label_2);

        comboBox_config_file_name = new QComboBox(widget);
        comboBox_config_file_name->addItem(QString());
        comboBox_config_file_name->setObjectName(QString::fromUtf8("comboBox_config_file_name"));
        comboBox_config_file_name->setEditable(true);

        horizontalLayout_5->addWidget(comboBox_config_file_name);


        verticalLayout_16->addLayout(horizontalLayout_5);

        pushButton_load_config_file = new QPushButton(widget);
        pushButton_load_config_file->setObjectName(QString::fromUtf8("pushButton_load_config_file"));

        verticalLayout_16->addWidget(pushButton_load_config_file);


        verticalLayout_17->addLayout(verticalLayout_16);


        horizontalLayout_4->addLayout(verticalLayout_17);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_14->addWidget(label_4);

        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMaximumSize(QSize(400, 16777215));

        verticalLayout_14->addWidget(listWidget);


        horizontalLayout_4->addLayout(verticalLayout_14);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_15->addWidget(label_5);

        tableView_all_position = new QTableView(widget);
        tableView_all_position->setObjectName(QString::fromUtf8("tableView_all_position"));

        verticalLayout_15->addWidget(tableView_all_position);


        horizontalLayout_6->addLayout(verticalLayout_15);


        verticalLayout_13->addWidget(widget);

        tabWidget->addTab(tab_main, QString());

        verticalLayout_7->addWidget(tabWidget);

        ctpClass->setCentralWidget(centralWidget1);
        statusBar = new QStatusBar(ctpClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ctpClass->setStatusBar(statusBar);

        retranslateUi(ctpClass);

        tabWidget->setCurrentIndex(0);
        tables->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ctpClass);
    } // setupUi

    void retranslateUi(QMainWindow *ctpClass)
    {
        ctpClass->setWindowTitle(QApplication::translate("ctpClass", "ctp", nullptr));
        action_cd->setText(QApplication::translate("ctpClass", "\346\222\244\345\215\225", nullptr));
        action_delete_hy->setText(QApplication::translate("ctpClass", "\345\210\240\351\231\244\345\220\210\347\272\246", nullptr));
        tables->setTabText(tables->indexOf(tab), QApplication::translate("ctpClass", "\350\241\214\346\203\205\347\252\227\345\217\243", nullptr));
        tables->setTabText(tables->indexOf(tab_3), QApplication::translate("ctpClass", "\345\247\224\346\211\230\350\256\260\345\275\225", nullptr));
        tables->setTabText(tables->indexOf(tab_4), QApplication::translate("ctpClass", "\346\210\220\344\272\244\350\256\260\345\275\225", nullptr));
        tables->setTabText(tables->indexOf(tab_2), QApplication::translate("ctpClass", "\346\214\201\344\273\223|\350\265\204\351\207\221", nullptr));
        tables->setTabText(tables->indexOf(tab_5), QApplication::translate("ctpClass", "\346\211\200\346\234\211\345\220\210\347\272\246", nullptr));
        lineEdit_addInst->setPlaceholderText(QApplication::translate("ctpClass", "\345\220\210\347\272\246\344\273\243\347\240\201", nullptr));
        pushButton_addinst->setText(QApplication::translate("ctpClass", "\346\267\273\345\212\240\350\241\214\346\203\205", nullptr));
        label->setText(QApplication::translate("ctpClass", "\345\215\225\345\220\210\347\272\246\344\272\244\346\230\223\345\217\260", nullptr));
        label_6->setText(QApplication::translate("ctpClass", "\345\220\210\347\272\246\344\273\243\347\240\201:", nullptr));
        label_7->setText(QApplication::translate("ctpClass", "\344\270\213\345\215\225\346\225\260\351\207\217:", nullptr));
        radioPJ->setText(QApplication::translate("ctpClass", "\345\271\263\344\273\212\344\273\223", nullptr));
        radioPZ->setText(QApplication::translate("ctpClass", "\345\271\263\346\230\250\344\273\223", nullptr));
        radioXJ->setText(QApplication::translate("ctpClass", "\351\231\220\344\273\267", nullptr));
        radioSJ->setText(QApplication::translate("ctpClass", "\345\270\202\344\273\267", nullptr));
        comboBox_xd->setItemText(0, QApplication::translate("ctpClass", "\345\274\200\345\244\232", nullptr));
        comboBox_xd->setItemText(1, QApplication::translate("ctpClass", "\345\271\263\345\244\232", nullptr));
        comboBox_xd->setItemText(2, QApplication::translate("ctpClass", "\345\274\200\347\251\272", nullptr));
        comboBox_xd->setItemText(3, QApplication::translate("ctpClass", "\345\271\263\347\251\272", nullptr));

        label_8->setText(QApplication::translate("ctpClass", "\345\215\226\344\270\200\344\273\267:", nullptr));
        label_ask->setText(QApplication::translate("ctpClass", "0     ", nullptr));
        label_11->setText(QApplication::translate("ctpClass", "\346\234\200\346\226\260\344\273\267:", nullptr));
        label_last->setText(QApplication::translate("ctpClass", "0", nullptr));
        label_12->setText(QApplication::translate("ctpClass", "\344\271\260\344\270\200\344\273\267:", nullptr));
        label_bid->setText(QApplication::translate("ctpClass", "0", nullptr));
        label_13->setText(QApplication::translate("ctpClass", "\346\266\250\345\201\234\344\273\267:", nullptr));
        label_up->setText(QApplication::translate("ctpClass", "0", nullptr));
        label_14->setText(QApplication::translate("ctpClass", "\350\267\214\345\201\234\344\273\267:", nullptr));
        label_down->setText(QApplication::translate("ctpClass", "0", nullptr));
        pushButton_xd->setText(QApplication::translate("ctpClass", "\344\270\213 \345\215\225", nullptr));
        lineEdit_pairA->setText(QApplication::translate("ctpClass", "cu2104", nullptr));
        lineEdit_pairA->setPlaceholderText(QApplication::translate("ctpClass", "\345\220\210\347\272\246A\344\273\243\347\240\201", nullptr));
        lineEdit_pairB->setText(QApplication::translate("ctpClass", "cu2105", nullptr));
        lineEdit_pairB->setPlaceholderText(QApplication::translate("ctpClass", "\345\220\210\347\272\246B\344\273\243\347\240\201", nullptr));
        lineEdit_pairBeta->setInputMask(QString());
        lineEdit_pairBeta->setText(QApplication::translate("ctpClass", "1", nullptr));
        lineEdit_pairBeta->setPlaceholderText(QApplication::translate("ctpClass", "beta\347\263\273\346\225\260", nullptr));
        comboBox_pairTrading->setItemText(0, QApplication::translate("ctpClass", "A - B", nullptr));

        pushButton_add_pairTrading->setText(QApplication::translate("ctpClass", "Add pair trading", nullptr));
        label_2->setText(QApplication::translate("ctpClass", "\351\205\215\347\275\256\346\226\207\344\273\266\357\274\232", nullptr));
        comboBox_config_file_name->setItemText(0, QApplication::translate("ctpClass", "\351\200\211\346\213\251\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));

        pushButton_load_config_file->setText(QApplication::translate("ctpClass", "\345\212\240\350\275\275\351\205\215\347\275\256", nullptr));
        label_4->setText(QApplication::translate("ctpClass", "\345\216\206\345\217\262\350\256\260\345\275\225\357\274\232", nullptr));
        label_5->setText(QApplication::translate("ctpClass", "pair trading \346\234\254\345\234\260\346\214\201\344\273\223\346\261\207\346\200\273\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_main), QApplication::translate("ctpClass", "\344\270\273\347\252\227\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ctpClass: public Ui_ctpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTP_H
