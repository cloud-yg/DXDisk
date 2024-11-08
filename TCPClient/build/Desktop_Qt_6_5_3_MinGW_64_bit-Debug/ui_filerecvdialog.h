/********************************************************************************
** Form generated from reading UI file 'filerecvdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILERECVDIALOG_H
#define UI_FILERECVDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileRecvDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeWidget *fileInfoTW;
    QHBoxLayout *horizontalLayout;
    QPushButton *agreePB;
    QSpacerItem *horizontalSpacer;
    QPushButton *refusePB;

    void setupUi(QWidget *FileRecvDialog)
    {
        if (FileRecvDialog->objectName().isEmpty())
            FileRecvDialog->setObjectName("FileRecvDialog");
        FileRecvDialog->resize(449, 257);
        verticalLayout_2 = new QVBoxLayout(FileRecvDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        fileInfoTW = new QTreeWidget(FileRecvDialog);
        fileInfoTW->setObjectName("fileInfoTW");
        fileInfoTW->header()->setVisible(true);
        fileInfoTW->header()->setMinimumSectionSize(80);
        fileInfoTW->header()->setDefaultSectionSize(180);
        fileInfoTW->header()->setStretchLastSection(false);

        verticalLayout->addWidget(fileInfoTW);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        agreePB = new QPushButton(FileRecvDialog);
        agreePB->setObjectName("agreePB");

        horizontalLayout->addWidget(agreePB);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refusePB = new QPushButton(FileRecvDialog);
        refusePB->setObjectName("refusePB");

        horizontalLayout->addWidget(refusePB);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FileRecvDialog);

        QMetaObject::connectSlotsByName(FileRecvDialog);
    } // setupUi

    void retranslateUi(QWidget *FileRecvDialog)
    {
        FileRecvDialog->setWindowTitle(QCoreApplication::translate("FileRecvDialog", "\346\226\207\344\273\266\346\216\245\346\224\266", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = fileInfoTW->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("FileRecvDialog", "\345\210\206\344\272\253\350\200\205", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("FileRecvDialog", "\345\244\247\345\260\217", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("FileRecvDialog", "\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("FileRecvDialog", "          \345\220\215\345\255\227", nullptr));
        agreePB->setText(QCoreApplication::translate("FileRecvDialog", "\346\216\245\346\224\266", nullptr));
        refusePB->setText(QCoreApplication::translate("FileRecvDialog", "\346\213\222\347\273\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileRecvDialog: public Ui_FileRecvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILERECVDIALOG_H
