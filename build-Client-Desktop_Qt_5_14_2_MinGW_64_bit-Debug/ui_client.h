/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *username_LE;
    QLabel *label_2;
    QLineEdit *password_PB;
    QHBoxLayout *horizontalLayout;
    QPushButton *regist_PB;
    QSpacerItem *horizontalSpacer;
    QPushButton *login_PB;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(389, 203);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        Client->setFont(font);
        layoutWidget = new QWidget(Client);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 30, 311, 131));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        username_LE = new QLineEdit(layoutWidget);
        username_LE->setObjectName(QString::fromUtf8("username_LE"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(16);
        username_LE->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, username_LE);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        password_PB = new QLineEdit(layoutWidget);
        password_PB->setObjectName(QString::fromUtf8("password_PB"));
        password_PB->setFont(font1);
        password_PB->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, password_PB);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        regist_PB = new QPushButton(layoutWidget);
        regist_PB->setObjectName(QString::fromUtf8("regist_PB"));
        regist_PB->setFont(font1);

        horizontalLayout->addWidget(regist_PB);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        login_PB = new QPushButton(layoutWidget);
        login_PB->setObjectName(QString::fromUtf8("login_PB"));
        login_PB->setFont(font1);

        horizontalLayout->addWidget(login_PB);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Client", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("Client", "\345\257\206  \347\240\201\357\274\232", nullptr));
        regist_PB->setText(QCoreApplication::translate("Client", "\346\263\250\345\206\214", nullptr));
        login_PB->setText(QCoreApplication::translate("Client", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
