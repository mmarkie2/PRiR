//
// Created by mm on 16.04.2021.
//

#ifndef PRIR_SEMAFOR_H
#define PRIR_SEMAFOR_H

#include <mutex>

using namespace std;
class Semafor {


    public:
        Semafor (int _count=1);
    void sygnalizuj();
    void czekaj();
    bool proboj_czekac();
    int wartosc() const;
private:
    int licznikZasobow;
    mutex mutexLicznika;
condition_variable warunekLicznikaRoznyOdZera;


};


#endif //PRIR_SEMAFOR_H