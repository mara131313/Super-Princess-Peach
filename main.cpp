#include "headers/Stage.h"
#include "headers/Coins.h"
#include "headers/Heal.h"
#include "headers/TimeBoost.h"

int Object::cntObj = 0;

void initialObj(std::vector<std::shared_ptr<Object> > &objects) {
    objects.clear();
    for( int i = 10; i <= 610; i += 40) {
        objects.emplace_back(std::make_shared<Coins>(i, 450.f));
    }
    for( int i = 480; i <= 1000; i += 40) {
        objects.emplace_back(std::make_shared<Coins>(i, 150.f));
    }
    for( int i = 1080; i <= 1480; i += 40) {
        objects.emplace_back(std::make_shared<Coins>(i, 450.f));
    }
    for( int i = 400; i <= 480; i += 40) {
        objects.emplace_back(std::make_shared<Coins>(i, 300.f));
    }
    for( int i = 920; i <= 1000; i += 40) {
        objects.emplace_back(std::make_shared<Coins>(i, 300.f));
    }
    for( int i = 670; i <= 750; i += 40) {
        objects.emplace_back(std::make_shared<Coins>(i, 300.f));
    }
    objects.emplace_back(std::make_shared<Coins>(1300.f, 240.f));
    objects.emplace_back(std::make_shared<Coins>(1265.f, 230.f));
    objects.emplace_back(std::make_shared<Coins>(1335.f, 230.f));
    objects.emplace_back(std::make_shared<Coins>(1230.f, 210.f));
    objects.emplace_back(std::make_shared<Coins>(1370.f, 210.f));
    objects.emplace_back(std::make_shared<Coins>(1220.f, 170.f));
    objects.emplace_back(std::make_shared<Coins>(1380.f, 170.f));
    objects.emplace_back(std::make_shared<Coins>(1370.f, 130.f));
    objects.emplace_back(std::make_shared<Coins>(1230.f, 130.f));
    objects.emplace_back(std::make_shared<Coins>(1335.f, 110.f));
    objects.emplace_back(std::make_shared<Coins>(1265.f, 110.f));
    objects.emplace_back(std::make_shared<Coins>(1300.f, 100.f));
    objects.emplace_back(std::make_shared<Heal>(1450.f, 420.f, 25));
    objects.emplace_back(std::make_shared<Heal>(85.f, 70.f, 25));
    objects.emplace_back(std::make_shared<TimeBoost>(835.f, 400.f, 15.0f));
    objects.emplace_back(std::make_shared<TimeBoost>(1295.f, 165.f, 15.0f));
}

