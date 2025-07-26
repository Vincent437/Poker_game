#pragma once
#include "configs/models/CardResConfig.h"
#include "cocos2d.h"

class CardModel {
public:
    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position);

    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    cocos2d::Vec2& getPosition() { return _position; }
    bool isRedSuit() const {
        return _suit == CardSuitType::CST_HEARTS || _suit == CardSuitType::CST_DIAMONDS;
    }

    void setPosition(const cocos2d::Vec2& position) { _position = position; }

private:
    CardFaceType _face;
    CardSuitType _suit;
    cocos2d::Vec2 _position;
};