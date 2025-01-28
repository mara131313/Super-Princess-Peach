#pragma once
#include "Object.h"

class TimeBoost : public Object {
private:
    float time;

public:
    TimeBoost(const float x, const float y, const float time = 30.f) :
    Object(x, y, 15, sf::Color::Red), time(time) {}

    void interact() const override {
        std::cout << " Ai primit " << time << " secunde aditionale." << std::endl;
    }

    void makeAppear(float& adjustedTime) override {
        if (static_cast<int>(adjustedTime) % 30 < 15) {
            setVisible(true);
        } else {
            setVisible(false);
        }
    }

    std::unique_ptr<Object> clone() const override {
        return std::make_unique<TimeBoost>(*this);
    }

    void print(std::ostream& os) const override {
        os << "TimeBoost colectat.";
    }
};