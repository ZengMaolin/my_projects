#include "ctp.h"
#include "stdafx.h"
#include <QDebug>
#include <iostream>
#include <QSettings>
#include <QFileInfo>
#include "ctp_beep.h"

ctp::ctp(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    /*行情表格*/
    QStringList headerHQ;

    ui.HQTable->setColumnCount(11);
    //ui.HQTable->setRowCount(10);
    headerHQ.append(QString::fromUtf8("合约代码"));
    headerHQ.append(QString::fromUtf8("更新时间"));
    headerHQ.append(QString::fromUtf8("最新价"));
    headerHQ.append(QString::fromUtf8("买一价"));
    headerHQ.append(QString::fromUtf8("买一量"));
    headerHQ.append(QString::fromUtf8("卖一价"));
    headerHQ.append(QString::fromUtf8("卖一量"));
    headerHQ.append(QString::fromUtf8("涨幅"));
    headerHQ.append(QString::fromUtf8("成交量"));
    headerHQ.append(QString::fromUtf8("涨停价"));
    headerHQ.append(QString::fromUtf8("跌停价"));

    ui.HQTable->setHorizontalHeaderLabels(headerHQ);
    ui.HQTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.HQTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.HQTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*委托表格*/
    QStringList headerWT;

    ui.WTtable->setColumnCount(9);

    headerWT.append(QString::fromUtf8("委托时间"));
    headerWT.append(QString::fromUtf8("合约代码"));
    headerWT.append(QString::fromUtf8("买卖"));
    headerWT.append(QString::fromUtf8("开平"));
    headerWT.append(QString::fromUtf8("数量"));
    headerWT.append(QString::fromUtf8("价格"));
    headerWT.append(QString::fromUtf8("状态"));
    headerWT.append(QString::fromUtf8("委托号"));
    headerWT.append(QString::fromUtf8("交易所"));

    ui.WTtable->setHorizontalHeaderLabels(headerWT);
    ui.WTtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.WTtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.WTtable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    /*成交表格*/
    QStringList headerCJ;

    ui.CJtable->setColumnCount(8);

    headerCJ.append(QString::fromUtf8("成交时间"));
    headerCJ.append(QString::fromUtf8("合约代码"));
    headerCJ.append(QString::fromUtf8("买卖"));
    headerCJ.append(QString::fromUtf8("开平"));
    headerCJ.append(QString::fromUtf8("数量"));
    headerCJ.append(QString::fromUtf8("价格"));
    headerCJ.append(QString::fromUtf8("委托号"));
    headerCJ.append(QString::fromUtf8("交易所"));

    ui.CJtable->setHorizontalHeaderLabels(headerCJ);
    ui.CJtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.CJtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.CJtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*持仓表格*/
    QStringList headerCC;

    ui.CCtable->setColumnCount(4);

    headerCC.append(QString::fromUtf8("合约代码"));
    headerCC.append(QString::fromUtf8("持仓类型"));
    headerCC.append(QString::fromUtf8("持仓数量"));
    headerCC.append(QString::fromUtf8("持仓成本"));

    ui.CCtable->setHorizontalHeaderLabels(headerCC);
    ui.CCtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.CCtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.CCtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*资金表格*/
    QStringList headerZJ;

    ui.ZJtable->setColumnCount(5);

    headerZJ.append(QString::fromUtf8("账号"));
    headerZJ.append(QString::fromUtf8("总权益"));
    headerZJ.append(QString::fromUtf8("占用保证金"));
    headerZJ.append(QString::fromUtf8("可用资金"));
    headerZJ.append(QString::fromUtf8("风险度"));

    ui.ZJtable->setHorizontalHeaderLabels(headerZJ);
    ui.ZJtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.ZJtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.ZJtable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*合约表格*/
    QStringList headerHY;

    ui.HYtable->setColumnCount(4);

    headerHY.append(QString::fromUtf8("合约代码"));
    headerHY.append(QString::fromUtf8("合约名称"));
    headerHY.append(QString::fromUtf8("合约乘数"));
    headerHY.append(QString::fromUtf8("合约点数"));


    ui.HYtable->setHorizontalHeaderLabels(headerHY);
    ui.HYtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.HYtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.HYtable->setEditTriggers(QAbstractItemView::NoEditTriggers);




    /////右键菜单

    ui.WTtable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui.HQTable->setContextMenuPolicy(Qt::CustomContextMenu);


    //connect signal and slot
    connect(ui.pushButton_add_pairTrading, SIGNAL(clicked()), this, SLOT(init_pair_trading()));
    connect(ui.pushButton_xd, SIGNAL(clicked()), this, SLOT(xiadan()));
    connect(ui.pushButton_addinst, SIGNAL(clicked()), this, SLOT(add_hq_instrument()));
    connect(ui.WTtable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(OnWTMenu(const QPoint&)));
    connect(ui.HQTable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(OnHQMenu(const QPoint&)));
    connect(ui.action_cd, SIGNAL(triggered()), this, SLOT(chedan()));
    connect(ui.action_delete_hy, SIGNAL(triggered()), this, SLOT(delete_hq_hy()));

    //日期/时间显示
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));
    timer->start(500);

    //加载固定存储
    QString file_path = QCoreApplication::applicationDirPath() + "/info.ini";
    QFileInfo file(file_path);

    if (file.exists()) //存在储存配置文件
    {
        QStringList history_pair_list;
        QString lastest;
        QStringList lastest_list;
        m_IniFile = new QSettings(file_path, QSettings::IniFormat);
        m_IniFile->beginGroup("history_pair");
        history_pair_list = m_IniFile->allKeys();
        m_IniFile->endGroup();
        ui.listWidget->addItems(history_pair_list);

        m_IniFile->beginGroup("latest_pair");
        lastest = m_IniFile->value("latest_one").toString();
        m_IniFile->endGroup();

        if (lastest != "")
        {
            lastest_list = lastest.split("_");
            ui.lineEdit_pairA->setText(lastest_list.value(0));
            ui.lineEdit_pairB->setText(lastest_list.value(1));
            ui.lineEdit_pairBeta->setText(lastest_list.value(2));
        }
    }
    ui.listWidget->setMouseTracking(true);


    connect(ui.listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(double_clicked_pair_list()));
    ui.tabWidget->setTabsClosable(true);
    ((QTabBar*)(ui.tabWidget->tabBar()))->setTabButton(0, QTabBar::RightSide, NULL);

    connect(ui.tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(close_pair_trading(int)));

    //状态栏设置
    time_status = new QLabel(this);
    time_status->setText(tr("时间："));
    time_status->setStyleSheet("color:rgb(255,85,0); font:12pt;");
    ui.statusBar->addWidget(time_status);//显示永久信息

    md_status = new QLabel(this);
    md_status->setText(tr("行情：未登录"));
    md_status->setStyleSheet("color:red;");
    ui.statusBar->addPermanentWidget(md_status);//显示永久信息

    td_status = new QLabel(this);
    td_status->setText(tr("交易：未登录"));
    td_status->setStyleSheet("color:red;");
    ui.statusBar->addPermanentWidget(td_status);//显示永久信息

    id_status = new QLabel(this);
    id_status->setText(tr("账号：000000"));
    ui.statusBar->addPermanentWidget(id_status);//显示永久信息

    //add 配置文件读取名字。
    QString m_sProjectPath = QCoreApplication::applicationDirPath() + "/arb_pos/";/*文件夹全路径名*/
    QDir dir(m_sProjectPath);
    if (!dir.exists()) /*判断文件夹是否存在*/
    {
        //新建文件夹
        dir.mkdir(m_sProjectPath);
    }

    dir.setFilter(QDir::Files); /*设置dir的过滤模式,表示只遍历本文件夹内的文件*/
    QFileInfoList fileList = dir.entryInfoList();
    int fileCount = fileList.count(); /*获取本文件夹内的文件个数*/
    for (int i = 0; i < fileCount; i++)
    {
        QFileInfo fileInfo = fileList[i]; /*获取每个文件信息*/
        QString suffix = fileInfo.suffix(); /*获取文件后缀名*/
        /*筛选出所有csv文件*/
        if ((QString::compare(suffix, QString("csv"), Qt::CaseInsensitive)) == 0)
        {
            QString file_name = fileInfo.fileName();
            ui.comboBox_config_file_name->addItem(file_name);
        }
    }
    connect(ui.pushButton_load_config_file, SIGNAL(clicked()), this, SLOT(load_config_file()));
}


