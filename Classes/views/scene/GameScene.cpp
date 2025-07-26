// Classes/views/scenes/GameScene.cpp
#include "GameScene.h"
#include "controllers/GameController.h"
#include "ui/CocosGUI.h" // Cocos2d-x �� UI ���
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

    // ��ȡҪ�ƶ��Ŀ�����ͼ
    auto movingCard = _playfieldCardViews[playfieldIndex];

    // ��ȡ����������λ�ã����һ���Ƶ�λ�ã�
    cocos2d::Vec2 targetPos;
    if (!_stackCardViews.empty()) {
        targetPos = _stackCardViews.back()->getPosition();
        // ��΢ƫ�Ʊ����ص�
        targetPos.x += 30;
    }
    else {
        // ���û�����ƣ�ʹ��Ĭ��λ��
        targetPos = cocos2d::Vec2(200, 100);
    }

    // ִ���ƶ�����
    movingCard->runAction(cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.5f, targetPos),
        cocos2d::CallFunc::create([this, movingCard, playfieldIndex]() {
            _model->getPlayfieldCardModels()[playfieldIndex].setPosition(
                movingCard->getPosition()
            );
            // ������ɺ�
            // 1. ��������ͼ�Ƴ�
            _playfieldCardViews.erase(_playfieldCardViews.begin() + playfieldIndex);

            // 2. ��ӵ���������ͼ
            _stackCardViews.push_back(movingCard);

            // 3. �����������㼶��ȷ�������������ϲ㣩
            for (size_t i = 0; i < _stackCardViews.size(); ++i) {
                _stackCardViews[i]->setLocalZOrder(i);
            }
            }),
        nullptr
    ));
}

void GameScene::undoCardMove(const CardModel& card, cocos2d::Vec2 originalPos) {
    // �ҵ��������е�Ŀ���ƣ�ͨ�������һ�ţ�
    if (!_stackCardViews.empty()) {
        auto movingCard = _stackCardViews.back();
        if( movingCard->getModel()->getFace() != card.getFace() ||
            movingCard->getModel()->getSuit() != card.getSuit()) {
            // ��������Ʋ���Ŀ���ƣ�ֱ�ӷ���
            return;
		}
        // ִ�з��򶯻�
        movingCard->runAction(cocos2d::Sequence::create(
            cocos2d::MoveTo::create(0.3f, originalPos),
            cocos2d::CallFunc::create([this, movingCard]() {
                // 1. ���������Ƴ�
                _stackCardViews.pop_back();

                // 2. ��ӻ�������ͼ
                _playfieldCardViews.push_back(movingCard);

                // 3. ���²㼶
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
	// ����������������
    if (!_stackCardViews.empty()) {
            auto topCard = _stackCardViews.back();
            topCard->setColor(cocos2d::Color3B::YELLOW); // �򵥸���Ч��
            // ������Ӹ��ද��Ч��
    }
}

void GameScene::overrideStackCard(int stackIndex) {
    if (stackIndex < 0 || stackIndex >= _stackCardViews.size()) return;

    // ��ȡҪ�ƶ����ƺ�Ŀ��λ��
    auto movingCard = _stackCardViews[stackIndex];
    auto targetPos = _stackCardViews.back()->getPosition();

    // ִ�ж���
    movingCard->runAction(cocos2d::Sequence::create(
        cocos2d::MoveTo::create(0.3f, targetPos),
        cocos2d::CallFunc::create([this, movingCard, stackIndex]() {
            // ����ģ��
            _stackCardViews.erase(_stackCardViews.begin() + stackIndex);

            // ��ӵ�����
            _stackCardViews.push_back(movingCard);

            // ���ò㼶
            for (size_t i = 0; i < _stackCardViews.size(); ++i) {
                _stackCardViews[i]->setLocalZOrder(i);
            }
            }),
        nullptr
    ));
}

void GameScene::undoStackOverride(int targetIndex, CardModel& originalCard) {
    // �ҵ���ǰ������
    if (!_stackCardViews.empty()) {
        auto movingCard = _stackCardViews.back();

        // ִ�з��򶯻�
        movingCard->runAction(cocos2d::Sequence::create(
            cocos2d::MoveTo::create(0.3f, originalCard.getPosition()),
            cocos2d::CallFunc::create([this, movingCard, targetIndex]() {
                // ������ͼ
                _stackCardViews.pop_back();
                _stackCardViews.insert(_stackCardViews.begin() + targetIndex, movingCard);

                // ���ò㼶
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
    // �ҵ��������е�Ŀ����
    if (!_stackCardViews.empty()) {
        auto movingCard = _stackCardViews.back();

        // ��֤������Ϣ
        if (movingCard->getModel()->getFace() == card.getFace() &&
            movingCard->getModel()->getSuit() == card.getSuit()) {

            // ִ�з��򶯻�
            movingCard->runAction(cocos2d::Sequence::create(
                cocos2d::MoveTo::create(0.3f, originalPos),
                cocos2d::CallFunc::create([this, movingCard]() {
                    // 1. ���������Ƴ�
                    _stackCardViews.pop_back();

                    // 2. ��ӻ�������ͼ
                    _playfieldCardViews.push_back(movingCard);

                    // 3. ���²㼶
                    movingCard->setLocalZOrder(_playfieldCardViews.size() - 1);
                    }),
                nullptr
            ));
        }
    }
}