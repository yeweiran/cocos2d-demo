#include "BonusWheel.h"

USING_NS_CC;

BonusWheel::BonusWheel(cocos2d::Sprite *spr_BG) {
    // Wheel BG, Wheel, Wheel Arrow sprites
    spr_wheelBG = Sprite::create("wheel_border.png");
    spr_BG->addChild(spr_wheelBG, 3);
    spr_wheelBG->setPosition(spr_BG->getContentSize().width / 2, spr_BG->getContentSize().height / 2);
    spr_wheel = Sprite::create("wheel_sections_8.png");
    spr_wheelBG->addChild(spr_wheel,-1);
    spr_wheel->setPosition(spr_wheelBG->getContentSize().width / 2, spr_wheelBG->getContentSize().height / 2);
    spr_arrow = Sprite::create("wheel_arrow.png");
    spr_wheelBG->addChild(spr_arrow);
    spr_arrow->setPosition(spr_wheelBG->getContentSize().width / 2, spr_wheelBG->getContentSize().height - 10);
    int numOfPrize = GameManager::GetInstance()->GetNumOfPrizes();
    for(int i = 0; i < numOfPrize; ++i){
        auto spr_prize = Sprite::create(GameManager::GetInstance()->spr_prizes[i]);
        auto text_prize = Label::createWithTTF(GameManager::GetInstance()->text_prizes[i], "fonts/Marker Felt.ttf", font_size_prize);
        spr_wheel->addChild(spr_prize);
        spr_prize->addChild(text_prize);
        text_prize->setTextColor(Color4B(0, 0, 0, 255));
        text_prize->setPosition(spr_prize->getContentSize().width / 2,spr_prize->getContentSize().height / 2 - 10);
        float angle = (180 / numOfPrize + 360 / numOfPrize * i) * 3.1416 / 180;
        int len = 80;
        spr_prize->setPosition(spr_wheel->getContentSize().width / 2 - len * sin(angle),spr_wheel->getContentSize().width / 2 + len * cos(angle));
        spr_prize->setRotation(-(180 / numOfPrize + 360 / numOfPrize * i));
    }
}

void BonusWheel::SpinWheel(int prizeIndex) {
    int numOfPrizes = GameManager::GetInstance()->GetNumOfPrizes();
    auto act_pullback = RotateBy::create(0.3, -5);
    float angle = 180 / numOfPrizes + 360 / numOfPrizes*prizeIndex + 360 * 5 + 5;
    auto act_spin = EaseExponentialOut::create(RotateBy::create(5,angle));
    spr_wheel->runAction(Sequence::create(act_pullback, act_spin,
                                          CallFunc::create(CC_CALLBACK_0(GameManager::ShowResultPrize, GameManager::GetInstance())),nullptr));
}

void BonusWheel::Enable(bool flag) {
    spr_wheelBG->setVisible(flag);
    spr_wheel->setRotation(0);
}
