#include "aiplaycard.h"
#include"rulers.h"

int AIPlayCard::findSmallestCards(QList<Card *> &card)
{
    //在选牌之前要将所有牌设置成未选中
    for(Card*c:card)
    {
        c->setUnSelected();
    }

    //优先级 最高 先出小牌 能够带出更多牌的牌型组合
    //顺子 》 连队 》 飞机带翅膀 》 飞机 》 三代二 》 三带一 》三张 》 对子 》单张 》炸弹 》王炸
    int selected=0;
    selected=findStraight(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findStraightPair(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findPlanWithPair(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findPlanWithOne(card);
    if(selected!=0)
    {
        return selected;
    }

    selected=findPlan(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findTripleWithPair(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findTripleWithOne(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findTriple(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findPair(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findSignal(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findBomb(card,-1);
    if(selected!=0)
    {
        return selected;
    }
    selected=findKingBomb(card);
    if(selected!=0)
    {
        return selected;
    }
    selected=findSmallestCards(card);
    if(selected!=0)
    {
        return selected;
    }
}

int AIPlayCard::findStraight(QList<Card *> &card)
{
    //从手牌中找最小最长顺子
    map<int,Card*> mapPointToCard;//用于去重
    //去重
    for(Card*c:card)
    {
        if(c->m_point==Card_2||c->m_point==Card_BigKing||
                c->m_point==Card_SmallKing)continue;
        mapPointToCard[c->m_point]=c;
    }
    //map里存的就是从小到大的排序
    vector<int> vec;
    for(pair<int,Card*> p:mapPointToCard)
    {
        vec.push_back(p.first);
    }
    int n=vec.size();
    if(n<5)return 0;

    int maxLen=0;
    int count=1;
    int begin=vec[0];//顺子其实第一张牌
    //去识别一个范围
    vector<int> vecBeginToEnd(2,0);  //定义了2个整型元素的向量,且给出每个元素的初值为0
    //做标记
    //有比maxLen长的就更新 满足一个比一个大1
    for(int i=0;i<n-1;i++)
    {
        if(vec[i+1]-vec[i]==1)
        {
            count++;
        }
        else//出现不连续
        {
            if(count>=5&&count>maxLen)
            {
                maxLen=count;
                vecBeginToEnd=vector<int>{begin,vec[i]};
            }
            begin=vec[i+1];
            count=1;
        }
    }
    if(count>=5&&count>maxLen)
    {
        maxLen=count;
        vecBeginToEnd=vector<int>{begin,vec[n-1]};
    }
    //找到了最长顺子
    //标记被选中
    if(maxLen!=0)
    {
        for(int i=vecBeginToEnd[0];i<=vecBeginToEnd[1];i++)
        {
            //从map中取 不从card中取牌 因为map去重了
            Card* c=mapPointToCard[i];
            c->setSelected();
        }
    }
    return maxLen;
}

int AIPlayCard::findStraightPair(QList<Card *> &card)
{
    //查找最长最小的连队 连队不能有2

    //map统计个数
    map<int,int> mapPointToCount;//用于统计个数
    //去重
    for(Card*c:card)
    {
        if(c->m_point==Card_2)continue;//王只会出现一次，可以不过滤
        mapPointToCount[c->m_point]+=1;
    }
    //vec装 个数 >=2的点数
    vector<int> vec;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second>=2)//如果考虑不拆炸弹 个数使用2，3
        vec.push_back(p.first);
    }
    if(vec.size()<=3)return 0;
    int count=1;
    int begin=vec[0];
    vector<int> vecBeginToEnd(2,0);//连队point的范围
    int maxlen=0;
    //看vec 连续的数 同上
    for(int i=0;i<vec.size()-1;i++)
    {
        if(vec[i+1]-vec[i]==1)
        {
            count++;
        }
        else
        {
            if(count>=3&&maxlen<count)
            {
                maxlen=count;
                vecBeginToEnd={begin,vec[i]};
            }
            begin=vec[i+1];
            count=1;
        }
    }
    if(count>=3&&maxlen<count)
    {
        maxlen=count;
        vecBeginToEnd={begin,vec[vec.size()-1]};
    }
    //标记牌
    int twocount=0;
    int pos=vecBeginToEnd[1];
    if(maxlen!=0)
    {
        //牌一定是[vecBeginToEnd[0] vecBeginToEnd[1]] 范围
        //但是牌 不一定是2个 可能是3个4个
        //选牌的时候要看个数
        for(Card*c:card)//card是从大到小排序的
        {
            if(c->m_point>=vecBeginToEnd[0]&&c->m_point<=vecBeginToEnd[1])
            {
                //选两个
                if(c->m_point==pos)
                    twocount++;
                else
                {
                    pos--;
                    twocount=1;
                }
                if(twocount<=2)//==,解决
                {
                    c->setSelected();
                }
            }
        }
    }
    return maxlen*2;
}

int AIPlayCard::findPlanWithOne(QList<Card *> &card)
{
    //飞机不能出现2
    //统计个数 要个数 找三和一
    //首先统计个数
    map<int,int> mapPointToCount;//用于统计个数
    for(Card*c:card)
    {
        if(c->m_point==Card_2||c->m_point==Card_BigKing||
                c->m_point==Card_SmallKing)continue;//单张不能带大小王和2
        mapPointToCount[c->m_point]+=1;
    }
    //判断个数为3 和1 的加入vec
    vector<int> vec;
    vector<int> vecSingle;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3)//如果考虑不拆炸弹 个数使用 3
            vec.push_back(p.first);
        if(p.second==1)             //如果考虑不拆炸弹 个数使用 3
            vecSingle.push_back(p.first);
    }
    if(vec.size()<2||vecSingle.size()<2)return 0;
    for(int i=0;i<vec.size()-1;i++)
    {
        if(vec[i]+1==vec[i+1])//找到了
        {
            //选中标记
            for(Card* c:card)
            {
                if(c->m_point==vec[i]||c->m_point==vec[i+1]||
                        c->m_point==vecSingle[0]||c->m_point==vecSingle[1])
                    //带最小的单张牌，为下标 0 1
                    c->setSelected();
            }
            return 8;
        }
    }
    return 0;
}

int AIPlayCard::findPlanWithPair(QList<Card *> &card)
{
    //飞机不能出现2
    //统计个数 要个数 找三和二
    //首先统计个数
    map<int,int> mapPointToCount;//用于统计个数
    for(Card*c:card)
    {
        if(c->m_point==Card_2||c->m_point==Card_BigKing||
                c->m_point==Card_SmallKing)continue;//单张不能带大小王和2
        mapPointToCount[c->m_point]+=1;
    }
    //判断个数为3 和1 的加入vec
    vector<int> vec;
    vector<int> vecPair;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3)             //如果考虑不拆炸弹 个数使用 3
            vec.push_back(p.first);
        if(p.second==2)             //对子
            vecPair.push_back(p.first);
    }
    if(vec.size()<2||vecPair.size()<2)return 0;
    for(int i=0;i<vec.size()-1;i++)
    {
        if(vec[i]+1==vec[i+1])//找到了
        {
            //选中标记
            for(Card* c:card)
            {
                if(c->m_point==vec[i]||c->m_point==vec[i+1]||
                        c->m_point==vecPair[0]||c->m_point==vecPair[1])
                    //带最小的单张牌，为下标 0 1
                    c->setSelected();
            }
            return 10;
        }
    }
    return 0;
}

int AIPlayCard::findPlan(QList<Card *> &card)
{
    //飞机不能出现2
    //飞机 二连三张
    //不拆炸弹
    //首先统计个数
    map<int,int> mapPointToCount;//用于统计个数
    for(Card*c:card)
    {
        if(c->m_point==Card_2)continue;//王只会出现一次，可以不过滤
        mapPointToCount[c->m_point]+=1;
    }
    //判断个数为3的 加入vec
    vector<int> vec;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3)//如果考虑不拆炸弹 个数使用 3
        vec.push_back(p.first);
    }

    //遍历数组 两个挨着的值差1 就找到了
    int n=vec.size();
    if(n<2)return 0;
    for(int i=0;i<n-1;i++)
    {
        if(vec[i+1]==vec[i]+1)//找到了
        {
            //选中标记
            for(Card* c:card)
            {
                if(c->m_point==vec[i]||c->m_point==vec[i+1])
                    c->setSelected();
            }
            return 6;
        }
    }
    return 0;
}

int AIPlayCard::findTripleWithOne(QList<Card *> &card)
{
    //找最小单张
    //智能选牌
    //牌多的时候 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(card.size()>6&&c->m_point==Card_2)continue;
        mapPointToCount[c->m_point]++;
    }
    int triple=-1;
    int one=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&triple==-1)
            triple=p.first;
        if(p.second==1&&one==-1)
            one=p.first;
        if(triple!=-1&&one!=-1) break;
    }
    if(triple==-1)return 0;
    if(one==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==triple||c->m_point==one)
            c->setSelected();
    }
    return 4;
}

