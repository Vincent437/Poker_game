#include "LevelConfig.h"
#include <fstream>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

bool LevelConfig::initWithFile(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        json config;
        file >> config;

        // 解析 Playfield 卡牌
        if (config.contains("Playfield")) {
            for (const auto& cardJson : config["Playfield"]) {
                CardInitData card;
                card.id = static_cast<int>(_initialCards.size());
                card.number = cardJson["CardFace"].get<int>();
                card.suit = cardJson["CardSuit"].get<int>();
                card.initialState = 1;
                card.x = cardJson["Position"]["x"].get<float>();
                card.y = cardJson["Position"]["y"].get<float>();

                // 验证卡牌数据
                if (card.number < 0 || card.number >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES) ||
                    card.suit < 0 || card.suit >= static_cast<int>(CardSuitType::CST_NUM_CARD_SUIT_TYPES)) {
                    continue; // 跳过无效卡牌
                }

                _initialCards.push_back(card);
            }
        }

        // 解析 Stack 卡牌
        if (config.contains("Stack")) {
            for (const auto& cardJson : config["Stack"]) {
                CardInitData card;
                card.id = static_cast<int>(_initialCards.size());
                card.number = cardJson["CardFace"].get<int>();
                card.suit = cardJson["CardSuit"].get<int>();
                card.initialState = 0;

                // Stack 卡牌位置可能在游戏逻辑中处理，这里设为0或从配置读取
                if (cardJson.contains("Position")) {
                    card.x = cardJson["Position"]["x"].get<float>();
                    card.y = cardJson["Position"]["y"].get<float>();
                }
                else {
                    card.x = 0;
                    card.y = 0;
                }

                // 验证卡牌数据
                if (card.number < 0 || card.number >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES) ||
                    card.suit < 0 || card.suit >= static_cast<int>(CardSuitType::CST_NUM_CARD_SUIT_TYPES)) {
                    continue;
                }

                _initialCards.push_back(card);
            }
        }

        return !_initialCards.empty(); // 至少有一张卡牌才算成功
    }
    catch (...) {
        return false;
    }
}