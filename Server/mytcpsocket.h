#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include "protocol.h"
#include "msghandler.h"

#include <QTcpSocket>


class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MyTcpSocket();
    ~MyTcpSocket();

    QString m_strLoginName;//登录的用户名
    PDU* readPDU();
    PDU* handleMsg(PDU* pdu);
    void sendPDU(PDU* pdu);
    MsgHandler* m_pmh;
public slots:
    void recvMsg();//接收并处理客户端发来的消息
    void clientOffline();//客户端下线

signals:
    //定义信号
    void offline(MyTcpSocket* mysocket);
};

#endif // MYTCPSOCKET_H
