#pragma once
#include <vector>
#include "CardModel.h"
#include "configs/models/LevelConfig.h"

class GameModel {
public:
    GameModel(const std::vector<CardConfig>& playfield,
        const std::vector<CardConfig>& stack);

    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }
    const std::vector<CardConfig>& getStackCards() const { return _stackCards; }

    // 这里可以添加更多游戏状态管理方法

private:
    std::vector<CardConfig> _playfieldCards;
    std::vector<CardConfig> _stackCards;

    // 实际游戏中应该存储CardModel指针，这里简化处理
};