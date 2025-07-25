#pragma once
#include "configs/models/LevelConfig.h"
#include "views/scene/GameScene.h"

class GameScene;

class GameController {
public:
    GameController(GameScene* scene, const LevelConfig& levelConfig);
    void onEnter(); // 初始化游戏逻辑

private:
    GameScene* _scene; // 弱引用
    LevelConfig _levelConfig; // 关卡配置
};