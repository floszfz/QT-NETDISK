#ifndef RESHANDLER_H
#define RESHANDLER_H

#include "protocol.h"


class ResHandler
{
public:
    ResHandler();
    void regist(PDU* pdu);//注册
    void login(PDU* pdu);//登录
    void findUser(PDU* pdu);
    void onlineUser(PDU* pdu);
    void addFriend(PDU* pdu);
    void addFriendRequest(PDU* pdu);
    void addFriendAgree(PDU* pdu);
    void flushFriend(PDU* pdu);
};

#endif // RESHANDLER_H
