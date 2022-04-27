#pragma once

#include <QWidget>
#include "ui_pair_trading_setting.h"

#pragma execution_character_set("utf-8")

struct trading_setting
{
    int sample_series_points; //minutes * 120

    //挂单设置参数
    bool enable_order_start_time;
    int order_delay_time; //minutes
    int order_before_end_time;//minutes
    int order_total_points;
    int order_points;
    bool is_B_cancel_times_OK;
    bool enable_optional_options;
    bool enable_optional_A; //
    double optional_A_value;
    bool enable_optional_B;
    bool enable_optional_C;
    bool enable_optional_D;
    bool enable_optional_E;
    bool enable_optional_F;
    int optional_F_value;

    //撤单设置
    bool enable_cancel_time;
    int cancel_before_time;
    int cancel_total_points;
    int cancel_points;
    bool cancel_by_vol;
    bool cancel_by_ticks;
    int cancel_by_ticks_value;
    bool cancel_by_Bticks;
    int cancel_by_Bticks_value;
    bool cancel_by_option_6;
    bool cancel_by_option_7;

    //new add往后加-否则读取旧的数据会影响之前的设置。
    int optional_E_value;
    trading_setting()
    {
        sample_series_points = 0;
        enable_order_start_time = false;
        order_delay_time = 0;
        order_before_end_time = 0;
        order_total_points = 0;
        order_points = 0;
        is_B_cancel_times_OK = false;
        enable_optional_options = false;
        enable_optional_A = false;
        optional_A_value = 0;
        enable_optional_B = false;
        enable_optional_C = false;
        enable_optional_D = false;
        enable_optional_E = false;
        optional_E_value = 0;
        enable_optional_F = false;
        optional_F_value = 0;
        enable_cancel_time = false;
        cancel_before_time = 0;
        cancel_total_points = 0;
        cancel_points = 0;
        cancel_by_vol = false;
        cancel_by_ticks = false;
        cancel_by_ticks_value = 0;
        cancel_by_Bticks = false;
        cancel_by_Bticks_value = 0;
        cancel_by_option_6 = false;
        cancel_by_option_7 = false;
    }
};
class pair_trading_setting : public QWidget
{
    Q_OBJECT

public:
    pair_trading_setting(QWidget* parent = Q_NULLPTR);
    ~pair_trading_setting();
    trading_setting pair_trading_set_struct;
private:
    Ui::pair_trading_setting ui;
    void read_trading_setting(void);

public slots:
    void save_event(void);
    void recieve_setting_value(trading_setting);

public:
signals:
    void send_setting_value(trading_setting);
};
