#include "pair_trading.h"
#include <QDateTime>
#include "ctp_beep.h"
pair_trading::pair_trading(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //chart 1 设置
    splineSeries = new QLineSeries();
    chart = new QChart();
    chart->addSeries(splineSeries);
    chart->setTitle(QString::fromUtf8("spread real time data"));
    mAxY = new QValueAxis();
    mAxDateX = new QDateTimeAxis();
    mAxY->setRange(0, maxY);
    mAxY->setTickCount(6);
    mAxDateX->setFormat("mm:ss");// 145°时："yyyy-M-d HH:mm s\""
    mAxDateX->setLabelsAngle(0);
    mAxDateX->setTickCount(5);
    chart->addAxis(mAxY, Qt::AlignLeft);
    chart->addAxis(mAxDateX, Qt::AlignBottom);
    splineSeries->attachAxis(mAxY);// 此二句一定要放在 this->chart()->addAxis 语句之后，不然
    splineSeries->attachAxis(mAxDateX);// 没有曲线显示
    splineSeries->setName("spread_ask(for short spread)");

    splineSeries2 = new QLineSeries();
    chart->addSeries(splineSeries2);
    splineSeries2->attachAxis(mAxY);// 此二句一定要放在 this->chart()->addAxis 语句之后，不然
    splineSeries2->attachAxis(mAxDateX);// 没有曲线显示
    splineSeries2->setName("spread_bid(for long spread)");

    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->show();

    ui.chart_1->setChart(chart);
    ui.chart_1->setRenderHint(QPainter::Antialiasing);


    //chart 2 设置

    chart2 = new QChart();
    splineSeries3 = new QLineSeries();
    chart2->addSeries(splineSeries3);
    chart2->setTitle(QString::fromUtf8("spread real time data"));
    mAxY2 = new QValueAxis();
    mAxDateX2 = new QDateTimeAxis();
    mAxY2->setRange(0, maxY);
    mAxY2->setTickCount(6);
    mAxDateX2->setFormat("mm:ss");// 145°时："yyyy-M-d HH:mm s\""
    mAxDateX2->setLabelsAngle(0);
    mAxDateX2->setTickCount(5);
    chart2->addAxis(mAxY2, Qt::AlignLeft);
    chart2->addAxis(mAxDateX2, Qt::AlignBottom);
    splineSeries3->attachAxis(mAxY2);// 此二句一定要放在 this->chart()->addAxis 语句之后，不然
    splineSeries3->attachAxis(mAxDateX2);// 没有曲线显示
    splineSeries3->setName("spread_ask(for short spread)");

    splineSeries4 = new QLineSeries();
    chart2->addSeries(splineSeries4);
    splineSeries4->attachAxis(mAxY2);// 此二句一定要放在 this->chart()->addAxis 语句之后，不然
    splineSeries4->attachAxis(mAxDateX2);// 没有曲线显示
    splineSeries4->setName("spread_bid(for long spread)");

    chart2->legend()->setAlignment(Qt::AlignBottom);
    chart2->legend()->show();

    ui.chart_2->setChart(chart2);
    ui.chart_2->setRenderHint(QPainter::Antialiasing);



    //历史记录表格
    QStringList headerCC;

    ui.tableWidget_history->setColumnCount(12);
    headerCC.append(QString::fromUtf8("序号"));
    headerCC.append(QString::fromUtf8("主合约"));
    headerCC.append(QString::fromUtf8("次合约"));
    headerCC.append(QString::fromUtf8("方向"));
    headerCC.append(QString::fromUtf8("数量"));
    headerCC.append(QString::fromUtf8("入场时间"));
    headerCC.append(QString::fromUtf8("入场目标"));
    headerCC.append(QString::fromUtf8("入场价差"));
    headerCC.append(QString::fromUtf8("出场时间"));
    headerCC.append(QString::fromUtf8("出场目标"));
    headerCC.append(QString::fromUtf8("出场价差"));
    headerCC.append(QString::fromUtf8("盈亏"));
    ui.tableWidget_history->setHorizontalHeaderLabels(headerCC);
    ui.tableWidget_history->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui.tableWidget_history->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableWidget_history->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //交易表格
    QStringList headerJY;

    ui.tableWidget_trading->setColumnCount(16);
    headerJY.append(QString::fromUtf8("编号"));
    headerJY.append(QString::fromUtf8("价格type"));
    headerJY.append(QString::fromUtf8("合约"));
    headerJY.append(QString::fromUtf8("开平"));
    headerJY.append(QString::fromUtf8("方向"));
    headerJY.append(QString::fromUtf8("挂单价格"));
    headerJY.append(QString::fromUtf8("|市-挂|"));
    headerJY.append(QString::fromUtf8("挂单量"));
    headerJY.append(QString::fromUtf8("撮合量"));
    headerJY.append(QString::fromUtf8("目标量"));
    headerJY.append(QString::fromUtf8("目标价差"));
    headerJY.append(QString::fromUtf8("实时spd"));
    headerJY.append(QString::fromUtf8("挂单时间"));
    headerJY.append(QString::fromUtf8("状态"));
    headerJY.append(QString::fromUtf8("操作1"));
    headerJY.append(QString::fromUtf8("操作2"));
    ui.tableWidget_trading->setHorizontalHeaderLabels(headerJY);
    ui.tableWidget_trading->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui.tableWidget_trading->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui.tableWidget_trading->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //现有持仓表格
    QStringList header_have;

    ui.tableWidget_have->setColumnCount(12);
    header_have.append(QString::fromUtf8("编号"));
    header_have.append(QString::fromUtf8("spd方向"));
    header_have.append(QString::fromUtf8("spd数量"));

    header_have.append(QString::fromUtf8("持仓天数"));
    header_have.append(QString::fromUtf8("盈亏1"));
    header_have.append(QString::fromUtf8("盈亏2"));
    header_have.append(QString::fromUtf8("盈利目标"));
    header_have.append(QString::fromUtf8("A价格选项"));
    header_have.append(QString::fromUtf8("B价格选项"));
    header_have.append(QString::fromUtf8("持仓成本"));
    header_have.append(QString::fromUtf8("持仓时间"));
    header_have.append(QString::fromUtf8("操作"));
    ui.tableWidget_have->setHorizontalHeaderLabels(header_have);
    ui.tableWidget_have->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui.tableWidget_have->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableWidget_have->setEditTriggers(QAbstractItemView::NoEditTriggers);


    connect(this->ui.pushButton_buy, SIGNAL(clicked()), this, SLOT(buy_event()));
    connect(this->ui.pushButton_sell, SIGNAL(clicked()), this, SLOT(buy_event()));

    //设置输入框限制为数字
    ui.textBrowser_message->setTextColor(QColor(100, 50, 150));

    //自动化操作界面初始化
    auto_ui = new auto_process();
    connect(this->ui.pushButton_auto, SIGNAL(clicked()), this, SLOT(auto_process_show()));

    //设置界面初始化
    setting_ui = new pair_trading_setting();
    connect(this->ui.pushButton_setting, SIGNAL(clicked()), this, SLOT(setting_show()));

    //设置右键菜单
    ui.tableWidget_have->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.tableWidget_have, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(OnPositionMenu(const QPoint&)));
    connect(ui.action_delete, SIGNAL(triggered()), this, SLOT(OnPosition_delete()));
    connect(ui.action_edit, SIGNAL(triggered()), this, SLOT(OnPosition_edit()));

    qRegisterMetaType< position_table_row_UI>("position_table_row_UI");
    connect(&edit_window, SIGNAL(send_new_position(position_table_row_UI)), this, SLOT(receive_Position_edit_ret(position_table_row_UI)));
}


