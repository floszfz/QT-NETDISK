#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpSocket>
#include <QWidget>
#include "protocol.h"
#include "reshandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    ~Client();
    void loadConfig();  //添加配置
    static Client& getInstance();
    void recvMsg();
    QTcpSocket& getTcpSocket();
    PDU *readPDU();//读取
    void handleMsg(PDU* pdu);//处理消息类型
    ResHandler* m_prh;
    QString m_strLoginName;//当前的登录名
    void sendPDU(PDU* pdu);

public slots://槽函数
    void showConnect();

private slots:
//    void on_pushButton_clicked();

    void on_regist_PB_clicked();
    void on_login_PB_clicked();

private:
    Ui::Client *ui;
    //定义两个属性
    QString m_strIP;//地址
    quint16 m_usPort;//端口号
    QTcpSocket m_tcpSocket;//用他链接服务器
    Client(QWidget *parent = nullptr);//私有构造
    Client(const Client& instance) = delete;
    Client& operator=(const Client&) = delete;
};
#endif // WIDGET_H
