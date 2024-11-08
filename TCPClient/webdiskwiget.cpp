#include "webdiskwiget.h"
#include "ui_webdiskwiget.h"
#include "tcpclient.h"
#include "UniversalFunction.h"
#include "filesavedialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

WebDiskWiget::WebDiskWiget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WebDiskWiget)
{
    ui->setupUi(this);
    ui->m_pFileInfoTreeW->setColumnWidth(0,360);
    ui->m_pFileInfoTreeW->setColumnWidth(1,120);
    ui->m_pFileInfoTreeW->setColumnWidth(2,120);

    // 设置第一列宽度可拉伸
    ui->m_pFileInfoTreeW->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    // 设置第二、三列宽度固定
    ui->m_pFileInfoTreeW->header()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->m_pFileInfoTreeW->header()->setSectionResizeMode(2, QHeaderView::Fixed);
}

WebDiskWiget::~WebDiskWiget()
{
    delete ui;
}

void WebDiskWiget::refreshFileList(std::shared_ptr<PDU> pdu)
{
    if(pdu == nullptr) return;
    ui->m_pFileInfoTreeW->clear();
    m_mapFileInfo.clear();
    FileInfo *pFileInfo = nullptr;
    int iCount = pdu->uiMsgLen/sizeof(FileInfo);
    if(iCount == 0)
    {
        QTreeWidgetItem *pFileInfoItem = new QTreeWidgetItem(ui->m_pFileInfoTreeW);
        pFileInfoItem->setText(0,"此文件夹为空");
        ui->m_pFileInfoTreeW->setEnabled(false);
    }
    else
    {
        ui->m_pFileInfoTreeW->setEnabled(true);
        for(int i = 0; i < iCount; ++i)
        {
            pFileInfo = (FileInfo*)pdu->caMsg + i;
            QTreeWidgetItem *pFileInfoItem = new QTreeWidgetItem(ui->m_pFileInfoTreeW);
            //显示文件名字,icon,文件类型
            pFileInfoItem->setText(0,pFileInfo->caFileNameUtf8);
            setFileTypeIcon(pFileInfoItem,pFileInfo->iFileType,0,1);
            //显示文件大小
            pFileInfoItem->setText(2,byteConversion(pFileInfo->llFileSize));

            QPair<int,qint64> fileInfoPair;
            fileInfoPair.first = pFileInfo->iFileType;
            fileInfoPair.second = pFileInfo->llFileSize;
            m_mapFileInfo.insert(pFileInfo->caFileNameUtf8,fileInfoPair);
        }
    }
}

void WebDiskWiget::refresh()
{
    on_m_pRefreshDirPB_clicked();
}

QString WebDiskWiget::getUploadFilePath()
{
    return m_strUploadFilePath;
}

QString WebDiskWiget::getSaveFilePath()
{
    return m_strSaveFilePath;
}

QString WebDiskWiget::getShareFileName()
{
    return m_strShareFileName;
}

QString WebDiskWiget::getMoveFilePath()
{
    return m_strMoveFilePath;
}


