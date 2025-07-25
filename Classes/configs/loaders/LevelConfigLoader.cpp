// LevelConfigLoader.cpp
#include "LevelConfigLoader.h"
#include "LevelConfig.h"
#include <memory>

LevelConfig* LevelConfigLoader::loadLevelConfig(int levelId) {
    // ���� levelId �����ļ��������磺
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