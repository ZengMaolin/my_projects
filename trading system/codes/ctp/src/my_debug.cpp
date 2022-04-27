#include "my_debug.h"
#include <QMutex>
#include <QDateTime>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>

my_debug::my_debug(QObject* parent)
    : QObject(parent)
{
}

my_debug::~my_debug()
{
}

QStringList log_data;
QMutex mutex_log;
void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    // 加锁
    mutex_log.lock();

    //QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch (type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("MM-dd hh:mm:ss.zzz");
    QString strMessage = QString("%1: %2")
        .arg(strDateTime).arg(msg);

    // 输出信息至缓存中（读写、追加形式）
    log_data << strMessage;

    // 解锁
    mutex_log.unlock();
}