pair_trading::~pair_trading()
{
    delete chart;
    delete chart2;

    delete auto_ui;
    delete setting_ui;
}

void pair_trading::OnPositionMenu(const QPoint& pt)
{
    QMenu menu;
    if (ui.tableWidget_have->rowCount() == 0)
    {
        return;
    }

    menu.addAction(ui.action_delete);
    menu.addAction(ui.action_edit);
    menu.exec(ui.tableWidget_have->mapToGlobal(pt));
}
void pair_trading::OnPosition_delete(void)
{
    position_table_row_UI data;
    int i = ui.tableWidget_have->currentIndex().row();
    int index = ui.tableWidget_have->item(i, 0)->text().toInt();

    switch (QMessageBox::information(this, tr("提示"),
        "你确定删除持仓：" + ui.tableWidget_have->item(i, 0)->text(),
        tr("确定"), tr("取消"), 0, 1))

    {

    case 0:
        emit send_position_edit(index, true, data);
        break;

    case 1:

    default:
        break;
    }
}
void pair_trading::OnPosition_edit(void)
{
    position_table_row_UI row_UI;
    int i = ui.tableWidget_have->currentIndex().row();

    row_UI.index = ui.tableWidget_have->item(i, 0)->text();
    row_UI.direction_spd = ui.tableWidget_have->item(i, 1)->text();
    row_UI.vol_spd = ui.tableWidget_have->item(i, 2)->text();

    row_UI.vol_A = ui.tableWidget_have->item(i, 2)->text();
    row_UI.vol_B = ui.tableWidget_have->item(i, 2)->text();

    row_UI.profit = ui.tableWidget_have->item(i, 4)->text();
    row_UI.profit_ticks = ui.tableWidget_have->item(i, 5)->text();
    row_UI.cost = ui.tableWidget_have->item(i, 9)->text();
    row_UI.position_time = ui.tableWidget_have->item(i, 10)->text();

    edit_window.set_position(row_UI);
    edit_window.show();
}
void pair_trading::receive_Position_edit_ret(position_table_row_UI data)
{
    int row_count = ui.tableWidget_have->rowCount();
    for (int i = 0; i < row_count; i++)
    {
        if (ui.tableWidget_have->item(i, 0)->text() == data.index)
        {
            ui.tableWidget_have->setItem(i, 1, new QTableWidgetItem(data.direction_spd));
            ui.tableWidget_have->setItem(i, 2, new QTableWidgetItem(data.vol_spd));
            ui.tableWidget_have->setItem(i, 10, new QTableWidgetItem(data.position_time));

            edit_window.hide();
            //增加提示框修改成功
            QMessageBox::information(this, tr("提示"), tr("修改成功"));
            emit send_position_edit(data.index.toInt(), false, data);
        }
    }
}

