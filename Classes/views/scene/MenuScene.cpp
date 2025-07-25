#include "MenuScene.h"
#include "ui/CocosGUI.h" // Cocos2d-x 的 UI 组件

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

    // 1. 初始化控制器
    _controller = new MenuController(this); // 传入当前场景作为上下文

    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(245, 222, 179, 255));
    this->addChild(background);
    // 2. 设置UI
    setupUI();

    return true;
}

void MenuScene::setupUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // 示例：创建一个按钮（UI逻辑）
    auto startButton = ui::Button::create("start.png", "start_pressed.png");
    startButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    startButton->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            _controller->onStartButtonClicked(); // 调用控制器逻辑
        }
        });
    this->addChild(startButton,1);
}