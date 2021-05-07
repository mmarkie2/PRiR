//
// Created by mm on 07.05.2021.
//

#include "lab08.h"
#include "iostream"
#include <string>
#include <random>
#include <thread>
#include <string>
#include <vector>
#include <set>
#include "Semafor.h"

using namespace std;
const int POJEMNOSC_HANGARU = 5;
const int LICZBA_SAMOLOTOW = 10;

random_device rd8;
minstd_rand generator8(rd8());
uniform_int_distribution<int> zakres8(1000, 3000);

class Hangar;

class Samolot;

class Lotnisko {
private:
    bool pasWolny;
    Hangar& hangar;
Semafor semaforPas;
Semafor semaforDoHangaru;Semafor semaforZHangaru;
public:
    Lotnisko(Hangar &h) : pasWolny(true), hangar(h) {

    }

    void laduj(Samolot &s);

    void kolujDoHangaru(Samolot &s);

    void opuscHangar(Samolot &s);

    void startuj(Samolot &s);
};

class Samolot {
public:
    Samolot(Lotnisko &lotnisko, const string nazwa) : lotnisko(lotnisko), nazwa(nazwa) {}

    const string &getNazwa() const {
        return nazwa;
    }

    void operator()() {
        this_thread::sleep_for(chrono::milliseconds(zakres8(generator8)));
        lotnisko.laduj(*this);
        this_thread::sleep_for(chrono::milliseconds(zakres8(generator8)));
        lotnisko.kolujDoHangaru(*this);
        this_thread::sleep_for(chrono::milliseconds(zakres8(generator8)));
        lotnisko.opuscHangar(*this);
        this_thread::sleep_for(chrono::milliseconds(zakres8(generator8)));
        lotnisko.startuj(*this);


    }

private:
    Lotnisko &lotnisko;
    string nazwa;
};

class Hangar {
private:
    unsigned rozmiarHangaru;
    set<string> samoloty;
    Semafor semafor;
public:
    Hangar(int n) : rozmiarHangaru(n), semafor(POJEMNOSC_HANGARU) {

    }
void czekaj()
{
    semafor.czekaj();
}
    void parkuj(Samolot &s) {

        if (samoloty.size() < rozmiarHangaru) {
            samoloty.insert(s.getNazwa());

        } else {
            cout << "hangar pelny\n";
        }

    }

    void opusc(Samolot &s) {
        if (samoloty.count(s.getNazwa()) == 1) {
            samoloty.erase(s.getNazwa());

        } else {
            cout << "w hangarze nie ma tego samolotu\n";
        }
        semafor.sygnalizuj();
    }
};

void Lotnisko::laduj(Samolot &s)
{
hangar.czekaj();
    semaforPas.czekaj();
    if(pasWolny)
    {
        pasWolny=false;
        string info="Samolot " + s.getNazwa()+ " laduje\n";
        cout<<info;
        this_thread::sleep_for(chrono::milliseconds(zakres8(generator8)));
        info="Samolot " + s.getNazwa()+ " wyladowal\n";
        cout<<info;
        pasWolny=true;
    }
    else
    {
        cout<<"zderzenie na pasie";
    }
    semaforPas.sygnalizuj();
}
void Lotnisko::kolujDoHangaru(Samolot &s) {

    semaforDoHangaru.czekaj();
    hangar.parkuj(s);
    semaforDoHangaru.sygnalizuj();



}
void Lotnisko::opuscHangar(Samolot &s) {
    semaforZHangaru.czekaj();
    hangar.opusc(s);
    semaforZHangaru.sygnalizuj();
}
void Lotnisko::startuj(Samolot &s) {

    semaforPas.czekaj();

    if(pasWolny)
    {
        pasWolny=false;
        string info="Samolot " + s.getNazwa()+ " startuje\n";
        cout<<info;
        this_thread::sleep_for(chrono::milliseconds(zakres8(generator8)));
        info="Samolot " + s.getNazwa()+ " wystartowal\n";
        cout<<info;
        pasWolny=true;
    }
    else
    {
        cout<<"zderzenie na pasie";
    }

    semaforPas.sygnalizuj();
}


void l8z1() {
Hangar hangar(POJEMNOSC_HANGARU);
Lotnisko lotnisko(hangar);
vector<thread> watki;
for (int i=0;i<LICZBA_SAMOLOTOW;i++)
{
    watki.emplace_back(Samolot(lotnisko,to_string(i)));
}
    for (thread &w: watki) {
        w.join();
    }
}