void pair_trading::init_initialparameters(QStringList parameters)
{
    ui.label_instrumentA->setText(parameters.value(0));
    ui.label_instrumentB->setText(parameters.value(1));
    chart->setTitle(QString::fromUtf8("spread real time data(") + "beta =" + parameters.value(3) + ")");
    chart2->setTitle(QString::fromUtf8("spread rival price(") + "beta =" + parameters.value(3) + ")");
    ui.label_instrumentA_Chinese->setText(parameters.value(4));
    ui.label_instrumentB_Chinese->setText(parameters.value(5));
}
void pair_trading::set_config_file_parameter(QStringList parameters)
{
    int vol = parameters.value(2).toDouble() + 0.5;//数量文件中是以小数储存，这里四舍五入。
    double target_price = parameters.value(3).toDouble();
    if (vol > 0)
    {
        ui.spinBox_buy_vol->setValue(vol);
        ui.doubleSpinBox_buy_price->setValue(target_price);
    }
    else if (vol < 0) //排除vol为0的情况
    {
        ui.spinBox_sell_vol->setValue(-vol);
        ui.doubleSpinBox_sell_price->setValue(target_price);
    }

}

void pair_trading::update_price_value(QStringList price_group, QStringList price_A, QStringList price_B, QStringList price_group2)
{
    //update group price
    ui.label_high2->setText(price_group.value(0));
    ui.label_high1->setText(price_group.value(1));
    ui.label_low2->setText(price_group.value(2));
    ui.label_low1->setText(price_group.value(3));
    ui.label_average2->setText(price_group.value(4));
    ui.label_average1->setText(price_group.value(5));
    ui.label_now2->setText(price_group.value(6));
    ui.label_now1->setText(price_group.value(7));

    ui.label_series_ask_len->setText("ask:" + price_group.value(9) + "/" + price_group.value(10));
    ui.label_series_bid_len->setText("bid:" + price_group.value(8) + "/" + price_group.value(10));

    ui.label_high_rival_bid->setText(price_group2.value(0));
    ui.label_high_rival_ask->setText(price_group2.value(1));
    ui.label_low_rival_bid->setText(price_group2.value(2));
    ui.label_low_rival_ask->setText(price_group2.value(3));
    ui.label_average_rival_bid->setText(price_group2.value(4));
    ui.label_average_rival_ask->setText(price_group2.value(5));
    ui.label_rival_now_bid->setText(price_group2.value(6));
    ui.label_rival_now_ask->setText(price_group2.value(7));


    //update instrument A price
    ui.label_askvol_A->setText(price_A.value(0));
    ui.label_ask1_A->setText(price_A.value(1));
    //ui.label_last_A->setText(price_A.value(2));
    ui.label_bid1_A->setText(price_A.value(3));
    ui.label_bidvol_A->setText(price_A.value(4));
    ui.label_A_return_3min->setText(price_A.value(7));
    ui.label_A_return_5min->setText(price_A.value(8));
    ui.label_A_return_10min->setText(price_A.value(9));
    ui.label_A_return_30min->setText(price_A.value(10));
    ui.label_A_Xmin_delta->setText(price_A.value(11));
    //ui.label_down_A->setText(price_A.value(6));
    ui.label_a_volatility->setText(price_A.value(12));

    //update instrument B price
    ui.label_askvol_B->setText(price_B.value(0));
    ui.label_ask1_B->setText(price_B.value(1));
    //ui.label_last_B->setText(price_B.value(2));
    ui.label_bid1_B->setText(price_B.value(3));
    ui.label_bidvol_B->setText(price_B.value(4));
    //ui.label_up_B->setText(price_B.value(5));
    //ui.label_down_B->setText(price_B.value(6));


}


