#pragma once
#include "cocos2d.h"
#include "controllers/MenuController.h" // ���������

class MenuScene : public cocos2d::Scene {
public:
    static MenuScene* create();
    virtual bool init() override;
    void menuCloseCallback(Ref* pSender);

private:
    MenuController* _controller; // ���п�����
    void setupUI();              // ��ʼ��UI
};