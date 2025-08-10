#include <Geode/Geode.hpp>

using namespace geode::prelude;

inline void checkToHideDifficultyElements(std::string setting, GJGameLevel* level, GJDifficultySprite* difficultySprite, CCLabelBMFont* starsLabel, CCLabelBMFont* orbsLabel) {
    if (!Mod::get()->getSettingValue<bool>("enabled")) return;
    if (!Mod::get()->getSettingValue<bool>(setting)) return;
    if (Mod::get()->getSettingValue<bool>("only-hide-rated-levels") && !level->m_stars) return;
    if (Mod::get()->getSettingValue<bool>("only-hide-uncompleted-levels") && GameStatsManager::sharedState()->hasCompletedLevel(level)) return;
    std::string hiddenTextReplacement = Mod::get()->getSettingValue<std::string>("hidden-text-replacement");
    if (Mod::get()->getSettingValue<bool>("hide-difficulty")) {
        difficultySprite->updateDifficultyFrame(0, GJDifficultyName::Short);
    }
    if (Mod::get()->getSettingValue<bool>("hide-stars")) {
        starsLabel->setString(hiddenTextReplacement.c_str());
        starsLabel->updateLabel();
    }
    if (Mod::get()->getSettingValue<bool>("hide-orbs") && orbsLabel) {
        // orbtained
        int orbsObtained = GameStatsManager::sharedState()->getAwardedCurrencyForLevel(level);
        orbsLabel->setString(fmt::format("{}/{}", orbsObtained, hiddenTextReplacement.c_str()).c_str());
        orbsLabel->updateLabel();
    }
}