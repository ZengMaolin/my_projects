#include "pair_trading_process.h"
#include <QTimer>
#include <iostream>
#include "auto_trading_process.h"
#include "ctp_beep.h"

pair_trading_process::pair_trading_process(pair_trading* ptu, Mdspi* p_md, Tdspi* p_td, QObject* parent)
    : QObject(parent)
{
    //初始化接收的参数。
    md = p_md;
    td = p_td;
    p_ui = ptu;
    connect(this, SIGNAL(send_charts_data(double, double, double, double, double, double, QDateTime)), \
        p_ui, SLOT(dataReceived(double, double, double, double, double, double, QDateTime)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_charts_data2(double, double, double, double, double, double, QDateTime)), \
        p_ui, SLOT(dataReceived2(double, double, double, double, double, double, QDateTime)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_price_value(QStringList, QStringList, QStringList, QStringList)), p_ui, SLOT(update_price_value(QStringList, QStringList, QStringList, QStringList)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_log_message(QString)), p_ui, SLOT(receive_log(QString)), Qt::QueuedConnection);
    connect(this->td, SIGNAL(td_send_login_status(QString)), p_ui, SLOT(receive_log(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_leg_warning_show(QString)), p_ui, SLOT(leg_warning(QString)), Qt::QueuedConnection);

    //初始化自动化交易
    auto_trade = new auto_trading_process(this);

    auto_objThread = new QThread();
    auto_trade->moveToThread(auto_objThread);
    connect(auto_objThread, &QThread::finished, auto_trade, &QObject::deleteLater);
    connect(auto_objThread, &QThread::finished, auto_objThread, &QObject::deleteLater);
    auto_objThread->start(); //开启线程
    connect(this, SIGNAL(send_auto_process_start()), auto_trade, SLOT(init_auto_trading()), Qt::QueuedConnection);

}

pair_trading_process::~pair_trading_process()
{
    auto_objThread->exit();

    if (data_process_thread != nullptr)
    {
        fun1_thread_flag = false;
        data_process_thread->join();
        delete data_process_thread;
    }
    if (timer != nullptr)
    {
        //timer->stop();
        delete timer;
    }
}

void pair_trading_process::update_event()
{
    //增加瘸腿显示发送
    if (is_lame_leg)
    {
        qDebug() << "瘸腿传递！！" << leg_count << endl;
        emit send_tabwidget_text_color(widget_tab_index);
    }
    if (time_count % 120 == 0) //1min刷新一次
    {
        QTime current_time = QTime::currentTime();
        QTime time_start = QTime::fromString("20:59:00", "hh:mm:ss");
        QTime time_end = QTime::fromString("21:00:00", "hh:mm:ss");

        if (current_time > time_start && current_time < time_end)
        {
            //在这个时间区间内更新持仓的持仓天数
            QList<position_status>::iterator position_item;

            for (position_item = position_list.begin(); position_item != position_list.end(); position_item++)
            {
                //持仓天数判断
                position_table_row_UI row_UI;

                row_UI.index = QString::number(position_item->index);
                QString str = "2021-" + position_item->position_time;
                QDateTime time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");


                QDateTime compare_time = QDateTime::currentDateTime();


                compare_time.setTime(QTime::fromString("20:00:00", "hh:mm:ss"));

                int delta_secs = time.secsTo(compare_time);

                if (delta_secs > 0) //昨仓算算天数就好
                {
                    int days = (delta_secs / (24 * 60 * 60)) + 1;
                    row_UI.potions_days = QString::number(days) + "天";
                }
                else
                {
                    row_UI.potions_days = "当天";
                }

                emit send_update_position_table_days(row_UI);
                emit send_log_message("修改持仓天数：" + row_UI.index);
            }

        }
    }
    time_count++;
}


void pair_trading_process::init_ui_data(void)
{
    QStringList parameters;

    //日期/时间显示
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_event()));
    timer->start(500);
    emit send_log_message("开始初始化...");
    HYstruct_A = td->get_HYinfo(InsrumentA);
    HYstruct_B = td->get_HYinfo(InsrumentB);
    parameters << InsrumentA << InsrumentB << group_mode <<
        QString::number(beta) << HYstruct_A.chinese_name << HYstruct_B.chinese_name;
    p_ui->init_initialparameters(parameters);


    qRegisterMetaType<CThostFtdcDepthMarketDataField>("CThostFtdcDepthMarketDataField");
    connect(md, SIGNAL(send_market_data(CThostFtdcDepthMarketDataField)), this, SLOT(receive_hq_data(CThostFtdcDepthMarketDataField)));

    qRegisterMetaType< QList<double>>("QList<double>");
    connect(p_ui, SIGNAL(send_buy_event(QList<double>)), this, SLOT(receive_buy_event(QList<double>)), Qt::QueuedConnection);
    connect(p_ui, SIGNAL(send_trading_action(QString)), this, SLOT(receive_trading_action(QString)), Qt::QueuedConnection);
    connect(p_ui, SIGNAL(send_position_action(int, double, int, int)), this, SLOT(receive_position_action(int, double, int, int)), Qt::QueuedConnection);

    connect(td, SIGNAL(send_WTdata(CThostFtdcOrderField)), this, SLOT(receive_WT_data(CThostFtdcOrderField)));
    connect(td, SIGNAL(send_CJdata(CThostFtdcTradeField)), this, SLOT(receive_CJ_data(CThostFtdcTradeField)));

    qRegisterMetaType< trading_table_row_UI>("trading_table_row_UI");
    connect(this, SIGNAL(send_add_trading_table_row(trading_table_row_UI)), p_ui, SLOT(reveive_add_trading_table_row(trading_table_row_UI)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_update_trading_table_row(trading_table_row_UI)), p_ui, SLOT(reveive_update_trading_table_row(trading_table_row_UI)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_delete_trading_table_rows(QString)), p_ui, SLOT(reveive_delete_trading_table_rows(QString)), Qt::QueuedConnection);

    qRegisterMetaType< position_table_row_UI>("position_table_row_UI");
    connect(this, SIGNAL(send_add_position_table_row(position_table_row_UI)), p_ui, SLOT(reveive_add_position_table_row(position_table_row_UI)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_update_position_table_row(position_table_row_UI)), p_ui, SLOT(reveive_update_position_table_row(position_table_row_UI)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_update_position_table_days(position_table_row_UI)), p_ui, SLOT(reveive_update_position_table_days(position_table_row_UI)), Qt::QueuedConnection);
    connect(this, SIGNAL(send_delete_position_table_row(QString)), p_ui, SLOT(reveive_delete_position_table_row(QString)), Qt::QueuedConnection);
    connect(p_ui, SIGNAL(send_position_edit(int, bool, position_table_row_UI)), this, SLOT(receive_position_edit(int, bool, position_table_row_UI)), Qt::QueuedConnection);


    qRegisterMetaType< history_position_status>("history_position_status");
    connect(this, SIGNAL(send_add_history_table_row(history_position_status)), p_ui, SLOT(receive_add_history_table_row(history_position_status)), Qt::QueuedConnection);

    if (td->loginFlag)
    {
        //判断持仓list是否有数据，有数据显示出来。
        QList<position_status>::iterator position_item;

        //更新各个持仓状态
        for (position_item = position_list.begin(); position_item != position_list.end(); position_item++)
        {
            if (position_item->close_position_status != 0)
            {
                position_item->button.button_text = "平仓";
                position_item->button.enbale = true;
                position_item->close_position_status = 0;
            }
            position_status new_row = *position_item;
            position_table_row_UI row_UI;

            row_UI.index = QString::number(new_row.index);
            row_UI.direction_spd = (new_row.spd_direction == POSITION_BUY) ? "buy" : "sell";
            row_UI.direction_A = (new_row.direction_A == POSITION_BUY) ? "buy" : "sell";
            row_UI.direction_B = (new_row.direction_B == POSITION_BUY) ? "buy" : "sell";
            row_UI.vol_spd = QString::number(new_row.spd_vol);
            row_UI.vol_A = QString::number(new_row.vol_A);
            row_UI.vol_B = QString::number(new_row.vol_B);
            row_UI.instrumentA = new_row.instrumentA;
            row_UI.instrumentB = new_row.instrumentB;
            row_UI.profit = QString::number(new_row.profit);
            row_UI.profit_ticks = QString::number(new_row.profit_ticks);
            row_UI.cost = QString::number(new_row.cost_A, 'f', 1) + "-" +
                QString::number(new_row.cost_B, 'f', 1) + "*" + QString::number(beta, 'f', 1) + "=" + QString::number(new_row.cost, 'f', 1);

            row_UI.position_time = new_row.position_time;
            row_UI.button = new_row.button;

            //持仓天数判断
            QString str = "2021-" + new_row.position_time;
            QDateTime time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

            QDateTime compare_today_time = QDateTime::currentDateTime();
            compare_today_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));
            int delta_secs_now = QDateTime::currentDateTime().secsTo(compare_today_time);

            QDateTime compare_time = QDateTime::currentDateTime();

            if (delta_secs_now > 0) //在21点以前
            {
                //判断是不是周一，周一要减3天
                QString weekday = compare_time.toString("ddd");
                if (weekday == "星期一")
                {
                    compare_time = compare_time.addDays(-3); //减一天
                }
                else
                {
                    compare_time = compare_time.addDays(-1); //减一天
                }
            }

            compare_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));

            int delta_secs = time.secsTo(compare_time);

            if (delta_secs > 0) //昨仓算算天数就好
            {
                int days = (delta_secs / (24 * 60 * 60)) + 1;
                row_UI.potions_days = QString::number(days) + "天";
            }
            else
            {
                row_UI.potions_days = "当天";
            }

            emit send_add_position_table_row(row_UI);
            emit send_log_message("新增持仓" + row_UI.index);
        }
        emit send_log_message("初始化完成...");
        emit send_auto_process_start(); //开启自动化交易线程
    }
    else
    {
        emit send_log_message("未登录交易服务器，无法交易！！！");
    }

    //data_process_thread = new std::thread(&pair_trading_process::thread_data_process_fun1, this);

}


void pair_trading_process::update_price_ui(void)
{
    QStringList group_list, group_list2;
    QStringList a_list;
    QStringList b_list;
    double A_price_return_3min, A_price_return_5min, A_price_return_10min, A_price_return_30min;
    QString A_return_3min, A_return_5min, A_return_10min, A_return_30min;
    QDateTime time = QDateTime::currentDateTime();
    group_list << QString::number(group_price.delta_AaBa_higest) << QString::number(group_price.delta_AbBb_higest)\
        << QString::number(group_price.delta_AaBa_lowest) << QString::number(group_price.delta_AbBb_lowest)\
        << QString::number(group_price.delta_AaBa_average, 10, 2) << QString::number(group_price.delta_AbBb_average, 10, 2)\
        << QString::number(group_price.delta_AaBa_beta) << QString::number(group_price.delta_AbBb_beta) \
        << QString::number(group_price.delta_AaBa_beta_series.size()) << QString::number(group_price.delta_AbBb_beta_series.size()) \
        << QString::number(pair_setting.sample_series_points);

    group_list2 << QString::number(group_price.delta_rival_AaBb_higest) << QString::number(group_price.delta_rival_AbBa_higest)\
        << QString::number(group_price.delta_rival_AaBb_lowest) << QString::number(group_price.delta_rival_AbBa_lowest)\
        << QString::number(group_price.delta_rival_AaBb_average, 10, 2) << QString::number(group_price.delta_rival_AbBa_average, 10, 2)\
        << QString::number(group_price.delta_rival_AaBb_beta) << QString::number(group_price.delta_rival_AbBa_beta) \
        << QString::number(group_price.delta_rival_AaBb_beta_series.size()) << QString::number(group_price.delta_rival_AbBa_beta_series.size()) \
        << QString::number(pair_setting.sample_series_points);

    int size_a = A_price.last_price_series.size();
    if (size_a > 360) //3min
    {
        A_price_return_3min = ((A_price.last_price_series.at(size_a - 1) - A_price.last_price_series.at(size_a - 360)) / A_price.last_price_series.at(size_a - 360)) * 100;
        A_return_3min = QString::number(A_price_return_3min, 10, 2) + "%";
    }
    else
    {
        A_return_3min = "wait... ";
    }

    if (size_a > 600) //5min
    {
        A_price_return_5min = ((A_price.last_price_series.at(size_a - 1) - A_price.last_price_series.at(size_a - 600)) / A_price.last_price_series.at(size_a - 600)) * 100;
        A_return_5min = QString::number(A_price_return_5min, 10, 2) + "%";
    }
    else
    {
        A_return_5min = "wait... ";
    }

    if (size_a > 1200) //10min
    {
        A_price_return_10min = ((A_price.last_price_series.at(size_a - 1) - A_price.last_price_series.at(size_a - 1200)) / A_price.last_price_series.at(size_a - 1200)) * 100;
        A_return_10min = QString::number(A_price_return_10min, 10, 2) + "%";
    }
    else
    {
        A_return_10min = "wait... ";
    }

    if (size_a > 3600)
    {
        A_price_return_30min = ((A_price.last_price_series.at(size_a - 1) - A_price.last_price_series.at(size_a - 3600)) / A_price.last_price_series.at(size_a - 3600)) * 100;
        A_return_30min = QString::number(A_price_return_30min, 10, 2) + "%";
    }
    else
    {
        A_return_30min = "wait... ";
    }

    QString xmin_delta_ticks = QString::number(A_price.delta_ticks_in_xmins) + "tick";

    a_list << QString::number(A_price.ask1_vol) << QString::number(A_price.ask1)\
        << QString::number(A_price.last) << QString::number(A_price.bid1)\
        << QString::number(A_price.bid1_vol) << QString::number(A_price.up)\
        << QString::number(A_price.down) << A_return_3min << A_return_5min
        << A_return_10min << A_return_30min << xmin_delta_ticks << QString::number(A_price.price_volatility, 10, 2) + "% ";

    b_list << QString::number(B_price.ask1_vol) << QString::number(B_price.ask1)\
        << QString::number(B_price.last) << QString::number(B_price.bid1)\
        << QString::number(B_price.bid1_vol) << QString::number(B_price.up)\
        << QString::number(B_price.down);

    emit send_price_value(group_list, a_list, b_list, group_list2);
    emit send_charts_data(group_price.delta_AbBb_beta, group_price.delta_AbBb_higest + HYstruct_B.hyds, group_price.delta_AbBb_lowest - HYstruct_B.hyds, \
        group_price.delta_AaBa_beta, group_price.delta_AaBa_higest + HYstruct_B.hyds, group_price.delta_AaBa_lowest - HYstruct_B.hyds, time); //发送最新数据到界面
    emit send_charts_data2(group_price.delta_rival_AbBa_beta, group_price.delta_rival_AbBa_higest + HYstruct_B.hyds, group_price.delta_rival_AbBa_lowest - HYstruct_B.hyds, \
        group_price.delta_rival_AaBb_beta, group_price.delta_rival_AaBb_higest + HYstruct_B.hyds, group_price.delta_rival_AaBb_lowest - HYstruct_B.hyds, time); //发送最新数据到界面
}

