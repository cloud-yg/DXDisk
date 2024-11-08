#include "opedb.h"
#include <QMessageBox>
#include <QDebug>

OpeDB::OpeDB(QObject *parent)
    : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

OpeDB &OpeDB::getInstance()
{
    static OpeDB instance;
    return instance;
}

void OpeDB::init()
{
    m_db.setHostName("localhost");
    m_db.setDatabaseName("C:\\QT\\Project\\DXDisk\\TCPServer\\cloud.db");
    if(m_db.open())
    {
        qDebug() << "(OpeDB::init)数据库打开成功";
        // QSqlQuery query;
        // query.exec("select * from usrInfo");
        // while(query.next())
        // {
        //     QString data = QString("%1,%2,%3,%4").arg(query.value(0).toString())
        //                        .arg(query.value(1).toString()).arg(query.value(2).toString())
        //                        .arg(query.value(3).toString());
        //     qDebug() << data;
        // }
    }
    else
    {
        QMessageBox::critical(NULL,"打开数据库","打开数据库失败");
    }
}

OpeDB::~OpeDB()
{
    m_db.close();
}

//处理注册，成功则将信息添加到数据库中
bool OpeDB::handleRegist(const char *name, const char *pwd)
{
    if(name == NULL || pwd == NULL)return false;
    QString command = QString("insert into usrInfo(name,pwd) values(\'%1\',\'%2\')")
                        .arg(name).arg(pwd);
    qDebug() << command;
    QSqlQuery query;
    return query.exec(command);
}

uint OpeDB::handleLogin(const char *name, const char *pwd)
{
    if(name == NULL || pwd == NULL)return false;
    QString command = QString("select * from usrInfo where name=\'%1\'").arg(name);
    qDebug() << command;
    QSqlQuery query;
    query.exec(command);
    if(!query.next())return 1;     //用户名不存在，用户未注册
    else if(query.value(2) != pwd)return 2;    //密码错误
    else if(query.value(3) == 1) return 3;     //用户已在线，不能重复登录
    else
    {
        //登录成功,并将状态online置为在线状态1
        command = QString("update usrInfo set online=1 where name='%1' and pwd='%2'")
                      .arg(name).arg(pwd);
        qDebug() << command;
        query.exec(command);
        return 0;
    }
}

void OpeDB::handeleOffline(const char *name)
{
    if(name == NULL)return;
    QString command = QString("update usrInfo set online=0 where name='%1'").arg(name);
    QSqlQuery query;
    query.exec(command);
}

QStringList OpeDB::handeleAllOnlineUsr()
{
    //获取在线用户列表命令
    QString command = QString("select name from usrInfo where online=1");
    QSqlQuery query;
    query.exec(command);

    QStringList OnlineUsr;
    OnlineUsr.clear();

    while(query.next())
    {
        OnlineUsr.append(query.value(0).toString().toUtf8());
    }
    return OnlineUsr;
}

QMap<QString,QString> OpeDB::handleSearchUsr(const char *searchUsrName_pre)
{
    QMap<QString,QString> SearchResultMap;
    SearchResultMap.clear();

    if(searchUsrName_pre == NULL)return SearchResultMap; //搜索用户名为空
    QString command = QString("select * from usrInfo where name like '%1%'")
                          .arg(searchUsrName_pre);
    QSqlQuery query;
    query.exec(command);
    while(query.next())
    {
        SearchResultMap.insert(query.value(1).toString().toUtf8(),query.value(3).toString());
    }
    return SearchResultMap;
}

//perUsrName:被询问者、被请求者、被回复者 myName:询问者、请求者、回复者
int OpeDB::queryUsrState(const char *perUsrName, const char *myName)
{
    if(perUsrName == NULL || myName == NULL)return -5;  //-5:故障情况
    if(strcmp(perUsrName,myName) == 0)return -4;  //-4:对方是自己
    QString queryFriCommand = QString("select * from friendInfo where "
                                      "(name='%1' and fname='%2') "
                                      "or (name='%2' and fname='%1')")
                                  .arg(perUsrName).arg(myName);
    QString queryStaCommand = QString("select online from usrInfo where name='%1'")
                                  .arg(perUsrName);
    QSqlQuery queryFriResult;
    QSqlQuery queryStaResult;
    queryFriResult.exec(queryFriCommand);
    queryStaResult.exec(queryStaCommand);
    //双方不是好友: -3:账号已注销,对方不存在 -2:对方不在线 -1:对方在线
    if(!queryFriResult.next())
    {
        if(queryStaResult.next())
            return queryStaResult.value(0).toInt()-2;
        else return -3;
    }
    //双方是好友: 0:对方不在线 1:对方在线
    else
    {
        if(queryStaResult.next())
            return queryStaResult.value(0).toInt();
        else return -5;
    }
}

bool OpeDB::handleAddFriend(const char *perUsrName, const char *myName)
{
    if(perUsrName == NULL || myName == NULL)return false;
    QString command = QString("insert into friendInfo(name,fname) values('%1','%2')")
                          .arg(perUsrName).arg(myName);
    QSqlQuery query;
    return query.exec(command);
}

QMap<QString,QString> OpeDB::handleRefFriend(const char *name)
{
    QMap<QString,QString> friendMap;
    if(name == NULL)return friendMap;
    //commandFriName 为查找好友名字列表指令
    QString commandFriName = QString("select name from friendInfo where fname='%1'").arg(name);
    QString commandFriInfo;     //查看指定好友的在线状态
    QSqlQuery queryFriName;
    QSqlQuery queryFriInfo;
    queryFriName.exec(commandFriName);
    while(queryFriName.next())
    {
        commandFriInfo = QString("select online from usrInfo where name='%1'")
                             .arg(queryFriName.value(0).toString().toUtf8());
        queryFriInfo.exec(commandFriInfo);
        if(queryFriInfo.next())
            friendMap.insert(queryFriName.value(0).toString().toUtf8(),
                            queryFriInfo.value(0).toString());
    }
    commandFriName = QString("select fname from friendInfo where name='%1'").arg(name);
    queryFriName.exec(commandFriName);
    while(queryFriName.next())
    {
        commandFriInfo = QString("select online from usrInfo where name='%1'")
                             .arg(queryFriName.value(0).toString().toUtf8());
        queryFriInfo.exec(commandFriInfo);
        if(queryFriInfo.next())
            friendMap.insert(queryFriName.value(0).toString().toUtf8(),
                            queryFriInfo.value(0).toString());
    }
    // qDebug() << "Debug friendMap: " << friendMap;
    return friendMap;
}

bool OpeDB::handleDelFriend(const char *perUsrName, const char *myName)
{
    if(perUsrName == NULL || myName == NULL)return false;
    QString command1 = QString("delete from friendInfo where name='%1' and fname='%2'")
                          .arg(perUsrName).arg(myName);
    QString command2 = QString("delete from friendInfo where fname='%1' and name='%2'")
                           .arg(perUsrName).arg(myName);
    QSqlQuery query;
    query.exec(command1);
    query.exec(command2);
    return query.exec(command1) || query.exec(command2);
}
