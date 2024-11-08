/********************************************************************************
** Form generated from reading UI file 'filesavedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESAVEDIALOG_H
#define UI_FILESAVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSaveDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *returnPB;
    QPushButton *createDirPB;
    QPushButton *savePB;
    QPushButton *cancelPB;
    QTreeWidget *FileInfoTreeW;

    void setupUi(QWidget *FileSaveDialog)
    {
        if (FileSaveDialog->objectName().isEmpty())
            FileSaveDialog->setObjectName("FileSaveDialog");
        FileSaveDialog->resize(424, 273);
        verticalLayout_2 = new QVBoxLayout(FileSaveDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        returnPB = new QPushButton(FileSaveDialog);
        returnPB->setObjectName("returnPB");

        horizontalLayout->addWidget(returnPB);

        createDirPB = new QPushButton(FileSaveDialog);
        createDirPB->setObjectName("createDirPB");

        horizontalLayout->addWidget(createDirPB);

        savePB = new QPushButton(FileSaveDialog);
        savePB->setObjectName("savePB");

        horizontalLayout->addWidget(savePB);

        cancelPB = new QPushButton(FileSaveDialog);
        cancelPB->setObjectName("cancelPB");

        horizontalLayout->addWidget(cancelPB);


        verticalLayout->addLayout(horizontalLayout);

        FileInfoTreeW = new QTreeWidget(FileSaveDialog);
        FileInfoTreeW->setObjectName("FileInfoTreeW");
        FileInfoTreeW->header()->setMinimumSectionSize(80);
        FileInfoTreeW->header()->setDefaultSectionSize(240);
        FileInfoTreeW->header()->setStretchLastSection(false);

        verticalLayout->addWidget(FileInfoTreeW);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FileSaveDialog);

        QMetaObject::connectSlotsByName(FileSaveDialog);
    } // setupUi

    void retranslateUi(QWidget *FileSaveDialog)
    {
        FileSaveDialog->setWindowTitle(QCoreApplication::translate("FileSaveDialog", "\350\257\267\351\200\211\346\213\251\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        returnPB->setText(QCoreApplication::translate("FileSaveDialog", "\350\277\224\345\233\236", nullptr));
        createDirPB->setText(QCoreApplication::translate("FileSaveDialog", "\346\226\260\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        savePB->setText(QCoreApplication::translate("FileSaveDialog", "\344\277\235\345\255\230", nullptr));
        cancelPB->setText(QCoreApplication::translate("FileSaveDialog", "\345\217\226\346\266\210", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = FileInfoTreeW->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("FileSaveDialog", "\345\244\247\345\260\217", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("FileSaveDialog", "\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("FileSaveDialog", "          \346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileSaveDialog: public Ui_FileSaveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESAVEDIALOG_H
