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
    numOfPrizes = 8;
    spr_prizes.assign({"hammer.png", "gem.png", "brush.png", "coin.png", "hammer.png", "gem.png", "brush.png", "heart.png"});
    text_prizes.assign({"X1", "X75", "X1", "X750", "X3", "X35", "X3", "30min"});
    PrizesChances.assign({20, 5, 20, 5, 10, 10, 10, 20});
}

void GameManager::InitGame(cocos2d::Sprite *spr_BG) {
    srand((unsigned)time(NULL));

    bonusWheel = std::make_shared<BonusWheel>(spr_BG);
    resultPrize = std::make_shared<ResultPrize>(spr_BG);
    btn_spin = std::make_shared<MyButton>(spr_BG, "Play On");
    btn_claim = std::make_shared<MyButton>(spr_BG, "Claim");
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
        total+= PrizesChances[i];
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