void pair_trading::receive_log(QString data)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("hh:mm:ss.zzz: ");
    ui.textBrowser_message->append(str + data);
    ui.textBrowser_message->moveCursor(QTextCursor::MoveOperation::End);
    qDebug() << data << endl;
}

//曲线一的数据
void pair_trading::dataReceived(double value1, double max1, double min1, double value2, double max2, double min2, QDateTime time)
{
    double scale_X, scale_Y;


    if (splineSeries->count() > maxSize)
    {
        splineSeries->removePoints(0, splineSeries->count() - maxSize);
    }

    if (splineSeries2->count() > maxSize)
    {
        splineSeries2->removePoints(0, splineSeries2->count() - maxSize);
    }


    if (min1 < min2)
    {
        scale_X = min1;
    }
    else
    {
        scale_X = min2;
    }

    if (max1 < max2)
    {
        scale_Y = max2;
    }
    else
    {
        scale_Y = max1;
    }

    mAxDateX->setRange(QDateTime::currentDateTime().addSecs(-112 * 1), QDateTime::currentDateTime().addSecs(8));
    mAxY->setRange(scale_X, scale_Y);
    splineSeries->append(time.toMSecsSinceEpoch(), value1);
    splineSeries2->append(time.toMSecsSinceEpoch(), value2);

}

//曲线2的数据
void pair_trading::dataReceived2(double value1, double max1, double min1, double value2, double max2, double min2, QDateTime time)
{
    double scale_X, scale_Y;


    if (splineSeries3->count() > maxSize)
    {
        splineSeries3->removePoints(0, splineSeries3->count() - maxSize);
    }

    if (splineSeries4->count() > maxSize)
    {
        splineSeries4->removePoints(0, splineSeries4->count() - maxSize);
    }


    if (min1 < min2)
    {
        scale_X = min1;
    }
    else
    {
        scale_X = min2;
    }

    if (max1 < max2)
    {
        scale_Y = max2;
    }
    else
    {
        scale_Y = max1;
    }

    mAxDateX2->setRange(QDateTime::currentDateTime().addSecs(-112 * 1), QDateTime::currentDateTime().addSecs(8));
    mAxY2->setRange(scale_X, scale_Y);
    splineSeries3->append(time.toMSecsSinceEpoch(), value1);
    splineSeries4->append(time.toMSecsSinceEpoch(), value2);

}

