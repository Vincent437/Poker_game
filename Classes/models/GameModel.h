#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <vector>
#include <memory>
#include "CardModel.h"

class GameModel {
public:
    using CardPtr = std::shared_ptr<CardModel>;
    using CardList = std::vector<CardPtr>;

    bool init(int levelId);

    // Ö÷ÅÆ¶Ñ
    const CardList& getPlayFieldCards() const { return _playFieldCards; }
    void setPlayFieldCards(const CardList& cards) { _playFieldCards = cards; }

    // µ×ÅÆ¶Ñ
    const CardList& getStackCards() const { return _stackCards; }
    void addToStack(CardPtr card) { _stackCards.push_back(card); }
    void removeFromStack() { if (!_stackCards.empty()) _stackCards.pop_back(); }
    CardPtr getTopStackCard() const { return _stackCards.empty() ? nullptr : _stackCards.back(); }

    // ±¸ÓÃÅÆ¶Ñ
    const CardList& getReserveCards() const { return _reserveCards; }
    void setReserveCards(const CardList& cards) { _reserveCards = cards; }
    CardPtr drawReserveCard();

    // ÓÎÏ·×´Ì¬
    bool isGameOver() const { return _isGameOver; }
    bool isWin() const { return _isWin; }

    void setGameOver(bool isWin) {
        _isGameOver = true;
        _isWin = isWin;
    }

private:
    CardList _playFieldCards;   // Ö÷ÅÆ¶Ñ
    CardList _stackCards;       // µ×ÅÆ¶Ñ
    CardList _reserveCards;     // ±¸ÓÃÅÆ¶Ñ

    bool _isGameOver = false;
    bool _isWin = false;
    int _levelId = 0;
};

#endif // __GAME_MODEL_H__