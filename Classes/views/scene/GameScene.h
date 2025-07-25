// Classes/views/scenes/GameScene.h
#pragma once
#include "cocos2d.h"
#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"
#include "views/CardView.h"

class GameController; // ǰ������

class GameScene : public cocos2d::Scene {
public:
    static GameScene* create(GameModel* model);
    virtual bool init(GameModel* model);

    void setController(GameController* controller); // �󶨿�����

    void updateCardPositions();

private:

    void setupPlayfield();
    void setupStack();

    GameModel* _model;
    cocos2d::Vector<CardView*> _cardViews;

    GameController* _controller; // ������
};