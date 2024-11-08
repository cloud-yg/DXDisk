#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "searchdialog.h"
#include "friendwidget.h"
#include "UniversalFunction.h"
#include "filerecvdialog.h"
#include "filesavedialog.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

TCPClient::TCPClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCPClient)
{
    ui->setupUi(this);

    m_elapsedTimer = new QElapsedTimer;

    if(!isConnected)
    {
        ui->status_lab->setText("未连接");
        // 创建一个 QPalette 对象
        QPalette palette = ui->status_lab->palette();
        // 设置字体颜色
        palette.setColor(QPalette::WindowText, QColor(Qt::red));  // 将字体颜色设置为红色
        // 将 QPalette 应用到 QLabel
        ui->status_lab->setPalette(palette);
    }

    connect(&m_tcpSocket,SIGNAL(connected()),this,SLOT(showConnect()));
    connect(&m_tcpSocket,SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &TCPClient::onError);
    connect(&m_tcpSocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));
}

TCPClient::~TCPClient()
{
    delete ui;
}


TCPClient &TCPClient::getInstance()
{
    static TCPClient instance;
    return instance;
}

QTcpSocket &TCPClient::getTCPSocket()
{
    return m_tcpSocket;
}

QString TCPClient::getLoginName()
{
    return m_loginName;
}

QString TCPClient::getCurPath()
{
    return m_curPath;
}

void TCPClient::setCurPath(QString curPath)
{
    m_curPath = curPath;
}

QString TCPClient::getRootPath()
{
    return m_rootPath;
}

void TCPClient::setCurPathTemp(QString curPathTemp)
{
    m_curPathTemp = curPathTemp;
}

void TCPClient::showConnect()
{
    ui->status_lab->setText("已连接");
    OpeWidget::getInstance().getStatus()->setText("已连接");
    // 创建一个 QPalette 对象
    QPalette palette = ui->status_lab->palette();
    // 设置字体颜色
    palette.setColor(QPalette::WindowText, QColor(Qt::green));  // 将字体颜色设置为绿色
    // 将 QPalette 应用到 QLabel
    ui->status_lab->setPalette(palette);
    OpeWidget::getInstance().getStatus()->setPalette(palette);
    isConnected = true;
    QMessageBox::information(this,"连接服务器","连接服务器成功");
}

void TCPClient::onDisconnected()
{
    isConnected = false;
    QMessageBox::information(this,"连接服务器","断开服务器连接");
}

void TCPClient::onError(QAbstractSocket::SocketError error)
{
    ui->status_lab->setText("未连接");
    OpeWidget::getInstance().getStatus()->setText("未连接");
    // 创建一个 QPalette 对象
    QPalette palette = ui->status_lab->palette();
    // 设置字体颜色
    palette.setColor(QPalette::WindowText, QColor(Qt::red));  // 将字体颜色设置为红色
    // 将 QPalette 应用到 QLabel
    ui->status_lab->setPalette(palette);
    OpeWidget::getInstance().getStatus()->setPalette(palette);
    qDebug() << "Connection error occurred:" << m_tcpSocket.errorString();
    //服务器地址或端口号错误
    if (error != QAbstractSocket::HostNotFoundError && !isConnected)
        QMessageBox::warning(this,"连接服务器失败","请检查IP和端口是否正确后重试");
}

