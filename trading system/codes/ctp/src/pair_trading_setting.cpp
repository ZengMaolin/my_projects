#include "pair_trading_setting.h"
#include <QtWidgets/qmessagebox.h>

pair_trading_setting::pair_trading_setting(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(save_event()));
    read_trading_setting();
}

pair_trading_setting::~pair_trading_setting()
{
}

void pair_trading_setting::read_trading_setting(void)
{
    pair_trading_set_struct.sample_series_points = ui.spinBox_sample->value() * 120;

    //挂单参数
    pair_trading_set_struct.enable_order_start_time = ui.checkBox_start_time->isChecked();
    pair_trading_set_struct.order_delay_time = ui.spinBox_start_delay->value();
    pair_trading_set_struct.order_before_end_time = ui.spinBox_start_before->value();
    pair_trading_set_struct.order_total_points = ui.spinBox_start_total_points->value();
    pair_trading_set_struct.order_points = ui.spinBox_start_points->value();
    pair_trading_set_struct.is_B_cancel_times_OK = ui.checkBox_cacel_time->isChecked();
    pair_trading_set_struct.enable_optional_options = ui.checkBox_start_optional->isChecked();
    pair_trading_set_struct.enable_optional_A = ui.checkBox_start_optional_A->isChecked();
    pair_trading_set_struct.optional_A_value = ui.doubleSpinBox_start_optional_A_value->value();
    pair_trading_set_struct.enable_optional_B = ui.checkBox_start_optional_B->isChecked();
    pair_trading_set_struct.enable_optional_C = ui.checkBox_start_optional_C->isChecked();
    pair_trading_set_struct.enable_optional_D = ui.checkBox_start_optional_D->isChecked();
    pair_trading_set_struct.enable_optional_E = ui.checkBox_start_optional_E->isChecked();
    pair_trading_set_struct.optional_E_value = ui.spinBox_start_optional_E_value->value();

    pair_trading_set_struct.enable_optional_F = ui.checkBox_start_optional_F->isChecked();
    pair_trading_set_struct.optional_F_value = ui.spinBox_start_optional_F_value->value();

    //撤单参数
    pair_trading_set_struct.enable_cancel_time = ui.checkBox_cancel_time->isChecked();
    pair_trading_set_struct.cancel_before_time = ui.spinBox_cancel_before_end->value();
    pair_trading_set_struct.cancel_total_points = ui.spinBox_cancel_total_points->value();
    pair_trading_set_struct.cancel_points = ui.spinBox_cancel_points->value();
    pair_trading_set_struct.cancel_by_vol = ui.checkBox_cancel_by_vol->isChecked();
    pair_trading_set_struct.cancel_by_ticks = ui.checkBox_cancel_by_ticks->isChecked();
    pair_trading_set_struct.cancel_by_ticks_value = ui.spinBox_cancel_by_ticks_value->value();
    pair_trading_set_struct.cancel_by_Bticks = ui.checkBox_cancel_B_ticks->isChecked();
    pair_trading_set_struct.cancel_by_Bticks_value = ui.spinBox_cancel_B_ticks_value->value();
    pair_trading_set_struct.cancel_by_option_6 = ui.checkBox_cancel_option_6->isChecked();
    pair_trading_set_struct.cancel_by_option_7 = ui.checkBox_cancel_option_7->isChecked();


}

void pair_trading_setting::recieve_setting_value(trading_setting value)
{
    pair_trading_set_struct = value;

    ui.spinBox_sample->setValue(pair_trading_set_struct.sample_series_points / 120);

    //挂单参数
    ui.checkBox_start_time->setChecked(pair_trading_set_struct.enable_order_start_time);
    ui.spinBox_start_delay->setValue(pair_trading_set_struct.order_delay_time);
    ui.spinBox_start_before->setValue(pair_trading_set_struct.order_before_end_time);
    ui.spinBox_start_total_points->setValue(pair_trading_set_struct.order_total_points);
    ui.spinBox_start_points->setValue(pair_trading_set_struct.order_points);
    ui.checkBox_cacel_time->setChecked(pair_trading_set_struct.is_B_cancel_times_OK);
    ui.checkBox_start_optional->setChecked(pair_trading_set_struct.enable_optional_options);
    ui.checkBox_start_optional_A->setChecked(pair_trading_set_struct.enable_optional_A);
    ui.doubleSpinBox_start_optional_A_value->setValue(pair_trading_set_struct.optional_A_value);
    ui.checkBox_start_optional_B->setChecked(pair_trading_set_struct.enable_optional_B);
    ui.checkBox_start_optional_C->setChecked(pair_trading_set_struct.enable_optional_C);
    ui.checkBox_start_optional_D->setChecked(pair_trading_set_struct.enable_optional_D);
    ui.checkBox_start_optional_E->setChecked(pair_trading_set_struct.enable_optional_E);
    ui.spinBox_start_optional_E_value->setValue(pair_trading_set_struct.optional_E_value);

    ui.checkBox_start_optional_F->setChecked(pair_trading_set_struct.enable_optional_F);
    ui.spinBox_start_optional_F_value->setValue(pair_trading_set_struct.optional_F_value);

    //撤单参数
    ui.checkBox_cancel_time->setChecked(pair_trading_set_struct.enable_cancel_time);
    ui.spinBox_cancel_before_end->setValue(pair_trading_set_struct.cancel_before_time);
    ui.spinBox_cancel_total_points->setValue(pair_trading_set_struct.cancel_total_points);
    ui.spinBox_cancel_points->setValue(pair_trading_set_struct.cancel_points);
    ui.checkBox_cancel_by_vol->setChecked(pair_trading_set_struct.cancel_by_vol);
    ui.checkBox_cancel_by_ticks->setChecked(pair_trading_set_struct.cancel_by_ticks);
    ui.spinBox_cancel_by_ticks_value->setValue(pair_trading_set_struct.cancel_by_ticks_value);
    ui.checkBox_cancel_B_ticks->setChecked(pair_trading_set_struct.cancel_by_Bticks);
    ui.spinBox_cancel_B_ticks_value->setValue(pair_trading_set_struct.cancel_by_Bticks_value);
    ui.checkBox_cancel_option_6->setChecked(pair_trading_set_struct.cancel_by_option_6);
    ui.checkBox_cancel_option_7->setChecked(pair_trading_set_struct.cancel_by_option_7);
}

void pair_trading_setting::save_event(void)
{
    read_trading_setting();
    emit send_setting_value(pair_trading_set_struct);
    QMessageBox::information(this, "", QString::fromUtf8("参数已生效并保存！"));
}
