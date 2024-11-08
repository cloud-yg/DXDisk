#include "mytcpserver.h"
#include <QDebug>

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{}

MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;
}

QSet<MyTcpSocket *> &MyTcpServer::getTcpSocketSet()
{
    return m_tcpSocketSet;
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "(MyTcpServer::incomingConnection)new client connected";
    MyTcpSocket *pTcpSocket = new MyTcpSocket;
    pTcpSocket->setSocketDescriptor(socketDescriptor);
    m_tcpSocketSet.insert(pTcpSocket);

    //将客户端下线信号与信号槽连接
    connect(pTcpSocket,SIGNAL(offline(MyTcpSocket*)),
            this,SLOT(deleteSocket(MyTcpSocket*)));
}

void MyTcpServer::transpond(QString name,std::shared_ptr<PDU> pdu)
{
    if(name.isEmpty())return;     //判断非法
    //找到名字为perUsrName的客户端，将信息PDU转发给该客户端
    for(auto iter = m_tcpSocketSet.cbegin(); iter !=m_tcpSocketSet.cend(); ++iter)
    {
        if((*iter)->getName() == name)
        {
            (*iter)->write((char*)pdu.get(),pdu->uiPDULen);
            break;
        }
    }
}

//删除下线客户端的socket
void MyTcpServer::deleteSocket(MyTcpSocket *mysocket)
{
    //查找socket指针集合中mysocket，返回指向它的迭代器
    QSet<MyTcpSocket*>::iterator iter = m_tcpSocketSet.find(mysocket);
    if(iter != m_tcpSocketSet.end())
    {
        (*iter)->deleteLater();   //释放*iter指向的对象，即客户端socket
        const_cast<MyTcpSocket*&>(*iter) = nullptr; //将指向已释放的客户端socket的指针置为空
        m_tcpSocketSet.erase(iter);     //删除socket指针集合中该指针
    }
    //for(auto a:m_tcpSocketSet)qDebug() << a->getName();   //打印当前在线的客户端
}

