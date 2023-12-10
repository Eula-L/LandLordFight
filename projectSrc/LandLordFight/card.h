#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <qDebug>
namespace Ui {
class Card;
}

//牌点数枚举
#define CardPoint_Begin Card_3
enum CardPoint{
    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,
    Card_SmallKing,
    Card_BigKing,

    CardPoint_End
};
//牌花色枚举
#define CardSuit_Begin Diamond
enum CardSuit{
    //方片
    Diamond,
    //梅花
    Club,
    //红桃
    Heart,
    //黑桃
    Spade,
    //无花色，大小王
    Lucency,

    CardSuit_End
};

//画图尺寸
#define Card_Width (80)
#define Card_Height (105)
#define CARD_UP_DISTANCE (20)//牌点击后，升起的高度
#define CARD_SHOW_WIDTH (25)//牌之间重叠摆放，露出来的部分
//牌类
class Card : public QWidget
{
    Q_OBJECT

public:
    explicit Card(int point,int suit, QWidget *parent = nullptr);
    //数字初始化牌
    //按照3-K,A,2,花色*4
    explicit Card(int num, QWidget *parent = nullptr);
    ~Card();
    //设置是否选择
    void setSelected();
    void setUnSelected();
    //设置鼠标点击
    void mousePressEvent(QMouseEvent *event);
    //设置正反面
    void setCardPositive(bool flag);
    //牌上移
    void slot_moveUp();

private:
    Ui::Card *ui;
    void init(int point,int suit);
    //用来存总的图片，不用每次绘制都加载
    static QImage m_img;
    //绘制 --绘图事件
    void paintEvent(QPaintEvent *event);

public:
    //正反面
    bool m_isPositive = false;
    //是否点击
    bool m_isClicked = false;
    //花色
    int m_suit;
    //点数
    int m_point;
};

#endif // CARD_H
