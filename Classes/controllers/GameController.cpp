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

    // ������������ͼ
    for (size_t i = 0; i < _gameModel->getStackCardModels().size(); ++i) {
        auto cardView = CardView::create(&_gameModel->getStackCardModels()[i]);
        cardView->setClickCallback([this, i]() {
                onStackCardClicked(i);
            });
        _scene->addStackCardView(cardView);
    }

    // ������������ͼ
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
        // ������Ƕ����ƣ���ǰ���ƣ�
        _scene->highlightStackTopCard();
        return;
    }
    // ��ȡҪ�滻������Ϣ
    auto& newTopCard = _gameModel->getStackCard(stackIndex);
    auto& originalTopCard = _gameModel->getStackCardModels().back();

    // ��¼���˲���
    _undoManager->recordOverrideStackAction(stackIndex);

    // ִ���滻
    _gameModel->overrideStackCard(stackIndex, originalTopCard);
    _gameModel->replaceTopStackCard(newTopCard);

    // ������ͼ
    _scene->overrideStackCard(stackIndex);
}

void GameController::onPlayfieldCardClicked(int playfieldIndex) {
    auto& playfieldCard = _gameModel->getPlayfieldCardModels()[playfieldIndex];
    auto& topStackCard = _gameModel->getStackCardModels().back();

    // �������Ƿ����1�����Ի�ɫ��
    if (abs(playfieldCard.getFace() - topStackCard.getFace()) == 1) {
        // ��¼���˲���
        _undoManager->recordMatchAction(topStackCard, playfieldCard, playfieldIndex);

        // ִ��ƥ��
        _gameModel->replaceTopStackCard(playfieldCard);
        _gameModel->removePlayfieldCard(playfieldIndex);

        // ������ͼ
        _scene->moveCardToStackTop(playfieldIndex);
    }
}

void GameController::onUndoButtonClicked() {
    if (_undoManager->canUndo()) {
        _undoManager->undoLastAction(*_gameModel, *_scene);
    }
}