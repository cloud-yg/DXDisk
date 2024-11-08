#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QList>
#include "mytcpsocket.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    static MyTcpServer& getInstance();

    QSet<MyTcpSocket*>& getTcpSocketSet();
    void incomingConnection(qintptr socketDescriptor);
    void transpond(QString name,std::shared_ptr<PDU> pdu);      //转发函数

public slots:
    void deleteSocket(MyTcpSocket *mysocket);   //删除下线的客户端的socket

private:
    QSet<MyTcpSocket*> m_tcpSocketSet;
};

#endif // MYTCPSERVER_H
