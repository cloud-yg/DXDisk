#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <QtTypes>
#include <QFile>

typedef unsigned int uint;

#define UNKONW_ERROR "unknow error"

#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed : name existed"

#define LOGIN_OK "login ok"
#define LOGIN_FAILED_NOEXIST "login failed : name not exist"
#define LOGIN_FAILED_PWDERROR "login failed : password error"
#define LOGIN_FAILED_RELOGIN "login failed : relogin"

#define SEARCH_USRNAME_NULL "search failed : name is null"
#define SEARCH_USR_NOEXIST "search failed : user not exist"
#define SEARCH_USR_OK "search ok"

#define ADD_FRIEND_EXITED "add friend failed : friend exist"
#define ADD_FRIEND_OFFLINE "add friend failed : user offline"
#define ADD_FRIEND_NOEXIST "add friend failed : user not exist"
#define ADD_FRIEND_SELF "add friend failed : add self as a friend"
#define ADD_FRIEND_SENT "add friend request has been sent"

#define DELETE_FRIEND_OK "delete friend ok"
#define DELETE_FRIEND_FAILED "delete friend failed"

#define SEND_MESSAGE_OK "send message ok"
#define SEND_MESSAGE_OFFLINE "send message failed: your friend is offline"
#define SEND_MESSAGE_NOFRIEND "send message failed: you are not friends"
#define SEND_MESSAGE_NOEXIST "send message failed: usr not exist"

#define CREATE_DIR_OK "create dir ok"
#define CREATE_DIR_PATH_NOEXIST "create dir failed: dir path not exist"
#define CREATE_DIR_FILE_EXISTED "create dir failed: file existed"

#define DELETE_DIRORFILE_OK "delete ok"
#define DELETE_DIRORFILE_FAILED "delete failed"

#define RENAME_DIRORFILE_OK "rename ok"
#define RENAME_DIRORFILE_FAILED "rename failed"

#define ENTER_DIR_OK "enter dir ok"
#define ENTER_DIR_FAILED "enter dir failed: enter a regular file"

#define UPLOAD_FILE_OK "upload file ok"
#define UPLOAD_FILE_FAILED "upload file failed"

#define SAVE_FILE_OK "save file ok"
#define SAVE_FILE_FAILED "save file failed"
#define SAVE_FILE_FAILED_EXISTED "save file failed: file existed"

#define MOVE_FILE_OK "move file ok"
#define MOVE_FILE_FAILED "move file failed"

enum ENUM_MSG_TYPE
{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUEST,   //注册请求1
    ENUM_MSG_TYPE_REGIST_RESPOND,   //注册回复2

    ENUM_MSG_TYPE_LOGIN_REQUEST,   //登录请求3
    ENUM_MSG_TYPE_LOGIN_RESPOND,   //登录回复4

    ENUM_MSG_TYPE_ALL_ONLINEUSR_REQUEST,   //在线用户请求5
    ENUM_MSG_TYPE_ALL_ONLINEUSR_RESPOND,   //在线用户回复6

    ENUM_MSG_TYPE_SEARCH_USR_REQUEST,   //搜索用户请求7
    ENUM_MSG_TYPE_SEARCH_USR_RESPOND,   //搜索用户回复8

    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST,   //添加好友请求9
    ENUM_MSG_TYPE_ADD_FRIEND_RESPOND,   //添加好友回复10

    ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND,   //同意添加好友回复11
    ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPOND_RESPOND,  //同意添加好友回复的回复12
    ENUM_MSG_TYPE_ADD_FRIEND_REFUSE_RESPOND,   //拒绝添加好友回复13

    ENUM_MSG_TYPE_REFRESH_FRIEND_REQUEST,   //刷新好友列表请求14
    ENUM_MSG_TYPE_REFRESH_FRIEND_RESPOND,   //刷新好友列表回复15

    ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST,   //删除好友请求16
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND,   //删除好友回复17

    ENUM_MSG_TYPE_SENDMSG_REQUEST,   //发送消息请求18
    ENUM_MSG_TYPE_SENDMSG_RESPOND,   //发送消息回复19

