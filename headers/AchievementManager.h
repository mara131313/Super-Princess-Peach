#pragma once
#include "Achievement.h"
#include <unordered_map>
#include <ranges>

class AchievementManager {
private:
    std::unordered_map<std::string, Achievement> achievements;

    AchievementManager() {
        achievements["Big Money"] = Achievement("BIG MONEY. Ai acumulat toti banii!");
        achievements["Slayer"] = Achievement("SLAYER. Ai omorat toti inamicii!");
        achievements["Time Saver"] = Achievement("TIME SAVER. Ai acumulat toate time boost-urile!");
        achievements["Healer"] = Achievement("HEALER. Ai acumulat toate heal-urile!");
    }

public:
    static AchievementManager& getInstance() {
        static AchievementManager instance;
        return instance;
    }

    void unlockAchievement(const std::string& name) {
        if (achievements.contains(name)) {
            achievements[name].unlock();
        }
    }

    void lockAllAchievements() {
        for (Achievement& achievement : achievements | std::views::values) {
            achievement.lock();
        }
    }

    bool isUnlocked(const std::string& name) {
        return achievements[name].isUnlocked();
    }
};