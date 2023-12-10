#include "cardlist.h"

CardList::CardList(QObject *parent) : QObject(parent)
{

}

void CardList::setCardListType(int type)
{
    m_cardListType =type;
}

void CardList::addCard(Card *card)
{
    //如果当前玩家是中间玩家，可以将牌设为正面
    if(m_cardListType == CARDLIST_MID_PLAYER)
    {
        card->setCardPositive(true);
    }
    if(m_cardListType == CARDLIST_LIFT_PLAYER_OUT||
            m_cardListType == CARDLIST_MID_PLAYER_OUT||
            m_cardListType == CARDLIST_RIGHT_PLAYER_OUT)
    {
        card->setCardPositive(true);
    }
    m_cardList.append(card);
}

void CardList::addCard(QList<Card *> cards)
{
    for(Card* card:cards)
    {
        addCard(card);
    }
}

void CardList::cardShow()
{
    int count =0;
    switch(m_cardListType)
    {
    case CARDLIST_LIFT_PLAYER:
        m_beginX =70;
        m_beginY =170;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->move(m_beginX,m_beginY+(count++)*10);
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//左边玩家牌堆
    case CARDLIST_MID_PLAYER:
        m_beginX =1000/2-(Card_Width+(m_cardList.size()-1)*CARD_SHOW_WIDTH)/2;
        m_beginY =650-150;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->setCardPositive(true);
            card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);
            if(card->m_isClicked)
            {
                card->slot_moveUp();
            }
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//中间玩家牌堆
    case CARDLIST_RIGHT_PLAYER:
        m_beginX =850;
        m_beginY =170;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->move(m_beginX,m_beginY+(count++)*10);
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//右边玩家牌堆
    case CARDLIST_LORD:
        m_beginX =1000/2-(Card_Width*3+20*2)/2;
        m_beginY =50;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->move(m_beginX+(count++)*(Card_Width+20),m_beginY);
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//三张地主牌
    case CARDLIST_WHOLE:
        m_beginX =1000/2-(Card_Width+(m_cardList.size()-1)*5)/2;
        m_beginY =650/2-Card_Height/2;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->setCardPositive(false);
            card->move(m_beginX+(count++)*5,m_beginY);
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//初始牌堆，待发牌堆
    case CARDLIST_LIFT_PLAYER_OUT:
        m_beginX = 70+80+50;
        m_beginY = 170+10;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->setCardPositive(true);
            card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);
            //将牌至于最上方
            card->raise();
            card->show();
        }

        break;//左边玩家出牌堆
    case CARDLIST_MID_PLAYER_OUT:
        m_beginX =1000/2-(Card_Width+(m_cardList.size()-1)*CARD_SHOW_WIDTH)/2;
        m_beginY =300;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->setCardPositive(true);
            card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//中间玩家出牌堆
    case CARDLIST_RIGHT_PLAYER_OUT:
        m_beginX = 800-(Card_Width+(m_cardList.size()-1)*CARD_SHOW_WIDTH);
        m_beginY = 170+10;
        //显示每张牌
        for(Card* card:m_cardList)
        {
            card->setCardPositive(true);
            card->move(m_beginX+(count++)*CARD_SHOW_WIDTH,m_beginY);
            //将牌至于最上方
            card->raise();
            card->show();
        }
        break;//右边玩家出牌堆
    }
}
#include <QDebug>
void CardList::cardPrint()
{
    QString str ;
    //str += "当前牌：";
    for(Card *card :m_cardList)
    {
        if(card->m_point==Card_SmallKing)
        {
            str+="小王 ";
            continue;
        }
        else if(card->m_point==Card_BigKing)
        {
            str+="大王 ";
            continue;
        }

        switch(card->m_suit)
        {
        case Spade:
            str += "黑桃";
            break;
        case Heart:
            str += "红桃";
            break;
        case Club:
            str += "梅花";
            break;
        case Diamond:
            str += "方片";
            break;
        }

        if(card->m_point ==Card_A)
        {
            str+="A ";
        }
        else if(card->m_point == Card_2)
        {
            str+="2 ";
        }
        else
        {
            str+=QString::number(card->m_point+3);
            str+=" ";
        }

    }
    qDebug()<<str;
}

QList<Card *> CardList::getSelectedCards()
{
    QList<Card *> lst;
    for(Card* card:m_cardList)
    {
        if(card->m_isClicked)
            lst.append(card);
    }
    return lst;

}

void CardList::deleteSelectedCards()
{
    for(auto ite = m_cardList.begin();ite!=m_cardList.end();/*ite++*/)
    {
        Card*  card = *ite;
        if(card->m_isClicked)
        {
            ite = m_cardList.erase(ite);
        }
        else
        {
            ++ite;
        }
    }
}


Card *CardList::getOneCard()
{
    if(!m_cardList.isEmpty())
    {
        return m_cardList.takeFirst();//从链表头部拿节点，并且移除这个
    }
    return nullptr;
}

#include <random>
#include <QDateTime>
void CardList::shuffle()
{
    //用当前时间戳作为随机数种子
    //林威治时间：1970 01 01 00 00 00 距离当前时间是多少秒
    qint64 seed =QDateTime::currentSecsSinceEpoch();
    std::shuffle(m_cardList.begin(),m_cardList.end(),std::default_random_engine(seed));//第三个参数是——随机数生成器
}

void CardList::cardSort()
{
    //牌排序
    //规则：点数大的在左边、点数相同的花色安装 片 梅 黑 红 无
    //权重排序
    //lambda表达式

    std::sort(m_cardList.begin(),m_cardList.end(),
              [this](Card* &a,Card* &b)
              {return getCardValue(a)>getCardValue(b);});
}

int CardList::getCardValue(Card *card)
{
    return card->m_point*10+(4-card->m_suit);
}
