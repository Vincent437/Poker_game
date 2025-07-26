#include "GameModel.h"

GameModel::GameModel(const std::vector<CardConfig>& playfield,
    const std::vector<CardConfig>& stack)
    : _playfieldCards(playfield), _stackCards(stack) {
	// ��ʼ�������ƺ�������ģ��
    for(const auto& cardData : playfield) {
        _playfieldCardModels.push_back(CardModel(static_cast<CardFaceType>(cardData.CardFace),
            static_cast<CardSuitType>(cardData.CardSuit),
            cocos2d::Vec2(cardData.Position.x, cardData.Position.y+300)));
	}
    for(const auto& cardData : stack) {
        _stackCardModels.push_back(CardModel(static_cast<CardFaceType>(cardData.CardFace),
            static_cast<CardSuitType>(cardData.CardSuit),
            cocos2d::Vec2(cardData.Position.x, cardData.Position.y+300)));
	}
    auto container = stack;
	int offsetX = 100;
    for(int i=0; i<stack.size()-1; i++){
        _stackCardModels.push_back(CardModel(static_cast<CardFaceType>(container[i].CardFace),
            static_cast<CardSuitType>(container[i].CardSuit),
			cocos2d::Vec2(container[i].Position.x + offsetX, container[i].Position.y + 300)));
		offsetX += 50; // ÿ����֮���ˮƽ���
    }
    offsetX += 300;
    _stackCardModels.push_back(CardModel(static_cast<CardFaceType>(container.back().CardFace),
        static_cast<CardSuitType>(container.back().CardSuit),
		cocos2d::Vec2(container.back().Position.x + offsetX, container.back().Position.y + 300)));
}



void GameModel::removePlayfieldCard(int index) {
    if (index >= 0 && index < _playfieldCardModels.size()) {
        _playfieldCardModels.erase(_playfieldCardModels.begin() + index);
    }
}

void GameModel::overrideStackCard(int targetIndex, const CardModel& newCard) {
    if (targetIndex >= 0 && targetIndex < _stackCardModels.size()) {
        // ��¼ԭʼλ�����ڻ���
        auto originalPos = _stackCardModels[targetIndex].getPosition();

        // �滻ָ��λ�õ���
        _stackCardModels[targetIndex] = newCard;
        _stackCardModels[targetIndex].setPosition(originalPos);
    }
}

void GameModel::restoreStackCard(int targetIndex, const CardModel& originalCard) {
    if (targetIndex >= 0 && targetIndex < _stackCardModels.size()) {
        _stackCardModels[targetIndex] = originalCard;
    }
}

CardModel& GameModel::getStackCard(int index) {
    static CardModel emptyModel(CardFaceType::CFT_NONE, CardSuitType::CST_NONE, cocos2d::Vec2::ZERO);
    return (index >= 0 && index < _stackCardModels.size()) ?
        _stackCardModels[index] : emptyModel;
}

// 1. �ָ�������
void GameModel::restorePlayfieldCard(const CardModel& card, int index) {
    if (index >= 0 && index <= _playfieldCardModels.size()) {
        _playfieldCardModels.insert(_playfieldCardModels.begin() + index, card);
    }
}

// 2. �ָ�������������
void GameModel::replaceTopStackCard(const CardModel& newCard) {
    if (!_stackCardModels.empty()) {
        // �滻�����ƣ�����λ����Ϣ��
        auto position = _stackCardModels.back().getPosition();
        _stackCardModels.back() = newCard;
        _stackCardModels.back().setPosition(position);
    }
}

CardModel& GameModel::getPlayfieldCard(int index) {
    static CardModel emptyModel(CardFaceType::CFT_NONE, CardSuitType::CST_NONE, cocos2d::Vec2::ZERO);
    return (index >= 0 && index < _playfieldCardModels.size()) ?
        _playfieldCardModels[index] : emptyModel;
}