#include "client.h"
#include "friend.h"
#include "protocol.h"
#include "ui_friend.h"


#include <QInputDialog>
#include <QDebug>

Friend::Friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Friend)
{
    ui->setupUi(this);
    m_pOnlineUser = new OnlineUser;
    flushFriend();
}

Friend::~Friend()
{
    delete ui;
}

OnlineUser *Friend::getOnlineUser()
{
    return m_pOnlineUser;
}

void Friend::showOnlineFriend(QStringList friendList)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(friendList);
}

void Friend::flushFriend()
{
    QString strName = Client::getInstance().m_strLoginName;
    //获取当前用户
    PDU* pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST;
    memcpy(pdu->caData,strName.toStdString().c_str(),32);
    Client::getInstance().sendPDU(pdu);
    //把当前客户端名字放PDU里，然后发出去
}

void Friend::on_findFriend_PB_clicked()
{
    //点击查找用户，弹出搜索框
    QString strName = QInputDialog::getText(this,"搜索","用户名:");
    //搜索框里写用户名
    qDebug()<<"on_findFriend_PB_clicked strName:"<<strName;
    if (strName.isEmpty()){
        return;
    }
    PDU* pdu = mkPDU(0);//弄个协议结构体类型的对象
    pdu->uiMsgType = ENUM_MSG_TYPE_FIND_USER_REQUEST;
    memcpy(pdu->caData,strName.toStdString().c_str(),strName.size());
    //将搜索框中的用户名放在caData中
    Client::getInstance().sendPDU(pdu);
}

void Friend::on_online_PB_clicked()
{
    if(m_pOnlineUser->isHidden()){
        m_pOnlineUser->show();
    }
    PDU* pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_ONLINE_USER_REQUEST;
    Client::getInstance().sendPDU(pdu);
}

void Friend::on_flushFriend_PB_clicked()
{
    flushFriend();
}

void Friend::on_delFriend_PB_clicked()
{
    QListWidgetItem* pItem = ui->listWidget->currentItem();   //消息界面的单选框就是返回当前项
    if(!pItem){
        QMessageBox::information(this,"删除好友","请选择要删除的好友");
        return;
    }
    QString strTarName = pItem->text();
    int ret = QMessageBox::question(this,"删除好友",QString("是否确认删除好友 %1").arg(strTarName));
    if(ret != QMessageBox::Yes){
        return;
    }
    PDU* pdu = mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST;
    QString strCurName = Client::getInstance().m_strLoginName;
    memcpy(pdu->caData,strCurName.toStdString().c_str(),32);
    memcpy(pdu->caData+32,strTarName.toStdString().c_str(),32);
    Client::getInstance().sendPDU(pdu);
}
