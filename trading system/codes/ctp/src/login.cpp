#include "login.h"
#include <QDebug>
#include <QFileInfo>


login::login(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);


    QString file_path = QCoreApplication::applicationDirPath() + "/info.ini";
    QFileInfo file(file_path);

    qDebug() << "开始了，开始了" << endl;
    if (file.exists()) //存在储存配置文件
    {
        m_IniFile = new QSettings(file_path, QSettings::IniFormat);
        m_IniFile->beginGroup("login");
        QString md_addr = m_IniFile->value("md_addr").toString();
        QString td_addr = m_IniFile->value("td_addr").toString();
        QString brokerID = m_IniFile->value("brokerID").toString();
        QString account = m_IniFile->value("account").toString();
        QString appId = m_IniFile->value("appID").toString();
        m_IniFile->endGroup();
        delete m_IniFile;

        ui.lineEdit_mdaddr->setText(md_addr);
        ui.lineEdit_tdaddr->setText(td_addr);
        ui.lineEdit_bidID->setText(brokerID);
        ui.lineEdit_userid->setText(account);
        ui.lineEdit_password->setText("");
        ui.lineEdit_AppID->setText(appId);
        ui.lineEdit_AuthCode->setText("");
    }
    connect(this->ui.pushButton_pass_login, SIGNAL(clicked()), this, SLOT(MDLogin()));
    connect(this->ui.pushButton_login, SIGNAL(clicked()), this, SLOT(TDLogin()));
    connect(this->ui.pushButton_login_auth, SIGNAL(clicked()), this, SLOT(TD_AuthLogin()));
}

login::~login()
{
}

void login::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) //按下enter键 登陆
    {
        TD_AuthLogin();
    }
}

void login::set_status(QString status)
{
    ui.label_status->setText(status);
}

void login::TDLogin()
{
    QString bal1 = ui.lineEdit_mdaddr->text();
    QString bal2 = ui.lineEdit_bidID->text();
    QString bal3 = ui.lineEdit_tdaddr->text();
    QString bal4 = ui.lineEdit_userid->text();
    QString bal5 = ui.lineEdit_password->text();
    QString bal6 = "direct";


    QStringList message;
    message << bal1 << bal2 << bal3 << bal4 << bal5 << bal6;
    emit TD_send_message(message);

    qDebug() << "sign in" << endl;

    set_status("login ...");

    QString file_path = QCoreApplication::applicationDirPath() + "/info.ini";
    m_IniFile = new QSettings(file_path, QSettings::IniFormat);
    m_IniFile->beginGroup("login");
    m_IniFile->setValue("md_addr", ui.lineEdit_mdaddr->text());
    m_IniFile->setValue("brokerID", ui.lineEdit_bidID->text());
    m_IniFile->setValue("td_addr", bal3);
    m_IniFile->setValue("account", bal4);
    m_IniFile->endGroup();
    delete m_IniFile;
}

void login::TD_AuthLogin()
{
    QString bal1 = ui.lineEdit_mdaddr->text();
    QString bal2 = ui.lineEdit_bidID->text();
    QString bal3 = ui.lineEdit_tdaddr->text();
    QString bal4 = ui.lineEdit_userid->text();
    QString bal5 = ui.lineEdit_password->text();
    QString bal6 = "auth";
    QString bal7 = ui.lineEdit_AppID->text();
    QString bal8 = ui.lineEdit_AuthCode->text();

    QStringList message;
    message << bal1 << bal2 << bal3 << bal4 << bal5 << bal6 << bal7 << bal8;
    emit TD_send_message(message);

    qDebug() << "sign in" << endl;

    set_status("login ...");

    QString file_path = QCoreApplication::applicationDirPath() + "/info.ini";
    m_IniFile = new QSettings(file_path, QSettings::IniFormat);
    m_IniFile->beginGroup("login");
    m_IniFile->setValue("md_addr", ui.lineEdit_mdaddr->text());
    m_IniFile->setValue("brokerID", ui.lineEdit_bidID->text());
    m_IniFile->setValue("td_addr", bal3);
    m_IniFile->setValue("account", bal4);
    m_IniFile->setValue("appID", bal7);
    m_IniFile->endGroup();
    delete m_IniFile;
}

//只登陆市场
void login::MDLogin()
{
    QString bal1 = ui.lineEdit_mdaddr->text();
    QString bal2 = ui.lineEdit_bidID->text();


    QStringList message;
    message << bal1 << bal2;
    emit MD_send_message(message);

    qDebug() << "sign in" << endl;

    set_status("login ...");

    QString file_path = QCoreApplication::applicationDirPath() + "/info.ini";
    m_IniFile = new QSettings(file_path, QSettings::IniFormat);
    m_IniFile->beginGroup("login");
    m_IniFile->setValue("md_addr", ui.lineEdit_mdaddr->text());
    m_IniFile->setValue("brokerID", ui.lineEdit_bidID->text());
    m_IniFile->endGroup();
    delete m_IniFile;

}
