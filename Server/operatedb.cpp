#include "operatedb.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

OperateDb::OperateDb(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
}

OperateDb &OperateDb::getInstance()
{
    static OperateDb instance;
    return instance;
}

void OperateDb::connect()
{
    m_db.setHostName("localhost");
    m_db.setDatabaseName("mydbwq");
    m_db.setPort(3306);
    m_db.setUserName("root");
    m_db.setPassword("123456");
    if(m_db.open()){
        qDebug()<<"数据库连接成功";
    }else{
        QMessageBox::critical(0,"链接数据库",m_db.lastError().text());
    }
}

OperateDb::~OperateDb()
{
    m_db.close();
}

bool OperateDb::handleRegist(char *name, char *pwd)
{
    qDebug()<<"handleRegist start name:" << name
           <<"pwd:" << pwd;
    if(name == NULL || pwd == NULL){
        qDebug()<<"handleRegist return false name == NULL || pwd == NULL";
        return false;
    }
    //检查添加的用户是否已经存在
    QString sql = QString("select * from user_info where name='%1'").arg(name);
    qDebug()<<"检查添加的用户是否已存在 sql:" << sql;
    QSqlQuery q;//查询语句的对象
    if (!q.exec(sql) || q.next()){
        //执行上述sql语句，找到了或者往下找找到都错
        return false;
    }
    //添加用户
    sql = QString("insert into user_info(name,pwd) values('%1','%2')").arg(name).arg(pwd);
    qDebug()<<"添加用户 sql:" << sql;
    return q.exec(sql);
}

bool OperateDb::handleLogin(char *name, char *pwd)
{
    qDebug()<<"handleLogin start name:" << name
           <<"pwd:" << pwd;
    if(name == NULL || pwd == NULL){
        qDebug()<<"handleLogin return false name == NULL || pwd == NULL";
        return false;
    }//判断传进来的用户名和密码是否为空
    QString sql = QString("select * from user_info where name='%1' and pwd='%2'").arg(name).arg(pwd);
    qDebug()<<"检查登录的用户名和密码是否正确 sql:" << sql;
    QSqlQuery q;//查询语句的对象
    if (!q.exec(sql) || !q.next()){
        return false;
    }
    sql = QString("update user_info set online=1 where name='%1' and pwd='%2'").arg(name).arg(pwd);
    qDebug()<<"用户切换为登录状态online=1 sql:" << sql;
    return q.exec(sql);
}

void OperateDb::handleOffline(const char *name)
{//处理下线
    if(name == NULL){
        qDebug() <<"handleOffline name is NULL";
        return;
    }
    QString sql = QString("update user_info set online=0 where name='%1'").arg(name);
    qDebug()<<"用户切换为下线状态online=0 sql:" << sql;
    QSqlQuery q;
    q.exec(sql);
}

int OperateDb::handleFindUser(const char *name)
{//查找用户
    if(name == NULL){
        qDebug() <<"handleFindUser name is NULL";
        return -1;
    }
    QString sql = QString("select online from user_info where name='%1'").arg(name);
    qDebug()<<"查找用户的online sql:" << sql;
    QSqlQuery q;
    q.exec(sql);//执行sql语句
    if(q.next()){//找到了
        return q.value(0).toInt();
    }
    qDebug()<<"用户不存在";
    return -1;
}

QStringList OperateDb::handleOnlineUser()
{
    QString sql = QString("select name from user_info where online=1");
    qDebug()<<"在线用户 sql:" << sql;
    QSqlQuery q;
    q.exec(sql);
    QStringList result;
    while(q.next()){
        result.append(q.value(0).toString());
    }
    return result;
}

int OperateDb::handleAddFriend(const char *curName, const char *tarName)
{
    //判断是否符合加好友函数
    if(curName == NULL || tarName == NULL){
        return -1;
    }
    QString sql = QString (R"(
                           select * from friend where
                            (
                                user_id=(select id from user_info where name = '%1')
                                and
                                friend_id=(select id from user_info where name = '%2')
                             )
                            or
                            (
                                friend_id=(select id from user_info where name = '%3')
                                and
                                user_id=(select id from user_info where name = '%4')
                            );
                           )").arg(curName).arg(tarName).arg(curName).arg(tarName);
    qDebug()<<"是否是好友sql："<<sql;
    QSqlQuery q;
    q.exec(sql);
    if(q.next()){
        return -2;//已经是好友了
    }
    sql = QString("select online from user_info where name='%1'").arg(tarName);
    q.exec(sql);
    if(q.next()){
        return q.value(0).toInt();//0不在线  1在线
    }
    return -1;
}

void OperateDb::handleAddFriendAgree(const char *curName, const char *tarName)
{
    if(curName == NULL || tarName == NULL){
        return;
    }
    QString sql = QString (R"(
                           insert into friend(user_id,friend_id)
                           select u1.id, u2.id from user_info u1,user_info u2
                           where u1.name='%1'and u2.name='%2';
                           )").arg(curName).arg(tarName);
    qDebug()<<"添加好友sql："<<sql;
    QSqlQuery q;
    q.exec(sql);
}

QStringList OperateDb::handleFlushFriend(const char *name)
{
    QStringList result;
    result.clear();
    if(name == NULL){
        return result;
    }
    QString sql = QString(R"(
                  select name from user_info
                    where online=1 and id in(
                        select user_id from friend where friend_id = (select id from user_info where name='%1')
                        union
                        select friend_id from friend where user_id = (select id from user_info where name='%1')
                  );
                  )").arg(name);
    qDebug()<<"handleFlushFriend sql:" << sql;
    QSqlQuery q;
    q.exec(sql);

    while(q.next()){
        result.append(q.value(0).toString());
    }
    return result;

}

