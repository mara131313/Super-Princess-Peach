#include <iostream>
#include <array>

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
        atac = _atac;
        viteza = _viteza;
        x = _x;
        y = _y;
        std::cout << "Personajul a fost creat" << std::endl;
    }
    ~Personaj() {
        std::cout << "Personajul fost eliberat" << std::endl;
    }
};

class Enemies
{
private:
    int viata, viteza, x, y, atac;
public:
    Enemies() {
        viata = 50;
        viteza = 20;
        atac = 50;
    }
    Enemies(int _viata, int _viteza) {
        viata = _viata;
        viteza = _viteza;
    }
    Enemies(const Enemies& altEnemies) {
        viata = altEnemies.viata;
        viteza = altEnemies.viteza;
        atac = altEnemies.atac;
    }
};

class Environment
{
public:
};

int main() {
    Personaj printesa;
    return 0;
}
