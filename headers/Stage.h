#pragma once
#include "Enemy.h"
#include "Character.h"
#include "Platform.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.h"

class Stage {
private:
    Character character;
    std::vector<Enemy> enemies;
    std::vector<Platform> platforms;
    std::vector<std::unique_ptr<Object>> objects;
    sf::Clock clock;

public:
    Stage(const Character& p, std::vector<Enemy>& e, const std::vector<Platform>& plat, std::vector<std::unique_ptr<Object>>&& o)
        : character(p), enemies(std::move(e)), platforms(plat), objects(std::move(o)) {}

    Character& getCharacter() {
        return character;
    }

    std::vector<Enemy>& getEnemies() {
        return enemies;
    }

    const std::vector<Platform>& getPlatforms() const {
        return platforms;
    }

    void drawObjects(sf::RenderWindow& window, float adjustedTime) const {
        for (auto& object : objects) {
            object->makeAppear(adjustedTime);
            if (object->isVisible()) {
                object->draw(window);
            }
        }
    }

    void update(const float grav) {
        character.update(platforms, grav, enemies);
        for (auto& enemy : enemies) {
            if (enemy.getIsAlive()) {
                enemy.walk(clock.getElapsedTime().asSeconds());
            }
        }
        clock.restart();
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& enemy : enemies) {
            if (enemy.getIsAlive()) {
                enemy.draw(window);
            }
        }
        for (const auto& platform : platforms) {
            platform.draw(window);
        }
        character.draw(window);
    }

    static void gameStats(const std::vector<std::unique_ptr<Object>>& collectedObjects) {
        int totalCoins = 0;
        int totalHeal = 0;
        int totalTimeBoosts = 0;

        std::cout << "Numarul de obiecte colectate in total: " << Object::getCntObj() << std::endl;

        for (const auto& object : collectedObjects) {
            if (const auto* heal = dynamic_cast<Heal*>(object.get())) {
                totalHeal += heal->getHeal();
            } else if (const auto* coins = dynamic_cast<Coins*>(object.get())) {
                totalCoins += coins->getVal();
            } else if (dynamic_cast<TimeBoost*>(object.get())) {
                ++totalTimeBoosts;
            }
        }

        std::cout << "Statistici obiecte colectate:\n";
        std::cout << "Total hp adaugat: " << totalHeal << " hp.\n";
        std::cout << "Total scor acumulat din banuti: " << totalCoins << " p.\n";
        std::cout << "Total TimeBoost-uri: " << totalTimeBoosts << " buc.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Stage& stage) {
        os << "\n INFORMATII GENERALE:\nDaca esti atacat de 2 ori de inamicii care se deplaseaza stanga-dreapta, fara a-ti da heal, ai murit. \nDaca "
        "esti atacat o data de inamicii care se deplaseaza sus-jos ai murit. \nDaca vei cadea de pe platforme, sub harta, ai murit. \nDaca depasesti "
        "limita de timp, respectiv un minut, fara a acumula minimul de 4250p pentru a castiga, ai murit. \nInamici omorati: 200p. \nBanut acumulat "
        "(GALBEN): 50p. \nHeal acumulat (VERDE): 100p, +25hp. \nTimeBoost acumulat (ROSU): 100p, +15s.\nPentru GameStats in legatura cu obiectele "
        "acumulate, apasati tasta G. Pentru a reincepe jocul, tasta R.\n\n PERSONAJ: \n" << stage.character << "\n "
        "INAMICI:\n";
        for (const auto& enemy : stage.enemies) {
            os << enemy;
        }
        os << std::endl << " PLATFORME:\n";
        for (const auto& platform : stage.platforms) {
            os << platform << std::endl;
        }
        return os;
    }
};