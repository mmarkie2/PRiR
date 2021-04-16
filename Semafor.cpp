//
// Created by mm on 16.04.2021.
//

#include "Semafor.h"

Semafor::Semafor(int _count)  :licznikZasobow(_count){

}

void Semafor::sygnalizuj() {
unique_lock<mutex> blokadaLicznika(mutexLicznika);
++licznikZasobow;
warunekLicznikaRoznyOdZera.notify_one();
}

void Semafor::czekaj() {

}

bool Semafor::proboj_czekac() {
    return false;
}

int Semafor::wartosc() const {
    return licznikZasobow;
}
