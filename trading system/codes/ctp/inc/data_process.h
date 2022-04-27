#pragma once

#include <QObject>
#include "pair_trading_process.h"
#include <QFile>
#include <QFileInfo>

#pragma execution_character_set("utf-8")

struct save_position_struct
{
    int index;
    int spd_direction;
    int spd_vol;
    int close_spd_vol;
    char instrumentA[20];
    int direction_A; // 0: buy other :sell
    int vol_A;
    char instrumentB[20];
    int direction_B; // 0: buy other :sell
    int vol_B;
    double profit;
    int profit_ticks;
    int profit_target;
    bool is_B_optimal;
    double cost_A;
    double cost_B;
    double cost;
    char position_time[50];
    char button_text[40];
    bool enable;

    CThostFtdcTradeField A_CJ;
    CThostFtdcTradeField B_CJ;

    //平仓相关
    int close_position_status; // 平仓状态。 0 ：未平仓  1：开始平仓，等待价格 10：平仓挂单中 100：平仓完成  
    double start_target_price;
};

struct save_history_position
{
    char index[20];
    char instrumentA[20];
    char instrumentB[20];
    char spd_direction[20];
    char spd_vol[20];
    char start_time[20];
    char start_target_price[20];
    char start_price[20];
    char end_time[20];
    char end_target_price[20];
    char end_price[20];
    char profit[20];
};

struct data_group
{
    save_position_struct position;
    QString file_path;
    int file_index;
    QFile* file;
};


class data_process : public QObject
{
    Q_OBJECT

public:
    data_process(pair_trading_process* pt, QObject* parent = nullptr);
    ~data_process();
    pair_trading_process* pt_p;
    QString m_sProjectPath;
    QString pair_trading_path;
    QString info_path;
    QSettings* m_IniFile;

    QList<data_group> data_list;

    QStandardItemModel* model_spd;
    QStandardItemModel* model_insA;
    QStandardItemModel* model_insB;

    QTimer* timer;



private:
    void load_setting_file(QString path);
    void load_file(QString path, QString name);
    void load_history_file(QString path);

    void update_statistic_tables();

    int update_event_count = 0;
    void sync_statistic_data(void);
    bool calculateVolatility(QList<double> queue, int periodOfSecond, double& fVolatility);

public slots:

    void start_data_process(void); //由信号触发
    void update_event(void);
    void delete_position_file(QString);
    void sync_position_file(position_status);
    void recieve_setting_value(trading_setting);
    void receive_history_data(history_position_status);

public:
signals:
    void send_pair_setting(trading_setting);
    void send_history_data(history_position_status);
};
