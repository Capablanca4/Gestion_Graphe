#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/alea.h"
#include <iostream>

int main() {
	int NbNoeud = 7, NbArc = 11;
	std::vector<std::vector<int>> M{ {0,1,1,0,1,0,0},
									 {0,0,1,0,0,0,0},
									 {0,0,1,1,0,0,0},
									 {0,0,0,0,1,1,0},
									 {0,0,1,0,0,0,0},
									 {0,0,0,0,0,0,0},
									 {0,0,0,1,0,1,0} };

	Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
	Mat.supprimeSommet(0);
}