void ctp::load_config_file(void)
{
    QString file_name = ui.comboBox_config_file_name->currentText();
    if (file_name.split(".").value(1) != "csv")
    {
        QMessageBox::warning(this, tr("警告"), tr("文件不是csv文件！"));
        return;
    }

    QString file_path = QCoreApplication::applicationDirPath() + "/arb_pos/" + file_name;

    QFile file(file_path);
    bool isOk = file.open(QIODevice::ReadOnly);
    if (isOk == true)
    {
        file.close();
        this->setWindowTitle(file_name.split(".").value(0));
        emit send_load_configFile(file_path);
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("文件不存在，或者异常！"));
    }
}


void ctp::xiadan()
{
    QString instrumentID = ui.lineEdit_code->text();
    QString type;
    QString lots = ui.lineEdit_xdsl->text();
    QString Price = ui.lineEdit_xj->text();
    QString price_type;
    QString close_type;
    int index = ui.comboBox_xd->currentIndex();
    if (index == 0)
    {
        type = "kd";
    }

    if (index == 1)
    {
        type = "pd";
    }

    if (index == 2)
    {
        type = "kk";
    }

    if (index == 3)
    {
        type = "pk";
    }

    if (ui.radioSJ->isChecked())
    {
        price_type = "SJ";
    }
    else
    {
        price_type = "XJ";
    }

    if (ui.radioPJ->isChecked())
    {
        close_type = "PJ";
    }
    else
    {
        close_type = "PZ";
    }
    QStringList message;
    message << instrumentID << type << price_type << close_type << Price << lots;
    emit send_xiadan(message);
}