int AIPlayCard::findTripleWithPair(QList<Card *> &card)
{
    //找最小单张
    //智能选牌
    //牌多的时候 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(card.size()>6&&c->m_point==Card_2)continue;
        mapPointToCount[c->m_point]++;
    }
    int triple=-1;
    int two=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&triple==-1)
            triple=p.first;
        if(p.second==2&&two==-1)
            two=p.first;
        if(triple!=-1&&two!=-1) break;
    }
    if(triple==-1)return 0;
    if(two==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==triple||c->m_point==two)
            c->setSelected();
    }
    return 5;
}

int AIPlayCard::findTriple(QList<Card *> &card)
{
    //智能选牌
    //牌多的时候 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(card.size()>6&&c->m_point==Card_2)continue;
        mapPointToCount[c->m_point]++;
    }
    int triple=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&triple==-1)
            triple=p.first;
        if(triple!=-1) break;
    }
    if(triple==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==triple)
            c->setSelected();
    }
    return 3;
}

int AIPlayCard::findPair(QList<Card *> &card)
{
    //找最小的
    //智能选牌 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(c->m_point==Card_2)continue;
        mapPointToCount[c->m_point]++;
    }
    int two=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==2&&two==-1)
            two=p.first;
        if(two!=-1) break;
    }
    if(two==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==two)
            c->setSelected();
    }
    return 2;
}

