#pragma once
#include "cocos2d.h"

class MenuController {
public:
    MenuController(cocos2d::Scene* parentScene);
    void onStartButtonClicked(); // ����ť���
    void MenuController::menuCloseCallback();
private:
    cocos2d::Scene* _parentScene; // �����ã�����ѭ������
};