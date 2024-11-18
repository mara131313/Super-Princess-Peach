#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "headers/Platforma.h"

#include <Helper.h>
#include "headers/Personaj.h"
#include "headers/Enemy.h"
#include "headers/atac.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach");
    Personaj Mara;
    atac foc, atingere;
    Enemy Cosmin, Victor, Maria, Dimu, Alex;
    Cosmin = Victor = Maria = Dimu = Alex;
    std::vector<Platforma> platforms = {
        Platforma(0.f, 480.f, 650.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(0.f, 500.f, 650.f, 500.f, sf::Color{107, 31, 31}),

        Platforma(800.f, 480.f, 100.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(800.f, 500.f, 100.f, 100.f, sf::Color{107, 31, 31}),

        Platforma(1050.f, 480.f, 450.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(1050.f, 500.f, 450.f, 100.f, sf::Color{107, 31, 31}),

        Platforma(550.f, 330.f, 50.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(550.f, 350.f, 50.f, 30.f, sf::Color{107, 31, 31})
    };

    const float gravity = 0.3f;
    const float moveSpeed = 0.8f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Cyan);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            Mara.walk(-moveSpeed, platforms, gravity);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            Mara.walk(moveSpeed, platforms, gravity);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            Mara.jump();
        }

        Mara.walk(0.f, platforms, gravity);

        for (const auto& platform : platforms) {
            platform.draw(window);
        }
        Mara.draw(window);

        window.display();
    }
    return 0;
}
