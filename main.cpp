#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "headers/Platforma.h"
#include "headers/Personaj.h"
#include "headers/Enemy.h"
#include "headers/Scena.h"

int main() {
    sf::ContextSettings settings;
    sf::Clock clock;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    settings.sRgbCapable = false;

    sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach", sf::Style::Default, settings);

    Personaj Mara(100, 5.f, 100.f, 400.f);
    Enemy Cosmin(50, 50, 1, 6.f, 1100, 1350, 420, 420, 1100, 420),
    Victor(50, 50, 4, 6.f, 1250, 1400, 240, 240, 1250, 240), Dimu;
    Dimu = Victor;
    Dimu.setPozi(650, 950, 120, 120);

    std::vector<Enemy> enemies;
    enemies.reserve(10);
    enemies.emplace_back(Cosmin);
    enemies.emplace_back(Victor);
    enemies.emplace_back(Dimu);

    std::vector platforms = {
        //stanga jos
        Platforma(0.f, 480.f, 650.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(0.f, 500.f, 650.f, 100.f, sf::Color{107, 31, 31}),

        //mijloc jos
        Platforma(800.f, 480.f, 100.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(800.f, 500.f, 100.f, 100.f, sf::Color{107, 31, 31}),

        //dreapta jos
        Platforma(1050.f, 480.f, 450.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(1050.f, 500.f, 450.f, 100.f, sf::Color{107, 31, 31}),

        //dreapta sus
        Platforma(1200.f, 300.f, 250.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(1200.f, 320.f, 250.f, 50.f, sf::Color{107, 31, 31}),

        //stanga sus
        Platforma(250.f, 300.f, 100.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(250.f, 320.f, 100.f, 50.f, sf::Color{107, 31, 31}),

        //mijloc sus
        Platforma(450.f, 180.f, 600.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(450, 200.f,600.f, 50.f, sf::Color{107, 31, 31})
    };

    Scena joc(Mara, enemies, platforms);

    std::cout << Mara << "Cosmin " << Cosmin << "Victor " << Victor << "Dimu " << Dimu << std::endl;

    sf::Event event = {};
    sf::Font font;
    sf::Text win, lose;

    if (!font.loadFromFile("fonts/VomitoCartoon.ttf")) {
        std::cerr << "Eroare la incarcarea fontului!" << std::endl;
    }

    win.setFont(font);
    win.setCharacterSize(80);
    win.setFillColor(sf::Color::Black);
    win.setStyle(sf::Text::Bold);
    win.setPosition(350.f, 100.f);

    lose.setFont(font);
    lose.setCharacterSize(80);
    lose.setFillColor(sf::Color::Red);
    lose.setStyle(sf::Text::Bold);
    lose.setPosition(100.f, 100.f);

    bool gameWon = false;

    while (window.isOpen()) {
        window.setFramerateLimit(150);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if ((joc.getPersonaj().getShape().getPosition().y > 600.f || joc.getPersonaj().getViata() <= 0) && !Mara.getIsOver()) {
            joc.getPersonaj().GameOver();
            if(!gameWon) {
                lose.setString("GAME OVER!! PRESS R TO RESTART");
                window.draw(lose);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && joc.getPersonaj().getIsOver()) {
            win.setString("");
            lose.setString("");

            joc.getPersonaj().restart();
            std::vector<std::tuple<int, float, float, float, float>> initialPositions = {
                {1, 1100, 1350, 420, 420},
                {4, 1250, 1400, 240, 240},
                {7, 650, 950, 120, 120}
            };

            joc.getEnemies().clear();
            for (auto& position : initialPositions) {
                joc.getEnemies().emplace_back(50, 50, std::get<0>(position), 6.f, std::get<1>(position),
                std::get<2>(position), std::get<3>(position), std::get<4>(position), std::get<1>(position), std::get<2>(position));
                joc.getEnemies().back().reset();
            }
        }
    window.clear(sf::Color::Cyan);

    constexpr float gravity = 0.1f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        joc.getPersonaj().walk(-1, joc.getPlatforms(), gravity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        joc.getPersonaj().walk(1, joc.getPlatforms(), gravity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        joc.getPersonaj().jump();
        joc.getPersonaj().resetJump();
    }

    joc.update(gravity);

    for (const auto& platform : joc.getPlatforms()) {
        platform.draw(window);
    }

    sf::Time deltaTime = clock.restart();
    float dt = deltaTime.asSeconds();
    for (auto it = joc.getEnemies().begin(); it != joc.getEnemies().end(); ) {
        if (!it->getIsAlive()) {
            it = joc.getEnemies().erase(it);
        } else {
            it->walk(dt);
            it->draw(window);
            joc.getPersonaj().attacked(*it);
            joc.getPersonaj().kill(*it);
            ++it;
        }
    }

    if (joc.getPersonaj().getIsOver() && !gameWon) {
        lose.setString("GAME OVER!! PRESS R TO RESTART");
        window.draw(lose);
        joc.getPersonaj().GameOver();
    }

    if ( joc.getEnemies().empty() && joc.getPersonaj().getViata()) {
        gameWon = true;
        win.setString("T O P !! AI CASTIGAT");
        window.draw(win);
    }

    joc.draw(window);
    window.display();
    }

    return 0;
}