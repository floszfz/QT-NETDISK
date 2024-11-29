#include "client.h"
#include "ui_client.h"
#include "protocol.h"
#include "index.h"

#include <QHostAddress>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

Client::Client(QWidget *parent): QWidget(parent), ui(new Ui::Client)
{
    ui->setupUi(this);
    m_prh = new ResHandler;
    loadConfig();
    connect(&m_tcpSocket,&QTcpSocket::connected,this,&Client::showConnect);
    connect(&m_tcpSocket,&QTcpSocket::readyRead,this,&Client::recvMsg);

    qDebug()<< "ip:" << m_strIP << "port:" << m_usPort;
    m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);//连接服务器
}

Client::~Client()
{
    delete m_prh;
    delete ui;
}

void Client::loadConfig()//配置
{
    QFile file(":/client.config");//读配置文件
    if(file.open(QIODevice::ReadOnly)){//以只读的方式打开文件
        QByteArray baData = file.readAll();//读取文件数据
        QString strData = QString(baData);//字符串展现数据
        QStringList strList = strData.split("\r\n");//将两个字段按照\r\n分割
        m_strIP = strList.at(0);//地址
        m_usPort = strList.at(1).toUShort();//端口号、强转成字符串类型
        qDebug()<<"ip:"<<m_strIP<<"port:"<<m_usPort;//打印
        file.close();
    }else{
        QMessageBox::critical(this,"打开配置","打开配置失败");
        //弹窗弹出警告
    }
}

Client &Client::getInstance()
{
    static Client instance;
    return instance;//生成一个静态对象，返回就行
}

void Client::recvMsg()
{
    PDU* pdu = readPDU();
    handleMsg(pdu);//根据消息类型进行处理
}

QTcpSocket& Client::getTcpSocket()
{
    return m_tcpSocket;
}

PDU *Client::readPDU()
{
    //读的是协议长度
    qDebug()<<"readPDU 接收消息长度：" << m_tcpSocket.bytesAvailable();
    uint uiPDULen = 0;
    m_tcpSocket.read((char*)&uiPDULen,sizeof(uint));
    //读协议长度以外的数据
    uint uiMsgLen = uiPDULen - sizeof(PDU);
    PDU* pdu = mkPDU(uiMsgLen);
    m_tcpSocket.read((char*)pdu + sizeof(uint),uiPDULen - sizeof(uint));
    //第一个参数是从哪里读，第二个参数是读多少
    qDebug()<<"readPDU 消息类型："<<pdu->uiMsgType
            <<" 消息内容：" << pdu->caMsg
            <<" 参数1：" << pdu->caData
            <<" 参数2：" << pdu->caData+32;
    return pdu;
}

void Client::handleMsg(PDU *pdu)
{
    //根据消息类型进行处理
    switch(pdu->uiMsgType){
    case ENUM_MSG_TYPE_REGIST_RESPEND:{
        m_prh->regist(pdu);
        break;
    }
    case ENUM_MSG_TYPE_LOGIN_RESPEND:{
        m_prh->login(pdu);
        break;
    }
    case ENUM_MSG_TYPE_FIND_USER_RESPEND:{
        m_prh->findUser(pdu);
        break;
    }
    case ENUM_MSG_TYPE_ONLINE_USER_RESPEND:{
        m_prh->onlineUser(pdu);
        break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_RESPEND:{
        m_prh->addFriend(pdu);
        break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_REQUEST:{
        m_prh->addFriendRequest(pdu);
        break;
    }
    case ENUM_MSG_TYPE_ADD_FRIEND_AGREE_RESPEND:{
        m_prh->addFriendAgree(pdu);
        break;
    }
    case ENUM_MSG_TYPE_FLUSH_FRIEND_RESPEND:{
        m_prh->flushFriend(pdu);
        break;
    }
    default:
        break;
    }
    free(pdu);
    pdu = NULL;
}

void Client::sendPDU(PDU *pdu)
{
    qDebug()<<"sendPDU pdu->caData"<<pdu->caData
           <<"pdu->caData+32"<<pdu->caData + 32
          <<"pdu->uiMsgType"<<pdu->uiMsgType
         <<"pdu->caMsg"<<pdu->caMsg;
    m_tcpSocket.write((char*)pdu,pdu->uiPDULen);//发给服务器
    free(pdu);
    pdu = NULL;
}
void Client::showConnect()
{
    qDebug()<<"连接服务器成功！";
}


//void Client::on_pushButton_clicked()
//{
//    //点击发送按钮，将消息发送给服务器
//    QString strMsg = ui->input_LE->text();
//    qDebug() << "发送 on_pushButton_clicked strMsg:" << strMsg;
//    //日志：是否能运行到这一步
//    if(strMsg.isEmpty()){
//        QMessageBox::warning(this,"发送消息","发送消息不能为空");
//        return;
//    }
//    PDU* pdu = mkPDU(strMsg.size());
//    memcpy(pdu->caMsg,strMsg.toStdString().c_str(),strMsg.size());
//    pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;
//    m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
//    free(pdu);
//    pdu = NULL;
//}



void Client::on_regist_PB_clicked()
{//注册按钮的槽函数
    qDebug()<<"on_regist_PB_clicked start";
    //获取输入框中的姓名和密码
    QString strName = ui->username_LE->text();
    QString strPwd = ui->password_PB->text();
    qDebug() << "strName:" << strName
             << "strPwd:" << strPwd;
    //是否获取成功
    if(strName.isEmpty() || strPwd.isEmpty() ||
            strName.size() > 32 || strPwd.size() > 32){
        QMessageBox::critical(this,"注册","用户名或密码错误");
        //父组件，标题，提示
        return;
    }
    //构建pdu，用户名和密码放入caData(参数)
    PDU* pdu = mkPDU(0);//柔性数组的长度
    pdu->uiMsgType = ENUM_MSG_TYPE_REGIST_REQUEST;//给服务器的请求
    memcpy(pdu->caData,strName.toStdString().c_str(),32);//将用户名复制到caData中
    memcpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
    sendPDU(pdu);
}

void Client::on_login_PB_clicked()
{//登录按钮的槽函数
    qDebug()<<"on_login_PB_clicked start";
    //获取输入框中的姓名和密码
    QString strName = ui->username_LE->text();
    QString strPwd = ui->password_PB->text();
    qDebug() << "strName:" << strName
             << "strPwd:" << strPwd;
    //是否获取成功
    if(strName.isEmpty() || strPwd.isEmpty() ||
            strName.size() > 32 || strPwd.size() > 32){
        QMessageBox::critical(this,"登录","用户名或密码错误");
        //父组件，标题，提示
        return;
    }
    //构建pdu，用户名和密码放入caData(参数)
    PDU* pdu = mkPDU(0);//柔性数组的长度
    pdu->uiMsgType = ENUM_MSG_TYPE_LOGIN_REQUEST;//给服务器的请求
    memcpy(pdu->caData,strName.toStdString().c_str(),32);
    memcpy(pdu->caData+32,strPwd.toStdString().c_str(),32);
    m_strLoginName = strName;//获取当前的登录名
    sendPDU(pdu);
}
