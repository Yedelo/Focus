#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Focus.hpp"

#include <Geode/modify/LevelCell.hpp>
class $modify(LevelCell) {
    void loadCustomLevelCell() {
        LevelCell::loadCustomLevelCell();
        CCNode* difficultyContainer = m_mainLayer->getChildByID("difficulty-container");
        if (!difficultyContainer) return;
        GJDifficultySprite* difficultySprite = geode::cast::typeinfo_cast<GJDifficultySprite*>(difficultyContainer->getChildByID("difficulty-sprite"));
        CCLabelBMFont* starsLabel = geode::cast::typeinfo_cast<CCLabelBMFont*>(difficultyContainer->getChildByID("stars-label"));
        CCLabelBMFont* orbsLabel = geode::cast::typeinfo_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("orbs-label"));
        // may be null but checked in this function
        hideDifficultyElements(
            "hide-in-level-cells",
            m_level,
            difficultySprite,
            starsLabel,
            orbsLabel
        );
    }
};