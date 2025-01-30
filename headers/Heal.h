#pragma once
#include "Object.h"

class Heal : public Object {
private:
    int hp;
public:
    Heal(const float x, const float y, const int hp = 25)
        : Object(x, y, 15, sf::Color::Green), hp(hp) {
    }

    void interact() const override {
        std::cout << "Heal colectat, hp adaugat: " << hp << std::endl;
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