void pair_trading_process::group_price_update()
{
    group_price.delta_AaBa = A_price.ask1 - B_price.ask1;
    group_price.delta_AbBb = A_price.bid1 - B_price.bid1;

    group_price.delta_AaBa_beta = A_price.ask1 - B_price.ask1 * beta;
    group_price.delta_AbBb_beta = A_price.bid1 - B_price.bid1 * beta;

    //更新序列数据

    while (group_price.delta_AaBa_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_AaBa_beta_series.removeFirst();
    }

    group_price.delta_AaBa_beta_series.append(group_price.delta_AaBa_beta);

    if (group_price.delta_AaBa_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_AaBa_beta_series_full = true;
    }
    else
    {
        group_price.delta_AaBa_beta_series_full = false;
    }


    while (group_price.delta_AbBb_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_AbBb_beta_series.removeFirst();
    }
    group_price.delta_AbBb_beta_series.append(group_price.delta_AbBb_beta);

    if (group_price.delta_AbBb_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_AbBb_beta_series_full = true;
    }
    else
    {
        group_price.delta_AbBb_beta_series_full = false;
    }

    //对手价
    group_price.delta_rival_AaBb = A_price.ask1 - B_price.bid1;
    group_price.delta_rival_AbBa = A_price.bid1 - B_price.ask1;

    group_price.delta_rival_AaBb_beta = A_price.ask1 - B_price.bid1 * beta;
    group_price.delta_rival_AbBa_beta = A_price.bid1 - B_price.ask1 * beta;

    //更新序列数据

    while (group_price.delta_rival_AaBb_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_rival_AaBb_beta_series.removeFirst();
    }

    group_price.delta_rival_AaBb_beta_series.append(group_price.delta_rival_AaBb_beta);

    if (group_price.delta_rival_AaBb_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_rival_AaBb_beta_series_full = true;
    }
    else
    {
        group_price.delta_rival_AaBb_beta_series_full = false;
    }


    while (group_price.delta_rival_AbBa_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_rival_AbBa_beta_series.removeFirst();
    }
    group_price.delta_rival_AbBa_beta_series.append(group_price.delta_rival_AbBa_beta);

    if (group_price.delta_rival_AbBa_beta_series.size() >= pair_setting.sample_series_points)
    {
        group_price.delta_rival_AbBa_beta_series_full = true;
    }
    else
    {
        group_price.delta_rival_AbBa_beta_series_full = false;
    }

    //计算出最大最小平均值
    //update A序列
    double max = -1000000;
    double min = 1000000;
    double average = 0;
    double total = 0;
    for each (double priceA in group_price.delta_AaBa_beta_series)
    {
        if (priceA > max)
        {
            max = priceA;
        }

        if (priceA < min)
        {
            min = priceA;
        }
        total += priceA;
    }
    average = total / group_price.delta_AaBa_beta_series.size();
    group_price.delta_AaBa_higest = max;
    group_price.delta_AaBa_lowest = min;
    group_price.delta_AaBa_average = average;

    //update B序列
    max = -1000000;
    min = 1000000;
    average = 0;
    total = 0;
    for each (double priceA in group_price.delta_AbBb_beta_series)
    {
        if (priceA > max)
        {
            max = priceA;
        }

        if (priceA < min)
        {
            min = priceA;
        }
        total += priceA;
    }
    average = total / group_price.delta_AaBa_beta_series.size();
    group_price.delta_AbBb_higest = max;
    group_price.delta_AbBb_lowest = min;
    group_price.delta_AbBb_average = average;

    //对手价
    max = -1000000;
    min = 1000000;
    average = 0;
    total = 0;
    for each (double priceA in group_price.delta_rival_AaBb_beta_series)
    {
        if (priceA > max)
        {
            max = priceA;
        }

        if (priceA < min)
        {
            min = priceA;
        }
        total += priceA;
    }
    average = total / group_price.delta_rival_AaBb_beta_series.size();
    group_price.delta_rival_AaBb_higest = max;
    group_price.delta_rival_AaBb_lowest = min;
    group_price.delta_rival_AaBb_average = average;

    //update B序列
    max = -1000000;
    min = 1000000;
    average = 0;
    total = 0;
    for each (double priceA in group_price.delta_rival_AbBa_beta_series)
    {
        if (priceA > max)
        {
            max = priceA;
        }

        if (priceA < min)
        {
            min = priceA;
        }
        total += priceA;
    }
    average = total / group_price.delta_rival_AaBb_beta_series.size();
    group_price.delta_rival_AbBa_higest = max;
    group_price.delta_rival_AbBa_lowest = min;
    group_price.delta_rival_AbBa_average = average;

}

void pair_trading_process::receive_hq_data(CThostFtdcDepthMarketDataField MarketData)
{
    if (MarketData.AskPrice1 < 0 || MarketData.AskPrice1 > 10000000 || MarketData.BidPrice1 < 0 || MarketData.BidPrice1 > 10000000)
    {
        return; //避免开盘的时候收到异常行情
    }
    if (MarketData.InstrumentID == this->InsrumentA)
    {
        A_price.bid1 = MarketData.BidPrice1;
        A_price.bid1_vol = MarketData.BidVolume1;
        A_price.ask1 = MarketData.AskPrice1;
        A_price.ask1_vol = MarketData.AskVolume1;
        A_price.last = MarketData.LastPrice;
        A_price.preClosePrice = MarketData.PreClosePrice;
        A_price.OpenPrice = MarketData.OpenPrice;
        A_price.up = MarketData.UpperLimitPrice;
        A_price.down = MarketData.LowerLimitPrice;
        //更新挂单数量序列
        int serires_size = A_price.bid1_vol_series.size();
        int remove_data_bid;
        int remove_data_ask;

        while (serires_size >= pair_setting.sample_series_points)
        {
            remove_data_bid = A_price.bid1_vol_series[0];
            A_price.bid1_vol_series.removeFirst();
            A_price.bid1_vol_series_median.removeOne(remove_data_bid);

            remove_data_ask = A_price.ask1_vol_series[0];
            A_price.ask1_vol_series.removeFirst();
            A_price.ask1_vol_series_median.removeOne(remove_data_ask);
            serires_size = A_price.bid1_vol_series.size();
        }
        A_price.bid1_vol_series.append(A_price.bid1_vol);
        A_price.ask1_vol_series.append(A_price.ask1_vol);
        serires_size = A_price.bid1_vol_series_median.size();

        if (serires_size == 0)
        {
            A_price.bid1_vol_series_median.append(A_price.bid1_vol);
            A_price.ask1_vol_series_median.append(A_price.ask1_vol);
        }
        else
        {
            for (int i = 0; i < serires_size; i++)
            {
                if (A_price.bid1_vol < A_price.bid1_vol_series_median[i])
                {
                    A_price.bid1_vol_series_median.insert(i, A_price.bid1_vol);
                    break;
                }
                if (i == serires_size - 1)
                {
                    A_price.bid1_vol_series_median.insert(serires_size, A_price.bid1_vol);
                }
            }

            for (int i = 0; i < serires_size; i++)
            {
                if (A_price.ask1_vol < A_price.ask1_vol_series_median[i])
                {
                    A_price.ask1_vol_series_median.insert(i, A_price.ask1_vol);
                    break;
                }
                if (i == serires_size - 1)
                {
                    A_price.ask1_vol_series_median.insert(serires_size, A_price.ask1_vol);
                }
            }
        }

        serires_size = A_price.bid1_vol_series_median.size() / 2;
        A_price.median_bid1_vol = A_price.bid1_vol_series_median[serires_size];
        A_price.median_ask1_vol = A_price.ask1_vol_series_median[serires_size];

        serires_size = A_price.bid1_vol_series_median.size() / 4;
        A_price.quarter_bid1_vol = A_price.bid1_vol_series_median[serires_size];
        A_price.quarter_ask1_vol = A_price.ask1_vol_series_median[serires_size];

        A_price.last_price_series.append(A_price.last);
        if (A_price.last_price_series.size() > 100000)
        {
            A_price.last_price_series.removeFirst();
        }
        if (A_price.last_price_series.size() > pair_setting.sample_series_points)
        {
            A_price.delta_ticks_in_xmins = ((A_price.last_price_series.at(A_price.last_price_series.size() - 1) -
                A_price.last_price_series.at(A_price.last_price_series.size() - pair_setting.sample_series_points)) / (HYstruct_A.hyds)) + 0.5;
        }
        else
        {
            A_price.delta_ticks_in_xmins = ((A_price.last_price_series.at(A_price.last_price_series.size() - 1) -
                A_price.last_price_series.at(0)) / (HYstruct_A.hyds)) + 0.5;
        }


        //最后更新flag
        update_flag |= 1;

    }
    if (MarketData.InstrumentID == this->InsrumentB)
    {
        B_price.bid1 = MarketData.BidPrice1;
        B_price.bid1_vol = MarketData.BidVolume1;
        B_price.ask1 = MarketData.AskPrice1;
        B_price.ask1_vol = MarketData.AskVolume1;
        B_price.last = MarketData.LastPrice;
        B_price.preClosePrice = MarketData.PreClosePrice;
        B_price.OpenPrice = MarketData.OpenPrice;
        B_price.up = MarketData.UpperLimitPrice;
        B_price.down = MarketData.LowerLimitPrice;

        //更新挂单数量序列
        int serires_size = B_price.bid1_vol_series.size();
        int remove_data_bid;
        int remove_data_ask;

        while (serires_size >= pair_setting.sample_series_points)
        {
            remove_data_bid = B_price.bid1_vol_series[0];
            B_price.bid1_vol_series.removeFirst();
            B_price.bid1_vol_series_median.removeOne(remove_data_bid);

            remove_data_ask = B_price.ask1_vol_series[0];
            B_price.ask1_vol_series.removeFirst();
            B_price.ask1_vol_series_median.removeOne(remove_data_ask);
            serires_size = B_price.bid1_vol_series.size();
        }
        B_price.bid1_vol_series.append(B_price.bid1_vol);
        B_price.ask1_vol_series.append(B_price.ask1_vol);
        serires_size = B_price.bid1_vol_series_median.size();

        if (serires_size == 0)
        {
            B_price.bid1_vol_series_median.append(B_price.bid1_vol);
            B_price.ask1_vol_series_median.append(B_price.ask1_vol);
        }
        else
        {
            for (int i = 0; i < serires_size; i++)
            {
                if (B_price.bid1_vol < B_price.bid1_vol_series_median[i])
                {
                    B_price.bid1_vol_series_median.insert(i, B_price.bid1_vol);
                    break;
                }
                if (i == serires_size - 1)
                {
                    B_price.bid1_vol_series_median.insert(serires_size, B_price.bid1_vol);
                }
            }

            for (int i = 0; i < serires_size; i++)
            {
                if (B_price.ask1_vol < B_price.ask1_vol_series_median[i])
                {
                    B_price.ask1_vol_series_median.insert(i, B_price.ask1_vol);
                    break;
                }
                if (i == serires_size - 1)
                {
                    B_price.ask1_vol_series_median.insert(serires_size, B_price.ask1_vol);
                }
            }
        }

        serires_size = B_price.bid1_vol_series_median.size() / 2;
        B_price.median_bid1_vol = B_price.bid1_vol_series_median[serires_size];
        B_price.median_ask1_vol = B_price.ask1_vol_series_median[serires_size];

        serires_size = B_price.bid1_vol_series_median.size() / 4;
        B_price.quarter_bid1_vol = B_price.bid1_vol_series_median[serires_size];
        B_price.quarter_ask1_vol = B_price.ask1_vol_series_median[serires_size];

        B_price.last_price_series.append(B_price.last);
        if (B_price.last_price_series.size() > 100000)
        {
            B_price.last_price_series.removeFirst();
        }

        //最后更新flag
        update_flag |= 2;
    }

    if (update_flag == 3 || (update_flag_first && update_flag != 0)) //确保有数据，且每次更新都更新
    {
        update_flag_first = true;
        update_flag = 0; // update flag
        //todo 统计耗时。
        group_price_update(); // 更新价格信息
        trading_process_MD_data();//使用最新的市场数据和价格数据更新交易状态
        position_process_MD_data(); //先处理交易，再处理持仓
        update_price_ui();
    }
}

void pair_trading_process::update_trading_UI(trading_status ts)
{
    //更新B合约行
    trading_table_row_UI row_B;

    row_B.index = QString::number(ts.index);
    row_B.sub_index = QString::number(ts.instrumentB_trading_list[0].sub_index);
    row_B.instrument = ts.instrumentB_trading_list[0].instrument;
    row_B.open_or_close = (ts.instrumentB_trading_list[0].open_or_close == OPEN_POSITION) ? "open" : "close";
    row_B.direction = (ts.instrumentB_trading_list[0].direction == POSITION_BUY) ? "buy" : "sell";

    if (ts.instrumentB_trading_list[0].status_step != 0)
    {
        row_B.order_price = QString::number(ts.instrumentB_trading_list[0].order_price);
        row_B.delta_latest_order = QString::number(ts.instrumentB_trading_list[0].delta_latest_order) + " tick";
        row_B.order_vol = QString::number(ts.instrumentB_trading_list[0].order_vol);
    }
    else
    {
        row_B.order_price = "-";
        row_B.delta_latest_order = "-";
        row_B.order_vol = "-";
    }
    row_B.finished_vol = QString::number(ts.instrumentB_trading_list[0].finished_vol);
    row_B.target_vol = QString::number(ts.target_vol);
    row_B.target_price = QString::number(ts.target_price);
    row_B.latest_spd_price = QString::number(ts.latest_spd_price);
    if (ts.instrumentB_trading_list[0].status_step > 1)
    {
        row_B.order_time = ts.instrumentB_trading_list[0].order_time;
    }
    else
    {
        row_B.order_time = "-";
    }
    row_B.status = ts.instrumentB_trading_list[0].status;
    row_B.button_1 = ts.instrumentB_trading_list[0].button_1;
    row_B.button_2 = ts.instrumentB_trading_list[0].button_2;
    emit send_update_trading_table_row(row_B);

    //更新A合约，如果有A合约
    QList<instrumentA_trading_status>::iterator insA_item;
    for (insA_item = ts.instrumentA_trading_list.begin(); insA_item != ts.instrumentA_trading_list.end(); insA_item++)
    {
        trading_table_row_UI row_A;

        row_A.index = QString::number(ts.index);
        row_A.sub_index = QString::number(insA_item->sub_index);
        row_A.instrument = insA_item->instrument;
        row_A.open_or_close = (insA_item->open_or_close == OPEN_POSITION) ? "open" : "close";
        row_A.direction = (insA_item->direction == POSITION_BUY) ? "buy" : "sell";

        if (insA_item->status_step != 0)
        {
            row_A.order_price = QString::number(insA_item->order_price);
            row_A.delta_latest_order = QString::number(insA_item->delta_latest_order) + " tick";
            row_A.order_vol = QString::number(insA_item->order_vol);
            row_A.order_time = insA_item->order_time;
        }
        else
        {
            row_A.order_price = "-";
            row_A.delta_latest_order = "-";
            row_A.order_vol = "-";
            row_A.order_time = "-";
        }
        row_A.finished_vol = QString::number(insA_item->finished_vol);
        row_A.target_vol = QString::number(ts.target_vol);
        row_A.target_price = QString::number(ts.target_price);
        row_A.latest_spd_price = QString::number(ts.latest_spd_price);
        row_A.status = insA_item->status;
        row_A.button_1 = insA_item->button_1;
        row_A.button_2 = insA_item->button_2;
        emit send_update_trading_table_row(row_A);
    }
}

