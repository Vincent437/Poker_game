// Classes/views/scenes/GameScene.cpp
#include "GameScene.h"
#include "controllers/GameController.h"
#include "ui/CocosGUI.h" // Cocos2d-x 的 UI 组件
#include <string>

GameScene* GameScene::create(std::shared_ptr<GameModel> model) {
    auto scene = new (std::nothrow) GameScene();
    if (scene && scene->init(model)) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool GameScene::init(std::shared_ptr<GameModel> model) {
    if (!Scene::init()) return false;
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto topLayer = cocos2d::LayerColor::create(cocos2d::Color4B(200, 200, 200, 255));
    topLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height*2));

    auto bottomLayer = cocos2d::LayerColor::create(cocos2d::Color4B(128, 64, 0, 255));
    bottomLayer->setContentSize(cocos2d::Size(visibleSize.width, visibleSize.height / 3));


    this->addChild(topLayer);
    this->addChild(bottomLayer);
    _model = model;

    auto undoButton = cocos2d::ui::Button::create("undo.png", "undo_pressed.png");
    undoButton->setPosition(cocos2d::Vec2(visibleSize.width - undoButton->getContentSize().width,
        undoButton->getContentSize().height * 2));
    undoButton->addTouchEventListener([this](Ref*, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            _controller->onUndoButtonClicked();
        }
        });

    addChild(undoButton);

    return true;
}


void GameScene::setController(std::unique_ptr<GameController> controller) {
    _controller = std::move(controller);
}


void GameScene::updateCardPositions() {
    for (auto cardView : _cardViews) {
        cardView->updatePosition();
    }
}


void GameScene::moveCardToStackTop(int playfieldIndex) {
    if (playfieldIndex < 0 || playfieldIndex >= _playfieldCardViews.size()) return;

    // 获取要移动的卡牌视图
    auto movingCard = _playfieldCardViews[playfieldIndex];

    // 获取手牌区顶部位置（最后一张牌的位置）
    cocos2d::Vec2 targetPos;
    if (!_stackCardViews.empty()) {
        targetPos = _stackCardViews.back()->getPosition();
        // 稍微偏移避免重叠
        targetPos.x += 30;
    }
    else {
        // 如果没有手牌，使用默认位置
        targetPos = cocos2d::Vec2(200, 100);
    }

    // 执行移动动画
    movingCard->runAction(cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.5f, targetPos),
        cocos2d::CallFunc::create([this, movingCard, playfieldIndex]() {
            _model->getPlayfieldCardModels()[playfieldIndex].setPosition(
                movingCard->getPosition()
            );
            // 动画完成后：
            // 1. 从桌面视图移除
            _playfieldCardViews.erase(_playfieldCardViews.begin() + playfieldIndex);

            // 2. 添加到手牌区视图
            _stackCardViews.push_back(movingCard);

            // 3. 更新手牌区层级（确保顶部牌在最上层）
            for (size_t i = 0; i < _stackCardViews.size(); ++i) {
                _stackCardViews[i]->setLocalZOrder(i);
            }
            }),
        nullptr
    ));
}

void GameScene::undoCardMove(const CardModel& card, cocos2d::Vec2 originalPos) {
    // 找到手牌区中的目标牌（通常是最后一张）
    if (!_stackCardViews.empty()) {
        auto movingCard = _stackCardViews.back();
        if( movingCard->getModel()->getFace() != card.getFace() ||
            movingCard->getModel()->getSuit() != card.getSuit()) {
            // 如果顶部牌不是目标牌，直接返回
            return;
		}
        // 执行反向动画
        movingCard->runAction(cocos2d::Sequence::create(
            cocos2d::MoveTo::create(0.3f, originalPos),
            cocos2d::CallFunc::create([this, movingCard]() {
                // 1. 从手牌区移除
                _stackCardViews.pop_back();

                // 2. 添加回桌面视图
                _playfieldCardViews.push_back(movingCard);

                // 3. 更新层级
                movingCard->setLocalZOrder(_playfieldCardViews.size() - 1);
                }),
            nullptr
        ));
    }
}

void GameScene::addStackCardView(CardView* cardView) {
    _stackCardViews.push_back(cardView);
    this->addChild(cardView);
}

void GameScene::addPlayfieldCardView(CardView* cardView) {
    _playfieldCardViews.push_back(cardView);
    this->addChild(cardView);
}

void GameScene::highlightStackTopCard(){
	// 高亮手牌区顶部牌
    if (!_stackCardViews.empty()) {
            auto topCard = _stackCardViews.back();
            topCard->setColor(cocos2d::Color3B::YELLOW); // 简单高亮效果
            // 可以添加更多动画效果
    }
}

void GameScene::overrideStackCard(int stackIndex) {
    if (stackIndex < 0 || stackIndex >= _stackCardViews.size()) return;

    // 获取要移动的牌和目标位置
    auto movingCard = _stackCardViews[stackIndex];
    auto targetPos = _stackCardViews.back()->getPosition();

    // 执行动画
    movingCard->runAction(cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.3f, targetPos),
        cocos2d::CallFunc::create([this, movingCard, stackIndex]() {
            // 更新模型
            _stackCardViews.erase(_stackCardViews.begin() + stackIndex);

            // 添加到顶部
            _stackCardViews.push_back(movingCard);

            // 重置层级
            for (size_t i = 0; i < _stackCardViews.size(); ++i) {
                _stackCardViews[i]->setLocalZOrder(i);
            }
            }),
        nullptr
    ));
}

void GameScene::undoStackOverride(int targetIndex, CardModel& originalCard) {
    // 找到当前顶部牌
    if (!_stackCardViews.empty()) {
        auto movingCard = _stackCardViews.back();

        // 执行反向动画
        movingCard->runAction(cocos2d::Sequence::create(
            cocos2d::MoveTo::create(0.3f, originalCard.getPosition()),
            cocos2d::CallFunc::create([this, movingCard, targetIndex]() {
                // 更新视图
                _stackCardViews.pop_back();
                _stackCardViews.insert(_stackCardViews.begin() + targetIndex, movingCard);

                // 重置层级
                for (size_t i = 0; i < _stackCardViews.size(); ++i) {
                    _stackCardViews[i]->setLocalZOrder(i);
                }
                }),
            nullptr
        ));
    }
}

// GameScene.cpp
void GameScene::undoLastMove(const CardModel& card, cocos2d::Vec2 originalPos) {
    // 找到手牌区中的目标牌
    if (!_stackCardViews.empty()) {
        auto movingCard = _stackCardViews.back();

        // 验证牌面信息
        if (movingCard->getModel()->getFace() == card.getFace() &&
            movingCard->getModel()->getSuit() == card.getSuit()) {

            // 执行反向动画
            movingCard->runAction(cocos2d::Sequence::create(
                cocos2d::MoveTo::create(0.3f, originalPos),
                cocos2d::CallFunc::create([this, movingCard]() {
                    // 1. 从手牌区移除
                    _stackCardViews.pop_back();

                    // 2. 添加回桌面视图
                    _playfieldCardViews.push_back(movingCard);

                    // 3. 更新层级
                    movingCard->setLocalZOrder(_playfieldCardViews.size() - 1);
                    }),
                nullptr
            ));
        }
    }
}