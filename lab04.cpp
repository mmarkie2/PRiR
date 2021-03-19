//l
#include "lab04.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>

using namespace std;

const int OPOZNIENIE = 100;
int licznik;
mutex licznikMutex;


class Watek {
private:
    int numer;
public:
    Watek(int _numer) : numer(_numer) {}

    void operator()() {

        while (licznik > 0) {

            cout << "w " << numer << " 1: " << licznik << endl;
            --licznik;
            this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));
        }

    }
};

void l4z1() {

    licznik = 50;
    thread w1(Watek(1));
    thread w2(Watek(2));
    w1.join();
    w2.join();


}

class Watek2 {
private:
    int numer;
public:
    Watek2(int _numer) : numer(_numer) {}

    void operator()() {

        while (licznik > 0) {

            {
                lock_guard<mutex> blokada(licznikMutex);
                if (licznik <= 0) {
                    break;
                }
                cout << "w " << numer << " 1: " << licznik << endl;
                --licznik;
            }
            this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));


        }

    }
};

void l4z2() {

    licznik = 50;
    thread w1(Watek2(1));
    thread w2(Watek2(2));
    w1.join();
    w2.join();

}

class Watek3 {
private:
    int numer;
public:
    Watek3(int _numer) : numer(_numer) {}

    void operator()() {

        while (licznik > 0) {

            licznikMutex.lock();

                if (licznik <= 0) {
                    break;
                }
                cout << "w " << numer << " 1: " << licznik << endl;
                --licznik;
            licznikMutex.unlock();
            this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));


        }

    }
};

void l4z3() {
    licznik = 50;
    thread w1(Watek3(1));
    thread w2(Watek3(2));
    w1.join();
    w2.join();
}

void l4z4() {

}

//dodatkowe tablica mutexow, zmienna globalna licznik
void l4zDodatkowe() {

}
