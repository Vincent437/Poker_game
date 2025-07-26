// Classes/controllers/GameController.cpp
#include "GameController.h"
#include "views/scene/GameScene.h"
#include "models/GameModel.h"
#include "views/CardView.h"
#include "services/CardMatchingService.h"

GameController::GameController(GameScene* scene, std::shared_ptr<GameModel> gameModel)
    : _scene(scene), _gameModel(gameModel){
	_undoManager = std::make_unique<UndoManager>(gameModel);
    onEnter();
}

void GameController::onEnter() {

    // 创建手牌区视图
    for (size_t i = 0; i < _gameModel->getStackCardModels().size(); ++i) {
        auto cardView = CardView::create(&_gameModel->getStackCardModels()[i]);
        cardView->setClickCallback([this, i]() {
                onStackCardClicked(i);
            });
        _scene->addStackCardView(cardView);
    }

    // 创建桌面牌视图
    for (size_t i = 0; i < _gameModel->getPlayfieldCardModels().size(); ++i) {
        auto cardView = CardView::create(&_gameModel->getPlayfieldCardModels()[i]);
        cardView->setClickCallback([this, i]() {
            onPlayfieldCardClicked(i);
            });
        _scene->addPlayfieldCardView(cardView);
    }
}

// controllers/GameController.cpp
void GameController::onStackCardClicked(int stackIndex) {
    if (stackIndex == _gameModel->getStackCardModels().size() - 1) {
        // 点击的是顶部牌（当前底牌）
        _scene->highlightStackTopCard();
        return;
    }
    // 获取要替换的牌信息
    auto& newTopCard = _gameModel->getStackCard(stackIndex);
    auto& originalTopCard = _gameModel->getStackCardModels().back();

    // 记录回退操作
    _undoManager->recordOverrideStackAction(stackIndex);

    // 执行替换
    _gameModel->overrideStackCard(stackIndex, originalTopCard);
    _gameModel->replaceTopStackCard(newTopCard);

    // 更新视图
    _scene->overrideStackCard(stackIndex);
}

void GameController::onPlayfieldCardClicked(int playfieldIndex) {
    auto& playfieldCard = _gameModel->getPlayfieldCardModels()[playfieldIndex];
    auto& topStackCard = _gameModel->getStackCardModels().back();

    // 检查点数是否相差1（忽略花色）
    if (abs(playfieldCard.getFace() - topStackCard.getFace()) == 1) {
        // 记录回退操作
        _undoManager->recordMatchAction(topStackCard, playfieldCard, playfieldIndex);

        // 执行匹配
        _gameModel->replaceTopStackCard(playfieldCard);
        _gameModel->removePlayfieldCard(playfieldIndex);

        // 更新视图
        _scene->moveCardToStackTop(playfieldIndex);
    }
}

void GameController::onUndoButtonClicked() {
    if (_undoManager->canUndo()) {
        _undoManager->undoLastAction(*_gameModel, *_scene);
    }
}