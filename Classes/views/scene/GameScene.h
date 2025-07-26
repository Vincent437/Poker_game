#pragma once
#include "cocos2d.h"
//#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"
#include "views/CardView.h"

class GameController; // 前置声明

class GameScene : public cocos2d::Scene {
public:
    //static GameScene* create(GameModel* model);

    static GameScene* create(std::shared_ptr<GameModel> model);

    //bool init(GameModel* model);

    bool init(std::shared_ptr<GameModel> model);
    void addStackCardView(CardView* cardView);
    void addPlayfieldCardView(CardView* cardView);

    void setController(std::unique_ptr<GameController> controller); // 绑定控制器

    void updateCardPositions();


    // 卡牌移动方法
    void moveCardToStackTop(int playfieldIndex);
    void undoCardMove(const CardModel& card, cocos2d::Vec2 originalPos);
    void highlightStackTopCard();
    void overrideStackCard(int stackIndex);
    void undoStackOverride(int targetIndex, CardModel& originalCard);
    void undoLastMove(const CardModel& card, cocos2d::Vec2 originalPos);

    // 卡牌视图管理
    std::vector<CardView*> getStackCardViews() const { return _stackCardViews; }
    std::vector<CardView*> getPlayfieldCardViews() const { return _playfieldCardViews; }

    void onUndoButtonClicked();
private:

    void setupPlayfield();
    void setupStack();

    //GameModel* _model;
    std::shared_ptr<GameModel> _model;
    cocos2d::Vector<CardView*> _cardViews;
	std::unique_ptr<GameController> _controller; // 控制器
    //GameController* _controller; // 弱引用
    std::vector<CardView*> _stackCardViews;
    std::vector<CardView*> _playfieldCardViews;
};