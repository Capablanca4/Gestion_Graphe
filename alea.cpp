#include <cstdlib>
#include <ctime>
#include "alea.h"

alea::alea(int a, int b):a{d_a},b{d_b}
{
}

int alea::val_alea(int a, int b)const
{
    return rand()%(b-a)+a;
}
int alea::ValeurBinaireAleatoire()const
{
    return val_alea(0,2);
}
bool alea::tirageAleatoire(int p)
{
    return val_alea(0,101)<=p;
}
