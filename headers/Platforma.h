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
    bool verif(const sf::RectangleShape& fm_pers) const {
        return platformShape.getGlobalBounds().intersects(fm_pers.getGlobalBounds());
    }
    void draw(sf::RenderWindow& window) const {
        window.draw(platformShape);
    }
    ~Platforma() {}
};