#include "MenuScene.h"
#include "ui/CocosGUI.h" // Cocos2d-x �� UI ���

USING_NS_CC;

MenuScene* MenuScene::create() {
    auto scene = new (std::nothrow) MenuScene();
    if (scene && scene->init()) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool MenuScene::init() {
    if (!Scene::init()) return false;

    // 1. ��ʼ��������
    _controller = new MenuController(this); // ���뵱ǰ������Ϊ������

    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(245, 222, 179, 255));
    this->addChild(background);
    // 2. ����UI
    setupUI();

    return true;
}

void MenuScene::setupUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // ʾ��������һ����ť��UI�߼���
    auto startButton = ui::Button::create("start.png", "start_pressed.png");
    startButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    startButton->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            _controller->onStartButtonClicked(); // ���ÿ������߼�
        }
        });
    this->addChild(startButton,1);
}