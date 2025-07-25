// Classes/views/scenes/GameScene.h
#pragma once
#include "cocos2d.h"
#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"
#include "views/CardView.h"

class GameController; // 前置声明

class GameScene : public cocos2d::Scene {
public:
    static GameScene* create(GameModel* model);
    virtual bool init(GameModel* model);

    void setController(GameController* controller); // 绑定控制器

    void updateCardPositions();

private:

    void setupPlayfield();
    void setupStack();

    GameModel* _model;
    cocos2d::Vector<CardView*> _cardViews;

    GameController* _controller; // 弱引用
};