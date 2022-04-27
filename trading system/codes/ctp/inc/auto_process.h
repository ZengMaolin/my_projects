#pragma once

#include <QWidget>
#include "ui_auto_process.h"
#pragma execution_character_set("utf-8")

class auto_process : public QWidget
{
    Q_OBJECT

public:
    auto_process(QWidget* parent = Q_NULLPTR);
    ~auto_process();

private:
    Ui::auto_process ui;

public slots:
    void receive_start_button_event();

public:
signals:
    void send_start_event(bool, QStringList);
};
