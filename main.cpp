#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "headers/Platforma.h"
#include "headers/Enemy.h"
#include "headers/Personaj.h"
// #include "headers/atac.h"

int main() {
    sf::ContextSettings settings;
    sf::Clock clock;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    settings.sRgbCapable = false;

    sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach", sf::Style::Default, settings);

    Personaj Mara(100, 50, 0.8f, 100.f, 400.f);
    //atac foc, atingere;
    Enemy Cosmin(50, 50, 1, 6.f, 1100, 1250, 420, 1100, true),
    Victor(50, 50, 2, 6.f, 1250, 1400, 220, 1250, true);
    std::vector<Enemy> enemies = {Cosmin, Victor};

    std::vector<Platforma> platforms = {
        Platforma(0.f, 480.f, 650.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(0.f, 500.f, 650.f, 100.f, sf::Color{107, 31, 31}),

        Platforma(800.f, 480.f, 100.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(800.f, 500.f, 100.f, 100.f, sf::Color{107, 31, 31}),

        Platforma(1050.f, 480.f, 450.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(1050.f, 500.f, 450.f, 100.f, sf::Color{107, 31, 31}),

        Platforma(1200.f, 280.f, 250.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(1200.f, 300.f, 250.f, 50.f, sf::Color{107, 31, 31}),

        Platforma(250.f, 280.f, 100.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(250.f, 300.f, 100.f, 50.f, sf::Color{107, 31, 31})
    };

    sf::Event event = {};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased)
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                    Mara.resetJump();
                }
        }

        if ((Mara.getShape().getPosition().y > 600.f || Mara.getViata() <= 0) && !Mara.getIsOver()) {
            Mara.GameOver(window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && Mara.getIsOver()) {
            Mara.restart();
        }
    window.clear(sf::Color::Cyan);

    constexpr float gravity = 0.1f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        Mara.walk(-1, platforms, gravity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        Mara.walk(1, platforms, gravity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        Mara.jump();
    }

    Mara.update(platforms, gravity, enemies, window);

    for (const auto& platform : platforms) {
        platform.draw(window);
    }


    sf::Time deltaTime = clock.restart();
    float dt = deltaTime.asSeconds();
    Cosmin.walk(dt);
    Cosmin.draw(window);
    Victor.draw(window);
    Victor.walk(dt);
    Mara.attacked(Cosmin, window);
    Mara.GameOver(window);

    Mara.draw(window);

    window.display();
    }

    return 0;
}