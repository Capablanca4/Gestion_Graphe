#include <cstdlib>
#include <ctime>
#include "../include/alea.h"


alea::alea() :
	d_val{ rand() } {}

alea::alea(int a, int b) :
	d_val{ rand() % (b - a) + a } {}

alea::alea(int a) :
	d_val{ rand() % (a)+1 } {}

int alea::val_alea() const {
	return d_val;
}

bool alea::tirageAleatoire(int p) {
	return p >= d_val;
}
