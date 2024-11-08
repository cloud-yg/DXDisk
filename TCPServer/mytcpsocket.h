#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include "protocol.h"
#include "opedb.h"
#include <QDir>
#include <QFile>

//每一个与服务端建立socket的客户端都定义自己的socket
class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    std::shared_ptr<PDU> refreshDirPDU(QString pCurPath);    //根据路径生成刷新文件夹信息的PDU
    void handleRqsPDU(std::shared_ptr<PDU> pdu);    //处理请求函数
    QString getName();  //获取socketName
    //拷贝文件夹的函数
    bool copyDir(QString srcDir, QString destDir);

signals:
    void offline(MyTcpSocket *mysocket);     //客户端下线信号

public slots:
    void recvMsg();
    void clientOffline();   //处理客户端下线函数

private:
    QString socketName;     //存放登录的用户名
    FileRecv fileRecv;
    QString m_curPath;      //当前上传文件的文件夹路径
};

#endif // MYTCPSOCKET_H
