#pragma once

class Platforma
{
private:
    sf::RectangleShape platformShape;
public:
    Platforma(float x, float y, float lung, float lat, sf::Color color) {
        platformShape.setSize(sf::Vector2f(lung, lat));
        platformShape.setPosition(x, y);
        platformShape.setFillColor(color);
    }
    const sf::RectangleShape& getShape() const {
        return platformShape;
    }
    bool verif(const sf::RectangleShape& pers) const {
        return pers.getGlobalBounds().intersects(platformShape.getGlobalBounds()) &&
            pers.getPosition().y + pers.getSize().y <= platformShape.getPosition().y + 5.f;
    }
    void draw(sf::RenderWindow& window) const {
        window.draw(platformShape);
    }
    ~Platforma() = default;
};