//
// Created by Allen on 12/22/2020.
//

#include "GameManager.h"

USING_NS_CC;

GameManager * GameManager::Instance = nullptr;
GameManager * GameManager::GetInstance() {
    if ( Instance == nullptr )
        Instance = new GameManager();
    return Instance;
}

cocos2d::Size GameManager::GetVisibleSize() {
    return visibleSize;
}

cocos2d::Vec2 GameManager::GetOrigin() {
    return origin;
}

GameManager::GameManager() {
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    // Init Prizes sprites and texts
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
}

void GameManager::InitGame(cocos2d::Sprite *spr_BG) {
    srand((unsigned)time(NULL));
    bonusWheel = new BonusWheel(spr_BG);
    resultPrize = new ResultPrize(spr_BG);
    btn_spin = new MyButton(spr_BG, "Play On");
    btn_claim = new MyButton(spr_BG, "Claim");
    btn_claim->Enable(false);
}

void GameManager::PlayOnBtnClicked() {
    btn_spin->Enable(false);
    prizeIndex = GetRandomPrize();
    bonusWheel->SpinWheel(prizeIndex);
    //CCLOG("cclog result: %d", DrawResult);
}

void GameManager::ClaimBtnClicked() {
    btn_spin->Enable(true);
    btn_claim->Enable(false);
    bonusWheel->Enable(true);
    resultPrize->Enable(false);
}

int GameManager::GetRandomPrize() {
    int res = rand() % 100, total = 0;
    for(int i = 0; i < numOfPrizes; ++i){
        total+=PrizesChances[i];
        if(res < total) return i;
    }
    return -1;
}

void GameManager::ShowResultPrize() {
    bonusWheel->Enable(false);
    btn_claim->Enable(true);
    resultPrize->ShowResultPrize(prizeIndex);
}

int GameManager::GetNumOfPrizes() {
    return numOfPrizes;
}
