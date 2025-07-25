#pragma once
#include <vector>
#include <string>
#include "cocos2d.h"

// 卡牌位置信息
struct CardPosition {
    int x;
    int y;
};

// 卡牌配置数据
struct CardConfig {
    int CardFace;  // 牌面数字（如 0=A, 1=2, ..., 12=K）
    int CardSuit;  // 花色（0=梅花, 1=方块, 2=红桃, 3=黑桃）
    CardPosition Position;
};

// 关卡配置
class LevelConfig {
public:
    std::vector<CardConfig> PlayfieldCards; // 主牌堆的牌
    std::vector<CardConfig> StackCards;     // 备用牌堆的牌

    bool initWithFile(const std::string& filepath); // 从JSON文件加载
};