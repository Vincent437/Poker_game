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

        // ���� Playfield ����
        if (config.contains("Playfield")) {
            for (const auto& cardJson : config["Playfield"]) {
                CardInitData card;
                card.id = static_cast<int>(_initialCards.size());
                card.number = cardJson["CardFace"].get<int>();
                card.suit = cardJson["CardSuit"].get<int>();
                card.initialState = 1;
                card.x = cardJson["Position"]["x"].get<float>();
                card.y = cardJson["Position"]["y"].get<float>();

                // ��֤��������
                if (card.number < 0 || card.number >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES) ||
                    card.suit < 0 || card.suit >= static_cast<int>(CardSuitType::CST_NUM_CARD_SUIT_TYPES)) {
                    continue; // ������Ч����
                }

                _initialCards.push_back(card);
            }
        }

        // ���� Stack ����
        if (config.contains("Stack")) {
            for (const auto& cardJson : config["Stack"]) {
                CardInitData card;
                card.id = static_cast<int>(_initialCards.size());
                card.number = cardJson["CardFace"].get<int>();
                card.suit = cardJson["CardSuit"].get<int>();
                card.initialState = 0;

                // Stack ����λ�ÿ�������Ϸ�߼��д���������Ϊ0������ö�ȡ
                if (cardJson.contains("Position")) {
                    card.x = cardJson["Position"]["x"].get<float>();
                    card.y = cardJson["Position"]["y"].get<float>();
                }
                else {
                    card.x = 0;
                    card.y = 0;
                }

                // ��֤��������
                if (card.number < 0 || card.number >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES) ||
                    card.suit < 0 || card.suit >= static_cast<int>(CardSuitType::CST_NUM_CARD_SUIT_TYPES)) {
                    continue;
                }

                _initialCards.push_back(card);
            }
        }

        return !_initialCards.empty(); // ������һ�ſ��Ʋ���ɹ�
    }
    catch (...) {
        return false;
    }
}