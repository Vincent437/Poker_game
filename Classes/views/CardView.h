// Classes/views/CardView.h
#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "configs/models/CardResConfig.h"

class CardView : public cocos2d::Node {
public:
    static CardView* create(CardModel* model);
    virtual bool init(CardModel* model);

    void updatePosition();

    const CardModel* getModel();
    void setClickCallback(const std::function<void()>& callback);

private:
    void setupCardUI();
    std::function<void()> _clickCallback;

    CardModel* _model;
    cocos2d::Sprite* _baseSprite;
    cocos2d::Sprite* _numberSprite;
    cocos2d::Sprite* _suitSprite;
};