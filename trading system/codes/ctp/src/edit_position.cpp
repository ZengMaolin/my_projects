#include "pair_trading.h"

edit_position::edit_position(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(this->ui.pushButton_ok, SIGNAL(clicked()), this, SLOT(save_event()));
}

edit_position::~edit_position()
{
}

void edit_position::set_position(position_table_row_UI position)
{
    position_save = position;

    ui.label_index->setText(position_save.index);

    if (position_save.direction_spd == "buy")
    {
        ui.comboBox_spd_direction->setCurrentIndex(0);
    }
    else
    {
        ui.comboBox_spd_direction->setCurrentIndex(1);
    }
    ui.spinBox_spd_vol->setValue(position_save.vol_spd.toInt());
    QString str = "2021-" + position.position_time;
    QDateTime time = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
    ui.dateTimeEdit_time->setDateTime(time);
}

void edit_position::save_event(void)
{
    if (0 == ui.comboBox_spd_direction->currentIndex())
    {
        position_save.direction_spd = "buy";
    }
    else
    {
        position_save.direction_spd = "sell";
    }
    position_save.vol_spd = QString::number(ui.spinBox_spd_vol->value());
    position_save.position_time = ui.dateTimeEdit_time->dateTime().toString("MM-dd hh:mm:ss");

    emit send_new_position(position_save);
}
