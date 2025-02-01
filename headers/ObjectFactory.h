#pragma once
#include <memory>
#include "Object.h"
#include "Heal.h"
#include "Coins.h"
#include "TimeBoost.h"

class ObjectFactory {
public:
    static std::shared_ptr<Object> createObject(const std::string& type, float x, float y, float extra = 0) {
        if (type == "Coin") return std::make_shared<Coins>(x, y);
        if (type == "Heal") return std::make_shared<Heal>(x, y, static_cast<int>(extra));
        if (type == "TimeBoost") return std::make_shared<TimeBoost>(x, y, extra);
        return nullptr;
    }
};