int AIPlayCard::findSignal(QList<Card *> &card)
{
    //真 单张  个数为1的牌
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(c->m_point==Card_SmallKing||c->m_point==Card_BigKing)continue;
        mapPointToCount[c->m_point]++;
    }
    int one=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==1&&one==-1)
            one=p.first;
        if(one!=-1) break;
    }
    if(one==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==one)
            c->setSelected();
    }
    return 1;
}

int AIPlayCard::findBomb(QList<Card *> &card, int value)
{
    //选最小的  找大于value的 如果是-1 是任意一个
    //智能选牌
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        //if(card.size()>6/*&&c->m_point==Card_2*/)continue;//
        if(c->m_point>value)
            mapPointToCount[c->m_point]++;//2也要出
    }
    int bomb=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==4&&bomb==-1)
            bomb=p.first;
        if(bomb!=-1) break;
    }
    if(bomb==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==bomb)
            c->setSelected();
    }
    return 4;
}

int AIPlayCard::findKingBomb(QList<Card *> &card)
{
    //card 排好序的 大到小
    if(card.size()>=2)return 0;
    if(card.at(0)->m_point==Card_BigKing&&card.at(1)->m_point==Card_SmallKing)
    {
        card.at(0)->setSelected();
        card.at(1)->setSelected();
        return 2;
    }
    return 0;
}

int AIPlayCard::findSmallestSingle(QList<Card *> &card)
{
    //假单张 出最右边的牌
    if(card.size()==0)return 0;
    card.back()->setSelected();
    return 1;
}

/////////////////////////管牌////////////

QList<Card *> AIPlayCard::BeatCards(QList<Card *> cardInHand, QList<Card *> &cardsLastPlayer)
{
    //总的情况

    //智能选派 智能管牌 在一起
    QList<Card*> cards;
    int selected=0;
    //在选牌之前要将所有牌设置为未选中
    for(Card* card:cardInHand)
    {
        card->setUnSelected();
    }
    //如果 cardsLastPlayer当前是电脑的牌权，电脑智能选牌
    if(cardsLastPlayer.size()==0)
        findSmallestCards(cardInHand);
    else
    {
        //要管牌

        //如果是王炸 返回空
        if(KING_BOMB==Rulers::getCardType(cardsLastPlayer))return cards;
        //相同类型管牌
        selected=findBeatSameType(cardInHand,cardsLastPlayer);

        //管不了
        //看有没有炸弹
            //上一个有没有炸弹
            //没有选这个炸弹
        //没有炸弹
        //看有没有王炸
        //没有就是要不起
        if(selected==0)
        {
            if(BOMB==Rulers::getCardType(cardsLastPlayer))
            {
                selected=findBomb(cardInHand,cardsLastPlayer.back()->m_point);
            }
            else
            {
                selected=findBomb(cardInHand,-1);//找任意炸弹
            }
            if(selected==0)
            {
                selected=findKingBomb(cardInHand);
                //要不起
                if(selected==0)
                    return cards;
            }
        }

    }
    //cards里面添加选中的
    for(Card* card:cardInHand)
    {
        if(card->m_isClicked)
            cards.append(card);
    }
    return cards;
}

