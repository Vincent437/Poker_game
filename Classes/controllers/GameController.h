#pragma once
//#include "configs/models/LevelConfig.h"
#include "views/scene/GameScene.h"
#include "managers/UndoManager.h"

class GameScene;

class GameController {
public:
    //GameController(GameScene* scene, const LevelConfig& levelConfig);
    GameController(GameScene* scene, std::shared_ptr<GameModel> gameModel);
    void onEnter(); // 初始化游戏逻辑

    // 卡牌交互方法
    void onStackCardClicked(int stackIndex);
    void onPlayfieldCardClicked(int playfieldIndex);
    void onUndoButtonClicked();

private:
    GameScene* _scene; // 弱引用
    //LevelConfig _levelConfig; // 关卡配置
    std::shared_ptr<GameModel> _gameModel; // 改为智能指针
    std::unique_ptr<UndoManager> _undoManager; // 新增回退管理器
};