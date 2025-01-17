#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Obiect {
private:
    float x, y, raza, lung, lat;
    sf::Color color;
    sf::CircleShape shape;
    mutable bool isCollected;
    static int objectCounter;
public:
    Obiect(const float x, const float y, const float raza, const float lung, const float lat, const sf::Color color) :
    x(x), y(y), raza(raza), lung(lung), lat(lat), color(color), isCollected(false) {
        shape.setRadius(raza);
        shape.setPosition(x, y);
        shape.setFillColor(color);
    }

    virtual ~Obiect() = default;

    virtual void interact() const = 0;

    virtual void print(std::ostream& os) const {
        os << "Obiect la poziția (" << x << ", " << y << ")";
    }

    friend std::ostream& operator<<(std::ostream& os, const Obiect& obj) {
        obj.print(os);
        return os;
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
        } else {
            std::cout << "Obiect deja colectat!" << std::endl;
        }
    }

    virtual std::unique_ptr<Obiect> clone() const = 0;

    static int countObjects() {
        return objectCounter;
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }
};