int main() {
    try {
        sf::ContextSettings settings;
        sf::Clock clock, gameClock;
        settings.antialiasingLevel = 4;
        settings.majorVersion = 3;
        settings.minorVersion = 0;
        settings.sRgbCapable = false;

        sf::RenderWindow window(sf::VideoMode(1500, 600), "Super Princess Peach", sf::Style::Default, settings);

        int score = 0;

        Character Mara(100, 5.f, 100.f, 400.f);
        Enemy Cosmin("Cosmin", 50, 50, 1, 6.f, 1100, 1350, 420, 420, 1100, 420),
        Victor("Victor", 50, 50, 4, 6.f, 1250, 1400, 240, 240, 1250, 240),
        Alex("Alex", 50, 100, 3, 6.f, 480, 480, 400, 560, 480, 400),
        Maria("Maria", 50, 100,5,  6.f, 830, 830, 400, 600, 830, 400), Dimu;
        Dimu = Victor;
        Dimu.makeChange(650, 950, 120, 120, "Dimu");

        std::vector<Enemy> enemies;
        enemies.reserve(20);
        enemies.emplace_back(Cosmin);
        enemies.emplace_back(Victor);
        enemies.emplace_back(Alex);
        enemies.emplace_back(Maria);
        enemies.emplace_back(Dimu);

        std::vector platforms = {
            //st jos
            Platform(0.f, 480.f, 650.f, 20.f, sf::Color{33, 206, 108}),
            Platform(0.f, 500.f, 650.f, 100.f, sf::Color{107, 31, 31}),

            //mij jos
            Platform(800.f, 480.f, 100.f, 20.f, sf::Color{33, 206, 108}),
            Platform(800.f, 500.f, 100.f, 100.f, sf::Color{107, 31, 31}),

            //dr jos
            Platform(1050.f, 480.f, 450.f, 20.f, sf::Color{33, 206, 108}),
            Platform(1050.f, 500.f, 450.f, 100.f, sf::Color{107, 31, 31}),

            //dr sus
            Platform(1200.f, 300.f, 250.f, 20.f, sf::Color{33, 206, 108}),
            Platform(1200.f, 320.f, 250.f, 50.f, sf::Color{107, 31, 31}),

            //st sus
            Platform(250.f, 300.f, 100.f, 20.f, sf::Color{33, 206, 108}),
            Platform(250.f, 320.f, 100.f, 50.f, sf::Color{107, 31, 31}),

            //mij sus
            Platform(450.f, 180.f, 600.f, 20.f, sf::Color{33, 206, 108}),
            Platform(450, 200.f,600.f, 50.f, sf::Color{107, 31, 31}),

            //st sus de tot
            Platform(50.f, 130.f, 100.f, 20.f, sf::Color{33, 206, 108}),
            Platform(50.f, 150.f,100.f, 50.f, sf::Color{107, 31, 31})
        };

        sf::Event event = {};
        sf::Font font;
        sf::Text win, lose;

        if (!font.loadFromFile("fonts/VomitoCartoon.ttf")) {
            throw GameInitException("Failed to load font.");
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

        std::vector<std::shared_ptr<Object>> objects, collected_objects;
        initialObj(objects);
        Stage joc(Mara, enemies, platforms, objects);
        std::cout << joc << std::endl;

        while (window.isOpen()) {
            window.setFramerateLimit(120);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            sf::Time elapsedTime = gameClock.getElapsedTime();
            static float bonusTime = 0.f;
            float adjustedTime = elapsedTime.asSeconds() - bonusTime;
            int totalSeconds = static_cast<int>(adjustedTime);
            int minutes = totalSeconds / 60;
            int seconds = totalSeconds % 60;
            bool ok;

            if(totalSeconds >= 15) {
                ok = true;
            }
            else {
                ok = false;
            }

            timerText.setString("Time spent: " + std::to_string(minutes) + "min " + std::to_string(seconds)+ "sec ");
            scoreText.setString("Score: " + std::to_string(score) + "p ");

            if(minutes >= 1 && score <= 4250) {
                Mara.GameOver();
                if(!gameWon) {
                    lose.setString("GAME OVER!! PRESS R TO RESTART");
                    window.draw(lose);
                }
            }

            if ((Mara.getShape().getPosition().y > 600.f || Mara.getHP() <= 0) && !Mara.getIsOver()) {
                Mara.GameOver();
                if(!gameWon) {
                    lose.setString("GAME OVER!! PRESS R TO RESTART");
                    window.draw(lose);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && (Mara.getIsOver() || gameWon)) {
                Stage::gameStats(collected_objects);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && Mara.getIsOver()) {
                score = 0; bonusTime = 0;
                win.setString("");
                lose.setString("");
                Mara.restart();
                collected_objects.clear();
                objects.clear();
                Stage newGame = joc;
                std::swap(joc, newGame);
                initialObj(objects);
                joc.restart(objects);
                
                if (objects.empty()) {
                    throw ObjectException("Failed to create objects!");
                }
                std::vector<std::tuple<int, float, float, float, float, std::string>> initialPositions = {
                    {1, 1100, 1350, 420, 420, "Cosmin"},
                    {4, 1250, 1400, 240, 240, "Victor"},
                    {6, 650, 950, 120, 120, "Dimu"},
                    {3, 480, 480, 400, 560, "Alex"},
                    {5, 830, 830, 400, 600, "Maria"}
                };
                enemies.clear();
                for (auto& position : initialPositions) {
                    enemies.emplace_back(
            std::get<5>(position), 50, 50, std::get<0>(position), 6.f, std::get<1>(position),
            std::get<2>(position), std::get<3>(position), std::get<4>(position), std::get<1>(position), std::get<3>(position) );
                    enemies.back().reset();
                }
                gameClock.restart();
            }

            timerText.setString("Time spent: " + std::to_string(minutes) + "min " + std::to_string(seconds)+ "sec");
            scoreText.setString("Score: " + std::to_string(score) + "p");

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
                Mara.resetJump();
            }

            Mara.update(platforms, gravity, enemies);
            joc.update();

            for (const auto& platform : platforms) {
                platform.draw(window);
            }

            joc.drawObjects(window, adjustedTime);
            Mara.collectObjects(objects, collected_objects, score, bonusTime, ok);

            sf::Time deltaTime = clock.restart();
            float dt = deltaTime.asSeconds();
            for (auto it = enemies.begin(); it != enemies.end(); ) {
                if (!it->getIsAlive()) {
                    score += 200;
                    it = enemies.erase(it);
                } else {
                    it->walk(dt);
                    it->draw(window);
                    Mara.attacked(*it);
                    Mara.kill(*it);
                    ++it;
                }
            }

            if (Mara.getIsOver() && !gameWon) {
                lose.setString("GAME OVER!! PRESS R TO RESTART");
                window.draw(lose);
                Mara.GameOver();
            }

            if ( ((score >= 4250 && minutes == 1) || (score == 4500 && minutes <= 1)) && Mara.getHP()) {
                gameWon = true;
                win.setString("T O P !! AI CASTIGAT");
                window.draw(win);
            }

            Mara.draw(window);
            joc.draw(window);
            window.draw(timerText);
            window.draw(scoreText);
            window.display();
        }
    } catch (const GameException& e) {
        std::cerr << "Game Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}