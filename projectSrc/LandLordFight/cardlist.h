#ifndef CARDLIST_H
#define CARDLIST_H

#include <QObject>
#include <QList>
#include "card.h"
//牌堆类型
#define CARDLIST_TYPE_COUNT (8)
enum CARDLIST_TYPE{
    CARDLIST_LIFT_PLAYER,//左边玩家牌堆
    CARDLIST_MID_PLAYER,//中间玩家牌堆
    CARDLIST_RIGHT_PLAYER,//右边玩家牌堆
    CARDLIST_LORD,//三张地主牌
    CARDLIST_WHOLE,//初始牌堆，待发牌堆
    CARDLIST_LIFT_PLAYER_OUT,//左边玩家出牌堆
    CARDLIST_MID_PLAYER_OUT,//中间玩家出牌堆
    CARDLIST_RIGHT_PLAYER_OUT,//右边玩家出牌堆
};

//
//牌堆（牌的链表）
//

class CardList : public QObject
{
    Q_OBJECT

public:
    explicit CardList(QObject *parent = nullptr);
    //赋值类型
    void setCardListType(int type);
    //添加牌
    void addCard(Card* card);
    //以列表形式添加牌
    void addCard(QList<Card*> cards);
    //显示牌堆
    void cardShow();
    //打印牌堆:有的是背面，看不到，但是可以打印出来
    void cardPrint();
    //选牌-出牌
    //获取选中的链表
    QList<Card*> getSelectedCards();
    //删除选中的链表
    void deleteSelectedCards();

    //发牌
    //从牌堆拿一张牌
    Card* getOneCard();
    //把所有牌设置为正面或者反面
    void setAllCardsPositive(bool flag);

    //洗牌
    //打乱顺序 shuffle
    void shuffle();
    //排序
    void cardSort();
private:
    //获取当前牌的权重
    int getCardValue(Card* card);

signals:

private:
    int m_cardListType;//牌堆类型
    int m_beginX = 0;
    int m_beginY = 0;


public:
    QList<Card*> m_cardList;//管理牌的链表

};

#endif // CARDLIST_H
