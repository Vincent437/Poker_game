// models/UndoModel.h
#pragma once
#include "configs/models/LevelConfig.h"
#include "CardModel.h"
#include "cocos2d.h"

//enum class UndoType {
//    STACK_REPLACE,
//    PLAYFIELD_MATCH
//};
//
//struct UndoAction {
//    UndoType type;
//    CardModel originalCard;
//    CardModel newCard;
//    int fromIndex; // 桌面牌索引（匹配时使用）
//    cocos2d::Vec2 originalStackPos;
//};
enum class UndoType {
    STACK_REPLACE,
    PLAYFIELD_MATCH
};

struct UndoAction {
    UndoType type;
    CardModel originalCard;  // 原顶部牌
    CardModel newCard;       // 被移动的牌
    int fromIndex;           // 桌面牌原始索引
    cocos2d::Vec2 originalStackPos;  // 手牌区原始位置
    cocos2d::Vec2 originalPlayfieldPos; // 桌面牌原始位置（新增）
};