void pair_trading_process::receive_buy_event(QList<double> data)
{
    if (!td->loginFlag)  //如果交易服务器未登录或者断开，无法交易
    {
        emit send_log_message("交易服务器断开，无法操作！！！");
        return;
    }

    int direction = data.value(0) + 0.01; // 0 : buy other: sell
    int B_back_tick = data.value(1) + 0.01; // 0: no other: yes
    double dream_price = data.value(2);
    int vol = data.value(3) + 0.01;
    int A_price_type = data.value(4) + 0.01;

    // 新增交易操作
    trading_status new_trading = init_new_trading_status();
    if (direction) //sell
    {
        new_trading.instrumentB_trading_list[0].direction = POSITION_BUY;
        new_trading.latest_spd_price = group_price.delta_AbBb_beta;
        new_trading.group_direction = POSITION_SELL;
    }
    else //buy
    {
        new_trading.instrumentB_trading_list[0].direction = POSITION_SELL;
        new_trading.latest_spd_price = group_price.delta_AaBa_beta;
        new_trading.group_direction = POSITION_BUY;
    }


    new_trading.B_price_type = B_back_tick;
    new_trading.A_price_type = A_price_type;

    new_trading.target_price = dream_price;
    new_trading.target_vol = vol;

    new_trading.target_price = dream_price;
    new_trading.target_vol = new_trading.target_vol; //todo 加入系数进行计算
    new_trading.instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("未下单");
    new_trading.instrumentB_trading_list[0].button_1.enbale = false;
    new_trading.instrumentB_trading_list[0].button_2.button_text = QString::fromUtf8("停止");
    new_trading.instrumentB_trading_list[0].button_2.enbale = true;
    new_trading.op_cl = OPEN_POSITION;
    new_trading.instrumentB_trading_list[0].open_or_close = OPEN_POSITION;
    new_trading.instrumentB_trading_list[0].status_step = 1; //进入等待报单状态，否则无法交易

    trading_list.append(new_trading);

    trading_table_row_UI row;
    row.index = QString::number(new_trading.index);
    row.sub_index = QString::number(new_trading.instrumentB_trading_list[0].sub_index);
    row.instrument = new_trading.instrumentB_trading_list[0].instrument;
    row.open_or_close = (new_trading.instrumentB_trading_list[0].open_or_close == OPEN_POSITION) ? "open" : "close";
    row.direction = (new_trading.instrumentB_trading_list[0].direction == POSITION_BUY) ? "buy" : "sell";
    row.order_price = "-";
    row.delta_latest_order = "-";
    row.order_vol = "-";
    row.finished_vol = "0";
    row.target_vol = QString::number(new_trading.target_vol);
    row.target_price = QString::number(dream_price);
    row.latest_spd_price = QString::number(new_trading.latest_spd_price);
    row.order_time = "-";
    row.status = new_trading.instrumentB_trading_list[0].status;
    row.button_1 = new_trading.instrumentB_trading_list[0].button_1;
    row.button_2 = new_trading.instrumentB_trading_list[0].button_2;
    if (new_trading.B_price_type == 1)
    {
        row.price_type = "B退|";
    }
    else if (new_trading.B_price_type == 2)
    {
        row.price_type = "B对|";
    }
    else
    {
        row.price_type = "B正|";
    }

    if (new_trading.A_price_type == 0)
    {
        row.price_type = row.price_type + "A目";
    }
    else
    {
        row.price_type = row.price_type + "A对";
    }

    emit send_add_trading_table_row(row);
    emit send_log_message("新增交易：" + row.index);

    statistic_data.spd_open_times++;
}

bool pair_trading_process::judge_whther_start_order(trading_status trading_item)
{
    bool ret = false;

    POSITION_DIRECTION group_direction = trading_item.group_direction;
    double target_price = trading_item.target_price;
    QString trading_index = QString::number(trading_item.index);
    int B_price_type = trading_item.B_price_type;

    //1.判断交易时间
    if (pair_setting.enable_order_start_time)
    {
        QTime open_time = QTime::fromString("09:00:00", "hh:mm:ss");
        QTime close_time = QTime::fromString("11:30:00", "hh:mm:ss");
        QTime now_time = QTime::currentTime();

        int delta_to_open_sec = now_time.secsTo(open_time);
        int delta_to_close_sec = now_time.secsTo(close_time);

        if ((delta_to_open_sec > (-(pair_setting.order_delay_time * 60)) && delta_to_open_sec < 0)
            || (delta_to_close_sec < (pair_setting.order_before_end_time * 60) && delta_to_close_sec > 0))
        {
            emit send_log_message(trading_index + "不在设置交易时间内！请退出交易~~~");
            return ret; //时间不满足直接退出
        }

        open_time = QTime::fromString("13:30:00", "hh:mm:ss");
        close_time = QTime::fromString("15:00:00", "hh:mm:ss");
        now_time = QTime::currentTime();

        delta_to_open_sec = now_time.secsTo(open_time);
        delta_to_close_sec = now_time.secsTo(close_time);

        if ((delta_to_open_sec > (-(pair_setting.order_delay_time * 60)) && delta_to_open_sec < 0)
            || (delta_to_close_sec < (pair_setting.order_before_end_time * 60) && delta_to_close_sec > 0))
        {
            emit send_log_message(trading_index + "不在设置交易时间内！请退出交易~~~");
            return ret; //时间不满足直接退出
        }

        open_time = QTime::fromString("21:00:00", "hh:mm:ss");
        now_time = QTime::currentTime();

        delta_to_open_sec = now_time.secsTo(open_time);

        if (delta_to_open_sec > (-(pair_setting.order_delay_time * 60)) && delta_to_open_sec < 0)
        {
            emit send_log_message(trading_index + "不在设置交易时间内！请退出交易~~~");
            return ret; //时间不满足直接退出
        }

    }

    if (pair_setting.is_B_cancel_times_OK) //判断B撤单次数，次数不足直接退出
    {
        if (statistic_data.instrumentB_canceled_order_times > 450)
        {
            ret = false;
            emit send_log_message(trading_index + "B撤单次数不足，停止下单！！！");
            return ret;
        }
    }

    //判断市场数据
    if (B_price_type != 2)
    {
        int buy_size = group_price.delta_AaBa_beta_series.size();
        int sell_size = group_price.delta_AbBb_beta_series.size();
        if (group_direction == POSITION_BUY)
        {
            if (group_price.delta_AaBa_beta <= (target_price + 0.00001))
            {
                //判断历史数据数量是否足够
                if (buy_size > pair_setting.order_total_points)
                {
                    int good_points = 0;
                    for (int i = 1; i <= pair_setting.order_total_points; i++)
                    {
                        if (group_price.delta_AaBa_beta_series[buy_size - i] <= (target_price + 0.00001)) //double 比较有精度误差
                        {
                            good_points++;
                        }
                    }
                    if (good_points >= pair_setting.order_points)
                    {
                        ret = true;
                    }
                }
            }
        }
        else //卖
        {
            if (group_price.delta_AbBb_beta >= (target_price - 0.00001))
            {
                //判断历史数据数量是否足够
                if (sell_size > pair_setting.order_total_points)
                {
                    int good_points = 0;
                    for (int i = 1; i <= pair_setting.order_total_points; i++)
                    {
                        if (group_price.delta_AbBb_beta_series[buy_size - i] >= (target_price - 0.00001))//double 比较有精度误差
                        {
                            good_points++;
                        }
                    }
                    if (good_points >= pair_setting.order_points)
                    {
                        ret = true;
                    }
                }
            }
        }

        //判断可选参数设置
        if (ret == true)
        {
            if (pair_setting.enable_optional_options)
            {
                //a.判断平均价差
                if (pair_setting.enable_optional_A)
                {
                    if (group_price.delta_AaBa_beta_series_full == false)
                    {
                        ret = false;
                        emit send_log_message(trading_index + "阻止下单，等待采样序列！");
                    }
                    else
                    {
                        if (group_direction == POSITION_BUY)
                        {
                            if (group_price.delta_AaBa_average > (target_price + (HYstruct_B.hyds * pair_setting.optional_A_value)))
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，由于平均价格未达到条件");
                            }
                        }
                        else //sell
                        {
                            if (group_price.delta_AbBb_average < (target_price - (HYstruct_B.hyds * pair_setting.optional_A_value)))
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，由于平均价格未达到条件");
                            }
                        }
                    }

                }

                //b.判断实时挂单量
                if (ret == true)
                {
                    if (pair_setting.enable_optional_B)
                    {
                        if (group_direction == POSITION_BUY)
                        {
                            if (A_price.ask1_vol <= B_price.ask1_vol)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，A实时挂单 <= B实时挂单 ");
                            }
                        }
                        else
                        {
                            if (A_price.bid1_vol <= B_price.bid1_vol)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，A实时挂单 <= B实时挂单 ");
                            }
                        }
                    }
                }

                //c.判断挂单量中位数
                if (ret == true)
                {
                    if (pair_setting.enable_optional_C)
                    {
                        if (group_price.delta_AaBa_beta_series_full == false)
                        {
                            ret = false;
                            emit send_log_message(trading_index + "阻止下单，等待采样序列！");
                        }
                        else
                        {
                            if (group_direction == POSITION_BUY)
                            {
                                if (A_price.ask1_vol < A_price.median_ask1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，A实时挂单 < X分钟A挂单量中位数！ ");
                                }
                            }
                            else
                            {
                                if (A_price.bid1_vol < A_price.median_bid1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，A实时挂单 < X分钟A挂单量中位数！ ");
                                }
                            }
                        }
                    }
                }

                //d.判断挂单量中位数
                if (ret == true)
                {
                    if (pair_setting.enable_optional_D)
                    {
                        if (group_price.delta_AaBa_beta_series_full == false)
                        {
                            ret = false;
                            emit send_log_message(trading_index + "阻止下单，等待采样序列！");
                        }
                        else
                        {
                            if (group_direction == POSITION_BUY)
                            {
                                if (A_price.median_ask1_vol <= B_price.median_ask1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，X分钟,A挂单量中位数 < B挂单量中位数 ");
                                }
                            }
                            else
                            {
                                if (A_price.median_bid1_vol <= B_price.median_bid1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，X分钟,A挂单量中位数 < B挂单量中位数 ");
                                }
                            }
                        }
                    }
                }

                //e.判断A价格波动率
                if (ret == true)
                {
                    if (pair_setting.enable_optional_E)
                    {
                        if (A_price.price_volatility > pair_setting.optional_E_value)
                        {
                            ret = false;
                            emit send_log_message(trading_index + "阻止下单，波动率超过阈值： " + QString::number(pair_setting.optional_E_value));
                        }
                    }
                }

                //f.X分钟A的价格往不利的方向变动超过Xticks
                if (ret == true)
                {
                    if (pair_setting.enable_optional_F)
                    {
                        if (group_direction == POSITION_BUY)
                        {
                            //价格增长过快
                            if (A_price.delta_ticks_in_xmins > pair_setting.optional_F_value)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，X分钟,A价格增长过快 ");
                            }
                        }
                        else
                        {
                            //价格跌太快
                            if (A_price.delta_ticks_in_xmins < -pair_setting.optional_F_value)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，X分钟,A价格跌得过快 ");
                            }
                        }
                    }
                }
            }
        }
        if (ret == true)
        {
            //输出debug信息
            emit send_log_message(trading_index + "下单判断通过，新增下单：目标价格：" + QString::number(target_price));
        }
    }
    else
    {
        int buy_size = group_price.delta_rival_AaBb_beta_series.size();
        int sell_size = group_price.delta_rival_AbBa_beta_series.size();
        if (group_direction == POSITION_BUY)
        {
            if (group_price.delta_rival_AaBb_beta <= (target_price + 0.00001))
            {
                //判断历史数据数量是否足够
                if (buy_size > pair_setting.order_total_points)
                {
                    int good_points = 0;
                    for (int i = 1; i <= pair_setting.order_total_points; i++)
                    {
                        if (group_price.delta_rival_AaBb_beta_series[buy_size - i] <= (target_price + 0.00001)) //double 比较有精度误差
                        {
                            good_points++;
                        }
                    }
                    if (good_points >= pair_setting.order_points)
                    {
                        ret = true;
                    }
                }
            }
        }
        else //卖
        {
            if (group_price.delta_rival_AbBa_beta >= (target_price - 0.00001))
            {
                //判断历史数据数量是否足够
                if (sell_size > pair_setting.order_total_points)
                {
                    int good_points = 0;
                    for (int i = 1; i <= pair_setting.order_total_points; i++)
                    {
                        if (group_price.delta_rival_AbBa_beta_series[buy_size - i] >= (target_price - 0.00001))//double 比较有精度误差
                        {
                            good_points++;
                        }
                    }
                    if (good_points >= pair_setting.order_points)
                    {
                        ret = true;
                    }
                }
            }
        }

        //判断可选参数设置
        if (ret == true)
        {
            if (pair_setting.enable_optional_options)
            {
                //a.判断平均价差
                if (pair_setting.enable_optional_A)
                {
                    if (group_price.delta_AaBa_beta_series_full == false)
                    {
                        ret = false;
                        emit send_log_message(trading_index + "阻止下单，等待采样序列！");
                    }
                    else
                    {
                        if (group_direction == POSITION_BUY)
                        {
                            if (group_price.delta_rival_AaBb_average > (target_price + (HYstruct_B.hyds * pair_setting.optional_A_value)))
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，由于平均价格未达到条件");
                            }
                        }
                        else //sell
                        {
                            if (group_price.delta_rival_AbBa_average < (target_price - (HYstruct_B.hyds * pair_setting.optional_A_value)))
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，由于平均价格未达到条件");
                            }
                        }
                    }

                }

                //b.判断实时挂单量
                if (ret == true)
                {
                    if (pair_setting.enable_optional_B)
                    {
                        if (group_direction == POSITION_BUY)
                        {
                            if (A_price.ask1_vol <= B_price.bid1_vol)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，A实时挂单 <= B实时挂单 ");
                            }
                        }
                        else
                        {
                            if (A_price.bid1_vol <= B_price.ask1_vol)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，A实时挂单 <= B实时挂单 ");
                            }
                        }
                    }
                }

                //c.判断挂单量中位数
                if (ret == true)
                {
                    if (pair_setting.enable_optional_C)
                    {
                        if (group_price.delta_AaBa_beta_series_full == false)
                        {
                            ret = false;
                            emit send_log_message(trading_index + "阻止下单，等待采样序列！");
                        }
                        else
                        {
                            if (group_direction == POSITION_BUY)
                            {
                                if (A_price.ask1_vol < A_price.median_ask1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，A实时挂单 < X分钟A挂单量中位数！ ");
                                }
                            }
                            else
                            {
                                if (A_price.bid1_vol < A_price.median_bid1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，A实时挂单 < X分钟A挂单量中位数！ ");
                                }
                            }
                        }
                    }
                }

                //d.判断挂单量中位数
                if (ret == true)
                {
                    if (pair_setting.enable_optional_D)
                    {
                        if (group_price.delta_AaBa_beta_series_full == false)
                        {
                            ret = false;
                            emit send_log_message(trading_index + "阻止下单，等待采样序列！");
                        }
                        else
                        {
                            if (group_direction == POSITION_BUY)
                            {
                                if (A_price.median_ask1_vol <= B_price.median_ask1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，X分钟,A挂单量中位数 < B挂单量中位数 ");
                                }
                            }
                            else
                            {
                                if (A_price.median_bid1_vol <= B_price.median_bid1_vol)
                                {
                                    ret = false;
                                    emit send_log_message(trading_index + "阻止下单，X分钟,A挂单量中位数 < B挂单量中位数 ");
                                }
                            }
                        }
                    }
                }

                //e.判断A价格波动率
                if (ret == true)
                {
                    if (pair_setting.enable_optional_E)
                    {
                        if (A_price.price_volatility > pair_setting.optional_E_value)
                        {
                            ret = false;
                            emit send_log_message(trading_index + "阻止下单，波动率超过阈值： " + QString::number(pair_setting.optional_E_value));
                        }
                    }
                }

                //f.X分钟A的价格往不利的方向变动超过Xticks
                if (ret == true)
                {
                    if (pair_setting.enable_optional_F)
                    {
                        if (group_direction == POSITION_BUY)
                        {
                            //价格增长过快
                            if (A_price.delta_ticks_in_xmins > pair_setting.optional_F_value)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，X分钟,A价格增长过快 ");
                            }
                        }
                        else
                        {
                            //价格跌太快
                            if (A_price.delta_ticks_in_xmins < -pair_setting.optional_F_value)
                            {
                                ret = false;
                                emit send_log_message(trading_index + "阻止下单，X分钟,A价格跌得过快 ");
                            }
                        }
                    }
                }
            }
        }
        if (ret == true)
        {
            //输出debug信息
            emit send_log_message(trading_index + "下单判断通过，新增下单：目标价格：" + QString::number(target_price));
        }
    }

    return ret;
}