void pair_trading::buy_event(void)
{
    QList<double> message;

    QObject* senderObj = sender();
    const QString sSenderObjName = senderObj->objectName();
    int direction; // 0 : buy other: sell
    int B_back_tick = 0; // 0: normal; 1:退一tick 2::使用对手价
    double dream_price;
    int vol;
    int A_price_type = 0;


    if (senderObj->objectName() == "pushButton_buy")
    {
        direction = 0;
        if (ui.radioButton_b_back_buy->isChecked())
        {
            B_back_tick = 1;
        }
        else if (ui.radioButton_rival_price_buy->isChecked())
        {
            B_back_tick = 2;
        }
        dream_price = ui.doubleSpinBox_buy_price->value();
        vol = ui.spinBox_buy_vol->value();
        A_price_type = ui.comboBox_A_price_type_buy->currentIndex();

        if (vol > 0)
        {
            message << direction << B_back_tick << dream_price << vol << A_price_type;
            emit send_buy_event(message);
        }
        else
        {
            QMessageBox::information(this, "", QString::fromUtf8("请输入正确数量！"));
        }
    }
    else if (senderObj->objectName() == "pushButton_sell")
    {
        direction = 1;
        if (ui.radioButton_b_back_sell->isChecked())
        {
            B_back_tick = 1;
        }
        else if (ui.radioButton_rival_price_sell->isChecked())
        {
            B_back_tick = 2;
        }
        dream_price = ui.doubleSpinBox_sell_price->value();
        vol = ui.spinBox_sell_vol->value();
        A_price_type = ui.comboBox_A_price_type_sell->currentIndex();
        if (vol > 0)
        {
            message << direction << B_back_tick << dream_price << vol << A_price_type;
            emit send_buy_event(message);
        }
        else
        {
            QMessageBox::information(this, "", QString::fromUtf8("请输入正确数量！"));
        }
    }
    qDebug() << "开启交易：" << message << endl;;

}


void pair_trading::reveive_add_trading_table_row(trading_table_row_UI row)
{
    int size = ui.tableWidget_trading->rowCount();
    int i;
    int row_count = size;
    for (i = size - 1; i >= 0; i--)
    {
        QStringList strlist = ui.tableWidget_trading->item(i, 0)->text().split("_");
        if (strlist.value(0) == row.index)
        {
            row_count = i + 1;
            break;
        }
    }
    ui.tableWidget_trading->insertRow(row_count);
    ui.tableWidget_trading->setItem(row_count, 0, new QTableWidgetItem(row.index + "_" + row.sub_index));
    if (row.sub_index != "0")
    {
        ui.tableWidget_trading->item(row_count, 0)->setBackgroundColor(QColor(255, 125, 0));
    }

    ui.tableWidget_trading->setItem(row_count, 1, new QTableWidgetItem(row.price_type));
    ui.tableWidget_trading->setItem(row_count, 2, new QTableWidgetItem(row.instrument));
    ui.tableWidget_trading->setItem(row_count, 3, new QTableWidgetItem(row.open_or_close));
    ui.tableWidget_trading->setItem(row_count, 4, new QTableWidgetItem(row.direction));
    ui.tableWidget_trading->setItem(row_count, 5, new QTableWidgetItem(row.order_price));
    ui.tableWidget_trading->setItem(row_count, 6, new QTableWidgetItem(row.delta_latest_order));
    ui.tableWidget_trading->setItem(row_count, 7, new QTableWidgetItem(row.order_vol));
    ui.tableWidget_trading->setItem(row_count, 8, new QTableWidgetItem(row.finished_vol));
    ui.tableWidget_trading->setItem(row_count, 9, new QTableWidgetItem(row.target_vol));
    ui.tableWidget_trading->setItem(row_count, 10, new QTableWidgetItem(row.target_price));
    ui.tableWidget_trading->setItem(row_count, 11, new QTableWidgetItem(row.latest_spd_price));
    ui.tableWidget_trading->setItem(row_count, 12, new QTableWidgetItem(row.order_time));
    ui.tableWidget_trading->setItem(row_count, 13, new QTableWidgetItem(row.status));

    if (row.price_type.split("|").value(0) == "B对")
    {
        ui.tableWidget_trading->item(row_count, 1)->setTextColor(QColor(180, 80, 60));
        ui.tableWidget_trading->item(row_count, 11)->setTextColor(QColor(180, 80, 60));
    }

    QPushButton* pBackOrderPushButton1 = new QPushButton(row.button_1.button_text);
    QPushButton* pBackOrderPushButton2 = new QPushButton(row.button_2.button_text);

    pBackOrderPushButton1->setObjectName("button1_" + row.index + "_" + row.sub_index);
    pBackOrderPushButton2->setObjectName("button2_" + row.index + "_" + row.sub_index);
    pBackOrderPushButton1->setEnabled(row.button_1.enbale);
    pBackOrderPushButton2->setEnabled(row.button_2.enbale);

    ui.tableWidget_trading->setCellWidget(row_count, 14, pBackOrderPushButton1);
    ui.tableWidget_trading->setCellWidget(row_count, 15, pBackOrderPushButton2);

    connect(pBackOrderPushButton1, SIGNAL(clicked()), this, SLOT(trading_action()));
    connect(pBackOrderPushButton2, SIGNAL(clicked()), this, SLOT(trading_action()));
}

