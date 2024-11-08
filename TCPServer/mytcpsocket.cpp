#include "mytcpsocket.h"
#include "mytcpserver.h"
#include "UniversalFunction.h"
#include <QDebug>

MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this,SIGNAL(readyRead()),this,SLOT(recvMsg()));
    connect(this,SIGNAL(disconnected()),this,SLOT(clientOffline()));
}

//根据路径生成刷新文件夹信息的PDU
std::shared_ptr<PDU> MyTcpSocket::refreshDirPDU(QString pCurPath)
{
    QDir dir(pCurPath);
    QFileInfoList fileInfoList = dir.entryInfoList();   //将该路径下的所有文件信息存入列表
    //前两个文件信息.和..是此文件夹和上一级文件夹，不用将这两个数据传到客户端
    std::shared_ptr<PDU> pdu = mk_shared_PDU(
        (sizeof(FileInfo)) * (fileInfoList.size() - 2));
    FileInfo *pFileInfo = nullptr;  //结构体指针,该指针每次+1，rpdPDU移动sizeof(FileInfo)个字节

    for(int i = 0; i<fileInfoList.size() - 2; ++i)
    {
        pFileInfo = (FileInfo*)(pdu->caMsg) + i;
        //存放文件名字
        memcpy(pFileInfo->caFileNameUtf8,
               fileInfoList[i+2].fileName().toUtf8(),
               fileInfoList[i+2].fileName().toUtf8().size());

        //存放文件类型，忽略前两个信息，从第三个开始
        if(fileInfoList[i+2].isDir())pFileInfo->iFileType = 0;   //文件夹类型
        else if(fileInfoList[i+2].isFile())
        {
            QString suffix = fileInfoList[i+2].suffix();  //文件后缀名
            pFileInfo->iFileType = determineFileType(suffix);
        }

        //存放文件大小
        pFileInfo->llFileSize = fileInfoList[i+2].size();
    }
    return pdu;
}

