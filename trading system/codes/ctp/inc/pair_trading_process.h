#pragma once

#include <QObject>
#include "pair_trading.h"
#include "Mdspi.h"
#include "tdspi.h"
#include <thread>
#include <QDateTime>
#include "pair_trading_setting.h"

#pragma execution_character_set("utf-8")

enum OPEN_CLOSE_TYPE
{
    OPEN_POSITION = 0,
    CLOSE_POSITION
};

enum POSITION_DIRECTION
{
    POSITION_BUY = 0,
    POSITION_SELL
};


struct order_insert_id
{
    TThostFtdcFrontIDType frontID;
    TThostFtdcSessionIDType sessionID;
    QString ReturnOrderRef;
    QString OrderSysID;
    QString JYS_ID; //交易所ID 撤单时使用
    bool is_canceled;
    QStringList TradeID; //成交ID
};
struct instrumentB_trading_status
{
    int sub_index;
    QString instrument;
    OPEN_CLOSE_TYPE open_or_close; // 0: open other: close
    POSITION_DIRECTION direction; // 0: buy other :sell
    double order_price;
    double A_order_price; //A使用目标价格的时候，使用此价格。此价格在B发出订单的时候确定。
    int delta_latest_order; //ticks
    int order_vol;
    int finished_vol;
    QString order_time;
    QString status;
    //0:idle 1：等待交易  2：等待报单 3：挂单成功 10：部分成交 100：全部成交 50：停止中 80:重新下单 -1：挂单失败 -100：异常状态，点击停止
    int status_step;
    trading_table_action_button button_1;
    trading_table_action_button button_2;
    order_insert_id insert_id_B;
    int order_err_count; //订单下撤单时异常计数器。
    QDateTime wait_order_time; //用于计算报单回报是否丢失
    instrumentB_trading_status()
    {
        sub_index = 0;
        order_price = 0;
        delta_latest_order = 0;
        order_vol = 0;
        finished_vol = 0;
        status_step = 0;
        order_err_count = 0;
    }
};

struct instrumentA_trading_status
{
    int sub_index;
    QString instrument;
    OPEN_CLOSE_TYPE open_or_close; // 0: open other: close
    POSITION_DIRECTION direction; // 0: buy other :sell
    double order_price;
    int delta_latest_order; //ticks
    int order_vol;
    int finished_vol;
    int leg_check_count;
    QString order_time;
    QString status;
    trading_table_action_button button_1;
    trading_table_action_button button_2;
    order_insert_id idA;
    //0:idle 1：等待交易  2：等待报单 3：挂单成功 10：部分成交 100：全部成交 50：停止中 80:重新下单 -1：挂单失败
    int status_step;
    int order_err_count; //订单下撤单时异常计数器。

    CThostFtdcTradeField B_CJ; //记录B成交单
    QDateTime wait_order_time; //用于计算报单回报是否丢失
    instrumentA_trading_status()
    {
        sub_index = 0;
        order_price = 0;
        delta_latest_order = 0;
        order_vol = 0;
        finished_vol = 0;
        status_step = 0;
        leg_check_count = 0;
        order_err_count = 0;
    }
};

struct position_status
{
    int index;
    POSITION_DIRECTION spd_direction;
    int spd_vol;
    int close_spd_vol;
    QString instrumentA;
    POSITION_DIRECTION direction_A; // 0: buy other :sell
    int vol_A;
    QString instrumentB;
    POSITION_DIRECTION direction_B; // 0: buy other :sell
    int vol_B;
    double profit;
    int profit_ticks;
    int profit_target;
    bool is_B_optimal;
    double cost_A;
    double cost_B;
    double cost;
    QString position_time;
    trading_table_action_button button;

    CThostFtdcTradeField A_CJ;
    CThostFtdcTradeField B_CJ;

    //平仓相关
    int close_position_status; // 平仓状态。 0 ：未平仓  1：开始平仓，等待价格 10：平仓挂单中 100：平仓完成  

    //记录相关
    double start_target_price;
    position_status()
    {
        profit = 0;
        profit_ticks = 0;
    }
};



struct trading_status
{
    int status; // 0: 初始化  1：等待交易  10：交易中  100：交易完成
    int index;
    int sub_index_count;
    int B_price_type; // 0：normal 1：B退1tick 2：使用对手价
    int A_price_type; //0:必须使用目标价格 1：使用对手价格

    POSITION_DIRECTION group_direction;
    double latest_spd_price;
    double target_price;
    int target_vol;
    int product_finished_vol;
    OPEN_CLOSE_TYPE op_cl;
    QList<instrumentB_trading_status> instrumentB_trading_list;
    QList<instrumentA_trading_status> instrumentA_trading_list;

    //平仓相关
    position_status* close_position_status;
    bool is_close_yesterday;
};


