#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Object {
private:
    float x, y, raza;
    sf::Color color;
    sf::CircleShape shape;
    mutable bool isCollected;
    bool visible;
    static int cntObj;
    sf::Vector2f pos;

public:
    Object(const float x, const float y, const float raza, const sf::Color color) :
    x(x), y(y), raza(raza), color(color), isCollected(false), visible(false),
    pos(x, y) {
        shape.setRadius(raza);
        shape.setPosition(x, y);
        shape.setFillColor(color);
    }

    virtual ~Object() {
        if (isCollected) {
            --cntObj;
        }
    }

    virtual std::shared_ptr<Object> clone() const = 0;
    virtual void interact() const = 0;
    virtual void makeAppear(float& adjustedTime) = 0;

    virtual void print(std::ostream& os) const {
        os << "Obiect la pozitia (" << x << ", " << y << ") cu raza " << raza;
    }

    bool checkCollision(const sf::RectangleShape& player) const {
        if (!isVisible() || isCollected) {
            return false;
        }

        if (player.getGlobalBounds().intersects(shape.getGlobalBounds())) {
            isCollected = true;
            ++cntObj;
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

    bool isVisible() const {
        return visible;
    }

    void setVisible(const bool state) {
        visible = state;
    }

    void resetState() {
        isCollected = false;
        visible = true;
    }

    static int getCntObj() {
        return cntObj;
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    void moveTo(const float x, const float y) {
        this->x = x;
        this->y = y;
        shape.setPosition(x, y);
    }

    sf::Vector2f getPos() const {
        return pos;
    }

    void resetPosition() {
        moveTo(pos.x, pos.y);
    }

    void draw(sf::RenderWindow& window) const {
        if (visible && !isCollected) {
            window.draw(shape);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
        obj.print(os);
        return os;
    }
};