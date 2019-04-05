#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/Rang.h"
#include "include/alea.h"
#include <iostream>
#include <fstream>

int main() {
	int NbNoeud = 7,NbArc = 11;
	std::vector<int> fs{ 2,3,5,0,3,0,3,4,0,5,6,0,3,0,0,4,6,0 };
	std::vector<int> aps{ 0,4,6,9,12,14,15 };
	Graphe::FsAps testFsAps{ NbNoeud, fs,NbArc,aps };
	Graphe::Distance testDist{ testFsAps };
	testDist.affiche();
	getchar();
	return 0;
}