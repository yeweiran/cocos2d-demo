#include "MyButton.h"

USING_NS_CC;

MyButton::MyButton(cocos2d::Sprite *spr_BG, std::string text) {
    btnText = text;
    btn = ui::Button::create("spin_button.png");
    btn->setTitleText(btnText);
    btn->setTitleFontName("arial.ttf");
    btn->setTitleFontSize(font_size_btn);
    btn->setTitleColor(Color3B(255,255,255));
    spr_BG->addChild(btn, 1, btnText);
    btn->setPosition(Point(spr_BG->getContentSize().width / 2, 100));
    btn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        std::string a = "Play On";
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (btnText == "Play On") GameManager::GetInstance()->PlayOnBtnClicked();
                else if(btnText == "Claim") GameManager::GetInstance()->ClaimBtnClicked();
                break;
            default:
                break;
        }
    });
}

void MyButton::Enable(bool flag) {
    btn->setVisible(flag);
    btn->setEnabled(flag);
}
