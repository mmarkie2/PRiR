

#include "lab05.h"

#include <iostream>
#include <mutex>


using namespace std;

template <typename TypDanych>
class Monitor
{
private:
    TypDanych dane;
    bool saDane;
    mutex mutexDane;
    condition_variable warunekSaNoweDane;
    condition_variable warunekZabranoDane;
};
void l5z1()

{
const int CZAS_PRACY=5;

}
void l5z2()
{

}
void l5z3()
{

}