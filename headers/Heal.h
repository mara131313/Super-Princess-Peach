#pragma once
#include "Obiect.h"


class Heal : public Obiect {
private:
    int hp;
public:
    Heal(const float x, const float y, const int hp = 25)
        : Obiect(x, y, 15, 5, 5, sf::Color::Green), hp(hp) {
    }

    void interact() const override {
        std::cout << "Heal colectat, hp adăugat: " << hp << std::endl;
    }

    std::unique_ptr<Obiect> clone() const override {
        return std::make_unique<Heal>(*this);
    }

    int getHeal() const {
        return hp;
    }
};
