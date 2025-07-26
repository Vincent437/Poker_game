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
//    int fromIndex; // ������������ƥ��ʱʹ�ã�
//    cocos2d::Vec2 originalStackPos;
//};
enum class UndoType {
    STACK_REPLACE,
    PLAYFIELD_MATCH
};

struct UndoAction {
    UndoType type;
    CardModel originalCard;  // ԭ������
    CardModel newCard;       // ���ƶ�����
    int fromIndex;           // ������ԭʼ����
    cocos2d::Vec2 originalStackPos;  // ������ԭʼλ��
    cocos2d::Vec2 originalPlayfieldPos; // ������ԭʼλ�ã�������
};