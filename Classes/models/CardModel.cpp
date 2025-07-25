#include "CardModel.h"

CardModel::CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position)
    : _face(face), _suit(suit), _position(position) {
}