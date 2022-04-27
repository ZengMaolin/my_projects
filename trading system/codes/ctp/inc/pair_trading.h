#pragma once

#include <QWidget>
#include "ui_pair_trading.h"
#include <QtCharts>
#include <QTimer>
#include <QDateTime>
#include <QColor>
#include "auto_process.h"
#include "pair_trading_setting.h"
#include "ui_edit_position.h"

#pragma execution_character_set("utf-8")
QT_CHARTS_USE_NAMESPACE

struct trading_table_action_button
{
    QString button_text;
    bool enbale;
};

struct history_position_status
{
    QString index;
    QString instrumentA;
    QString instrumentB;
    QString spd_direction;
    QString spd_vol;
    QString start_time;
    QString start_target_price;
    QString start_price;
    QString end_time;
    QString end_target_price;
    QString end_price;
    QString profit;
};

struct trading_table_row_UI
{
    QString index;
    QString sub_index;
    QString price_type;
    QString instrument;
    QString open_or_close; // 0: open other: close
    QString direction; // 0: buy other :sell
    QString order_price;
    QString delta_latest_order;
    QString order_vol;
    QString finished_vol;
    QString target_vol;
    QString target_price;
    QString latest_spd_price;
    QString order_time;
    QString status;
    trading_table_action_button button_1;
    trading_table_action_button button_2;
};

struct position_table_row_UI
{
    QString index;
    QString direction_spd;
    QString vol_spd;
    QString instrumentA;
    QString direction_A; // 0: buy other :sell
    QString vol_A;
    QString instrumentB;
    QString direction_B; // 0: buy other :sell
    QString vol_B;
    QString profit;
    QString profit_ticks;
    QString profit_target;
    bool is_B_optimal;
    QString cost;
    QString position_time;
    trading_table_action_button button;
    QString potions_days;
};

//这类在这里声明，作为此模块子窗口
class edit_position : public QWidget
{
    Q_OBJECT

public:
    edit_position(QWidget* parent = Q_NULLPTR);
    ~edit_position();
    void set_position(position_table_row_UI position);

private:
    Ui::edit_position ui;
    position_table_row_UI position_save;

public slots:
    void save_event(void);

public:
signals:
    void send_new_position(position_table_row_UI);
};

class pair_trading : public QWidget
{
    Q_OBJECT

public:
    pair_trading(QWidget* parent = Q_NULLPTR);
    ~pair_trading();
    void init_initialparameters(QStringList);
    void set_config_file_parameter(QStringList parameters);


public slots:
    void update_price_value(QStringList price_group, QStringList price_A, QStringList price_B, QStringList price_group2);
    void receive_log(QString data);
    void dataReceived(double, double, double, double, double, double, QDateTime);
    void dataReceived2(double value1, double max1, double min1, double value2, double max2, double min2, QDateTime time);
    void buy_event(void);
    void reveive_add_trading_table_row(trading_table_row_UI);
    void reveive_update_trading_table_row(trading_table_row_UI row);
    void reveive_delete_trading_table_rows(QString index);
    void trading_action();
    void position_action();
    void reveive_add_position_table_row(position_table_row_UI row);
    void reveive_update_position_table_row(position_table_row_UI row);
    void reveive_update_position_table_days(position_table_row_UI row);
    void reveive_delete_position_table_row(QString index);
    void receive_add_history_table_row(history_position_status);
    void auto_process_show(void);
    void setting_show(void);
    void set_spd_models(QStandardItemModel* spd, QStandardItemModel* spd_A, QStandardItemModel* spd_B);
    void OnPositionMenu(const QPoint& pt);

    void OnPosition_delete(void);

    void OnPosition_edit(void);

    void receive_Position_edit_ret(position_table_row_UI data);
    void leg_warning(QString message);

public:
signals:
    void send_buy_event(QList<double>);
    void send_trading_action(QString);
    void send_position_action(int, double, int, int);
    void send_close_event();
    void send_close_data(QStringList);
    void send_position_edit(int, bool, position_table_row_UI);
private:
    Ui::pair_trading ui;
private:
    edit_position edit_window;

protected:
    void closeEvent(QCloseEvent* event);

public:
    int maxSize = 500;  // data 最多存储 maxSize 个元素
    int maxX;
    int maxY = 100;

    QChart* chart;
    QDateTimeAxis* mAxDateX;
    QValueAxis* mAxY;
    QLineSeries* splineSeries;
    QLineSeries* splineSeries2;

    QChart* chart2;
    QDateTimeAxis* mAxDateX2;
    QValueAxis* mAxY2;
    QLineSeries* splineSeries3;
    QLineSeries* splineSeries4;

    auto_process* auto_ui;
    pair_trading_setting* setting_ui;
};
