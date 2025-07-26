#pragma once
#include "models/CardModel.h"

class CardMatchingService {
public:
    static bool isMatchValid(const CardModel* card1, const CardModel* card2) {
        if (!card1 || !card2) return false;
        return abs(card1->getFace() - card2->getFace()) == 1;
    }
};