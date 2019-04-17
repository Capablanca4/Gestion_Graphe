#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/Rang.h"
#include "include/alea.h"
#include "CoeficientConnexe.h"
#include "GrapheReduit.h"
#include <iostream>
#include <fstream>
#include <ctime>

int main() {
	using std::vector;
	int INFINI = INT_MAX;
	int NbNoeud = 12,NbArc = 19;
	std::vector<int> aps{0, 3, 6, 10, 14, 17, 20, 22, 24, 25, 27, 30 };
	std::vector<int> fs{2, 3, 0, 4, 9, 0, 4, 6, 8, 0, 8, 9, 11, 0, 3, 6, 0, 7, 8, 0, 8, 0, 10, 0, 0, 11, 0, 10, 12, 0, 0 };
	std::cout << aps.size();
	Graphe::FsAps testFsAps{ NbNoeud, fs,NbArc,aps };
	testFsAps.affiche();
	Graphe::Distance D(testFsAps);
	D.affiche();
	Graphe::CoeficientConnexe C(D);
	//Graphe::GrapheReduit G(C, testFsAps);
	//G.getFsAps().affiche();
	/*Graphe::Distance testDist{ testFsAps };
	testDist.affiche();
	getchar();*/

	/*
	vector<vector<int>> Matrice = { {0,2,INFINI,2,INFINI,6},
	{5,0,4,INFINI,0,2},{3,INFINI,0,4,INFINI,INFINI},{INFINI,INFINI,INFINI,0,1,1},{INFINI,INFINI,6,INFINI,0,2},{INFINI,INFINI,INFINI,INFINI,INFINI,0} };
	srand(time(0));
	alea A(10);
	Graphe::MatriceAdjacenceValuee M(Matrice,6,13);
	M.affiche();
	std::vector<int>distance, predecesseur;;
	M.Djikstra(distance, predecesseur, 1);
	std::cout << std::endl;
	M.affiche();
	std::cout << std::endl;
	for (int i = 0;i < distance.size();i++) {
		std::cout << distance[i] << " ";
	}
	std::cout << std::endl;
	*/
	system("pause");
	return 0;
}