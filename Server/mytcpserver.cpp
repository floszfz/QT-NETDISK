#include "mytcpserver.h"

MyTcpServer::MyTcpServer()
{

}

MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;
}

void MyTcpServer::incomingConnection(qintptr handle)
{
    qDebug()<<"新客户端链接";
    MyTcpSocket *pTcpSocket = new MyTcpSocket;
    //弄新的套接字也就是新的客户端发出信号的装置

    pTcpSocket->setSocketDescriptor(handle);//参数是接收到的客户端
    m_tcpSocketList.append(pTcpSocket);//客户端连接到服务器的列表

    foreach(MyTcpSocket *pTcpSocket,m_tcpSocketList){
        qDebug()<<"客户端连接情况："<<pTcpSocket;
        //测试，查看所有客户端的连接情况
    }
    connect(pTcpSocket,&MyTcpSocket::offline,this,&MyTcpServer::deleteSocket);
    //服务器上每一个链接的客户端都可以发出关闭的信号
}

void MyTcpServer::resend(char *tarName, PDU *pdu)
{
    //转发函数
    if(tarName == NULL || pdu == NULL){
        return;
    }
    for(int i = 0;i < m_tcpSocketList.size();i++){
        if(tarName == m_tcpSocketList.at(i)->m_strLoginName){
            m_tcpSocketList.at(i)->write((char*)pdu,pdu->uiPDULen);
            break;
        }
    }
}

void MyTcpServer::deleteSocket(MyTcpSocket *mysocket)
{
    m_tcpSocketList.removeOne(mysocket);
    mysocket->deleteLater();
    mysocket = NULL;
    //测试是否移除成功
    qDebug()<<"当前有 "<<m_tcpSocketList.size()<<" 个用户处于登录状态";
    for(int i = 0;i<m_tcpSocketList.size();i++){
        qDebug()<<m_tcpSocketList.at(i)->m_strLoginName;
    }
}
