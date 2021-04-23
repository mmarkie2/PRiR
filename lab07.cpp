//
// Created by mm on 23.04.2021.
//
#include "iostream"
#include <string>
#include <random>
#include <thread>

#include <vector>
#include "Semafor.h"

using namespace std;
const int MAX_OPOZNIENIE = 1000;
const int LICZBA_FILOZOFOW = 5;
const int LICZBA_POSILKOW = 3;

random_device rd;
minstd_rand generator(rd());
uniform_int_distribution<int> rozklad(0, MAX_OPOZNIENIE);

class Filozof {
private:
    int numer;
    int lewyWidelec;
    int prawyWidelec;
    int zjedzonychPosilkow;

public:
    Filozof(int n) : numer(n), zjedzonychPosilkow(0) {

    }

    void operator()() {
        while (zjedzonychPosilkow < LICZBA_POSILKOW) {
            int czasPosilku = rozklad(generator);
            zjedzonychPosilkow++;
            cout << "Filozof " + std::to_string(numer) + " je " + std::to_string(zjedzonychPosilkow)
                    + " posilek przez najbliższe " + std::to_string(czasPosilku) + " ms \n";

            this_thread::sleep_for(chrono::milliseconds(czasPosilku));
            cout << "Filozof " + std::to_string(numer) + " skonczyl jesc " + std::to_string(zjedzonychPosilkow)
                    + " posilek "  + " \n";
        }

        cout << "Filozof " + std::to_string(numer) + " sie najadl \n ";
    }

};

void l7z1()
{
  vector<thread> filozofowie;
  for (int i=0; i<LICZBA_FILOZOFOW;++i)
  {
      filozofowie.emplace_back(Filozof(i));
  }

  for(thread &f: filozofowie)
  {
      f.join();
  }
}