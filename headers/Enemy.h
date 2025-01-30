#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <utility>
#include "GameException.h"

class Enemy {
private:
    std::string name;
    int hp, attack, color;
    float speed, x1, x2, y1, y2, xrn, yrn;
    bool isRight = true, isDown = true, isAlive = true;
    sf::RectangleShape shape;

public:
    Enemy() : name("Inamic"), hp(50), attack(50), color(6), speed(0.8f), x1(0), x2(0), y1(0), y2(0), xrn(0), yrn(0){
        shape.setSize(sf::Vector2f(40.f, 60.f));
        setShapeColor();
        shape.setPosition(xrn, yrn);
    }

    Enemy(std::string _name, int _hp, int _attack, int _color, float _speed, float _x1, float _x2, float _y1,
        float _y2, float _xrn, float _yrn) :
        name(std::move(_name)), hp(_hp), attack(_attack), color(_color), speed(_speed), x1(_x1), x2(_x2), y1(_y1),
        y2(_y2), xrn(_xrn), yrn(_yrn) {
        shape.setSize(sf::Vector2f(40.f, 60.f));
        setShapeColor();
        shape.setPosition(xrn, yrn);
    }

    Enemy(const Enemy& altEnemies) = default;

    Enemy& operator=(const Enemy& altEnemy) {
        if (this == &altEnemy)
            return *this;
        hp = altEnemy.hp;
        attack = altEnemy.attack;
        color = altEnemy.color;
        speed = altEnemy.speed;
        x1 = altEnemy.x1;
        x2 = altEnemy.x2;
        y1 = altEnemy.y1;
        y2 = altEnemy.y2;
        xrn = altEnemy.xrn;
        yrn = altEnemy.yrn;
        isRight = altEnemy.isRight;
        isDown = altEnemy.isDown;
        return *this;
    }

    Enemy(Enemy&& altEnemy) noexcept :
    hp(altEnemy.hp), attack(altEnemy.attack), color(altEnemy.color), speed(altEnemy.speed), x1(altEnemy.x1),
    x2(altEnemy.x2), y1(altEnemy.y1), y2(altEnemy.y2), xrn(altEnemy.xrn), yrn(altEnemy.yrn),
    isRight(altEnemy.isRight), isDown(altEnemy.isDown), isAlive(altEnemy.isAlive), shape(std::move(altEnemy.shape)) {
        altEnemy.hp = 0;
        altEnemy.attack = 0;
        altEnemy.speed = 0;
        altEnemy.x1 = 0;
        altEnemy.x2 = 0;
        altEnemy.y1 = 0;
        altEnemy.y2 = 0;
        altEnemy.xrn = 0;
        altEnemy.yrn = 0;
        altEnemy.isRight = true;
        altEnemy.isDown = true;
        altEnemy.isAlive = true;
    }

    Enemy& operator=(Enemy&& altEnemy) noexcept {
        if (this == &altEnemy)
            return *this;
        hp = altEnemy.hp;
        attack = altEnemy.attack;
        color = altEnemy.color;
        speed = altEnemy.speed;
        x1 = altEnemy.x1;
        x2 = altEnemy.x2;
        y1 = altEnemy.y1;
        y2 = altEnemy.y2;
        xrn = altEnemy.xrn;
        yrn = altEnemy.yrn;
        isRight = altEnemy.isRight;
        isDown = altEnemy.isDown;
        isAlive = altEnemy.isAlive;
        shape = std::move(altEnemy.shape);

        altEnemy.hp = 0;
        altEnemy.attack = 0;
        altEnemy.speed = 0;
        altEnemy.x1 = 0;
        altEnemy.x2 = 0;
        altEnemy.y1 = 0;
        altEnemy.y2 = 0;
        altEnemy.xrn = 0;
        altEnemy.yrn = 0;
        altEnemy.isRight = true;
        altEnemy.isDown = true;
        altEnemy.isAlive = true;

        return *this;
    }

    [[nodiscard]] int getAttack() const {
        return attack;
    }

    void setShapeColor() {
        switch (color) {
            case 1: shape.setFillColor(sf::Color::Green);
            break;
            case 2: shape.setFillColor(sf::Color{107, 31, 31});
            break;
            case 3: shape.setFillColor(sf::Color::Yellow);
            break;
            case 4: shape.setFillColor(sf::Color::Blue);
            break;
            case 5: shape.setFillColor(sf::Color::Red);
            break;
            default: shape.setFillColor(sf::Color::White);
            break;
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    void walk(const float deltaTime) {
        if (y1 == y2 && isAlive) {
            if (isRight) {
                xrn += speed * 4 * deltaTime;
                if (xrn >= x2) {
                    xrn = x2;
                    isRight = false;
                }
            } else {
                xrn -= speed * 4 * deltaTime;
                if (xrn <= x1) {
                    xrn = x1;
                    isRight = true;
                }
            }
            shape.setPosition(xrn, y1);
        }
        if (x1 == x2 && isAlive) {
            if(isDown) {
                yrn += speed * 4 * deltaTime;
                if (yrn >= y2) {
                    yrn = y2;
                    isDown = false;
                }
            } else {
                yrn -= speed * 4 * deltaTime;
                if (yrn <= y1) {
                    yrn = y1;
                    isDown = true;
                }
            }
            shape.setPosition(x1, yrn);
        }
    }

    void die() {
        hp = 0;
        isAlive = false;
        shape.setPosition(1600, 800);
    }

    bool getIsAlive() const {
        return isAlive;
    }

    void makeChange(const float a, const float b, const float c, const float d, const std::string& e) {
        x1 = a;
        x2 = b;
        y1 = c;
        y2 = d;
        xrn = a;
        yrn = c;
        if (!e.empty()) {
            name = e;
        } else {
            throw EnemyException("Enemy name is invalid.");
        }
    }

    void reset() {
        isAlive = true;
        isDown = true;
        isRight = true;
    }

    const sf::RectangleShape& getShape() const {
        return shape;
    }

    ~Enemy() = default;

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
        os << enemy.name << " ataca cu "<< enemy.attack;
        if (enemy.x1 == enemy.x2) {
            os <<  " damage. Se deplaseaza de sus in jos, de la y = " << enemy.y1 << " pana la y = " << enemy.y2 << std::endl;
        }
        else {
            os << " damage. Se deplaseaza de la dreapta la stanga, de la x = " << enemy.x1 << " pana la x = " << enemy.y2 << std::endl;
        }
        return os;
    }
};