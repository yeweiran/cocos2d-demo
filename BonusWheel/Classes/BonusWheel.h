#ifndef __BONUSWHEEL_H__
#define __BONUSWHEEL_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "ui\CocosGUI.h"

class BonusWheel
{
public:
    BonusWheel(cocos2d::Sprite *spr_BG);
    void SpinWheel(int prizeIndex);
    void Enable(bool flag = true);
private:
    //cocos2d::Sprite *spr_BG;
    cocos2d::Sprite *spr_wheelBG;
    cocos2d::Sprite *spr_wheel;
    cocos2d::Sprite *spr_arrow;
};

#endif // __BONUSWHEEL_H__
