#include <Geode/Geode.hpp>

using namespace geode::prelude;

#define STANDARD_DEMON_NUMBER 6
#define NA_NUMBER 0

void hideDifficultyElements(
    std::string setting,
    GJGameLevel *level, 
    GJDifficultySprite *difficultySprite, 
    CCLabelBMFont *starsLabel, 
    CCLabelBMFont *orbsLabel
) {
    if (!Mod::get()->getSettingValue<bool>("enabled")) return;
    if (!Mod::get()->getSettingValue<bool>(setting)) return;
    if (Mod::get()->getSettingValue<bool>("only-hide-rated-levels") && !level->m_stars) return;
    if (Mod::get()->getSettingValue<bool>("only-hide-uncompleted-levels") && GameStatsManager::sharedState()->hasCompletedLevel(level)) return;
    if (Mod::get()->getSettingValue<bool>("dont-hide-auto-levels") && level->m_autoLevel) return;
    std::string hiddenTextReplacement = Mod::get()->getSettingValue<std::string>("hidden-text-replacement");
    if (Mod::get()->getSettingValue<bool>("demon-mode") && level->m_stars == 10) {
        difficultySprite->updateDifficultyFrame(STANDARD_DEMON_NUMBER, GJDifficultyName::Short);
        return;
    }
    if (Mod::get()->getSettingValue<bool>("hide-difficulty") && difficultySprite) {
        difficultySprite->updateDifficultyFrame(NA_NUMBER, GJDifficultyName::Short);
    }
    if (Mod::get()->getSettingValue<bool>("hide-stars") && starsLabel) {
        starsLabel->setString(hiddenTextReplacement.c_str());
        starsLabel->updateLabel();
    }
    // the orbsLabel check is not only for unrated levels but for auto levels which give no orbs
    // if the level has ? stars and no orbs label i think you can figure out what the difficulty is
    if (Mod::get()->getSettingValue<bool>("hide-orbs") && orbsLabel) {
        // orbtained
        int orbsObtained = GameStatsManager::sharedState()->getAwardedCurrencyForLevel(level);
        orbsLabel->setString(fmt::format("{}/{}", orbsObtained, hiddenTextReplacement.c_str()).c_str());
        orbsLabel->updateLabel();
    }
}

void hideDifficultyElementsForLevelInfoLayer(LevelInfoLayer* levelInfoLayer) {
    hideDifficultyElements(
        "hide-in-level-screens", 
        levelInfoLayer->m_level, 
        levelInfoLayer->m_difficultySprite, 
        levelInfoLayer->m_starsLabel, 
        levelInfoLayer->m_orbsLabel
    );
}