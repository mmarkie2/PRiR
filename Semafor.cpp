//
// Created by mm on 16.04.2021.
//

#include "Semafor.h"

Semafor::Semafor(int _count) : licznikZasobow(_count) {

}

void Semafor::sygnalizuj() {
    unique_lock<mutex> blokadaLicznika(mutexLicznika);
    ++licznikZasobow;
    warunekLicznikaRoznyOdZera.notify_one();
}

void Semafor::czekaj() {
    unique_lock<mutex> blokadaLicznika(mutexLicznika);
    while (this->licznikZasobow == 0) {
        warunekLicznikaRoznyOdZera.wait(blokadaLicznika);
    }
    --licznikZasobow;
}

bool Semafor::proboj_czekac() {
    unique_lock<mutex> blokadaLicznika(mutexLicznika);

    if (licznikZasobow != 0) {
        --licznikZasobow;
        return true;
    } else {
        return false;
    }
}

int Semafor::wartosc() const {
    return licznikZasobow;
}
