//
// Created by mm on 16.04.2021.
//
#include "iostream"
#include <string>
#include <random>
#include <thread>

using namespace std;

class Peron;

class Pociag {
private:
    string m_nazwa;
    Peron &peron;
    Peron &peronZapasowy;
public:
    Pociag(string n, Peron &p1, Peron &p2);

    void operator()();

    string nazwa();

};


class Peron {
private:
    string nazwa;
    bool pusty;
public:
    Peron(string n) : nazwa(n), pusty(true) {

    }

    void przyjazd(Pociag &p) {
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
    }

    bool czyPusty() {
        return pusty;
    }
};

minstd_rand generator;
uniform_int_distribution<int> zakres(0, 500);


Pociag::Pociag(string n, Peron &p1, Peron &p2)
        : m_nazwa(n), peron(p1), peronZapasowy(p2) {

}

void Pociag::operator()() {
    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
        if (peron.czyPusty()) {
            peron.przyjazd(*this);
            this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
            peron.odjazd(*this);

        } else {
            peronZapasowy.przyjazd(*this);
            this_thread::sleep_for(chrono::milliseconds(zakres(generator)));
            peronZapasowy.odjazd(*this);
        }
    }
}

string Pociag::nazwa() {
    return m_nazwa;
}


void l6z1() {
    Peron p1("p1"), p2("p2"), p3("p3");
    Pociag pociag1("pociag1", p2, p1);
    Pociag pociag2("pociag2", p2, p3);
    Pociag pociag3("pociag3", p2, p1);
    Pociag pociag4("pociag4", p2, p3);

    thread w1(pociag1),w2(pociag2),w3(pociag3),w4(pociag4);
    w1.join();
    w2.join();
    w3.join();
    w4.join();




}