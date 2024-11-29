#include"protocol.h"
#include <stdlib.h>
#include <string.h>

PDU *mkPDU(uint uiMsgLen){
    //申请空间
    uint uiPDULen = sizeof(PDU) + uiMsgLen;
    //协议总长度 = PDU长度 + 消息长度
    PDU* pdu = (PDU*)malloc(uiPDULen);
    //用协议总长度申请空间
    if(pdu == NULL){
        exit(1);//为空退出
    }
    memset(pdu,0,uiPDULen);//清空内存
    pdu->uiPDULen = uiPDULen;
    pdu->uiMsgLen = uiMsgLen;
    return pdu;
}
