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

    friend std::ostream& operator<<(std::ostream& os, const Scena& scena) {
        os << "\n INFORMATII GENERALE:" << std::endl << " Daca esti atacat de 2 ori, fara a-ti da heal, ai murit. \n Daca vei cadea de pe platforme sub "
        "harta, ai murit. \n Daca depasesti limita de timp, respectiv 2 minute, ai murit. \n Pentru a castiga trebuie sa acumulezi un minim de 3500p. \n"
        "Inamici omorati: 150p. Banut acumulat: 50p. Heal acumulat: 50p. TimeBoost acumulat: 50p.\n\n PERSONAJ: \n" << scena.personaj << std::endl;
        os << "INAMICI:\n";
        for (const auto& enemy : scena.enemies) {
            os << enemy;
        }

        os << std::endl << "PLATFORME:\n";
        for (const auto& platform : scena.platforms) {
            os << platform << std::endl;
        }
        return os;
    }

};