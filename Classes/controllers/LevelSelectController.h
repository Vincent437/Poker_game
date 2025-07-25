#pragma once
#include "cocos2d.h"
#include "views/scene/LevelSelectScene.h"
//#include "managers/LevelProgressManager.h"

class LevelSelectController {
public:
    LevelSelectController(cocos2d::Scene* scene);

    // void onLevelButtonClicked(int levelId); // ��ť����ص�
    void loadLevels();                      // ���عؿ�����

private:
    cocos2d::Scene* _scene;
    //LevelProgressManager* _progressManager; // ���й��������ǵ�����
};