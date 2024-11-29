#include "msghandler.h"
#include "operatedb.h"
#include "mytcpserver.h"

#include <QDebug>

MsgHandler::MsgHandler()
{

}

PDU *MsgHandler::regist(PDU *pdu)
{
    qDebug()<<"case ENUM_MSG_TYPE_REGIST_REQUEST";
    //处理注册
    char caName[32] = {'\0'};
    char caPwd[32] = {'\0'};
    memcpy(caName,pdu->caData,32);//用户名信息拷贝到caName变量中
    memcpy(caPwd,pdu->caData+32,32);
    bool ret = OperateDb::getInstance().handleRegist(caName,caPwd);
    qDebug()<<"ret:"<<ret;
    //执行数据库单例对象的添加用户函数，返回成功或失败
    PDU* respdu = mkPDU(0);//返回的pdu构建
    respdu->uiMsgType = ENUM_MSG_TYPE_REGIST_RESPEND;//响应
    memcpy(respdu->caData,&ret,sizeof(bool));//结果放在返回的pdu中
    return respdu;
}

PDU *MsgHandler::login(PDU *pdu, QString &strloginName)
{
    qDebug()<<"case ENUM_MSG_TYPE_LOGIN_REQUEST";
    //处理登录
    char caName[32] = {'\0'};
    char caPwd[32] = {'\0'};
    memcpy(caName,pdu->caData,32);//用户名信息拷贝到caName变量中
    memcpy(caPwd,pdu->caData+32,32);
    //数据库处理登录
    bool ret = OperateDb::getInstance().handleLogin(caName,caPwd);
    strloginName = caName;
    qDebug()<<"用户:"<<strloginName;
    qDebug()<<"ret:"<<ret;
    //执行数据库单例对象的添加用户函数，返回成功或失败
    PDU* respdu = mkPDU(0);//返回的pdu构建
    respdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_RESPEND;//响应
    memcpy(respdu->caData,&ret,sizeof(bool));//结果放在返回的pdu中
    return respdu;
}

PDU *MsgHandler::findUser(PDU *pdu)
{
    qDebug()<<"case ENUM_MSG_TYPE_FIND_USER_REQUEST";
    //查找用户
    char caName[32] = {'\0'};
    memcpy(caName,pdu->caData,32);//用户名信息拷贝到caName变量中
    //数据库处理用户查找
    int ret = OperateDb::getInstance().handleFindUser(caName);
    qDebug()<<"ret:"<<ret;
    //执行数据库单例对象的添加用户函数，返回成功或失败
    PDU* respdu = mkPDU(0);//返回的pdu构建
    respdu->uiMsgType = ENUM_MSG_TYPE_FIND_USER_RESPEND;//响应
    memcpy(respdu->caData,caName,32);//用户名放在respdu中
    memcpy(respdu->caData+32,&ret,sizeof(int));//查询的用户状态放在caData+32位置
    return respdu;
}

PDU *MsgHandler::onlineUser()
{
    qDebug()<<"case ENUM_MSG_TYPE_ONLINE_USER_REQUEST";
    //处理在线用户
    //数据库处理用户查找
    QStringList ret = OperateDb::getInstance().handleOnlineUser();
    qDebug()<<"ret:"<<ret;
    //执行数据库单例对象的添加用户函数，返回成功或失败
    PDU* respdu = mkPDU(ret.size()*32);//caMsg总长度
    respdu->uiMsgType = ENUM_MSG_TYPE_ONLINE_USER_RESPEND;//响应

    for(int i = 0;i<ret.size();i++){
        qDebug()<<"ret.at(i)"<<ret.at(i);
        memcpy(respdu->caMsg + i*32,ret.at(i).toStdString().c_str(),32);
    }
    return respdu;
}

PDU *MsgHandler::addFriend(PDU *pdu)
{
    qDebug()<<"case ENUM_MSG_TYPE_ADD_FRIEND_RESPEND";
    //读取pdu中的当前用户和目标用户
    char caCurName[32] = {'\0'};
    char caTarName[32] = {'\0'};
    memcpy(caCurName,pdu->caData,32);//用户名信息拷贝到caName变量中
    memcpy(caTarName,pdu->caData+32,32);

    int ret = OperateDb::getInstance().handleAddFriend(caCurName,caTarName);
    qDebug()<<"ret:"<<ret;
    if(ret == 1){
        MyTcpServer::getInstance().resend(caTarName,pdu);
    }
    PDU* respdu = mkPDU(0);
    respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_RESPEND;//响应
    memcpy(respdu->caData,&ret,sizeof(int));
    return respdu;
}

PDU *MsgHandler::addFriendAgree(PDU *pdu)
{
    qDebug()<<"case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPEND";
    //读取pdu中的当前用户和目标用户
    char caCurName[32] = {'\0'};
    char caTarName[32] = {'\0'};
    memcpy(caCurName,pdu->caData,32);//用户名信息拷贝到caName变量中
    memcpy(caTarName,pdu->caData+32,32);
    OperateDb::getInstance().handleAddFriendAgree(caCurName,caTarName);
    PDU* respdu = mkPDU(0);
    respdu->uiMsgType = ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPEND;//响应
    MyTcpServer::getInstance().resend(caCurName,respdu);
    return respdu;
}

PDU *MsgHandler::flushFriend(PDU *pdu)
{
    qDebug()<<"case ENUM_MSG_TYPE_FLUSH_FRIEND_RESPEND";
    char caCurName[32] = {'\0'};
    memcpy(caCurName,pdu->caData,32);
    QStringList ret = OperateDb::getInstance().handleFlushFriend(caCurName);
    qDebug()<<"ret:"<<ret;
    //执行数据库单例对象的添加用户函数，返回成功或失败
    PDU* respdu = mkPDU(ret.size()*32);//caMsg总长度
    respdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_RESPEND;//响应
    for(int i = 0;i<ret.size();i++){
        qDebug()<<"ret.at(i)"<<ret.at(i);
        memcpy(respdu->caMsg + i*32,ret.at(i).toStdString().c_str(),32);
    }
    return respdu;
}
