/********************************************************************************
** Form generated from reading UI file 'auto_process.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTO_PROCESS_H
#define UI_AUTO_PROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_auto_process
{
public:
    QLabel *label;
    QPushButton *pushButton_start;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;

    void setupUi(QWidget *auto_process)
    {
        if (auto_process->objectName().isEmpty())
            auto_process->setObjectName(QString::fromUtf8("auto_process"));
        auto_process->resize(978, 782);
        auto_process->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        label = new QLabel(auto_process);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 731, 51));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pushButton_start = new QPushButton(auto_process);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(350, 700, 141, 61));
        pushButton_start->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 100, 0);"));
        widget = new QWidget(auto_process);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 720, 300, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(11);
        lineEdit->setFont(font2);

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(auto_process);

        QMetaObject::connectSlotsByName(auto_process);
    } // setupUi

    void retranslateUi(QWidget *auto_process)
    {
        auto_process->setWindowTitle(QApplication::translate("auto_process", "auto_process", nullptr));
        label->setText(QApplication::translate("auto_process", "\350\207\252\345\212\250\345\214\226\344\272\244\346\230\223", nullptr));
        pushButton_start->setText(QApplication::translate("auto_process", "\345\274\200\345\247\213\350\207\252\345\212\250\345\214\226\344\272\244\346\230\223", nullptr));
        label_2->setText(QApplication::translate("auto_process", "\350\207\252\345\212\250\345\214\226\345\256\236\344\276\213\344\270\252\346\225\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class auto_process: public Ui_auto_process {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTO_PROCESS_H
