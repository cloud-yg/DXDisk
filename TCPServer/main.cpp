#include "tcpserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OpeDB::getInstance().init();

    TCPServer w;
    w.show();

    QObject::connect(&a, &QCoreApplication::aboutToQuit,
                     &w, &TCPServer::disconnectAllClients);

    return a.exec();
}
