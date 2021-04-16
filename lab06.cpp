//
// Created by mm on 16.04.2021.
//
#include "iostream"
#include <string>

using namespace std;
class Pociąg
{
private:
    string m_nazwa;
    Peron &Peron;
    Peron &PeronZapasowy;
public:
    Pociąg(string n, Peron &p1, Peron &p2);
    void operator()();
    string nazwa();

};
class Peron{
private:
    string nazwa;
    bool pusty;
public:
    Peron(string n): nazwa(n), pusty (true)
    {

    }
    void przyjazd (Pociąg& p)
    {
        if(pusty)
        {
            string info;
            info.append("Pociąg ");
            info.append(p.nazwa());
            info.append(" wjedza na peron  ");
            info.append(nazwa);
            info.append("\n ");
            cout << info;
        }
    }
};

void l6z1()

{

}