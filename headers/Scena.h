#pragma once
#include "Enemy.h"
#include "Personaj.h"
#include "Platforma.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Obiect.h"

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
        for (const auto& enemy : enemies) {
            if (enemy.getIsAlive()) {
                enemy.draw(window);
            }
        }
        for (const auto& platform : platforms) {
            platform.draw(window);
        }
        personaj.draw(window);
    }

    static void analizaObiecte(const std::vector<std::unique_ptr<Obiect>>& obiecteColectate) {
        int totalBanuti = 0;
        int totalHeal = 0;
        int totalTimeBoosts = 0;

        for (const auto& obiect : obiecteColectate) {
            if (const auto* heal = dynamic_cast<Heal*>(obiect.get())) {
                totalHeal += heal->getHeal();
            } else if (const auto* bani = dynamic_cast<Banuti*>(obiect.get())) {
                totalBanuti += bani->getValoare();
            } else if (dynamic_cast<TimeBoost*>(obiect.get())) {
                ++totalTimeBoosts;
            }
        }

        std::cout << "Statistici obiecte colectate:\n";
        std::cout << "Total hp adaugat: " << totalHeal << " hp.\n";
        std::cout << "Total scor acumulat din banuti: " << totalBanuti << " p.\n";
        std::cout << "Total TimeBoost-uri: " << totalTimeBoosts << " buc.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Scena& scena) {
        os << "\n INFORMATII GENERALE:\nDaca esti atacat de 2 ori de inamicii care se deplaseaza stanga-dreapta, fara a-ti da heal, ai murit. \nDaca "
        "esti atacat o data de inamicii care se deplaseaza sus-jos ai murit. \nDaca vei cadea de pe platforme, sub harta, ai murit. \nDaca depasesti "
        "limita de timp, respectiv un minut, fara a acumula minimul de 4250p pentru a castiga, ai murit. \nInamici omorati: 200p. \nBanut acumulat "
        "(GALBEN): 50p. \nHeal acumulat (VERDE): 100p, +25hp. \nTimeBoost acumulat (ROSU): 100p, +15s.\nPentru GameStats in legatura cu obiectele "
        "acumulate, apasati tasta G. Pentru a reincepe jocul, tasta R.\n\n PERSONAJ: \n" << scena.personaj << "\n "
        "INAMICI:\n";
        for (const auto& enemy : scena.enemies) {
            os << enemy;
        }
        os << std::endl << " PLATFORME:\n";
        for (const auto& platform : scena.platforms) {
            os << platform << std::endl;
        }
        return os;
    }

};