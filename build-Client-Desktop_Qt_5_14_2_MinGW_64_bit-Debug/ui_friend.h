/********************************************************************************
** Form generated from reading UI file 'friend.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIEND_H
#define UI_FRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Friend
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *char_PB;
    QPushButton *flushFriend_PB;
    QPushButton *delFriend_PB;
    QSpacerItem *verticalSpacer;
    QPushButton *findFriend_PB;
    QPushButton *online_PB;

    void setupUi(QWidget *Friend)
    {
        if (Friend->objectName().isEmpty())
            Friend->setObjectName(QString::fromUtf8("Friend"));
        Friend->resize(800, 600);
        horizontalLayout = new QHBoxLayout(Friend);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, -1, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(Friend);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        char_PB = new QPushButton(Friend);
        char_PB->setObjectName(QString::fromUtf8("char_PB"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(14);
        char_PB->setFont(font);

        verticalLayout->addWidget(char_PB);

        flushFriend_PB = new QPushButton(Friend);
        flushFriend_PB->setObjectName(QString::fromUtf8("flushFriend_PB"));
        flushFriend_PB->setFont(font);

        verticalLayout->addWidget(flushFriend_PB);

        delFriend_PB = new QPushButton(Friend);
        delFriend_PB->setObjectName(QString::fromUtf8("delFriend_PB"));
        delFriend_PB->setFont(font);

        verticalLayout->addWidget(delFriend_PB);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        findFriend_PB = new QPushButton(Friend);
        findFriend_PB->setObjectName(QString::fromUtf8("findFriend_PB"));
        findFriend_PB->setFont(font);

        verticalLayout->addWidget(findFriend_PB);

        online_PB = new QPushButton(Friend);
        online_PB->setObjectName(QString::fromUtf8("online_PB"));
        online_PB->setFont(font);

        verticalLayout->addWidget(online_PB);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(Friend);

        QMetaObject::connectSlotsByName(Friend);
    } // setupUi

    void retranslateUi(QWidget *Friend)
    {
        Friend->setWindowTitle(QCoreApplication::translate("Friend", "Form", nullptr));
        char_PB->setText(QCoreApplication::translate("Friend", "\350\201\212\345\244\251", nullptr));
        flushFriend_PB->setText(QCoreApplication::translate("Friend", "\345\210\267\346\226\260\345\245\275\345\217\213", nullptr));
        delFriend_PB->setText(QCoreApplication::translate("Friend", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        findFriend_PB->setText(QCoreApplication::translate("Friend", "\346\237\245\346\211\276\347\224\250\346\210\267", nullptr));
        online_PB->setText(QCoreApplication::translate("Friend", "\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Friend: public Ui_Friend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIEND_H
