#include <vector>
#include <tuple>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "headers/Platforma.h"
#include "headers/Personaj.h"
#include "headers/Enemy.h"
#include "headers/Scena.h"
#include "headers/Obiect.h"
#include "headers/Banuti.h"
#include "headers/Heal.h"
#include "headers/TimeBoost.h"

void initialObj(std::vector<std::unique_ptr<Obiect>>& obiecte) {
    obiecte.clear();
    for( int i = 10; i <= 610; i += 40) {
        obiecte.emplace_back(std::make_unique<Banuti>(i, 450.f, 50));
    }
    for( int i = 480; i <= 1000; i += 40) {
        obiecte.emplace_back(std::make_unique<Banuti>(i, 150.f, 50));
    }
    for( int i = 1080; i <= 1480; i += 40) {
        obiecte.emplace_back(std::make_unique<Banuti>(i, 450.f, 50));
    }
    for( int i = 400; i <= 480; i += 40) {
        obiecte.emplace_back(std::make_unique<Banuti>(i, 300.f, 50));
    }
    for( int i = 920; i <= 1000; i += 40) {
        obiecte.emplace_back(std::make_unique<Banuti>(i, 300.f, 50));
    }
    for( int i = 670; i <= 750; i += 40) {
        obiecte.emplace_back(std::make_unique<Banuti>(i, 300.f, 50));
    }
    obiecte.emplace_back(std::make_unique<Banuti>(1300.f, 240.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1265.f, 230.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1335.f, 230.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1230.f, 210.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1370.f, 210.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1220.f, 170.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1380.f, 170.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1370.f, 130.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1230.f, 130.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1335.f, 110.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1265.f, 110.f, 50));
    obiecte.emplace_back(std::make_unique<Banuti>(1300.f, 100.f, 50));
    obiecte.emplace_back(std::make_unique<Heal>(1450.f, 420.f, 25));
    obiecte.emplace_back(std::make_unique<Heal>(85.f, 70.f, 25));
    obiecte.emplace_back(std::make_unique<TimeBoost>(835.f, 400.f, 15.0f));
    obiecte.emplace_back(std::make_unique<TimeBoost>(1295.f, 165.f, 15.0f));
}

int main() {
    sf::ContextSettings settings;
    sf::Clock clock, gameClock;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    settings.sRgbCapable = false;

    sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach", sf::Style::Default, settings);

    int score = 0;

    Personaj Mara(100, 5.f, 100.f, 400.f);
    Enemy Cosmin("Cosmin", 50, 50, 1, 6.f, 1100, 1350, 420, 420, 1100, 420),
    Victor("Victor", 50, 50, 4, 6.f, 1250, 1400, 240, 240, 1250, 240),
    Alex("Alex", 50, 100, 3, 6.f, 480, 480, 400, 560, 480, 400),
    Maria("Maria", 50, 100,5,  6.f, 830, 830, 400, 600, 830, 400), Dimu;
    Dimu = Victor;
    Dimu.setPozi(650, 950, 120, 120);
    Dimu.setNume("Dimu");

    std::vector<Enemy> enemies;
    enemies.reserve(20);
    enemies.emplace_back(Cosmin);
    enemies.emplace_back(Victor);
    enemies.emplace_back(Alex);
    enemies.emplace_back(Maria);
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
        Platforma(450, 200.f,600.f, 50.f, sf::Color{107, 31, 31}),

        //stanga sus de tot
        Platforma(50.f, 130.f, 100.f, 20.f, sf::Color{33, 206, 108}),
        Platforma(50.f, 150.f,100.f, 50.f, sf::Color{107, 31, 31})
    };

    Scena joc(Mara, enemies, platforms);

    std::cout << joc << std::endl;

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
    lose.setPosition(150.f, 100.f);

    sf::Text timerText, scoreText;
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(0.f, 0.f);

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(230.f, 0.f);

    bool gameWon = false;

    std::vector<std::unique_ptr<Obiect>> obiecte, obiecteColectate;
    initialObj(obiecte);

    while (window.isOpen()) {
        window.setFramerateLimit(150);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsedTime = gameClock.getElapsedTime();
        static float bonusTime = 0.f;
        float adjustedTime = elapsedTime.asSeconds() - bonusTime;
        int totalseconds = static_cast<int>(adjustedTime);
        int minutes = totalseconds / 60;
        int seconds = totalseconds % 60;
        timerText.setString("Timp: " + std::to_string(minutes) + "min " + std::to_string(seconds)+ "sec ");
        scoreText.setString("Scor: " + std::to_string(score) + "p ");

        if(minutes >= 1 && score <= 3750) {
            joc.getPersonaj().GameOver();
            if(!gameWon) {
                lose.setString("GAME OVER!! PRESS R TO RESTART");
                window.draw(lose);
            }
        }

        if ((joc.getPersonaj().getShape().getPosition().y > 600.f || joc.getPersonaj().getViata() <= 0) && !Mara.getIsOver()) {
            joc.getPersonaj().GameOver();
            if(!gameWon) {
                lose.setString("GAME OVER!! PRESS R TO RESTART");
                window.draw(lose);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && joc.getPersonaj().getIsOver()) {
            Scena::analizaObiecte(obiecteColectate);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && joc.getPersonaj().getIsOver()) {
            score = 0;
            bonusTime = 0;
            win.setString("");
            lose.setString("");
            joc.getPersonaj().restart();
            gameClock.restart();
            initialObj(obiecte);
            std::vector<std::tuple<int, float, float, float, float, std::string>> initialPositions = {
                {1, 1100, 1350, 420, 420, "Cosmin"},
                {4, 1250, 1400, 240, 240, "Victor"},
                {6, 650, 950, 120, 120, "Dimu"},
                {3, 480, 480, 400, 560, "Alex"},
                {5, 830, 830, 400, 600, "Maria"}
            };
            joc.getEnemies().clear();
            for (auto& position : initialPositions) {
                joc.getEnemies().emplace_back(
        std::get<5>(position), 50, 50, std::get<0>(position), 6.f, std::get<1>(position),
        std::get<2>(position), std::get<3>(position), std::get<4>(position), std::get<1>(position), std::get<3>(position) );
                joc.getEnemies().back().reset();
            }
        }

        timerText.setString("Time spent: " + std::to_string(minutes) + "min " + std::to_string(seconds)+ "sec");
        scoreText.setString("Score: " + std::to_string(score) + "p");

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

        for(const auto& obiect : obiecte) {
            obiect -> draw(window);
        }

        joc.getPersonaj().collectObiecte(obiecte, obiecteColectate, score, bonusTime);

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        for (auto it = joc.getEnemies().begin(); it != joc.getEnemies().end(); ) {
            if (!it->getIsAlive()) {
                score += 200;
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

        if ( ((score >= 4250 && minutes == 1) || (score == 4500 && minutes <= 1)) && joc.getPersonaj().getViata()) {
            gameWon = true;
            win.setString("T O P !! AI CASTIGAT");
            window.draw(win);
        }

        joc.draw(window);
        window.draw(timerText);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}