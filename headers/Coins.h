#pragma once
#include "Object.h"

class Coins : public Object {
private:
    int val;
public:
    Coins(const float x, const float y, const int val = 50)
        : Object(x, y, 10, sf::Color::Yellow), val(val) {
    }

    void interact() const override {
        std::cout << "Banut colectat." << std::endl;
    }

    void makeAppear(float& adjustedTime) override {
        if (static_cast<int>(adjustedTime) % 10 < 5) {
            setVisible(true);
        } else {
            setVisible(false);
        }
    }

    std::unique_ptr<Object> clone() const override {
        return std::make_unique<Coins>(*this);
    }

    int getVal() const {
        return val;
    }
};