#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Obiect {
private:
    float x, y, raza;
    sf::Color color;
    sf::CircleShape shape;
    mutable bool isCollected;
public:
    Obiect(const float x, const float y, const float raza, const sf::Color color) :
    x(x), y(y), raza(raza), color(color), isCollected(false) {
        shape.setRadius(raza);
        shape.setPosition(x, y);
        shape.setFillColor(color);
    }

    virtual ~Obiect() = default;

    virtual void interact() const = 0;

    virtual void print(std::ostream& os) const {
        os << "Obiect la pozitia (" << x << ", " << y << ")";
    }

    bool checkCollision(const sf::RectangleShape& player) const {
        if (!isCollected && player.getGlobalBounds().intersects(shape.getGlobalBounds())) {
            isCollected = true;
            return true;
        }
        return false;
    }

    void action() const {
        if (!isCollected) {
            this->interact();
            isCollected = true;
        }
    }

    virtual std::unique_ptr<Obiect> clone() const = 0;

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    friend std::ostream& operator<<(std::ostream& os, const Obiect& obj) {
        obj.print(os);
        return os;
    }
};