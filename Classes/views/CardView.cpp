// Classes/views/CardView.cpp
#include "CardView.h"

CardView* CardView::create(const CardModel* model) {
    CardView* ret = new CardView();
    if (ret && ret->init(model)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init(const CardModel* model) {
    if (!Node::init()) return false;

    _model = model;
    setupCardUI();
    updatePosition();

    return true;
}

void CardView::setupCardUI() {
    auto resConfig = CardResConfig::getInstance();

    // �������Ƶ�ͼ
    _baseSprite = cocos2d::Sprite::create(resConfig->getCardBasePath());
    this->addChild(_baseSprite);

    // ���ÿ��ƴ�С (�����ͼ��СΪ100x150)
    auto cardSize = _baseSprite->getContentSize();
    this->setContentSize(cardSize);

    // �������ֺͻ�ɫ (����򻯴���ʵ��Ӧ���ݿ�����ֵ����λ��)
    _numberSprite = cocos2d::Sprite::create(resConfig->getNumberPath(_model->getFace(), _model->isRedSuit()));
    
    /*float numberX = cardSize.width / 2;
    float numberY = cardSize.height / 2;*/
    //_numberSprite->setPosition(numberX, numberY);
    _numberSprite->setPosition(0, 0);
    this->addChild(_numberSprite);

    _suitSprite = cocos2d::Sprite::create(resConfig->getSuitPath(_model->getSuit()));
    
    float suitX = cardSize.width/2 - _suitSprite->getContentSize().width;
    float suitY = cardSize.height/2 - _suitSprite->getContentSize().height;
    _suitSprite->setPosition(suitX, suitY);
    this->addChild(_suitSprite);

    //// ���½�Ҳ������ֺͻ�ɫ (�򻯴���)
    //auto number2 = cocos2d::Sprite::create(resConfig->getNumberTexturePath(_model->getFace(), isRed));
    //number2->setPosition(this->getContentSize().width * 0.7f,
    //    this->getContentSize().height * 0.3f);
    //number2->setRotation(180);
    //this->addChild(number2);

    //auto suit2 = cocos2d::Sprite::create(resConfig->getSuitTexturePath(_model->getSuit(), isRed));
    //suit2->setPosition(this->getContentSize().width * 0.7f,
    //    this->getContentSize().height * 0.15f);
    //suit2->setRotation(180);
    //this->addChild(suit2);
}

void CardView::updatePosition() {
    this->setPosition(_model->getPosition().x, _model->getPosition().y + 300);
}