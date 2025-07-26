#pragma once
//#include "configs/models/LevelConfig.h"
#include "views/scene/GameScene.h"
#include "managers/UndoManager.h"

class GameScene;

class GameController {
public:
    //GameController(GameScene* scene, const LevelConfig& levelConfig);
    GameController(GameScene* scene, std::shared_ptr<GameModel> gameModel);
    void onEnter(); // ��ʼ����Ϸ�߼�

    // ���ƽ�������
    void onStackCardClicked(int stackIndex);
    void onPlayfieldCardClicked(int playfieldIndex);
    void onUndoButtonClicked();

private:
    GameScene* _scene; // ������
    //LevelConfig _levelConfig; // �ؿ�����
    std::shared_ptr<GameModel> _gameModel; // ��Ϊ����ָ��
    std::unique_ptr<UndoManager> _undoManager; // �������˹�����
};