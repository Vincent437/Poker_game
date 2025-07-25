// Classes/views/scenes/GameScene.cpp
#include "GameScene.h"
#include "controllers/GameController.h"

GameScene* GameScene::create(GameModel* model) {
    auto scene = new (std::nothrow) GameScene();
    if (scene && scene->init(model)) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool GameScene::init(GameModel* model) {
    if (!Scene::init()) return false;
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto topLayer = cocos2d::LayerColor::create(cocos2d::Color4B(200, 200, 200, 255));
    topLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height*2));
    /*topLayer->setPosition(0, visibleSize.height / 3);*/
    auto bottomLayer = cocos2d::LayerColor::create(cocos2d::Color4B(128, 64, 0, 255));
    bottomLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height / 3));
    /*auto background = cocos2d::LayerColor::create(cocos2d::Color4B(200, 200, 200, 255));
    addChild(background);*/

    this->addChild(topLayer);
    this->addChild(bottomLayer);
    _model = model;
    setupPlayfield();
    setupStack();

    return true;
}

void GameScene::setController(GameController* controller) {
    _controller = controller;
}

void GameScene::setupPlayfield() {
    for (const auto& cardData : _model->getPlayfieldCards()) {
        auto cardModel = new CardModel(static_cast<CardFaceType>(cardData.CardFace),
            static_cast<CardSuitType>(cardData.CardSuit),
            cocos2d::Vec2(cardData.Position.x, cardData.Position.y));

        auto cardView = CardView::create(cardModel);
        this->addChild(cardView);
        _cardViews.pushBack(cardView);

        // 模型由GameModel管理，这里不需要delete cardModel
    }
}

void GameScene::setupStack() {
    // 类似playfield的处理
    int offsetX = 100;
	int offsetY = 50;
    for (const auto& cardData : _model->getStackCards()) {
        auto cardModel = new CardModel(static_cast<CardFaceType>(cardData.CardFace),
            static_cast<CardSuitType>(cardData.CardSuit),
            cocos2d::Vec2(cardData.Position.x, cardData.Position.y));
		offsetX += 20; // 每张牌之间的水平间距
		cardModel->setPosition(cocos2d::Vec2(cardData.Position.x + offsetX, cardData.Position.y + offsetY));
        auto cardView = CardView::create(cardModel);
        this->addChild(cardView);
        _cardViews.pushBack(cardView);
    }
}

void GameScene::updateCardPositions() {
    for (auto cardView : _cardViews) {
        cardView->updatePosition();
    }
}