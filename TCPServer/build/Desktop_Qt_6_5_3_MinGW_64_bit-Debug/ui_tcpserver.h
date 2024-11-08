/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPServer
{
public:

    void setupUi(QWidget *TCPServer)
    {
        if (TCPServer->objectName().isEmpty())
            TCPServer->setObjectName("TCPServer");
        TCPServer->resize(800, 600);

        retranslateUi(TCPServer);

        QMetaObject::connectSlotsByName(TCPServer);
    } // setupUi

    void retranslateUi(QWidget *TCPServer)
    {
        TCPServer->setWindowTitle(QCoreApplication::translate("TCPServer", "TCPServer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCPServer: public Ui_TCPServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
