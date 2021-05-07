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
#include "Semafor.h"

using namespace std;
const int POJEMNOSC_HANGARU=5;
const int LICZBA_SAMOLOTOW=10;

random_device rd;
minstd_rand generator(rd());
uniform_int_distribution<int> zakres(1000, 3000);

class Hangar;
class Samolot;

class Lotnisko
{
private:
    bool pasWolny;
    Hangar hangar;

public:
    Lotnisko(Hangar &h) : pasWolny(true), hangar(h)
    {
        void laduj(Samolot &s);
        void kolujDoHangaru(Samolot &s);
        void oposcHangar(Samolot &s);
        void startuj(Samolot &s);
    }

};

class Samolot

        {
        public:
    Samolot(Lotnisko &lotnisko, const string nazwa) : lotnisko(lotnisko), nazwa(nazwa) {}
void operator()()
        {
            this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        }
private:
            Lotnisko &lotnisko;
            string nazwa;
        };
void l8z1() {

}