bool pair_trading_process::judge_whther_cancel_order(trading_status trading_item)
{
    bool is_B_at_first = false;
    QString trading_index = QString::number(trading_item.index);
    //1.判断交易时间
    if (pair_setting.enable_order_start_time)
    {

        QTime end_time = QTime::fromString("11:30:00", "hh:mm:ss");
        QTime start_time = end_time.addSecs(-pair_setting.order_delay_time * 60);
        QTime now_time = QTime::currentTime();

        int delta_to_start_sec = start_time.secsTo(now_time);
        int delta_to_end_sec = now_time.secsTo(end_time);

        if ((delta_to_start_sec > 0) &&
            (delta_to_end_sec > 0)) //时间在这个区间内
        {
            emit send_log_message(trading_index + "撤单，即将收盘！");
            return true; //时间不满足直接退出
        }

        end_time = QTime::fromString("15:00:00", "hh:mm:ss");
        start_time = end_time.addSecs(-pair_setting.order_delay_time * 60);
        now_time = QTime::currentTime();

        delta_to_start_sec = start_time.secsTo(now_time);
        delta_to_end_sec = now_time.secsTo(end_time);

        if ((delta_to_start_sec > 0) &&
            (delta_to_end_sec > 0)) //时间在这个区间内
        {
            emit send_log_message(trading_index + "撤单，即将收盘！");
            return true; //时间不满足直接退出
        }

        end_time = QTime::fromString("23:30:00", "hh:mm:ss");
        start_time = end_time.addSecs(-pair_setting.order_delay_time * 60);
        now_time = QTime::currentTime();

        delta_to_start_sec = start_time.secsTo(now_time);
        delta_to_end_sec = now_time.secsTo(end_time);

        if ((delta_to_start_sec > 0) &&
            (delta_to_end_sec > 0)) //时间在这个区间内
        {
            emit send_log_message(trading_index + "撤单，即将收盘！");
            return true; //时间不满足直接退出
        }

    }
    //先判断B是否在最优档
    int buy_size = group_price.delta_AaBa_beta_series.size();
    int sell_size = group_price.delta_AbBb_beta_series.size();
    if (trading_item.group_direction == POSITION_BUY) //买
    {
        if (trading_item.instrumentB_trading_list[0].order_price <= B_price.ask1)
        {
            is_B_at_first = true;
        }
        if (is_B_at_first)
        {
            //2 判断价格
            if (group_price.delta_AaBa_beta > (trading_item.target_price + 0.00001))//double 比较有精度误差
            {
                //2判断历史数据数量是否足够
                if (buy_size > pair_setting.cancel_total_points)
                {
                    int bad_points = 0;
                    for (int i = 1; i <= pair_setting.cancel_total_points; i++)
                    {
                        if (group_price.delta_AaBa_beta_series[buy_size - i] > (trading_item.target_price + 0.00001))//double 比较有精度误差
                        {
                            bad_points++;
                        }
                    }
                    if (bad_points >= pair_setting.cancel_points)
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置2.");
                        return true;
                    }
                }

                //3.判断挂单量决定是否撤单，如果A挂单低于Q1和B.order则撤单 且B价格劣于挂单价
                if (pair_setting.cancel_by_vol)
                {
                    if ((A_price.ask1_vol < B_price.ask1_vol) || (A_price.ask1_vol < A_price.quarter_ask1_vol))
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置3.");
                        return true;
                    }
                }
            }



            //4.直接判断多少个tick
            if (pair_setting.cancel_by_ticks)
            {
                if (group_price.delta_AaBa_beta > trading_item.target_price + (HYstruct_B.hyds * pair_setting.cancel_by_ticks_value))
                {
                    emit send_log_message(trading_index + "撤单，符合撤单设置4.");
                    return true;
                }
            }

            //option 6 and 7
            if ((group_price.delta_AaBa_beta <= (trading_item.target_price + 0.00001)) &&
                (group_price.delta_AaBa_beta > (trading_item.target_price - HYstruct_B.hyds)))  //判断价格相等，在大于等于1个tick范围内
            {
                // 6.市场价差等于目标价差，且B位于最优档，且A的实时挂单量 < Q1，则撤单
                if (pair_setting.cancel_by_option_6)
                {
                    if (A_price.ask1_vol < A_price.quarter_ask1_vol)
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置6.");
                        return true;
                    }
                }

                //7.市场价差等于目标价差，且B位于最优档，且A的\n  实时挂单量 < B.order, 则撤单
                if (pair_setting.cancel_by_option_7)
                {
                    if (A_price.ask1_vol < B_price.ask1_vol)
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置7.");
                        return true;
                    }
                }
            }
        }
        else
        {
            //5.撤单由于B 的报价距离过大
            if (pair_setting.cancel_by_Bticks)
            {
                if (trading_item.instrumentB_trading_list[0].order_price >= B_price.last + (HYstruct_B.hyds * pair_setting.cancel_by_Bticks_value))
                {
                    emit send_log_message(trading_index + "撤单，符合撤单设置5.");
                    return true;
                }
            }
        }
    }
    else
    {
        if (trading_item.instrumentB_trading_list[0].order_price >= (B_price.bid1 - 0.00001))
        {
            is_B_at_first = true;
        }
        if (is_B_at_first)
        {
            //2 判断价格
            if (group_price.delta_AbBb_beta < (trading_item.target_price - 0.00001))//double 比较有精度误差
            {
                //2判断历史数据数量是否足够
                if (sell_size > pair_setting.cancel_total_points)
                {
                    int bad_points = 0;
                    for (int i = 1; i <= pair_setting.cancel_total_points; i++)
                    {
                        if (group_price.delta_AbBb_beta_series[buy_size - i] < (trading_item.target_price - 0.00001))//double 比较有精度误差
                        {
                            bad_points++;
                        }
                    }
                    if (bad_points >= pair_setting.cancel_points)
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置2.");
                        return true;
                    }
                }

                //3.判断挂单量决定是否撤单，如果A挂单低于Q1和B.order则撤单 且B价格劣于挂单价
                if (pair_setting.cancel_by_vol)
                {
                    if ((A_price.bid1_vol < B_price.bid1_vol) || (A_price.bid1_vol < A_price.quarter_bid1_vol))
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置3.");
                        return true;
                    }
                }
            }

            //4.直接判断多少个tick
            if (pair_setting.cancel_by_ticks)
            {
                if (group_price.delta_AbBb_beta < trading_item.target_price - (HYstruct_B.hyds * pair_setting.cancel_by_ticks_value))
                {
                    emit send_log_message(trading_index + "撤单，符合撤单设置4.");
                    return true;
                }
            }

            //option 6 and 7
            if ((group_price.delta_AaBa_beta >= (trading_item.target_price - 0.00001)) &&
                (group_price.delta_AaBa_beta < (trading_item.target_price + HYstruct_B.hyds)))  //判断价格相等，在大于等于1个tick范围内
            {
                // 6.市场价差等于目标价差，且B位于最优档，且A的实时挂单量 < Q1，则撤单
                if (pair_setting.cancel_by_option_6)
                {
                    if (A_price.bid1_vol < A_price.quarter_bid1_vol)
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置6.");
                        return true;
                    }
                }

                //7.市场价差等于目标价差，且B位于最优档，且A的\n  实时挂单量 < B.order, 则撤单
                if (pair_setting.cancel_by_option_7)
                {
                    if (A_price.bid1_vol < B_price.bid1_vol)
                    {
                        emit send_log_message(trading_index + "撤单，符合撤单设置7.");
                        return true;
                    }
                }
            }
        }
        else
        {
            //5.撤单由于B 的报价距离过大
            if (pair_setting.cancel_by_Bticks)
            {
                if (trading_item.instrumentB_trading_list[0].order_price <= B_price.last - (HYstruct_B.hyds * pair_setting.cancel_by_Bticks_value))
                {
                    emit send_log_message(trading_index + "撤单，符合撤单设置5.");
                    return true;
                }
            }
        }
    }

    //3.

    return false;

}
void pair_trading_process::trading_process_MD_data()
{
    QList<trading_status>::iterator trading_item;
    is_lame_leg = false;

    for (trading_item = trading_list.begin(); trading_item != trading_list.end(); trading_item++)
    {

        if (trading_item->group_direction == POSITION_BUY)
        {
            if (trading_item->B_price_type == 2)
            {
                trading_item->latest_spd_price = group_price.delta_rival_AaBb_beta;
            }
            else
            {
                trading_item->latest_spd_price = group_price.delta_AaBa_beta;
            }
        }
        else
        {
            if (trading_item->B_price_type == 2)
            {
                trading_item->latest_spd_price = group_price.delta_rival_AbBa_beta;
            }
            else
            {
                trading_item->latest_spd_price = group_price.delta_AbBb_beta;
            }
        }

        if (trading_item->instrumentB_trading_list[0].status_step == 1) //判断B是否在等待交易
        {
            //增加一个函数判断是否买入。

            if (trading_item->group_direction == POSITION_BUY)
            {
                if (judge_whther_start_order(*trading_item)) //比目标价格低，卖
                {
                    int vol = trading_item->target_vol - trading_item->instrumentB_trading_list[0].finished_vol;  ///todo 做数量转化。
                    double buy_price;

                    if (trading_item->B_price_type == 1)
                    {
                        buy_price = B_price.ask1 + HYstruct_B.hyds;
                    }
                    else if (trading_item->B_price_type == 2)
                    {
                        buy_price = B_price.bid1;
                    }
                    else
                    {
                        buy_price = B_price.ask1;
                    }

                    if (trading_item->op_cl == OPEN_POSITION) //开仓
                    {
                        trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                            td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Sell, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, buy_price, vol, HYstruct_B.exchangeID);
                    }
                    else // 平仓
                    {
                        if (HYstruct_B.exchangeID == "SHFE") //如果是上海交易所
                        {
                            //时间判断平今和平昨天
                            QString str = "2021-" + trading_item->close_position_status->position_time;
                            QDateTime time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

                            QDateTime compare_today_time = QDateTime::currentDateTime();
                            compare_today_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));
                            int delta_secs_now = QDateTime::currentDateTime().secsTo(compare_today_time);

                            QDateTime compare_time = QDateTime::currentDateTime();

                            if (delta_secs_now > 0) //在21点以前
                            {
                                //判断是不是周一，周一要减3天
                                QString weekday = compare_time.toString("ddd");
                                if (weekday == "星期一")
                                {
                                    compare_time = compare_time.addDays(-3); //减一天
                                }
                                else
                                {
                                    compare_time = compare_time.addDays(-1); //减一天
                                }
                            }

                            compare_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));

                            int delta_secs = time.secsTo(compare_time);
                            if (delta_secs > 0) //大于0表明在昨天以前
                            {
                                trading_item->is_close_yesterday = true;
                                trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseYesterday, THOST_FTDC_OPT_LimitPrice, buy_price, vol, HYstruct_B.exchangeID);
                            }
                            else //平今
                            {
                                trading_item->is_close_yesterday = false;
                                trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseToday, THOST_FTDC_OPT_LimitPrice, buy_price, vol, HYstruct_B.exchangeID);
                            }
                        }
                        else
                        {
                            trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                                td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Sell, THOST_FTDC_OF_Close, THOST_FTDC_OPT_LimitPrice, buy_price, vol, HYstruct_B.exchangeID);
                        }
                    }
                    trading_item->instrumentB_trading_list[0].insert_id_B.frontID = td->trade_front_id;
                    trading_item->instrumentB_trading_list[0].insert_id_B.sessionID = td->session_id;

                    trading_item->instrumentB_trading_list[0].order_price = buy_price;
                    if (trading_item->A_price_type == 0) //如果A使用目标价格，记录当时的A的价格作为之后的A的报单价格
                    {
                        trading_item->instrumentB_trading_list[0].A_order_price = A_price.ask1;
                    }
                    trading_item->instrumentB_trading_list[0].order_vol = trading_item->target_vol;
                    trading_item->instrumentB_trading_list[0].button_2.enbale = false;
                    trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("下单中");

                    QDateTime time = QDateTime::currentDateTime();
                    QString str = time.toString("hh:mm:ss");
                    trading_item->instrumentB_trading_list[0].order_time = str;
                    trading_item->instrumentB_trading_list[0].wait_order_time = time;
                    trading_item->instrumentB_trading_list[0].status_step = 2;
                    trading_item->instrumentB_trading_list[0].order_err_count = 0;
                    trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待报单");
                    trading_item->status = 2;
                }
            }
            else
            {
                if (judge_whther_start_order(*trading_item)) //比目标价格高，买
                {
                    int vol = trading_item->target_vol - trading_item->instrumentB_trading_list[0].finished_vol;  ///todo 做数量转化。
                    int sell_price;

                    if (trading_item->B_price_type == 1)
                    {
                        sell_price = B_price.bid1 - HYstruct_B.hyds;
                    }
                    else if (trading_item->B_price_type == 2)
                    {
                        sell_price = B_price.ask1;
                    }
                    else
                    {
                        sell_price = B_price.bid1;
                    }

                    if (trading_item->op_cl == OPEN_POSITION) //开仓
                    {
                        trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                            td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Buy, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, sell_price, vol, HYstruct_B.exchangeID);
                    }
                    else //平仓
                    {
                        if (HYstruct_B.exchangeID == "SHFE") //如果是上海交易所
                        {
                            //todo：：：增加时间判断平今和平昨天******************************************************************************************
                            QString str = "2021-" + trading_item->close_position_status->position_time;
                            QDateTime time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

                            QDateTime compare_today_time = QDateTime::currentDateTime();
                            compare_today_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));
                            int delta_secs_now = QDateTime::currentDateTime().secsTo(compare_today_time);


                            QDateTime compare_time = QDateTime::currentDateTime();
                            if (delta_secs_now > 0) //在21点以前
                            {
                                //判断是不是周一，周一要减3天
                                QString weekday = compare_time.toString("ddd");
                                if (weekday == "星期一")
                                {
                                    compare_time = compare_time.addDays(-3); //减一天
                                }
                                else
                                {
                                    compare_time = compare_time.addDays(-1); //减一天
                                }
                            }

                            compare_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));

                            int delta_secs = time.secsTo(compare_time);
                            if (delta_secs > 0) //大于一天平昨
                            {
                                trading_item->is_close_yesterday = true;
                                trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseYesterday, THOST_FTDC_OPT_LimitPrice, sell_price, vol, HYstruct_B.exchangeID);
                            }
                            else
                            {
                                trading_item->is_close_yesterday = false;
                                trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseToday, THOST_FTDC_OPT_LimitPrice, sell_price, vol, HYstruct_B.exchangeID);
                            }

                        }
                        else
                        {
                            trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef =  //储存交易号，在报单中匹配
                                td->reqOrderInsert_new(InsrumentB, THOST_FTDC_D_Buy, THOST_FTDC_OF_Close, THOST_FTDC_OPT_LimitPrice, sell_price, vol, HYstruct_B.exchangeID);
                        }
                    }
                    trading_item->instrumentB_trading_list[0].insert_id_B.frontID = td->trade_front_id;
                    trading_item->instrumentB_trading_list[0].insert_id_B.sessionID = td->session_id;

                    trading_item->instrumentB_trading_list[0].order_price = sell_price;
                    if (trading_item->A_price_type == 0) //如果A使用目标价格，记录当时的A的价格作为之后的A的报单价格
                    {
                        trading_item->instrumentB_trading_list[0].A_order_price = A_price.bid1;
                    }
                    trading_item->instrumentB_trading_list[0].order_vol = trading_item->target_vol;
                    trading_item->instrumentB_trading_list[0].button_2.enbale = false;

                    QDateTime time = QDateTime::currentDateTime();
                    QString str = time.toString("hh:mm:ss");
                    trading_item->instrumentB_trading_list[0].order_time = str;
                    trading_item->instrumentB_trading_list[0].wait_order_time = time;
                    trading_item->instrumentB_trading_list[0].status_step = 2;
                    trading_item->instrumentB_trading_list[0].order_err_count = 0;
                    trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待报单");
                    trading_item->status = 2;
                }
            }
        }
        /*交易中，更新各个合约的价差*/
        if (trading_item->instrumentB_trading_list[0].status_step == 3 || trading_item->instrumentB_trading_list[0].status_step == 10) /*交易中，更新各个合约的价差*/
        {
            trading_item->instrumentB_trading_list[0].delta_latest_order = (abs(B_price.last - trading_item->instrumentB_trading_list[0].order_price) + 0.000001) / HYstruct_B.hyds; //更新B价差
        }
        /*等待下单回报中，异常检测*/
        if (trading_item->instrumentB_trading_list[0].status_step == 2)
        {
            trading_item->instrumentB_trading_list[0].order_err_count++;
            if (trading_item->instrumentB_trading_list[0].order_err_count > 60) //超过一段时间仍然停留在此状态，表明下单异常。增加异常处理
            {
                //报错。
                trading_item->instrumentB_trading_list[0].status_step = -1;
                trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("下单异常");
                trading_item->instrumentB_trading_list[0].button_1.enbale = true;
                trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("异常|重发单？");
                trading_item->instrumentB_trading_list[0].button_2.enbale = true;
                emit send_log_message(QString::number(trading_item->index) + ":下单异常，请处理！！！");
            }
        }

        //如果有A在，更新A相关信息
        QList<instrumentA_trading_status>::iterator insA_item;
        for (insA_item = trading_item->instrumentA_trading_list.begin(); insA_item != trading_item->instrumentA_trading_list.end(); insA_item++)
        {
            if (insA_item->status_step == 3 || insA_item->status_step == 10)
            {
                insA_item->delta_latest_order = (abs(A_price.last - insA_item->order_price) + 0.00001) / HYstruct_A.hyds;
            }
            if (insA_item->status_step != 100)
            {
                insA_item->leg_check_count++;
                if (insA_item->leg_check_count > 1)
                {
                    is_lame_leg = true;
                    if (insA_item->leg_check_count < 3)
                    {
                        emit send_log_message(QString::number(trading_item->index) + ":瘸腿，请注意");
                        emit send_leg_warning_show(widget_tab_index);
                    }
                }
            }
            if (insA_item->status_step == 2)
            {
                insA_item->order_err_count++;
                if (insA_item->order_err_count > 60)
                {
                    //报错。
                    insA_item->status_step = -1;
                    insA_item->status = QString::fromUtf8("下单异常");
                    insA_item->button_1.enbale = true;
                    insA_item->button_1.button_text = QString::fromUtf8("异常|重发单？");
                    emit send_log_message(QString::number(trading_item->index) + ":下单异常，请处理！！！");
                }
            }
        }

        update_trading_UI(*trading_item);

        //判断是否需要自动撤单
        if ((trading_item->instrumentB_trading_list[0].status_step == 3) ||
            (trading_item->instrumentB_trading_list[0].status_step == 10)) //判断B是否等待撮合
        {
            if (judge_whther_cancel_order(*trading_item)) //判断是否撤单
            {
                QString action_back;

                action_back = "button1_" + QString::number(trading_item->index) + "_" + QString::number(trading_item->instrumentB_trading_list[0].sub_index);
                receive_trading_action(action_back);
            }
        }
    }
}


