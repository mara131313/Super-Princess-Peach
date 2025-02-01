#pragma once
#include <iostream>
#include <utility>

class Achievement {
private:
    std::string name;
    bool unlocked;

public:
    Achievement() : unlocked(false) {}
    explicit Achievement(std::string  _name) : name(std::move(_name)), unlocked(false) {}

    void unlock() {
        if (!unlocked) {
            unlocked = true;
            std::cout << "Achievement deblocat: " << name << std::endl;
        }
    }

    void lock() {
        unlocked = false;
    }

    [[nodiscard]] bool isUnlocked() const {
        return unlocked;
    }
};