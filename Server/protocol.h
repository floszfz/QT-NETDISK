#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef unsigned int uint;//起别名（无符号int类型）


enum ENUM_MSG_TYPE//消息的类型
{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUEST,//注册的请求  客->服
    ENUM_MSG_TYPE_REGIST_RESPEND,//注册的响应  服->客

    ENUM_MSG_TYPE_LOGIN_REQUEST,//登录的请求  客->服
    ENUM_MSG_TYPE_LOGIN_RESPEND,//登录的响应  服->客

    ENUM_MSG_TYPE_FIND_USER_REQUEST,//查找用户的请求  客->服
    ENUM_MSG_TYPE_FIND_USER_RESPEND,//查找用户的响应  服->客

    ENUM_MSG_TYPE_ONLINE_USER_REQUEST,//在线用户的请求  客->服
    ENUM_MSG_TYPE_ONLINE_USER_RESPEND,//在线用户的响应  服->客

    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST,//添加好友的请求  客->服
    ENUM_MSG_TYPE_ADD_FRIEND_RESPEND,//添加好友的响应  服->客

    ENUM_MSG_TYPE_ADD_FRIEND_AGREE_REQUEST,//同意添加好友的请求  客->服
    ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPEND,//同意添加好友的响应  服->客

    ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST,//刷新好友的请求  客->服
    ENUM_MSG_TYPE_FLUSH_FRIEND_RESPEND,//刷新好友的响应  服->客

    ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST,//删除好友的请求  客->服
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPEND,//删除好友的响应  服->客

    ENUM_MSG_TYPE_MAX = 0x00ffffff,
};

struct PDU{//协议数据单元结构体
    uint uiPDULen;//协议总长度
    uint uiMsgLen;//实际消息长度
    uint uiMsgType;//消息类型
    char caData[64];//参数
    char caMsg[];//实际消息
};

PDU* mkPDU(uint uiMsgLen);//创建协议数据单元

#endif // PROTOCOL_H
