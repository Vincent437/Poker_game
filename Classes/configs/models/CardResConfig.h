#pragma once
#include <string>
#include <unordered_map>
#include "CardType.h"

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1) ^ (h2 >> (sizeof(size_t) * 8 - 1));
    }
};

class CardResConfig {
public:

    static CardResConfig* getInstance();

    // ��ʼ����Դ·��
    void init();

    // ��ȡ���Ƶ�ͼ·��
    std::string getCardBasePath() const { return "res/card_general.png"; }

    // ��ȡ����ͼƬ·��
    std::string getNumberPath(CardFaceType face, bool isBlack) const;

    // ��ȡ��ɫͼƬ·��
    std::string getSuitPath(CardSuitType suit) const;

private:
    static CardResConfig* _instance;
    std::unordered_map<std::pair<CardFaceType, bool>, std::string, PairHash> numberPaths;
    std::unordered_map<CardSuitType, std::string> suitPaths;
};