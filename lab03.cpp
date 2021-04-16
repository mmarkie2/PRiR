#include "lab03.h"
#include <random>
#include <iostream>
#include <thread>
#include "kolory.h"

#include <iomanip>


using namespace std;


short wynik1, wynik2;
int rozmiarTablicy = 10;
unsigned int polowa = rozmiarTablicy / 2;


void wypelnijLosowymi(short T[], int n) {
    random_device maszynkaLosujaca;
    uniform_int_distribution<short> dystrybucja(-10, 10);
    for (int i = 0; i < n; i++) T[i] = dystrybucja(maszynkaLosujaca);
}


void wyswietlTablice(const short T[], int n) {
    short suma = 0;
    cout << "informacje o tablicy:" << endl;
    for (int i = 0; i < n; i++) {
        cout << T[i] << " ";
        suma += T[i];
    }
    cout << endl << "Suma=" << suma << endl << endl;
}

void sumujOdDo(const short T[], int poczatek, int koniec, short &wynik) {

    string k = Kolor::nastepny(), r = Kolor::reset();

    wynik = 0;
    for (int i = poczatek; i < koniec; i++) {
        wynik += T[i];

        string info = k + to_string(T[i]) + r + "\n";
        cout << info;
    }

}


void l3z1() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);

    thread watek1(sumujOdDo, TAB, 0, polowa, ref(wynik1));
    thread watek2(sumujOdDo, TAB, polowa, rozmiarTablicy, ref(wynik2));

    watek1.join();
    watek2.join();


    cout << endl << "Wyniki pracy wątków" << endl
         << "suma1=" << wynik1 << " suma2=" << wynik2
         << " suma=" << wynik1 + wynik2 << endl << endl;

    delete[] TAB;
}


void sumujCoDrugi(const short T[], int poczatek, int koniec, short &wynik) {

    string k = Kolor::nastepny(), r = Kolor::reset();

    wynik = 0;
    for (int i = poczatek; i < koniec; i = i + 2) {
        wynik += T[i];

        string info = k + to_string(T[i]) + r + "\n";
        cout << info;
    }

}

void l3z2() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);

    thread watek1(sumujCoDrugi, TAB, 0, rozmiarTablicy, ref(wynik1));
    thread watek2(sumujCoDrugi, TAB, 1, rozmiarTablicy, ref(wynik2));

    watek1.join();
    watek2.join();


    cout << endl << "Wyniki pracy wątków" << endl
         << "suma1=" << wynik1 << " suma2=" << wynik2
         << " suma=" << wynik1 + wynik2 << endl << endl;

    delete[] TAB;
}

void sumujZnak(const short T[], char znak, int koniec, short &wynik) {

    string k = Kolor::nastepny(), r = Kolor::reset();

    wynik = 0;
    for (int i = 0; i < koniec; i++) {
        if (znak == '-' && T[i] < 0) {
            wynik += T[i];
            string info = k + to_string(T[i]) + r + "\n";
            cout << info;
        } else if (znak == '+' && T[i] > 0) {
            wynik += T[i];
            string info = k + to_string(T[i]) + r + "\n";
            cout << info;
        }


    }

}

void l3z3() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);

    thread watek1(sumujZnak, TAB, '-', rozmiarTablicy, ref(wynik1));
    thread watek2(sumujZnak, TAB, '+', rozmiarTablicy, ref(wynik2));

    watek1.join();
    watek2.join();


    cout << endl << "Wyniki pracy wątków" << endl
         << "suma1=" << wynik1 << " suma2=" << wynik2
         << " suma=" << wynik1 + wynik2 << endl << endl;

    delete[] TAB;
}

void kwadratujIPodminCoDrugi(short T[], int poczatek, int koniec) {

    string k = Kolor::nastepny(), r = Kolor::reset();


    for (int i = poczatek; i < koniec; i = i + 2) {


        string info = k + to_string(T[i]) + r + "\n";
        cout << info;

        T[i] = T[i] * T[i];
    }

}

void l3z4() {
    short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);

    wyswietlTablice(TAB, rozmiarTablicy);

    thread watek1(kwadratujIPodminCoDrugi, TAB, 0, rozmiarTablicy);
    thread watek2(kwadratujIPodminCoDrugi, TAB, 1, rozmiarTablicy);

    watek1.join();
    watek2.join();

    wyswietlTablice(TAB, rozmiarTablicy);


    delete[] TAB;
}

void wyswietlTablice(const float T[], int n) {

    cout << "informacje o tablicy:" << endl;
    for (int i = 0; i < n; i++) {
        cout << setprecision(2) << T[i] << " ";

    }

}

void filtrDyskretnyCoDrugi(short T[], float resT[], int poczatek, int koniec) {

    string k = Kolor::nastepny(), r = Kolor::reset();


    for (int i = poczatek; i < koniec; i = i + 2) {


        string info = k + to_string(T[i]) + r + "\n";
        cout << info;

        if (i == 0) {
            resT[i] = (float) (T[i] + T[i + 1]) / 2;
        } else if (i == koniec - 1) {
            resT[i] = (float) (T[i - 1] + T[i]) / 2;
        } else {
            resT[i] = (float) (T[i - 1] + T[i] + T[i + 1]) / 3;
        }


    }

}

void l3z5() {
    static short *TAB; //Tablica
    TAB = new short[rozmiarTablicy];

    float *resTAB = new float[rozmiarTablicy];

    wypelnijLosowymi(TAB, rozmiarTablicy);
    cout << "Dane" << endl;
    wyswietlTablice(TAB, rozmiarTablicy);

    thread watek1(filtrDyskretnyCoDrugi, TAB, resTAB, 0, rozmiarTablicy);
    thread watek2(filtrDyskretnyCoDrugi, TAB, resTAB, 1, rozmiarTablicy);

    watek1.join();
    watek2.join();

    cout << "Wyniki" << endl;
    wyswietlTablice(resTAB, rozmiarTablicy);

    delete[] TAB;
    delete[] resTAB;
}
