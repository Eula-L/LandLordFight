#include "rulers.h"



int Rulers::getCardType(QList<Card *> &card)
{
    int n = card.count();
    if(n == 0)return CARDTYPE_NONE;
    if(n ==1)
    {
        return SINGLE;
    }
    else if(n == 2)
    {
        if(card.at(0)->m_point == card.at(1)->m_point)
        {
            return PAIR;
        }
        else if(card.at(0)->m_point == Card_BigKing &&
                card.at(1)->m_point ==  Card_SmallKing)
        {
            return KING_BOMB;
        }
    }
    else if(n == 3)
    {
        if(card.at(0)->m_point == card.at(1)->m_point &&
                card.at(1)->m_point == card.at(2)->m_point)
        {
            return TRIPLE;
        }
    }
    else if(n == 4)
    {
        //炸弹
        if(card.at(0)->m_point == card.at(1)->m_point &&
           card.at(1)->m_point == card.at(2)->m_point &&
           card.at(2)->m_point == card.at(3)->m_point)
        {
            return BOMB;
        }
        //三带一
        if((card.at(0)->m_point != card.at(1)->m_point &&
           card.at(1)->m_point == card.at(2)->m_point &&
           card.at(2)->m_point == card.at(3)->m_point)
                ||
           (card.at(0)->m_point == card.at(1)->m_point &&
            card.at(1)->m_point == card.at(2)->m_point &&
            card.at(2)->m_point != card.at(3)->m_point))
        {
            qDebug()<<"三带一";
            return TRIPLE_WITH_ONE;
        }
    }
    else if(n == 5)
    {
        //三带一对
        if((card.at(0)->m_point == card.at(1)->m_point &&
           card.at(1)->m_point != card.at(2)->m_point &&
           card.at(2)->m_point == card.at(3)->m_point &&
           card.at(3)->m_point == card.at(4)->m_point)
                ||
                (card.at(0)->m_point == card.at(1)->m_point &&
                           card.at(1)->m_point == card.at(2)->m_point &&
                           card.at(2)->m_point != card.at(3)->m_point &&
                           card.at(3)->m_point == card.at(4)->m_point))
        {
            return TRIPLE_WITH_PAIR;
        }
        //顺子
        if(isStraight(card))return  STRAIGHT;

    }
    else if(n == 6)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;
        //连对
        if(isStiaightPair(card))return STRAIGHT_PAIR;
        //飞机
        if(isPlane(card))return PLANE;
        //四带二
        if(isFourWithTwo(card))return FOUR_WITH_TOW;
    }
    else if(n == 7)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;
    }
    else if(n == 8)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;
        //连对
        if(isStiaightPair(card))return STRAIGHT_PAIR;
        //飞机带翅膀两个3张带2个单张
        if(isPlaneWithWing(card))return PLANT_WITH_WING;

        //四个加两对
        if(isFourWithTwoPair(card)) return FOUR_WITH_TWO_PAIR;
    }
    else if(n == 9)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;
        //飞机
        if(isPlane(card))return PLANE;
    }
    else if(n == 10)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;
        //连对
        if(isStiaightPair(card))return STRAIGHT_PAIR;
        //飞机带翅膀两个3张带2对
        if(isPlaneWithWing(card))return PLANT_WITH_WING;
    }
    else if(n == 11)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;

    }
    else if(n == 12)
    {
        //顺子
        if(isStraight(card))return  STRAIGHT;
        //连对
        if(isStiaightPair(card))return STRAIGHT_PAIR;
        //飞机
        if(isPlane(card))return PLANE;
    }
    else if(n == 13)
    {

    }
    else if(n == 14)
    {
        //连对
        if(isStiaightPair(card))return STRAIGHT_PAIR;
    }
    else if(n == 15)
    {

    }
    else if(n == 16)
    {

    }

}

bool Rulers::isStraight(QList<Card *> &card)
{
    int len = card.size();
    for(int i=0;i<len;i++)
    {
        if(card.at(i)->m_point==Card_2 ||
                card.at(i)->m_point==Card_SmallKing ||
                card.at(i)->m_point==Card_BigKing)
            return false;
        if(i>0)
        {
            if(card.at(i)->m_point != card.at(i-1)->m_point-1)
                return false;

        }
    }
    return true;
}

