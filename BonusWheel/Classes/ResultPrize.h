#ifndef __RESULT_PRIZE_H__
#define __RESULT_PRIZE_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "ui\CocosGUI.h"

class ResultPrize
{
public:
    ResultPrize(cocos2d::Sprite *spr_BG);
    void ShowResultPrize(int prizeIndex);
    void Enable(bool flag);
private:
    cocos2d::Sprite *spr_prize;
    cocos2d::Vec2 originPos;
};

#endif // __RESULT_PRIZE_H__
