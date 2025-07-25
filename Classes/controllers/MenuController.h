#pragma once
#include "cocos2d.h"

class MenuController {
public:
    MenuController(cocos2d::Scene* parentScene);
    void onStartButtonClicked(); // 处理按钮点击
    void MenuController::menuCloseCallback();
private:
    cocos2d::Scene* _parentScene; // 弱引用，避免循环持有
};