bool Rulers::isStiaightPair(QList<Card *> &card)
{
//    //1、大于6张，且偶数
//    //2、对2 对王 不能出现
//    //3、每张牌出现的次数是2
//    int size = card.size();
//    if(size<6||size%2!=0)return false;

//    for(int i=0;i<size;i++)
//    {
//        if(card.at(i)->m_point==Card_2 ||
//                card.at(i)->m_point==Card_SmallKing ||
//                card.at(i)->m_point==Card_BigKing)
//            return false;
//        if(card.at(i)->m_point !=card.at(i+1)->m_point)return false;
//        i++;
//        if(card.at(i)->m_point !=card.at(i+1)->m_point-1)return  false;
//    }
//    return true;
//    //1、牌不能少于6张 必须是偶数          2、对二对王不能出现
//        //3、统计个数 每张牌出现次数都应该是2   4、差值 满足情况第一张-最后一张=n/2-1；循环card[i]-card[i+2]==1;
//        int n=card.size();
//        if(n<6)return false;
//        if(n%2!=0)return false;        //偶数张牌
//        if(card.at(0)->m_point==Card_2||
//            card.at(0)->m_point==Card_BigKing||
//            card.at(0)->m_point==Card_SmallKing)
//            return false;
//        map<int,int> mapPointToCount;  //点数出现的次数
//        for(Card* c:card)              //统计个数
//        {
//           mapPointToCount[c->m_point]++;
//        }
//        //遍历map 看是否都是2个
//        for(pair<int,int> p:mapPointToCount)
//            if(p.second!=2) return false;

//        if(card.front()->m_point-card.back()->m_point ==  n/2-1)
//            return true;

//        return false;
    //1、牌不能少于6张 必须是偶数          2、对二对王不能出现
        //3、统计个数 每张牌出现次数都应该是2   4、差值 满足情况第一张-最后一张=n/2-1；循环card[i]-card[i+2]==1;
        int n=card.size();
        if(n<6)return false;
        if(n%2!=0)return false;        //偶数张牌
        if(card.at(0)->m_point==Card_2||
            card.at(0)->m_point==Card_BigKing||
            card.at(0)->m_point==Card_SmallKing)
            return false;
        map<int,int> mapPointToCount;  //点数出现的次数
        for(Card* c:card)              //统计个数
        {
           mapPointToCount[c->m_point]++;
        }
        //遍历map 看是否都是2个
        for(pair<int,int> p:mapPointToCount)
            if(p.second!=2) return false;

        if(card.front()->m_point-card.back()->m_point ==  n/2-1)
            return true;

        return false;
}

bool Rulers::isPlane(QList<Card *> &card)
{
    //根据上面的进行修改
        //1、牌不能少于6张 必须是三的倍数          2、对二和王不能出现
        //3、统计个数 每张牌出现次数都应该是3   4、差值 满足情况第一张-最后一张=n/3-1；循环card[i]-card[i+3]==1;
        int n=card.size();
        if(n<6)return false;
        if(n%3!=0)return false;        //偶数张牌
        if(card.at(0)->m_point==Card_2||
            card.at(0)->m_point==Card_BigKing||
            card.at(0)->m_point==Card_SmallKing)
            return false;
        map<int,int> mapPointToCount;  //点数出现的次数
        for(Card* c:card)              //统计个数
        {
           mapPointToCount[c->m_point]++;
        }
        //遍历map 看是否都是2个
        for(pair<int,int> p:mapPointToCount)
            if(p.second!=3) return false;

        if(card.front()->m_point-card.back()->m_point ==  n/3-1)
            return true;

        return false;
}

bool Rulers::isPlaneWithWing(QList<Card *> &card)
{
    //判断八张和十张的情况
        int n=card.size();
        //1.统计个数  2.大小王和二不能出现
        //3.判断三个的是否连续 单牌带两个数 要不相等 要有两个数
        //10张 带两个不同的对子

        if(card.at(0)->m_point==Card_2||
            card.at(0)->m_point==Card_BigKing||
            card.at(0)->m_point==Card_SmallKing)
            return false;
        map<int,int> mapPointToCount;  //点数出现的次数
        for(Card* c:card)              //统计个数
        {
           mapPointToCount[c->m_point]++;
        }
        //map从小到大的顺序
        if(n==8)
        {
           int count =0;
           vector<int> vec;
           //遍历map 看看到个数为三 加入到vector
           //看vec 是否是两个元素 是否差值为1 vec[1]-vec[0]==1
           //单牌 个数为1 就count++ 看count 是不是2个
           for(pair<int,int> p:mapPointToCount)
           {
               if(p.second==3) vec.push_back(p.first);
               if(p.second==1)count++;
           }
           if(count!=2)return false;
           if(vec.size()!=2)return false;
           if(vec[1]-vec[0]!=1)return false;

           return true;
        }
        else if(n==10)
        {
            int count =0;
            vector<int> vec;
            //遍历map 看看到个数为三 加入到vector
            //看vec 是否是两个元素 是否差值为1 vec[1]-vec[0]==1
            //单牌 个数为1 就count++ 看count 是不是2个
            for(pair<int,int> p:mapPointToCount)
            {
                if(p.second==3) vec.push_back(p.first);
                if(p.second==1)return false;
                if(p.second==2)count++;
            }
            if(count!=2)return false;
            if(vec.size()!=2)return false;
            if(vec[1]-vec[0]!=1)return false;
            return true;
        }
        else
        {
            return false;
        }
}

bool Rulers::isFourWithTwo(QList<Card *> &card)
{
    std::map<int,int> my_map;
    int size = card.size();
    if(size!=6)return false;

    for(Card* c:card)
    {
         if(my_map.count(c->m_point)!=0)
         {
             my_map[c->m_point] +=1;
         }
         else
         {
             my_map[c->m_point] =1;
         }
    }
    int count =0;
    //遍历map，看个数为4的元素

    for(pair<int,int> p :my_map)
    {
        if(p.second == 4)
            count+=40;
        if(p.second ==1)
            count+=1;
    }
    if(count==42)return true;
    return false;
}

