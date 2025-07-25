#pragma once
#include "cocos2d.h"
#include "controllers/LevelSelectController.h" // Ensure this file defines LevelSelectController

class LevelSelectController; // Forward declaration to ensure the compiler knows about this class

class LevelSelectScene : public cocos2d::Scene {
public:
    static LevelSelectScene* create();
    virtual bool init() override;

    void setupUI(); // 初始化UI（暂时留空）
    //void setupUI(const std::vector<LevelModel*>& levels); // 由控制器调用

private:
    LevelSelectController* _controller; // Ensure LevelSelectController is defined
};