void TCPClient::handleRpdPDU(std::shared_ptr<PDU> pdu)
{
    switch(pdu->uiMsgType)
    {
        case ENUM_MSG_TYPE_REGIST_RESPOND:  //注册回复
        {
            if(strcmp(pdu->caData,REGIST_OK) == 0)
                QMessageBox::information(this,"注册",REGIST_OK);
            else if(strcmp(pdu->caData,REGIST_FAILED) == 0)
                QMessageBox::warning(this,"注册",REGIST_FAILED);
            break;
        }
        case ENUM_MSG_TYPE_LOGIN_RESPOND:   //登录回复
        {
            if(strcmp(pdu->caData,LOGIN_OK) == 0)
            {
                m_curPath = QString("./UserWebDisk/%1").arg(m_loginName);   //设置刚登陆时的路径
                m_rootPath = "./UserWebDisk/" + m_loginName;
                QMessageBox::information(this,"登录",LOGIN_OK);
                OpeWidget::getInstance().show();    //登陆成功后跳转到二级界面
                OpeWidget::getInstance().getFriendW()->on_refFriend_pb_clicked();
                OpeWidget::getInstance().getWebDiskW()->refresh();
                FileSaveDialog::getInstance().setCurPath(m_rootPath);
                hide();     //隐藏登录界面
            }
            else if(strcmp(pdu->caData,LOGIN_FAILED_NOEXIST) == 0)
                QMessageBox::warning(this,"登录",LOGIN_FAILED_NOEXIST);
            else if(strcmp(pdu->caData,LOGIN_FAILED_PWDERROR) == 0)
                QMessageBox::warning(this,"登录",LOGIN_FAILED_PWDERROR);
            else QMessageBox::warning(this,"登录",LOGIN_FAILED_RELOGIN);
            break;
        }
        case ENUM_MSG_TYPE_ALL_ONLINEUSR_RESPOND:   //在线用户回复
        {
            OpeWidget::getInstance().getFriendW()->showAllOnlineUsr(pdu);
            break;
        }
        case ENUM_MSG_TYPE_SEARCH_USR_RESPOND:      //搜索结果回复
        {
            SearchDialog::getInstance().updateSearchDialog(pdu);
            SearchDialog::getInstance().show();
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:      //处理添加好友请求，同意或者拒绝
        {
            auto ret = QMessageBox::information(this,"添加好友",QString
            ("Do you want to agree [%1] to add you as a friend ?").arg(pdu->caData+32),
                                     QMessageBox::Yes,QMessageBox::No);
            //创建回复PDU
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
            rpdPDU->uiMsgType = (ret == QMessageBox::Yes ?
                                 ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND :
                                 ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_RESPOND);
            //pdu->caData+32即原来请求（添加好友)者,作为被回复者rpdPDU->caData
            memcpy(rpdPDU->caData,pdu->caData+32,32);
            //pdu->caData即原来被请求（添加好友)者,作为回复者rpdPDU->caData+32
            memcpy(rpdPDU->caData+32,pdu->caData,32);
            m_tcpSocket.write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_RESPOND:      //添加好友失败回复
        {
            QMessageBox::information(this,"添加好友",pdu->caData);
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND:    //好友请求通过
        {
            OpeWidget::getInstance().getFriendW()->refreshFriend(pdu);  //刷新好友列表
            QMessageBox::information(this,"好友请求回复",QString
                            ("[%1] agreed your friend request").arg(pdu->caData+32));
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND_RESPOND:    //好友请求通过回复
        {
            OpeWidget::getInstance().getFriendW()->refreshFriend(pdu);  //刷新好友列表
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_RESPOND:   //被拒绝添加好友回复
        {
            QMessageBox::information(this,"好友请求回复",QString
                            ("[%1] refused your friend request").arg(pdu->caData+32));
            break;
        }
        case ENUM_MSG_TYPE_REFRESH_FRIEND_RESPOND:  //刷新好友列表回复
        {
            OpeWidget::getInstance().getFriendW()->refreshFriend(pdu);
            break;
        }
        case ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND:   //删除好友回复
        {
            char delFriName[32];
            strcpy(delFriName,pdu->caData+32);
            OpeWidget::getInstance().getFriendW()->delCurFriInfo(delFriName);
            OpeWidget::getInstance().getFriendW()->refreshFriend(pdu);
            QMessageBox::information(this,"删除好友",pdu->caData);
            break;
        }
        case ENUM_MSG_TYPE_SENDMSG_REQUEST:     //发送消息请求
        {
            OpeWidget::getInstance().getFriendW()->updateRecvMsg(pdu);
            break;
        }
        case ENUM_MSG_TYPE_SENDMSG_RESPOND:     //发送消息回复
        {
            if(strcmp(pdu->caData,SEND_MESSAGE_OK) == 0)
            {
                OpeWidget::getInstance().getFriendW()->updateSendMsg();
            }
            else
                QMessageBox::information(this,"发送消息",pdu->caData);
            break;
        }
        case ENUM_MSG_TYPE_SENDPUBLICMSG_REQUEST:   //发送群聊消息请求
        {
            OpeWidget::getInstance().getFriendW()->updateRecvMsg(pdu);
            break;
        }
        case ENUM_MSG_TYPE_CREATE_DIR_RESPOND:      //新建文件夹回复
        {
            QMessageBox::information(this,"新建文件夹",pdu->caData);
            if(strcmp(pdu->caData, CREATE_DIR_OK) == 0)
                OpeWidget::getInstance().getWebDiskW()->refreshFileList(pdu);
            break;
        }
        case ENUM_MSG_TYPE_REFRESH_DIR_RESPOND:     //刷新文件夹回复
        {
            OpeWidget::getInstance().getWebDiskW()->refreshFileList(pdu);
            break;
        }
        case ENUM_MSG_TYPE_DELETE_DIRORFILE_RESPOND:    //删除文件回复
        {
            QMessageBox::information(this,"删除",pdu->caData);
            if(strcmp(pdu->caData, DELETE_DIRORFILE_OK) == 0)
                OpeWidget::getInstance().getWebDiskW()->refreshFileList(pdu);
            break;
        }
        case ENUM_MSG_TYPE_RENAME_DIRORFILE_RESPOND:    //重命名文件回复
        {
            if(strcmp(pdu->caData, RENAME_DIRORFILE_OK) == 0)
                OpeWidget::getInstance().getWebDiskW()->refreshFileList(pdu);
            else QMessageBox::information(this,"重命名",pdu->caData);
            break;
        }
        case ENUM_MSG_TYPE_ENTER_DIR_RESPOND:       //进入文件夹回复
        {
            if(strcmp(pdu->caData, ENTER_DIR_OK) == 0)
            {
                OpeWidget::getInstance().getWebDiskW()->refreshFileList(pdu);
                m_curPath = m_curPathTemp;
            }
            else QMessageBox::information(this,"进入文件夹",pdu->caData);
            break;
        }
        case ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST_RESPOND:  //上传文件请求回复
        {
            fileRecv.file.setFileName(OpeWidget::getInstance().getWebDiskW()->getUploadFilePath());
            if(!fileRecv.file.open(QIODevice::ReadOnly))
            {
                QMessageBox::warning(this,"上传文件失败","打开文件失败");
                return;
            }
            m_elapsedTimer = new QElapsedTimer;
            FileRecv &fileRecv = TCPClient::getInstance().getFileRecv();

            char *pBuffer = new char[4096]; //读取缓冲,实验测试4096效率较高
            qint64 ret = 0;     //实际读取数据数量
            while(1)
            {
                ret = fileRecv.file.read(pBuffer,4096);  //将file数据读入到pBuffer,返回实际读取的数据数量
                fileRecv.recvedSize += ret;
                //上传进度
                QString process = QString("%1%").arg((double)fileRecv.recvedSize/(double)fileRecv.totalSize*100);
                //上传速度
                secondTime = m_elapsedTimer->nsecsElapsed();
                double dv = (double)ret/(secondTime - firstTime) * 1000000000.0;
                QString speed = std::isinf(dv) ? "INF" : byteConversion(dv) + "/S";

                firstTime = secondTime;
                OpeWidget::getInstance().getFileTransferW()->updateFTWItem(fileRecv.recvedSize,
                                                                           process,
                                                                           speed,
                                                                           "正在上传");
                if(ret > 0 && ret <=4096)   //如果读取到数据
                {
                    TCPClient::getInstance().getTCPSocket().write(pBuffer,ret);//将读取的数据发送给服务器，服务器以二进制字节收取
                    TCPClient::getInstance().getTCPSocket().flush(); // 确保数据立即发送
                }
                else if(ret == 0)break;     //读取结束
                else
                {
                    OpeWidget::getInstance().getFileTransferW()->updateFTWItem(fileRecv.recvedSize,
                                                                               process,
                                                                               "0",
                                                                               "上传失败");
                }
            }
            m_elapsedTimer->invalidate();
            firstTime = 0;
            secondTime = 0;

            delete []pBuffer;
            pBuffer = nullptr;
            qDebug() << "关闭上传文件线程";

            break;
        }
        case ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND:     //上传文件回复
        {
            QMessageBox::information(this,"上传文件",pdu->caData);
            if(strcmp(pdu->caData, UPLOAD_FILE_OK) == 0)
            {
                OpeWidget::getInstance().getFileTransferW()->updateFTWItem(fileRecv.recvedSize,
                                                                           "100%",
                                                                           "0",
                                                                           "上传成功");
                OpeWidget::getInstance().getWebDiskW()->refreshFileList(pdu);
            }
            fileRecv.file.close();
            fileRecv.recvedSize = 0;
            fileRecv.totalSize = 0;
            break;
        }
        case ENUM_MSG_TYPE_SHARE_FILE_REQUEST:      //转发分享文件请求
        {
            OpeWidget::getInstance().getFileRecvD()->addFileRecvDialog(pdu);
            break;
        }
        case ENUM_MSG_TYPE_REFRESH_SAVE_RESPOND:    //保存文件窗口刷新文件回复
        {
            FileSaveDialog::getInstance().updateFileSaveDialog(pdu);
            break;
        }
        case ENUM_MSG_TYPE_ENTER_DIR_SAVE_RESPOND:  //保存窗口进入文件夹回复
        {
            if(strcmp(pdu->caData, ENTER_DIR_OK) == 0)
            {
                FileSaveDialog::getInstance().updateFileSaveDialog(pdu);
                FileSaveDialog::getInstance().setCurPath(FileSaveDialog::getInstance().getCurPathTemp());
            }
            else QMessageBox::information(this,"进入文件夹",pdu->caData);
            break;
        }
        case ENUM_MSG_TYPE_CREATE_DIR_SAVE_RESPOND:      //保存文件窗口新建文件夹回复
        {
            QMessageBox::information(this,"新建文件夹",pdu->caData);
            if(strcmp(pdu->caData, CREATE_DIR_OK) == 0)
                FileSaveDialog::getInstance().updateFileSaveDialog(pdu);
            break;
        }
        case ENUM_MSG_TYPE_SAVE_FILE_RESPOND:       //保存文件回复
        {
            QMessageBox::information(this,"保存文件",pdu->caData);
            if(strcmp(pdu->caData, SAVE_FILE_OK) == 0)
            {
                FileSaveDialog::getInstance().close();
                OpeWidget::getInstance().getFileRecvD()->deleteFileInfoItem(
                    OpeWidget::getInstance().getFileRecvD()->getSaveFileIndex());
            }
            break;
        }
        case ENUM_MSG_TYPE_MOVE_FILE_RESPOND:       //移动文件回复
        {
            QMessageBox::information(this,"移动文件",pdu->caData);
            FileSaveDialog::getInstance().setSaveFlag(true);
            FileSaveDialog::getInstance().close();
            if(strcmp(pdu->caData, MOVE_FILE_OK) == 0)
            {
                OpeWidget::getInstance().getWebDiskW()->refresh();
            }

            break;
        }
        default:
            break;
    }
}

FileRecv &TCPClient::getFileRecv()
{
    return fileRecv;
}

void TCPClient::startElapsedTimer()
{
    // m_elapsedTimer->restart();
    // firstTime = 0;
    // secondTime = 0;
}

void TCPClient::recvMsg()
{
    if(!fileRecv.recvingFlag)
    {
        while(m_tcpSocket.bytesAvailable())
        {
            //qDebug() << "(TCPClient::recvMsg)客户端接收数据大小:" << m_tcpSocket.bytesAvailable(); //读取可读字节数
            uint uiPDULen = 0;
            m_tcpSocket.read((char*)&uiPDULen,sizeof(uint));  //获取协议单元数据总大小
            uint uiMsgLen = uiPDULen - sizeof(PDU);     //获取实际数据大小
            std::shared_ptr<PDU> pdu = mk_shared_PDU(uiMsgLen);
            m_tcpSocket.read((char*)pdu.get()+sizeof(uiPDULen),uiPDULen-sizeof(uiPDULen));
            pdu->uiPDULen = uiPDULen;
            showPDUInfo(pdu);
            handleRpdPDU(pdu);
        }
    }
    else
    {
        QByteArray recvBuff = m_tcpSocket.readAll();
        fileRecv.file.write(recvBuff);
        fileRecv.recvedSize += recvBuff.size();

        //下载进度
        QString process = QString("%1%").arg((double)fileRecv.recvedSize/(double)fileRecv.totalSize*100);
        //下载速度
        secondTime = m_elapsedTimer->nsecsElapsed();
        double dv = (double)recvBuff.size()/(secondTime - firstTime) * 1000.0;
        QString speed = std::isinf(dv) ? "INF" : byteConversion(dv) + "/S";
        firstTime = secondTime;

        OpeWidget::getInstance().getFileTransferW()->updateFTWItem(fileRecv.recvedSize,
                                                                   process,
                                                                   speed,
                                                                   "正在下载");

        if(fileRecv.recvedSize >= fileRecv.totalSize)
        {
            fileRecv.file.close();
            fileRecv.recvingFlag = false;
            m_elapsedTimer->invalidate();
            firstTime = 0;
            secondTime = 0;
            if(fileRecv.recvedSize == fileRecv.totalSize)
            {
                OpeWidget::getInstance().getFileTransferW()->updateFTWItem(fileRecv.recvedSize,
                                                                           process,
                                                                           "0",
                                                                           "下载成功");
                QMessageBox::information(this,"下载文件","下载文件成功");
            }
            else
            {
                OpeWidget::getInstance().getFileTransferW()->updateFTWItem(fileRecv.recvedSize,
                                                                           process,
                                                                           "0",
                                                                           "下载失败");
                QMessageBox::critical(this,"下载文件","下载文件失败");
            }

            fileRecv.recvedSize = 0;
            fileRecv.totalSize = 0;
        }
    }
}

//登录按键响应函数
void TCPClient::on_login_pb_clicked()
{
    QString strName = ui->name_le->text();
    QString strPwd = ui->pwd_le->text();
    if(!strName.isEmpty() && !strPwd.isEmpty())
    {
        m_loginName = strName;
        std::shared_ptr<PDU> pdu = mk_shared_PDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_REQUEST;
        strncpy(pdu->caData,strName.toUtf8(),32);
        strncpy(pdu->caData+32,strPwd.toUtf8(),32);
        m_tcpSocket.write((char*)pdu.get(),pdu->uiPDULen);
    }
    else
    {
        QMessageBox::critical(this,"登录","登录失败：用户名和密码不能为空");
    }
}

//注册按键响应函数
void TCPClient::on_regist_pb_clicked()
{
    QString strName = ui->name_le->text();
    QString strPwd = ui->pwd_le->text();
    if(!strName.isEmpty() && !strPwd.isEmpty())
    {
        if(strName.toUtf8().size() <= 32)
        {
            std::shared_ptr<PDU> pdu = mk_shared_PDU(0);
            pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;
            strncpy(pdu->caData,strName.toUtf8(),32);
            strncpy(pdu->caData+32,strPwd.toUtf8(),32);
            m_tcpSocket.write((char*)pdu.get(),pdu->uiPDULen);
        }
        else QMessageBox::critical(this,"注册","注册失败：用户名字符不能超过32字符(中文3个字符)");
    }
    else
    {
        QMessageBox::critical(this,"注册","注册失败：用户名和密码不能为空");
    }
}


//连接按键响应函数
void TCPClient::on_connect_pb_clicked()
{
    if(isConnected)
    {
        QMessageBox::warning(this,"连接服务器","已连接服务器");
    }
    else
    {
        m_strIP = ui->ip_le->text();
        m_usPort = ui->port_le->text().toInt();
        qDebug() << "(TCPClient)加载成功" << "ip:" << m_strIP << " " << "port:" << m_usPort;

        ui->status_lab->setText("连接中...");
        OpeWidget::getInstance().getStatus()->setText("连接中...");
        // 创建一个 QPalette 对象
        QPalette palette = ui->status_lab->palette();
        // 设置字体颜色
        palette.setColor(QPalette::WindowText, QColor());  // 将字体颜色设置为黑色
        // 将 QPalette 应用到 QLabel
        ui->status_lab->setPalette(palette);
        OpeWidget::getInstance().getStatus()->setPalette(palette);
        //连接服务器
        m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);
        // m_tcpSocket.connectToHost("127.0.0.1",8888); //本地连接
    }
}

