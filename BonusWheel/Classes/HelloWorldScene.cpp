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
    auto visibleSize = GameManager::GetInstance()->GetVisibleSize();
    Vec2 origin = GameManager::GetInstance()->GetOrigin();

    auto centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    spr_BG = Sprite::create("background.png");
    spr_BG->setPosition(centerPos);
    this->addChild(spr_BG, 1);
    GameManager::GetInstance()->InitGame(spr_BG);
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

//void HelloWorld::TestEmulateSpin(int times) {
//    int res[8] = {0};
//    for(int i = 0; i < times; ++i){
//        ++res[Draw()];
//    }
//    std::stringstream ss;
//    ss << "cclog\nPrize:\t\tTimes\nHammer 1X:\t\t" << res[0]
//    << "\nGem 75:\t\t" << res[1] << "\nBrush 1X:\t\t" << res[2]
//    << "\nCoins 750:\t\t" << res[3] << "\nHammer 3X:\t\t" << res[4]
//    << "\nGem 35:\t\t" << res[5] << "\nBrush 3X:\t\t" << res[6] << "\nLife 30 min:\t\t" << res[7];
//    std::string log = ss.str();
//    cocos2d::log("%s", log.c_str());
//    auto fileUtils = FileUtils::getInstance();
//    std::string path = fileUtils->getWritablePath() + "BonusWheel_emulate_log.txt";
//    //std::string path = "/SDCARD/Android/data/BonusWheel_emulate_log.txt";
//    if(fileUtils->writeStringToFile(log, path)){
//        cocos2d::log("cclog Write to %s success!", path.c_str());
//    }
//}
