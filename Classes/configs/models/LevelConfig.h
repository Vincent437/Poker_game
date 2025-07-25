#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include <vector>
#include <string>

struct CardInitData {
    int id;
    int number;
    int suit;  // 0-3对应CardSuit枚举
    int initialState; // 0-covered, 1-revealed
    float x;   // 添加位置信息
    float y;
};

class LevelConfig {
public:
    bool initWithFile(const std::string& filename);

    int getLevelId() const { return _levelId; }
    const std::string& getLevelName() const { return _levelName; }
    const std::vector<CardInitData>& getInitialCards() const { return _initialCards; }
    int getReserveCardCount() const { return _reserveCardCount; }

private:
    int _levelId = 0;
    std::string _levelName;
    std::vector<CardInitData> _initialCards;
    int _reserveCardCount = 0;
};

#endif // __LEVEL_CONFIG_H__