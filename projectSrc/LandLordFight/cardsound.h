#ifndef CARDSOUND_H
#define CARDSOUND_H
#include <QSound>
#include <QSoundEffect>
#include "rulers.h"
enum SOUND_TYPE{
    SOUND_NOCALL,
    SOUND_CALL,
    SOUND_LOSE,//失败
    SOUND_PASS,//不要
    SOUND_ROBLORD,//抢地主
    SOUND_WIN,
    SOUND_SHUFFLE///洗牌
};

///
/// The CardSound class
/// 播放声音类
/// 使用qt的 multimedia 里的
/// QSound 这个无法调节音量
/// QSoundEffect 只能播放 .wav 其他格式需要转换
///

class CardSound
{
public:

    //根据类型播放
    static void playSound(int type);
    //根据牌组播放
    static void playCardsSound(QList<Card*> &cards);
    //播放背景音乐
    static void playBGM();
};

#endif // CARDSOUND_H
