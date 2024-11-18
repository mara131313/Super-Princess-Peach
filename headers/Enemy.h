#pragma once

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
    void attack() {

    }
    void walk() {

    }
    ~Enemy() {
        std::cout << "Enemies a fost eliberat" << std::endl;
    }
};
