/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QFrame *frame_2;
    QLabel *label;
    QLabel *label_edtion;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_ss;
    QLabel *label_status;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *label_14;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_mdaddr;
    QLineEdit *lineEdit_tdaddr;
    QLineEdit *lineEdit_bidID;
    QLineEdit *lineEdit_userid;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_AppID;
    QLineEdit *lineEdit_AuthCode;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_login_auth;
    QPushButton *pushButton_login;
    QPushButton *pushButton_pass_login;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->setEnabled(true);
        login->resize(800, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(40);
        sizePolicy.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy);
        login->setMinimumSize(QSize(800, 500));
        login->setMaximumSize(QSize(800, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/temp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        login->setWindowIcon(icon);
        login->setStyleSheet(QString::fromUtf8("\n"
"#label_edtion{\n"
"	color: rgb(255, 255, 255);\n"
"	\n"
"	font: 20pt \"Arial\";\n"
"}\n"
" \n"
"QLineEdit{\n"
" \n"
"	border:2px solid#7b7b7b;\n"
"	border-radius:15px;\n"
"	background-color:#fffef0;\n"
"}\n"
"QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
" \n"
"QPushButton{\n"
"	border:2px solid#7b7b7b;\n"
"	border-radius:15px;\n"
"	background-color:#6a92ff;\n"
"	font: 75 15pt \"Arial\";\n"
"}\n"
" \n"
"QPushButton:hover{\n"
"	background-color:#aa92ff\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color:#FF90ff\n"
"}"));
        frame_2 = new QFrame(login);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, -10, 811, 511));
        frame_2->setStyleSheet(QString::fromUtf8("#frame_2{\n"
"border-image: url(:/login/image/login.jpg);\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 10, 551, 101));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(30);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        label_edtion = new QLabel(frame_2);
        label_edtion->setObjectName(QString::fromUtf8("label_edtion"));
        label_edtion->setGeometry(QRect(690, 460, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_edtion->setFont(font1);
        layoutWidget = new QWidget(frame_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 440, 501, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_ss = new QLabel(layoutWidget);
        label_ss->setObjectName(QString::fromUtf8("label_ss"));
        label_ss->setMaximumSize(QSize(60, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label_ss->setFont(font2);

        horizontalLayout->addWidget(label_ss);

        label_status = new QLabel(layoutWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font3.setPointSize(10);
        label_status->setFont(font3);
        label_status->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));

        horizontalLayout->addWidget(label_status);

        layoutWidget1 = new QWidget(frame_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(130, 100, 501, 321));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        frame_3 = new QFrame(layoutWidget1);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        label_2->setFont(font4);

        verticalLayout_3->addWidget(label_2);

        label_5 = new QLabel(frame_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font4);

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font4);

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(frame_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font4);

        verticalLayout_3->addWidget(label_7);

        label_8 = new QLabel(frame_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font4);

        verticalLayout_3->addWidget(label_8);

        label_13 = new QLabel(frame_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font4);

        verticalLayout_3->addWidget(label_13);

        label_14 = new QLabel(frame_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font4);

        verticalLayout_3->addWidget(label_14);


        horizontalLayout_4->addWidget(frame_3);

        frame = new QFrame(layoutWidget1);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
" \n"
"	border:2px solid#7b7b7b;\n"
"	border-radius:15px;\n"
"	background-color:#fffef0\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit_mdaddr = new QLineEdit(frame);
        lineEdit_mdaddr->setObjectName(QString::fromUtf8("lineEdit_mdaddr"));
        lineEdit_mdaddr->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_mdaddr);

        lineEdit_tdaddr = new QLineEdit(frame);
        lineEdit_tdaddr->setObjectName(QString::fromUtf8("lineEdit_tdaddr"));
        lineEdit_tdaddr->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_tdaddr);

        lineEdit_bidID = new QLineEdit(frame);
        lineEdit_bidID->setObjectName(QString::fromUtf8("lineEdit_bidID"));
        lineEdit_bidID->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_bidID);

        lineEdit_userid = new QLineEdit(frame);
        lineEdit_userid->setObjectName(QString::fromUtf8("lineEdit_userid"));
        lineEdit_userid->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(lineEdit_userid);

        lineEdit_password = new QLineEdit(frame);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setMinimumSize(QSize(0, 30));
        lineEdit_password->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_password);

        lineEdit_AppID = new QLineEdit(frame);
        lineEdit_AppID->setObjectName(QString::fromUtf8("lineEdit_AppID"));
        lineEdit_AppID->setMinimumSize(QSize(0, 30));
        lineEdit_AppID->setEchoMode(QLineEdit::Normal);

        verticalLayout->addWidget(lineEdit_AppID);

        lineEdit_AuthCode = new QLineEdit(frame);
        lineEdit_AuthCode->setObjectName(QString::fromUtf8("lineEdit_AuthCode"));
        lineEdit_AuthCode->setMinimumSize(QSize(0, 30));
        lineEdit_AuthCode->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_AuthCode);


        horizontalLayout_4->addWidget(frame);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_login_auth = new QPushButton(layoutWidget1);
        pushButton_login_auth->setObjectName(QString::fromUtf8("pushButton_login_auth"));
        pushButton_login_auth->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_login_auth->sizePolicy().hasHeightForWidth());
        pushButton_login_auth->setSizePolicy(sizePolicy2);
        pushButton_login_auth->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(pushButton_login_auth);

        pushButton_login = new QPushButton(layoutWidget1);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setEnabled(true);
        sizePolicy2.setHeightForWidth(pushButton_login->sizePolicy().hasHeightForWidth());
        pushButton_login->setSizePolicy(sizePolicy2);
        pushButton_login->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(pushButton_login);

        pushButton_pass_login = new QPushButton(layoutWidget1);
        pushButton_pass_login->setObjectName(QString::fromUtf8("pushButton_pass_login"));
        sizePolicy2.setHeightForWidth(pushButton_pass_login->sizePolicy().hasHeightForWidth());
        pushButton_pass_login->setSizePolicy(sizePolicy2);
        pushButton_pass_login->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(pushButton_pass_login);


        verticalLayout_5->addLayout(horizontalLayout_3);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", nullptr));
        label->setText(QApplication::translate("login", "PAIR TRADING \344\272\244\346\230\223\347\263\273\347\273\237", nullptr));
        label_edtion->setText(QApplication::translate("login", "V4.05", nullptr));
        label_ss->setText(QApplication::translate("login", "Status\357\274\232", nullptr));
        label_status->setText(QApplication::translate("login", "\346\234\252\347\231\273\351\231\206", nullptr));
        label_2->setText(QApplication::translate("login", "M      D:", nullptr));
        label_5->setText(QApplication::translate("login", "T      D:", nullptr));
        label_6->setText(QApplication::translate("login", "BROKER  :", nullptr));
        label_7->setText(QApplication::translate("login", "USER    :", nullptr));
        label_8->setText(QApplication::translate("login", "PWD     :", nullptr));
        label_13->setText(QApplication::translate("login", "APPID   :", nullptr));
        label_14->setText(QApplication::translate("login", "AUTHCODE:", nullptr));
        lineEdit_mdaddr->setText(QString());
        lineEdit_mdaddr->setPlaceholderText(QApplication::translate("login", "   MD address", nullptr));
        lineEdit_tdaddr->setText(QString());
        lineEdit_tdaddr->setPlaceholderText(QApplication::translate("login", "   TD address", nullptr));
        lineEdit_bidID->setText(QString());
        lineEdit_bidID->setPlaceholderText(QApplication::translate("login", "   Broker ID", nullptr));
        lineEdit_userid->setText(QString());
        lineEdit_userid->setPlaceholderText(QApplication::translate("login", "   User ID", nullptr));
        lineEdit_password->setText(QString());
        lineEdit_password->setPlaceholderText(QApplication::translate("login", "   Password", nullptr));
        lineEdit_AppID->setText(QString());
        lineEdit_AppID->setPlaceholderText(QApplication::translate("login", "   App id", nullptr));
        lineEdit_AuthCode->setText(QString());
        lineEdit_AuthCode->setPlaceholderText(QApplication::translate("login", "   Auth code", nullptr));
        pushButton_login_auth->setText(QApplication::translate("login", "\350\256\244\350\257\201\347\231\273\351\231\206", nullptr));
        pushButton_login->setText(QApplication::translate("login", "\347\233\264\346\216\245\347\231\273\351\231\206", nullptr));
        pushButton_pass_login->setText(QApplication::translate("login", "\347\233\264\346\216\245\350\277\233\345\205\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
