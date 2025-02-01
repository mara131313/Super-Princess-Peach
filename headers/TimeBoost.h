#pragma once
#include "Object.h"

class TimeBoost : public Object {
private:
    float time;
    static int cntT;

public:
    TimeBoost(const float x, const float y, const float time = 30.f) :
    Object(x, y, 15, sf::Color::Red), time(time) {}

    void interact() const override {
        std::cout << " Ai primit " << time << " secunde aditionale." << std::endl;
        cntT++;
        if (cntT == 2) {
            AchievementManager::getInstance().unlockAchievement("Time Saver");
        }
    }

    static void setCnt() {
        cntT = 0;
    }

    void makeAppear(float& adjustedTime) override {
        if (static_cast<int>(adjustedTime) % 30 < 15) {
            setVisible(true);
        } else {
            setVisible(false);
        }
    }

    std::shared_ptr<Object> clone() const override {
        return std::make_unique<TimeBoost>(*this);
    }

    void print(std::ostream& os) const override {
        os << "TimeBoost colectat.";
    }
};