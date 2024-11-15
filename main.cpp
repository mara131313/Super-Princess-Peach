#include <iostream>
#include <array>
#include <string.h>
#include <SFML/Graphics.hpp>

#include <Helper.h>
#include "headers/Personaj.h"
#include "headers/Enemy.h"
#include "headers/atac.h"
#include "headers/Environment.h"

int main() {
    Personaj Mara;
    Enemy Cosmin, Victor, Maria, Dimu, Alex;
    Cosmin = Victor = Maria;
    Environment spatiu;
    sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Cyan);
        sf::RectangleShape rectangle(sf::Vector2f(120.f,50.f));
        rectangle.setSize(sf::Vector2f(650.f, 100.f));
        rectangle.setPosition(sf::Vector2f(0.f, 500.f));
        rectangle.setFillColor(sf::Color{107, 31, 31, 250});
        window.draw(rectangle);
        rectangle.setSize(sf::Vector2f(650, 20));
        rectangle.setPosition(sf::Vector2f(0.f, 480.f));
        rectangle.setFillColor(sf::Color{33, 206, 108, 250});
        window.draw(rectangle);

        rectangle.setSize(sf::Vector2f(100.f, 100.f));
        rectangle.setPosition(sf::Vector2f(800.f, 500.f));
        rectangle.setFillColor(sf::Color{107, 31, 31, 250});
        window.draw(rectangle);
        rectangle.setSize(sf::Vector2f(100, 20));
        rectangle.setPosition(sf::Vector2f(800.f, 480.f));
        rectangle.setFillColor(sf::Color{33, 206, 108, 250});
        window.draw(rectangle);

        rectangle.setSize(sf::Vector2f(450.f, 100.f));
        rectangle.setPosition(sf::Vector2f(1050.f, 500.f));
        rectangle.setFillColor(sf::Color{107, 31, 31, 250});
        window.draw(rectangle);
        rectangle.setSize(sf::Vector2f(450, 20));
        rectangle.setPosition(sf::Vector2f(1050.f, 480.f));
        rectangle.setFillColor(sf::Color{33, 206, 108, 250});
        window.draw(rectangle);

        rectangle.setSize(sf::Vector2f(50.f, 50.f));
        rectangle.setPosition(sf::Vector2f(550.f, 250.f));
        rectangle.setFillColor(sf::Color{107, 31, 31, 250});
        window.draw(rectangle);
        rectangle.setSize(sf::Vector2f(50, 20));
        rectangle.setPosition(sf::Vector2f(550.f, 230.f));
        rectangle.setFillColor(sf::Color{33, 206, 108, 250});
        window.draw(rectangle);

        window.display();
    }
    return 0;
}
