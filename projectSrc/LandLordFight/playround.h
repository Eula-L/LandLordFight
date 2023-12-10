#ifndef PLAYROUND_H
#define PLAYROUND_H

#include <QObject>
#include "card.h"
#include "aiplaycard.h"

class MainDialog;//避免循环调用，头文件中创建一个类，cpp文件中再去包含要包含的那个头文件

class PlayRound : public QObject
{
    Q_OBJECT
public:
    explicit PlayRound(MainDialog *p,QObject *parent = nullptr);
    //初始化，清空数据
    void initRound();
    //延时函数
    void delayMSecond(int msec);
signals:

public:
    //叫地主阶段

    /////////////出牌阶段
    //开启回合
    void startRound(int player);
    //回合传递
    void turnPlayer(int player);
    //玩家出牌
    void slot_midPlayerPlayCards();
    //玩家不要-todo
    void slot_midPlayerPass();

    //电脑回合
    void slot_copmuterRound(int player);
    //电脑出牌
    void slot_computerPlayCards(int player);
    //电脑不要
    void slot_computerPass();

    ///////////////结算阶段

    ///////////////出牌阶段的成员

    //出牌牌权->最大玩家
    int biggestPlayer=0;
    //当前出牌的人
    int currentPlayer=0;
    //上一个出牌的人的牌组
    QList<Card*>lastPlayerCards;
    //当前牌组类型（可以由上一个出牌人的牌组获取）

private:
    MainDialog * m_mainDialog;
};

#endif // PLAYROUND_H