int AIPlayCard::findBeatSameType(QList<Card *> cardInHand, QList<Card *> &cardsLastPlayer)
{
    int type=Rulers::getCardType(cardsLastPlayer);
    int Selected=0;
    switch(type)
    {
    case CARDTYPE_NONE:
        Selected=0;
        break;
    case SINGLE:
        Selected=findSignal(cardInHand,cardsLastPlayer.front()->m_point);
    break;
    case PAIR:
        Selected=findPair(cardInHand,cardsLastPlayer.front()->m_point);
    break;
    case TRIPLE:
        Selected=findPair(cardInHand,cardsLastPlayer.front()->m_point);
    break;
    case TRIPLE_WITH_ONE:
    {
        //找哪个三张
        int point=0;
        map<int,int> mapPointToCount;
        for(Card* c:cardsLastPlayer)
        {
            mapPointToCount[c->m_point]++;//2也要出
        }
        int bomb=-1;
        for(pair<int,int> p:mapPointToCount)
        {
            if(p.second==3)
            {
               point=p.first;
               break;
            }
        }
        Selected=findTripleWithOne(cardInHand,point);
    }
    break;
    case TRIPLE_WITH_PAIR:
    {
        //找哪个三张
        int point=0;
        map<int,int> mapPointToCount;
        for(Card* c:cardsLastPlayer)
        {
            mapPointToCount[c->m_point]++;//2也要出
        }
        for(pair<int,int> p:mapPointToCount)
        {
            if(p.second==3)
            {
               point=p.first;
               break;
            }
        }
        Selected=findTripleWithPair(cardInHand,point);
    }
    break;
    case BOMB:
        //炸弹放外面管
        Selected=0;
    break;
    case STRAIGHT:
        Selected=findStraight(cardInHand,cardsLastPlayer.back()->m_point,cardsLastPlayer.size());
        break;
    case STRAIGHT_PAIR:
        Selected=findStraightPair(cardInHand,cardsLastPlayer.back()->m_point,cardsLastPlayer.size()/2);
        break;
    case PLANE://连续两个三张
        Selected=findPlan(cardInHand,cardsLastPlayer.back()->m_point);
        break;
    case PLANT_WITH_WING://判断是带两张单牌还是两对
    {
        //找哪个三张
        int point=0;
        map<int,int> mapPointToCount;
        for(Card* c:cardsLastPlayer)
        {
            mapPointToCount[c->m_point]++;//2也要出
        }
        vector<int> vec;
        vector<int> vecSingle;
        vector<int> vecTwo;
        for(pair<int,int> p:mapPointToCount)
        {
            if(p.second==3)
            {
               vec.push_back(p.first);
            }
            if(p.second==2)
            {
               vecSingle.push_back(p.first);
            }
            if(p.second==1)
            {
               vecTwo.push_back(p.first);
            }
        }
        if(vecTwo.size()==0)//带单张
            Selected=findPlanWithOne(cardInHand,vec.front());
        else
            Selected=findPlanWithPair(cardInHand,vecTwo.front());

        break;
    }
    case KING_BOMB:
        Selected=0;
    break;
    }
    return Selected;
}

