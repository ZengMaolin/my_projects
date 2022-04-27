#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ctp.h"
#include <QSettings>
#include <QtCharts>
#include <QTimer>
#include <QColor>

QT_CHARTS_USE_NAMESPACE
#pragma execution_character_set("utf-8")

class ctp : public QMainWindow
{
    Q_OBJECT

public:
    ctp(QWidget* parent = Q_NULLPTR);
    QString add_new_pair_trading(QWidget* new_tab, QString name);
    void set_spd_models(QStandardItemModel* spd);
    int leg_warnning_count = 0;

public:
signals:
    void send_add_hq_instrumentID(QString);
    void send_delete_hq_instrumentID(QString);
    void send_pair_trading_init(QStringList);
    void send_xiadan(QStringList);
    void send_load_configFile(QString);

public slots:
    void xiadan();
    void load_config_file(void);
    void receive_HQ(QString);
    void receive_CJ(QString);
    void receive_WT(QString);
    void receive_HY(QString);
    void receive_CC(QString);
    void receive_ZJ(QString);
    void OnWTMenu(const QPoint& pt);
    void OnHQMenu(const QPoint& pt);
    void chedan();
    void init_pair_trading();
    void add_hq_instrument();
    void delete_hq_hy(void);
    void update_time();
    void double_clicked_pair_list(void);
    void close_pair_trading(int index);
    void update_ctp_value(QStringList);
    void set_tabwidget_text_color(QString index);


private:
    Ui::ctpClass ui;
    QSettings* m_IniFile;
    QLabel* time_status;
    QLabel* td_status;
    QLabel* md_status;
    QLabel* id_status;

protected:
    void closeEvent(QCloseEvent* event);

};
