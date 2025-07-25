// Classes/controllers/GameController.cpp
#include "GameController.h"
#include "views/scene/GameScene.h"

GameController::GameController(GameScene* scene, const LevelConfig& levelConfig)
    : _scene(scene), _levelConfig(levelConfig) {
    onEnter();
}

void GameController::onEnter() {
    CCLOG("GameController initialized with Level 0 config.");
    // ������������ؿ��ơ���ʼ����Ϸ�߼�
}