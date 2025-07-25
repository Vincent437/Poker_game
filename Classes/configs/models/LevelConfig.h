#pragma once
#include <vector>
#include <string>
#include "cocos2d.h"

// ����λ����Ϣ
struct CardPosition {
    int x;
    int y;
};

// ������������
struct CardConfig {
    int CardFace;  // �������֣��� 0=A, 1=2, ..., 12=K��
    int CardSuit;  // ��ɫ��0=÷��, 1=����, 2=����, 3=���ң�
    CardPosition Position;
};

// �ؿ�����
class LevelConfig {
public:
    std::vector<CardConfig> PlayfieldCards; // ���ƶѵ���
    std::vector<CardConfig> StackCards;     // �����ƶѵ���

    bool initWithFile(const std::string& filepath); // ��JSON�ļ�����
};