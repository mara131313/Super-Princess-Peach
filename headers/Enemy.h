#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
private:
    int viata, viteza, atac, culoare;
    float x, y;
    sf::RectangleShape shape;

public:
    Enemy() : viata(50), viteza(20), atac(50), culoare(1), x(0), y(0) {
        shape.setSize(sf::Vector2f(40.f, 60.f));
        setShapeColor();
        shape.setPosition(x, y);
    }

    Enemy(int _viata, int _viteza, int _atac, int _culoare, float _x, float _y) :
        viata(_viata), viteza(_viteza), atac(_atac), culoare(_culoare), x(_x), y(_y) {
        shape.setSize(sf::Vector2f(40.f, 60.f));
        setShapeColor();
        shape.setPosition(x, y);
    }

    Enemy(const Enemy& altEnemies) {
        viata = altEnemies.viata;
        viteza = altEnemies.viteza;
        atac = altEnemies.atac;
        culoare = altEnemies.culoare;
        x = altEnemies.x;
        y = altEnemies.y;
    }

    Enemy& operator=(const Enemy& altEnemy) {
        if (this == &altEnemy)
            return *this;
        viata = altEnemy.viata;
        viteza = altEnemy.viteza;
        atac = altEnemy.atac;
        x = altEnemy.x;
        y = altEnemy.y;
        return *this;
    }

    Enemy(Enemy&& altEnemy) noexcept :
    viata(altEnemy.viata), viteza(altEnemy.viteza), atac(altEnemy.atac), culoare(altEnemy.culoare), x(altEnemy.x),
    y(altEnemy.y), shape(std::move(altEnemy.shape)) {
        altEnemy.viata = 0;
        altEnemy.viteza = 0;
        altEnemy.atac = 0;
        altEnemy.x = 0;
        altEnemy.y = 0;
        std::cout << "Enemy mutat!" << std::endl;
    }

    Enemy& operator=(Enemy&& altEnemy) noexcept {
        if (this == &altEnemy)
            return *this;
        viata = altEnemy.viata;
        viteza = altEnemy.viteza;
        atac = altEnemy.atac;
        culoare = altEnemy.culoare;
        x = altEnemy.x;
        y = altEnemy.y;
        shape = std::move(altEnemy.shape);

        altEnemy.viata = 0;
        altEnemy.viteza = 0;
        altEnemy.atac = 0;
        altEnemy.x = 0;
        altEnemy.y = 0;
        std::cout << "Enemy atribuit prin mutare!" << std::endl;

        return *this;
    }

    [[nodiscard]] int getAtac() const {
        return atac;
    }

    void setShapeColor() {
        switch (culoare) {
            case 1:
                shape.setFillColor(sf::Color::Green);
            break;
            case 2:
                shape.setFillColor(sf::Color{107, 31, 31});
            break;
            case 3:
                shape.setFillColor(sf::Color::Yellow);
            break;
            case 4:
                shape.setFillColor(sf::Color::Blue);
            break;
            case 5:
                shape.setFillColor(sf::Color::Red);
            break;
            default:
                shape.setFillColor(sf::Color::White);
            break;
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    ~Enemy() {
        std::cout << "Enemies a fost eliberat" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
        os<< "ataca cu : " << enemy.atac<< "damage.";
        return os;
    }
};
