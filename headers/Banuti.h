#pragma once
#include "Obiect.h"

class Banuti : public Obiect {
private:
    int val;
public:
    Banuti(const float x, const float y, const int val = 50)
        : Obiect(x, y, 10, sf::Color::Yellow), val(val) {
    }

    void interact() const override {
        std::cout << "Banut colectat." << std::endl;
    }

    std::unique_ptr<Obiect> clone() const override {
        return std::make_unique<Banuti>(*this);
    }

    int getValoare() const {
        return val;
    }
};
