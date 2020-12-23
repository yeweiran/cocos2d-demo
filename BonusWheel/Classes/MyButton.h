#ifndef __MYBUTTON_H__
#define __MYBUTTON_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "ui\CocosGUI.h"

class MyButton
{
public:
    MyButton(cocos2d::Sprite *spr_BG, std::string text);
    void Enable(bool flag = true);
private:
    //cocos2d::Sprite *spr_BG;
    cocos2d::ui::Button *btn;
    std::string btnText;
};

#endif // __MYBUTTON_H__
