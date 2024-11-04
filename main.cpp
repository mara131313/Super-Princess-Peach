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
    Enemies& operator=(const Enemies& altEnemy) {
        viata = altEnemy.viata;
        viteza = altEnemy.viteza;
        std::cout << "Operator '=' apelat" << std::endl;
        return *this;
    }
    ~Enemies() {
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
    Personaj printesa;
    Enemies Cosmin, Victor, Maria;
    Cosmin = Victor = Maria;
    Environment spatiu;
    return 0;
}
