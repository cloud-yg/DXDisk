/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPClient
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *statusbar_lab;
    QLabel *status_lab;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ip_lab;
    QLineEdit *ip_le;
    QLabel *port_lab;
    QLineEdit *port_le;
    QPushButton *connect_pb;
    QHBoxLayout *horizontalLayout_3;
    QLabel *name_lab;
    QLineEdit *name_le;
    QHBoxLayout *horizontalLayout_4;
    QLabel *pwd_lab;
    QLineEdit *pwd_le;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *login_pb;
    QPushButton *regist_pb;

    void setupUi(QWidget *TCPClient)
    {
        if (TCPClient->objectName().isEmpty())
            TCPClient->setObjectName("TCPClient");
        TCPClient->resize(472, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TCPClient->sizePolicy().hasHeightForWidth());
        TCPClient->setSizePolicy(sizePolicy);
        TCPClient->setMinimumSize(QSize(472, 300));
        TCPClient->setMaximumSize(QSize(472, 300));
        verticalLayout_2 = new QVBoxLayout(TCPClient);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        statusbar_lab = new QLabel(TCPClient);
        statusbar_lab->setObjectName("statusbar_lab");
        statusbar_lab->setMinimumSize(QSize(90, 50));
        statusbar_lab->setMaximumSize(QSize(90, 50));
        QFont font;
        font.setPointSize(12);
        statusbar_lab->setFont(font);

        horizontalLayout->addWidget(statusbar_lab);

        status_lab = new QLabel(TCPClient);
        status_lab->setObjectName("status_lab");
        status_lab->setEnabled(true);
        status_lab->setMinimumSize(QSize(340, 50));
        status_lab->setMaximumSize(QSize(340, 50));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        status_lab->setPalette(palette);
        status_lab->setFont(font);
        status_lab->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(status_lab);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        ip_lab = new QLabel(TCPClient);
        ip_lab->setObjectName("ip_lab");
        ip_lab->setEnabled(true);
        ip_lab->setMinimumSize(QSize(30, 50));
        ip_lab->setMaximumSize(QSize(40, 50));
        ip_lab->setFont(font);

        horizontalLayout_2->addWidget(ip_lab);

        ip_le = new QLineEdit(TCPClient);
        ip_le->setObjectName("ip_le");
        ip_le->setMinimumSize(QSize(160, 50));
        ip_le->setMaximumSize(QSize(160, 50));
        ip_le->setFont(font);

        horizontalLayout_2->addWidget(ip_le);

        port_lab = new QLabel(TCPClient);
        port_lab->setObjectName("port_lab");
        port_lab->setEnabled(true);
        port_lab->setMinimumSize(QSize(50, 50));
        port_lab->setMaximumSize(QSize(50, 50));
        port_lab->setFont(font);

        horizontalLayout_2->addWidget(port_lab);

        port_le = new QLineEdit(TCPClient);
        port_le->setObjectName("port_le");
        port_le->setMinimumSize(QSize(100, 50));
        port_le->setMaximumSize(QSize(100, 50));
        port_le->setFont(font);

        horizontalLayout_2->addWidget(port_le);

        connect_pb = new QPushButton(TCPClient);
        connect_pb->setObjectName("connect_pb");
        connect_pb->setMinimumSize(QSize(70, 50));
        connect_pb->setMaximumSize(QSize(70, 50));
        connect_pb->setFont(font);

        horizontalLayout_2->addWidget(connect_pb);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        name_lab = new QLabel(TCPClient);
        name_lab->setObjectName("name_lab");
        name_lab->setEnabled(true);
        name_lab->setMinimumSize(QSize(70, 50));
        name_lab->setMaximumSize(QSize(70, 50));
        name_lab->setFont(font);

        horizontalLayout_3->addWidget(name_lab);

        name_le = new QLineEdit(TCPClient);
        name_le->setObjectName("name_le");
        name_le->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(name_le->sizePolicy().hasHeightForWidth());
        name_le->setSizePolicy(sizePolicy1);
        name_le->setMinimumSize(QSize(360, 50));
        name_le->setMaximumSize(QSize(360, 50));
        name_le->setFont(font);

        horizontalLayout_3->addWidget(name_le);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pwd_lab = new QLabel(TCPClient);
        pwd_lab->setObjectName("pwd_lab");
        pwd_lab->setEnabled(true);
        pwd_lab->setMinimumSize(QSize(70, 50));
        pwd_lab->setMaximumSize(QSize(70, 50));
        pwd_lab->setFont(font);

        horizontalLayout_4->addWidget(pwd_lab);

        pwd_le = new QLineEdit(TCPClient);
        pwd_le->setObjectName("pwd_le");
        sizePolicy1.setHeightForWidth(pwd_le->sizePolicy().hasHeightForWidth());
        pwd_le->setSizePolicy(sizePolicy1);
        pwd_le->setMinimumSize(QSize(360, 50));
        pwd_le->setMaximumSize(QSize(360, 50));
        pwd_le->setFont(font);
        pwd_le->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        pwd_le->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(pwd_le);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        login_pb = new QPushButton(TCPClient);
        login_pb->setObjectName("login_pb");
        login_pb->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(login_pb->sizePolicy().hasHeightForWidth());
        login_pb->setSizePolicy(sizePolicy2);
        login_pb->setMinimumSize(QSize(0, 50));
        login_pb->setMaximumSize(QSize(16777215, 50));
        login_pb->setFont(font);

        horizontalLayout_5->addWidget(login_pb);

        regist_pb = new QPushButton(TCPClient);
        regist_pb->setObjectName("regist_pb");
        regist_pb->setEnabled(true);
        sizePolicy2.setHeightForWidth(regist_pb->sizePolicy().hasHeightForWidth());
        regist_pb->setSizePolicy(sizePolicy2);
        regist_pb->setMinimumSize(QSize(0, 50));
        regist_pb->setMaximumSize(QSize(16777215, 50));
        regist_pb->setFont(font);

        horizontalLayout_5->addWidget(regist_pb);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(TCPClient);

        QMetaObject::connectSlotsByName(TCPClient);
    } // setupUi

    void retranslateUi(QWidget *TCPClient)
    {
        TCPClient->setWindowTitle(QCoreApplication::translate("TCPClient", "DXDisk-Login", nullptr));
        statusbar_lab->setText(QCoreApplication::translate("TCPClient", "\350\277\236\346\216\245\347\212\266\346\200\201:", nullptr));
        status_lab->setText(QString());
        ip_lab->setText(QCoreApplication::translate("TCPClient", "IP:", nullptr));
        port_lab->setText(QCoreApplication::translate("TCPClient", "\347\253\257\345\217\243:", nullptr));
        connect_pb->setText(QCoreApplication::translate("TCPClient", "\350\277\236\346\216\245", nullptr));
        name_lab->setText(QCoreApplication::translate("TCPClient", "\347\224\250\346\210\267\345\220\215:", nullptr));
        pwd_lab->setText(QCoreApplication::translate("TCPClient", "\345\257\206   \347\240\201:", nullptr));
        login_pb->setText(QCoreApplication::translate("TCPClient", "\347\231\273\345\275\225", nullptr));
        regist_pb->setText(QCoreApplication::translate("TCPClient", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCPClient: public Ui_TCPClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
