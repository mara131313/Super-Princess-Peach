#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#include <Helper.h>

class Personaj
{
private:
    int viata;
    int atac;
    int viteza;
    int x, y;
public:
    Personaj() {
        viata = 100;
        atac = 50;
        viteza = 10;
        x = 1;
        y = 1;
    }
    Personaj(int _viata, int _viteza, int _atac, int _x, int _y) {
        viata = _viata;
        viteza = _viteza;
        atac = _atac;
        x = _x;
        y = _y;
        std::cout << "Personajul a fost creat" << std::endl;
    }
    ~Personaj() {
        std::cout << "Personajul fost eliberat" << std::endl;
    }
};

class Enemy
{
private:
    int viata, viteza, x, y, atac;
public:
    Enemy() {
        viata = 50;
        viteza = 20;
        atac = 50;
    }
    Enemy(int _viata, int _viteza, int _atac) {
        viata = _viata;
        viteza = _viteza;
        atac = _atac;
    }
    Enemy(const Enemy& altEnemies) {
        viata = altEnemies.viata;
        viteza = altEnemies.viteza;
        atac = altEnemies.atac;
    }
    Enemy& operator=(const Enemy& altEnemy) {
        viata = altEnemy.viata;
        viteza = altEnemy.viteza;
        std::cout << "Operator '=' apelat" << std::endl;
        return *this;
    }
    ~Enemy() {
        std::cout << "Enemies fost eliberat" << std::endl;
    }
};

class Environment
{
private:
    int x, y;
public:
    Environment() {}
    ~Environment() {}
};

int main() {
    Personaj Mara;
    Enemy Cosmin, Victor, Maria;
    Cosmin = Victor = Maria;
    Environment spatiu;
    sf::RenderWindow window(sf::VideoMode(840, 600), "Super Princess Peach");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Cyan);
        sf::RectangleShape rectangle(sf::Vector2f(120.f,50.f));
        rectangle.setSize(sf::Vector2f(840.f, 100.f));
        rectangle.setPosition(sf::Vector2f(0.f, 500.f));
        rectangle.setFillColor(sf::Color{107, 31, 31, 250});
        window.draw(rectangle);
        rectangle.setSize(sf::Vector2f(840, 20));
        rectangle.setPosition(sf::Vector2f(0.f, 480.f));
        rectangle.setFillColor(sf::Color{33, 206, 108, 250});
        window.draw(rectangle);
        window.display();
    }
    return 0;
}
