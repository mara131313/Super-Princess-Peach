#pragma once

class Platforma
{
private:
    sf::RectangleShape platformShape;
public:
    Platforma(const float x, const float y, const float lung, const float lat, const sf::Color color) {
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

    friend std::ostream& operator<<(std::ostream& os, const Platforma& platforma) {
        const auto& shape = platforma.getShape();
        os << "Platforma de pozitie ("
           << shape.getPosition().x << ", "
           << shape.getPosition().y << "), dimensiuni ("
           << shape.getSize().x << ", "
           << shape.getSize().y << ").";
        return os;
    }

};