/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(360, 540, ResolutionPolicy::NO_BORDER );
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    srand((unsigned)time(NULL));

    auto centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    spr_BG = Sprite::create("background.png");
    spr_BG->setPosition(centerPos);
    this->addChild(spr_BG, 1);
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
    // On Wheel Prizes sprites and texts
    spr_prizes.assign(8, Sprite::create());
    text_prizes.assign(8, Label::create());
    spr_prizes[0] = Sprite::create("hammer.png");
    text_prizes[0] = Label::createWithTTF("X1", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[1] = Sprite::create("gem.png");
    text_prizes[1] = Label::createWithTTF("X75", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[2] = Sprite::create("brush.png");
    text_prizes[2] = Label::createWithTTF("X1", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[3] = Sprite::create("coin.png");
    text_prizes[3] = Label::createWithTTF("X750", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[4] = Sprite::create("hammer.png");
    text_prizes[4] = Label::createWithTTF("X3", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[5] = Sprite::create("gem.png");
    text_prizes[5] = Label::createWithTTF("X35", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[6] = Sprite::create("brush.png");
    text_prizes[6] = Label::createWithTTF("X3", "fonts/Marker Felt.ttf", font_size_prize);
    spr_prizes[7] = Sprite::create("heart.png");
    text_prizes[7] = Label::createWithTTF("30min", "fonts/Marker Felt.ttf", font_size_prize);
    for(int i = 0; i < 8; ++i){
        spr_wheel->addChild(spr_prizes[i]);
        spr_prizes[i]->addChild(text_prizes[i]);
        text_prizes[i]->setTextColor(Color4B(0, 0, 0, 255));
        text_prizes[i]->setPosition(spr_prizes[i]->getContentSize().width / 2,
                spr_prizes[i]->getContentSize().height / 2 - 10);
        float angle = (22.5 + 45 * i) * 3.1416 / 180;
        int len = 80;
        spr_prizes[i]->setPosition(spr_wheel->getContentSize().width / 2 - len * sin(angle),
                spr_wheel->getContentSize().width / 2 + len * cos(angle));
        spr_prizes[i]->setRotation(-(22.5 + 45 * i));
    }
    // Prize Sprite and text
    spr_prize = Sprite::create("coin.png");
    auto effect = Sprite::create("light_effect.png");
    spr_prize->addChild(effect, -1, "spr_effect");
    effect->setPosition(spr_prize->getContentSize().width / 2, spr_prize->getContentSize().height / 2);
    effect->runAction(RepeatForever::create(RotateBy::create(5, 360)));
    effect->setVisible(false);
    auto text_prize = Label::createWithTTF("X1", "fonts/Marker Felt.ttf", font_size_prize);
    text_prize->setTextColor(Color4B(0, 0, 0, 255));
    spr_prize->addChild(text_prize,1,"text_prize");
    text_prize->setPosition(spr_prize->getContentSize().width / 2, spr_prize->getContentSize().height / 2 - 10);
    spr_BG->addChild(spr_prize, 100, "spr_prize");
    spr_prize->setPosition(Point(spr_BG->getContentSize().width / 2, spr_BG->getContentSize().height / 2 + 80));
    spr_prize->setVisible(false);
    // Play On Button
    auto btn_draw = ui::Button::create("spin_button.png");
    btn_draw->setTitleText("Play On");
    btn_draw->setTitleFontName("arial.ttf");
    btn_draw->setTitleFontSize(font_size_btn);
    btn_draw->setTitleColor(Color3B(255,255,255));
    spr_BG->addChild(btn_draw, 1, "btn_draw");
    btn_draw->setPosition(Point(spr_BG->getContentSize().width / 2, 100));
    btn_draw->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                PlayOnBtnClicked();
                TestEmulateSpin(10000);
                break;
            default:
                break;
        }
    });
    // Claim Button
    auto btn_claim = ui::Button::create("spin_button.png");
    btn_claim->setTitleText("Claim");
    btn_claim->setTitleFontName("arial.ttf");
    btn_claim->setTitleFontSize(font_size_btn);
    btn_claim->setTitleColor(Color3B(255,255,255));
    spr_BG->addChild(btn_claim, 1, "btn_claim");
    btn_claim->setPosition(Point(spr_BG->getContentSize().width / 2, 100));
    btn_claim->setVisible(false);
    btn_claim->setEnabled(false);
    btn_claim->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                ClaimBtnClicked();
                break;
            default:
                break;
        }
    });
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::PlayOnBtnClicked() {
    auto btn_draw = spr_BG->getChildByName<ui::Button*>("btn_draw");
    btn_draw->setVisible(false);
    btn_draw->setEnabled(false);
    DrawResult = Draw();
    auto act_pullback = RotateBy::create(0.3, -5);
    float angle = 22.5+ 45*DrawResult + 360 * 5 + 5;
    auto act_spin = EaseExponentialOut::create(RotateBy::create(5,angle));
    spr_wheel->runAction(Sequence::create(act_pullback, act_spin,
            CallFunc::create(CC_CALLBACK_0(HelloWorld::ShowDrawResult, this)),nullptr));
    CCLOG("cclog result: %d", DrawResult);
}

