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

random_device rd;
minstd_rand generator(rd());
uniform_int_distribution<int> zakres(1000, 3000);

class Hangar;

class Samolot;

class Lotnisko {
private:
    bool pasWolny;
    Hangar& hangar;

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
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        lotnisko.laduj(*this);
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        lotnisko.kolujDoHangaru(*this);
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        lotnisko.opuscHangar(*this);
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
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
public:
    Hangar(int n) : rozmiarHangaru(n) {

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
    }
};

void Lotnisko::laduj(Samolot &s)
{
    if(pasWolny)
    {
        pasWolny=false;
        string info="Samolot " + s.getNazwa()+ " laduje\n";
        cout<<info;
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        info="Samolot " + s.getNazwa()+ " wyladowal\n";
        cout<<info;
        pasWolny=true;
    }
    else
    {
        cout<<"zderzenie na pasie";
    }
}
void Lotnisko::kolujDoHangaru(Samolot &s) {
    hangar.parkuj(s);
}
void Lotnisko::opuscHangar(Samolot &s) {
    hangar.opusc(s);
}
void Lotnisko::startuj(Samolot &s) {
    if(pasWolny)
    {
        pasWolny=false;
        string info="Samolot " + s.getNazwa()+ " startuje\n";
        cout<<info;
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        info="Samolot " + s.getNazwa()+ " wystartowal\n";
        cout<<info;
        pasWolny=true;
    }
    else
    {
        cout<<"zderzenie na pasie";
    }
}


void l8z1() {
Hangar hangar(POJEMNOSC_HANGARU);
Lotnisko lotnisko(hangar);
vector<thread> watki;
for (int i=0;i<LICZBA_SAMOLOTOW;i++)
{
    watki.emplace_back(Samolot(lotnisko,to_string(i)));
}
}

