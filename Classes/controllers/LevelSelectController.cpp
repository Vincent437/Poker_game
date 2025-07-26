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

    // 2. 使用 std::make_shared 创建 GameModel  
    auto gameModel = std::make_shared<GameModel>(levelConfig.PlayfieldCards, levelConfig.StackCards);  

    // 3. 创建游戏场景并传递配置  
    auto gameScene = GameScene::create(gameModel);  

    // 4. 使用 std::make_unique 创建 GameController  
    auto gameController = std::make_unique<GameController>(gameScene, gameModel);  
    gameScene->setController(std::move(gameController));

    // 5. 替换当前场景  
    cocos2d::Director::getInstance()->replaceScene(gameScene);  
}