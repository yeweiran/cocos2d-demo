#include "ResultPrize.h"

USING_NS_CC;

ResultPrize::ResultPrize(cocos2d::Sprite *spr_BG) {
    // Prize Sprite and text
    spr_prize = Sprite::create("coin.png");
    auto effect = Sprite::create("light_effect.png");
    spr_prize->addChild(effect, -1, "spr_effect");
    effect->setPosition(spr_prize->getContentSize().width / 2, spr_prize->getContentSize().height / 2);
    effect->runAction(RepeatForever::create(RotateBy::create(5, 360)));
    auto text_prize = Label::createWithTTF("X1", "fonts/Marker Felt.ttf", font_size_prize);
    text_prize->setTextColor(Color4B(0, 0, 0, 255));
    spr_prize->addChild(text_prize,1,"text_prize");
    text_prize->setPosition(spr_prize->getContentSize().width / 2, spr_prize->getContentSize().height / 2 - 10);
    spr_BG->addChild(spr_prize, 100, "spr_prize");
    originPos = Vec2(spr_BG->getContentSize().width / 2, spr_BG->getContentSize().height / 2 + 80);
    Enable(false);
}

void ResultPrize::ShowResultPrize(int prizeIndex) {
    auto act_scaleup = ScaleTo::create(0.5,2);
    auto act_movedown = MoveBy::create(1, Point(0, -80));
    spr_prize->setTexture(GameManager::GetInstance()->spr_prizes[prizeIndex]->getTexture());
    ((Label*)spr_prize->getChildByName("text_prize"))->setString(GameManager::GetInstance()->text_prizes[prizeIndex]->getString());
    spr_prize->setVisible(true);
    spr_prize->runAction(act_scaleup);
    spr_prize->runAction(Sequence::create(act_movedown,CallFunc::create([&](){
        spr_prize->getChildByName("spr_effect")->setVisible(true);
    }),nullptr));
}

void ResultPrize::Enable(bool flag) {
    spr_prize->stopAllActions();
    spr_prize->setPosition(originPos);
    spr_prize->setScale(1);
    spr_prize->getChildByName("spr_effect")->setVisible(flag);
    spr_prize->setVisible(flag);
}
