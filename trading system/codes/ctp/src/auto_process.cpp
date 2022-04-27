#include "auto_process.h"

auto_process::auto_process(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(this->ui.pushButton_start, SIGNAL(clicked()), this, SLOT(receive_start_button_event()));
}

auto_process::~auto_process()
{
}

void auto_process::receive_start_button_event(void)
{
    if (this->ui.pushButton_start->text() == QString::fromUtf8("开始自动化交易"))
    {
        this->ui.pushButton_start->setText(QString::fromUtf8("停止自动化交易"));
        QStringList data;
        send_start_event(true, data);
    }
    else
    {
        this->ui.pushButton_start->setText(QString::fromUtf8("开始自动化交易"));
        QStringList data;
        send_start_event(false, data);
    }
}
