//l
#include "lab04.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <string>
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

const int LICZBA_WATKOW = 5;
const int ZNAKOW_DO_ZAPISANIA = 1024;

class Watek4 {
private:
    char znak;
    string &lancuch;
public:
    Watek4(char _znak,
           string &_lancuch) : znak(_znak), lancuch(_lancuch) {}

    void operator()() {

            licznikMutex.lock();
        for (int i = 0; i < ZNAKOW_DO_ZAPISANIA; ++i) {

                lancuch[i] = znak;

            this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));

        }
            licznikMutex.unlock();

    }
};

void l4z4() {
    string lancuch;
    lancuch.resize(ZNAKOW_DO_ZAPISANIA);
    vector<thread> watki;

    for (unsigned int i = 0; i < LICZBA_WATKOW; ++i) {
        watki.push_back(thread(Watek4('a' + i, lancuch)));
    }

    for (thread &w: watki) {
        w.join();
    }
    cout << lancuch<<endl;
}


//dodatkowe tablica mutexow, zmienna globalna licznik
void l4zDodatkowe() {

}
