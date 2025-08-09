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
        if (Mod::get()->getSettingValue<bool>("only-hide-uncompleted-levels") && GameStatsManager::sharedState()->hasCompletedLevel(m_level)) return;
        if (Mod::get()->getSettingValue<bool>("hide-stars-in-level-screen")) {
            m_starsLabel->setCString("?");
            m_starsLabel->updateLabel();
        }
        if (Mod::get()->getSettingValue<bool>("hide-difficulty-in-level-screen")) {
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
    }
};

$execute {
    enabled = Mod::get()->getSettingValue<bool>("enabled");
    listenForSettingChangesV3("enabled", [](bool enabled) {
        ::enabled = enabled;
    });
}