#include "mytcpsocket.h"
#include "operatedb.h"
#include "protocol.h"


MyTcpSocket::MyTcpSocket()
{
    connect(this,&QTcpSocket::readyRead,this,&MyTcpSocket::recvMsg);
    connect(this,&QTcpSocket::disconnected,this,&MyTcpSocket::clientOffline);
    m_pmh = new MsgHandler;//需要释放（析构函数）
}

MyTcpSocket::~MyTcpSocket()
{
    delete m_pmh;
}

void MyTcpSocket::recvMsg()
{//接受消息函数
    PDU* pdu = readPDU();
    PDU* respdu = handleMsg(pdu);
    sendPDU(respdu);
    free(pdu);
    pdu = NULL;
}

void MyTcpSocket::clientOffline()
{
    OperateDb::getInstance().handleOffline(m_strLoginName.toStdString().c_str());
    emit offline(this);//移除
}

PDU *MyTcpSocket::readPDU()
{
    qDebug()<<"readPDU 接收消息长度：" << this->bytesAvailable();
    uint uiPDULen = 0;
    this->read((char*)&uiPDULen,sizeof(uint));//读的是协议长度

    uint uiMsgLen = uiPDULen - sizeof(PDU);
    //消息长度 = 协议总长度 - 协议长度（数据头长）
    PDU* pdu = mkPDU(uiMsgLen);

    this->read((char*)pdu + sizeof(uint),uiPDULen - sizeof(uint));
    //第一个参数是从哪里读，第二个参数是读多少
    //读取协议长度以外的数据
    qDebug()<<"readPDU 消息类型："<<pdu->uiMsgType
            <<" 消息内容：" << pdu->caMsg
            <<" 参数1：" << pdu->caData
            <<" 参数2：" << pdu->caData+32;
    return pdu;
}

PDU *MyTcpSocket::handleMsg(PDU *pdu)
{
    //根据消息类型进行处理
    switch(pdu->uiMsgType){
    case ENUM_MSG_TYPE_REGIST_REQUEST:
        return m_pmh->regist(pdu);
    case ENUM_MSG_TYPE_LOGIN_REQUEST:
        return m_pmh->login(pdu,m_strLoginName);
    case ENUM_MSG_TYPE_FIND_USER_REQUEST:
        return m_pmh->findUser(pdu);
    case ENUM_MSG_TYPE_ONLINE_USER_REQUEST:
        return m_pmh->onlineUser();
    case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:
        return m_pmh->addFriend(pdu);
    case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_REQUEST:
        return m_pmh->addFriendAgree(pdu);
    case ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST:
        return m_pmh->flushFriend(pdu);
    default:
        break;
    }
    return NULL;
}

void MyTcpSocket::sendPDU(PDU *pdu)
{
    if(pdu == NULL){
        return;
    }
    write((char*)pdu,pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}
