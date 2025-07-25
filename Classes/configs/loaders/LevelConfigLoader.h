#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

#include "configs/models/LevelConfig.h"
#include <string>

class LevelConfigLoader {
public:
    static LevelConfig* loadLevelConfig(int levelId);
    static LevelConfig* loadLevelConfigFromFile(const std::string& filename);

private:
    LevelConfigLoader() = delete;
};

#endif // __LEVEL_CONFIG_LOADER_H__