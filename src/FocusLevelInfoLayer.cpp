#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Focus.hpp"

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;
        checkToHideAllElements();
        return true;
    }
    
    void levelDownloadFinished(GJGameLevel* level) {
        LevelInfoLayer::levelDownloadFinished(level);
        checkToHideAllElements();
    }
    
    void checkToHideAllElements() {
        hideDifficultyElements("hide-in-level-screens", m_level, m_difficultySprite, m_starsLabel, m_orbsLabel);
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
};