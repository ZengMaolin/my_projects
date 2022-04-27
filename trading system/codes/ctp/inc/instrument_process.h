#pragma once

#include <QObject>
#include "Mdspi.h"
#include "tdspi.h"
#include <QTimer>
#include <QDateTime>
#include <QWidget>
#include <QtCharts>
#pragma execution_character_set("utf-8")

class instrument_process : public QObject
{
    Q_OBJECT
        struct ctp_status
    {
        double available_money;
        double frozen_cash;
        double total_margin;
        QString MD_status;
        QString TD_Status;
        QString account;
        ctp_status()
        {
            available_money = 0;
            frozen_cash = 0;
            total_margin = 0;
        }
    };

public:
    instrument_process(Mdspi* p_md, Tdspi* p_td, QObject* parent = nullptr);
    ~instrument_process();
    Mdspi* md;
    Tdspi* td;
    char* g_pInstrumentID[5];
    int instrumentNum = 0;
    QList<QString> InstrumentID;
    QList<QStringList> All_instruments_info;
    ctp_status CTP_status;

    QStandardItemModel* spd_all_position_model;
    void update_all_position(void);
    void update_logFile(void);
    QString log_file_path;
    void load_position(QString dir_path, QString name);

public slots:
    void init(int);
    void receive_hq_data(CThostFtdcDepthMarketDataField MarketData);
    void add_hq_instrument(QString);
    void delete_hq_instrument(QString);
    void receive_HY_data(QString);
    void receive_ZJ_data(CThostFtdcTradingAccountField);
    void receive_CC_data(CThostFtdcInvestorPositionField cc_data);
    void receive_WT_data(CThostFtdcOrderField wt_data);
    void receive_CJ_data(CThostFtdcTradeField cj_data);

    void receive_trading_order(QStringList);
    void update_event(void);

public:

signals:
    void send_dataToUI(QString);
    void send_ZJdata_ui(QString);
    void send_CCdata_ui(QString);
    void send_WTdata_ui(QString);
    void send_CJdata_ui(QString);

    void send_ctp_status(QStringList);

private:
    void process_connect(void);

    void process_inquire(void);

};