int AIPlayCard::findStraight(QList<Card *> &card, int point, int len)
{
    //找等长的 最右边一张的点数大于point 最小顺子
    map<int,Card*> mapPointToCard;//用于去重
    //去重
    for(Card*c:card)
    {
        if(c->m_point==Card_2||c->m_point==Card_BigKing||
                c->m_point==Card_SmallKing)continue;
        if(c->m_point>point)
            mapPointToCard[c->m_point]=c;
    }
    //map里存的就是从小到大的排序
    vector<int> vec;
    for(pair<int,Card*> p:mapPointToCard)
    {
        vec.push_back(p.first);
    }
    int n=vec.size();
    if(n<len)return 0;

    int count=1;
    int begin=vec[0];//顺子其实第一张牌
    //去识别一个范围
    vector<int> vecBeginToEnd(2,0);  //定义了2个整型元素的向量,且给出每个元素的初值为0
    //做标记
    //有比maxLen长的就更新 满足一个比一个大1
    for(int i=0;i<n-1;i++)
    {
        if(vec[i+1]-vec[i]==1)
        {
            count++;
            if(count==len)
            {
                vecBeginToEnd=vector<int>{begin,begin+len-1};
                //找到然后标记
                for(int i=vecBeginToEnd[0];i<=vecBeginToEnd[1];i++)
                {
                    Card*c=mapPointToCard[i];
                    c->setSelected();
                }
                return len;
            }
        }
        else//出现不连续
        {
            begin=vec[i+1];
            count=1;
        }
    }
    return 0;
}

int AIPlayCard::findStraightPair(QList<Card *> &card, int point, int len)
{
    //查找最长最小的连队 连队不能有2

    //map统计个数
    map<int,int> mapPointToCount;//用于统计个数
    //去重
    for(Card*c:card)
    {
        if(c->m_point==Card_2)continue;//王只会出现一次，可以不过滤
        if(c->m_point>point)
        mapPointToCount[c->m_point]+=1;
    }
    //vec装 个数 >=2的点数
    vector<int> vec;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second>=2)//如果考虑不拆炸弹 个数使用2，3
        vec.push_back(p.first);
    }
    if(vec.size()<len)return 0;
    int count=1;
    int begin=vec[0];
    vector<int> vecBeginToEnd(2,0);//连队point的范围
    //看vec 连续的数 同上
    for(int i=0;i<vec.size()-1;i++)
    {
        if(vec[i+1]-vec[i]==1)
        {
            count++;
            if(count==len)
            {
                vecBeginToEnd=vector<int>{begin,begin+len-1};
                //标记牌
                int twocount=0;
                int pos=vecBeginToEnd[1];
                //牌一定是[vecBeginToEnd[0] vecBeginToEnd[1]] 范围
                //但是牌 不一定是2个 可能是3个4个
                //选牌的时候要看个数
                for(Card*c:card)//card是从大到小排序的
                {
                    if(c->m_point>=vecBeginToEnd[0]&&c->m_point<=vecBeginToEnd[1])
                    {
                        //选两个
                        if(c->m_point==pos)
                            twocount++;
                        else
                        {
                            pos--;
                            twocount=1;
                        }
                        if(twocount<=2)//==,解决
                        {
                            c->setSelected();
                        }
                    }
                    return len;
                }
            }
        }
        else
        {
            begin=vec[i+1];
            count=1;
        }
    }
    return 0;
}

int AIPlayCard::findPlanWithOne(QList<Card *> &card, int point)
{
    //飞机不能出现2
    //统计个数 要个数 找三和一
    //首先统计个数
    if(card.size()<10)return 0;
    map<int,int> mapPointToCount;//用于统计个数
    for(Card*c:card)
    {
        if(card.at(0)->m_point==Card_BigKing&&card.at(1)->m_point==Card_SmallKing)
        {
            //王炸的时候 大小王要跳过去
            if(c->m_point==Card_BigKing||
                c->m_point==Card_SmallKing)continue;//单张不能带大小王和2
            mapPointToCount[c->m_point]+=1;
        }
    }
    //判断个数为3 和1 的加入vec
    vector<int> vec;
    vector<int> vecSingle;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&p.first>point)//如果考虑不拆炸弹 个数使用 3
            vec.push_back(p.first);
        if(p.second==1)             //如果考虑不拆炸弹 个数使用 3
            vecSingle.push_back(p.first);
    }
    if(vec.size()<2||vecSingle.size()<2)return 0;
    for(int i=0;i<vec.size()-1;i++)
    {
        if(vec[i]+1==vec[i+1])//找到了
        {
            //选中标记
            for(Card* c:card)
            {
                if(c->m_point==vec[i]||c->m_point==vec[i+1]||
                        c->m_point==vecSingle[0]||c->m_point==vecSingle[1])
                    //带最小的单张牌，为下标 0 1
                    c->setSelected();
            }
            return 10;
        }
    }
    return 0;
}