void ctp::receive_HQ(QString tick)
{
    QStringList strlist = tick.split(',');

    if (strlist.value(0) == ui.lineEdit_code->text())
    {
        ui.label_ask->setText(strlist.value(5));
        ui.label_last->setText(strlist.value(2));
        ui.label_bid->setText(strlist.value(3));
        ui.label_up->setText(strlist.value(9));
        ui.label_down->setText(strlist.value(10));
    }

    for (uint16_t i = 0; i < ui.HQTable->rowCount(); i++)
    {
        if (ui.HQTable->item(i, 0)->text() == strlist.value(0))
        {
            ui.HQTable->setItem(i, 0, new QTableWidgetItem(strlist.value(0)));
            ui.HQTable->setItem(i, 1, new QTableWidgetItem(strlist.value(1)));
            ui.HQTable->setItem(i, 2, new QTableWidgetItem(strlist.value(2)));
            ui.HQTable->setItem(i, 3, new QTableWidgetItem(strlist.value(3)));
            ui.HQTable->setItem(i, 4, new QTableWidgetItem(strlist.value(4)));
            ui.HQTable->setItem(i, 5, new QTableWidgetItem(strlist.value(5)));
            ui.HQTable->setItem(i, 6, new QTableWidgetItem(strlist.value(6)));
            ui.HQTable->setItem(i, 7, new QTableWidgetItem(strlist.value(7)));
            ui.HQTable->setItem(i, 8, new QTableWidgetItem(strlist.value(8)));
            ui.HQTable->setItem(i, 9, new QTableWidgetItem(strlist.value(9)));
            ui.HQTable->setItem(i, 10, new QTableWidgetItem(strlist.value(10)));

            return;
        }
    }

    int row = ui.HQTable->rowCount();
    ui.HQTable->insertRow(row);

    ui.HQTable->setItem(row, 0, new QTableWidgetItem(strlist.value(0)));
    ui.HQTable->setItem(row, 1, new QTableWidgetItem(strlist.value(1)));
    ui.HQTable->setItem(row, 2, new QTableWidgetItem(strlist.value(2)));
    ui.HQTable->setItem(row, 3, new QTableWidgetItem(strlist.value(3)));
    ui.HQTable->setItem(row, 4, new QTableWidgetItem(strlist.value(4)));
    ui.HQTable->setItem(row, 5, new QTableWidgetItem(strlist.value(5)));
    ui.HQTable->setItem(row, 6, new QTableWidgetItem(strlist.value(6)));
    ui.HQTable->setItem(row, 7, new QTableWidgetItem(strlist.value(7)));
    ui.HQTable->setItem(row, 8, new QTableWidgetItem(strlist.value(8)));
    ui.HQTable->setItem(row, 9, new QTableWidgetItem(strlist.value(9)));
    ui.HQTable->setItem(row, 10, new QTableWidgetItem(strlist.value(10)));


}

