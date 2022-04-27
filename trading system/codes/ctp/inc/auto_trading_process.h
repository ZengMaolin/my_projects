#pragma once

#include <QObject>
#include "pair_trading_process.h"
#pragma execution_character_set("utf-8")



class auto_trading_process : public QObject
{
    Q_OBJECT

public:
    auto_trading_process(pair_trading_process* ptr, QObject* parent = nullptr);
    ~auto_trading_process();
    pair_trading_process* pt_p;

    bool atuo_tarding_flag = false;
    int total_positon_vol = 0;


public slots:
    void init_auto_trading(void);
    void timer_enevt(void);
    void start_auto_trading(bool, QStringList);


};