int AIPlayCard::findPlanWithPair(QList<Card *> &card, int point)
{
    //飞机不能出现2
    //统计个数 要个数 找三和一
    //首先统计个数
    if(card.size()<8)return 0;
    map<int,int> mapPointToCount;//用于统计个数
    for(Card*c:card)
    {
        //王炸的时候 大小王要跳过去
        if(c->m_point==Card_BigKing||
            c->m_point==Card_SmallKing)continue;//单张不能带大小王和2

        mapPointToCount[c->m_point]+=1;
    }
    //判断个数为3 和1 的加入vec
    vector<int> vec;
    vector<int> vecTwo;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&p.first>point)//如果考虑不拆炸弹 个数使用 3
            vec.push_back(p.first);
        if(p.second==1)             //如果考虑不拆炸弹 个数使用 3
            vecTwo.push_back(p.first);
    }
    if(vec.size()<2||vecTwo.size()<2)return 0;
    for(int i=0;i<vec.size()-1;i++)
    {
        if(vec[i]+1==vec[i+1])//找到了
        {
            //选中标记
            for(Card* c:card)
            {
                if(c->m_point==vec[i]||c->m_point==vec[i+1]||
                        c->m_point==vecTwo[0]||c->m_point==vecTwo[1])
                    //带最小的单张牌，为下标 0 1
                    c->setSelected();
            }
            return 8;
        }
    }
    return 0;
}

int AIPlayCard::findPlan(QList<Card *> &card, int point)
{
    //飞机不能出现2
    //飞机 二连三张
    //不拆炸弹
    //首先统计个数
    map<int,int> mapPointToCount;//用于统计个数
    for(Card*c:card)
    {
        if(c->m_point==Card_2)continue;//王只会出现一次，可以不过滤
        if(c->m_point>point)
            mapPointToCount[c->m_point]+=1;
    }
    //判断个数为3的 加入vec
    vector<int> vec;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3)//如果考虑不拆炸弹 个数使用 3
        vec.push_back(p.first);
    }

    //遍历数组 两个挨着的值差1 就找到了
    int n=vec.size();
    if(n<2)return 0;
    for(int i=0;i<n-1;i++)
    {
        if(vec[i+1]==vec[i]+1)//找到了
        {
            //选中标记
            for(Card* c:card)
            {
                if(c->m_point==vec[i]||c->m_point==vec[i+1])
                    c->setSelected();
            }
            return 6;
        }
    }
    return 0;
}

int AIPlayCard::findTripleWithOne(QList<Card *> &card, int point)
{
    //找最小单张
    //智能选牌
    //牌多的时候 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        mapPointToCount[c->m_point]++;
    }
    int triple=-1;
    int one=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&triple==-1&&p.first>point)
            triple=p.first;
        if(p.second==1&&one==-1)
            one=p.first;
        if(triple!=-1&&one!=-1) break;
    }
    if(triple==-1)return 0;
    if(one==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==triple||c->m_point==one)
            c->setSelected();
    }
    return 4;
}

int AIPlayCard::findTripleWithPair(QList<Card *> &card, int point)
{
    //找最小单张
    //智能选牌
    //牌多的时候 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        mapPointToCount[c->m_point]++;
    }
    int triple=-1;
    int two=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&triple==-1&&p.first>point)
            triple=p.first;
        if(p.second==2&&two==-1)
            two=p.first;
        if(triple!=-1&&two!=-1) break;
    }
    if(triple==-1)return 0;
    if(two==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==triple||c->m_point==two)
            c->setSelected();
    }
    return 5;
}

int AIPlayCard::findTriple(QList<Card *> &card, int point)
{
    //智能选牌
    //牌多的时候 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(c->m_point>point)
        mapPointToCount[c->m_point]++;
    }
    int triple=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==3&&triple==-1)
            triple=p.first;
        if(triple!=-1) break;
    }
    if(triple==-1)return 0;
    for(Card* c:card)
    {
        if(c->m_point==triple)
            c->setSelected();
    }
    return 3;
}