void ctp::receive_CJ(QString CJdata)
{
    QStringList strlist = CJdata.split(',');
    QString buysell = "";
    QString openclose = "";

    if (strlist.value(2) == "0")
    {
        buysell = QString::fromUtf8("买入");
    }
    else
    {
        buysell = QString::fromUtf8("卖出");
    }

    if (strlist.value(3) == "0")
    {
        openclose = QString::fromUtf8("开仓");
    }
    else if (strlist.value(3) == "3")
    {
        openclose = QString::fromUtf8("平今");
    }
    else
    {
        openclose = QString::fromUtf8("平昨");
    }

    int row = ui.CJtable->rowCount();
    ui.CJtable->insertRow(row);
    ui.CJtable->setItem(row, 0, new QTableWidgetItem(strlist.value(0)));
    ui.CJtable->setItem(row, 1, new QTableWidgetItem(strlist.value(1)));
    ui.CJtable->setItem(row, 2, new QTableWidgetItem(buysell));
    ui.CJtable->setItem(row, 3, new QTableWidgetItem(openclose));
    ui.CJtable->setItem(row, 4, new QTableWidgetItem(strlist.value(4)));
    ui.CJtable->setItem(row, 5, new QTableWidgetItem(strlist.value(5)));
    ui.CJtable->setItem(row, 6, new QTableWidgetItem(strlist.value(6)));
    ui.CJtable->setItem(row, 7, new QTableWidgetItem(strlist.value(7)));
}

void ctp::receive_WT(QString WTdata)
{
    QStringList strlist = WTdata.split(',');
    QString buysell = "";
    QString openclose = "";

    if (strlist.value(2) == "0")
    {
        buysell = QString::fromUtf8("买入");
    }
    else
    {
        buysell = QString::fromUtf8("卖出");
    }

    if (strlist.value(3) == "0")
    {
        openclose = QString::fromUtf8("开仓");
    }
    else if (strlist.value(3) == "3")
    {
        openclose = QString::fromUtf8("平今");
    }
    else
    {
        openclose = QString::fromUtf8("平昨");
    }

    int row = ui.WTtable->rowCount();
    ui.WTtable->insertRow(row);
    ui.WTtable->setItem(row, 0, new QTableWidgetItem(strlist.value(0)));
    ui.WTtable->setItem(row, 1, new QTableWidgetItem(strlist.value(1)));
    ui.WTtable->setItem(row, 2, new QTableWidgetItem(buysell));
    ui.WTtable->setItem(row, 3, new QTableWidgetItem(openclose));
    ui.WTtable->setItem(row, 4, new QTableWidgetItem(strlist.value(4)));
    ui.WTtable->setItem(row, 5, new QTableWidgetItem(strlist.value(5)));
    ui.WTtable->setItem(row, 6, new QTableWidgetItem(strlist.value(6)));
    ui.WTtable->setItem(row, 7, new QTableWidgetItem(strlist.value(7)));
    ui.WTtable->setItem(row, 8, new QTableWidgetItem(strlist.value(8)));
}

void ctp::receive_HY(QString hy_data)
{
    QStringList strlist = hy_data.split(',');

    int row = ui.HYtable->rowCount();
    ui.HYtable->insertRow(row);
    ui.HYtable->setItem(row, 0, new QTableWidgetItem(strlist.value(0)));
    ui.HYtable->setItem(row, 1, new QTableWidgetItem(strlist.value(1)));
    ui.HYtable->setItem(row, 2, new QTableWidgetItem(strlist.value(2)));
    ui.HYtable->setItem(row, 3, new QTableWidgetItem(strlist.value(3)));
}