void MyTcpSocket::handleRqsPDU(std::shared_ptr<PDU> pdu)
{
    switch(pdu->uiMsgType)
    {
        case ENUM_MSG_TYPE_REGIST_REQUEST:  //注册请求
        {
            char caName[32];
            char caPwd[32];
            strncpy(caName,pdu->caData,32);
            strncpy(caPwd,pdu->caData+32,32);
            bool ret = OpeDB::getInstance().handleRegist(caName,caPwd);
            auto rpdPDU = mk_shared_PDU(0); //回复信息PDU
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_REGIST_RESPOND;
            if(ret)
            {
                QDir dir;
                dir.mkdir(QString("./UserWebDisk/%1").arg(caName)); //在服务端创建以该注册名创建文件夹
                strcpy(rpdPDU->caData,REGIST_OK);
            }
            else strcpy(rpdPDU->caData,REGIST_FAILED);
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_LOGIN_REQUEST:  //登录请求
        {
            uint ret = OpeDB::getInstance().handleLogin(pdu->caData,pdu->caData+32);
            auto rpdPDU = mk_shared_PDU(0); //回复信息PDU
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_LOGIN_RESPOND;

            ret == 0 ? strcpy(rpdPDU->caData,LOGIN_OK):
            ret == 1 ? strcpy(rpdPDU->caData,LOGIN_FAILED_NOEXIST):
            ret == 2 ? strcpy(rpdPDU->caData,LOGIN_FAILED_PWDERROR):
                       strcpy(rpdPDU->caData,LOGIN_FAILED_RELOGIN);
            if(ret == 0)socketName = pdu->caData;   //存放登录的用户名

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_MSGBOXCLICKED_RESPOND:   //处理客户端已确认消息提示框
        {
            write((char*)pdu.get(),pdu->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_ALL_ONLINEUSR_REQUEST:   //在线用户请求
        {
            QStringList OnlineUsr = OpeDB::getInstance().handeleAllOnlineUsr();
            uint uiMsgLen = OnlineUsr.size() * 32;
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(uiMsgLen);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINEUSR_RESPOND;
            for(uint i=0; i<OnlineUsr.size(); ++i)
            {
                qDebug() << OnlineUsr.at(i);
                memcpy((char*)(rpdPDU->caMsg)+i*32,
                       OnlineUsr.at(i).toUtf8(),
                       OnlineUsr.at(i).toUtf8().size());
            }
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_SEARCH_USR_REQUEST:  //搜索用户请求
        {
            char searchUsrName[32];
            memcpy(searchUsrName,pdu->caData,32);
            auto rearchResultMap = OpeDB::getInstance().handleSearchUsr(searchUsrName);
            auto uiMsgLen = rearchResultMap.size() * 34;

            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(uiMsgLen);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_SEARCH_USR_RESPOND;
            if(uiMsgLen == 0)strcpy(rpdPDU->caData,SEARCH_USR_NOEXIST);
            else
            {
                strcpy(rpdPDU->caData,SEARCH_USR_OK);
                uint i = 0;
                for(auto iter = rearchResultMap.cbegin();
                     iter != rearchResultMap.cend(); ++iter,++i)
                {
                    memcpy((char*)rpdPDU->caMsg+i*34,
                           iter.key().toUtf8(),
                           iter.key().toUtf8().size());
                    memcpy((char*)rpdPDU->caMsg+32+i*34,
                           iter.value().toStdString().c_str(),
                           iter.value().size());
                }
            }
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:  //添加好友请求
        {
            int ret = OpeDB::getInstance().queryUsrState(pdu->caData,pdu->caData+32);
            //回复信息PDU
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPOND;

            switch(ret)
            {
                case -5:    //故障情况
                {
                    strcpy(rpdPDU->caData,UNKONW_ERROR);
                    break;
                }
                case -4:    //添加自己为好友
                {
                    strcpy(rpdPDU->caData,ADD_FRIEND_SELF);
                    break;
                }
                case -3:    //账号已注销，对方不存在
                {
                    strcpy(rpdPDU->caData,ADD_FRIEND_NOEXIST);
                    break;
                }
                case -2:    //对方不在线
                {
                    strcpy(rpdPDU->caData,ADD_FRIEND_OFFLINE);
                    break;
                }
                case -1:    //对方在线，询问客户端是否同意添加好友
                {
                    strcpy(rpdPDU->caData,ADD_FRIEND_SENT);
                    char name[32];
                    memcpy(name,pdu->caData,32);
                    MyTcpServer::getInstance().transpond(name,pdu);     //转发
                    break;
                }
                case 0:
                case 1:    //双方已为好友
                {
                    strcpy(rpdPDU->caData,ADD_FRIEND_EXITED);
                    break;
                }
                default:
                    break;
            }

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND:   //同意添加好友请求
        {
            bool ret = OpeDB::getInstance().handleAddFriend(pdu->caData,pdu->caData+32);
            if(ret)
            {
                //创建回复PDU
                char myName[32];
                memcpy(myName,pdu->caData+32,32);
                auto myFriendMap = OpeDB::getInstance().handleRefFriend(myName);
                auto respondMsgLen = myFriendMap.size() * 34;
                std::shared_ptr<PDU> respondPDU = mk_shared_PDU(respondMsgLen);    //回复PDU
                respondPDU->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND_RESPOND;
                uint i = 0;
                for(auto iter = myFriendMap.cbegin();
                     iter != myFriendMap.cend(); ++iter, ++i)
                {
                    memcpy((char*)respondPDU->caMsg+i*34,
                           iter.key().toUtf8(),
                           iter.key().toUtf8().size());
                    memcpy((char*)respondPDU->caMsg+32+i*34,
                           iter.value().toStdString().c_str(),
                           iter.value().size());
                }
                write((char*)respondPDU.get(),respondPDU->uiPDULen);

                //创建转发PDU
                char perName[32];
                memcpy(perName,pdu->caData,32);
                auto perFriendMap = OpeDB::getInstance().handleRefFriend(perName);
                auto transpondMsgLen = perFriendMap.size() * 34;
                std::shared_ptr<PDU> transpondPDU = mk_shared_PDU(transpondMsgLen);
                transpondPDU->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND;
                memcpy(transpondPDU->caData,pdu->caData,64);
                i = 0;
                for(auto iter = perFriendMap.cbegin();
                     iter != perFriendMap.cend(); ++iter, ++i)
                {
                    memcpy((char*)transpondPDU->caMsg+i*34,
                           iter.key().toUtf8(),
                           iter.key().toUtf8().size());
                    memcpy((char*)transpondPDU->caMsg+32+i*34,
                           iter.value().toStdString().c_str(),
                           iter.value().size());
                }
                char name[32];
                memcpy(name,transpondPDU->caData,32);
                MyTcpServer::getInstance().transpond(name,transpondPDU);     //转发
            }
            break;
        }
        case ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_RESPOND:   //拒绝添加好友请求
        {
            char name[32];
            memcpy(name,pdu->caData,32);
            MyTcpServer::getInstance().transpond(name,pdu);     //转发
            break;
        }
        case ENUM_MSG_TYPE_REFRESH_FRIEND_REQUEST:  //刷新好友列表请求
        {
            char name[32];
            memcpy(name,pdu->caData,32);
            auto FriendMap = OpeDB::getInstance().handleRefFriend(name);
            auto uiMsgLen = FriendMap.size() * 34;
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(uiMsgLen);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_REFRESH_FRIEND_RESPOND;

            uint i = 0;
            for(auto iter = FriendMap.cbegin();
                 iter != FriendMap.cend(); ++iter, ++i)
            {
                memcpy(rpdPDU->caMsg+i*34,
                       iter.key().toUtf8(),
                       iter.key().toUtf8().size());
                memcpy(rpdPDU->caMsg+32+i*34,
                       iter.value().toStdString().c_str(),
                       iter.value().size());
            }
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST:   //删除好友请求
        {
            bool ret = OpeDB::getInstance().handleDelFriend(pdu->caData,pdu->caData+32);
            char myName[32];
            memcpy(myName,pdu->caData+32,32);
            auto myFriendMap = OpeDB::getInstance().handleRefFriend(myName);
            auto respondMsgLen = myFriendMap.size() * 34;
            std::shared_ptr<PDU> respondPDU = mk_shared_PDU(respondMsgLen);    //回复PDU
            respondPDU->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND;
            uint i = 0;
            for(auto iter = myFriendMap.cbegin();
                 iter != myFriendMap.cend(); ++iter, ++i)
            {
                memcpy((char*)respondPDU->caMsg+i*34,
                       iter.key().toUtf8(),
                       iter.key().toUtf8().size());
                memcpy((char*)respondPDU->caMsg+32+i*34,
                       iter.value().toStdString().c_str(),
                       iter.value().size());
            }
            strcpy(respondPDU->caData, ret ? DELETE_FRIEND_OK : DELETE_FRIEND_FAILED);
            memcpy(respondPDU->caData+32, pdu->caData, 32);
            write((char*)respondPDU.get(),respondPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_SENDMSG_REQUEST:         //发送消息请求
        {
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_SENDMSG_RESPOND;
            //判断双方状态
            int ret = OpeDB::getInstance().queryUsrState(pdu->caData,pdu->caData+32);
            switch(ret)
            {
                case 1:     //好友在线
                {
                    strcpy(rpdPDU->caData,SEND_MESSAGE_OK);
                    char name[32];
                    memcpy(name,pdu->caData,32);
                    MyTcpServer::getInstance().transpond(name,pdu);    //将消息发送至好友
                    break;
                }
                case 0:     //好友不在线
                {
                    strcpy(rpdPDU->caData,SEND_MESSAGE_OFFLINE);
                    break;
                }
                case -1:
                case -2:    //不是好友
                {
                    strcpy(rpdPDU->caData,SEND_MESSAGE_NOFRIEND);
                    break;
                }
                case -3:    //对方已注销
                {
                    strcpy(rpdPDU->caData,SEND_MESSAGE_NOEXIST);
                    break;
                }
                default:    //故障
                {
                    strcpy(rpdPDU->caData,UNKONW_ERROR);
                    break;
                }
            }
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_SENDPUBLICMSG_REQUEST:   //发送群聊消息请求
        {
            auto onlineUsrList = OpeDB::getInstance().handeleAllOnlineUsr();
            for(uint i = 0; i<onlineUsrList.size(); ++i)
                MyTcpServer::getInstance().transpond(onlineUsrList.at(i),pdu);  //将消息发送至好友

            break;
        }
        //新建文件夹请求或保存文件窗口新建文件夹请求
        case ENUM_MSG_TYPE_CREATE_DIR_REQUEST:
        case ENUM_MSG_TYPE_CREATE_DIR_SAVE_REQUEST:
        {
            QDir dir;
            QString strCurPath = QString("%1").arg((char*)pdu->caMsg);  //当前目录
            bool ret = dir.exists(strCurPath);
            std::shared_ptr<PDU> rpdPDU1 = mk_shared_PDU(0);
            rpdPDU1->uiMsgType = (pdu->uiMsgType == ENUM_MSG_TYPE_CREATE_DIR_REQUEST) ?
                                                    ENUM_MSG_TYPE_CREATE_DIR_RESPOND :
                                                    ENUM_MSG_TYPE_CREATE_DIR_SAVE_RESPOND;

            if(ret)     //当前目录存在,可以在该目录下新建文件夹
            {
                char caNewDir[64];
                memcpy(caNewDir,pdu->caData,64);    //新建文件夹名称
                QString strNewPath = strCurPath + "/" + caNewDir;   //新建文件夹后的新路径
                ret = dir.exists(strNewPath);
                if(ret)     //已存在该目录，新建文件夹失败
                {
                    strcpy(rpdPDU1->caData,CREATE_DIR_FILE_EXISTED);
                }
                else        //不存在该目录，可以新建文件夹
                {
                    dir.mkdir(strNewPath);
                    std::shared_ptr<PDU> rpdPDU2 = refreshDirPDU(strCurPath);
                    rpdPDU2->uiMsgType = (pdu->uiMsgType == ENUM_MSG_TYPE_CREATE_DIR_REQUEST) ?
                                                            ENUM_MSG_TYPE_CREATE_DIR_RESPOND :
                                                            ENUM_MSG_TYPE_CREATE_DIR_SAVE_RESPOND;
                    strcpy(rpdPDU2->caData,CREATE_DIR_OK);
                    write((char*)rpdPDU2.get(),rpdPDU2->uiPDULen);
                    break;
                }
            }
            else        //当前目录不存在
            {
                strcpy(rpdPDU1->caData,CREATE_DIR_PATH_NOEXIST);
            }
            write((char*)rpdPDU1.get(),rpdPDU1->uiPDULen);
            break;
        }
        //刷新文件夹请求或保存文件窗口刷新文件请求
        case ENUM_MSG_TYPE_REFRESH_DIR_REQUEST:
        case ENUM_MSG_TYPE_REFRESH_SAVE_REQUEST:
        {
            char *pCurPath = new char[pdu->uiMsgLen];
            memcpy(pCurPath,pdu->caMsg,pdu->uiMsgLen);  //得到当前路径

            //根据路径生成刷新文件夹信息的PDU
            std::shared_ptr<PDU> rpdPDU = refreshDirPDU(pCurPath);
            rpdPDU->uiMsgType = (pdu->uiMsgType == ENUM_MSG_TYPE_REFRESH_DIR_REQUEST) ?
                                                   ENUM_MSG_TYPE_REFRESH_DIR_RESPOND :
                                                   ENUM_MSG_TYPE_REFRESH_SAVE_RESPOND;

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_DELETE_DIRORFILE_REQUEST:      //删除文件请求
        {
            char caName[64];
            strcpy(caName,pdu->caData);
            char *pPath = new char[pdu->uiMsgLen];
            memcpy(pPath,pdu->caMsg,pdu->uiMsgLen);
            QString delPath = QString("%1/%2").arg(pPath).arg(caName);
            QFileInfo fileInfo(delPath);

            bool ret = false;
            QDir dir;
            if(fileInfo.isDir())    //要删除的是文件夹
            {
                dir.setPath(delPath);
                ret = dir.removeRecursively();
            }
            else if(fileInfo.isFile())  //要删除的是常规文件
                ret = dir.remove(delPath);

            std::shared_ptr<PDU> rpdPDU = refreshDirPDU(pPath);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_DELETE_DIRORFILE_RESPOND;

            if(ret)
                memcpy(rpdPDU->caData,DELETE_DIRORFILE_OK,strlen(DELETE_DIRORFILE_OK));
            else
                memcpy(rpdPDU->caData,DELETE_DIRORFILE_FAILED,strlen(DELETE_DIRORFILE_FAILED));

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_RENAME_DIRORFILE_REQUEST:    //重命名文件请求
        {
            QString newName = pdu->caData;
            QString oldName = pdu->caMsg;   //oldName存放在caMsg的前一部分
            QString curPath = pdu->caMsg + oldName.toUtf8().size() + 1;
            QString oldPath = QString("%1/%2").arg(curPath).arg(oldName);
            QString newPath = QString("%1/%2").arg(curPath).arg(newName);

            QDir dir;
            bool ret = dir.rename(oldPath,newPath);
            std::shared_ptr<PDU> rpdPDU = refreshDirPDU(curPath);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_RENAME_DIRORFILE_RESPOND;
            strcpy(rpdPDU->caData, ret ? RENAME_DIRORFILE_OK : RENAME_DIRORFILE_FAILED);

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        //进入文件夹请求或保存文件窗口进入文件请求
        case ENUM_MSG_TYPE_ENTER_DIR_REQUEST:
        case ENUM_MSG_TYPE_ENTER_DIR_SAVE_REQUEST:
        {
            QString dirName = pdu->caData;
            QString curPath = pdu->caMsg;
            QString enterDirPath = curPath + "/" + dirName;
            QFileInfo fileInfo(enterDirPath);
            if(fileInfo.isDir())
            {
                std::shared_ptr<PDU> rpdPDU = refreshDirPDU(enterDirPath);
                rpdPDU->uiMsgType = (pdu->uiMsgType == ENUM_MSG_TYPE_ENTER_DIR_REQUEST) ?
                                                       ENUM_MSG_TYPE_ENTER_DIR_RESPOND :
                                                       ENUM_MSG_TYPE_ENTER_DIR_SAVE_RESPOND;
                strcpy(rpdPDU->caData,ENTER_DIR_OK);
                write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            }
            else if(fileInfo.isFile())
            {
                std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
                rpdPDU->uiMsgType = (pdu->uiMsgType == ENUM_MSG_TYPE_ENTER_DIR_REQUEST) ?
                                                       ENUM_MSG_TYPE_ENTER_DIR_RESPOND :
                                                       ENUM_MSG_TYPE_ENTER_DIR_SAVE_RESPOND;
                strcpy(rpdPDU->caData,ENTER_DIR_FAILED);
                write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            }
            break;
        }
        case ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST:  //上传文件请求
        {
            char uploadFileName[64] = {'\0'};
            strcpy(uploadFileName,pdu->caData);
            //文件大小存在pdu前部分
            QString strUploadFileSize = pdu->caMsg;
            qint64 uploadFileSize = strUploadFileSize.toLongLong();
            char *uploadPath = new char[pdu->uiMsgLen - strUploadFileSize.size() - 1];
            memcpy(uploadPath,
                   pdu->caMsg + strUploadFileSize.size() + 1,
                   pdu->uiMsgLen - strUploadFileSize.size() - 1);

            QString uploadFilePath = QString("%1/%2").arg(uploadPath).arg(uploadFileName);

            fileRecv.file.setFileName(uploadFilePath);
            if(fileRecv.file.open(QIODevice::WriteOnly))    //以只写的方式打开文件，若文件不存在，会自动创建文件
            {
                fileRecv.recvingFlag = true;
                fileRecv.totalSize = uploadFileSize;
                fileRecv.recvedSize = 0;
                m_curPath = uploadPath;
            }

            //释放指针
            delete []uploadPath;
            uploadPath = nullptr;

            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST_RESPOND;
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);

            break;
        }
        case ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST:   //下载文件请求
        {
            QString downloadFilePath = QString("%1/%2").arg(pdu->caMsg).arg(pdu->caData);

            //开始发送数据
            QFile file(downloadFilePath);
            file.open(QIODevice::ReadOnly);

            char *pBuffer = new char[4096]; //读取缓冲,实验测试4096效率较高
            qint64 ret = 0;     //实际读取数据数量
            while(1)
            {
                ret = file.read(pBuffer,4096);  //将file数据读入到pBuffer,返回实际读取的数据数量
                if(ret > 0 && ret <=4096)   //如果读取到数据
                   write(pBuffer,ret);//将读取的数据发送给客户端，客户端以二进制字节收取
                else if(ret == 0)break;     //读取结束
                else
                {
                    qDebug() << "客户端向服务器下载文件失败";
                    break;
                }
            }
            file.close();
            delete []pBuffer;
            pBuffer = nullptr;

            break;
        }
        case ENUM_MSG_TYPE_SHARE_FILE_REQUEST:      //分享文件请求
        {
            //提取分享文件路径
            QString m_shareFilePath = pdu->caMsg;
            qDebug() << "文件路径:" << m_shareFilePath;

            //截取文件名,获取路径右端文件名
            int index = m_shareFilePath.lastIndexOf('/');
            QString shareFileName = m_shareFilePath.right(m_shareFilePath.size()-index-1);
            qDebug() << "文件名字:" << shareFileName;

            //提取接收方数量
            char caRecverNum[sizeof(m_shareFilePath.size())];
            memcpy(caRecverNum, pdu->caMsg + m_shareFilePath.toUtf8().size() + 1,
                   sizeof(m_shareFilePath.size()));
            int recverNum = QString("%1").arg(caRecverNum).toInt();
            qDebug() << "接收人数:" << recverNum;

            QFileInfo fileInfo(m_shareFilePath);
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(sizeof(FileInfo) + m_shareFilePath.toUtf8().size() + 1);

            FileInfo *pFileInfo = (FileInfo*)(rpdPDU->caMsg);
            //存放文件名字
            memcpy(pFileInfo->caFileNameUtf8,
                   shareFileName.toUtf8(),
                   shareFileName.toUtf8().size());
            //存放文件类型
            if(fileInfo.isDir())pFileInfo->iFileType = 0;   //文件夹类型
            else if(fileInfo.isFile())
            {
                QString suffix = fileInfo.suffix();  //文件后缀名
                pFileInfo->iFileType = determineFileType(suffix);
            }
            //存放文件大小
            pFileInfo->llFileSize = fileInfo.size();
            //存放分享文件路径
            memcpy(rpdPDU->caMsg + sizeof(FileInfo),pdu->caMsg,m_shareFilePath.toUtf8().size());

            //提取发送方名字
            rpdPDU->uiMsgType = pdu->uiMsgType;
            strcpy(rpdPDU->caData, pdu->caData);

            //提取接收方名字,转发
            for(int i = 0; i < recverNum; ++i)
            {
                char recverName[64];
                strcpy(recverName,
                       pdu->caMsg + m_shareFilePath.toUtf8().size() + 1
                       + sizeof(m_shareFilePath.size()) + 1
                       + i * 64);
                qDebug() << "接收好友:" << recverName;
                MyTcpServer::getInstance().transpond(recverName, rpdPDU);
            }

            break;
        }
        case ENUM_MSG_TYPE_SAVE_FILE_REQUEST:       //保存文件请求
        {
            QString savePath = QString("%1").arg(pdu->caMsg);
            QString shareFilePath = QString("%1")
                                        .arg(pdu->caMsg + savePath.toUtf8().size() + 1);
            //获得分享文件的文件名
            int index = shareFilePath.lastIndexOf('/');
            QString shareFileName = shareFilePath.right(shareFilePath.size() - index - 1);
            QFileInfo fileInfo(shareFilePath);
            //将保存路径和文件名拼接成完整的保存文件名
            QString saveFilePath = savePath + "/" + shareFileName;

            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_SAVE_FILE_RESPOND;

            //判断保存文件路径下是否已有同名文件
            QDir dir;
            bool ret = dir.exists(saveFilePath);
            if(ret)     //已存在该目录，新建文件夹失败
            {
                strcpy(rpdPDU->caData,SAVE_FILE_FAILED_EXISTED);
            }
            else
            {
                //常规文件的拷贝
                if(fileInfo.isFile())
                    ret = QFile::copy(shareFilePath,saveFilePath);
                //文件夹的拷贝
                else if(fileInfo.isDir())
                    ret = copyDir(shareFilePath,saveFilePath);
                strcpy(rpdPDU->caData, ret ? SAVE_FILE_OK : SAVE_FILE_FAILED);
            }

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        case ENUM_MSG_TYPE_MOVE_FILE_REQUEST:       //移动文件请求
        {
            QString destPath = QString("%1").arg(pdu->caMsg);
            QString srcPath = QString("%1").arg(pdu->caMsg + destPath.toUtf8().size() + 1);

            //获得移动文件的文件名
            int index = srcPath.lastIndexOf('/');
            QString moveFileName = srcPath.right(srcPath.size() - index - 1);

            QString destFilePath = destPath + "/" + moveFileName;
            bool ret = QFile::rename(srcPath,destFilePath);
            std::shared_ptr<PDU> rpdPDU = mk_shared_PDU(0);
            rpdPDU->uiMsgType = ENUM_MSG_TYPE_MOVE_FILE_RESPOND;
            strcpy(rpdPDU->caData, ret ? MOVE_FILE_OK : MOVE_FILE_FAILED);

            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
            break;
        }
        default:
            break;
    }
}

QString MyTcpSocket::getName()
{
    return socketName;
}

bool MyTcpSocket::copyDir(QString srcDir, QString destDir)
{
    QDir dir;
    bool ret1 = dir.mkdir(destDir);
    bool ret2 = true, ret3 = true;
    dir.setPath(srcDir);
    QFileInfoList fileInfoList = dir.entryInfoList();   //将该路径下的所有文件信息存入列表
    for(int i = 0; i < fileInfoList.size() - 2; ++i)
    {
        if(fileInfoList[i+2].isFile())
        {
            ret2 = QFile::copy(srcDir + "/" + fileInfoList[i+2].fileName(),
                               destDir + "/" + fileInfoList[i+2].fileName());
        }
        else if(fileInfoList[i+2].isDir())
        {
            ret3 = copyDir(srcDir + "/" + fileInfoList[i+2].fileName(),
                           destDir + "/" + fileInfoList[i+2].fileName());
        }
    }
    return ret1 &&ret2 && ret3;
}

void MyTcpSocket::recvMsg()
{
    if(!fileRecv.recvingFlag)
    {
        while(this->bytesAvailable())
        {
            qDebug() << "(MyTcpSocket::recvMsg)服务器接收数据:" << this->bytesAvailable(); //读取可读字节数
            uint uiPDULen = 0;
            this->read((char*)&uiPDULen,sizeof(uint));  //获取协议单元数据总大小
            uint uiMsgLen = uiPDULen - sizeof(PDU);     //获取实际数据大小

            std::shared_ptr<PDU> pdu = mk_shared_PDU(uiMsgLen);
            this->read((char*)pdu.get()+sizeof(uiPDULen),uiPDULen-sizeof(uiPDULen));
            pdu->uiPDULen = uiPDULen;

            showPDUInfo(pdu);

            handleRqsPDU(pdu);
        }
    }
    else
    {
        QByteArray recvBuff = readAll();
        fileRecv.file.write(recvBuff);
        fileRecv.recvedSize += recvBuff.size();
        qDebug() << "已上传:" << QString("%1%").
                    arg((double)fileRecv.recvedSize/(double)fileRecv.totalSize*100);
        if(fileRecv.recvedSize >= fileRecv.totalSize)
        {
            fileRecv.file.close();
            fileRecv.recvingFlag = false;
            std::shared_ptr<PDU> rpdPDU;
            if(fileRecv.recvedSize == fileRecv.totalSize)
            {
                rpdPDU = refreshDirPDU(m_curPath);
                rpdPDU->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND;
                strcpy(rpdPDU->caData,UPLOAD_FILE_OK);
            }
            else
            {
                rpdPDU = mk_shared_PDU(0);
                rpdPDU->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND;
                strcpy(rpdPDU->caData,UPLOAD_FILE_FAILED);
            }
            fileRecv.recvedSize = 0;
            fileRecv.totalSize = 0;
            write((char*)rpdPDU.get(),rpdPDU->uiPDULen);
        }
    }
}

void MyTcpSocket::clientOffline()
{
    OpeDB::getInstance().handeleOffline(socketName.toStdString().c_str());
    emit offline(this);     //发送客户端下线信号
}
