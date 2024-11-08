/********************************************************************************
** Form generated from reading UI file 'webdiskwiget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBDISKWIGET_H
#define UI_WEBDISKWIGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebDiskWiget
{
public:
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QTreeWidget *m_pFileInfoTreeW;
    QVBoxLayout *verticalLayout;
    QPushButton *m_pReturnPB;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pCreateDirPB;
    QPushButton *m_pDeletePB;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_pRefreshDirPB;
    QPushButton *m_pRenameFilePB;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_pUploadFilePB;
    QPushButton *m_pDownloadFilePB;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_pShareFilePB;
    QPushButton *m_pMoveFilePB;

    void setupUi(QWidget *WebDiskWiget)
    {
        if (WebDiskWiget->objectName().isEmpty())
            WebDiskWiget->setObjectName("WebDiskWiget");
        WebDiskWiget->resize(896, 453);
        horizontalLayout_6 = new QHBoxLayout(WebDiskWiget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        m_pFileInfoTreeW = new QTreeWidget(WebDiskWiget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(2, Qt::AlignLeading|Qt::AlignVCenter);
        m_pFileInfoTreeW->setHeaderItem(__qtreewidgetitem);
        m_pFileInfoTreeW->setObjectName("m_pFileInfoTreeW");
        m_pFileInfoTreeW->setEnabled(true);
        m_pFileInfoTreeW->setColumnCount(3);
        m_pFileInfoTreeW->header()->setMinimumSectionSize(120);
        m_pFileInfoTreeW->header()->setDefaultSectionSize(270);
        m_pFileInfoTreeW->header()->setStretchLastSection(false);

        horizontalLayout_5->addWidget(m_pFileInfoTreeW);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        m_pReturnPB = new QPushButton(WebDiskWiget);
        m_pReturnPB->setObjectName("m_pReturnPB");

        verticalLayout->addWidget(m_pReturnPB);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        m_pCreateDirPB = new QPushButton(WebDiskWiget);
        m_pCreateDirPB->setObjectName("m_pCreateDirPB");

        horizontalLayout->addWidget(m_pCreateDirPB);

        m_pDeletePB = new QPushButton(WebDiskWiget);
        m_pDeletePB->setObjectName("m_pDeletePB");

        horizontalLayout->addWidget(m_pDeletePB);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        m_pRefreshDirPB = new QPushButton(WebDiskWiget);
        m_pRefreshDirPB->setObjectName("m_pRefreshDirPB");

        horizontalLayout_2->addWidget(m_pRefreshDirPB);

        m_pRenameFilePB = new QPushButton(WebDiskWiget);
        m_pRenameFilePB->setObjectName("m_pRenameFilePB");

        horizontalLayout_2->addWidget(m_pRenameFilePB);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        m_pUploadFilePB = new QPushButton(WebDiskWiget);
        m_pUploadFilePB->setObjectName("m_pUploadFilePB");

        horizontalLayout_3->addWidget(m_pUploadFilePB);

        m_pDownloadFilePB = new QPushButton(WebDiskWiget);
        m_pDownloadFilePB->setObjectName("m_pDownloadFilePB");

        horizontalLayout_3->addWidget(m_pDownloadFilePB);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        m_pShareFilePB = new QPushButton(WebDiskWiget);
        m_pShareFilePB->setObjectName("m_pShareFilePB");

        horizontalLayout_4->addWidget(m_pShareFilePB);

        m_pMoveFilePB = new QPushButton(WebDiskWiget);
        m_pMoveFilePB->setObjectName("m_pMoveFilePB");

        horizontalLayout_4->addWidget(m_pMoveFilePB);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        retranslateUi(WebDiskWiget);

        QMetaObject::connectSlotsByName(WebDiskWiget);
    } // setupUi

    void retranslateUi(QWidget *WebDiskWiget)
    {
        WebDiskWiget->setWindowTitle(QCoreApplication::translate("WebDiskWiget", "Form", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = m_pFileInfoTreeW->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("WebDiskWiget", "\345\244\247\345\260\217", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("WebDiskWiget", "\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("WebDiskWiget", "          \345\220\215\347\247\260", nullptr));
        m_pReturnPB->setText(QCoreApplication::translate("WebDiskWiget", "\350\277\224\345\233\236", nullptr));
        m_pCreateDirPB->setText(QCoreApplication::translate("WebDiskWiget", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        m_pDeletePB->setText(QCoreApplication::translate("WebDiskWiget", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        m_pRefreshDirPB->setText(QCoreApplication::translate("WebDiskWiget", "\345\210\267\346\226\260\346\226\207\344\273\266\345\244\271", nullptr));
        m_pRenameFilePB->setText(QCoreApplication::translate("WebDiskWiget", "\351\207\215\345\221\275\345\220\215\346\226\207\344\273\266", nullptr));
        m_pUploadFilePB->setText(QCoreApplication::translate("WebDiskWiget", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        m_pDownloadFilePB->setText(QCoreApplication::translate("WebDiskWiget", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        m_pShareFilePB->setText(QCoreApplication::translate("WebDiskWiget", "\345\210\206\344\272\253\346\226\207\344\273\266", nullptr));
        m_pMoveFilePB->setText(QCoreApplication::translate("WebDiskWiget", "\347\247\273\345\212\250\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WebDiskWiget: public Ui_WebDiskWiget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBDISKWIGET_H