void pair_trading::reveive_update_trading_table_row(trading_table_row_UI row)
{
    /*QTime t;
    t.start();*/

    int size = ui.tableWidget_trading->rowCount();
    int i;
    int row_count = -1;
    for (i = 0; i < size; i++)
    {
        if (ui.tableWidget_trading->item(i, 0)->text() == (row.index + "_" + row.sub_index))
        {
            row_count = i;
            break;
        }
    }

    if (row_count != -1)
    {
        ui.tableWidget_trading->setItem(row_count, 5, new QTableWidgetItem(row.order_price));
        ui.tableWidget_trading->setItem(row_count, 6, new QTableWidgetItem(row.delta_latest_order));
        ui.tableWidget_trading->setItem(row_count, 7, new QTableWidgetItem(row.order_vol));
        ui.tableWidget_trading->setItem(row_count, 8, new QTableWidgetItem(row.finished_vol));
        //ui.tableWidget_trading->setItem(row_count, 9, new QTableWidgetItem(row.target_vol)); //这两个可以不更新
        //ui.tableWidget_trading->setItem(row_count, 10, new QTableWidgetItem(row.target_price));
        ui.tableWidget_trading->setItem(row_count, 11, new QTableWidgetItem(row.latest_spd_price));
        ui.tableWidget_trading->setItem(row_count, 12, new QTableWidgetItem(row.order_time));
        ui.tableWidget_trading->setItem(row_count, 13, new QTableWidgetItem(row.status));

        ui.tableWidget_trading->item(row_count, 11)->setTextColor(ui.tableWidget_trading->item(row_count, 1)->textColor());


        QPushButton* pBackOrderPushButton1 = (QPushButton*)ui.tableWidget_trading->cellWidget(row_count, 14);
        QPushButton* pBackOrderPushButton2 = (QPushButton*)ui.tableWidget_trading->cellWidget(row_count, 15);

        pBackOrderPushButton1->setEnabled(row.button_1.enbale);
        pBackOrderPushButton1->setText(row.button_1.button_text);
        pBackOrderPushButton2->setEnabled(row.button_2.enbale);
        pBackOrderPushButton2->setText(row.button_2.button_text);

        if (row.button_1.enbale)
        {
            pBackOrderPushButton1->setStyleSheet("background-color: rgb(175,238,238)");
        }
        else
        {
            pBackOrderPushButton1->setStyleSheet("");
        }

        if (row.button_2.enbale)
        {
            pBackOrderPushButton2->setStyleSheet("background-color: rgb(255,180,180)");
        }
        else
        {
            pBackOrderPushButton2->setStyleSheet("");
        }
    }

    //qDebug() << t.elapsed() << "ms";
}

void pair_trading::reveive_delete_trading_table_rows(QString index)
{
    int size = ui.tableWidget_trading->rowCount();
    int i;
    for (i = size - 1; i >= 0; i--)
    {
        QStringList strlist = ui.tableWidget_trading->item(i, 0)->text().split("_");
        if (strlist.value(0) == index)
        {
            ui.tableWidget_trading->removeRow(i);
        }
    }
}



