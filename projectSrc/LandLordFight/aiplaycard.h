#ifndef AIPLAYCARD_H
#define AIPLAYCARD_H
#include<card.h>

//电脑出牌类：分为智能选牌（当前电脑是最大牌权，随意出牌）  智能管牌（管其他人的牌）

//策略（全是静态方法）类

//智能选牌：电脑比如有17张牌，优先什么牌型出牌？
//优先级 最高 先出小牌 能够带出更多牌的牌型组合
//顺子 》 连队 》 飞机带翅膀 》 飞机 》 三带一 》 三代二 》三张 》 对子 》单张 》炸弹 》王炸
//带牌的时候，需要考虑2

//智能管牌：相同牌型 优先去找 然后管 ，然后没有考虑炸弹 然后王炸   管牌 优先最小的
//农民之间可能不管牌
using namespace std;

class AIPlayCard
{
public:
    ////////智能选牌//////
    //查找最小的牌 用于只能选牌
    static int findSmallestCards(QList<Card*>& card);
    //查找顺子 int 返回和一知道顺子长度
    static int findStraight(QList<Card*>& card);
    //查找连队
    static int findStraightPair(QList<Card*>& card);
    //查找飞机带翅膀之单张
    static int findPlanWithOne(QList<Card*>& card);
    //查找飞机带翅膀之对子
    static int findPlanWithPair(QList<Card*>& card);
    //查找飞机
    static int findPlan(QList<Card*>& card);
    //查找三带一
    static int findTripleWithOne(QList<Card*>& card);
    //查找三带二
    static int findTripleWithPair(QList<Card*>& card);
    //查找三张
    static int findTriple(QList<Card*>& card);
    //查找对子
    static int findPair(QList<Card*>& card);
    //查找单张
    static int findSignal(QList<Card*>& card);
    //查找炸弹  找> value 的炸弹  -1 找任意炸弹
    static int findBomb(QList<Card*>& card,int value);

    //查找王炸
    static int findKingBomb(QList<Card*>& card);

    //找最小单张 既最右侧那张
    static int findSmallestSingle(QList<Card*>& card);

    /////智能管牌//////
    //管牌函数
    static QList<Card*> BeatCards(QList<Card*>cardInHand,
                                  QList<Card*>&cardsLastPlayer);
    //找能管的牌 按照相同类型找 相同数量找， 然后 找炸弹 王炸，然后是要不起
    static int findBeatSameType(QList<Card*>cardInHand,
                                  QList<Card*>&cardsLastPlayer);

    //查找顺子 顺子传最小那张
    static int findStraight(QList<Card*>& card,int point,int len);
    //查找连队
    static int findStraightPair(QList<Card*>& card,int point,int len);
    //查找飞机带翅膀之单张
    static int findPlanWithOne(QList<Card*>& card, int point);
    //查找飞机带翅膀之对子
    static int findPlanWithPair(QList<Card*>& card, int point);
    //查找飞机
    static int findPlan(QList<Card*>& card, int point);
    //查找三带一
    static int findTripleWithOne(QList<Card*>& card, int point);
    //查找三带二
    static int findTripleWithPair(QList<Card*>& card, int point);
    //查找三张
    static int findTriple(QList<Card*>& card, int point);
    //查找对子
    static int findPair(QList<Card*>& card, int point);
    //查找单张
    static int findSignal(QList<Card*>& card, int point);
    //移除顺子
    static bool removeStraight(QList<Card*>&cards);

};

#endif // AIPLAYCARD_H
