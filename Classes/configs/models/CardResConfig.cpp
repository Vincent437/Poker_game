#include "CardResConfig.h"

CardResConfig* CardResConfig::_instance = nullptr;

CardResConfig* CardResConfig::getInstance() {
    if (!_instance) {
        _instance = new CardResConfig();
        _instance->init();
    }
    return _instance;
}

void CardResConfig::init() {
    // 初始化数字路径映射
    numberPaths = {
        {{CFT_ACE, false}, R"(D:\CPP\poker\Resources\res\number\big_black_A.png)"},
        {{CFT_TWO, false}, R"(D:\CPP\poker\Resources\res\number\big_black_2.png)"},
        {{CFT_THREE, false}, R"(D:\CPP\poker\Resources\res\number\big_black_3.png)"},
        {{CFT_FOUR, false}, R"(D:\CPP\poker\Resources\res\number\big_black_4.png)"},
        {{CFT_FIVE, false}, R"(D:\CPP\poker\Resources\res\number\big_black_5.png)"},
        {{CFT_SIX, false}, R"(D:\CPP\poker\Resources\res\number\big_black_6.png)"},
        {{CFT_SEVEN, false}, R"(D:\CPP\poker\Resources\res\number\big_black_7.png)"},
        {{CFT_EIGHT, false}, R"(D:\CPP\poker\Resources\res\number\big_black_8.png)"},
        {{CFT_NINE, false}, R"(D:\CPP\poker\Resources\res\number\big_black_9.png)"},
        {{CFT_TEN, false}, R"(D:\CPP\poker\Resources\res\number\big_black_10.png)"},
        {{CFT_JACK, false}, R"(D:\CPP\poker\Resources\res\number\big_black_J.png)"},
        {{CFT_QUEEN, false}, R"(D:\CPP\poker\Resources\res\number\big_black_Q.png)"},
        {{CFT_KING, false}, R"(D:\CPP\poker\Resources\res\number\big_black_K.png)"},
        {{CFT_ACE, true}, R"(D:\CPP\poker\Resources\res\number\big_red_A.png)"},
        {{CFT_TWO, true}, R"(D:\CPP\poker\Resources\res\number\big_red_2.png)"},
        {{CFT_THREE, true}, R"(D:\CPP\poker\Resources\res\number\big_red_3.png)"},
        {{CFT_FOUR, true}, R"(D:\CPP\poker\Resources\res\number\big_red_4.png)"},
        {{CFT_FIVE, true}, R"(D:\CPP\poker\Resources\res\number\big_red_5.png)"},
        {{CFT_SIX, true}, R"(D:\CPP\poker\Resources\res\number\big_red_6.png)"},
        {{CFT_SEVEN, true}, R"(D:\CPP\poker\Resources\res\number\big_red_7.png)"},
        {{CFT_EIGHT, true}, R"(D:\CPP\poker\Resources\res\number\big_red_8.png)"},
        {{CFT_NINE, true}, R"(D:\CPP\poker\Resources\res\number\big_red_9.png)"},
        {{CFT_TEN, true}, R"(D:\CPP\poker\Resources\res\number\big_red_10.png)"},
        {{CFT_JACK, true}, R"(D:\CPP\poker\Resources\res\number\big_red_J.png)"},
        {{CFT_QUEEN, true}, R"(D:\CPP\poker\Resources\res\number\big_red_Q.png)"},
        {{CFT_KING, true}, R"(D:\CPP\poker\Resources\res\number\big_red_K.png)"}
    };

    // 初始化花色路径映射
    suitPaths = {
        {CST_CLUBS,  R"(D:\CPP\poker\Resources\res\suits\club.png)"},
        {CST_DIAMONDS, R"(D:\CPP\poker\Resources\res\suits/diamond.png)"},
        {CST_HEARTS, R"(D:\CPP\poker\Resources\res\suits/heart.png)"},
        {CST_SPADES, R"(D:\CPP\poker\Resources\res\suits/spade.png)"}
    };
}

//void CardResConfig::init() {
//    // 初始化数字路径映射
//    numberPaths = {
//        {{CFT_ACE, false}, "res/number/big_black_A.png"},
//        {{CFT_TWO, false}, "res/number/big_black_2.png"},
//        {{CFT_THREE, false}, "res/number/big_black_3.png"},
//        {{CFT_FOUR, false}, "res/number/big_black_4.png"},
//        {{CFT_FIVE, false}, "res/number/big_black_5.png"},
//        {{CFT_SIX, false}, "res/number/big_black_6.png"},
//        {{CFT_SEVEN, false}, "res/number/big_black_7.png"},
//        {{CFT_EIGHT, false}, "res/number/big_black_8.png"},
//        {{CFT_NINE, false}, "res/number/big_black_9.png"},
//        {{CFT_TEN, false}, "res/number/big_black_10.png"},
//        {{CFT_JACK, false}, "res/number/big_black_J.png"},
//        {{CFT_QUEEN, false}, "res/number/big_black_Q.png"},
//        {{CFT_KING, false}, "res/number/big_black_K.png"},
//        {{CFT_ACE, true}, "res/number/big_red_A.png"},
//        {{CFT_TWO, true}, "res/number/big_red_2.png"},
//        {{CFT_THREE, true}, "res/number/big_red_3.png"},
//        {{CFT_FOUR, true}, "res/number/big_red_4.png"},
//        {{CFT_FIVE, true}, "res/number/big_red_5.png"},
//        {{CFT_SIX, true}, "res/number/big_red_6.png"},
//        {{CFT_SEVEN, true}, "res/number/big_red_7.png"},
//        {{CFT_EIGHT, true}, "res/number/big_red_8.png"},
//        {{CFT_NINE, true}, "res/number/big_red_9.png"},
//        {{CFT_TEN, true}, "res/number/big_red_10.png"},
//        {{CFT_JACK, true}, "res/number/big_red_J.png"},
//        {{CFT_QUEEN, true}, "res/number/big_red_Q.png"},
//        {{CFT_KING, true}, "res/number/big_red_K.png"}
//    };
//
//    // 初始化花色路径映射
//    suitPaths = {
//        {CST_CLUBS, "res/suits/clubs.png"},
//        {CST_DIAMONDS, "res/suits/diamonds.png"},
//        {CST_HEARTS, "res/suits/hearts.png"},
//        {CST_SPADES, "res/suits/spades.png"}
//    };
//}

std::string CardResConfig::getNumberPath(CardFaceType face, bool isBlack) const {
    auto it = numberPaths.find({ face , isBlack});
    return it != numberPaths.end() ? it->second : "";
}

std::string CardResConfig::getSuitPath(CardSuitType suit) const {
    auto it = suitPaths.find(suit);
    return it != suitPaths.end() ? it->second : "";
}