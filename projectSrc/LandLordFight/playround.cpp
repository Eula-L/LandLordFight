#include "playround.h"
#include "maindialog.h"



PlayRound::PlayRound(MainDialog *p,QObject *parent)
    : QObject(parent),m_mainDialog(p)
{

}

void PlayRound::initRound()
{
    biggestPlayer = CARDLIST_LORD;
    currentPlayer =CARDLIST_LORD;
    lastPlayerCards.clear();
}
#include <QCoreApplication>
void PlayRound::delayMSecond(int msec)
{
    do{
        _sleep(10);
        QCoreApplication::processEvents(QEventLoop::AllEvents,10);
        msec-=20;
    }
    while(msec>=0);

}

void PlayRound::startRound(int player)
{
    //所有“不出”隐藏
    m_mainDialog->slot_hideAllPass();
    qDebug()<<"PlayRound::startRound";
    //清除所有玩家外面的手牌
    m_mainDialog->slot_deleteAllPlayerOutCards();
    //上一个玩家的牌组，清掉
    lastPlayerCards.clear();
    //当前玩家赋值
    currentPlayer = player;
    if(currentPlayer == CARDLIST_MID_PLAYER)
    {
         qDebug()<<"//显示 出牌的按钮";
        //显示 出牌的按钮
        m_mainDialog->slot_showPlayCards(true);

    }
    else
    {
        delayMSecond(2000);
        slot_copmuterRound(player);
    }
}

void PlayRound::turnPlayer(int player)
{
    //当前玩家更新
    currentPlayer = player;
    if(biggestPlayer == player)
    {delayMSecond(1000);
        startRound(player);
        return;
    }
    //到谁的回合，就清除掉，自己外面的“不出”
    m_mainDialog->m_lbPassArr[currentPlayer]->hide();
    //不是他的牌权，需要管别人

    //清楚玩家外面手牌
    m_mainDialog->slot_deleteOnePlayerOutCards(player);
    //不显示 不出

   //判断是玩家还是电脑
    if(currentPlayer == CARDLIST_MID_PLAYER)
    {
        //显示 出牌的按钮
        m_mainDialog->slot_showPlayCards(true);

    }
    else
    {
        delayMSecond(2000);
        slot_copmuterRound(player);
    }
}

void PlayRound::slot_midPlayerPlayCards()
{
        //符合
        //获得选中牌
        QList<Card* > lst =m_mainDialog->m_cardList[CARDLIST_MID_PLAYER].getSelectedCards();
        if(lst.size()==0)return;
        if(Rulers::canPlayCards(lst,lastPlayerCards))
        {
            //根据牌组播放音乐
            //CardSound::playCardsSound(lst);
            //将选择的牌添加到玩家out牌堆
            m_mainDialog->m_cardList[CARDLIST_MID_PLAYER_OUT].addCard(lst);

            //删除选中
            m_mainDialog->m_cardList[CARDLIST_MID_PLAYER].deleteSelectedCards();

            biggestPlayer =CARDLIST_MID_PLAYER;
            lastPlayerCards =lst;

            //隐藏 出牌ui
            m_mainDialog->slot_showPlayCards(false);
            //回合传递
            turnPlayer(CARDLIST_MID_PLAYER+1);
        }

}

void PlayRound::slot_midPlayerPass()
{
    //当前牌权是自己，最大的是自己，不可以不出
    if(biggestPlayer == CARDLIST_MID_PLAYER)
    {
        return;
    }
    //出牌，隐藏按钮
    m_mainDialog->slot_showPlayCards(false);
    //播放声音
    CardSound::playSound(SOUND_PASS);
    //显示 不出
    m_mainDialog->m_lbPassArr[CARDLIST_MID_PLAYER]->show();
    //切换到下一个人
    turnPlayer(CARDLIST_MID_PLAYER+1);
}

void PlayRound::slot_copmuterRound(int player)
{
    //电脑出牌 出牌 不出
    slot_computerPlayCards(player);
    //下一个玩家
    turnPlayer((player+1)%3);//玩家轮转
}

void PlayRound::slot_computerPlayCards(int player)
{
    QList<Card*> cards;
    //找能出的牌
    //cards =func();
//    if(AIPlayCard::findSmallestCards(m_mainDialog->m_cardList[player].m_cardList)!=0)
//    {
//        cards =m_mainDialog->m_cardList[player].getSelectedCards();
//    }
    //不管是谁，都管
    cards = AIPlayCard::BeatCards(m_mainDialog->m_cardList[player].m_cardList,lastPlayerCards);
    if(cards.size()==0)
    {
        //找不到就不要
        CardSound::playSound(SOUND_PASS);
        //显示“不出”todo
        m_mainDialog->m_lbPassArr[player]->show();
    }
    else
    {
        //找到就管
        CardSound::playCardsSound(cards);
        m_mainDialog->m_cardList[player+CARDLIST_LIFT_PLAYER_OUT].addCard(cards);
        m_mainDialog->m_cardList[player].deleteSelectedCards();
        biggestPlayer =player;
        lastPlayerCards = cards;

    }
}

void PlayRound::slot_computerPass()
{

}
