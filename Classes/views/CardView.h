// Classes/views/CardView.h
#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "configs/models/CardResConfig.h"

class CardView : public cocos2d::Node {
public:
    static CardView* create(const CardModel* model);
    virtual bool init(const CardModel* model);

    void updatePosition();

private:
    void setupCardUI();

    const CardModel* _model;
    cocos2d::Sprite* _baseSprite;
    cocos2d::Sprite* _numberSprite;
    cocos2d::Sprite* _suitSprite;
};