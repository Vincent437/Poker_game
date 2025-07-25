#pragma once
#include "cocos2d.h"
#include "controllers/LevelSelectController.h" // Ensure this file defines LevelSelectController

class LevelSelectController; // Forward declaration to ensure the compiler knows about this class

class LevelSelectScene : public cocos2d::Scene {
public:
    static LevelSelectScene* create();
    virtual bool init() override;

    void setupUI(); // ��ʼ��UI����ʱ���գ�
    //void setupUI(const std::vector<LevelModel*>& levels); // �ɿ���������

private:
    LevelSelectController* _controller; // Ensure LevelSelectController is defined
};