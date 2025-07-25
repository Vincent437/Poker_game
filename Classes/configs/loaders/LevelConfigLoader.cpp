// LevelConfigLoader.cpp
#include "LevelConfigLoader.h"
#include "LevelConfig.h"
#include <memory>

LevelConfig* LevelConfigLoader::loadLevelConfig(int levelId) {
    // 根据 levelId 构造文件名，例如：
    char filename[64];
    snprintf(filename, sizeof(filename), "levels/level_%d.json", levelId);
    return loadLevelConfigFromFile(filename);
}

LevelConfig* LevelConfigLoader::loadLevelConfigFromFile(const std::string& filename) {
    auto config = std::make_unique<LevelConfig>();
    if (config->initWithFile(filename)) {
        return config.release();
    }
    return nullptr;
}