void WebDiskWiget::on_m_pCreateDirPB_clicked()
{
    bool isOk;
    QString strNewDir = QInputDialog::getText(this,"新建文件夹","输入名字(不超过63个字符,中文占3个字符):",
                                              QLineEdit::Normal,"",&isOk);

    if(!strNewDir.isEmpty())
    {
        if(strNewDir.toUtf8().size()>63)QMessageBox::warning(this,"新建文件夹","输入名字超过63个字符!");
        else
        {
            QString strCurPath = TCPClient::getInstance().getCurPath();

            std::shared_ptr<PDU> pdu = mk_shared_PDU(strCurPath.toUtf8().size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_REQUEST;
            strncpy(pdu->caData,strNewDir.toUtf8().toStdString().c_str(),strNewDir.toUtf8().size());
            memcpy(pdu->caMsg,strCurPath.toUtf8().toStdString().c_str(),strCurPath.toUtf8().size());
            TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
        }
    }
    else if(isOk) QMessageBox::warning(this,"新建文件夹","输入名字不能为空!");
}

void WebDiskWiget::on_m_pRefreshDirPB_clicked()
{
    QString strCurPath = TCPClient::getInstance().getCurPath();
    std::shared_ptr<PDU> pdu = mk_shared_PDU(strCurPath.toUtf8().size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_REFRESH_DIR_REQUEST;
    memcpy((char*)pdu->caMsg,strCurPath.toUtf8(),strCurPath.toUtf8().size());
    TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
}

void WebDiskWiget::on_m_pDeletePB_clicked()
{
    QTreeWidgetItem *pItem = ui->m_pFileInfoTreeW->currentItem();
    if(pItem != nullptr)
    {
        QString delName = pItem->text(0);
        QString strCurPath = TCPClient::getInstance().getCurPath();
        auto ret = QMessageBox::information(this,"删除文件",QString
                   ("Are you sure you want to delete [%1] ?").arg(delName),
                                            QMessageBox::Yes,QMessageBox::No);
        if(ret == QMessageBox::Yes)
        {
            std::shared_ptr<PDU> pdu = mk_shared_PDU(strCurPath.toUtf8().size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_DIRORFILE_REQUEST;
            strncpy(pdu->caData,delName.toUtf8(),delName.toUtf8().size());
            strncpy(pdu->caMsg,strCurPath.toUtf8(),strCurPath.toUtf8().size());
            TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
        }
    }
}


void WebDiskWiget::on_m_pRenameFilePB_clicked()
{
    QTreeWidgetItem *pItem = ui->m_pFileInfoTreeW->currentItem();
    if(pItem != nullptr)
    {
        QString oldName = pItem->text(0);
        QString strCurPath = TCPClient::getInstance().getCurPath();

        bool isOk;
        QString newName = QInputDialog::getText(this,"重命名","输入新名字(不超过63个字符,中文占3个字符):",
                                                  QLineEdit::Normal,oldName,&isOk);

        if(!newName.isEmpty() && newName != oldName)
        {
            std::shared_ptr<PDU> pdu = mk_shared_PDU(oldName.toUtf8().size()+ 1 + strCurPath.toUtf8().size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_RENAME_DIRORFILE_REQUEST;
            strncpy(pdu->caData,newName.toUtf8(),newName.toUtf8().size());
            strncpy(pdu->caMsg,oldName.toUtf8(),oldName.toUtf8().size());
            strncpy(pdu->caMsg+oldName.toUtf8().size()+1,strCurPath.toUtf8(),strCurPath.toUtf8().size());
            qDebug() << pdu->caMsg;
            QString str = pdu->caMsg;
            qDebug() << str << str.size() << str.toUtf8().size() << oldName.toUtf8().size();
            TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
        }
        else if(newName.isEmpty() && isOk) QMessageBox::warning(this,"重命名","输入的新名字不能为空!");
    }
}

//双击文件列表,进入文件夹
void WebDiskWiget::on_m_pFileInfoTreeW_doubleClicked(const QModelIndex &index)
{
    QString dirName = index.data().toString();
    QString curPath = TCPClient::getInstance().getCurPath();
    TCPClient::getInstance().setCurPathTemp(curPath + "/" + dirName);

    std::shared_ptr<PDU> pdu = mk_shared_PDU(curPath.toUtf8().size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_ENTER_DIR_REQUEST;
    strncpy(pdu->caData,dirName.toUtf8(),dirName.toUtf8().size());
    memcpy(pdu->caMsg,curPath.toUtf8(),curPath.toUtf8().size());
    TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
}

void WebDiskWiget::on_m_pReturnPB_clicked()
{
    QString curPath = TCPClient::getInstance().getCurPath();
    QString rootPath = TCPClient::getInstance().getRootPath();
    if(curPath == rootPath)
        QMessageBox::warning(this,"返回","返回失败:根目录下无法再返回!");
    else
    {
        int index = curPath.lastIndexOf('/');
        curPath.remove(index,curPath.size()-index);
        TCPClient::getInstance().setCurPath(curPath);
        on_m_pRefreshDirPB_clicked();
    }
}

void WebDiskWiget::on_m_pUploadFilePB_clicked()
{
    m_strUploadFilePath = QFileDialog::getOpenFileName();  //弹出打开文件窗口,返回选择文件的绝对路径
    if(!m_strUploadFilePath.isEmpty())
    {
        int index = m_strUploadFilePath.lastIndexOf('/');
        //截取文件名,获取uploadFilePath右端文件名
        QString uploadFileName = m_strUploadFilePath.right(m_strUploadFilePath.size()-index-1);

        if(uploadFileName.toUtf8().size() <= 63)
        {
            QFileInfo fileInfo(m_strUploadFilePath);
            QString fileSize = QString("%1").arg(fileInfo.size());
            QString curPath = TCPClient::getInstance().getCurPath();  //获取当前路径
            std::shared_ptr<PDU> pdu = mk_shared_PDU(sizeof(fileSize) + 1 + curPath.toUtf8().size() + 1);
            pdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST;
            strcpy(pdu->caData,uploadFileName.toUtf8());
            memcpy(pdu->caMsg,fileSize.toStdString().c_str(),fileSize.size());
            memcpy(pdu->caMsg+fileSize.size()+1,curPath.toUtf8(),curPath.toUtf8().size());

            TCPClient::getInstance().getFileRecv().totalSize= fileInfo.size();
            TCPClient::getInstance().getFileRecv().recvedSize = 0;

            OpeWidget::getInstance().getFileTransferW()->
                createFTWItem(uploadFileName,determineFileType(fileInfo.suffix()),fileInfo.size(),"开始上传");
            //开始计时,计算传输速度
            TCPClient::getInstance().startElapsedTimer();
            TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
        }
        else QMessageBox::warning(this,"上传文件失败","文件名字过长,请重命名(最多63字符)后再上传");
    }
    else QMessageBox::warning(this,"上传文件失败","未选择文件");
}

void WebDiskWiget::on_m_pDownloadFilePB_clicked()
{
    QTreeWidgetItem *pItem = ui->m_pFileInfoTreeW->currentItem();
    if(pItem != nullptr)
    {
        QString downloadFileName = pItem->text(0);
        //设置文件下载的路径
        m_strSaveFilePath = QFileDialog::getSaveFileName(nullptr,"下载文件","C:/DXDisk/Download/"+downloadFileName);
        if(m_strSaveFilePath.isEmpty())
        {
            QMessageBox::information(this,"下载文件失败","未选择下载路径");
        }
        else
        {
            QString curPath = TCPClient::getInstance().getCurPath();
            std::shared_ptr<PDU> pdu = mk_shared_PDU(curPath.toUtf8().size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST;
            strcpy(pdu->caData,downloadFileName.toUtf8());
            memcpy(pdu->caMsg,curPath.toUtf8(),curPath.toUtf8().size());

            TCPClient::getInstance().getFileRecv().file.setFileName(m_strSaveFilePath);
            if(TCPClient::getInstance().getFileRecv().file.open(QIODevice::WriteOnly))
            {
                auto iter = m_mapFileInfo.constFind(downloadFileName);
                if(iter != m_mapFileInfo.cend())
                {
                    if(iter->first == 0)
                        QMessageBox::information(this,"下载文件失败","无法下载文件夹");
                    else
                    {
                        TCPClient::getInstance().getFileRecv().totalSize= iter.value().second;
                        TCPClient::getInstance().getFileRecv().recvedSize = 0;
                        TCPClient::getInstance().getFileRecv().recvingFlag = true;

                        OpeWidget::getInstance().getFileTransferW()->
                            createFTWItem(downloadFileName,iter->first,iter->second,"开始下载");
                        //开始计时,计算传输速度
                        TCPClient::getInstance().startElapsedTimer();
                        TCPClient::getInstance().getTCPSocket().write((char*)pdu.get(),pdu->uiPDULen);
                    }
                }
                else QMessageBox::information(this,"下载文件失败","获取下载文件信息失败");
            }
            else QMessageBox::information(this,"下载文件失败","获取文件下载路径失败");
        }
    }
}


void WebDiskWiget::on_m_pShareFilePB_clicked()
{
    QTreeWidgetItem *pItem = ui->m_pFileInfoTreeW->currentItem();
    if(pItem != nullptr)
    {
        m_strShareFileName = pItem->text(0);     //获取分享文件名
        if(ShareFileWidget::getInstance().isHidden())
            ShareFileWidget::getInstance().show();
    }
}


void WebDiskWiget::on_m_pMoveFilePB_clicked()
{
    QTreeWidgetItem *pItem = ui->m_pFileInfoTreeW->currentItem();
    if(pItem != nullptr)
    {
        QString moveFileName = pItem->text(0);     //获取移动文件名
        m_strMoveFilePath = TCPClient::getInstance().getCurPath() + "/" + moveFileName;
        FileSaveDialog::getInstance().refreshDialog();
        FileSaveDialog::getInstance().show();
        FileSaveDialog::getInstance().setSaveFlag(false);
    }
}

