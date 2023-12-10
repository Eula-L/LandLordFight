#include "cardsound.h"
//#include <qDebug>

void CardSound::playSound(int type)
{
    QString str;
    switch(type)
    {
    case SOUND_NOCALL:
        str = "bujiao";
        break;
    case SOUND_CALL:
        str = "jiaodizhu";
        break;
    case SOUND_LOSE:
        str = "loseMusic";
        break;
    case SOUND_PASS:
        str = "passMusic";
        break;
    case SOUND_ROBLORD:
        str = "qiangdizhu";
        break;
    case SOUND_WIN:
        str = "win";
        break;
    case SOUND_SHUFFLE:
        str = "xipai";
        break;
    }
    str = QString(":/sound/%1.wav").arg(str);
    QSound::play(str);

}

#include <QTimer>
void CardSound::playCardsSound(QList<Card*> &cards)
{

    QString str;
    int card_type =  Rulers::getCardType(cards);
    qDebug()<<card_type;
    if(card_type ==TRIPLE)
    {
        QString path = QString(":/sound/sange.wav");
        QSound::play(path);

        str = QString::number(cards.front()->m_point+3);
        str = QString(":/sound/%1.wav").arg(str);
        QSound::play(str);
        //使用定时器，实现延时
        QTimer::singleShot(333,[str](){
            QSound::play(str);
        });//超时时间，执行的对象指针，执行的槽函数
    }
    switch (card_type) {
    case SINGLE:
        //qDebug()<<cards.front()->m_point;
        str = QString::number(cards.front()->m_point+3);
        break;
    case PAIR:
        str ="dui";
        str += QString::number(cards.front()->m_point+3);
        break;
    case TRIPLE_WITH_ONE:
        str ="sandaiyi";
        break;
    case TRIPLE_WITH_PAIR:
        str ="sandaiyidui";
        break;
    case STRAIGHT:
        str ="shunzi";
        break;
    case STRAIGHT_PAIR:
        str ="liandui";
        break;
    case PLANE:
        str ="feiji";
        break;
    case PLANT_WITH_WING:
        str ="shunzidaichibang";
        break;
    case FOUR_WITH_TOW:
        str = "sidaier";
         break;
    case FOUR_WITH_TWO_PAIR:
        str = "sidailiangdui";
         break;
    case BOMB:
         str = "zhadan";
         break;
    case KING_BOMB:
         str = "wangzha";
        break;
    }
    str = QString(":/sound/%1.wav").arg(str);
    //qDebug()<<"即将播放";
    QSound::play(str);
}

void CardSound::playBGM()
{
    static QSoundEffect sound;
    sound.setSource(QUrl::fromLocalFile(":/sound/bkMusic.wav"));
    sound.setLoopCount(QSoundEffect::Infinite);//设置为无限次
    //设置音量 0~1
    sound.setVolume(0.1);
    sound.play();
}
