#include "server.h"
#include "ui_server.h"

#include <qfile.h>
#include <QDebug>
#include <qmessagebox.h>
#include "mytcpserver.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    loadConfig();
    qDebug()<< "ip:" << m_strIP << "port:" << m_usPort;
    MyTcpServer::getInstance().listen(QHostAddress(m_strIP),m_usPort);//调用监听方法
}

Server::~Server()
{
    delete ui;
}

void Server::loadConfig()
{
    QFile file(":/server.config");//打开文件
    if(file.open(QIODevice::ReadOnly)){
        QByteArray baData = file.readAll();
        QString strData = QString(baData);
        QStringList strList = strData.split("\r\n");
        m_strIP = strList.at(0);
        m_usPort = strList.at(1).toUShort();
        qDebug()<< "ip:" << m_strIP << "port:" << m_usPort;
        file.close();
    }else{
        QMessageBox::critical(this,"打开配置","打开配置失败");
    }
}

