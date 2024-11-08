/********************************************************************************
** Form generated from reading UI file 'onlineusr.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINEUSR_H
#define UI_ONLINEUSR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnlineUsr
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *online_usr_lw;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *addFriend_pb;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *OnlineUsr)
    {
        if (OnlineUsr->objectName().isEmpty())
            OnlineUsr->setObjectName("OnlineUsr");
        OnlineUsr->resize(668, 438);
        horizontalLayout_2 = new QHBoxLayout(OnlineUsr);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        online_usr_lw = new QListWidget(OnlineUsr);
        new QListWidgetItem(online_usr_lw);
        new QListWidgetItem(online_usr_lw);
        new QListWidgetItem(online_usr_lw);
        new QListWidgetItem(online_usr_lw);
        online_usr_lw->setObjectName("online_usr_lw");
        QFont font;
        font.setPointSize(16);
        online_usr_lw->setFont(font);

        horizontalLayout->addWidget(online_usr_lw);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        addFriend_pb = new QPushButton(OnlineUsr);
        addFriend_pb->setObjectName("addFriend_pb");
        addFriend_pb->setFont(font);

        verticalLayout->addWidget(addFriend_pb);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(OnlineUsr);

        QMetaObject::connectSlotsByName(OnlineUsr);
    } // setupUi

    void retranslateUi(QWidget *OnlineUsr)
    {
        OnlineUsr->setWindowTitle(QCoreApplication::translate("OnlineUsr", "\345\234\250\347\272\277\347\224\250\346\210\267\345\210\227\350\241\250", nullptr));

        const bool __sortingEnabled = online_usr_lw->isSortingEnabled();
        online_usr_lw->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = online_usr_lw->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("OnlineUsr", "\345\215\226\345\245\263\345\255\251\347\232\204\345\260\217\347\201\253\346\237\264", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = online_usr_lw->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("OnlineUsr", "\351\207\207\345\247\221\345\250\230\347\232\204\345\260\217\350\230\221\350\217\207", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = online_usr_lw->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("OnlineUsr", "\346\250\252\345\210\200\345\220\221\345\244\251\347\254\221", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = online_usr_lw->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("OnlineUsr", "\344\270\226\345\244\226\351\253\230\344\272\272", nullptr));
        online_usr_lw->setSortingEnabled(__sortingEnabled);

        addFriend_pb->setText(QCoreApplication::translate("OnlineUsr", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OnlineUsr: public Ui_OnlineUsr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINEUSR_H
