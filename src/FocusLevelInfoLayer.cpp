#include "Geode/Enums.hpp"
#include "Geode/binding/GJDifficultySprite.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

bool enabled = true;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;
        checkToHide();
        return true;
    }

    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        checkToHide();
    }

    void checkToHide() {
        if (!enabled) return;
        if (!Mod::get()->getSettingValue<bool>("hide-in-level-screens")) return;
        if (Mod::get()->getSettingValue<bool>("only-hide-rated-levels") && !m_level->m_stars) return;
        if (Mod::get()->getSettingValue<bool>("only-hide-uncompleted-levels") && GameStatsManager::sharedState()->hasCompletedLevel(m_level)) return;
        std::string hiddenTextReplacement = Mod::get()->getSettingValue<std::string>("hidden-text-replacement");
        if (Mod::get()->getSettingValue<bool>("hide-difficulty")) {
            m_difficultySprite->updateDifficultyFrame(0, GJDifficultyName::Short);
            if (Mod::get()->getSettingValue<bool>("hide-rate-demon-button")) {
                if (m_demonRateBtn) {
                    // i don't actually know a reason why someone would want to hide the button
                    // but be able to click it
                    // just in case though...
                    m_demonRateBtn->setOpacity(0);
                }
            }
        }
        if (Mod::get()->getSettingValue<bool>("hide-stars")) {
            m_starsLabel->setString(hiddenTextReplacement.c_str());
            m_starsLabel->updateLabel();
        }
        if (Mod::get()->getSettingValue<bool>("hide-orbs")) {
            // orbtained
            int orbsObtained = GameStatsManager::sharedState()->getAwardedCurrencyForLevel(m_level);
            m_orbsLabel->setString(fmt::format("{}/{}", orbsObtained, hiddenTextReplacement.c_str()).c_str());
            m_orbsLabel->updateLabel();
        }
    }
};

$execute {
    enabled = Mod::get()->getSettingValue<bool>("enabled");
    listenForSettingChangesV3("enabled", [](bool enabled) {
        ::enabled = enabled;
    });
}