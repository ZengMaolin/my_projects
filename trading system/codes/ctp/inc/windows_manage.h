#pragma once

#include <QObject>
#include "ctp.h"
#include "stdafx.h"
#include "login.h"
#include "Mdspi.h"
#include "tdspi.h"
#include "instrument_process.h"
#include "pair_trading.h"
#include "pair_trading_process.h"
#include "data_process.h"
#pragma execution_character_set("utf-8")

class windows_manage : public QObject
{
    Q_OBJECT

public:
    windows_manage(QObject* parent);
    ~windows_manage();
    login* p_login_window;
    ctp* p_ctp_window;
    Mdspi* md;
    Tdspi* td;
    instrument_process* Ins_pro;

    typedef struct
    {
        pair_trading* p_ui;
        pair_trading_process* p_process;
        QThread* threadID;
        data_process* data_Save_process;
        QThread* thread_Data;
        int index; //储存在list的index。初始化的时候赋值。
    }pair_struct;

    QList<pair_struct> pair_list;


    int login_way = 0; // 0: 只登陆行情 其它: 登陆交易系统
    int md_status = 0; // 0: 未登陆 1: 登陆成功
    int td_status = 0; // 0: 未登陆 1: 登陆成功

public slots:
    void get_md_login_data(QStringList);
    void get_md_login_ok();
    void get_td_login_data(QStringList);
    void get_td_login_ok();
    void init_pair_trading(QStringList);
    void load_config_pair_trading(QString file_path);
    void get_pair_quit_event(QStringList);
public:
signals:
    void send_ins_process_init(int mode);
    void send_pair_process_init(void);

public:
    pair_struct generate_pair_trading(void);
};
