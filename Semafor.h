//
// Created by mm on 16.04.2021.
//

#ifndef PRIR_SEMAFOR_H
#define PRIR_SEMAFOR_H

#include <mutex>
#include <condition_variable>
using namespace std;

class Semafor {


public:
    Semafor(int _count = 1);

    void sygnalizuj();

    void czekaj();

    bool proboj_czekac();

    int wartosc() const;

    Semafor(const Semafor &obj);

private:
    int licznikZasobow;
    mutex mutexLicznika;
    condition_variable warunekLicznikaRoznyOdZera;


};


#endif //PRIR_SEMAFOR_H
