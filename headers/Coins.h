#pragma once
#include "Object.h"
#include "AchievementManager.h"

class Coins : public Object {
private:
    static int cntC;
public:
    Coins(const float x, const float y)
        : Object(x, y, 10, sf::Color::Yellow) {
    }

    void interact() const override {
        std::cout << "Banut colectat." << std::endl;
        ++cntC;
        if (cntC == 62) {
            AchievementManager::getInstance().unlockAchievement("Big Money");
        }
    }

    void makeAppear(float& adjustedTime) override {
        if (static_cast<int>(adjustedTime) % 10 < 5) {
            setVisible(true);
        } else {
            setVisible(false);
        }
    }

    static void setCnt() {
        cntC = 0;
    }

    std::shared_ptr<Object> clone() const override {
        return std::make_unique<Coins>(*this);
    }
};