int AIPlayCard::findPair(QList<Card *> &card, int point)
{
    //找最小的
    //智能选牌 不考虑出2
    //统计个数
    map<int,int> mapPointToCount;
    for(Card* c:card)
    {
        if(c->m_point>point)
        mapPointToCount[c->m_point]++;
    }
    int two=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==2&&two==-1)
            two=p.first;
        if(two!=-1) break;
    }
    //出牌是先三张 再两张 管牌是同类型 222
    //没有能管的对子 拆三张和四张的2去管
    if(two==-1)
    {
        if(point<Card_2&&(mapPointToCount.count(Card_2)==3||
                mapPointToCount.count(Card_2)==4))
        {
            int _count=0;
            for(Card* c:card)
            {
                if(c->m_point==Card_2)
                {
                    c->setSelected();
                    _count++;
                }
                if(_count>=2)
                    return 2;
            }
        }
        return 0;
    }
    for(Card* c:card)
    {
        if(c->m_point==two)
            c->setSelected();
    }
    return 2;
}

int AIPlayCard::findSignal(QList<Card *> &card, int point)
{
    //如果手里的是顺子 todo 需要把顺子移除掉 然后看有没有能管的牌
    //创建牌组副本
    QList<Card *> newCards=card;//复制一份牌，改变 改变复制的牌  //浅拷贝
    if(card.size()>=5)
    {
        while(removeStraight(newCards));
    }
    //真 单张  个数为1的牌
    map<int,int> mapPointToCount;
    for(Card* c:newCards)
    {
        if(c->m_point>point)
        mapPointToCount[c->m_point]++;
    }
    int one=-1;
    for(pair<int,int> p:mapPointToCount)
    {
        if(p.second==1&&one==-1)
            one=p.first;
        if(one!=-1) break;
    }
    if(one==-1)
    {
        //没找到单牌 看有没有2 有2 用2管
        if(point<Card_2)
        {
            for(Card*c:newCards)
            {
                if(c->m_point==Card_2)
                {
                    c->setSelected();
                    return 1;
                }
            }
        }
        return 0;
    }
    for(Card* c:newCards)
    {
        if(c->m_point==one)
            c->setSelected();
    }
    return 1;
}

bool AIPlayCard::removeStraight(QList<Card *> &cards)
{
    //从手牌中移除顺子
    //从手牌中找最小最长顺子
    map<int,Card*> mapPointToCard;//用于去重
    //去重
    for(Card*c:cards)
    {
        if(c->m_point==Card_2||c->m_point==Card_BigKing||
                c->m_point==Card_SmallKing)continue;
        mapPointToCard[c->m_point]=c;
    }
    //map里存的就是从小到大的排序
    vector<int> vec;
    for(pair<int,Card*> p:mapPointToCard)
    {
        vec.push_back(p.first);
    }
    int n=vec.size();
    if(n<5)return false;

    int maxLen=0;
    int count=1;
    int begin=vec[0];//顺子其实第一张牌
    //去识别一个范围
    vector<int> vecBeginToEnd(2,0);  //定义了2个整型元素的向量,且给出每个元素的初值为0
    //做标记
    //有比maxLen长的就更新 满足一个比一个大1
    for(int i=0;i<n-1;i++)
    {
        if(vec[i+1]-vec[i]==1)
        {
            count++;
        }
        else//出现不连续
        {
            if(count>=5)
            {
                vecBeginToEnd=vector<int>{begin,vec[i]};
                //移除原来的顺子
                for(int j=vecBeginToEnd[1];j>=vecBeginToEnd[0];j--)
                {
                    Card*card=mapPointToCard[j];
                    for(auto ite=cards.begin();ite!=cards.end();)
                    {
                        if(card==*ite)
                        {
                            ite=cards.erase(ite);
                            break;
                        }
                        else
                            ite++;
                    }
                }
                return true;
            }
            begin=vec[i+1];
            count=1;
        }
    }
    if(count>=5)
    {
        vecBeginToEnd=vector<int>{begin,vec[n-1]};
        //移除原来的顺子
        for(int j=vecBeginToEnd[1];j>=vecBeginToEnd[0];j--)
        {
            Card*card=mapPointToCard[j];
            for(auto ite=cards.begin();ite!=cards.end();)
            {
                if(card==*ite)
                {
                    ite=cards.erase(ite);
                    break;
                }
                else
                    ite++;
            }
        }
        return true;
    }

    return false;
    //找到顺子
    //找到就返回真
}

