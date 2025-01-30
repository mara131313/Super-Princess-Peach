#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"
#include "Platform.h"
#include "Object.h"
#include "Coins.h"
#include "Heal.h"
#include "TimeBoost.h"

class Character {
private:
    int hp;
    float speed, x, y;
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isOnGround, isJumping, isOver;
    sf::Clock clock;
    sf::Time lastHitTime;
    const float cooldownDuration = 3.0f;

public:
    Character(const int _hp, const float _speed, const float _x, const float _y) :
    hp(_hp), speed(_speed), x(_x), y(_y), velocity(0.f, 0.f), isOnGround(false), isJumping(false),
    isOver(false), lastHitTime(sf::Time::Zero) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
    }

    Character(const Character& altPers) :
    hp(altPers.hp), speed(altPers.speed), x(altPers.x), y(altPers.y), shape(altPers.shape),
    velocity(altPers.velocity), isOnGround(altPers.isOnGround), isJumping(altPers.isJumping), isOver(altPers.isOver) {}

    Character& operator = (const Character& altPers) {
        if (this == &altPers)
            return *this;
        hp = altPers.hp;
        speed = altPers.speed;
        x = altPers.x;
        y = altPers.y;
        shape = altPers.shape;
        velocity = altPers.velocity;
        isOnGround = altPers.isOnGround;
        isJumping = altPers.isJumping;
        isOver = altPers.isOver;
        return *this;
    }

    void attacked(const Enemy& enemy) {
    if (lastHitTime + sf::seconds(cooldownDuration) <= clock.getElapsedTime()) {
        const float MaraSt = shape.getPosition().x;
        const float MaraDr = shape.getPosition().x + shape.getSize().x;
        const float MaraSus = shape.getPosition().y;
        const float MaraJos = shape.getPosition().y + shape.getSize().y;

        const float enemySt = enemy.getShape().getPosition().x;
        const float enemyDr = enemy.getShape().getPosition().x + enemy.getShape().getSize().x;
        const float enemySus = enemy.getShape().getPosition().y;
        const float enemyJos = enemy.getShape().getPosition().y + enemy.getShape().getSize().y;

        if (!hp) {
            GameOver();
            shape.move(-10, -10);
        }

        if (MaraDr > enemySt && MaraSt < enemyDr && MaraJos > enemySus && MaraSus < enemyJos && hp
            && !(MaraJos <= enemySus + 5 && MaraJos >= enemySus - 5)) {
            hp -= enemy.getAttack();
            lastHitTime = clock.getElapsedTime();
            std::cout << "Ai fost atacat! Viata ramasa: " << hp << std::endl << "Esti invincibil 3 secunde!" << std::endl;

            if (MaraDr > enemySt && MaraSt < enemySt) {
                shape.move(-shape.getSize().x, 0.f);
            }if (MaraSt < enemyDr && MaraDr > enemyDr) {
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

    void kill(Enemy& enemy) const {
        const float MaraSt = shape.getPosition().x;
        const float MaraDr = shape.getPosition().x + shape.getSize().x;
        const float MaraJos = shape.getPosition().y + shape.getSize().y;

        const float enemySt = enemy.getShape().getPosition().x;
        const float enemyDr = enemy.getShape().getPosition().x + enemy.getShape().getSize().x;
        const float enemySus = enemy.getShape().getPosition().y;

        if (MaraDr > enemySt && MaraSt < enemyDr &&
            MaraJos <= enemySus + 5 && MaraJos >= enemySus - 5) {
            enemy.die();
            std::cout << "Inamicul a fost omorat!" << std::endl;
            }
    }

    void checkEnemyCollisions(const std::vector<Enemy>& enemies) {
        for (const auto& enemy : enemies) {
            attacked(enemy);
        }
    }

    void updateGround(const std::vector<Platform>& platforms) {
        isOnGround = false;
        for (const auto& platform : platforms) {
            if (platform.verify(shape)) {
                const float platformSus = platform.getShape().getPosition().y;
                const float MaraJos = shape.getPosition().y + shape.getSize().y;

                if (velocity.y >= 0 && MaraJos <= platformSus + velocity.y) {
                    isOnGround = true;
                    velocity.y = 0;
                    shape.setPosition(shape.getPosition().x, platformSus - shape.getSize().y);
                    break;
                }
            }
        }
    }

    void walk(const int dir, const std::vector<Platform>& platforms, const float grav) {
        if(dir == -1)
            shape.move(-speed, 0);
        else
            shape.move(speed, 0);

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
            speed = 2.5f;
            shape.move(speed, velocity.y);
            if(velocity.y < -40.f)
                isOnGround = false;
            isJumping = true;
        }
    }

    void update(const std::vector<Platform>& platforms, const float grav, const std::vector<Enemy>& enemies) {
        if (!isOnGround) {
            velocity.y += grav;
            if (velocity.y > 5.f)
                velocity.y = 5.f;
        }
        shape.move(0, velocity.y);
        updateGround(platforms);
        checkEnemyCollisions(enemies);
    }

    int getHP() const {
        return hp;
    }

    void resetJump() {
        isJumping = false;
        speed = 5.f;
    }

    const sf::RectangleShape& getShape() const {
        return shape;
    }

    int getIsOver() const {
        return isOver;
    }

    void GameOver()  {
        isOver = true;
    }

    void restart() {
        hp = 100;
        isOver = false;
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
        std::cout << "Ai reinceput jocul!" << std::endl;
    }

    void collectObjects(std::vector<std::shared_ptr<Object>> &objects, std::vector<std::shared_ptr<Object>> &collectedObjects,
                    int& score, float& seconds, const bool ok) {
        for (auto it = objects.begin(); it != objects.end();) {
            if ((*it)->checkCollision(shape) && (*it)->isVisible()) {
                (*it)->action();
                if (const auto heal = std::dynamic_pointer_cast<Heal>(*it)) {
                    score += 100;
                    heal->interact();
                    addHP();
                }
                else if (const auto bani = std::dynamic_pointer_cast<Coins>(*it)) {
                    score += 50;
                    bani->interact();
                }
                else if (const auto timeBoost = std::dynamic_pointer_cast<TimeBoost>(*it)) {
                    timeBoost->print(std::cout);
                    timeBoost->interact();
                    if (ok) {
                        seconds += 15;
                    }
                    score += 100;
                }
                else {
                    (*it)->interact();
                }
                collectedObjects.push_back(std::move(*it));
                it = objects.erase(it);
            } else {
                ++it;
            }
        }
    }

    void addHP() {
        if (hp > 0) {
            hp += 25;
            if (hp > 100) {
                hp = 100;
            }
        }
        std::cout << "Viata actuala: " << hp << "/100hp." << std::endl;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    ~Character() = default;

    friend std::ostream& operator<<(std::ostream& os, const Character& p) {
        os << "Viata personajului: " << p.hp << ". A inceput de pe pozitia x : " << p.x << " si y : "<< p.y
        << ". Se deplaseaza cu viteza : " << p.speed << "." << std::endl;
        return os;
    }
};