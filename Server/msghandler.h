#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include "protocol.h"

#include <QString>



class MsgHandler
{
public:
    MsgHandler();
    PDU* regist(PDU* pdu);
    PDU*login(PDU* pdu,QString& strloginName);
    PDU* findUser(PDU* pdu);
    PDU* onlineUser();
    PDU* addFriend(PDU* pdu);
    PDU* addFriendAgree(PDU* pdu);
    PDU* flushFriend(PDU* pdu);
};

#endif // MSGHANDLER_H
