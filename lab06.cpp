//
// Created by mm on 16.04.2021.
//
#include "iostream"
#include <string>
#include <random>
#include <thread>

#include <vector>
#include "Semafor.h"

using namespace std;

class Peron;

class Stacja;

class Pociag {
private:
    string m_nazwa;
public:
    const string &getMNazwa() const;

private:
    Stacja &stacja;


public:
    Pociag(string n, Stacja &stacja);

    void operator()();

    string nazwa();

};


class Peron {
private:
    string nazwa;
public:
    const string &getNazwa() const {
        return nazwa;
    }

private:
    bool pusty;
    Pociag *pociag = nullptr;
public:
    Pociag *getPociag() const {
        return pociag;
    }

public:
    Peron(string n) : nazwa(n), pusty(true) {

    }

    void przyjazd(Pociag &p) {
        pociag = &p;
        if (pusty) {
            string info;
            info.append("Pociąg ");
            info.append(p.nazwa());
            info.append(" wjedza na peron  ");
            info.append(nazwa);
            info.append("\n ");
            cout << info;
        } else {
            string info;
            info.append("Pociąg ");
            info.append(p.nazwa());
            info.append(" spowoduje katastrofe na peron  ");
            info.append(nazwa);
            info.append("\n ");
            cout << info;
        }

        pusty = false;
    }

    void odjazd(Pociag &p) {
        string info;
        info.append("Pociąg ");
        info.append(p.nazwa());
        info.append(" opuszcza peron  ");
        info.append(nazwa);
        info.append("\n ");
        cout << info;
        pusty = true;
        pociag = nullptr;
    }

    bool czyPusty() {
        return pusty;
    }


};

class Stacja {
    vector<Peron>& perony;
    Semafor semafor;
    mutex mutexPerony;
public :
    explicit Stacja(vector<Peron>& _perony) : perony(_perony), semafor(_perony.size()) {

    }

    bool czyWolnyPeron() {
        return semafor.wartosc() > 0;
    }
void wyswietlPerony()
{
    string s="";
    for ( Peron& peron:perony) {
       s+="peron: "+peron.getNazwa()+ "  ";
        if (peron.getPociag()!= nullptr ) {
          s+=   peron.getPociag()->nazwa();
        }else
        {
            s+= "brak   ";
        }

    }
    cout<<s+", wolne perony: "+to_string(semafor.wartosc())+"  \n";


}
    void przyjazd(Pociag &pociag) {
        semafor.czekaj();
        unique_lock<mutex> blokadaLicznika(mutexPerony);
        for (Peron &peron:perony) {
            if (peron.czyPusty()) {
                peron.przyjazd(pociag);
                wyswietlPerony();
                return;
            }

        }
        perony[0].przyjazd(pociag);
        wyswietlPerony();
    }

    void odjazd(Pociag &pociag) {

        for (Peron& peron:perony) {
            if (peron.getPociag()!= nullptr && peron.getPociag()->nazwa() == pociag.nazwa()) {
                peron.odjazd(pociag);
                break;
            }
        }
        semafor.sygnalizuj();
    }

};

minstd_rand generator;
uniform_int_distribution<int> zakres(0, 500);


void Pociag::operator()() {
    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));

            stacja.przyjazd(*this);
            this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
            stacja.odjazd(*this);


    }
}

string Pociag::nazwa() {
    return m_nazwa;
}

Pociag::Pociag(string n, Stacja &stacja) : m_nazwa(n), stacja(stacja) {

}

const string &Pociag::getMNazwa() const {
    return m_nazwa;
}


void l6z1() {
    vector<Peron> perony;
    Peron p1("p1"),p2("p2"),p3("p3");
    perony.push_back( p1);
    perony.push_back(p2);
    perony.push_back(p3);
    Stacja stacja(perony);


    Pociag pociag1("pociag1", stacja);
    Pociag pociag2("pociag2", stacja);
    Pociag pociag3("pociag3", stacja);
    Pociag pociag4("pociag4", stacja);

    thread w1(pociag1), w2(pociag2), w3(pociag3), w4(pociag4);
    w1.join();
    w2.join();
    w3.join();
    w4.join();


}