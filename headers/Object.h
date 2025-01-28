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

public:
    Object(const float x, const float y, const float raza, const sf::Color color) :
    x(x), y(y), raza(raza), color(color), isCollected(false), visible(false) {
        shape.setRadius(raza);
        shape.setPosition(x, y);
        shape.setFillColor(color);
    }

    Object(const Object& other):
    x(other.x), y(other.y), raza(other.raza), color(other.color), shape(other.shape), isCollected(other.isCollected), visible(other.visible) {
        std::cout << "Copy constructor" << std::endl;
    }

    Object(Object&& other) noexcept
        : x(other.x), y(other.y), raza(other.raza), color(other.color), shape(std::move(other.shape)),
          isCollected(other.isCollected), visible(other.visible) {
        other.isCollected = true;
    }

    virtual ~Object() {
        if (isCollected) {
            --cntObj;
        }
    }

    virtual std::unique_ptr<Object> clone() const = 0;
    virtual void interact() const = 0;
    virtual void makeAppear(float& adjustedTime) = 0;

    Object& operator=(const Object& other) {
        Object temp(other);
        swap(*this, temp);
        return *this;
    }

    virtual void print(std::ostream& os) const {
        os << "Obiect la pozitia (" << x << ", " << y << ") cu raza " << raza;
    }

    bool checkCollision(const sf::RectangleShape& player) const {
        if (!isVisible() || isCollected) {
            ++cntObj;
            return false;
        }

        if (player.getGlobalBounds().intersects(shape.getGlobalBounds())) {
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

    bool isVisible() const {
        return visible;
    }

    void setVisible(const bool state) {
        visible = state;
    }

    static int getCntObj() {
        return cntObj;
    }

    void draw(sf::RenderWindow& window) const {
        if (visible && !isCollected) {
            window.draw(shape);
        }
    }

    friend void swap(Object& first, Object& second) noexcept {
        using std::swap;
        swap(first.x, second.x);
        swap(first.y, second.y);
        swap(first.raza, second.raza);
        swap(first.color, second.color);
        swap(first.isCollected, second.isCollected);
        swap(first.visible, second.visible);
        swap(first.shape, second.shape);
    }

    friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
        obj.print(os);
        return os;
    }
};