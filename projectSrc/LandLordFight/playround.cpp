#include "playround.h"
#include "maindialog.h"



PlayRound::PlayRound(MainDialog *p,QObject *parent)
    : QObject(parent),m_mainDialog(p)
{

}

void PlayRound::initRound()
{
    //关于叫地主
    beginCallLord =CARDLIST_LORD;//记录从谁开始
    isEndCall = false;//是否结束叫地主
    lordPlayer = CARDLIST_LORD;//地主是谁
    //关于出牌
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
void PlayRound::decideBeginLord()
{
    beginCallLord = qrand()%3; // 0 1 2
    callLordOrGiveUp(beginCallLord);
}

void PlayRound::slot_midPlayerCallLord()
{
    //播放声音
    //区分叫地主和抢地主

    if(biggestPlayer ==CARDLIST_LORD)
    {
        //没人叫
        CardSound::playSound(SOUND_JIAODIZHU);
    }
    else
    {
        //有人叫，那就是抢地主
        CardSound::playSound(SOUND_ROBLORD);
    }
    biggestPlayer = CARDLIST_MID_PLAYER;
    //叫完了，隐藏ui
    m_mainDialog->slot_showCallLord(false);
    //显示叫地主和不叫的ui标签todo

    //回合剩余时间显示

    //切换下一个
    turnCallLord(CARDLIST_MID_PLAYER+1);
}

void PlayRound::slot_midPlayerNoCallLord()
{
        //播放声音
     CardSound::playSound(SOUND_NOCALL);
        //显示不叫todo
     //叫完了，隐藏ui
     m_mainDialog->slot_showCallLord(false);
    //回合时间 todo
    //切换下一个玩家
     turnCallLord(CARDLIST_MID_PLAYER+1);
}

void PlayRound::slot_computerCallLord(int player)
{
    //看有没有炸，有就叫
    bool res = AIPlayCard::isCallLord(m_mainDialog->m_cardList[player].m_cardList);
    if(res)
    {
        //叫地主
        if(biggestPlayer ==CARDLIST_LORD)
        {
            //没人叫
            CardSound::playSound(SOUND_JIAODIZHU);
        }
        else
        {
            //有人叫，那就是抢地主
            CardSound::playSound(SOUND_ROBLORD);
        }
        biggestPlayer = player;
        //回合剩余时间显示todo
    }
    else
    {
        //不叫地主
        CardSound::playSound(SOUND_NOCALL);
    }
    //切换下一个
    turnCallLord((player+1)%3);
}

void PlayRound::slot_computerNoCallLord(int player)
{
    currentPlayer =player;
    //首先判断是否结束
    if(player == (biggestPlayer+1)%3)
    {
        //第二次进
       if(isEndCall)
        {
           //都不叫地主
           if(biggestPlayer ==CARDLIST_LORD)
           {
               //重新开局
               delayMSecond(1000);
               m_mainDialog->on_pb_quickStart_clicked();
               return;
           }
           //有人叫地主
           //开始出牌阶段
           lordPlayer = biggestPlayer;
           //设置地主的图标

           //地主加三张牌
            m_mainDialog->slot_lordAddCards(lordPlayer);
           //开始出牌阶段
           delayMSecond(1000);
           startRound(biggestPlayer);
           return;
        }
    }
    isEndCall = true;
    //没结束 抢地主
    if(biggestPlayer ==player)
    {
        turnCallLord((player+1)%3);
        return;
    }
    callLordOrGiveUp(player);
}

void PlayRound::turnCallLord(int player)
{
        //当前玩家赋值
        currentPlayer=player;

        //首先判断是否结束  1-》2-》0-》1-》2  2决定 是否结束 来记录第一次还是第二次 isEndcall来确认
        if(player==(beginCallLord+1)%3)
        {
            //这个player第二次进来 结束
            if(isEndCall)
            {
                //都不叫地主
                if(biggestPlayer==CARDLIST_LORD)
                {
                    //重新开局
                    delayMSecond(5000);
                    m_mainDialog->on_pb_quickStart_clicked();
                    return;
                }
                //有人叫地主
                lordPlayer=biggestPlayer;
                //设置地主图标

                //地主家三张牌
                m_mainDialog->slot_lordAddCards(lordPlayer);
                //开始出牌阶段
                delayMSecond(1000);
                startRound(biggestPlayer);
                return;
            }
        }
        isEndCall=true;
        //没有结束
        //进行 抢地主
        //如果自己是最大的 ，不能抢自己
        if(biggestPlayer==player)
        {
            turnCallLord((player+1)%3);
            return;
        }
        callLordOrGiveUp(player);

    }

void PlayRound::callLordOrGiveUp(int player)
{
    //看当前用户，叫地主还是放弃
    currentPlayer = player;

    //如果是玩家，显示ui
    if(currentPlayer == CARDLIST_MID_PLAYER)
    {
        m_mainDialog->slot_showCallLord(true);
    }
    else
    {
        delayMSecond(2000);
        slot_computerCallLord(currentPlayer);
    }
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
