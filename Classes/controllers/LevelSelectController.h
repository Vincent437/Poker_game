#pragma once
#include "cocos2d.h"
#include "views/scene/LevelSelectScene.h"
//#include "managers/LevelProgressManager.h"
#include "views/scene/GameScene.h"
#include "controllers/GameController.h"

class LevelSelectController {
public:
    LevelSelectController(cocos2d::Scene* scene);

    // void onLevelButtonClicked(int levelId); // ��ť����ص�
    void loadLevels();                      // ���عؿ�����

    void onLevel0ButtonClicked(); // �����0�ذ�ť
private:
    cocos2d::Scene* _scene;
    //LevelProgressManager* _progressManager; // ���й��������ǵ�����
};