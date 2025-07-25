#include "LevelSelectScene.h"

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
    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(100, 100, 255, 255));
    this->addChild(background);

    setupUI(); // 初始化UI（暂时留空）
    return true;
}

void LevelSelectScene::setupUI() {
    // 暂时留空，后续实现关卡按钮
}