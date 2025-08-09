#include <Geode/Geode.hpp>

using namespace geode::prelude;

bool enabled = true;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;
        checkToHideStarCount();
        return true;
    }

    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        checkToHideStarCount();
    }

    void checkToHideStarCount() {
        if (enabled && Mod::get()->getSettingValue<bool>("hide-stars-in-level-screen")) {
            if (Mod::get()->getSettingValue<bool>("only-hide-uncompleted-levels") && GameStatsManager::sharedState()->hasCompletedLevel(m_level)) return;
            m_starsLabel->setCString("?");
            m_starsLabel->updateLabel();
        }
    }
};

$execute {
    enabled = Mod::get()->getSettingValue<bool>("enabled");
    listenForSettingChangesV3("enabled", [](bool enabled) {
        ::enabled = enabled;
    });
}