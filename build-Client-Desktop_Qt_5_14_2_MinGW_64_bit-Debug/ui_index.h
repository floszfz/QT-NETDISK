/********************************************************************************
** Form generated from reading UI file 'index.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDEX_H
#define UI_INDEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "file.h"
#include "friend.h"

QT_BEGIN_NAMESPACE

class Ui_Index
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *friend_PB;
    QPushButton *file_PB;
    QStackedWidget *stackedWidget;
    Friend *friendPage;
    File *filePage;

    void setupUi(QWidget *Index)
    {
        if (Index->objectName().isEmpty())
            Index->setObjectName(QString::fromUtf8("Index"));
        Index->resize(800, 600);
        horizontalLayout = new QHBoxLayout(Index);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        friend_PB = new QPushButton(Index);
        friend_PB->setObjectName(QString::fromUtf8("friend_PB"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(friend_PB->sizePolicy().hasHeightForWidth());
        friend_PB->setSizePolicy(sizePolicy);
        friend_PB->setMinimumSize(QSize(0, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(20);
        friend_PB->setFont(font);
        friend_PB->setStyleSheet(QString::fromUtf8("border:none;background-color:rgb(255,255,255);padding:20px;"));

        verticalLayout->addWidget(friend_PB);

        file_PB = new QPushButton(Index);
        file_PB->setObjectName(QString::fromUtf8("file_PB"));
        sizePolicy.setHeightForWidth(file_PB->sizePolicy().hasHeightForWidth());
        file_PB->setSizePolicy(sizePolicy);
        file_PB->setMinimumSize(QSize(0, 100));
        file_PB->setFont(font);
        file_PB->setStyleSheet(QString::fromUtf8("border:none;background-color:rgba(255,255,255,0);padding:20px;"));

        verticalLayout->addWidget(file_PB);


        horizontalLayout->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(Index);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        friendPage = new Friend();
        friendPage->setObjectName(QString::fromUtf8("friendPage"));
        stackedWidget->addWidget(friendPage);
        filePage = new File();
        filePage->setObjectName(QString::fromUtf8("filePage"));
        stackedWidget->addWidget(filePage);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(Index);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Index);
    } // setupUi

    void retranslateUi(QWidget *Index)
    {
        Index->setWindowTitle(QCoreApplication::translate("Index", "Form", nullptr));
        friend_PB->setText(QCoreApplication::translate("Index", "\345\245\275\n"
"\345\217\213", nullptr));
        file_PB->setText(QCoreApplication::translate("Index", "\346\226\207\n"
"\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Index: public Ui_Index {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDEX_H