struct group_instrument_price
{
    double delta_AaBa; //A ask1 - B ask1
    double delta_AaBa_beta; //A ask1 - B ask1 * beta
    double delta_AaBa_higest;
    double delta_AaBa_lowest;
    double delta_AaBa_average;
    double delta_AaBa_average_total;
    int delta_AaBa_average_count;
    double delta_AbBb; //A ask1 - B bid1
    double delta_AbBb_beta; //A ask1 - B bid1 * beta
    double delta_AbBb_higest;
    double delta_AbBb_lowest;
    double delta_AbBb_average;
    double delta_AbBb_average_total;
    int delta_AbBb_average_count;
    QList<double> delta_AaBa_beta_series;
    bool delta_AaBa_beta_series_full;
    QList<double> delta_AbBb_beta_series;
    bool delta_AbBb_beta_series_full;

    //rival price
    double delta_rival_AaBb; //A ask1 - B ask1
    double delta_rival_AaBb_beta; //A ask1 - B ask1 * beta
    double delta_rival_AaBb_higest;
    double delta_rival_AaBb_lowest;
    double delta_rival_AaBb_average;
    double delta_rival_AaBb_average_total;
    int delta_rival_AaBb_average_count;
    double delta_rival_AbBa; //A ask1 - B bid1
    double delta_rival_AbBa_beta; //A ask1 - B bid1 * beta
    double delta_rival_AbBa_higest;
    double delta_rival_AbBa_lowest;
    double delta_rival_AbBa_average;
    double delta_rival_AbBa_average_total;
    int delta_rival_AbBa_average_count;
    QList<double> delta_rival_AaBb_beta_series;
    bool delta_rival_AaBb_beta_series_full;
    QList<double> delta_rival_AbBa_beta_series;
    bool delta_rival_AbBa_beta_series_full;
    group_instrument_price()
    {
        delta_AaBa = 0; //A ask1 - B ask1
        delta_AaBa_higest = -1000000;
        delta_AaBa_lowest = 1000000;
        delta_AaBa_average = 0;
        delta_AaBa_average_total = 0;
        delta_AaBa_average_count = 0;
        delta_AbBb = 0; //A ask1 - B bid1
        delta_AbBb_higest = -1000000;
        delta_AbBb_lowest = 1000000;
        delta_AbBb_average = 0;
        delta_AbBb_average_total = 0;
        delta_AbBb_average_count = 0;
        delta_AaBa_beta_series_full = false;
        delta_AbBb_beta_series_full = false;

        delta_rival_AaBb = 0; //A ask1 - B ask1
        delta_rival_AaBb_higest = -1000000;
        delta_rival_AaBb_lowest = 1000000;
        delta_rival_AaBb_average = 0;
        delta_rival_AaBb_average_total = 0;
        delta_rival_AaBb_average_count = 0;
        delta_rival_AbBa = 0; //A ask1 - B bid1
        delta_rival_AbBa_higest = -1000000;
        delta_rival_AbBa_lowest = 1000000;
        delta_rival_AbBa_average = 0;
        delta_rival_AbBa_average_total = 0;
        delta_rival_AbBa_average_count = 0;
        delta_rival_AaBb_beta_series_full = false;
        delta_rival_AbBa_beta_series_full = false;
    }
};

struct pair_trading_statistic
{
    int spd_total_positions; //持仓总量
    double spd_close_profit; //平仓盈亏
    double spd_rt_profit; //持仓盈亏
    int spd_open_times; //开仓次数
    int spd_close_times; //平仓次数

    int instrumentA_local_positons; //持仓-本地
    int instrumentA_remote_positions; //持仓-远程
    int instrumentA_order_times; //下单次数
    int instrumentA_finished_order_times; //成交次数
    int instrumentA_canceled_order_times; //撤单次数

    int instrumentB_local_positons; //持仓-本地 
    int instrumentB_remote_positions; //持仓-远程
    int instrumentB_order_times; //下单次数
    int instrumentB_finished_order_times; //成交次数
    int instrumentB_canceled_order_times; //撤单次数

    pair_trading_statistic()
    {
        spd_total_positions = 0; //持仓总量
        spd_close_profit = 0; //平仓盈亏
        spd_rt_profit = 0; //持仓盈亏
        spd_open_times = 0; //开仓次数
        spd_close_times = 0; //平仓次数

        instrumentA_local_positons = 0; //持仓-本地
        instrumentA_remote_positions = 0; //持仓-远程
        instrumentA_order_times = 0; //下单次数
        instrumentA_finished_order_times = 0; //成交次数
        instrumentA_canceled_order_times = 0; //撤单次数

        instrumentB_local_positons = 0; //持仓-本地 
        instrumentB_remote_positions = 0; //持仓-远程
        instrumentB_order_times = 0; //下单次数
        instrumentB_finished_order_times = 0; //成交次数
        instrumentB_canceled_order_times = 0; //撤单次数
    }
};

