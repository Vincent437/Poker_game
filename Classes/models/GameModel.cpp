#include "GameModel.h"

GameModel::GameModel(const std::vector<CardConfig>& playfield,
    const std::vector<CardConfig>& stack)
    : _playfieldCards(playfield), _stackCards(stack) {
}