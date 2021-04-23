//
// Created by mm on 23.04.2021.
//
#include "iostream"
#include <string>
#include <random>
#include <thread>

#include <vector>
#include "Semafor.h"

const int MAX_OPOZNIENIE =1000;
const int LICZBA_FILOZOFOW =5;
const int LICZBA_POSILKOW =3;

random_device rd;
minstd_rand generator(rd());

class Filozof
{
private:
    int numer;
    int lewyWidelec;
    int prawyWidelec;
    int zjedzonychPosilkow;

public:
    Filozof(int n): numer (n),zjedzonychPosilkow(0){

    }

    void operator()()
    {

    }
};