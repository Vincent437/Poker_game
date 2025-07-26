// Classes/views/CardView.cpp
#include "CardView.h"

CardView* CardView::create(CardModel* model) {
    CardView* ret = new CardView();
    if (ret && ret->init(model)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init(CardModel* model) {
    if (!Node::init()) return false;

    _model = model;
    setupCardUI();
    updatePosition();
    this->setAnchorPoint(cocos2d:: Vec2::ANCHOR_BOTTOM_LEFT);
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event*) {
        auto localPos = this->convertToNodeSpace(touch->getLocation());
        if (cocos2d::Rect(0, 0, this->getContentSize().width, this->getContentSize().height).containsPoint(localPos)) {
        //if (this->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation()))) {
            if (_clickCallback) _clickCallback();
            return true;
        }
        return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void CardView::setupCardUI() {
    auto resConfig = CardResConfig::getInstance();

    // �������Ƶ�ͼ
    _baseSprite = cocos2d::Sprite::create(resConfig->getCardBasePath());
    this->addChild(_baseSprite);

    // ���ÿ��ƴ�С (�����ͼ��СΪ100x150)
    auto cardSize = _baseSprite->getContentSize();

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

    this->setContentSize(cardSize);  // ȷ���ڵ�ߴ��뾫��һ��
}

void CardView::updatePosition() {
    //_model->getPosition().y += 300;
    this->setPosition(_model->getPosition().x, _model->getPosition().y);
}

const CardModel* CardView::getModel() {
    return _model;
}

void CardView::setClickCallback(const std::function<void()>& callback) {
    _clickCallback = callback;
}
