#pragma once
#include <iostream>
class Enemy
{
private:
    int viata, viteza, atac;
    float x, y;

public:
    Enemy() : viata(50), viteza(20), atac(50), x(0), y(0) {}

    Enemy(int _viata, int _viteza, int _atac, float _x, float _y) :
    viata(_viata), viteza(_viteza), atac(_atac), x(_x), y(_y) {}

    Enemy(const Enemy& altEnemies) {
        viata = altEnemies.viata;
        viteza = altEnemies.viteza;
        atac = altEnemies.atac;
        x = altEnemies.x;
        y = altEnemies.y;
    }

    Enemy& operator=(const Enemy& altEnemy) {
        viata = altEnemy.viata;
        viteza = altEnemy.viteza;
        return *this;
    }

    [[nodiscard]] int getAtac() const {
        return atac;
    }

    ~Enemy() {
        std::cout << "Enemies a fost eliberat" << std::endl;
    }
};
