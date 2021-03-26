

#include "lab05.h"

#include <iostream>
#include <mutex>
#include <random>


using namespace std;

const int CZAS_PRACY=5;


template <typename TypDanych>
class Monitor
{
private:
    TypDanych dane;
    bool saDane;
    mutex mutexDane;
    condition_variable warunekSaNoweDane;
    condition_variable warunekZabranoDane;

public:
    Monitor()
    {
        saDane=false;

    }
    void zapisz(TypDanych noweDane)
    {
       unique_lock<mutex> blokada(mutexDane);
       saDane=true;
       dane=noweDane;
       warunekSaNoweDane.notify_one();
    }
    TypDanych odczytaj()
    {
        unique_lock<mutex> blokada(mutexDane);

        if(!saDane)
        {
            warunekSaNoweDane.wait(blokada);
        }
        saDane=false;
        warunekZabranoDane.notify_one();
        return  dane;
    }
};

class  Producent
{
private:
    int czas;
    Monitor<char>& pojemnik;
    char biezacyZnak;

    minstd_rand generator;
    uniform_int_distribution<char> rozklad;

public:
    Producent(Monitor <char>& _pojemnik):
    czas(0), pojemnik(_pojemnik), biezacyZnak('a'),
    generator(random_device()()),rozklad('a','z')
    {

    }

    void operator()()
    {
        while (czas<CZAS_PRACY)
        {
            pojemnik.zapisz(biezacyZnak);
            biezacyZnak=(biezacyZnak+1-97)%25-97;
            this_thread::sleep_for(chrono::seconds(1));
            ++czas;
        }
        pojemnik.zapisz(EOF);
    }
};

void l5z1()

{


}
void l5z2()
{

}
void l5z3()
{

}