#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "headers/Platforma.h"
#include "headers/Personaj.h"
#include "headers/Enemy.h"
// #include "headers/atac.h"

int main() {
    sf::ContextSettings settings;
    sf::Clock clock;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    settings.sRgbCapable = false;

    sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach", sf::Style::Default, settings);

    Personaj Mara(100, 0.8f, 100.f, 400.f);
    //atac foc, atingere;
    Enemy Cosmin(50, 50, 1, 6.f, 1100, 1350, 420, 420, 1100, 420, true, true),
    Victor(50, 50, 4, 6.f, 1250, 1400, 240, 240, 1250, 240, true, true), Dimu;
    Dimu = Victor;
    Dimu.setPozi(650, 950, 120, 120);

    std::vector enemies_pt = {&Cosmin, &Victor, &Dimu};
    std::vector enemies = {Cosmin, Victor, Dimu};

    std::vector<Platforma> platforms = {
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

    std::cout << Mara << std::endl;
    std::cout << "Cosmin " << Cosmin << std::endl;
    std::cout << "Victor " << Victor << std::endl;
    std::cout << "Dimu " << Dimu << std::endl;

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
            std::vector<std::tuple<float, float, float, float>> initialPositions = {
                {1100, 1350, 420, 420},
                {1250, 1400, 240, 240},
                {650, 950, 120, 120}
            };
            int i = 0;
            for (auto& enemy : enemies_pt) {
                auto [x1, x2, y1, y2] = initialPositions[i++];
                enemy->setPozi(x1, x2, y1, y2);
                enemy->reset();
            }
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
    for (auto it = enemies_pt.begin(); it != enemies_pt.end(); ) {
        if (!(*it)->getIsAlive()) {
            it = enemies_pt.erase(it);
        } else {
            (*it)->walk(dt);
            (*it)->draw(window);
            Mara.attacked(**it, window);
            Mara.kill(**it);
            ++it;
        }
    }

    if (Mara.getIsOver()) {
        Mara.GameOver(window);
    }

    if ( enemies.empty() ) {
        sf::Font font;
        sf::Text win;

        if (!font.loadFromFile("../fonts/VomitoCartoon.ttf")) {
            std::cerr << "Eroare la incarcarea fontului!" << std::endl;
        }

        win.setFont(font);
        win.setCharacterSize(80);
        win.setFillColor(sf::Color::Black);
        win.setStyle(sf::Text::Bold);
        win.setPosition(100.f, 100.f);
        win.setString("T O P !! AI CASTIGAT");
        window.draw(win);
    }

    Mara.draw(window);

    window.display();
    }

    return 0;
}