void pair_trading_process::position_process_MD_data(void)
{
    position_status* position_item;
    int i = 0;
    int size = position_list.size();

    int total_positions = 0;
    int total_positions_A = 0;
    int total_positions_B = 0;
    int total_profit = 0;
    //更新各个持仓状态
    for (i = size - 1; i >= 0; i--)
    {
        position_item = &position_list[i];
        //计算实时盈亏
        double profit_A, profit_B;
        if (position_item->spd_direction == POSITION_BUY)
        {
            profit_A = (A_price.bid1 - position_item->cost_A) * position_item->vol_A * HYstruct_A.hycs;
            profit_B = (position_item->cost_B - B_price.bid1) * position_item->vol_B * HYstruct_B.hycs;
        }
        else
        {
            profit_A = (position_item->cost_A - A_price.ask1) * position_item->vol_A * HYstruct_A.hycs;
            profit_B = (B_price.ask1 - position_item->cost_B) * position_item->vol_B * HYstruct_B.hycs;
        }
        position_item->profit = profit_A + profit_B;
        if (abs(position_item->profit) < 0.000001)
        {
            position_item->profit = 0;
        }

        if (position_item->profit > 0)
        {
            position_item->profit_ticks = (position_item->profit / (position_item->spd_vol * HYstruct_A.hyds * HYstruct_A.hycs)) + 0.5; //四舍五入
        }
        else
        {
            position_item->profit_ticks = (position_item->profit / (position_item->spd_vol * HYstruct_A.hyds * HYstruct_A.hycs)) - 0.5; //四舍五入
        }

        total_positions += position_item->spd_vol;
        total_positions_A += position_item->vol_A;
        total_positions_B += position_item->vol_B;
        total_profit += position_item->profit;

        if (position_item->close_spd_vol == position_item->spd_vol)
        {
            //平仓完成，删除此条
            position_list.removeAt(i);
        }
        else
        {

            update_position_table_row(*position_item);
        }

    }

    statistic_data.spd_total_positions = total_positions;
    statistic_data.spd_rt_profit = total_profit;
    statistic_data.instrumentA_local_positons = total_positions_A;
    statistic_data.instrumentB_local_positons = total_positions_B;
}


