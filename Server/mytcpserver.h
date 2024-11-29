#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include "mytcpsocket.h"

//MyTcpServer重写的含义是服务器接收到的每个客户端的socket
//每一个MyTcpServer都是对应一个客户端

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    static MyTcpServer& getInstance();//单例对象静态函数
    void incomingConnection(qintptr handle);//参数表示接受到的客户端
    //当有客户端连接到服务器的时候自动调用该函数
    void resend(char* tarName,PDU* pdu);
public slots:
    void deleteSocket(MyTcpSocket* mysocket);
private:
    //单例模式
    MyTcpServer();
    MyTcpServer(const MyTcpServer& instance) = delete;
    MyTcpServer& operator=(const MyTcpServer&) = delete;

    QList<MyTcpSocket*> m_tcpSocketList;
    //定义属性m_tcpSocketList(套接字列表)，存放客户端的QTcpSocket(套接字)
};

#endif // MYTCPSERVER_H
