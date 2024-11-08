#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include "protocol.h"
#include "opewidget.h"
#include <QTimer>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class TCPClient;
}
QT_END_NAMESPACE

class TCPClient : public QWidget
{
    Q_OBJECT

public:
    TCPClient(QWidget *parent = nullptr);
    ~TCPClient();
    void loadConfig();
    static TCPClient &getInstance();
    QTcpSocket &getTCPSocket();
    QString getLoginName();
    QString getCurPath();
    void setCurPath(QString curPath);
    QString getRootPath();
    void setCurPathTemp(QString curPathTemp);
    void handleRpdPDU(std::shared_ptr<PDU> pdu);    //处理回复函数
    void setFileRecv();
    FileRecv& getFileRecv();
    void startElapsedTimer();       //开始计时,测量传输速度

public slots:
    void showConnect();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    void recvMsg();

public slots:
    void on_connect_pb_clicked();

private slots:

    void on_login_pb_clicked();
    void on_regist_pb_clicked();

private:
    Ui::TCPClient *ui;
    QString m_strIP;    //存放IP
    quint16 m_usPort;   //存放端口

    //连接服务器，和服务器数据交互
    QTcpSocket m_tcpSocket;

    bool isConnected = false;       //客户端与服务器连接状态

    QString m_loginName;    //当前登录用户的用户名
    QString m_curPath;      //当前路径
    QString m_curPathTemp;  //缓存路径
    QString m_rootPath;     //根路径

    FileRecv fileRecv;

    QElapsedTimer *m_elapsedTimer;
    qint64 firstTime = 0;
    qint64 secondTime = 0;
};
#endif // TCPCLIENT_H
