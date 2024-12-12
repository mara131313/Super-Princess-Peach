#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
private:
    int viata, atac, culoare;
    float viteza, x1, x2, y1, y2, xrn, yrn;
    bool isRight, isDown, isAlive = true;
    sf::RectangleShape shape;

public:
    Enemy() : viata(50), atac(50), culoare(6), viteza(0.8f), x1(0), x2(0), y1(0), y2(0), xrn(0), yrn(0), isRight(true), isDown(true) {
        shape.setSize(sf::Vector2f(40.f, 60.f));
        setShapeColor();
        shape.setPosition(xrn, yrn);
    }

    Enemy(int _viata, int _atac, int _culoare, float _viteza, float _x1, float _x2, float _y1,
        float _y2, float _xrn, float _yrn, bool _isRight, bool _isDown) :
        viata(_viata), atac(_atac), culoare(_culoare), viteza(_viteza), x1(_x1), x2(_x2), y1(_y1),
        y2(_y2), xrn(_xrn), yrn(_yrn), isRight(_isRight), isDown(_isDown) {
        shape.setSize(sf::Vector2f(40.f, 60.f));
        setShapeColor();
        shape.setPosition(xrn, yrn);
    }

    Enemy(const Enemy& altEnemies) {
        viata = altEnemies.viata;
        atac = altEnemies.atac;
        culoare = altEnemies.culoare;
        viteza = altEnemies.viteza;
        x1 = altEnemies.x1;
        x2 = altEnemies.x2;
        y1 = altEnemies.y1;
        y2 = altEnemies.y2;
        xrn = altEnemies.xrn;
        yrn = altEnemies.yrn;
        isRight = altEnemies.isRight;
        isDown = altEnemies.isDown;
    }

    Enemy& operator=(const Enemy& altEnemy) {
        if (this == &altEnemy)
            return *this;
        viata = altEnemy.viata;
        atac = altEnemy.atac;
        culoare = altEnemy.culoare;
        viteza = altEnemy.viteza;
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
    viata(altEnemy.viata), atac(altEnemy.atac), culoare(altEnemy.culoare), viteza(altEnemy.viteza), x1(altEnemy.x1),
    x2(altEnemy.x2), y1(altEnemy.y1), y2(altEnemy.y2), xrn(altEnemy.xrn), yrn(altEnemy.yrn),
    isRight(altEnemy.isRight), isDown(altEnemy.isDown), shape(std::move(altEnemy.shape)) {
        altEnemy.viata = 0;
        altEnemy.atac = 0;
        altEnemy.viteza = 0;
        altEnemy.x1 = 0;
        altEnemy.x2 = 0;
        altEnemy.y1 = 0;
        altEnemy.y2 = 0;
        altEnemy.xrn = 0;
        altEnemy.yrn = 0;
        altEnemy.isRight = true;
        altEnemy.isDown = true;
        std::cout << "Enemy mutat!" << std::endl;
    }

    Enemy& operator=(Enemy&& altEnemy) noexcept {
        if (this == &altEnemy)
            return *this;
        viata = altEnemy.viata;
        atac = altEnemy.atac;
        culoare = altEnemy.culoare;
        viteza = altEnemy.viteza;
        x1 = altEnemy.x1;
        x2 = altEnemy.x2;
        y1 = altEnemy.y1;
        y2 = altEnemy.y2;
        xrn = altEnemy.xrn;
        yrn = altEnemy.yrn;
        isRight = altEnemy.isRight;
        isDown = altEnemy.isDown;
        shape = std::move(altEnemy.shape);

        altEnemy.viata = 0;
        altEnemy.atac = 0;
        altEnemy.viteza = 0;
        altEnemy.x1 = 0;
        altEnemy.x2 = 0;
        altEnemy.y1 = 0;
        altEnemy.y2 = 0;
        altEnemy.xrn = 0;
        altEnemy.yrn = 0;
        altEnemy.isRight = true;
        altEnemy.isDown = true;
        std::cout << "Enemy atribuit prin mutare!" << std::endl;

        return *this;
    }

    [[nodiscard]] int getAtac() const {
        return atac;
    }

    void setShapeColor() {
        switch (culoare) {
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
                xrn += viteza * 4 * deltaTime;
                if (xrn >= x2) {
                    xrn = x2;
                    isRight = false;
                }
            } else {
                xrn -= viteza * 4 * deltaTime;
                if (xrn <= x1) {
                    xrn = x1;
                    isRight = true;
                }
            }
            shape.setPosition(xrn, y1);
        }
        if (x1 == x2 && isAlive) {
            if(isDown) {
                yrn += viteza * 4 * deltaTime;
                if (yrn >= y2) {
                    yrn = y2;
                    isDown = false;
                }
            } else {
                yrn -= viteza * 4 * deltaTime;
                if (yrn <= y1) {
                    yrn = y1;
                    isDown = true;
                }
            }
            shape.setPosition(x1, yrn);
        }
    }

    void die() {
        viata = 0;
        isAlive = false;
        shape.setPosition(1600, 800);
    }

    bool getIsAlive() const {
        return isAlive;
    }

    const sf::RectangleShape& getShape() const {
        return shape;
    }

    ~Enemy() = default;

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
        os<< "ataca cu : " << enemy.atac<< " damage.";
        return os;
    }
};
