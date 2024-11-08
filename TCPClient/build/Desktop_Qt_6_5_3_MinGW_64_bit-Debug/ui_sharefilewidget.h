/********************************************************************************
** Form generated from reading UI file 'sharefilewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREFILEWIDGET_H
#define UI_SHAREFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShareFileWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QWidget *m_pOnlineFriendW;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_5;

    void setupUi(QWidget *ShareFileWidget)
    {
        if (ShareFileWidget->objectName().isEmpty())
            ShareFileWidget->setObjectName("ShareFileWidget");
        ShareFileWidget->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(ShareFileWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(ShareFileWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(ShareFileWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(ShareFileWidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout);

        m_pOnlineFriendW = new QWidget(ShareFileWidget);
        m_pOnlineFriendW->setObjectName("m_pOnlineFriendW");
        verticalLayout_3 = new QVBoxLayout(m_pOnlineFriendW);
        verticalLayout_3->setObjectName("verticalLayout_3");
        scrollArea = new QScrollArea(m_pOnlineFriendW);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 352, 178));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        verticalLayout->addWidget(m_pOnlineFriendW);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_4 = new QPushButton(ShareFileWidget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout_2->addWidget(pushButton_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_5 = new QPushButton(ShareFileWidget);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout_2->addWidget(pushButton_5);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ShareFileWidget);

        QMetaObject::connectSlotsByName(ShareFileWidget);
    } // setupUi

    void retranslateUi(QWidget *ShareFileWidget)
    {
        ShareFileWidget->setWindowTitle(QCoreApplication::translate("ShareFileWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ShareFileWidget", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ShareFileWidget", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ShareFileWidget", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("ShareFileWidget", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("ShareFileWidget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShareFileWidget: public Ui_ShareFileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREFILEWIDGET_H
