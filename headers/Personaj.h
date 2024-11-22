#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Platforma.h"

class Personaj
{
private:
    int viata;
    int atac;
    float x, y;
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isOnGround;

public:
    Personaj() :
        viata(100), atac(50), x(1), y(1), isOnGround(false), velocity(0.f, 0.f) {
        shape.setSize(sf::Vector2f(40.f, 80.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(100.f, 400.f);

    }

    Personaj(int _viata, int _atac, float _x, float _y) :
    viata(_viata), atac(_atac), x(_x), y(_y), isOnGround(false), velocity(0.f, 0.f) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
        std::cout << "Personajul a fost creat" << std::endl;
    }

    void attack() {

    }

    void heal() {

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
    ~Personaj() {
        std::cout << "Personajul a fost eliberat" << std::endl;
    }
};