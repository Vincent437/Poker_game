// managers/UndoManager.cpp
#include "UndoManager.h"
UndoManager::UndoManager(std::shared_ptr<GameModel> gameModel)
    : _gameModel(gameModel) {
}

//void UndoManager::recordMatchAction(const CardModel& originalTop,
//    const CardModel& matchedCard,
//    int playfieldIndex) {
//    _undoStack.push({
//        UndoType::PLAYFIELD_MATCH,
//        originalTop,
//        matchedCard,
//        playfieldIndex,
//		cocos2d::Vec2(originalTop.getPosition().x, originalTop.getPosition().y)
//        });
//}

void UndoManager::recordMatchAction(CardModel& originalTop,
    const CardModel& matchedCard,
    int playfieldIndex) {
    // ��ȡ������ԭʼλ��
    auto& playfieldCard = _gameModel->getPlayfieldCard(playfieldIndex);

    _undoStack.push({
        UndoType::PLAYFIELD_MATCH,
        originalTop,        // ԭ������
        matchedCard,        // ���ƶ���������
        playfieldIndex,     // ������ԭʼ����
        originalTop.getPosition(),  // ������ԭʼλ��
        playfieldCard.getPosition() // ������ԭʼλ�ã�������
        });
}

void UndoManager::recordOverrideStackAction(int stackIndex) {
    // ��¼�滻����
    auto& originalCard = _gameModel->getStackCard(stackIndex);
    auto& newCard = _gameModel->getStackCardModels().back();

    _undoStack.push({
        UndoType::STACK_REPLACE,
        originalCard,    // ԭʼ��
        newCard,         // ����
        stackIndex,      // Ŀ��λ��
        originalCard.getPosition() // ԭʼλ��
        });
}

void UndoManager::undoLastAction(GameModel& model, GameScene& scene) {
    if (_undoStack.empty()) return;

    auto action = _undoStack.top();
    _undoStack.pop();

    switch (action.type) {
        case UndoType::PLAYFIELD_MATCH:
            // 1. �ָ�������
            model.restorePlayfieldCard(action.newCard, action.fromIndex);

            // 2. �ָ�������������
            model.replaceTopStackCard(action.originalCard);

            // 3. ִ�з��򶯻�
            scene.undoLastMove(action.newCard, action.originalPlayfieldPos);
            break;
	    case UndoType::STACK_REPLACE:
            model.restoreStackCard(action.fromIndex, action.originalCard);

            // �ָ�������
            model.replaceTopStackCard(action.newCard);

            // ִ����ͼ����
            scene.undoStackOverride(action.fromIndex, action.originalCard);
            break;
    }
}