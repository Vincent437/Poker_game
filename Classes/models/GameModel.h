#pragma once
#include <vector>
#include "CardModel.h"
#include "configs/models/LevelConfig.h"

#include "UndoModel.h" // 新增回退模型

class GameModel {
public:
    GameModel(const std::vector<CardConfig>& playfield,
        const std::vector<CardConfig>& stack);

    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }
    const std::vector<CardConfig>& getStackCards() const { return _stackCards; }

	std::vector<CardModel>& getPlayfieldCardModels() { return _playfieldCardModels; }
	std::vector<CardModel>& getStackCardModels() { return _stackCardModels; }

    // 手牌区操作
    void replaceTopStackCard(const CardModel& newCard);
    void removePlayfieldCard(int index);
    CardModel& getPlayfieldCard(int index);

    // 备用牌操作
    CardModel& getStackCard(int index);
    void overrideStackCard(int targetIndex, const CardModel& newCard);

	// 回退操作
    void restoreStackCard(int targetIndex, const CardModel& originalCard);
    void restorePlayfieldCard(const CardModel& card, int index);
private:
    std::vector<CardConfig> _playfieldCards;
    std::vector<CardConfig> _stackCards;

	std::vector<CardModel> _playfieldCardModels; // 桌面牌模型
	std::vector<CardModel> _stackCardModels;     // 手牌区模型
};