void pair_trading_process::receive_WT_data(CThostFtdcOrderField wt_data)
{
    QString sReturnIns = wt_data.InstrumentID;

    if (sReturnIns != InsrumentA && sReturnIns != InsrumentB)
        return;// 非我们关心的合约. 
    TThostFtdcFrontIDType iReturnFrontId = wt_data.FrontID;
    TThostFtdcSessionIDType iReturnSessionId = wt_data.SessionID;
    QString sReturnOrderRef = wt_data.OrderRef;
    QString sReturnCombOffsetFlag = wt_data.CombOffsetFlag;
    QString sReturnOrderSysID = wt_data.OrderSysID;


    if (wt_data.OrderStatus != THOST_FTDC_OST_Canceled) //如果不是撤单
    {
        if ((wt_data.OrderSubmitStatus == THOST_FTDC_OSS_Accepted || wt_data.OrderSubmitStatus == THOST_FTDC_OSS_InsertSubmitted)
            && (sReturnOrderSysID.size() != 0)) //过滤那次没有报单号的报单)
        {
            //循环合约
            QList<trading_status>::iterator trading_item;

            for (trading_item = trading_list.begin(); trading_item != trading_list.end(); trading_item++)
            {
                if (sReturnIns == InsrumentB) //合约B处理
                {
                    //匹配下单合约

                    if ((trading_item->instrumentB_trading_list[0].insert_id_B.frontID == iReturnFrontId) &&
                        (trading_item->instrumentB_trading_list[0].insert_id_B.sessionID == iReturnSessionId) &&
                        (trading_item->instrumentB_trading_list[0].insert_id_B.ReturnOrderRef == sReturnOrderRef) &&
                        (trading_item->instrumentB_trading_list[0].status_step == 2 || trading_item->instrumentB_trading_list[0].status_step == -1)) //不在撤单状态
                    {
                        trading_item->instrumentB_trading_list[0].status_step = 3;
                        trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("待成交");
                        trading_item->instrumentB_trading_list[0].button_1.enbale = true;
                        trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("已下单|重发单");
                        trading_item->instrumentB_trading_list[0].button_2.enbale = true;
                        trading_item->instrumentB_trading_list[0].insert_id_B.OrderSysID = sReturnOrderSysID;
                        trading_item->instrumentB_trading_list[0].insert_id_B.is_canceled = false;
                        trading_item->instrumentB_trading_list[0].insert_id_B.JYS_ID = wt_data.ExchangeID;
                        update_trading_UI(*trading_item);
                        statistic_data.instrumentB_order_times++;
                    }

                }
                else  //合约A处理
                {
                    QList<instrumentA_trading_status>::iterator insA_item;
                    for (insA_item = trading_item->instrumentA_trading_list.begin(); insA_item != trading_item->instrumentA_trading_list.end(); insA_item++)
                    {
                        //匹配下单合约
                        if ((insA_item->idA.frontID == iReturnFrontId) &&
                            (insA_item->idA.sessionID == iReturnSessionId) &&
                            (insA_item->idA.ReturnOrderRef == sReturnOrderRef) &&
                            (insA_item->status_step == 2 || insA_item->status_step == -1))                     //不在撤单状态
                        {
                            insA_item->status_step = 3;
                            insA_item->status = QString::fromUtf8("待成交");
                            insA_item->button_1.enbale = true;
                            insA_item->button_1.button_text = QString::fromUtf8("已下单|重发单");
                            insA_item->idA.OrderSysID = sReturnOrderSysID;
                            insA_item->idA.is_canceled = false;
                            insA_item->idA.JYS_ID = wt_data.ExchangeID;
                            update_trading_UI(*trading_item);
                            statistic_data.instrumentA_order_times++;
                        }
                    }
                }
            }

        }
    }
    else if (wt_data.OrderSubmitStatus == THOST_FTDC_OSS_Accepted)  //撤单处理
    {
        int list_size = trading_list.size();
        trading_status* trading_item;

        for (int i = list_size - 1; i >= 0; i--)
        {
            trading_item = &trading_list[i];
            //匹配合约
            if (sReturnIns == InsrumentB) //合约B处理
            {
                if (trading_item->instrumentB_trading_list[0].insert_id_B.OrderSysID == sReturnOrderSysID)
                {
                    if (trading_item->instrumentB_trading_list[0].insert_id_B.is_canceled == true)
                    {
                        return;
                    }
                    if (trading_item->instrumentB_trading_list[0].status_step == 50) //判断状态为停止，因此撤单。
                    {
                        statistic_data.instrumentB_canceled_order_times++;
                        //判断是否已挂单全部成交，如果全部成交直接处理，否则等待A完成。
                        if (trading_item->instrumentB_trading_list[0].finished_vol == trading_item->product_finished_vol) // todo 需要转换
                        {
                            //如果全部都已经停止，删除此行
                            if (trading_item->op_cl == CLOSE_POSITION) //平仓，更新持仓数据 后再删除
                            {
                                trading_item->close_position_status->button.button_text = QString::fromUtf8("平仓");
                                trading_item->close_position_status->button.enbale = true;
                                trading_item->close_position_status->spd_vol -= trading_item->close_position_status->close_spd_vol;
                                trading_item->close_position_status->close_spd_vol = 0;
                                trading_item->close_position_status->vol_A = trading_item->close_position_status->spd_vol;
                                trading_item->close_position_status->vol_B = trading_item->close_position_status->spd_vol;
                                trading_item->close_position_status->close_position_status = 0;
                                update_position_table_row(*trading_item->close_position_status);
                            }
                            //删除此挂单。
                            send_delete_trading_table_rows(QString::number(trading_item->index));
                            trading_list.removeAt(i);
                        }
                        else //如果有未成交A单，修改目标成交量，当所有完成时直接删除自己
                        {
                            trading_item->target_vol = trading_item->instrumentB_trading_list[0].finished_vol; //需要转换
                            trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待A成交");
                            update_trading_UI(*trading_item);
                            trading_item->instrumentB_trading_list[0].insert_id_B.is_canceled = true;
                        }
                    }
                    else if (trading_item->instrumentB_trading_list[0].status_step == 80) //判断状态为重新下单
                    {
                        statistic_data.instrumentB_canceled_order_times++;

                        trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待中");
                        trading_item->instrumentB_trading_list[0].status_step = 1;
                        trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("未下单");
                        trading_item->instrumentB_trading_list[0].button_1.enbale = false;
                        trading_item->instrumentB_trading_list[0].button_2.enbale = true;
                        trading_item->instrumentB_trading_list[0].order_price = 0;
                        trading_item->instrumentB_trading_list[0].delta_latest_order = 0;
                        trading_item->instrumentB_trading_list[0].order_vol = 0;
                        update_trading_UI(*trading_item);
                        trading_item->instrumentB_trading_list[0].insert_id_B.is_canceled = true;
                    }
                    else if (trading_item->instrumentB_trading_list[0].status_step != -100) //从其它设备来的撤单
                    {
                        statistic_data.instrumentB_canceled_order_times++;

                        trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("异常撤单！");
                        trading_item->instrumentB_trading_list[0].status_step = -100;
                        trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("请注意");
                        trading_item->instrumentB_trading_list[0].button_1.enbale = false;
                        trading_item->instrumentB_trading_list[0].button_2.enbale = true;
                        trading_item->instrumentB_trading_list[0].order_price = 0;
                        trading_item->instrumentB_trading_list[0].delta_latest_order = 0;
                        trading_item->instrumentB_trading_list[0].order_vol = 0;
                        update_trading_UI(*trading_item);
                        trading_item->instrumentB_trading_list[0].insert_id_B.is_canceled = true;
                    }
                }
            }
            else //A合约撤单
            {
                QList<instrumentA_trading_status>::iterator insA_item;
                for (insA_item = trading_item->instrumentA_trading_list.begin(); insA_item != trading_item->instrumentA_trading_list.end(); insA_item++)
                {
                    //匹配合约
                    if (insA_item->idA.OrderSysID == sReturnOrderSysID)
                    {
                        //if (insA_item->status_step == 80) //判断状态为重新下单
                        //A只要收到撤单回报就立即重新下单。A必须能够下单。
                        if (insA_item->idA.is_canceled == false)
                        {
                            statistic_data.instrumentA_canceled_order_times++;
                            //重新下单，只下单未成交的数量
                            int vol = insA_item->order_vol - insA_item->finished_vol;

                            if (insA_item->open_or_close == OPEN_POSITION) //开仓
                            {
                                if (insA_item->direction == POSITION_BUY) //buy
                                {
                                    insA_item->order_price = A_price.ask1;
                                    insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                        td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                }
                                else //sell
                                {
                                    insA_item->order_price = A_price.bid1;
                                    insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                        td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                }
                            }
                            else //close
                            {
                                QThread::msleep(15); //延时等待服务器处理完撤单信息，再下单，否则可能会出现仓位不足。
                                if (insA_item->direction == POSITION_BUY) //buy
                                {
                                    if (HYstruct_A.exchangeID == "SHFE") //如果是上海交易所
                                    {
                                        //增加平今和平昨
                                        insA_item->order_price = A_price.ask1;

                                        if (trading_item->is_close_yesterday == true)
                                        {
                                            insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseYesterday,
                                                    THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                        }
                                        else
                                        {
                                            insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseToday,
                                                    THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                        }
                                    }
                                    else
                                    {
                                        insA_item->order_price = A_price.ask1;
                                        insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                            td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_Close,
                                                THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                    }
                                }
                                else //sell
                                {
                                    if (HYstruct_A.exchangeID == "SHFE") //如果是上海交易所
                                    {
                                        insA_item->order_price = A_price.bid1;
                                        if (trading_item->is_close_yesterday == true)
                                        {
                                            insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseYesterday,
                                                    THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                        }
                                        else
                                        {
                                            insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseToday,
                                                    THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                        }
                                    }
                                    else
                                    {
                                        insA_item->order_price = A_price.bid1;
                                        insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                            td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_Close,
                                                THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                    }
                                }
                            }
                            insA_item->delta_latest_order = (abs(A_price.last - insA_item->order_price) + 0.00001) / HYstruct_A.hyds;
                            insA_item->idA.frontID = td->trade_front_id;
                            insA_item->idA.sessionID = td->session_id;
                            insA_item->status = QString::fromUtf8("等待报单");
                            insA_item->status_step = 2;
                            insA_item->order_err_count = 0;
                            insA_item->button_1.button_text = QString::fromUtf8("下单中");
                            insA_item->button_1.enbale = false;
                            update_trading_UI(*trading_item);
                        }
                        insA_item->idA.is_canceled = true;
                    }
                }
            }
        }
    }
}

void pair_trading_process::receive_CJ_data(CThostFtdcTradeField cj_data)
{
    QString InstrumentID = cj_data.InstrumentID;
    QString sReturnOrderSysID = cj_data.OrderSysID;
    if ((InstrumentID != InsrumentB) && (InstrumentID != InsrumentA)) //不关心合约，直接退出
    {
        return;
    }
    //循环合约
    trading_status* trading_item;
    int trading_size = trading_list.size();
    for (int i = trading_size - 1; i >= 0; i--)
    {
        trading_item = &trading_list[i];
        if (InstrumentID == InsrumentB) //有B单成交，马上开A单。
        {
            //匹配成交合约
            if ((trading_item->instrumentB_trading_list[0].insert_id_B.OrderSysID == sReturnOrderSysID))
            {
                if (trading_item->instrumentB_trading_list[0].insert_id_B.TradeID.contains(QString(cj_data.TradeID)))
                {
                    return;  //处理过的成交单，不用处理两次
                }
                ctp_beep_set(1); // 发出提示音表明成交
                statistic_data.instrumentB_finished_order_times++;

                instrumentA_trading_status instrumentA_status; //新增一个A单

                instrumentA_status.instrument = InsrumentA;
                instrumentA_status.sub_index = trading_item->sub_index_count;
                trading_item->sub_index_count++;
                instrumentA_status.direction = trading_item->group_direction;
                instrumentA_status.open_or_close = trading_item->op_cl;

                int vol = cj_data.Volume;  //

                instrumentA_status.order_vol = vol;
                QDateTime time = QDateTime::currentDateTime();
                QString str = time.toString("hh:mm:ss");
                instrumentA_status.order_time = str;
                instrumentA_status.wait_order_time = time;
                instrumentA_status.status_step = 2;
                instrumentA_status.order_err_count = 0;
                instrumentA_status.status = QString::fromUtf8("等待报单");
                instrumentA_status.button_1.button_text = QString::fromUtf8("下单中");
                instrumentA_status.button_1.enbale = false;
                instrumentA_status.button_2.button_text = QString::fromUtf8("--");
                instrumentA_status.button_2.enbale = false;
                instrumentA_status.B_CJ = cj_data;

                if (instrumentA_status.open_or_close == OPEN_POSITION) //开仓
                {
                    if (trading_item->group_direction == POSITION_BUY) //buy
                    {
                        if (trading_item->A_price_type == 0)
                        {
                            instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                        }
                        else
                        {
                            instrumentA_status.order_price = A_price.ask1;
                        }
                        instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                            td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                    }
                    else //sell
                    {
                        if (trading_item->A_price_type == 0)
                        {
                            instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                        }
                        else
                        {
                            instrumentA_status.order_price = A_price.bid1;
                        }
                        instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                            td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                    }
                }
                else //close
                {
                    if (trading_item->group_direction == POSITION_BUY) //buy
                    {
                        if (HYstruct_A.exchangeID == "SHFE") //如果是上海交易所
                        {
                            //增加平今和平昨

                            if (trading_item->is_close_yesterday == true)
                            {
                                if (trading_item->A_price_type == 0)
                                {
                                    instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                                }
                                else
                                {
                                    instrumentA_status.order_price = A_price.ask1;
                                }
                                instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseYesterday,
                                        THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                            }
                            else//平今
                            {
                                if (trading_item->A_price_type == 0)
                                {
                                    instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                                }
                                else
                                {
                                    instrumentA_status.order_price = A_price.ask1;
                                }
                                instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseToday,
                                        THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                            }
                        }
                        else
                        {
                            if (trading_item->A_price_type == 0)
                            {
                                instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                            }
                            else
                            {
                                instrumentA_status.order_price = A_price.ask1;
                            }
                            instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_Close,
                                    THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                        }
                    }
                    else //sell
                    {
                        if (HYstruct_A.exchangeID == "SHFE") //如果是上海交易所
                        {
                            if (trading_item->is_close_yesterday == true)
                            {
                                if (trading_item->A_price_type == 0)
                                {
                                    instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                                }
                                else
                                {
                                    instrumentA_status.order_price = A_price.bid1;
                                }
                                instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseYesterday,
                                        THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                            }
                            else
                            {
                                if (trading_item->A_price_type == 0)
                                {
                                    instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                                }
                                else
                                {
                                    instrumentA_status.order_price = A_price.bid1;
                                }
                                instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseToday,
                                        THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                            }
                        }
                        else
                        {
                            if (trading_item->A_price_type == 0)
                            {
                                instrumentA_status.order_price = trading_item->instrumentB_trading_list[0].A_order_price;
                            }
                            else
                            {
                                instrumentA_status.order_price = A_price.bid1;
                            }
                            instrumentA_status.idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_Close,
                                    THOST_FTDC_OPT_LimitPrice, instrumentA_status.order_price, vol, HYstruct_A.exchangeID);
                        }
                    }
                }
                instrumentA_status.delta_latest_order = (abs(A_price.last - instrumentA_status.order_price) + 0.00001) / HYstruct_A.hyds;
                instrumentA_status.idA.frontID = td->trade_front_id;
                instrumentA_status.idA.sessionID = td->session_id;
                trading_item->instrumentA_trading_list.append(instrumentA_status);

                trading_table_row_UI row_A;

                row_A.index = QString::number(trading_item->index);
                row_A.sub_index = QString::number(instrumentA_status.sub_index);
                row_A.instrument = instrumentA_status.instrument;
                row_A.open_or_close = (instrumentA_status.open_or_close == OPEN_POSITION) ? "open" : "close";
                row_A.direction = (instrumentA_status.direction == POSITION_BUY) ? "buy" : "sell";
                row_A.order_price = QString::number(instrumentA_status.order_price);
                row_A.delta_latest_order = QString::number(instrumentA_status.delta_latest_order) + " tick";
                row_A.order_vol = QString::number(instrumentA_status.order_vol);
                row_A.order_time = instrumentA_status.order_time;

                row_A.finished_vol = QString::number(instrumentA_status.finished_vol);
                row_A.target_vol = QString::number(trading_item->target_vol);
                row_A.target_price = QString::number(trading_item->target_price);
                row_A.latest_spd_price = QString::number(trading_item->latest_spd_price);
                row_A.status = instrumentA_status.status;
                row_A.button_1 = instrumentA_status.button_1;
                row_A.button_2 = instrumentA_status.button_2;
                if (trading_item->A_price_type == 0)
                {
                    row_A.price_type = "正常价";
                }
                else
                {
                    row_A.price_type = "对手价";
                }
                emit send_add_trading_table_row(row_A);

                //更新B单状态和总体状态
                trading_item->instrumentB_trading_list[0].finished_vol += cj_data.Volume;
                trading_item->instrumentB_trading_list[0].insert_id_B.TradeID.append(QString(cj_data.TradeID));
                if (trading_item->instrumentB_trading_list[0].finished_vol >= trading_item->instrumentB_trading_list[0].order_vol)
                {
                    trading_item->instrumentB_trading_list[0].button_1.enbale = false;
                    trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("报单完成");
                    trading_item->instrumentB_trading_list[0].button_2.enbale = false;
                    trading_item->instrumentB_trading_list[0].status_step = 100;
                    trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("全部成交");
                }
                else
                {
                    if (trading_item->instrumentB_trading_list[0].status_step == 3) //如果是等待成交则修改状态，否则状态不变
                    {
                        trading_item->instrumentB_trading_list[0].status_step = 10;
                    }
                    trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("部分成交");
                }
                update_trading_UI(*trading_item);
            }
        }
        else if (InstrumentID == InsrumentA)
        {
            QList<instrumentA_trading_status>::iterator insA_item;
            for (insA_item = trading_item->instrumentA_trading_list.begin(); insA_item != trading_item->instrumentA_trading_list.end(); insA_item++)
            {
                //匹配成交合约
                if ((insA_item->idA.OrderSysID == sReturnOrderSysID))
                {
                    //更新A单状态和总体状态
                    if (insA_item->idA.TradeID.contains(QString(cj_data.TradeID)))
                    {
                        return; //此单已经处理，不用重复处理
                    }
                    ctp_beep_set(1); // 发出提示音表明成交
                    statistic_data.instrumentA_finished_order_times++;

                    insA_item->finished_vol += cj_data.Volume;
                    insA_item->idA.TradeID.append(QString(cj_data.TradeID));
                    if (insA_item->finished_vol >= insA_item->order_vol)
                    {
                        insA_item->button_1.enbale = false;
                        insA_item->status_step = 100;
                        insA_item->status = QString::fromUtf8("全部成交");
                    }
                    else
                    {
                        insA_item->status_step = 10;
                        insA_item->status = QString::fromUtf8("部分成交");
                    }
                    trading_item->product_finished_vol += cj_data.Volume; //转换一下。

                    //add 持仓UI
                    if (trading_item->op_cl == OPEN_POSITION)
                    {
                        position_status new_position;
                        new_position.index = get_position_status_index();
                        new_position.spd_vol = cj_data.Volume; //转换一下。
                        new_position.close_spd_vol = 0;
                        new_position.spd_direction = trading_item->group_direction;
                        new_position.instrumentA = insA_item->instrument;
                        new_position.direction_A = insA_item->direction;
                        new_position.vol_A = cj_data.Volume;
                        new_position.instrumentB = insA_item->B_CJ.InstrumentID;
                        new_position.vol_B = cj_data.Volume; //转换一下。
                        new_position.direction_B = trading_item->instrumentB_trading_list[0].direction;

                        QDateTime time = QDateTime::currentDateTime();
                        QString str = time.toString("MM-dd hh:mm:ss");
                        new_position.position_time = str;
                        new_position.button.button_text = QString::fromUtf8("平仓");
                        new_position.button.enbale = true;
                        new_position.A_CJ = cj_data;
                        new_position.B_CJ = insA_item->B_CJ;

                        new_position.cost_A = new_position.A_CJ.Price;
                        new_position.cost_B = new_position.B_CJ.Price;
                        new_position.cost = new_position.cost_A - new_position.cost_B * beta;

                        //计算实时盈亏
                        double profit_A, profit_B;
                        if (new_position.spd_direction == POSITION_BUY)
                        {
                            profit_A = (A_price.bid1 - new_position.cost_A) * new_position.vol_A * HYstruct_A.hycs;
                            profit_B = (new_position.cost_B - B_price.bid1) * new_position.vol_B * HYstruct_B.hycs;
                        }
                        else
                        {
                            profit_A = (new_position.cost_A - A_price.ask1) * new_position.vol_A * HYstruct_A.hycs;
                            profit_B = (B_price.ask1 - new_position.cost_B) * new_position.vol_B * HYstruct_B.hycs;
                        }
                        new_position.profit = profit_A + profit_B;
                        new_position.close_position_status = 0;
                        new_position.start_target_price = trading_item->target_price;

                        add_position_table_row(new_position);
                        position_list.append(new_position);
                    }
                    else //平仓操作 更新UI
                    {
                        trading_item->close_position_status->close_spd_vol += cj_data.Volume; //转换一下。

                        if (trading_item->close_position_status->spd_vol > trading_item->close_position_status->close_spd_vol) //部分成交
                        {
                            //更新UI
                            trading_item->close_position_status->button.button_text =
                                QString::fromUtf8("已平仓:") + QString::number(trading_item->close_position_status->close_spd_vol);
                            update_position_table_row(*(trading_item->close_position_status)); //更新UI
                            emit sync_position_data(*(trading_item->close_position_status));
                        }
                        else //全部成交
                        {
                            //删除持仓显示
                            emit send_delete_position_table_row(QString::number(trading_item->close_position_status->index));
                        }
                        //增加记录显示
                        history_position_status new_history;

                        new_history.index = QString::number(get_history_position_index()) + "-" + QString::number(trading_item->index);
                        new_history.instrumentA = InsrumentA;
                        new_history.instrumentB = InsrumentB;
                        new_history.spd_direction = (trading_item->close_position_status->spd_direction == POSITION_BUY) ? "buy" : "sell";
                        new_history.spd_vol = QString::number(cj_data.Volume);//转换一下。
                        new_history.start_time = trading_item->close_position_status->position_time;
                        new_history.start_target_price = QString::number(trading_item->close_position_status->start_target_price);
                        new_history.start_price = QString::number(trading_item->close_position_status->cost);

                        QDateTime time = QDateTime::currentDateTime();
                        QString str = time.toString("MM-dd:hh:mm:ss");
                        new_history.end_time = str;
                        new_history.end_target_price = QString::number(trading_item->target_price);
                        new_history.end_price = QString::number(cj_data.Price) + "-" + QString::number(insA_item->B_CJ.Price) + " * beta ="
                            + QString::number(cj_data.Price - (beta * insA_item->B_CJ.Price));

                        if (trading_item->close_position_status->spd_direction == POSITION_BUY)
                        {
                            new_history.profit = QString::number(((cj_data.Price - trading_item->close_position_status->A_CJ.Price) * trading_item->close_position_status->vol_A * HYstruct_A.hycs) +
                                ((trading_item->close_position_status->B_CJ.Price - insA_item->B_CJ.Price) * trading_item->close_position_status->vol_B * HYstruct_B.hycs));
                        }
                        else
                        {
                            new_history.profit = QString::number(((trading_item->close_position_status->A_CJ.Price - cj_data.Price) * trading_item->close_position_status->vol_A * HYstruct_A.hycs) +
                                ((insA_item->B_CJ.Price - trading_item->close_position_status->B_CJ.Price) * trading_item->close_position_status->vol_B * HYstruct_B.hycs));
                        }

                        history_position_list.append(new_history);
                        emit send_add_history_table_row(new_history);

                        statistic_data.spd_close_profit += new_history.profit.toDouble();
                    }
                    update_trading_UI(*trading_item);
                }
            }
            //等循环结束才能够删除。
            if (trading_item->product_finished_vol == trading_item->target_vol)
            {
                //全部完成！！！
                qDebug() << "交易完成";
                emit send_delete_trading_table_rows(QString::number(trading_item->index));
                if (trading_item->instrumentB_trading_list[0].status_step == 50) //两种异常状态过来
                {
                    if (trading_item->op_cl == CLOSE_POSITION) //平仓，更新持仓数据 后再删除
                    {
                        trading_item->close_position_status->button.button_text = QString::fromUtf8("平仓");
                        trading_item->close_position_status->button.enbale = true;
                        trading_item->close_position_status->spd_vol -= trading_item->close_position_status->close_spd_vol;
                        trading_item->close_position_status->close_spd_vol = 0;
                        trading_item->close_position_status->vol_A = trading_item->close_position_status->spd_vol;
                        trading_item->close_position_status->vol_B = trading_item->close_position_status->spd_vol;
                        trading_item->close_position_status->close_position_status = 0;
                        update_position_table_row(*trading_item->close_position_status);
                    }
                }
                //增加删除list
                trading_list.removeAt(i);
            }
        }
    }
}

