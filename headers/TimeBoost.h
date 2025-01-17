#pragma once
#include <iostream>
#include "Obiect.h"

class TimeBoost : public Obiect {
private:
    float time;

public:
    TimeBoost(const float x, const float y, const float time = 30.f) :
    Obiect(x, y, 15, 5, 5, sf::Color::Red), time(time) {}

    void interact() const override {
        std::cout << "Jucătorul primește " << time << " secunde adiționale!" << std::endl;
    }

    std::unique_ptr<Obiect> clone() const override {
        return std::make_unique<TimeBoost>(*this);
    }

    void print(std::ostream& os) const override {
        os << "TimeBoost colectat.";
    }
};