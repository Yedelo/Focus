#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Focus.hpp"

#include <Geode/modify/LevelCell.hpp>
class $modify(LevelCell) {
    void loadCustomLevelCell() {
        LevelCell::loadCustomLevelCell();
        CCNode* difficultyContainer = m_mainLayer->getChildByID("difficulty-container");
        checkToHideDifficultyElements(
            "hide-in-level-cells",
            m_level,
            static_cast<GJDifficultySprite*>(difficultyContainer->getChildByID("difficulty-sprite")),
            static_cast<CCLabelBMFont*>(difficultyContainer->getChildByID("stars-label")),
            static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("orbs-label"))
        );
    }
};