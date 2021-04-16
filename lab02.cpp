
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>

using namespace std;
#define M_PI 3.14

void kodWatku() {
    for (int i = 0; i < 10; ++i) {
        cout << "watek: " << this_thread::get_id() << " mówi cześć, i=" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void listing1() {

    thread w1(kodWatku);
    thread w2(kodWatku);
    w1.join();
    w2.join();
}

const int LICZBA_PUNKTOW = 10;
//zmiennych globalnych przechowywane są dane potrzebne do działania wątku 
double a = 0.0; //zakres całkowania
double b = M_PI;
double wynik = 0.0; //wartosc całki

//funkcja zawiera zadanie do wykonania w osobnym wątku 
void calkaSinusa() {
    cout << "Wątek pracuje..." << endl;
    double h = (b - a) / LICZBA_PUNKTOW;
    double s = sin(a);
    for (int i = 1; i < LICZBA_PUNKTOW; i++) {
        //lekkie spowolnienie wątku (wartość w milisekundach) //warto wypróbować różne wartości
        this_thread::sleep_for(chrono::milliseconds(10));
        s += 2 * sin(a + i * h);
    }

    s += sin(b);
    wynik = s * h / 2;
    cout << "Wątek się zakończył..." << endl;
}

int listing2() {

//tworzenie wątku 
    thread watek(calkaSinusa);
//główny wątek w między czasie może coś zrobić 
//np. sprawdzić możliwości sprzętu 
    cout << "Sprzętowa współbieżność: " << thread::hardware_concurrency() << endl;
    cout << "ID wątku: " << watek.get_id() << endl;
//oczekiwanie na zakończenie wątku 
    watek.join();
    cout << "wynik= " << wynik << endl;
    return EXIT_SUCCESS;

}

class CalkaSinusa {
private:
    double a, b; //zakres calkowania
    double *wartosc;// wskanik do zmiennej wynikoej

public:
    CalkaSinusa(double _a, double _b, double *_wartosc) : a(_a), b(_b), wartosc(_wartosc) {

    }

    void operator()();
};

void CalkaSinusa::operator()() {
    cout << "watek pracuje" << endl;

    double h = (b - a) / LICZBA_PUNKTOW;
    double s = sin(a);
    for (int i = 1; i < LICZBA_PUNKTOW; i++) {
        //lekkie spowolnienie wątku (wartość w milisekundach) //warto wypróbować różne wartości
        this_thread::sleep_for(chrono::milliseconds(1000));
        s += 2 * sin(a + i * h);
    }

    s += sin(b);
    *wartosc = s * h / 2;
    cout << "Wątek się zakończył..." << endl;
}


int listing3() {
    double wynik = 0.0;
    CalkaSinusa calka(0, M_PI, &wynik);
    thread watek(calka);


//główny wątek w między czasie może coś zrobić 
//np. sprawdzić możliwości sprzętu 
    cout << "Sprzętowa współbieżność: " << thread::hardware_concurrency() << endl;
    cout << "ID wątku: " << watek.get_id() << endl;
//oczekiwanie na zakończenie wątku 
    watek.join();
    cout << "wynik= " << wynik << endl;
    return EXIT_SUCCESS;
}


