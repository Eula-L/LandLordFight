#include "card.h"
#include "ui_card.h"
QImage Card::m_img =QImage(":/image/card.png");

Card::Card(int point,int suit,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
    init(point,suit);
}

Card::Card(int num, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
    //根据数学规律初始化
    //0-51 number%13是点数 number/13是花色
    //52 小王
    //53 大王
    if(num == 52)
    {
        init(Card_SmallKing,Lucency);
    }
    else if(num == 53)
    {
        init(Card_BigKing,Lucency);
    }
    else
    {
        init(num%13,num/13);
    }
}

Card::~Card()
{
    delete ui;
}

void Card::setSelected()
{
    m_isClicked =true;
}

void Card::setUnSelected()
{
    m_isClicked =false;
}

void Card::mousePressEvent(QMouseEvent *event)
{
    m_isClicked = !m_isClicked;
}

void Card::setCardPositive(bool flag)
{
    m_isPositive = flag;
}

void Card::slot_moveUp()
{
    //上升
    //1、获取当前牌的位置
    QRect rect = this->geometry();//获取：什么位置，多高多宽
    int x =rect.x();
    int y = rect.y()-CARD_UP_DISTANCE;
    this->move(x,y);
}

void Card::init(int point, int suit)
{
    m_point = point;
    m_suit = suit;
    m_isClicked =false;
    m_isPositive =false;
}
#include <QPainter>
//绘图事件
void Card::paintEvent(QPaintEvent *event)
{
    //创建绘图对象，想画谁，就传谁的地址
    QPainter paint(this);
    int x=0;
    int y=0;
    if(m_isPositive)
    {
        if(m_point == Card_SmallKing)
        {
            x=0;
            y=4;
        }
        else if(m_point == Card_BigKing)
        {
            x=1;
            y=4;
        }
        else
        {
            x=m_point;
            y=m_suit;
        }

    }
    else
    {
        //反面
        x=2;
        y=4;

    }
    paint.drawImage(0,0,m_img,
                    x*Card_Width,y*Card_Height,
                    Card_Width,Card_Height);
    paint.end();

}
