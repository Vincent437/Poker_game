#pragma once
#include "cocos2d.h"
#include "controllers/MenuController.h" // 引入控制器

class MenuScene : public cocos2d::Scene {
public:
    static MenuScene* create();
    virtual bool init() override;
    void menuCloseCallback(Ref* pSender);

private:
    MenuController* _controller; // 持有控制器
    void setupUI();              // 初始化UI
};