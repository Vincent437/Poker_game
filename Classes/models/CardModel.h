#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include <string>

// ��ɫ����
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // ÷��
    CST_DIAMONDS,   // ����
    CST_HEARTS,     // ����
    CST_SPADES,     // ����
    CST_NUM_CARD_SUIT_TYPES
};

// ��������
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

enum class CardSuit {
    HEART,
    DIAMOND,
    CLUB,
    SPADE,
    NONE
};

enum class CardState {
    COVERED,    // ���ŵ�
    REVEALED,   // ������
    MATCHED,    // ��ƥ������
    INVALID
};

class CardModel {
public:
    CardModel(int id, int number, CardSuit suit);

    int getId() const { return _id; }
    int getNumber() const { return _number; }
    CardSuit getSuit() const { return _suit; }
    CardState getState() const { return _state; }

    void setState(CardState state) { _state = state; }

    bool isRevealed() const { return _state == CardState::REVEALED; }
    bool isMatched() const { return _state == CardState::MATCHED; }
    bool isCovered() const { return _state == CardState::COVERED; }

    std::string getResourceName() const;

private:
    int _id;
    int _number;    // 1-13 (A-K)
    CardSuit _suit;
    CardState _state = CardState::COVERED;
};

#endif // __CARD_MODEL_H__