int HelloWorld::Draw() {
    int res = rand() % 100, total = 0;
    for(int i = 0; i < 8; ++i){
        total+=PrizesChances[i];
        if(res < total) return i;
    }
    return -1;
}

void HelloWorld::ShowDrawResult() {
    spr_wheelBG->setVisible(false);
    spr_wheel->setRotation(0);
    auto btn_claim = spr_BG->getChildByName<ui::Button*>("btn_claim");
    btn_claim->setVisible(true);
    btn_claim->setEnabled(true);
    auto act_scaleup = ScaleTo::create(0.5,2);
    auto act_movedown = MoveBy::create(1, Point(0, -80));
    spr_prize->setTexture(spr_prizes[DrawResult]->getTexture());
    ((Label*)spr_prize->getChildByName("text_prize"))->setString(text_prizes[DrawResult]->getString());
    spr_prize->setVisible(true);
    spr_prize->runAction(act_scaleup);
    spr_prize->runAction(Sequence::create(act_movedown,CallFunc::create([&](){
        spr_prize->getChildByName("spr_effect")->setVisible(true);
    }),nullptr));
}

void HelloWorld::ClaimBtnClicked() {
    auto btn_draw = spr_BG->getChildByName<ui::Button*>("btn_draw");
    btn_draw->setVisible(true);
    btn_draw->setEnabled(true);
    auto btn_claim = spr_BG->getChildByName<ui::Button*>("btn_claim");
    btn_claim->setVisible(false);
    btn_claim->setEnabled(false);
    spr_wheelBG->setVisible(true);
    spr_prize->stopAllActions();
    spr_prize->setPosition(Point(spr_BG->getContentSize().width / 2, spr_BG->getContentSize().height / 2 + 120));
    spr_prize->setScale(0.2);
    spr_prize->getChildByName("spr_effect")->setVisible(false);
    spr_prize->setVisible(false);
}

void HelloWorld::TestEmulateSpin(int times) {
    int res[8] = {0};
    for(int i = 0; i < times; ++i){
        ++res[Draw()];
    }
    std::stringstream ss;
    ss << "cclog\nPrize:\t\tTimes\nHammer 1X:\t\t" << res[0]
    << "\nGem 75:\t\t" << res[1] << "\nBrush 1X:\t\t" << res[2]
    << "\nCoins 750:\t\t" << res[3] << "\nHammer 3X:\t\t" << res[4]
    << "\nGem 35:\t\t" << res[5] << "\nBrush 3X:\t\t" << res[6] << "\nLife 30 min:\t\t" << res[7];
    std::string log = ss.str();
    cocos2d::log("%s", log.c_str());
    auto fileUtils = FileUtils::getInstance();
    std::string path = fileUtils->getWritablePath() + "BonusWheel_emulate_log.txt";
    //std::string path = "/SDCARD/Android/data/BonusWheel_emulate_log.txt";
    if(fileUtils->writeStringToFile(log, path)){
        cocos2d::log("cclog Write to %s success!", path.c_str());
    }
}
