#pragma once
#include "cocos2d.h"
#include "views/scene/LevelSelectScene.h"
//#include "managers/LevelProgressManager.h"
#include "views/scene/GameScene.h"
#include "controllers/GameController.h"

class LevelSelectController {
public:
    LevelSelectController(cocos2d::Scene* scene);

    // void onLevelButtonClicked(int levelId); // 按钮点击回调
    void loadLevels();                      // 加载关卡数据

    void onLevel0ButtonClicked(); // 点击第0关按钮
private:
    cocos2d::Scene* _scene;
    //LevelProgressManager* _progressManager; // 持有管理器（非单例）
};