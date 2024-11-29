#ifndef OPERATEDB_H
#define OPERATEDB_H

#include <QObject>
#include <QSqlDatabase>

class OperateDb : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase m_db;//数据库对象
    static OperateDb &getInstance();
    void connect();
    ~OperateDb();
    bool handleRegist(char* name,char* pwd);
    bool handleLogin(char* name,char* pwd);
    void handleOffline(const char* name);
    int handleFindUser(const char* name);
    QStringList handleOnlineUser();
    int handleAddFriend(const char* curName,const char* tarName);
    void handleAddFriendAgree(const char* curName,const char* tarName);
    QStringList handleFlushFriend(const char *name);
private:
    explicit OperateDb(QObject *parent = nullptr);
    OperateDb(const OperateDb& instance) = delete;
    OperateDb& operator=(const OperateDb&) = delete;


signals:

};

#endif // OPERATEDB_H
