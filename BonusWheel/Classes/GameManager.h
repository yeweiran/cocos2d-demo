//
// Created by Allen on 12/22/2020.
//

#ifndef PROJ_ANDROID_GAMEMANAGER_H
#define PROJ_ANDROID_GAMEMANAGER_H

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "BonusWheel.h"
#include "ResultPrize.h"
#include "MyButton.h"

const int font_size_prize = 20;
const int font_size_btn = 24;

class ResultPrize;
class MyButton;
class BonusWheel;

class GameManager
{
public:
    static GameManager* GetInstance();
    cocos2d::Size GetVisibleSize();
    cocos2d::Vec2 GetOrigin();
    std::vector<cocos2d::Sprite*> spr_prizes;
    std::vector<cocos2d::Label*> text_prizes;
    void InitGame(cocos2d::Sprite *spr_BG);
    int GetNumOfPrizes();
    void ShowResultPrize();
    void PlayOnBtnClicked();
    void ClaimBtnClicked();
private:
    GameManager();
    static GameManager *Instance;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    BonusWheel *bonusWheel;
    ResultPrize *resultPrize;
    MyButton *btn_spin;
    MyButton *btn_claim;
    int prizeIndex;
    int numOfPrizes = 8;
    int PrizesChances[8] = {20, 5, 20, 5, 10, 10, 10, 20};
    int GetRandomPrize();

};
#endif //PROJ_ANDROID_GAMEMANAGER_H