bool Rulers::isFourWithTwoPair(QList<Card *> &card)
{
    std::map<int,int> my_map;
    int size = card.size();
    if(size!=8)return false;

    for(Card* c:card)
    {
         if(my_map.count(c->m_point)!=0)
         {
             my_map[c->m_point] +=1;
         }
         else
         {
             my_map[c->m_point] =1;
         }
    }
    int count =0;
    //遍历map，看个数为4的元素

    for(pair<int,int> p :my_map)
    {
        if(p.second == 4)
            count+=40;
        if(p.second ==2)
            count+=2;
    }
    if(count==44)return true;
    return false;
}

bool Rulers::compareCards(QList<Card *> &cards1, QList<Card *> &cards2)
{
    int type1  = getCardType(cards1);
    int type2  = getCardType(cards2);
    //类型相同，张数相同
    if(type1 == type2&& cards1.size() == cards2.size())
    {
        return compareSameCards(cards1,cards2,type1);
    }
    //不同
    //王炸
    if(type1 ==KING_BOMB)
    {
        return true;
    }
    //不是王炸
    if(type1 ==BOMB&& type2!=KING_BOMB)
    {
        return true;
    }
    return false;
}

bool Rulers::compareSameCards(QList<Card *> &cards1, QList<Card *> &cards2, int type)
{
    int value1= 0;
    int value2 =0;
    switch (type) {
    case SINGLE:
         return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    case PAIR:
         return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    case TRIPLE:
         return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    case TRIPLE_WITH_ONE:
        {
            map<int,int> mapPointCount1;
            map<int,int> mapPointCount2;
            for(Card* c:cards1)
            {
                mapPointCount1[c->m_point]+=1;
                if(mapPointCount1[c->m_point]==3)value1 = c->m_point;
            }
            for(Card* c:cards2)
            {
                mapPointCount2[c->m_point]+=1;
                if(mapPointCount2[c->m_point]==3)value2= c->m_point;
            }
            return value1>value2;
        }
         break;
    case TRIPLE_WITH_PAIR:
    {
        map<int,int> mapPointCount1;
        map<int,int> mapPointCount2;
        for(Card* c:cards1)
        {
            mapPointCount1[c->m_point]+=1;
            if(mapPointCount1[c->m_point]==3)value1 = c->m_point;
        }
        for(Card* c:cards2)
        {
            mapPointCount2[c->m_point]+=1;
            if(mapPointCount2[c->m_point]==3)value2= c->m_point;
        }
        return value1>value2;
    }
         break;
    case STRAIGHT:
        return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    case STRAIGHT_PAIR:
        return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    case PLANE:
        return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    case PLANT_WITH_WING:
    {
        map<int,int> mapPointCount1;
        map<int,int> mapPointCount2;
        for(Card* c:cards1)
        {
            mapPointCount1[c->m_point]+=1;
            if(mapPointCount1[c->m_point]==3){
                value1 = c->m_point;
                break;
            }
        }
        for(Card* c:cards2)
        {
            mapPointCount2[c->m_point]+=1;
            if(mapPointCount2[c->m_point]==3)
            {
                value2= c->m_point;
                break;
            }
        }
        return value1>value2;
    }
         break;
    case FOUR_WITH_TOW:
    {
        map<int,int> mapPointCount1;
        map<int,int> mapPointCount2;
        for(Card* c:cards1)
        {
            mapPointCount1[c->m_point]+=1;
            if(mapPointCount1[c->m_point]==4)value1 = c->m_point;
        }
        for(Card* c:cards2)
        {
            mapPointCount2[c->m_point]+=1;
            if(mapPointCount2[c->m_point]==4)value2= c->m_point;
        }
        return value1>value2;
    }
         break;
    case FOUR_WITH_TWO_PAIR:
    {
        map<int,int> mapPointCount1;
        map<int,int> mapPointCount2;
        for(Card* c:cards1)
        {
            mapPointCount1[c->m_point]+=1;
            if(mapPointCount1[c->m_point]==4)value1 = c->m_point;
        }
        for(Card* c:cards2)
        {
            mapPointCount2[c->m_point]+=1;
            if(mapPointCount2[c->m_point]==4)value2= c->m_point;
        }
        return value1>value2;
    }
         break;
    case BOMB:
        return cards1.at(0)->m_point>cards2.at(0)->m_point;
         break;
    }

}

bool Rulers::canBeat(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    //能不能管
    return compareCards(cardInHand,cardLastPlayer);
}

bool Rulers::canPlayCards(QList<Card *> &cardInHand, QList<Card *> &cardLastPlayer)
{
    //牌权在不在自己手里 cardLastPlayer.size() ==0 此时只需要符合牌型就可以
    //牌权不在自己手里 管的上才能出
    if(cardLastPlayer.size()==0)
    {
        return CARDTYPE_NONE != getCardType(cardInHand);
    }
    return canBeat(cardInHand,cardLastPlayer);

}
