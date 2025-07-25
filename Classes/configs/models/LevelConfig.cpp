#include "LevelConfig.h"
#include <fstream>
#include <direct.h>
//#include <nlohmann/json.hpp> 
#include "nlohmann/json.hpp"

using json = nlohmann::json;

bool LevelConfig::initWithFile(const std::string& filename) {
    //try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            char buf[512];
            CCLOG("current dir: %s", _getcwd(buf,512));
            return false;
        }
        json config;
        file >> config;

        // 解析 Playfield 卡牌
        if (config.contains("Playfield")) {
            for (const auto& cardJson : config["Playfield"]) {
                CardConfig card;
                card.CardFace = cardJson["CardFace"].get<int>();
                card.CardSuit = cardJson["CardSuit"].get<int>();
                card.Position.x = cardJson["Position"]["x"].get<float>();
                card.Position.y = cardJson["Position"]["y"].get<float>();


                PlayfieldCards.push_back(card);
            }
        }

        // 解析 Stack 卡牌
        if (config.contains("Stack")) {
            for (const auto& cardJson : config["Stack"]) {
                CardConfig card;
                card.CardFace = cardJson["CardFace"].get<int>();
                card.CardSuit = cardJson["CardSuit"].get<int>();
                card.Position.x = cardJson["Position"]["x"].get<float>();
                card.Position.y = cardJson["Position"]["y"].get<float>();

                //// 验证卡牌数据
                //if (card.number < 0 || card.number >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES) ||
                //    card.suit < 0 || card.suit >= static_cast<int>(CardSuitType::CST_NUM_CARD_SUIT_TYPES)) {
                //    continue;
                //}

                StackCards.push_back(card);
            }
        }

        return true;
        //return !PlayfieldCards.empty(); // 至少有一张卡牌才算成功
    //}
    //catch (...) {
    //    return false;
    //}
}