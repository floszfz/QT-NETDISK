#ifndef FRIEND_H
#define FRIEND_H

#include <QWidget>
#include <QMessageBox>

#include "onlineuser.h"

namespace Ui {
class Friend;
}

class Friend : public QWidget
{
    Q_OBJECT

public:
    explicit Friend(QWidget *parent = nullptr);
    ~Friend();
    OnlineUser* getOnlineUser();
    void showOnlineFriend(QStringList friendList);
    void flushFriend();

private slots:
    void on_findFriend_PB_clicked();

    void on_online_PB_clicked();

    void on_flushFriend_PB_clicked();


    void on_delFriend_PB_clicked();

private:
    Ui::Friend *ui;
    OnlineUser* m_pOnlineUser;
};

#endif // FRIEND_H
