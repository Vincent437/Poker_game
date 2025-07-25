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
    // ��ʼ��������
    _controller = new LevelSelectController(this); // ���뵱ǰ������Ϊ������
    // ��ʱ�������������滻Ϊ���ü��أ�
    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(100, 100, 255, 255));
    this->addChild(background);

    setupUI(); // ��ʼ��UI����ʱ���գ�
    return true;
}

void LevelSelectScene::setupUI() {
    // ��ʱ���գ�����ʵ�ֹؿ���ť
}