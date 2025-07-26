#pragma once
#include <vector>
#include "CardModel.h"
#include "configs/models/LevelConfig.h"

#include "UndoModel.h" // ��������ģ��

class GameModel {
public:
    GameModel(const std::vector<CardConfig>& playfield,
        const std::vector<CardConfig>& stack);

    const std::vector<CardConfig>& getPlayfieldCards() const { return _playfieldCards; }
    const std::vector<CardConfig>& getStackCards() const { return _stackCards; }

	std::vector<CardModel>& getPlayfieldCardModels() { return _playfieldCardModels; }
	std::vector<CardModel>& getStackCardModels() { return _stackCardModels; }

    // ����������
    void replaceTopStackCard(const CardModel& newCard);
    void removePlayfieldCard(int index);
    CardModel& getPlayfieldCard(int index);

    // �����Ʋ���
    CardModel& getStackCard(int index);
    void overrideStackCard(int targetIndex, const CardModel& newCard);

	// ���˲���
    void restoreStackCard(int targetIndex, const CardModel& originalCard);
    void restorePlayfieldCard(const CardModel& card, int index);
private:
    std::vector<CardConfig> _playfieldCards;
    std::vector<CardConfig> _stackCards;

	std::vector<CardModel> _playfieldCardModels; // ������ģ��
	std::vector<CardModel> _stackCardModels;     // ������ģ��
};