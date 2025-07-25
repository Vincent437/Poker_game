#include "LevelSelectController.h"

LevelSelectController::LevelSelectController(cocos2d::Scene* scene) : _scene(scene) {
    loadLevels(); // 初始化
}

void LevelSelectController::loadLevels() {
    // 暂时留空，后续实现关卡加载逻辑
    CCLOG("LevelSelectController initialized.");
}