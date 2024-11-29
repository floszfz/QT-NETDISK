#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
    void loadConfig();

private:
    Ui::Server *ui;
    QString m_strIP;//地址
    quint16 m_usPort;//端口号

};
#endif // SERVER_H
