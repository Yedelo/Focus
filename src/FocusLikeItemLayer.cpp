#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "Focus.hpp"

#include <Geode/modify/LikeItemLayer.hpp>
class $modify(LikeItemLayer) {
    void triggerLike(bool isLiked) {
        // i think triggerLike destroys the parent relationship so lets get it before that happens
        CCScene* mainScene = geode::cast::typeinfo_cast<CCScene*>(getParent());
        LikeItemLayer::triggerLike(isLiked);
        if (LevelInfoLayer* levelInfoLayer = geode::cast::typeinfo_cast<LevelInfoLayer*>(mainScene->getChildByID("LevelInfoLayer"))) {
            hideDifficultyElementsForLevelInfoLayer(levelInfoLayer);
        }
    }
};