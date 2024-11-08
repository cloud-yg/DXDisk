#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>
#include <QFile>

TCPServer::TCPServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCPServer)
{
    ui->setupUi(this);

    loadConfig();
    MyTcpServer::getInstance().listen(QHostAddress::Any,m_usPort);  //监听
}

TCPServer::~TCPServer()
{
    delete ui;
}

void TCPServer::loadConfig()
{
    QFile file(":/server.config");  //打开资源文件
    if(file.open(QIODeviceBase::ReadOnly))
    {
        QByteArray baData = file.readAll();
        QString strData=baData.toStdString().c_str();
        file.close();

        QStringList strList = strData.split("\r\n");

        m_strIP = strList[0];
        m_usPort = strList[1].toUShort();
        qDebug() << "(TCPServer::loadConfig)服务器配置成功:" << "ip:" << m_strIP << " " << "port:" << m_usPort;
    }
    else
    {
        QMessageBox::critical(this,"open config","open config failed");
    }
}

void TCPServer::disconnectAllClients()
{
    qDebug() << "Disconnecting all clients...";

    for (QTcpSocket *socket : MyTcpServer::getInstance().getTcpSocketSet())
    {
        socket->disconnectFromHost();
    }

    MyTcpServer::getInstance().getTcpSocketSet().clear();

    // 关闭服务器以停止监听新连接
    close();
}