    ENUM_MSG_TYPE_MSGBOXCLICKED_RESPOND,   //消息提示框已确认回复20

    ENUM_MSG_TYPE_SENDPUBLICMSG_REQUEST,   //发送群聊消息请求21

    ENUM_MSG_TYPE_CREATE_DIR_REQUEST,   //创建文件夹请求22
    ENUM_MSG_TYPE_CREATE_DIR_RESPOND,   //创建文件夹回复23

    ENUM_MSG_TYPE_REFRESH_DIR_REQUEST,   //刷新文件夹请求24
    ENUM_MSG_TYPE_REFRESH_DIR_RESPOND,   //刷新文件夹回复25

    ENUM_MSG_TYPE_DELETE_DIRORFILE_REQUEST,   //删除文件夹或文件请求26
    ENUM_MSG_TYPE_DELETE_DIRORFILE_RESPOND,   //删除文件夹或文件回复27

    ENUM_MSG_TYPE_RENAME_DIRORFILE_REQUEST,   //重命名文件夹或文件请求28
    ENUM_MSG_TYPE_RENAME_DIRORFILE_RESPOND,   //重命名文件夹或文件回复29

    ENUM_MSG_TYPE_ENTER_DIR_REQUEST,   //重命名文件夹或文件请求30
    ENUM_MSG_TYPE_ENTER_DIR_RESPOND,   //重命名文件夹或文件回复31

    ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST,   //上传文件请求32
    ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST_RESPOND,  //上传文件请求回复33
    ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND,   //上传文件回复34

    ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST,   //下载文件请求35
    ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND,   //下载文件回复36

    ENUM_MSG_TYPE_SHARE_FILE_REQUEST,   //分享文件请求37

    ENUM_MSG_TYPE_REFRESH_SAVE_REQUEST,   //保存文件窗口刷新文件请求38
    ENUM_MSG_TYPE_REFRESH_SAVE_RESPOND,   //保存文件窗口刷新文件回复39

    ENUM_MSG_TYPE_ENTER_DIR_SAVE_REQUEST,   //保存文件窗口进入文件请求40
    ENUM_MSG_TYPE_ENTER_DIR_SAVE_RESPOND,   //保存文件窗口进入文件回复41

    ENUM_MSG_TYPE_CREATE_DIR_SAVE_REQUEST,  //保存文件窗口新建文件夹请求42
    ENUM_MSG_TYPE_CREATE_DIR_SAVE_RESPOND,  //保存文件窗口新建文件夹请求43

    ENUM_MSG_TYPE_SAVE_FILE_REQUEST,   //保存文件请求44
    ENUM_MSG_TYPE_SAVE_FILE_RESPOND,   //保存文件回复45

    ENUM_MSG_TYPE_MOVE_FILE_REQUEST,   //移动文件请求46
    ENUM_MSG_TYPE_MOVE_FILE_RESPOND,   //移动文件回复47

    ENUM_MSG_TYPE_MAX = 0x00ffffff,
};

struct FileRecv
{
    QFile file;           //接收时打开文件的对象
    qint64 totalSize = 0;    //文件总大小
    qint64 recvedSize = 0;   //已接收文件大小
    bool recvingFlag = false;    //文件接收状态标志
};

struct FileInfo
{
    char caFileNameUtf8[64];    //文件名字,设置为64和PDU保持一致,实际由于字节对齐为68,存放63个字符
    int iFileType;              //文件类型
    qint64 llFileSize;          //文件大小
};

struct PDU
{
    uint uiPDULen;      //总的协议数据单元大小
    uint uiMsgType;     //消息类型
    char caData[64];
    uint uiMsgLen;      //消息长度,比实际的大1
    char caMsg[];       //实际消息
};

std::shared_ptr<PDU> mk_shared_PDU(uint uiMsgLen);

void showPDUInfo(std::shared_ptr<PDU> pdu);

#endif // PROTOCOL_H