void pair_trading_process::add_position_table_row(position_status new_row)
{
    position_table_row_UI row_UI;

    row_UI.index = QString::number(new_row.index);
    row_UI.direction_spd = (new_row.spd_direction == POSITION_BUY) ? "buy" : "sell";
    row_UI.direction_A = (new_row.direction_A == POSITION_BUY) ? "buy" : "sell";
    row_UI.direction_B = (new_row.direction_B == POSITION_BUY) ? "buy" : "sell";
    row_UI.vol_spd = QString::number(new_row.spd_vol);
    row_UI.vol_A = QString::number(new_row.vol_A);
    row_UI.vol_B = QString::number(new_row.vol_B);
    row_UI.instrumentA = new_row.instrumentA;
    row_UI.instrumentB = new_row.instrumentB;
    row_UI.profit = QString::number(new_row.profit);
    row_UI.profit_ticks = QString::number(new_row.profit_ticks);
    row_UI.cost = QString::number(new_row.cost_A, 'f', 1) + "-" +
        QString::number(new_row.cost_B, 'f', 1) + "*" + QString::number(beta, 'f', 1) + "=" + QString::number(new_row.cost, 'f', 1);

    row_UI.position_time = new_row.position_time;
    row_UI.button = new_row.button;

    //持仓天数判断
    QString str = "2021-" + new_row.position_time;
    QDateTime time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");

    QDateTime compare_today_time = QDateTime::currentDateTime();
    compare_today_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));
    int delta_secs_now = QDateTime::currentDateTime().secsTo(compare_today_time);

    QDateTime compare_time = QDateTime::currentDateTime();

    if (delta_secs_now > 0) //在21点以前
    {
        //判断是不是周一，周一要减3天
        QString weekday = compare_time.toString("ddd");
        if (weekday == "星期一")
        {
            compare_time = compare_time.addDays(-3); //减一天
        }
        else
        {
            compare_time = compare_time.addDays(-1); //减一天
        }
    }

    compare_time.setTime(QTime::fromString("21:00:00", "hh:mm:ss"));

    int delta_secs = time.secsTo(compare_time);

    if (delta_secs > 0) //昨仓算算天数就好
    {
        int days = (delta_secs / (24 * 60 * 60)) + 1;
        row_UI.potions_days = QString::number(days) + "天";
    }
    else
    {
        row_UI.potions_days = "当天";
    }

    emit sync_position_data(new_row);
    emit send_add_position_table_row(row_UI);
    emit send_log_message("新增持仓" + row_UI.index);
}

void pair_trading_process::update_position_table_row(position_status new_row)
{
    position_table_row_UI row_UI;

    row_UI.index = QString::number(new_row.index);
    row_UI.direction_spd = (new_row.spd_direction == POSITION_BUY) ? "buy" : "sell";
    row_UI.direction_A = (new_row.direction_A == POSITION_BUY) ? "buy" : "sell";
    row_UI.direction_B = (new_row.direction_B == POSITION_BUY) ? "buy" : "sell";
    row_UI.vol_spd = QString::number(new_row.spd_vol);
    row_UI.vol_A = QString::number(new_row.vol_A);
    row_UI.vol_B = QString::number(new_row.vol_B);
    row_UI.instrumentA = new_row.instrumentA;
    row_UI.instrumentB = new_row.instrumentB;
    row_UI.profit = QString::number(new_row.profit);
    row_UI.profit_ticks = QString::number(new_row.profit_ticks);
    row_UI.cost = QString::number(new_row.cost_A, 'f', 1) + "-" +
        QString::number(new_row.cost_B, 'f', 1) + "=" + QString::number(new_row.cost, 'f', 1);

    row_UI.position_time = new_row.position_time;
    row_UI.button = new_row.button;

    emit send_update_position_table_row(row_UI);
}


int pair_trading_process::get_position_status_index(void)
{
    position_status_index++;
    return position_status_index;
}

int pair_trading_process::get_history_position_index(void)
{
    history_process_index++;
    return history_process_index;
}


trading_status pair_trading_process::init_new_trading_status(void)
{
    trading_status ret;

    ret.status = 1;
    ret.index = ++trading_process_index;
    ret.sub_index_count = 0;
    ret.B_price_type = 0;
    ret.group_direction = POSITION_BUY;
    ret.latest_spd_price = 0;
    ret.target_price = 0;
    ret.target_vol = 0;
    ret.product_finished_vol = 0;
    ret.op_cl = OPEN_POSITION;
    ret.is_close_yesterday = false;

    instrumentB_trading_status instrumentB_status;
    instrumentB_status.instrument = InsrumentB;
    instrumentB_status.sub_index = ret.sub_index_count;
    ret.sub_index_count++;
    instrumentB_status.status = QString::fromUtf8("等待中");



    ret.instrumentB_trading_list.append(instrumentB_status);

    return ret;
}






