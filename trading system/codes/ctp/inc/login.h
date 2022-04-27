#pragma once

#include <QWidget>
#include "ui_login.h"
#include <QSettings>
#include <QKeyEvent>

#pragma execution_character_set("utf-8")

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget* parent = Q_NULLPTR);
    ~login();
    void keyPressEvent(QKeyEvent*);

private:
    Ui::login ui;
    QSettings* m_IniFile;

public slots:
    void MDLogin();
    void TDLogin();
    void TD_AuthLogin();
    void set_status(QString);


public:
signals:
    void MD_send_message(QStringList);
    void TD_send_message(QStringList);
};
