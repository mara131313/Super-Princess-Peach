#pragma once

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
        viteza = 50;
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
    void attack() {

    }
    void heal() {

    }
    void walk() {

    }
    ~Personaj() {
        std::cout << "Personajul fost eliberat" << std::endl;
    }
};