void ctp::receive_CC(QString cc_data)
{
    QStringList strlist = cc_data.split(',');

    QString lx;

    if (strlist.value(1) == '2')
    {
        lx = QString::fromUtf8("买");
    }
    if (strlist.value(1) == '3')
    {
        lx = QString::fromUtf8("卖");
    }

    int row = ui.CCtable->rowCount();
    ui.CCtable->insertRow(row);
    ui.CCtable->setItem(row, 0, new QTableWidgetItem(strlist.value(0)));
    ui.CCtable->setItem(row, 1, new QTableWidgetItem(lx));
    ui.CCtable->setItem(row, 2, new QTableWidgetItem(strlist.value(2)));
    ui.CCtable->setItem(row, 3, new QTableWidgetItem(strlist.value(3)));
}

void ctp::receive_ZJ(QString zj_data)
{
    QStringList strlist = zj_data.split(',');

    int row = ui.ZJtable->rowCount();

    if (row == 0)
    {
        ui.ZJtable->insertRow(row);
    }
    ui.ZJtable->setItem(0, 0, new QTableWidgetItem(strlist.value(0)));
    ui.ZJtable->setItem(0, 1, new QTableWidgetItem(strlist.value(1)));
    ui.ZJtable->setItem(0, 2, new QTableWidgetItem(strlist.value(2)));
    ui.ZJtable->setItem(0, 3, new QTableWidgetItem(strlist.value(3)));
    ui.ZJtable->setItem(0, 4, new QTableWidgetItem(strlist.value(4)));
}

void ctp::OnWTMenu(const QPoint& pt)
{
    QMenu menu;

    menu.addAction(ui.action_cd);
    menu.exec(ui.WTtable->mapToGlobal(pt));
}

void ctp::OnHQMenu(const QPoint& pt)
{
    QMenu menu;

    menu.addAction(ui.action_delete_hy);
    menu.exec(ui.WTtable->mapToGlobal(pt));
}

void ctp::chedan()
{
    int i = ui.WTtable->currentIndex().row();

    QString wth = ui.WTtable->item(i, 7)->text();
    QString jys = ui.WTtable->item(i, 8)->text();
    //QString brokerid = ui.BIDEdit->text();
    //td->reqOrderAction(brokerid, wth, jys);

    QMessageBox::information(this, "", QString::fromUtf8("已撤单：") + wth);
}

void ctp::init_pair_trading()
{
    QStringList parameters;

    QString instrumentA = ui.lineEdit_pairA->text();
    QString instrumentB = ui.lineEdit_pairB->text();
    QString mode = ui.comboBox_pairTrading->currentText();
    QString beta = ui.lineEdit_pairBeta->text();

    //增加是否有此组合交易窗口判断。
    int size = ui.tabWidget->count();
    for (int i = 0; i < size; i++)
    {
        if (ui.tabWidget->tabText(i) == (instrumentA + "-" + instrumentB + " (beta=" + (beta)+")"))
        {
            QMessageBox::information(this, tr("提示"), tr("此spd交易窗口已经存在！"));
            return;
        }
    }

    parameters << instrumentA << instrumentB << mode << beta;
    emit send_pair_trading_init(parameters);

    QString key = instrumentA + "_" + instrumentB + "_" + beta;
    m_IniFile->beginGroup("history_pair");
    m_IniFile->setValue(key, 0);
    m_IniFile->endGroup();

    m_IniFile->beginGroup("latest_pair");
    m_IniFile->setValue("latest_one", key);
    m_IniFile->endGroup();

    QStringList history_pair_list;
    m_IniFile->beginGroup("history_pair");
    history_pair_list = m_IniFile->allKeys();
    m_IniFile->endGroup();
    ui.listWidget->clear();
    ui.listWidget->addItems(history_pair_list);
}

