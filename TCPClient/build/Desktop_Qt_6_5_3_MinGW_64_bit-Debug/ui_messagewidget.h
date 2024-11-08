/********************************************************************************
** Form generated from reading UI file 'messagewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEWIDGET_H
#define UI_MESSAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *msg_title_te;
    QTextEdit *m_pShowMsgTE;

    void setupUi(QWidget *MessageWidget)
    {
        if (MessageWidget->objectName().isEmpty())
            MessageWidget->setObjectName("MessageWidget");
        MessageWidget->resize(439, 359);
        verticalLayout_2 = new QVBoxLayout(MessageWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        msg_title_te = new QTextEdit(MessageWidget);
        msg_title_te->setObjectName("msg_title_te");
        msg_title_te->setMaximumSize(QSize(16777215, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        msg_title_te->setFont(font);
        msg_title_te->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        msg_title_te->setReadOnly(true);

        verticalLayout->addWidget(msg_title_te);

        m_pShowMsgTE = new QTextEdit(MessageWidget);
        m_pShowMsgTE->setObjectName("m_pShowMsgTE");
        QFont font1;
        font1.setPointSize(16);
        m_pShowMsgTE->setFont(font1);
        m_pShowMsgTE->setReadOnly(true);

        verticalLayout->addWidget(m_pShowMsgTE);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MessageWidget);

        QMetaObject::connectSlotsByName(MessageWidget);
    } // setupUi

    void retranslateUi(QWidget *MessageWidget)
    {
        MessageWidget->setWindowTitle(QCoreApplication::translate("MessageWidget", "Form", nullptr));
        msg_title_te->setHtml(QCoreApplication::translate("MessageWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:18pt; font-weight:700; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageWidget: public Ui_MessageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEWIDGET_H
