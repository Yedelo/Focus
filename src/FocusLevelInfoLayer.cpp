#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Focus.hpp"

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(FocusLevelInfoLayer, LevelInfoLayer) {
    struct Fields {
        bool m_revealedDifficultyInformation = false;
    };

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;
        hideAllDifficultyElements();
        return true;
    }
    
    void levelDownloadFinished(GJGameLevel* level) {
        LevelInfoLayer::levelDownloadFinished(level);
        hideAllDifficultyElements();
    }
    
    void hideAllDifficultyElements() {
        hideDifficultyElementsForLevelInfoLayer(this);
        if (
            Mod::get()->getSettingValue<bool>("enabled") 
            && Mod::get()->getSettingValue<bool>("hide-difficulty") 
            && Mod::get()->getSettingValue<bool>("hide-rate-demon-button") 
            && m_demonRateBtn
        ) {
            // i don't actually know a reason why someone would want to hide the button
            // but be able to click it
            // just in case though...
            m_demonRateBtn->setOpacity(0);
        }
    }

    void revealDifficultyInformation() {
        m_fields->m_revealedDifficultyInformation = true;
        updateLabelValues();
    }
};

void hideDifficultyElementsForLevelInfoLayer(LevelInfoLayer* levelInfoLayer) {
    if (!static_cast<FocusLevelInfoLayer*>(levelInfoLayer)->m_fields->m_revealedDifficultyInformation) {
        hideDifficultyElements(
            "hide-in-level-screens", 
            levelInfoLayer->m_level, 
            levelInfoLayer->m_difficultySprite, 
            levelInfoLayer->m_starsLabel, 
            levelInfoLayer->m_orbsLabel
        );
    }
}