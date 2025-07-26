#include "GameModel.h"

GameModel::GameModel(const std::vector<CardConfig>& playfield,
    const std::vector<CardConfig>& stack)
    : _playfieldCards(playfield), _stackCards(stack) {
	// 初始化桌面牌和手牌区模型
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
		offsetX += 50; // 每张牌之间的水平间距
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
        // 记录原始位置用于回退
        auto originalPos = _stackCardModels[targetIndex].getPosition();

        // 替换指定位置的牌
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

// 1. 恢复桌面牌
void GameModel::restorePlayfieldCard(const CardModel& card, int index) {
    if (index >= 0 && index <= _playfieldCardModels.size()) {
        _playfieldCardModels.insert(_playfieldCardModels.begin() + index, card);
    }
}

// 2. 恢复手牌区顶部牌
void GameModel::replaceTopStackCard(const CardModel& newCard) {
    if (!_stackCardModels.empty()) {
        // 替换顶部牌（保留位置信息）
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