void ctp::double_clicked_pair_list(void)
{
    QString data = ui.listWidget->currentItem()->text();
    QStringList data_list;
    if (data != "")
    {
        data_list = data.split("_");
        ui.lineEdit_pairA->setText(data_list.value(0));
        ui.lineEdit_pairB->setText(data_list.value(1));
        ui.lineEdit_pairBeta->setText(data_list.value(2));
    }
}

void ctp::add_hq_instrument()
{
    QString instrumentID = ui.lineEdit_addInst->text();
    emit send_add_hq_instrumentID(instrumentID);
}

void ctp::delete_hq_hy(void)
{
    int i = ui.HQTable->currentIndex().row();

    QString id = ui.HQTable->item(i, 0)->text();
    emit send_delete_hq_instrumentID(id);
    ui.HQTable->removeRow(i);
}

void ctp::update_time()
{
    QDateTime time = QDateTime::currentDateTime();

    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    time_status->setText(str);

    if (leg_warnning_count > -10)
    {
        leg_warnning_count--;
    }
    if (leg_warnning_count >= 0)
    {
        qDebug() << "瘸腿闪烁！！" << leg_warnning_count << endl;

        if (leg_warnning_count % 2 == 1)
        {
            ui.centralWidget1->setStyleSheet("#centralWidget1{ border:8px solid#ff0000;}");
            ctp_beep_set(2); //发出瘸腿提示音
        }
        else
        {
            ui.centralWidget1->setStyleSheet("");
        }
    }
    if (leg_warnning_count == 0)
    {
        //清除tab显示
        int max_index = ui.tabWidget->count();
        qDebug() << "瘸腿显示结束" << endl;;

        for (int i = 0; i < max_index; i++)
        {
            ui.tabWidget->tabBar()->setTabTextColor(i, QColor(0, 0, 0));
        }
    }
}

void ctp::update_ctp_value(QStringList ctp_data)
{
    QString MD_status = ctp_data.value(0);
    QString TD_status = ctp_data.value(1);
    QString account_status = ctp_data.value(2);

    if (MD_status == QString::fromUtf8("已登录"))
    {
        md_status->setText("行情：已登录");
        md_status->setStyleSheet("color:green;");
    }
    else
    {
        md_status->setText("行情:" + MD_status);
        md_status->setStyleSheet("color:red;");
    }

    if (TD_status == QString::fromUtf8("已登录"))
    {
        td_status->setText("交易：已登录");
        td_status->setStyleSheet("color:green;");
    }
    else
    {
        td_status->setText("交易:" + TD_status);
        td_status->setStyleSheet("color:red;");
    }

    id_status->setText("账户:" + account_status);
}


QString ctp::add_new_pair_trading(QWidget* new_tab, QString name)
{
    int index = ui.tabWidget->addTab(new_tab, name);
    ui.tabWidget->setCurrentIndex(index);
    return  name;
}

void ctp::set_tabwidget_text_color(QString index)
{
    int max_index = ui.tabWidget->count();
    qDebug() << "收到瘸腿信号:" << index << endl;;

    for (int i = 0; i < max_index; i++)
    {
        if (ui.tabWidget->tabBar()->tabText(i) == index)
        {
            ui.tabWidget->tabBar()->setTabTextColor(i, QColor(255, 0, 0));
            if (leg_warnning_count <= 0)
            {
                leg_warnning_count = 4;
            }
            return;
        }
    }
}

void ctp::close_pair_trading(int index)
{
    ui.tabWidget->widget(index)->close();
}

void ctp::closeEvent(QCloseEvent* event)
{
    int size = ui.tabWidget->count();

    ctp_beep_set(-1);//退出提示音

    if (size <= 1)
    {
        switch (QMessageBox::information(this, tr("提示"), tr("确定退出?"), tr("确定"), tr("取消"), 0, 1))

        {

        case 0:

            event->accept();
            break;

        case 1:

        default:

            event->ignore();

            break;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("您有未关闭交易窗口，请先关闭交易窗口"), tr("返回关闭"), 0);
        event->ignore();
    }
}

void ctp::set_spd_models(QStandardItemModel* spd)
{
    ui.tableView_all_position->setModel(spd);


    ui.tableView_all_position->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}
