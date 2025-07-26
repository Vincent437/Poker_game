// managers/UndoManager.h
#pragma once
#include "models/UndoModel.h"
#include "models/CardModel.h"
#include "models/GameModel.h"
#include "views/scene/GameScene.h"

class UndoManager {
public:
	UndoManager(std::shared_ptr<GameModel> gameModel);
    void recordMatchAction(CardModel& originalTop,
        const CardModel& matchedCard,
        int playfieldIndex);
    void recordOverrideStackAction(int stackIndex);
    bool canUndo() const { return !_undoStack.empty(); }
    void undoLastAction(GameModel& model, GameScene& scene);

private:
    std::stack<UndoAction> _undoStack;
	std::shared_ptr<GameModel> _gameModel; // 关联的游戏模型
};