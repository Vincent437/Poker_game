#include "LevelSelectController.h"

#include "configs/models/LevelConfig.h"

#include "models/GameModel.h"


LevelSelectController::LevelSelectController(cocos2d::Scene* scene) : _scene(scene) {
    loadLevels(); // 初始化
}

void LevelSelectController::loadLevels() {
    // 暂时留空，后续实现关卡加载逻辑
    CCLOG("LevelSelectController initialized.");
}

void LevelSelectController::onLevel0ButtonClicked() {
    // 1. 加载关卡配置
    LevelConfig levelConfig;
    if (!levelConfig.initWithFile(R"(D:\CPP\poker\Classes\levels\level_0.json)")) {
        CCLOG("Failed to load level_0.json");
        return;
    }

    // 2. 创建游戏场景并传递配置
	GameModel* gameModel = new GameModel(levelConfig.PlayfieldCards, levelConfig.StackCards);
    auto gameScene = GameScene::create(gameModel);
    auto gameController = new GameController(gameScene, levelConfig);
    gameScene->setController(gameController);
    cocos2d::Director::getInstance()->replaceScene(gameScene);
}