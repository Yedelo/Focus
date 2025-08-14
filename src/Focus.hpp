#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

void hideDifficultyElements(
    std::string setting, 
    GJGameLevel* level,
    GJDifficultySprite* difficultySprite, 
    CCLabelBMFont* starsLabel, 
    CCLabelBMFont* orbsLabel
);
void hideDifficultyElementsForLevelInfoLayer(LevelInfoLayer* levelInfoLayer);
bool revealedDifficultyInformation(LevelInfoLayer* levelInfoLayer);