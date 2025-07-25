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

    // ���������Ӹ�����Ϸ״̬������

private:
    std::vector<CardConfig> _playfieldCards;
    std::vector<CardConfig> _stackCards;

    // ʵ����Ϸ��Ӧ�ô洢CardModelָ�룬����򻯴���
};