struct instrument_price
{
    double last;
    QList <double> last_price_series;
    double price_volatility;
    int delta_ticks_in_xmins;
    int ask1_vol;
    QList <int> ask1_vol_series;
    QList <int> ask1_vol_series_median;
    int median_ask1_vol;
    int quarter_ask1_vol;
    double ask1;
    double bid1;
    int bid1_vol;
    QList <int> bid1_vol_series;
    QList <int> bid1_vol_series_median;
    int median_bid1_vol;
    int quarter_bid1_vol;
    double up;
    double down;
    double OpenPrice;
    double preClosePrice;

    instrument_price()
    {
        last = 0;
        price_volatility = 0;
        delta_ticks_in_xmins = 0;
        ask1_vol = 0;
        median_ask1_vol = 0;
        quarter_ask1_vol = 0;
        ask1 = 0;
        bid1 = 0;
        bid1_vol;
        median_bid1_vol = 0;
        quarter_bid1_vol = 0;
        up = 0;
        down = 0;
        OpenPrice = 0;
        preClosePrice = 0;
    }
};

class auto_trading_process;

class pair_trading_process : public QObject
{
    Q_OBJECT

public:
    pair_trading_process(pair_trading* ptu, Mdspi* p_md, Tdspi* p_td, QObject* parent = nullptr);
    ~pair_trading_process();

    Mdspi* md;
    Tdspi* td;
    pair_trading* p_ui;
    double beta = 1;
    QString InsrumentA;
    QString InsrumentB;
    QString group_mode;
    instrument_price A_price;
    instrument_price B_price;
    group_instrument_price group_price;
    Tdspi::HYstruct HYstruct_A, HYstruct_B;
    QString widget_tab_index;
    bool is_lame_leg = false;
    int leg_count = -1;
    QTimer* timer = nullptr;

    pair_trading_statistic statistic_data;

    //test code
    int A_need_buy_vol = 0;
    int A_finished_vol = 0;
    int A_price_type = 0;
    int B_need_buy_vol = 0;
    int B_finished_vol = 0;
    int B_price_type = 0;
    int status = 0;

    //index
    int position_status_index = 5000000;
    int trading_process_index = 1000000;
    int history_process_index = 0;
    QList<trading_status> trading_list;
    QList<position_status> position_list;
    QList<history_position_status> history_position_list;
public:
    auto_trading_process* auto_trade;
    QThread* auto_objThread = nullptr;
    void thread_data_process_fun1();
    bool fun1_thread_flag = true;

    trading_setting pair_setting;

    QTime test;
    QTime test2;
    int time_count = 0;

private:
    int update_flag = 0;
    bool update_flag_first = false;
    std::thread* data_process_thread = nullptr;

    void group_price_update();
    trading_status init_new_trading_status(void);
    int get_position_status_index(void);
    int get_history_position_index(void);
    bool judge_whther_start_order(trading_status trading_item);
    bool judge_whther_cancel_order(trading_status trading_item);
    void trading_process_MD_data();
    void update_trading_UI(trading_status ts);
    void position_process_MD_data(void);
    void update_position_table_row(position_status new_row);
    void add_position_table_row(position_status new_row);

public slots:
    void init_ui_data();
    void update_event();
    void receive_hq_data(CThostFtdcDepthMarketDataField MarketData);
    void update_price_ui(void);
    void receive_buy_event(QList<double>);
    void receive_WT_data(CThostFtdcOrderField wt_data);
    void receive_CJ_data(CThostFtdcTradeField cj_data);

    void receive_trading_action(QString); //接收到交易中操作按钮的信号
    void receive_position_action(int, double, int, int);
    void receive_position_edit(int, bool, position_table_row_UI);

public:
signals:
    void send_charts_data(double, double, double, double, double, double, QDateTime);
    void send_charts_data2(double, double, double, double, double, double, QDateTime);
    void send_price_value(QStringList, QStringList, QStringList, QStringList);
    void send_add_trading_table_row(trading_table_row_UI);
    void send_update_trading_table_row(trading_table_row_UI);
    void send_delete_trading_table_rows(QString);

    void send_add_position_table_row(position_table_row_UI);
    void send_update_position_table_days(position_table_row_UI);
    void send_update_position_table_row(position_table_row_UI);
    void send_delete_position_table_row(QString);

    void send_add_history_table_row(history_position_status);

    void sync_position_data(position_status);
    void send_log_message(QString);
    void send_auto_process_start(void);
    void send_tabwidget_text_color(QString index);
    void send_leg_warning_show(QString index);
};
