

#include "lab05.h"

#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <list>

using namespace std;

const int CZAS_PRACY = 5;


template<typename TypDanych>
class Monitor {
private:
    TypDanych dane;
    bool saDane;
    mutex mutexDane;
    condition_variable warunekSaNoweDane;
    condition_variable warunekZabranoDane;

public:
    Monitor() {
        saDane = false;

    }

    void zapisz(TypDanych noweDane) {
        unique_lock<mutex> blokada(mutexDane);
        saDane = true;
        dane = noweDane;
        warunekSaNoweDane.notify_one();
    }

    TypDanych odczytaj() {
        unique_lock<mutex> blokada(mutexDane);

        if (!saDane) {
            warunekSaNoweDane.wait(blokada);
        }
        saDane = false;
        warunekZabranoDane.notify_one();
        return dane;
    }
};

class Producent {
private:
    int czas;
    Monitor<char> &pojemnik;
    char biezacyZnak;

    minstd_rand generator;
    uniform_int_distribution<int> rozklad;

public:
    Producent(Monitor<char> &_pojemnik) :
            czas(0), pojemnik(_pojemnik), biezacyZnak('a'),
            generator(random_device()()), rozklad('a', 'z') {

    }

    void operator()() {
        while (czas < CZAS_PRACY) {
            pojemnik.zapisz(biezacyZnak);
            biezacyZnak = (biezacyZnak + 1 - 97) % 25 + 97;
            this_thread::sleep_for(chrono::seconds(1));
            ++czas;
        }
        pojemnik.zapisz(EOF);
    }
};

class Konsument {
private:
    Monitor<char> &pojemnik;
public:
    Konsument(Monitor<char> &_pojemnik) : pojemnik(_pojemnik) {

    }

    void operator()() {
        char znak = pojemnik.odczytaj();
        while (znak != EOF) {
            cout << znak << endl;
            znak = pojemnik.odczytaj();
        }
    }
};

void l5z1() {
    random_device r;
    minstd_rand generator(r());
    Monitor<char> pojemnik;
    Konsument konsument(pojemnik);
    Producent producent(pojemnik);
    thread wk(konsument);
    thread wp(producent);

    wp.join();
    wk.join();


}


template<typename TypDanych>
class Monitor2 {
private:
    TypDanych dane;
    bool saDane;
    mutex mutexDane;
    condition_variable warunekSaNoweDane;
    condition_variable warunekZabranoDane;
    unique_lock<mutex> lockProd;
    bool uzyty;
public:
    void setUzyty(bool uzyty) {
        Monitor2::uzyty = uzyty;
    }

public:
    bool isUzyty() const {
        return uzyty;
    }

public:
    Monitor2() {
        saDane = false;
        uzyty = false;

    }

    void zapisz(TypDanych noweDane, int id) {

        unique_lock<mutex> blokada(mutexDane);

        if (saDane) {
            warunekZabranoDane.wait(blokada);
        }
        cout << "Producent " << id << ":  " << noweDane << endl;
        saDane = true;

        dane = noweDane;

        warunekSaNoweDane.notify_one();

    }

    TypDanych odczytajProd(int id) {
        unique_lock<mutex> blokada(mutexDane);
        // cout<<"Producent odczyt "<<id<<":  "<<dane<<endl;

        return dane;
    }

    TypDanych odczytaj(int id) {
        unique_lock<mutex> blokada(mutexDane);


        warunekSaNoweDane.wait(blokada);

        saDane = false;

        cout << "Konsument " << id << ":  " << dane << endl;
        warunekZabranoDane.notify_one();
        return dane;
    }
};

const int CZAS_PRACY2 = 2;

class Producent2 {
private:
    int id;
    int czas;
    Monitor2<char> &pojemnik;
    char biezacyZnak;

    minstd_rand generator;
    uniform_int_distribution<int> rozklad;

public:
    Producent2(Monitor2<char> &_pojemnik, int _id) :
            czas(0), pojemnik(_pojemnik), biezacyZnak('a'),
            generator(random_device()()), rozklad('a', 'z'), id(_id) {

    }

    void operator()() {
        while (czas < CZAS_PRACY2) {
            if (pojemnik.isUzyty()) {
                biezacyZnak = pojemnik.odczytajProd(id);
                biezacyZnak = (biezacyZnak + 1 - 97) % 25 + 97;
            } else {
                pojemnik.setUzyty(true);
            }

            pojemnik.zapisz(biezacyZnak, this->id);

            this_thread::sleep_for(chrono::milliseconds(rand() % 500));
            ++czas;
        }
        pojemnik.zapisz(EOF, this->id);
    }
};

