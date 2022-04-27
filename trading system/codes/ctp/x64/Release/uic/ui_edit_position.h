/********************************************************************************
** Form generated from reading UI file 'edit_position.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_POSITION_H
#define UI_EDIT_POSITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_edit_position
{
public:
    QPushButton *pushButton_ok;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_index;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit_time;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_spd_direction;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *spinBox_spd_vol;

    void setupUi(QWidget *edit_position)
    {
        if (edit_position->objectName().isEmpty())
            edit_position->setObjectName(QString::fromUtf8("edit_position"));
        edit_position->resize(346, 249);
        edit_position->setMaximumSize(QSize(400, 400));
        edit_position->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 240, 230);"));
        pushButton_ok = new QPushButton(edit_position);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(10, 180, 93, 28));
        layoutWidget = new QWidget(edit_position);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 11, 149, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_index = new QLabel(layoutWidget);
        label_index->setObjectName(QString::fromUtf8("label_index"));
        label_index->setFont(font);

        horizontalLayout->addWidget(label_index);

        layoutWidget1 = new QWidget(edit_position);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 130, 271, 39));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        dateTimeEdit_time = new QDateTimeEdit(layoutWidget1);
        dateTimeEdit_time->setObjectName(QString::fromUtf8("dateTimeEdit_time"));

        horizontalLayout_4->addWidget(dateTimeEdit_time);

        layoutWidget2 = new QWidget(edit_position);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(11, 57, 191, 71));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        comboBox_spd_direction = new QComboBox(layoutWidget2);
        comboBox_spd_direction->addItem(QString());
        comboBox_spd_direction->addItem(QString());
        comboBox_spd_direction->setObjectName(QString::fromUtf8("comboBox_spd_direction"));

        horizontalLayout_2->addWidget(comboBox_spd_direction);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_3->addWidget(label_3);

        spinBox_spd_vol = new QSpinBox(layoutWidget2);
        spinBox_spd_vol->setObjectName(QString::fromUtf8("spinBox_spd_vol"));

        horizontalLayout_3->addWidget(spinBox_spd_vol);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(edit_position);

        QMetaObject::connectSlotsByName(edit_position);
    } // setupUi

    void retranslateUi(QWidget *edit_position)
    {
        edit_position->setWindowTitle(QApplication::translate("edit_position", "edit_position", nullptr));
        pushButton_ok->setText(QApplication::translate("edit_position", "\347\241\256\350\256\244\344\277\256\346\224\271", nullptr));
        label->setText(QApplication::translate("edit_position", "\347\274\226\345\217\267\357\274\232", nullptr));
        label_index->setText(QApplication::translate("edit_position", "0000000", nullptr));
        label_4->setText(QApplication::translate("edit_position", "\346\214\201\344\273\223\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QApplication::translate("edit_position", "spd\346\226\271\345\220\221\357\274\232", nullptr));
        comboBox_spd_direction->setItemText(0, QApplication::translate("edit_position", "buy", nullptr));
        comboBox_spd_direction->setItemText(1, QApplication::translate("edit_position", "sell", nullptr));

        label_3->setText(QApplication::translate("edit_position", "spd\346\225\260\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_position: public Ui_edit_position {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_POSITION_H
