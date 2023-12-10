#include "maindialog.h"
#include "ui_maindialog.h"
#include <QDateTime>


MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog),m_playRound(this)
{
    qDebug()<<"MainDialog::MainDialog(QWidget *parent)";
    ui->setupUi(this);
    //最小化最大化关闭按钮
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
    //窗口标题
    this->setWindowTitle("斗地主");
    //进入开始界面
    //界面索引0
    ui->sw_page->setCurrentIndex(0);
    //设置所有背景为统一的，但是开始界面、结算界面上面有图片覆盖
    slot_setBackGround();
    qDebug()<<"//牌堆数组初始化//创建了八个管理牌的牌堆";

    //添加随机种子
    qsrand(QDateTime::currentSecsSinceEpoch());

    //牌堆数组初始化
    //创建了八个管理牌的牌堆
    for(int i=0;i<CARDLIST_TYPE_COUNT;i++)
    {
        m_cardList[i].setCardListType(i);
    }
    connect(&m_timerRefresh,SIGNAL(timeout()),
            this,SLOT(slot_refreshAllCardList()));
    m_lbPassArr[CARDLIST_LIFT_PLAYER] = ui->lb_leftPass;
    m_lbPassArr[CARDLIST_MID_PLAYER] = ui->lb_midPass;
    m_lbPassArr[CARDLIST_RIGHT_PLAYER] = ui->lb_rightPass;
    //播放背景音乐
    //CardSound::playBGM();
}

MainDialog::~MainDialog()
{
    delete ui;
}

//点击快速开始
void MainDialog::on_pb_quickStart_clicked()
{
    qDebug()<<"void MainDialog::on_pb_quickStart_clicked()";
    ui->sw_page->setCurrentIndex(1);
    slot_startOneGame();
}

//点击下一局
void MainDialog::on_pb_goHome_clicked()
{
    ui->sw_page->setCurrentIndex(1);
}

//点击结束，回到home页面
void MainDialog::on_pb_next_2_clicked()
{
    ui->sw_page->setCurrentIndex(0);
}

//出结果
void MainDialog::on_pb_test_clicked()
{
    ui->sw_page->setCurrentIndex(2);
}
#include <QPalette>
//设置背景，game界面
void MainDialog::slot_setBackGround()
{
    //调色板
    QPalette p = this->palette();
    //设置画刷 设置图片
    QPixmap pixmap(":/image/bk.png");
    p.setBrush(QPalette::Background,QBrush(pixmap));
    //设置调色板 //所有的背景都被设置成了这样，只不过另外两个上面有lable覆盖
    this->setPalette(p);

}

void MainDialog::slot_startOneGame()
{
    //初始化 回合
    m_playRound.initRound();
    slot_hideAllPass();
    qDebug()<<"void MainDialog::slot_startOneGame()";
    //隐藏出牌和叫地主
    slot_showCallLord(false);
    slot_showPlayCards(false);
    //1、创建总牌堆
    for(int i=0;i<54;i++)
    {
        //创建牌
        Card* card = new Card(i,this->ui->page_game);
        card->setCardPositive(false);
        m_cardList[CARDLIST_WHOLE].addCard(card);
    }
    //洗牌
    m_cardList[CARDLIST_WHOLE].shuffle();
    //使用定时器
    m_timerRefresh.start(1000/10);
    //总牌堆显示
    //m_cardList[CARDLIST_WHOLE].cardShow();
    //总牌堆打印
    m_cardList[CARDLIST_WHOLE].cardPrint();
    //发牌 +动画+发牌音效
    QSound sound (":/sound/xipai.wav");
    sound.play();
    //1、三家用户牌
    int i=0;
    Card* card = nullptr;
    for(i=0;i<51;i+=3)
    {
        for(int j=0;j<3;j++)
        {
            _sleep(50);
            slot_refreshAllCardList();
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);


            card = m_cardList[CARDLIST_WHOLE].getOneCard();
            //TODO：在这里可以加动画，写一个牌缓慢移动的循环的函数，不能移动太快
            m_cardList[CARDLIST_LIFT_PLAYER+j].addCard(card);
        }
    }
    _sleep(100);
    //2、地主牌
    while(i<54)
    {
        _sleep(100);
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        slot_refreshAllCardList();
        card = m_cardList[CARDLIST_WHOLE].getOneCard();
        m_cardList[CARDLIST_LORD].addCard(card);
        i++;
    }
    //排序
    //玩家手牌排序
    i=0;
    while(i<3)
    {
        m_cardList[CARDLIST_LIFT_PLAYER+i].cardSort();
        i++;
    }
    //地主牌排序
    m_cardList[CARDLIST_LORD].cardSort();
    sound.stop();//发牌音效结束

    //打印牌
    i=0;
    while(i<3)
    {
        if(i==0)
        {
            qDebug()<<"左玩家";
        }
        else if(i==1)
        {
            qDebug()<<"中间玩家";
        }
        else
        {
            qDebug()<<"右玩家";
        }
        m_cardList[CARDLIST_LIFT_PLAYER+i].cardPrint();
        i++;
    }
    m_cardList[CARDLIST_LORD].cardPrint();
    //开启叫地主
    m_playRound.decideBeginLord();
    //测试
    //m_playRound.startRound(CARDLIST_MID_PLAYER);
    //m_playRound.currentPlayer = CARDLIST_LIFT_PLAYER;
    //从左侧玩家开始
    //m_playRound.startRound(CARDLIST_LIFT_PLAYER);

}

