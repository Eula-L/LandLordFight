/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QStackedWidget *sw_page;
    QWidget *page_home;
    QLabel *lb_homeShow;
    QPushButton *pb_quickStart;
    QWidget *page_game;
    QWidget *widget_2;
    QPushButton *pb_test;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QWidget *wdg_callLord;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_callLord;
    QPushButton *pb_noCall;
    QWidget *wdg_playCards;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_playCard;
    QPushButton *pb_helpPlayCard;
    QPushButton *pb_pass;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lb_leftPass;
    QLabel *lb_rightPass;
    QLabel *lb_midPass;
    QWidget *page_end;
    QLabel *lb_resultShow;
    QLabel *lb_win;
    QPushButton *pb_goHome;
    QPushButton *pb_next_2;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(1000, 650);
        MainDialog->setMinimumSize(QSize(1000, 650));
        MainDialog->setMaximumSize(QSize(1000, 650));
        sw_page = new QStackedWidget(MainDialog);
        sw_page->setObjectName(QString::fromUtf8("sw_page"));
        sw_page->setGeometry(QRect(0, 0, 1001, 651));
        page_home = new QWidget();
        page_home->setObjectName(QString::fromUtf8("page_home"));
        lb_homeShow = new QLabel(page_home);
        lb_homeShow->setObjectName(QString::fromUtf8("lb_homeShow"));
        lb_homeShow->setGeometry(QRect(0, 0, 1000, 650));
        lb_homeShow->setPixmap(QPixmap(QString::fromUtf8(":/image/home.png")));
        pb_quickStart = new QPushButton(page_home);
        pb_quickStart->setObjectName(QString::fromUtf8("pb_quickStart"));
        pb_quickStart->setGeometry(QRect(800, 550, 141, 71));
        pb_quickStart->setFlat(true);
        sw_page->addWidget(page_home);
        page_game = new QWidget();
        page_game->setObjectName(QString::fromUtf8("page_game"));
        widget_2 = new QWidget(page_game);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(-2, 0, 1001, 629));
        pb_test = new QPushButton(widget_2);
        pb_test->setObjectName(QString::fromUtf8("pb_test"));
        pb_test->setGeometry(QRect(0, 0, 80, 24));
        layoutWidget = new QWidget(widget_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 400, 1001, 56));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        wdg_callLord = new QWidget(layoutWidget);
        wdg_callLord->setObjectName(QString::fromUtf8("wdg_callLord"));
        horizontalLayout = new QHBoxLayout(wdg_callLord);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pb_callLord = new QPushButton(wdg_callLord);
        pb_callLord->setObjectName(QString::fromUtf8("pb_callLord"));
        pb_callLord->setMinimumSize(QSize(91, 32));
        pb_callLord->setMaximumSize(QSize(91, 32));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pb_callLord->setFont(font);
        pb_callLord->setStyleSheet(QString::fromUtf8("background-image: url(:/image/button.png);\n"
"color: rgb(255, 255, 255);"));
        pb_callLord->setFlat(true);

        horizontalLayout->addWidget(pb_callLord);

        pb_noCall = new QPushButton(wdg_callLord);
        pb_noCall->setObjectName(QString::fromUtf8("pb_noCall"));
        pb_noCall->setMinimumSize(QSize(91, 32));
        pb_noCall->setMaximumSize(QSize(91, 32));
        pb_noCall->setFont(font);
        pb_noCall->setStyleSheet(QString::fromUtf8("background-image: url(:/image/button.png);\n"
"color: rgb(255, 255, 255);"));
        pb_noCall->setFlat(true);

        horizontalLayout->addWidget(pb_noCall);


        horizontalLayout_3->addWidget(wdg_callLord);

        wdg_playCards = new QWidget(layoutWidget);
        wdg_playCards->setObjectName(QString::fromUtf8("wdg_playCards"));
        horizontalLayout_2 = new QHBoxLayout(wdg_playCards);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pb_playCard = new QPushButton(wdg_playCards);
        pb_playCard->setObjectName(QString::fromUtf8("pb_playCard"));
        pb_playCard->setMinimumSize(QSize(91, 32));
        pb_playCard->setMaximumSize(QSize(91, 32));
        pb_playCard->setFont(font);
        pb_playCard->setStyleSheet(QString::fromUtf8("background-image: url(:/image/button.png);\n"
"color: rgb(255, 255, 255);"));
        pb_playCard->setFlat(true);

        horizontalLayout_2->addWidget(pb_playCard);

        pb_helpPlayCard = new QPushButton(wdg_playCards);
        pb_helpPlayCard->setObjectName(QString::fromUtf8("pb_helpPlayCard"));
        pb_helpPlayCard->setMinimumSize(QSize(91, 32));
        pb_helpPlayCard->setMaximumSize(QSize(91, 32));
        pb_helpPlayCard->setFont(font);
        pb_helpPlayCard->setStyleSheet(QString::fromUtf8("background-image: url(:/image/button.png);\n"
"color: rgb(255, 255, 255);"));
        pb_helpPlayCard->setFlat(true);

        horizontalLayout_2->addWidget(pb_helpPlayCard);

        pb_pass = new QPushButton(wdg_playCards);
        pb_pass->setObjectName(QString::fromUtf8("pb_pass"));
        pb_pass->setMinimumSize(QSize(91, 32));
        pb_pass->setMaximumSize(QSize(91, 32));
        pb_pass->setFont(font);
        pb_pass->setStyleSheet(QString::fromUtf8("background-image: url(:/image/button.png);\n"
"color: rgb(255, 255, 255);"));
        pb_pass->setFlat(true);

        horizontalLayout_2->addWidget(pb_pass);


        horizontalLayout_3->addWidget(wdg_playCards);

        horizontalSpacer_2 = new QSpacerItem(157, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        lb_leftPass = new QLabel(widget_2);
        lb_leftPass->setObjectName(QString::fromUtf8("lb_leftPass"));
        lb_leftPass->setGeometry(QRect(250, 180, 100, 50));
        lb_leftPass->setPixmap(QPixmap(QString::fromUtf8(":/image/pass.png")));
        lb_leftPass->setAlignment(Qt::AlignCenter);
        lb_rightPass = new QLabel(widget_2);
        lb_rightPass->setObjectName(QString::fromUtf8("lb_rightPass"));
        lb_rightPass->setGeometry(QRect(650, 180, 100, 50));
        lb_rightPass->setPixmap(QPixmap(QString::fromUtf8(":/image/pass.png")));
        lb_rightPass->setAlignment(Qt::AlignCenter);
        lb_midPass = new QLabel(widget_2);
        lb_midPass->setObjectName(QString::fromUtf8("lb_midPass"));
        lb_midPass->setGeometry(QRect(450, 320, 100, 50));
        lb_midPass->setPixmap(QPixmap(QString::fromUtf8(":/image/pass.png")));
        lb_midPass->setAlignment(Qt::AlignCenter);
        sw_page->addWidget(page_game);
        page_end = new QWidget();
        page_end->setObjectName(QString::fromUtf8("page_end"));
        lb_resultShow = new QLabel(page_end);
        lb_resultShow->setObjectName(QString::fromUtf8("lb_resultShow"));
        lb_resultShow->setGeometry(QRect(0, 0, 1000, 650));
        lb_resultShow->setPixmap(QPixmap(QString::fromUtf8(":/image/win.png")));
        lb_win = new QLabel(page_end);
        lb_win->setObjectName(QString::fromUtf8("lb_win"));
        lb_win->setGeometry(QRect(400, 280, 191, 111));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font1.setPointSize(18);
        lb_win->setFont(font1);
        lb_win->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lb_win->setAlignment(Qt::AlignCenter);
        pb_goHome = new QPushButton(page_end);
        pb_goHome->setObjectName(QString::fromUtf8("pb_goHome"));
        pb_goHome->setGeometry(QRect(350, 450, 91, 31));
        pb_goHome->setFlat(true);
        pb_next_2 = new QPushButton(page_end);
        pb_next_2->setObjectName(QString::fromUtf8("pb_next_2"));
        pb_next_2->setGeometry(QRect(550, 450, 91, 31));
        pb_next_2->setFlat(true);
        sw_page->addWidget(page_end);

        retranslateUi(MainDialog);

        sw_page->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "MainDialog", nullptr));
        lb_homeShow->setText(QString());
        pb_quickStart->setText(QString());
        pb_test->setText(QApplication::translate("MainDialog", "\346\265\213\350\257\225\346\214\211\351\222\256", nullptr));
        pb_callLord->setText(QApplication::translate("MainDialog", "\345\217\253\345\234\260\344\270\273", nullptr));
        pb_noCall->setText(QApplication::translate("MainDialog", "\344\270\215\345\217\253", nullptr));
        pb_playCard->setText(QApplication::translate("MainDialog", "\345\207\272\347\211\214", nullptr));
        pb_helpPlayCard->setText(QApplication::translate("MainDialog", "\346\217\220\347\244\272", nullptr));
        pb_pass->setText(QApplication::translate("MainDialog", "\344\270\215\345\207\272", nullptr));
        lb_leftPass->setText(QString());
        lb_rightPass->setText(QString());
        lb_midPass->setText(QString());
        lb_resultShow->setText(QString());
        lb_win->setText(QApplication::translate("MainDialog", "\346\201\255\345\226\234\n"
" \344\275\240\350\265\242\344\272\206\357\274\201", nullptr));
        pb_goHome->setText(QString());
        pb_next_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
