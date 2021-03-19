//l
#include "lab04.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

const int OPOZNIENIE=100;
int licznik;

class Watek
{
  private:
int numer;
public:
Watek(int _numer): numer(_numer){}

void operator()()
{

while (licznik>0)
{

  cout<<"w "<<numer<<" 1: "<< licznik<<endl;
  --licznik;
  this_thread::sleep_for(chrono::microseconds(OPOZNIENIE));
}

}
};

void l4z1(){

  licznik=50;
  thread w1(Watek(1));
   thread w2(Watek(2));
   w1.join();
     w2.join(); 

   
}
void l4z2(){

  licznik=50;
  thread w1(Watek2(1));
   thread w2(Watek2(2));
   w1.join();
     w2.join(); 

}
void l4z3(){

}
void l4z4(){

}

//dodatkowe tablica mutexow, zmienna globalna licznik
void l4zDodatkowe(){

}
