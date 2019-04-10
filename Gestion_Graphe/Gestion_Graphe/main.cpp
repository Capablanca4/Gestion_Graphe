#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/Rang.h"
#include "include/alea.h"
#include <iostream>
#include <fstream>
#include <ctime>

int main() {
	using std::vector;
	int INFINI = INT_MAX;
	int NbNoeud = 12,NbArc = 19;
	std::vector<int> aps{0, 3, 6, 10, 14, 17, 20, 22, 24, 25, 27, 30};
	std::vector<int> fs{ 1, 2, -1, 3, 8, -1, 3, 5, 7, -1, 7, 8, 10, -1, 2, 5, -1, 6, 7, -1, 7, -1, 9, -1, -1, 10, -1, 9, 11, -1, -1 };
	std::cout << aps.size();
	Graphe::FsAps testFsAps{ NbNoeud, fs,NbArc,aps };
	testFsAps.affiche();
	vector<int> rang = testFsAps.rang();
	std::cout<<std::endl;
	for (int i = 0;i < rang.size();i++) {
		std::cout << rang[i] << " ";
	}
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