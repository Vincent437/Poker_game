#include "LevelSelectController.h"

#include "configs/models/LevelConfig.h"

#include "models/GameModel.h"


LevelSelectController::LevelSelectController(cocos2d::Scene* scene) : _scene(scene) {
    loadLevels(); // ��ʼ��
}

void LevelSelectController::loadLevels() {
    // ��ʱ���գ�����ʵ�ֹؿ������߼�
    CCLOG("LevelSelectController initialized.");
}

void LevelSelectController::onLevel0ButtonClicked() {  
    // 1. ���عؿ�����  
    LevelConfig levelConfig;  
    if (!levelConfig.initWithFile(R"(D:\CPP\poker\Classes\levels\level_0.json)")) {  
        CCLOG("Failed to load level_0.json");  
        return;  
    }  

    // 2. ʹ�� std::make_shared ���� GameModel  
    auto gameModel = std::make_shared<GameModel>(levelConfig.PlayfieldCards, levelConfig.StackCards);  

    // 3. ������Ϸ��������������  
    auto gameScene = GameScene::create(gameModel);  

    // 4. ʹ�� std::make_unique ���� GameController  
    auto gameController = std::make_unique<GameController>(gameScene, gameModel);  
    gameScene->setController(std::move(gameController));

    // 5. �滻��ǰ����  
    cocos2d::Director::getInstance()->replaceScene(gameScene);  
}