void pair_trading::reveive_add_position_table_row(position_table_row_UI row)
{
    int row_count = ui.tableWidget_have->rowCount();

    ui.tableWidget_have->insertRow(row_count);


    ui.tableWidget_have->setItem(row_count, 0, new QTableWidgetItem(row.index));
    ui.tableWidget_have->setItem(row_count, 1, new QTableWidgetItem(row.direction_spd));
    ui.tableWidget_have->setItem(row_count, 2, new QTableWidgetItem(row.vol_spd));
    //ui.tableWidget_have->setItem(row_count, 3, new QTableWidgetItem(row.vol_A + "|" + row.vol_B));
    ui.tableWidget_have->setItem(row_count, 3, new QTableWidgetItem(row.potions_days));
    ui.tableWidget_have->setItem(row_count, 4, new QTableWidgetItem(row.profit + "元"));
    ui.tableWidget_have->setItem(row_count, 5, new QTableWidgetItem(row.profit_ticks + "tick"));
    //设置一个输入框
    QLineEdit* line_edit = new QLineEdit();
    line_edit->setObjectName("line_edit_" + row.index);
    line_edit->setMaximumWidth(88);
    line_edit->setValidator(new QDoubleValidator());
    ui.tableWidget_have->setCellWidget(row_count, 6, line_edit);

    //增加A价格选项
    QComboBox* combo_box2 = new QComboBox();
    combo_box2->setObjectName("combo_box2_" + row.index);
    combo_box2->addItem("目标价格");
    combo_box2->addItem("对手价格");
    ui.tableWidget_have->setCellWidget(row_count, 7, combo_box2);


    //设置一个多选框-B价格选项
    QComboBox* combo_box = new QComboBox();
    combo_box->setObjectName("combo_box_" + row.index);
    combo_box->addItem("正常价格");
    combo_box->addItem("B退1tick");
    combo_box->addItem("对手价格");

    ui.tableWidget_have->setCellWidget(row_count, 8, combo_box);

    ui.tableWidget_have->setItem(row_count, 9, new QTableWidgetItem(row.cost));
    ui.tableWidget_have->setItem(row_count, 10, new QTableWidgetItem(row.position_time));

    QPushButton* pBackOrderPushButton = new QPushButton(row.button.button_text);
    pBackOrderPushButton->setObjectName("positionButton_" + row.index);
    pBackOrderPushButton->setEnabled(row.button.enbale);
    ui.tableWidget_have->setCellWidget(row_count, 11, pBackOrderPushButton);

    connect(pBackOrderPushButton, SIGNAL(clicked()), this, SLOT(position_action()));
}

void pair_trading::reveive_update_position_table_row(position_table_row_UI row)
{
    int row_count = ui.tableWidget_have->rowCount();
    for (int i = 0; i < row_count; i++)
    {
        if (ui.tableWidget_have->item(i, 0)->text() == row.index)
        {
            ui.tableWidget_have->setItem(i, 4, new QTableWidgetItem(row.profit + "元"));
            ui.tableWidget_have->setItem(i, 5, new QTableWidgetItem(row.profit_ticks + "tick"));
            ui.tableWidget_have->setItem(i, 9, new QTableWidgetItem(row.cost));

            QPushButton* pBackOrderPushButton = (QPushButton*)ui.tableWidget_have->cellWidget(i, 11);
            QComboBox* combo_box = (QComboBox*)ui.tableWidget_have->cellWidget(i, 7);
            QComboBox* combo_box2 = (QComboBox*)ui.tableWidget_have->cellWidget(i, 8);
            pBackOrderPushButton->setText(row.button.button_text);

            combo_box->setEnabled(row.button.enbale);
            combo_box2->setEnabled(row.button.enbale);
            pBackOrderPushButton->setEnabled(row.button.enbale);
            return;
        }
    }
}

void pair_trading::reveive_update_position_table_days(position_table_row_UI row)
{
    int row_count = ui.tableWidget_have->rowCount();
    for (int i = 0; i < row_count; i++)
    {
        if (ui.tableWidget_have->item(i, 0)->text() == row.index)
        {
            ui.tableWidget_have->setItem(i, 3, new QTableWidgetItem(row.potions_days));
            return;
        }
    }
}

void pair_trading::reveive_delete_position_table_row(QString index)
{
    int size = ui.tableWidget_have->rowCount();
    int i;
    for (i = size - 1; i >= 0; i--)
    {
        if (ui.tableWidget_have->item(i, 0)->text() == index)
        {
            ui.tableWidget_have->removeRow(i);
        }
    }
}

