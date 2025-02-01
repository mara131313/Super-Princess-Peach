#pragma once
#include "Object.h"

class Heal : public Object {
private:
    int hp;
    static int cntH;
public:
    Heal(const float x, const float y, const int hp = 25)
        : Object(x, y, 15, sf::Color::Green), hp(hp) {
    }

    void interact() const override {
        std::cout << "Heal colectat, hp adaugat: " << hp << std::endl;
        ++cntH;
        if (cntH == 2) {
            AchievementManager::getInstance().unlockAchievement("Healer");
        }
    }

    static void setCnt() {
        cntH = 0;
    }

    void makeAppear(float& adjustedTime) override {
        if (static_cast<int>(adjustedTime) % 30 < 15) {
            setVisible(true);
        } else {
            setVisible(false);
        }
    }

    std::shared_ptr<Object> clone() const override {
        return std::make_unique<Heal>(*this);
    }
};