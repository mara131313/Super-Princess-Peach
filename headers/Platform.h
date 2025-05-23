#pragma once

class Platform
{
private:
    sf::RectangleShape platformShape;
public:
    Platform(const float x, const float y, const float lung, const float lat, const sf::Color color) {
        platformShape.setSize(sf::Vector2f(lung, lat));
        platformShape.setPosition(x, y);
        platformShape.setFillColor(color);
    }
    const sf::RectangleShape& getShape() const {
        return platformShape;
    }
    bool verify(const sf::RectangleShape& pers) const {
        return pers.getGlobalBounds().intersects(platformShape.getGlobalBounds()) &&
            pers.getPosition().y + pers.getSize().y <= platformShape.getPosition().y + 5.f;
    }
    void draw(sf::RenderWindow& window) const {
        window.draw(platformShape);
    }
    ~Platform() = default;

    friend std::ostream& operator<<(std::ostream& os, const Platform& platforma) {
        const auto& shape = platforma.platformShape;
        os << "Platforma de pozitie ("
           << shape.getPosition().x << ", "
           << shape.getPosition().y << "), dimensiuni ("
           << shape.getSize().x << ", "
           << shape.getSize().y << ").";
        return os;
    }
};