void pair_trading_process::receive_trading_action(QString button_name)
{
    qDebug() << button_name;
    if (!td->loginFlag)  //如果交易服务器未登录或者断开，无法交易
    {
        emit send_log_message("交易服务器断开，无法操作！！！");
        return;
    }


    QStringList strlist = button_name.split('_');
    int index, subindex;
    trading_status* trading_item;
    int list_size = trading_list.size();
    int i;

    if (strlist.value(0) == "button1") //手动重新下单按钮
    {
        index = strlist.value(1).toInt();
        subindex = strlist.value(2).toInt();
        for (i = list_size - 1; i >= 0; i--)
        {
            trading_item = &trading_list[i];

            if (trading_item->index == index) //匹配index
            {
                if (trading_item->instrumentB_trading_list[0].sub_index == subindex) //如果是B合约
                {
                    if ((trading_item->instrumentB_trading_list[0].status_step == 3) ||
                        (trading_item->instrumentB_trading_list[0].status_step == 10))  //报单已经发出去，但是未成交完成。
                    {
                        //撤单+更新状态
                        trading_item->instrumentB_trading_list[0].status_step = 80; //进入重新下单
                        trading_item->instrumentB_trading_list[0].wait_order_time = QDateTime::currentDateTime();
                        trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("撤单中"); //进入停止状态
                        trading_item->instrumentB_trading_list[0].button_1.enbale = false;
                        trading_item->instrumentB_trading_list[0].button_2.enbale = false;
                        update_trading_UI(*trading_item);

                        //发出撤单指令。
                        this->td->reqOrderAction(QString(this->td->jy.BrokerID),
                            trading_item->instrumentB_trading_list[0].insert_id_B.OrderSysID,
                            trading_item->instrumentB_trading_list[0].insert_id_B.JYS_ID,
                            InsrumentB);

                    }

                    if (trading_item->instrumentB_trading_list[0].status_step == -1) //如果是下单异常，点击重新下单
                    {
                        //恢复到下单前
                        trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待中");
                        trading_item->instrumentB_trading_list[0].status_step = 1;
                        trading_item->instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("未下单");
                        trading_item->instrumentB_trading_list[0].button_1.enbale = false;
                        trading_item->instrumentB_trading_list[0].button_2.enbale = true;
                        trading_item->instrumentB_trading_list[0].order_price = 0;
                        trading_item->instrumentB_trading_list[0].delta_latest_order = 0;
                        trading_item->instrumentB_trading_list[0].order_vol = 0;
                        update_trading_UI(*trading_item);
                    }
                }
                else
                {
                    QList<instrumentA_trading_status>::iterator insA_item;
                    for (insA_item = trading_item->instrumentA_trading_list.begin(); insA_item != trading_item->instrumentA_trading_list.end(); insA_item++)
                    {
                        if (insA_item->sub_index == subindex) //匹配是A合约
                        {
                            if ((insA_item->status_step == 3) ||
                                (insA_item->status_step == 10))  //报单已经发出去，但是未成交完成。
                            {
                                //撤单+更新状态
                                insA_item->status_step = 80; //进入重新下单
                                insA_item->button_1.button_text = QString::fromUtf8("撤单中"); //进入停止状态
                                insA_item->button_1.enbale = false;
                                insA_item->wait_order_time = QDateTime::currentDateTime();
                                update_trading_UI(*trading_item);

                                //发出撤单指令。
                                this->td->reqOrderAction(QString(this->td->jy.BrokerID),
                                    insA_item->idA.OrderSysID,
                                    insA_item->idA.JYS_ID,
                                    InsrumentA);
                            }
                            else if (insA_item->status_step == -1)
                            {
                                //重新下单，只下单未成交的数量
                                int vol = insA_item->order_vol - insA_item->finished_vol;

                                if (insA_item->open_or_close == OPEN_POSITION) //开仓
                                {
                                    if (insA_item->direction == POSITION_BUY) //buy
                                    {
                                        insA_item->order_price = A_price.ask1;
                                        insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                            td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                    }
                                    else //sell
                                    {
                                        insA_item->order_price = A_price.bid1;
                                        insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                            td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_Open, THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                    }
                                }
                                else //close
                                {
                                    if (insA_item->direction == POSITION_BUY) //buy
                                    {
                                        if (HYstruct_A.exchangeID == "SHFE") //如果是上海交易所
                                        {
                                            //增加平今和平昨
                                            insA_item->order_price = A_price.ask1;

                                            if (trading_item->is_close_yesterday == true)
                                            {
                                                insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseYesterday,
                                                        THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                            }
                                            else
                                            {
                                                insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_CloseToday,
                                                        THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                            }
                                        }
                                        else
                                        {
                                            insA_item->order_price = A_price.ask1;
                                            insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Buy, THOST_FTDC_OF_Close,
                                                    THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                        }
                                    }
                                    else //sell
                                    {
                                        if (HYstruct_A.exchangeID == "SHFE") //如果是上海交易所
                                        {
                                            insA_item->order_price = A_price.bid1;
                                            if (trading_item->is_close_yesterday == true)
                                            {
                                                insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseYesterday,
                                                        THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                            }
                                            else
                                            {
                                                insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                    td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_CloseToday,
                                                        THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                            }
                                        }
                                        else
                                        {
                                            insA_item->order_price = A_price.bid1;
                                            insA_item->idA.ReturnOrderRef =  //储存交易号，在报单中匹配
                                                td->reqOrderInsert_new(InsrumentA, THOST_FTDC_D_Sell, THOST_FTDC_OF_Close,
                                                    THOST_FTDC_OPT_LimitPrice, insA_item->order_price, vol, HYstruct_A.exchangeID);
                                        }
                                    }
                                }
                                insA_item->delta_latest_order = (abs(A_price.last - insA_item->order_price) + 0.00001) / HYstruct_A.hyds;
                                insA_item->idA.frontID = td->trade_front_id;
                                insA_item->idA.sessionID = td->session_id;
                                insA_item->status = QString::fromUtf8("等待报单");
                                insA_item->status_step = 2;
                                insA_item->order_err_count = 0;
                                insA_item->button_1.button_text = QString::fromUtf8("下单中");
                                insA_item->button_1.enbale = false;
                                update_trading_UI(*trading_item);
                            }
                        }
                    }
                }
            }
        }

    }
    else if (strlist.value(0) == "button2") //stop button
    {
        index = strlist.value(1).toInt();
        subindex = strlist.value(2).toInt();
        for (i = list_size - 1; i >= 0; i--)
        {
            trading_item = &trading_list[i];

            if (trading_item->index == index) //匹配index
            {
                if (trading_item->instrumentB_trading_list[0].sub_index == subindex) //停止只判断B合约
                {
                    if (trading_item->instrumentB_trading_list[0].status_step == 1 || trading_item->instrumentB_trading_list[0].status_step == -100) //等待交易中
                    {
                        trading_item->instrumentB_trading_list[0].status_step = 50; //进入停止状态
                        trading_item->instrumentB_trading_list[0].button_2.button_text = QString::fromUtf8("停止中"); //进入停止状态
                        trading_item->instrumentB_trading_list[0].button_2.enbale = false;

                        //判断是否已挂单全部成交，如果全部成交直接处理，否则等待A完成。
                        if (trading_item->instrumentB_trading_list[0].finished_vol == trading_item->product_finished_vol) // todo 需要转换
                        {
                            //如果全部都已经停止，删除此行
                            if (trading_item->op_cl == CLOSE_POSITION) //平仓，更新持仓数据 后再删除
                            {
                                trading_item->close_position_status->button.button_text = QString::fromUtf8("平仓");
                                trading_item->close_position_status->button.enbale = true;
                                trading_item->close_position_status->spd_vol -= trading_item->close_position_status->close_spd_vol;
                                trading_item->close_position_status->close_spd_vol = 0;
                                trading_item->close_position_status->close_position_status = 0;
                                trading_item->close_position_status->vol_A = trading_item->close_position_status->spd_vol;
                                trading_item->close_position_status->vol_B = trading_item->close_position_status->spd_vol;
                                update_position_table_row(*trading_item->close_position_status);
                            }
                            //删除此挂单。
                            send_delete_trading_table_rows(QString::number(trading_item->index));
                            trading_list.removeAt(i);
                        }
                        else //如果有未成交A单，修改目标成交量，当所有完成时直接删除自己
                        {
                            trading_item->target_vol = trading_item->instrumentB_trading_list[0].finished_vol; //需要转换
                            trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待A成交");
                            update_trading_UI(*trading_item);
                        }
                    }
                    else if ((trading_item->instrumentB_trading_list[0].status_step == 3) ||
                        (trading_item->instrumentB_trading_list[0].status_step == 10))  //报单已经发出去，但是未成交完成。
                    {
                        //撤单+更新状态
                        trading_item->instrumentB_trading_list[0].status_step = 50; //进入停止状态
                        trading_item->instrumentB_trading_list[0].button_2.button_text = QString::fromUtf8("停止中"); //进入停止状态
                        trading_item->instrumentB_trading_list[0].button_2.enbale = false;
                        trading_item->instrumentB_trading_list[0].wait_order_time = QDateTime::currentDateTime();
                        update_trading_UI(*trading_item);

                        //发出撤单指令。
                        this->td->reqOrderAction(QString(this->td->jy.BrokerID),
                            trading_item->instrumentB_trading_list[0].insert_id_B.OrderSysID,
                            trading_item->instrumentB_trading_list[0].insert_id_B.JYS_ID,
                            InsrumentB);

                    }
                    else if (trading_item->instrumentB_trading_list[0].status_step == -1) //下单异常，的停止
                    {
                        trading_item->instrumentB_trading_list[0].status_step = 50; //保持异常状态
                        trading_item->instrumentB_trading_list[0].button_2.button_text = QString::fromUtf8("停止中"); //进入停止状态
                        trading_item->instrumentB_trading_list[0].button_2.enbale = false;

                        //判断是否已挂单全部成交，如果全部成交直接处理，否则等待A完成。
                        if (trading_item->instrumentB_trading_list[0].finished_vol == trading_item->product_finished_vol) // todo 需要转换
                        {
                            //如果全部都已经停止，删除此行
                            if (trading_item->op_cl == CLOSE_POSITION) //平仓，更新持仓数据 后再删除
                            {
                                trading_item->close_position_status->button.button_text = QString::fromUtf8("平仓");
                                trading_item->close_position_status->button.enbale = true;
                                trading_item->close_position_status->spd_vol -= trading_item->close_position_status->close_spd_vol;
                                trading_item->close_position_status->close_spd_vol = 0;
                                trading_item->close_position_status->close_position_status = 0;
                                trading_item->close_position_status->vol_A = trading_item->close_position_status->spd_vol;
                                trading_item->close_position_status->vol_B = trading_item->close_position_status->spd_vol;
                                update_position_table_row(*trading_item->close_position_status);
                            }
                            //删除此挂单。
                            send_delete_trading_table_rows(QString::number(trading_item->index));
                            trading_list.removeAt(i);
                        }
                        else //如果有未成交A单，修改目标成交量，当所有完成时直接删除自己
                        {
                            trading_item->target_vol = trading_item->instrumentB_trading_list[0].finished_vol; //需要转换
                            trading_item->instrumentB_trading_list[0].status = QString::fromUtf8("等待A成交");
                            update_trading_UI(*trading_item);
                        }
                    }
                }
            }
        }
    }
}

void pair_trading_process::receive_position_action(int index, double target_profit, int A_price_type, int B_price_type)
{
    //收到平仓命令

    if (!td->loginFlag)  //如果交易服务器未登录或者断开，无法平仓
    {
        emit send_log_message("交易服务器断开，无法操作！！！");
        return;
    }

    QList<position_status>::iterator position_item;

    //更新各个持仓状态
    for (position_item = position_list.begin(); position_item != position_list.end(); position_item++)
    {
        if (position_item->index == index) //匹配合约
        {
            //新增平仓操作

            trading_status new_trading = init_new_trading_status();
            new_trading.index = position_item->index;

            if (position_item->spd_direction == POSITION_SELL) //sell
            {
                new_trading.instrumentB_trading_list[0].direction = POSITION_SELL;
                new_trading.latest_spd_price = group_price.delta_AaBa_beta;
                new_trading.group_direction = POSITION_BUY;
                new_trading.target_price = position_item->cost - target_profit * HYstruct_A.hyds;
            }
            else //buy
            {
                new_trading.instrumentB_trading_list[0].direction = POSITION_BUY;
                new_trading.latest_spd_price = group_price.delta_AbBb_beta;
                new_trading.group_direction = POSITION_SELL;
                new_trading.target_price = position_item->cost + target_profit * HYstruct_A.hyds;
            }
            new_trading.B_price_type = B_price_type;
            new_trading.A_price_type = A_price_type;
            new_trading.target_vol = position_item->spd_vol;//todo 加入系数进行计算

            new_trading.instrumentB_trading_list[0].button_1.button_text = QString::fromUtf8("未下单");
            new_trading.instrumentB_trading_list[0].button_1.enbale = false;
            new_trading.instrumentB_trading_list[0].button_2.button_text = QString::fromUtf8("停止");
            new_trading.instrumentB_trading_list[0].button_2.enbale = true;
            new_trading.op_cl = CLOSE_POSITION;
            new_trading.instrumentB_trading_list[0].open_or_close = CLOSE_POSITION;
            new_trading.instrumentB_trading_list[0].status_step = 1;

            new_trading.close_position_status = &(*position_item);
            trading_list.append(new_trading);

            trading_table_row_UI row;
            row.index = QString::number(new_trading.index);
            row.sub_index = QString::number(new_trading.instrumentB_trading_list[0].sub_index);
            row.instrument = new_trading.instrumentB_trading_list[0].instrument;
            row.open_or_close = (new_trading.instrumentB_trading_list[0].open_or_close == OPEN_POSITION) ? "open" : "close";
            row.direction = (new_trading.instrumentB_trading_list[0].direction == POSITION_BUY) ? "buy" : "sell";
            row.order_price = "-";
            row.delta_latest_order = "-";
            row.order_vol = "-";
            row.finished_vol = "0";
            row.target_vol = QString::number(new_trading.target_vol);
            row.target_price = QString::number(new_trading.target_price);
            row.latest_spd_price = QString::number(new_trading.latest_spd_price);
            row.order_time = "-";
            row.status = new_trading.instrumentB_trading_list[0].status;
            row.button_1 = new_trading.instrumentB_trading_list[0].button_1;
            row.button_2 = new_trading.instrumentB_trading_list[0].button_2;

            if (new_trading.B_price_type == 1)
            {
                row.price_type = "B退|";
            }
            else if (new_trading.B_price_type == 2)
            {
                row.price_type = "B对|";
            }
            else
            {
                row.price_type = "B正|";
            }

            if (new_trading.A_price_type == 0)
            {
                row.price_type = row.price_type + "A目";
            }
            else
            {
                row.price_type = row.price_type + "A对";
            }
            emit send_add_trading_table_row(row);


            //更新持仓UI

            position_item->button.button_text = QString::fromUtf8("平仓中");
            position_item->button.enbale = false;
            position_item->close_position_status = 1;
            update_position_table_row(*position_item);
            emit send_log_message(row.index + "开始平仓");

            statistic_data.spd_close_times++;
        }
    }
}

void pair_trading_process::receive_position_edit(int index, bool is_delete, position_table_row_UI new_data)
{
    position_status* position_item;
    int i = 0;
    int size = position_list.size();

    //更新各个持仓状态
    for (i = size - 1; i >= 0; i--)
    {
        position_item = &position_list[i];
        //匹配合约
        if (position_item->index == index)
        {
            if (position_item->close_position_status != 0)
            {
                emit send_log_message(QString::number(position_item->index) + "平仓中，无法删除或者修改！");
                return;
            }
            if (is_delete) //删除
            {
                emit send_delete_position_table_row(QString::number(position_item->index));
                position_list.removeAt(i);
                emit send_log_message(QString::number(index) + "已删除！！！");
                return;
            }
            else
            {
                if (new_data.direction_spd == "buy")
                {
                    position_item->spd_direction = POSITION_BUY;
                    position_item->direction_A = POSITION_BUY;
                    position_item->direction_B = POSITION_SELL;
                }
                else
                {
                    position_item->spd_direction = POSITION_SELL;
                    position_item->direction_A = POSITION_SELL;
                    position_item->direction_B = POSITION_BUY;
                }
                position_item->spd_vol = new_data.vol_spd.toInt();
                position_item->vol_A = new_data.vol_spd.toInt();
                position_item->vol_B = new_data.vol_spd.toInt();
                position_item->position_time = new_data.position_time;
                emit send_log_message(QString::number(index) + "已经修改！！！");
                update_position_table_row(*position_item);
                emit sync_position_data(*position_item);
                return;
            }
        }
    }
}

//未使用此线程，单独while1线程太占用cpu资源。
void pair_trading_process::thread_data_process_fun1(void)
{


    while (fun1_thread_flag)
    {
        if (update_flag == 3 || (update_flag_first && update_flag != 0)) //确保有数据，且每次更新都更新
        {
            update_flag_first = true;
            update_flag = 0; // update flag
            //todo 统计耗时。
            group_price_update(); // 更新价格信息
            position_process_MD_data();
            //qDebug() << "计算耗时1:ms " << test.msecsTo(QTime::currentTime());
            trading_process_MD_data();//使用最新的市场数据和价格数据更新交易状态
            update_price_ui();
        }
    }
}
