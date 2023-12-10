#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "card.h"
#include "cardlist.h"
#include <QTimer>
#include <QDebug>
#include "rulers.h"
#include "cardsound.h"
#include "playround.h"
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private slots:
    void on_pb_quickStart_clicked();

    void on_pb_goHome_clicked();

    void on_pb_next_2_clicked();

    void on_pb_test_clicked();

    void slot_setBackGround();

    void slot_startOneGame();

    void slot_refreshAllCardList();

    void on_pb_playCard_clicked();

    void slot_deleteAllPlayerOutCards();

    void slot_deleteOnePlayerOutCards(int player);

    void slot_showPlayCards(bool flag);

    void slot_showCallLord(bool flag);

    void on_pb_pass_clicked();

    void slot_hideAllPass();

    void on_pb_callLord_clicked();

    void on_pb_noCall_clicked();

    //地主加三张牌
    void slot_lordAddCards(int player);

private:
    Ui::MainDialog *ui;
    //QList<Card* > m_cardLastPlayer;放在回合管理
    CardList m_cardList[CARDLIST_TYPE_COUNT];
    QLabel* m_lbPassArr[3];
    QTimer m_timerRefresh;//刷新显示定时器
    PlayRound m_playRound;//类中的对象的初始化 要在类的构造的参数列表实现初始化
    friend class PlayRound;
};
#endif // MAINDIALOG_H
