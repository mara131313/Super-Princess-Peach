#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platforma.h"
#include "Enemy.h"

class Personaj {
private:
    int viata, atac;
    float viteza, x, y;
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isOnGround, isJumping, isOver;
    sf::Clock clock;
    sf::Time lastHitTime;
    const float cooldownDuration = 3.0f;

    sf::Font font;
    sf::Text text;

public:
    Personaj(int _viata, int _atac, float _viteza, float _x, float _y) :
    viata(_viata), atac(_atac), viteza(_viteza), x(_x), y(_y), velocity(0.f, 0.f), isOnGround(false), isJumping(false),
    isOver(false), lastHitTime(sf::Time::Zero) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);

        if (!font.loadFromFile("../fonts/VomitoCartoon.ttf")) {
            std::cerr << "Eroare la incarcarea fontului!" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        text.setPosition(600.f, 300.f);
    }

    Personaj(const Personaj& altPers) :
    viata(altPers.viata), atac(altPers.atac), viteza(altPers.viteza), x(altPers.x), y(altPers.y), shape(altPers.shape),
    velocity(altPers.velocity), isOnGround(altPers.isOnGround), isJumping(altPers.isJumping), isOver(altPers.isOver) {}

    Personaj& operator = (const Personaj& altPers) {
        if (this == &altPers)
            return *this;
        viata = altPers.viata;
        atac = altPers.atac;
        viteza = altPers.viteza;
        x = altPers.x;
        y = altPers.y;
        shape = altPers.shape;
        velocity = altPers.velocity;
        isOnGround = altPers.isOnGround;
        isJumping = altPers.isJumping;
        isOver = altPers.isOver;
        return *this;
    }

    void attacked(const Enemy& enemy, sf::RenderWindow& window) {
    if (lastHitTime + sf::seconds(cooldownDuration) <= clock.getElapsedTime()) {
        const float MaraStanga = shape.getPosition().x;
        const float MaraDreapta = shape.getPosition().x + shape.getSize().x;
        const float MaraSus = shape.getPosition().y;
        const float MaraJos = shape.getPosition().y + shape.getSize().y;

        const float enemyStanga = enemy.getShape().getPosition().x;
        const float enemyDreapta = enemy.getShape().getPosition().x + enemy.getShape().getSize().x;
        float enemySus = enemy.getShape().getPosition().y;
        float enemyJos = enemy.getShape().getPosition().y + enemy.getShape().getSize().y;

        if (!viata) {
            GameOver(window);
            shape.move(-10, -10);
        }

        if (MaraDreapta > enemyStanga && MaraStanga < enemyDreapta && MaraJos > enemySus && MaraSus < enemyJos && viata) {
            viata -= enemy.getAtac();
            lastHitTime = clock.getElapsedTime();
            std::cout << "Ai fost atacat! Viata ramasa: " << viata << std::endl;

            if (MaraDreapta > enemyStanga && MaraStanga < enemyStanga) {
                shape.move(-shape.getSize().x, 0.f);
            }if (MaraStanga < enemyDreapta && MaraDreapta > enemyDreapta) {
                shape.move(shape.getSize().x, 0.f);
            }

            if (MaraJos > enemySus && MaraSus < enemySus) {
                shape.move(shape.getPosition().x, enemySus - shape.getSize().y);
            } else if (MaraSus < enemyJos && MaraJos > enemyJos) {
                shape.setPosition(shape.getPosition().x, enemyJos);
            }
        }
    }
}

    void checkEnemyCollisions(const std::vector<Enemy>& enemies, sf::RenderWindow& window) {
        for (const auto& enemy : enemies) {
            attacked(enemy, window);
        }
    }

/*    void heal() {

        viata += 50;
        if (viata > 100)
            viata = 100;
        std::cout << "Viata actuala: " << viata << std::endl;
    }*/

    void updateGround(const std::vector<Platforma>& platforms) {
        isOnGround = false;

        for (const auto& platform : platforms) {
            if (platform.verif(shape)) {
                float platformaSus = platform.getShape().getPosition().y;
                float MaraJos = shape.getPosition().y + shape.getSize().y;

                if (velocity.y >= 0 && MaraJos <= platformaSus + velocity.y) {
                    isOnGround = true;
                    velocity.y = 0;
                    shape.setPosition(shape.getPosition().x, platformaSus - shape.getSize().y);
                    break;
                }
            }
        }
    }

    void walk(const int dir, const std::vector<Platforma>& platforms, const float grav) {
        if(dir == -1)
            shape.move(-viteza, 0);
        else
            shape.move(viteza, 0);

        if (shape.getPosition().x < 0)
            shape.setPosition(0, shape.getPosition().y);
        else if (shape.getPosition().x + shape.getSize().x > 1500)
            shape.setPosition(1500 - shape.getSize().x, shape.getPosition().y);
        if (!isOnGround) {
            velocity.y += grav;
            if (velocity.y > 5.f)
                velocity.y = 5.f;
        }

        shape.move(0, velocity.y);
        updateGround(platforms);
    }

    void jump() {
        if (isOnGround && !isJumping)
        {
            if(velocity.y > -40.f)
                velocity.y -= 6.f;
            else
                velocity.y += 6.f;
            viteza = 2.5f;
            shape.move(viteza, velocity.y);
            if(velocity.y < -40.f)
                isOnGround = false;
            isJumping = true;
        }
    }

    void update(const std::vector<Platforma>& platforms, const float grav, const std::vector<Enemy>& enemies, sf::RenderWindow& window) {
        if (!isOnGround) {
            velocity.y += grav;
            if (velocity.y > 5.f)
                velocity.y = 5.f;
        }
        shape.move(0, velocity.y);
        updateGround(platforms);
        //attacked(enemy, window);
        checkEnemyCollisions(enemies, window);
    }

    void resetJump() {
        isJumping = false;
        viteza = 0.8f;
    }

    const sf::RectangleShape& getShape() const {
        return shape;
    }

    int getViata() const {
        return viata;
    }

    int getIsOver() const {
        return isOver;
    }

    void GameOver(sf::RenderWindow& window)  {
        if (!isOver) {
            window.draw(text);
            std::cout << "Ai murit! Apasa tasta R pentru a reincepe jocul." << std::endl;
            isOver = true;
        }
        text.setString("GAME OVER!!");
    }

    void restart() {
        isOver = false;
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
        viata = 100;
        text.setString("");
        std::cout << "Ai reinceput jocul!" << std::endl;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    ~Personaj() = default;

    friend std::ostream& operator<<(std::ostream& os, const Personaj& p) {
        os << "Viata personajului: " << p.viata;
        return os;
    }
};