void MainDialog::slot_refreshAllCardList()
{
    for(int i=0;i<CARDLIST_TYPE_COUNT;i++)
    {
        m_cardList[i].cardShow();
    }

}


void MainDialog::on_pb_playCard_clicked()
{
    m_playRound.slot_midPlayerPlayCards();
//    //选择 出牌
//    //首先清掉上一轮玩家在外面的手牌-》但是实际上应该是在回合开始的时候清掉
//    //TODO: 先判断选中的牌是否符合出牌规则


//    //符合
//    //获得选中牌
//    QList<Card* > lst = m_cardList[CARDLIST_MID_PLAYER].getSelectedCards();
//    if(Rulers::canPlayCards(lst,m_playRound.lastPlayerCards))
//    {
//        //根据牌组播放音乐
//        //CardSound::playCardsSound(lst);
//        //将选择的牌添加到玩家out牌堆
//        m_cardList[CARDLIST_MID_PLAYER_OUT].addCard(lst);

//        //删除选中
//        m_cardList[CARDLIST_MID_PLAYER].deleteSelectedCards();
//    }

//    //玩家out牌堆显示
}

void MainDialog::slot_deleteAllPlayerOutCards()
{
    for(int i=0;i<3;i++)
    {
        while(m_cardList[i+CARDLIST_LIFT_PLAYER_OUT].m_cardList.size()!=0)
        {
           Card*card= m_cardList[i+CARDLIST_LIFT_PLAYER_OUT].getOneCard();
           card->hide();
        }
    }
}

void MainDialog::slot_deleteOnePlayerOutCards(int player)
{
    int playerOutCards = player+CARDLIST_LIFT_PLAYER_OUT;
    while(m_cardList[playerOutCards].m_cardList.size()!=0)
    {
       Card*card= m_cardList[playerOutCards].getOneCard();
       card->hide();
    }
}

void MainDialog::slot_showPlayCards(bool flag)
{
    if(flag)
    {
        ui->wdg_playCards->show();
    }
    else
    {
        ui->wdg_playCards->hide();
    }
}

void MainDialog::slot_showCallLord(bool flag)
{
    if(flag)
    {
        ui->wdg_callLord->show();
    }
    else
    {
        ui->wdg_callLord->hide();
    }
}


void MainDialog::on_pb_pass_clicked()
{
    m_playRound.slot_midPlayerPass();
}

void MainDialog::slot_hideAllPass()
{
    for(QLabel* lb:m_lbPassArr)
    {
        lb->hide();
    }
}


void MainDialog::on_pb_callLord_clicked()
{
    m_playRound.slot_midPlayerCallLord();
}


void MainDialog::on_pb_noCall_clicked()
{
    m_playRound.slot_midPlayerNoCallLord();
}

void MainDialog::slot_lordAddCards(int player)
{
    //遍历牌堆，赋值出来（取出来）加进去
    for(Card* c:m_cardList[CARDLIST_LORD].m_cardList)
    {
        Card* newCard = new Card(c->m_point,c->m_suit,this->ui->page_game);
        m_cardList[player].addCard(newCard);
    }
    //排序
    m_cardList[player].cardSort();
    //地主牌 翻面
    m_cardList[CARDLIST_LORD].setAllCardsPositive(true);

}

