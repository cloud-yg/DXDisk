/********************************************************************************
** Form generated from reading UI file 'bookwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKWIDGET_H
#define UI_BOOKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *m_pBookLW;
    QVBoxLayout *verticalLayout;
    QPushButton *m_pReturnPB;
    QPushButton *m_pCreateDirPB;
    QPushButton *m_pDeleteDirPB;
    QPushButton *m_pRenameDirPB;
    QPushButton *m_pRefreshDirPB;
    QVBoxLayout *verticalLayout_2;
    QPushButton *m_pUploadFilePB;
    QPushButton *m_pDeleteFilePB;
    QPushButton *m_pDownloadFilePB;
    QPushButton *m_pShareFilePB;

    void setupUi(QWidget *BookWidget)
    {
        if (BookWidget->objectName().isEmpty())
            BookWidget->setObjectName("BookWidget");
        BookWidget->resize(339, 346);
        horizontalLayout_2 = new QHBoxLayout(BookWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        m_pBookLW = new QListWidget(BookWidget);
        m_pBookLW->setObjectName("m_pBookLW");
        QFont font;
        font.setPointSize(9);
        m_pBookLW->setFont(font);

        horizontalLayout->addWidget(m_pBookLW);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        m_pReturnPB = new QPushButton(BookWidget);
        m_pReturnPB->setObjectName("m_pReturnPB");
        m_pReturnPB->setFont(font);

        verticalLayout->addWidget(m_pReturnPB);

        m_pCreateDirPB = new QPushButton(BookWidget);
        m_pCreateDirPB->setObjectName("m_pCreateDirPB");
        m_pCreateDirPB->setFont(font);

        verticalLayout->addWidget(m_pCreateDirPB);

        m_pDeleteDirPB = new QPushButton(BookWidget);
        m_pDeleteDirPB->setObjectName("m_pDeleteDirPB");
        m_pDeleteDirPB->setFont(font);

        verticalLayout->addWidget(m_pDeleteDirPB);

        m_pRenameDirPB = new QPushButton(BookWidget);
        m_pRenameDirPB->setObjectName("m_pRenameDirPB");
        m_pRenameDirPB->setFont(font);

        verticalLayout->addWidget(m_pRenameDirPB);

        m_pRefreshDirPB = new QPushButton(BookWidget);
        m_pRefreshDirPB->setObjectName("m_pRefreshDirPB");
        m_pRefreshDirPB->setFont(font);

        verticalLayout->addWidget(m_pRefreshDirPB);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        m_pUploadFilePB = new QPushButton(BookWidget);
        m_pUploadFilePB->setObjectName("m_pUploadFilePB");
        m_pUploadFilePB->setFont(font);

        verticalLayout_2->addWidget(m_pUploadFilePB);

        m_pDeleteFilePB = new QPushButton(BookWidget);
        m_pDeleteFilePB->setObjectName("m_pDeleteFilePB");
        m_pDeleteFilePB->setFont(font);

        verticalLayout_2->addWidget(m_pDeleteFilePB);

        m_pDownloadFilePB = new QPushButton(BookWidget);
        m_pDownloadFilePB->setObjectName("m_pDownloadFilePB");
        m_pDownloadFilePB->setFont(font);

        verticalLayout_2->addWidget(m_pDownloadFilePB);

        m_pShareFilePB = new QPushButton(BookWidget);
        m_pShareFilePB->setObjectName("m_pShareFilePB");
        m_pShareFilePB->setFont(font);

        verticalLayout_2->addWidget(m_pShareFilePB);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(BookWidget);

        QMetaObject::connectSlotsByName(BookWidget);
    } // setupUi

    void retranslateUi(QWidget *BookWidget)
    {
        BookWidget->setWindowTitle(QCoreApplication::translate("BookWidget", "Form", nullptr));
        m_pReturnPB->setText(QCoreApplication::translate("BookWidget", "\350\277\224\345\233\236", nullptr));
        m_pCreateDirPB->setText(QCoreApplication::translate("BookWidget", "\345\210\233\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        m_pDeleteDirPB->setText(QCoreApplication::translate("BookWidget", "\345\210\240\351\231\244\346\226\207\344\273\266\345\244\271", nullptr));
        m_pRenameDirPB->setText(QCoreApplication::translate("BookWidget", "\351\207\215\345\221\275\345\220\215\346\226\207\344\273\266\345\244\271", nullptr));
        m_pRefreshDirPB->setText(QCoreApplication::translate("BookWidget", "\345\210\267\346\226\260\346\226\207\344\273\266\345\244\271", nullptr));
        m_pUploadFilePB->setText(QCoreApplication::translate("BookWidget", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        m_pDeleteFilePB->setText(QCoreApplication::translate("BookWidget", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        m_pDownloadFilePB->setText(QCoreApplication::translate("BookWidget", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        m_pShareFilePB->setText(QCoreApplication::translate("BookWidget", "\345\210\206\344\272\253\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookWidget: public Ui_BookWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKWIDGET_H
