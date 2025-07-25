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

    // 2. ������Ϸ��������������
	GameModel* gameModel = new GameModel(levelConfig.PlayfieldCards, levelConfig.StackCards);
    auto gameScene = GameScene::create(gameModel);
    auto gameController = new GameController(gameScene, levelConfig);
    gameScene->setController(gameController);
    cocos2d::Director::getInstance()->replaceScene(gameScene);
}