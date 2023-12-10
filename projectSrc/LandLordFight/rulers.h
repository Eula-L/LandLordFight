#ifndef RULERS_H
#define RULERS_H

#include<card.h>
#include<map>
#include<stack>
#include<qpair.h>
using namespace std;
//牌型
enum CARD_TYPE{
    CARDTYPE_NONE,//啥也不是

    SINGLE,//单张

    PAIR,//对子

    TRIPLE,//三张

    TRIPLE_WITH_ONE,//三带一

    TRIPLE_WITH_PAIR,//三带二
    STRAIGHT,//顺子  五个开始的连线 根据长度判断是否管牌 1.长度相等 2.看最大或最小的

    STRAIGHT_PAIR,//连对  三个开始的对子连线 根据长度判断是否管牌 1.长度相等 2.看最大或最小的

    PLANE,//飞机

    PLANT_WITH_WING,//飞机带翅膀（两组三张带两个单张或或两对）（此次只实现两组的）

    FOUR_WITH_TOW,//四代二

    FOUR_WITH_TWO_PAIR,//四代两对

    BOMB,//炸弹

    KING_BOMB//王炸
    //补充牌型

};

//方法类 ：游戏规则
//表示是否可以出牌 选中的牌是否可以管牌
//主要针对玩家选择出牌


class Rulers
{
public:
    static int getCardType(QList<Card*> &card);//获得牌型(语音)
    //是不是顺子
    static bool isStraight(QList<Card*> &card);
    //是不是连对
    static bool isStiaightPair(QList<Card*> &card);
    //判断是不是飞机
    static bool isPlane(QList<Card*> &card);
    //判断是不是飞机带翅膀
    static bool isPlaneWithWing(QList<Card*> &card);
    //判断是不是四代二
    static bool isFourWithTwo(QList<Card*> &card);
    //判断是不是四代两队
    static bool isFourWithTwoPair(QList<Card*> &card);
    //比较两个牌组谁大 card1 > card2 返回真
    static bool compareCards(QList<Card*> &cards1,QList<Card*>&cards2);

    //相同类型 比较牌组谁大
    static bool compareSameCards(QList<Card*> &cards1,QList<Card*>&cards2,int type);

    //是否可以管上
    static bool canBeat(QList<Card*> &cardInHand,QList<Card*>&cardLastPlayer);

    //是否能出牌 1.选中牌是否符合规则（玩家要出牌，当前玩家最大） 2. 管别人 能否管上 判断是否能出
    static bool canPlayCards(QList<Card*> &cardInHand,QList<Card*>&cardLastPlayer);

    friend class MainDialog;

};

#endif // RULERS_H
//switch () {
//case CARDTYPE_NONE:
//    break;

//caseSINGLE:
//    break;
//casePAIR:
//    break;
//caseTRIPLE:
//    break;
//caseTRIPLE_WITH_ONE:
//    break;
//caseTRIPLE_WITH_PAIR:
//    break;
//caseSTRAIGHT:
//    break;
//caseSTRAIGHT_PAIR:
//    break;
//casePLANE:
//    break;
//casePLANT_WITH_WING:
//    break;
//caseFOUR_WITH_TOW:
//    break;
//caseFOUR_WITH_TWO_PAIR:
//    break;
//caseBOMB:
//    break;
//caseKING_BOMB:
//    break;
//}