class Konsument2 {
private:
    int id;
    Monitor2<char> &pojemnik;
public:
    Konsument2(Monitor2<char> &_pojemnik, int _id) : pojemnik(_pojemnik), id(_id) {

    }

    void operator()() {
        char znak = pojemnik.odczytaj(this->id);
        while (znak != EOF) {

            znak = pojemnik.odczytaj(this->id);
        }
    }
};

void l5z2() {
    random_device r;
    minstd_rand generator(r());
    Monitor2<char> pojemnik;

    vector<thread> watki;

    for (int i = 0; i < 5; i++) {
        Konsument2 konsument(pojemnik, i);

        watki.emplace_back(konsument);
        Producent2 producent(pojemnik, i);
        watki.emplace_back(producent);
    }

    for (thread &watek :watki) {
        watek.join();
    }

}

template<typename TypDanych>
class Monitor3 {
private:
    list<TypDanych> dane;
    bool saDane;
    mutex mutexDane;
    condition_variable warunekSaNoweDane;
    condition_variable warunekZabranoDane;
    unique_lock<mutex> lockProd;
    bool uzyty;
public:
    void setUzyty(bool uzyty) {
        Monitor3::uzyty = uzyty;
    }

public:
    bool isUzyty() const {
        return uzyty;
    }

public:
    Monitor3() {
        saDane = false;

        dane = list<TypDanych>();
    }

    void zapisz(TypDanych noweDane, int id) {

        unique_lock<mutex> blokada(mutexDane);


        cout << "Producent " << id << ":  " << noweDane << endl;


        dane.push_front(noweDane);


        warunekSaNoweDane.notify_one();

    }

    TypDanych odczytajProd(int id) {
        unique_lock<mutex> blokada(mutexDane);
        // cout<<"Producent odczyt "<<id<<":  "<<dane<<endl;

    return dane.back();

    }

    TypDanych odczytaj(int id) {
        unique_lock<mutex> blokada(mutexDane);


        warunekSaNoweDane.wait(blokada);

        saDane = false;

        char pobierana = dane.back();
        dane.pop_back();
        cout << "Konsument " << id << ":  " << pobierana << endl;

        cout << "Zawartosc po odczycie "  << ":  "  << endl;
        for (auto i:dane)
        {
            cout << i << ",  "  ;
        }
        cout  << endl;

        warunekZabranoDane.notify_one();
        return pobierana;
    }
};

const int CZAS_PRACY3 = 2;

class Producent3 {
private:
    int id;
    int czas;
    Monitor3<char> &pojemnik;
    char biezacyZnak;

    minstd_rand generator;
    uniform_int_distribution<int> rozklad;

public:
    Producent3(Monitor3<char> &_pojemnik, int _id) :
            czas(0), pojemnik(_pojemnik), biezacyZnak('a'),
            generator(random_device()()), rozklad('a', 'z'), id(_id) {

    }

    void operator()() {
        while (czas < CZAS_PRACY3) {




            pojemnik.zapisz(biezacyZnak, this->id);
            biezacyZnak = (biezacyZnak + 1 - 97) % 25 + 97;
            this_thread::sleep_for(chrono::milliseconds(rand() % 500));
            ++czas;
        }
        pojemnik.zapisz(EOF, this->id);
    }
};

class Konsument3 {
private:
    int id;
    Monitor3<char> &pojemnik;
public:
    Konsument3(Monitor3<char> &_pojemnik, int _id) : pojemnik(_pojemnik), id(_id) {

    }

    void operator()() {
        char znak = pojemnik.odczytaj(this->id);
        while (znak != EOF) {

            znak = pojemnik.odczytaj(this->id);
        }
    }
};


void l5z3() {

    random_device r;
    minstd_rand generator(r());
    Monitor3<char> pojemnik;

    vector<thread> watki;

    for (int i = 0; i < 5; i++) {
        Konsument3 konsument(pojemnik, i);

        watki.emplace_back(konsument);
        Producent3 producent(pojemnik, i);
        watki.emplace_back(producent);
    }

    for (thread &watek :watki) {
        watek.join();
    }


}