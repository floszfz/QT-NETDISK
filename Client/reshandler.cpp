#include "reshandler.h"
#include "client.h"
#include "index.h"

#include <QMessageBox>
#include <string>


ResHandler::ResHandler()
{

}

void ResHandler::regist(PDU *pdu)
{
    //服务器->客户端  注册响应
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret){
        QMessageBox::information(&Client::getInstance(),"注册","注册成功");
    }else{
        QMessageBox::information(&Client::getInstance(),"注册","注册失败：用户名或密码错误");
    }
}

void ResHandler::login(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret){
        QMessageBox::information(&Client::getInstance(),"登录","登录成功");
        //登录后展示首页并隐藏登录界面
        Index::getInstance().show();
        Client::getInstance().hide();
    }else{
        QMessageBox::information(&Client::getInstance(),"登录","登录失败：用户名或密码错误");
    }
}

void ResHandler::findUser(PDU *pdu)
{
    char caName[32] = {'\0'};
    memcpy(caName,pdu->caData,32);
    int ret;
    memcpy(&ret,pdu->caData+32,sizeof(int));//pdu->caData记录的是查询的用户的状态
    if(ret == -1){
        QMessageBox::information(Index::getInstance().getFriend(),"搜索",QString("%1 不存在").arg(caName));
    }else if(ret == 0){
        QMessageBox::information(Index::getInstance().getFriend(),"搜索",QString("%1 不在线").arg(caName));
    }else{
        int ret = QMessageBox::information(
                    Index::getInstance().getFriend(),"搜索",QString("%1 在线").arg(caName),
                    "添加好友","取消");
        if(ret == 0){
            PDU* pdu = mkPDU(0);
            pdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_REQUEST;
            memcpy(pdu->caData,Client::getInstance().m_strLoginName.toStdString().c_str(),32);
            memcpy(pdu->caData+32,caName,32);
            Client::getInstance().sendPDU(pdu);
        }
    }
}

void ResHandler::onlineUser(PDU *pdu)
{
    uint uisize = pdu->uiMsgLen/32;//用户的数量
    char caTmp[32];//临时变量
    QStringList userList;
    for(uint i = 0;i < uisize;i++){
        memcpy(caTmp,pdu->caMsg+i*32,32);
        if(QString(caTmp) == Client::getInstance().m_strLoginName){
            continue;
        }
        userList.append(QString(caTmp));//将数据放在列表里
    }
    Index::getInstance().getFriend()->getOnlineUser()->showOnlineUser(userList);
}

void ResHandler::addFriend(PDU *pdu)
{
    int ret;
    memcpy(&ret,pdu->caData,sizeof(int));
    if(ret == -1){
        QMessageBox::information(Index::getInstance().getFriend(),"添加好友","添加错误");
    }else if(ret == -2){
        QMessageBox::information(Index::getInstance().getFriend(),"添加好友","对方已经是你的好友");
    }else if(ret == 0){
        QMessageBox::information(Index::getInstance().getFriend(),"添加好友","对方不在线");
    }
}

void ResHandler::addFriendRequest(PDU *pdu)
{
    char caName[32] = {'\0'};
    memcpy(caName, pdu->caData, 32);
    int ret = QMessageBox::question(
                Index::getInstance().getFriend(),
                "添加好友请求",
                QString("是否同意 %1 添加好友的请求？").arg(caName)
                );
    if(ret != QMessageBox::Yes){
        return;
    }
    PDU* respdu = mkPDU(0);
    respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE_REQUEST;
    memcpy(respdu->caData,pdu->caData,64);
    Client::getInstance().sendPDU(respdu);
}

void ResHandler::addFriendAgree(PDU *pdu)
{
    QMessageBox::information(Index::getInstance().getFriend(),"添加好友","添加成功");
    Index::getInstance().getFriend()->flushFriend();
}

void ResHandler::flushFriend(PDU *pdu)
{
    uint uisize = pdu->uiMsgLen/32;//用户的数量
    qDebug() << "在线好友数" << "flushFriend size" << uisize;
    char caTmp[32];//临时变量
    QStringList userList;
    for(uint i = 0;i < uisize;i++){
        memcpy(caTmp,pdu->caMsg+i*32,32);
        userList.append(QString(caTmp));//将数据放在列表里
    }
    Index::getInstance().getFriend()->showOnlineFriend(userList);
}