void pair_trading::receive_add_history_table_row(history_position_status data)
{
    int row = ui.tableWidget_history->rowCount();
    ui.tableWidget_history->insertRow(row);

    ui.tableWidget_history->setItem(row, 0, new QTableWidgetItem(data.index));
    ui.tableWidget_history->setItem(row, 1, new QTableWidgetItem(data.instrumentA));
    ui.tableWidget_history->setItem(row, 2, new QTableWidgetItem(data.instrumentB));
    ui.tableWidget_history->setItem(row, 3, new QTableWidgetItem(data.spd_direction));
    ui.tableWidget_history->setItem(row, 4, new QTableWidgetItem(data.spd_vol));
    ui.tableWidget_history->setItem(row, 5, new QTableWidgetItem(data.start_time));
    ui.tableWidget_history->setItem(row, 6, new QTableWidgetItem(data.start_target_price));
    ui.tableWidget_history->setItem(row, 7, new QTableWidgetItem(data.start_price));
    ui.tableWidget_history->setItem(row, 8, new QTableWidgetItem(data.end_time));
    ui.tableWidget_history->setItem(row, 9, new QTableWidgetItem(data.end_target_price));
    ui.tableWidget_history->setItem(row, 10, new QTableWidgetItem(data.end_price));
    ui.tableWidget_history->setItem(row, 11, new QTableWidgetItem(data.profit));
}



void pair_trading::trading_action()
{
    QObject* senderObj = sender();
    const QString sSenderObjName = senderObj->objectName();

    emit send_trading_action(sSenderObjName); //发送信号
}

void pair_trading::position_action()
{
    QObject* senderObj = sender();
    const QString sSenderObjName = senderObj->objectName();
    QStringList strlist = sSenderObjName.split('_');
    QString index;
    int send_index;
    double target_price;
    int A_price_type, B_price_type;
    if (strlist.value(0) == "positionButton")
    {
        index = strlist.value(1);
        int row_count = ui.tableWidget_have->rowCount();
        for (int i = 0; i < row_count; i++)
        {
            if (ui.tableWidget_have->item(i, 0)->text() == index)
            {
                send_index = index.toInt();
                //读取输入框
                QLineEdit* line_edit = (QLineEdit*)ui.tableWidget_have->cellWidget(i, 6);
                target_price = line_edit->text().toDouble();
                //设置一个多选框
                QComboBox* combo_box = (QComboBox*)ui.tableWidget_have->cellWidget(i, 7);
                A_price_type = combo_box->currentIndex();

                QComboBox* combo_box2 = (QComboBox*)ui.tableWidget_have->cellWidget(i, 8);
                B_price_type = combo_box2->currentIndex();
                emit send_position_action(send_index, target_price, A_price_type, B_price_type); //发送信号
            }
        }
    }
}


void pair_trading::closeEvent(QCloseEvent* event)
{
    int size = ui.tableWidget_trading->rowCount();
    QStringList message;
    ctp_beep_set(3); // 关闭提示音
    message << ui.label_instrumentA->text() << ui.label_instrumentB->text();
    if (size == 0)
    {
        switch (QMessageBox::information(this, tr("提示"),
            "你确定关闭" + ui.label_instrumentA->text() + "-" + ui.label_instrumentB->text() + "交易窗口",
            tr("确定"), tr("取消"), 0, 0))

        {

        case 0:

            event->accept();
            emit send_close_data(message);
            break;

        case 1:

        default:

            event->ignore();

            break;
        }
    }
    else
    {
        switch (QMessageBox::warning(this, tr("警告"),
            tr("您有交易中订单，请停止订单或者等待交易完成！！，如果仍想关闭此tab，请三思。"),
            tr("强制关闭"), tr("返回"), 0, 0))

        {

        case 0:

            event->accept();
            emit send_close_data(message);
            break;

        case 1:

        default:

            event->ignore();

            break;
        }
    }
}
void pair_trading::leg_warning(QString message)
{
    QMessageBox::critical(this, message, tr("有瘸腿订单，请立即处理"), 0, 0);
}

void pair_trading::auto_process_show(void)
{
    receive_log("打开自动化交易！");
    auto_ui->show();
}
void pair_trading::setting_show(void)
{
    receive_log("打开参数设置窗口！");
    setting_ui->show();
}

void pair_trading::set_spd_models(QStandardItemModel* spd, QStandardItemModel* spd_A, QStandardItemModel* spd_B)
{
    ui.tableView_spd->setModel(spd);
    ui.tableView_statisticA->setModel(spd_A);
    ui.tableView_statisticB->setModel(spd_B);

    ui.tableView_spd->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui.tableView_statisticA->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui.tableView_statisticB->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
