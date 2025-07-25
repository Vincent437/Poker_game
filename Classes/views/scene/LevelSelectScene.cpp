#include "LevelSelectScene.h"
#include "ui/CocosGUI.h" // Cocos2d-x 的 UI 组件

LevelSelectScene* LevelSelectScene::create() {
    auto scene = new (std::nothrow) LevelSelectScene();
    if (scene && scene->init()) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool LevelSelectScene::init() {
    if (!Scene::init()) {
        return false;
    }
    // 初始化控制器
    _controller = new LevelSelectController(this); // 传入当前场景作为上下文
    // 临时背景（后续可替换为配置加载）
    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(245, 222, 179, 255));
    this->addChild(background);

    setupUI();
    return true;
}

void LevelSelectScene::setupUI() {
    auto level0Button = cocos2d::ui::Button::create("level.png", "level_pressed.png");
    level0Button->setTitleText("Level 0");
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    level0Button->setPosition(cocos2d::Vec2(visibleSize.width / 2, 8* visibleSize.height / 10));
    level0Button->addTouchEventListener([this](Ref*, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            _controller->onLevel0ButtonClicked();
        }
        });
    addChild(level0Button);
}

