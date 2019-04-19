#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/Rang.h"
#include "include/alea.h"
#include "include/Prufer.h"
#include "Djikstra.h"
#include "Kruskal.h"
#include <iostream>
#include <fstream>

int main() {
	int nbNoeud = 5, nbArc = 12;
	const int INFINI = INT_MAX;
	std::vector<std::vector<int>> Poids{ {INT_MAX,1,2,INT_MAX,INT_MAX},
										 {1,INT_MAX,INT_MAX,2,INT_MAX},
										 {2,INT_MAX,INT_MAX,2,3},
										 {INT_MAX,2,2,INT_MAX,3},
										 {INT_MAX,INT_MAX,3,3,INT_MAX} };
	Graphe::MatriceAdjacenceValuee TestMat{ Poids ,nbNoeud,nbArc };
	Graphe::Kruskal testKruskal{ TestMat };
	testKruskal.affiche();
	getchar();
	return 0;
}