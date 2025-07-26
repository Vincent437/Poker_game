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
    // 获取桌面牌原始位置
    auto& playfieldCard = _gameModel->getPlayfieldCard(playfieldIndex);

    _undoStack.push({
        UndoType::PLAYFIELD_MATCH,
        originalTop,        // 原顶部牌
        matchedCard,        // 被移动的桌面牌
        playfieldIndex,     // 桌面牌原始索引
        originalTop.getPosition(),  // 手牌区原始位置
        playfieldCard.getPosition() // 桌面牌原始位置（新增）
        });
}

void UndoManager::recordOverrideStackAction(int stackIndex) {
    // 记录替换操作
    auto& originalCard = _gameModel->getStackCard(stackIndex);
    auto& newCard = _gameModel->getStackCardModels().back();

    _undoStack.push({
        UndoType::STACK_REPLACE,
        originalCard,    // 原始牌
        newCard,         // 新牌
        stackIndex,      // 目标位置
        originalCard.getPosition() // 原始位置
        });
}

void UndoManager::undoLastAction(GameModel& model, GameScene& scene) {
    if (_undoStack.empty()) return;

    auto action = _undoStack.top();
    _undoStack.pop();

    switch (action.type) {
        case UndoType::PLAYFIELD_MATCH:
            // 1. 恢复桌面牌
            model.restorePlayfieldCard(action.newCard, action.fromIndex);

            // 2. 恢复手牌区顶部牌
            model.replaceTopStackCard(action.originalCard);

            // 3. 执行反向动画
            scene.undoLastMove(action.newCard, action.originalPlayfieldPos);
            break;
	    case UndoType::STACK_REPLACE:
            model.restoreStackCard(action.fromIndex, action.originalCard);

            // 恢复顶部牌
            model.replaceTopStackCard(action.newCard);

            // 执行视图回退
            scene.undoStackOverride(action.fromIndex, action.originalCard);
            break;
    }
}