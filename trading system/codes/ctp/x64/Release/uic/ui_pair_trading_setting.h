/********************************************************************************
** Form generated from reading UI file 'pair_trading_setting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAIR_TRADING_SETTING_H
#define UI_PAIR_TRADING_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pair_trading_setting
{
public:
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *spinBox_sample;
    QLabel *label_3;
    QWidget *widget_order;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_start_time;
    QSpinBox *spinBox_start_delay;
    QLabel *label_5;
    QSpinBox *spinBox_start_before;
    QLabel *label_6;
    QCheckBox *checkBox_cacel_time;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QSpinBox *spinBox_start_total_points;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QSpinBox *spinBox_start_points;
    QLabel *label_9;
    QCheckBox *checkBox_start_optional;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_start_optional_A;
    QDoubleSpinBox *doubleSpinBox_start_optional_A_value;
    QLabel *label_12;
    QCheckBox *checkBox_start_optional_B;
    QCheckBox *checkBox_start_optional_C;
    QCheckBox *checkBox_start_optional_D;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_start_optional_E;
    QSpinBox *spinBox_start_optional_E_value;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_start_optional_F;
    QSpinBox *spinBox_start_optional_F_value;
    QLabel *label_14;
    QWidget *widget_cancel;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_cancel_time;
    QSpinBox *spinBox_cancel_before_end;
    QLabel *label_18;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_25;
    QSpinBox *spinBox_cancel_total_points;
    QLabel *label_20;
    QLabel *label_21;
    QSpinBox *spinBox_cancel_points;
    QLabel *label_22;
    QCheckBox *checkBox_cancel_by_vol;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox_cancel_by_ticks;
    QSpinBox *spinBox_cancel_by_ticks_value;
    QLabel *label_26;
    QLabel *label_24;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox_cancel_B_ticks;
    QSpinBox *spinBox_cancel_B_ticks_value;
    QLabel *label_23;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *checkBox_cancel_option_6;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *checkBox_cancel_option_7;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_save;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *pair_trading_setting)
    {
        if (pair_trading_setting->objectName().isEmpty())
            pair_trading_setting->setObjectName(QString::fromUtf8("pair_trading_setting"));
        pair_trading_setting->resize(520, 900);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pair_trading_setting->sizePolicy().hasHeightForWidth());
        pair_trading_setting->setSizePolicy(sizePolicy);
        pair_trading_setting->setMaximumSize(QSize(520, 900));
        verticalLayout_4 = new QVBoxLayout(pair_trading_setting);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(pair_trading_setting);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(pair_trading_setting);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox_sample = new QSpinBox(pair_trading_setting);
        spinBox_sample->setObjectName(QString::fromUtf8("spinBox_sample"));
        spinBox_sample->setMaximumSize(QSize(50, 16777215));
        spinBox_sample->setMinimum(1);
        spinBox_sample->setMaximum(100);
        spinBox_sample->setValue(10);

        horizontalLayout->addWidget(spinBox_sample);

        label_3 = new QLabel(pair_trading_setting);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);


        verticalLayout_4->addLayout(horizontalLayout);

        widget_order = new QWidget(pair_trading_setting);
        widget_order->setObjectName(QString::fromUtf8("widget_order"));
        widget_order->setStyleSheet(QString::fromUtf8("#widget_order{\n"
"background-color: rgb(255, 240, 240);\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(widget_order);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(widget_order);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox_start_time = new QCheckBox(widget_order);
        checkBox_start_time->setObjectName(QString::fromUtf8("checkBox_start_time"));

        horizontalLayout_2->addWidget(checkBox_start_time);

        spinBox_start_delay = new QSpinBox(widget_order);
        spinBox_start_delay->setObjectName(QString::fromUtf8("spinBox_start_delay"));
        spinBox_start_delay->setMaximumSize(QSize(50, 16777215));
        spinBox_start_delay->setMaximum(999);
        spinBox_start_delay->setValue(10);

        horizontalLayout_2->addWidget(spinBox_start_delay);

        label_5 = new QLabel(widget_order);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        spinBox_start_before = new QSpinBox(widget_order);
        spinBox_start_before->setObjectName(QString::fromUtf8("spinBox_start_before"));
        spinBox_start_before->setMaximumSize(QSize(50, 16777215));
        spinBox_start_before->setMaximum(999);
        spinBox_start_before->setValue(10);

        horizontalLayout_2->addWidget(spinBox_start_before);

        label_6 = new QLabel(widget_order);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout_2);

        checkBox_cacel_time = new QCheckBox(widget_order);
        checkBox_cacel_time->setObjectName(QString::fromUtf8("checkBox_cacel_time"));
        checkBox_cacel_time->setEnabled(true);
        checkBox_cacel_time->setChecked(true);

        verticalLayout_2->addWidget(checkBox_cacel_time);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(widget_order);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        spinBox_start_total_points = new QSpinBox(widget_order);
        spinBox_start_total_points->setObjectName(QString::fromUtf8("spinBox_start_total_points"));
        spinBox_start_total_points->setMaximumSize(QSize(50, 16777215));
        spinBox_start_total_points->setMinimum(1);
        spinBox_start_total_points->setMaximum(999);
        spinBox_start_total_points->setValue(1);

        horizontalLayout_4->addWidget(spinBox_start_total_points);

        label_7 = new QLabel(widget_order);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_10 = new QLabel(widget_order);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_3->addWidget(label_10);

        spinBox_start_points = new QSpinBox(widget_order);
        spinBox_start_points->setObjectName(QString::fromUtf8("spinBox_start_points"));
        spinBox_start_points->setMaximumSize(QSize(50, 16777215));
        spinBox_start_points->setMinimum(1);
        spinBox_start_points->setMaximum(999);
        spinBox_start_points->setValue(1);

        horizontalLayout_3->addWidget(spinBox_start_points);

        label_9 = new QLabel(widget_order);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        checkBox_start_optional = new QCheckBox(widget_order);
        checkBox_start_optional->setObjectName(QString::fromUtf8("checkBox_start_optional"));

        verticalLayout_2->addWidget(checkBox_start_optional);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_start_optional_A = new QCheckBox(widget_order);
        checkBox_start_optional_A->setObjectName(QString::fromUtf8("checkBox_start_optional_A"));

        horizontalLayout_5->addWidget(checkBox_start_optional_A);

        doubleSpinBox_start_optional_A_value = new QDoubleSpinBox(widget_order);
        doubleSpinBox_start_optional_A_value->setObjectName(QString::fromUtf8("doubleSpinBox_start_optional_A_value"));
        doubleSpinBox_start_optional_A_value->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(doubleSpinBox_start_optional_A_value);

        label_12 = new QLabel(widget_order);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_5->addWidget(label_12);


        verticalLayout->addLayout(horizontalLayout_5);

        checkBox_start_optional_B = new QCheckBox(widget_order);
        checkBox_start_optional_B->setObjectName(QString::fromUtf8("checkBox_start_optional_B"));
        checkBox_start_optional_B->setEnabled(true);

        verticalLayout->addWidget(checkBox_start_optional_B);

        checkBox_start_optional_C = new QCheckBox(widget_order);
        checkBox_start_optional_C->setObjectName(QString::fromUtf8("checkBox_start_optional_C"));
        checkBox_start_optional_C->setEnabled(true);

        verticalLayout->addWidget(checkBox_start_optional_C);

        checkBox_start_optional_D = new QCheckBox(widget_order);
        checkBox_start_optional_D->setObjectName(QString::fromUtf8("checkBox_start_optional_D"));
        checkBox_start_optional_D->setEnabled(true);

        verticalLayout->addWidget(checkBox_start_optional_D);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox_start_optional_E = new QCheckBox(widget_order);
        checkBox_start_optional_E->setObjectName(QString::fromUtf8("checkBox_start_optional_E"));
        checkBox_start_optional_E->setEnabled(true);

        horizontalLayout_6->addWidget(checkBox_start_optional_E);

        spinBox_start_optional_E_value = new QSpinBox(widget_order);
        spinBox_start_optional_E_value->setObjectName(QString::fromUtf8("spinBox_start_optional_E_value"));
        spinBox_start_optional_E_value->setEnabled(true);
        spinBox_start_optional_E_value->setValue(2);

        horizontalLayout_6->addWidget(spinBox_start_optional_E_value);

        label_13 = new QLabel(widget_order);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_6->addWidget(label_13);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        checkBox_start_optional_F = new QCheckBox(widget_order);
        checkBox_start_optional_F->setObjectName(QString::fromUtf8("checkBox_start_optional_F"));
        checkBox_start_optional_F->setEnabled(true);

        horizontalLayout_7->addWidget(checkBox_start_optional_F);

        spinBox_start_optional_F_value = new QSpinBox(widget_order);
        spinBox_start_optional_F_value->setObjectName(QString::fromUtf8("spinBox_start_optional_F_value"));

        horizontalLayout_7->addWidget(spinBox_start_optional_F_value);

        label_14 = new QLabel(widget_order);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_7->addWidget(label_14);


        verticalLayout->addLayout(horizontalLayout_7);


        horizontalLayout_9->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_9);


        verticalLayout_4->addWidget(widget_order);

        widget_cancel = new QWidget(pair_trading_setting);
        widget_cancel->setObjectName(QString::fromUtf8("widget_cancel"));
        widget_cancel->setStyleSheet(QString::fromUtf8("#widget_cancel{\n"
"background-color: rgb(200, 240, 240);\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(widget_cancel);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_15 = new QLabel(widget_cancel);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);

        verticalLayout_6->addWidget(label_15);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        checkBox_cancel_time = new QCheckBox(widget_cancel);
        checkBox_cancel_time->setObjectName(QString::fromUtf8("checkBox_cancel_time"));

        horizontalLayout_10->addWidget(checkBox_cancel_time);

        spinBox_cancel_before_end = new QSpinBox(widget_cancel);
        spinBox_cancel_before_end->setObjectName(QString::fromUtf8("spinBox_cancel_before_end"));
        spinBox_cancel_before_end->setMaximumSize(QSize(50, 16777215));
        spinBox_cancel_before_end->setMaximum(999);
        spinBox_cancel_before_end->setValue(10);

        horizontalLayout_10->addWidget(spinBox_cancel_before_end);

        label_18 = new QLabel(widget_cancel);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_10->addWidget(label_18);


        verticalLayout_6->addLayout(horizontalLayout_10);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_19 = new QLabel(widget_cancel);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_11->addWidget(label_19);


        gridLayout_2->addLayout(horizontalLayout_11, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_25 = new QLabel(widget_cancel);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_12->addWidget(label_25);

        spinBox_cancel_total_points = new QSpinBox(widget_cancel);
        spinBox_cancel_total_points->setObjectName(QString::fromUtf8("spinBox_cancel_total_points"));
        spinBox_cancel_total_points->setMaximumSize(QSize(50, 16777215));
        spinBox_cancel_total_points->setMinimum(1);
        spinBox_cancel_total_points->setMaximum(999);
        spinBox_cancel_total_points->setValue(1);

        horizontalLayout_12->addWidget(spinBox_cancel_total_points);

        label_20 = new QLabel(widget_cancel);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_12->addWidget(label_20);

        label_21 = new QLabel(widget_cancel);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_12->addWidget(label_21);

        spinBox_cancel_points = new QSpinBox(widget_cancel);
        spinBox_cancel_points->setObjectName(QString::fromUtf8("spinBox_cancel_points"));
        spinBox_cancel_points->setMaximumSize(QSize(50, 16777215));
        spinBox_cancel_points->setMinimum(1);
        spinBox_cancel_points->setMaximum(999);
        spinBox_cancel_points->setValue(1);

        horizontalLayout_12->addWidget(spinBox_cancel_points);

        label_22 = new QLabel(widget_cancel);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_12->addWidget(label_22);


        gridLayout_2->addLayout(horizontalLayout_12, 1, 0, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        checkBox_cancel_by_vol = new QCheckBox(widget_cancel);
        checkBox_cancel_by_vol->setObjectName(QString::fromUtf8("checkBox_cancel_by_vol"));
        checkBox_cancel_by_vol->setEnabled(true);

        verticalLayout_6->addWidget(checkBox_cancel_by_vol);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        checkBox_cancel_by_ticks = new QCheckBox(widget_cancel);
        checkBox_cancel_by_ticks->setObjectName(QString::fromUtf8("checkBox_cancel_by_ticks"));

        horizontalLayout_8->addWidget(checkBox_cancel_by_ticks);

        spinBox_cancel_by_ticks_value = new QSpinBox(widget_cancel);
        spinBox_cancel_by_ticks_value->setObjectName(QString::fromUtf8("spinBox_cancel_by_ticks_value"));
        spinBox_cancel_by_ticks_value->setMaximumSize(QSize(50, 16777215));
        spinBox_cancel_by_ticks_value->setMinimum(1);
        spinBox_cancel_by_ticks_value->setMaximum(999);
        spinBox_cancel_by_ticks_value->setValue(5);

        horizontalLayout_8->addWidget(spinBox_cancel_by_ticks_value);

        label_26 = new QLabel(widget_cancel);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_8->addWidget(label_26);


        verticalLayout_3->addLayout(horizontalLayout_8);

        label_24 = new QLabel(widget_cancel);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        verticalLayout_3->addWidget(label_24);


        verticalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        checkBox_cancel_B_ticks = new QCheckBox(widget_cancel);
        checkBox_cancel_B_ticks->setObjectName(QString::fromUtf8("checkBox_cancel_B_ticks"));

        horizontalLayout_14->addWidget(checkBox_cancel_B_ticks);

        spinBox_cancel_B_ticks_value = new QSpinBox(widget_cancel);
        spinBox_cancel_B_ticks_value->setObjectName(QString::fromUtf8("spinBox_cancel_B_ticks_value"));
        spinBox_cancel_B_ticks_value->setMaximumSize(QSize(50, 16777215));
        spinBox_cancel_B_ticks_value->setMinimum(1);
        spinBox_cancel_B_ticks_value->setValue(5);

        horizontalLayout_14->addWidget(spinBox_cancel_B_ticks_value);

        label_23 = new QLabel(widget_cancel);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_14->addWidget(label_23);


        verticalLayout_5->addLayout(horizontalLayout_14);

        label_28 = new QLabel(widget_cancel);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        verticalLayout_5->addWidget(label_28);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        checkBox_cancel_option_6 = new QCheckBox(widget_cancel);
        checkBox_cancel_option_6->setObjectName(QString::fromUtf8("checkBox_cancel_option_6"));
        checkBox_cancel_option_6->setEnabled(true);

        horizontalLayout_16->addWidget(checkBox_cancel_option_6);


        verticalLayout_6->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        checkBox_cancel_option_7 = new QCheckBox(widget_cancel);
        checkBox_cancel_option_7->setObjectName(QString::fromUtf8("checkBox_cancel_option_7"));
        checkBox_cancel_option_7->setEnabled(true);

        horizontalLayout_17->addWidget(checkBox_cancel_option_7);


        verticalLayout_6->addLayout(horizontalLayout_17);


        verticalLayout_4->addWidget(widget_cancel);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);

        pushButton_save = new QPushButton(pair_trading_setting);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_save->setFont(font2);

        horizontalLayout_13->addWidget(pushButton_save);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_13);


        retranslateUi(pair_trading_setting);

        QMetaObject::connectSlotsByName(pair_trading_setting);
    } // setupUi

    void retranslateUi(QWidget *pair_trading_setting)
    {
        pair_trading_setting->setWindowTitle(QApplication::translate("pair_trading_setting", "pair_trading_setting", nullptr));
        label->setText(QApplication::translate("pair_trading_setting", "\344\272\244\346\230\223\350\256\276\347\275\256", nullptr));
        label_2->setText(QApplication::translate("pair_trading_setting", "\351\207\207\346\240\267\351\230\237\345\210\227\345\210\206\351\222\237\350\267\250\345\272\246\357\274\232 X = ", nullptr));
        label_3->setText(QApplication::translate("pair_trading_setting", "\345\210\206\351\222\237\357\274\210\351\273\230\350\256\24410\345\210\206\351\222\237\357\274\211               ", nullptr));
        label_4->setText(QApplication::translate("pair_trading_setting", "\345\274\200/\345\271\263\344\273\223\346\214\202\345\215\225-\350\256\276\347\275\256", nullptr));
        checkBox_start_time->setText(QApplication::translate("pair_trading_setting", "1.\344\270\213\345\215\225\346\227\266\351\227\264\345\234\250\345\274\200\347\233\230", nullptr));
        label_5->setText(QApplication::translate("pair_trading_setting", "\345\210\206\351\222\237\345\220\216\357\274\214\346\224\266\347\233\230", nullptr));
        label_6->setText(QApplication::translate("pair_trading_setting", "\345\210\206\351\222\237\345\211\215", nullptr));
        checkBox_cacel_time->setText(QApplication::translate("pair_trading_setting", "2.B\344\273\212\345\244\251\346\222\244\345\215\225\346\254\241\346\225\260\345\205\205\350\266\263\357\274\210>50\357\274\211", nullptr));
        label_11->setText(QApplication::translate("pair_trading_setting", "3.\345\270\202\345\234\272\344\273\267\345\267\256\344\274\230\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\344\270\224\346\234\200\350\277\221", nullptr));
        label_7->setText(QApplication::translate("pair_trading_setting", "\344\270\252\344\273\267\345\267\256\345\272\217\345\210\227\344\270\255\357\274\214", nullptr));
        label_10->setText(QApplication::translate("pair_trading_setting", "  \346\234\211", nullptr));
        label_9->setText(QApplication::translate("pair_trading_setting", "\346\254\241\346\230\257\344\274\230\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\345\210\231\347\233\264\346\216\245\344\270\213\345\215\225\343\200\202          ", nullptr));
        checkBox_start_optional->setText(QApplication::translate("pair_trading_setting", "4.\345\217\257\351\200\211\345\217\202\346\225\260\350\256\276\347\275\256\357\274\210\346\273\241\350\266\263\345\205\250\351\203\250\351\200\211\344\270\255\344\270\272T\357\274\214\345\220\246\345\210\231\344\270\272F\357\274\211", nullptr));
        checkBox_start_optional_A->setText(QApplication::translate("pair_trading_setting", "a.X\345\210\206\351\222\237\345\271\263\345\235\207\344\273\267\345\267\256\344\270\215\345\212\243\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256", nullptr));
        label_12->setText(QApplication::translate("pair_trading_setting", "tick", nullptr));
        checkBox_start_optional_B->setText(QApplication::translate("pair_trading_setting", "b.\345\215\263\346\227\266A\346\214\202\345\215\225 > B\346\214\202\345\215\225", nullptr));
        checkBox_start_optional_C->setText(QApplication::translate("pair_trading_setting", "c.\345\215\263\346\227\266A\346\214\202\345\215\225\351\207\217>=X\345\210\206\351\222\237A\346\214\202\345\215\225\351\207\217\344\270\255\344\275\215\346\225\260", nullptr));
        checkBox_start_optional_D->setText(QApplication::translate("pair_trading_setting", "d.X\345\210\206\351\222\237A\346\214\202\345\215\225\351\207\217\344\270\255\344\275\215\346\225\260 > X\345\210\206\351\222\237B\346\214\202\345\215\225\351\207\217\344\270\255\344\275\215\346\225\260", nullptr));
        checkBox_start_optional_E->setText(QApplication::translate("pair_trading_setting", "e.\345\275\223\345\211\215A\344\273\267\346\240\27420\347\247\222\346\227\245\345\214\226\346\263\242\345\212\250\347\216\207 < ", nullptr));
        label_13->setText(QApplication::translate("pair_trading_setting", "%", nullptr));
        checkBox_start_optional_F->setText(QApplication::translate("pair_trading_setting", "f.X\345\210\206\351\222\237A\344\273\267\346\240\274\345\217\230\345\212\250\357\274\210\345\276\200\344\270\215\345\210\251\347\232\204\346\226\271\345\220\221\357\274\211\344\270\215\350\266\205\350\277\207", nullptr));
        label_14->setText(QApplication::translate("pair_trading_setting", "tick", nullptr));
        label_15->setText(QApplication::translate("pair_trading_setting", "\345\274\200/\345\271\263\344\273\223\346\222\244\345\215\225-\350\256\276\347\275\256", nullptr));
        checkBox_cancel_time->setText(QApplication::translate("pair_trading_setting", "1.\346\227\266\351\227\264\350\267\235\347\246\273\346\224\266\347\233\230\345\260\217\344\272\216", nullptr));
        label_18->setText(QApplication::translate("pair_trading_setting", "\345\210\206\351\222\237\357\274\214\345\210\231\346\222\244\345\215\225                   ", nullptr));
        label_19->setText(QApplication::translate("pair_trading_setting", "2.\345\270\202\345\234\272\344\273\267\345\267\256\345\212\243\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\344\270\224B\347\232\204\346\212\245\345\215\225\344\275\215\344\272\216\346\234\200\344\274\230\346\241\243\357\274\214\344\270\224\346\234\200\350\277\221", nullptr));
        label_25->setText(QString());
        label_20->setText(QApplication::translate("pair_trading_setting", "\344\270\252\344\273\267\345\267\256\345\272\217\345\210\227\344\270\255\357\274\214", nullptr));
        label_21->setText(QApplication::translate("pair_trading_setting", "\346\234\211", nullptr));
        label_22->setText(QApplication::translate("pair_trading_setting", "\346\254\241\346\230\257\345\212\243\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\345\210\231\346\222\244\345\215\225\343\200\202 ", nullptr));
        checkBox_cancel_by_vol->setText(QApplication::translate("pair_trading_setting", "3.\345\270\202\345\234\272\344\273\267\345\267\256\345\212\243\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\344\270\224B\345\244\204\344\272\216\346\234\200\344\274\230\346\241\243\357\274\214\344\270\224A\347\232\204\345\256\236\346\227\266\n"
"\346\214\202\345\215\225\351\207\217<max\357\274\210B.order, Q1\357\274\211,\345\210\231\346\222\244\345\215\225", nullptr));
        checkBox_cancel_by_ticks->setText(QApplication::translate("pair_trading_setting", "4.\345\270\202\345\234\272\344\273\267\345\267\256\345\212\243\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256", nullptr));
        label_26->setText(QApplication::translate("pair_trading_setting", "\344\270\252tick\344\273\245\344\270\212\357\274\214\344\270\224B\347\232\204\346\212\245\345\215\225", nullptr));
        label_24->setText(QApplication::translate("pair_trading_setting", "\344\275\215\344\272\216\346\234\200\344\274\230\346\241\243\357\274\214\345\210\231\346\222\244\345\215\225\343\200\202", nullptr));
        checkBox_cancel_B_ticks->setText(QApplication::translate("pair_trading_setting", "5.\345\270\202\345\234\272\346\234\200\346\226\260\346\210\220\344\272\244\344\273\267\350\267\235\347\246\273B\347\232\204\346\212\245\344\273\267\350\267\235\347\246\273>=", nullptr));
        label_23->setText(QApplication::translate("pair_trading_setting", "tick,\344\270\224B\347\232\204\346\212\245\345\215\225", nullptr));
        label_28->setText(QApplication::translate("pair_trading_setting", "\344\270\215\344\275\215\344\272\216\346\234\200\344\274\230\346\241\243\357\274\214\345\210\231\346\222\244\345\215\225\343\200\202", nullptr));
        checkBox_cancel_option_6->setText(QApplication::translate("pair_trading_setting", "6.\345\270\202\345\234\272\344\273\267\345\267\256\347\255\211\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\344\270\224B\344\275\215\344\272\216\346\234\200\344\274\230\346\241\243\357\274\214\344\270\224A\347\232\204\345\256\236\346\227\266\346\214\202\345\215\225\351\207\217< Q1\357\274\214\n"
"  \345\210\231\346\222\244\345\215\225", nullptr));
        checkBox_cancel_option_7->setText(QApplication::translate("pair_trading_setting", "7.\345\270\202\345\234\272\344\273\267\345\267\256\347\255\211\344\272\216\347\233\256\346\240\207\344\273\267\345\267\256\357\274\214\344\270\224B\344\275\215\344\272\216\346\234\200\344\274\230\346\241\243\357\274\214\344\270\224A\347\232\204\n"
"  \345\256\236\346\227\266\346\214\202\345\215\225\351\207\217< B.order,\345\210\231\346\222\244\345\215\225", nullptr));
        pushButton_save->setText(QApplication::translate("pair_trading_setting", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pair_trading_setting: public Ui_pair_trading_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAIR_TRADING_SETTING_H
