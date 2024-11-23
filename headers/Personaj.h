#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Platforma.h"
#include "Enemy.h"

class Personaj
{
private:
    int viata, atac;
    float x, y;
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isOnGround;

public:
    Personaj(int _viata, int _atac, float _x, float _y) :
    viata(_viata), atac(_atac), x(_x), y(_y), isOnGround(false), velocity(0.f, 0.f) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
        std::cout << "Personajul a fost creat" << std::endl;
    }

    Personaj(Personaj& altPers) :
    viata(altPers.viata), atac(altPers.atac), x(altPers.x), y(altPers.y), shape(altPers.shape),
    velocity(altPers.velocity), isOnGround(altPers.isOnGround) {
        std::cout << "Constructor de copiere" << std::endl;
    }

    Personaj& operator = (const Personaj& altPers) {
        if (this == &altPers)
            return *this;
        viata = altPers.viata;
        atac = altPers.atac;
        x = altPers.x;
        y = altPers.y;
        shape = altPers.shape;
        velocity = altPers.velocity;
        isOnGround = altPers.isOnGround;
        std::cout << "Operator = apelat" << std::endl;
        return *this;
    }

    ~Personaj() {
        std::cout << "Personajul a fost eliberat" << std::endl;
    }

    void attacked(const Enemy& enemy) {

        viata -= enemy.getAtac();
        std::cout << "Viata ramasa: " << viata << std::endl;
    }

    void heal() {

        viata += 50;
        if (viata > 100)
            viata = 100;
        std::cout << "Viata actuala: " << viata << std::endl;
    }

    void walk(float dx, const std::vector<Platforma>& platforms, float grav) {
        shape.move(dx, 0);

        if (shape.getPosition().x < 0)
            shape.setPosition(0, shape.getPosition().y);
        else if (shape.getPosition().x + shape.getPosition().x > 1500)
            shape.setPosition(1500 - shape.getSize().x, shape.getPosition().y);
        if (!isOnGround) {
            velocity.y += grav;
            if (velocity.y > 5.f)
                velocity.y = 5.f;
        }

        isOnGround = false;

        for (const auto& platform : platforms) {
            if (platform.verif(shape)) {
                float platformaSus = platform.getShape().getPosition().y;
                float MaraJos = shape.getPosition().y + shape.getSize().y;

                if (velocity.y > 0 && MaraJos <= platformaSus + velocity.y)
                {
                    isOnGround = true;
                    velocity.y = 0;
                    shape.setPosition(shape.getPosition().x, platformaSus- shape.getSize().y);
                    break;
                }
            }
        }
        shape.move(0, velocity.y);
    }

    void jump(float dx) {
        if (isOnGround)
        {
            velocity.y = -6.f;
            shape.move(dx * 10.f, 0);
            isOnGround = false;
        }
    }

    const sf::RectangleShape& getShape() const {
        return shape;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }
};