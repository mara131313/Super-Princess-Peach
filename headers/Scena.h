#pragma once
#include "Enemy.h"
#include "Personaj.h"
#include "Platforma.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Scena {
private:
    Personaj personaj;
    std::vector<Enemy> enemies;
    std::vector<Platforma> platforms;
    sf::Clock clock;

public:
    Scena(const Personaj& p, std::vector<Enemy>& e, const std::vector<Platforma>& plat)
        : personaj(p), enemies(std::move(e)), platforms(plat) {}

    Personaj& getPersonaj() {
        return personaj;
    }

    std::vector<Enemy>& getEnemies() {
        return enemies;
    }

    const std::vector<Platforma>& getPlatforms() const {
        return platforms;
    }

    void update(const float grav) {
        personaj.update(platforms, grav, enemies);
        for (auto& enemy : enemies) {
            if (enemy.getIsAlive()) {
                enemy.walk(clock.getElapsedTime().asSeconds());
            }
        }
        clock.restart();
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& platform : platforms) {
            platform.draw(window);
        }
        personaj.draw(window);
        for (const auto& enemy : enemies) {
            if (enemy.getIsAlive()) {
                enemy.draw(window);
            }
        }
    }
};