#pragma once
#include "Object.h"

class Coins : public Object {
public:
    Coins(const float x, const float y)
        : Object(x, y, 10, sf::Color::Yellow) {
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

    std::shared_ptr<Object> clone() const override {
        return std::make_unique<Coins>(*this);
    }
};