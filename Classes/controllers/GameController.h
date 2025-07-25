#pragma once
#include "configs/models/LevelConfig.h"
#include "views/scene/GameScene.h"

class GameScene;

class GameController {
public:
    GameController(GameScene* scene, const LevelConfig& levelConfig);
    void onEnter(); // ��ʼ����Ϸ�߼�

private:
    GameScene* _scene; // ������
    LevelConfig _levelConfig; // �ؿ�����
};