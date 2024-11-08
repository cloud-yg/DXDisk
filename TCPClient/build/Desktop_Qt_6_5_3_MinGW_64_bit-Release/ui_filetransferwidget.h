/********************************************************************************
** Form generated from reading UI file 'filetransferwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILETRANSFERWIDGET_H
#define UI_FILETRANSFERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileTransferWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeWidget *m_pFileTransferTreeW;

    void setupUi(QWidget *FileTransferWidget)
    {
        if (FileTransferWidget->objectName().isEmpty())
            FileTransferWidget->setObjectName("FileTransferWidget");
        FileTransferWidget->resize(713, 492);
        horizontalLayout = new QHBoxLayout(FileTransferWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        m_pFileTransferTreeW = new QTreeWidget(FileTransferWidget);
        m_pFileTransferTreeW->setObjectName("m_pFileTransferTreeW");
        m_pFileTransferTreeW->header()->setMinimumSectionSize(75);
        m_pFileTransferTreeW->header()->setDefaultSectionSize(270);
        m_pFileTransferTreeW->header()->setStretchLastSection(false);

        horizontalLayout->addWidget(m_pFileTransferTreeW);


        retranslateUi(FileTransferWidget);

        QMetaObject::connectSlotsByName(FileTransferWidget);
    } // setupUi

    void retranslateUi(QWidget *FileTransferWidget)
    {
        FileTransferWidget->setWindowTitle(QCoreApplication::translate("FileTransferWidget", "Form", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = m_pFileTransferTreeW->headerItem();
        ___qtreewidgetitem->setText(6, QCoreApplication::translate("FileTransferWidget", "\347\212\266\346\200\201", nullptr));
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("FileTransferWidget", "\351\200\237\345\272\246", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("FileTransferWidget", "\350\277\233\345\272\246", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("FileTransferWidget", "\345\244\247\345\260\217", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("FileTransferWidget", "\345\267\262\345\256\214\346\210\220", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("FileTransferWidget", "\347\261\273\345\236\213", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("FileTransferWidget", "          \346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileTransferWidget: public Ui_FileTransferWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILETRANSFERWIDGET_H
