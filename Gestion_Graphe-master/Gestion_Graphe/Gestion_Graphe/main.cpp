#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"

int main() {
	/*int NbSommets = 7,NbArc = 18;
	std::vector<int> FileSuivant{ 2,3,5,0,3,0,3,4,0,5,6,0,3,0,0,4,6,0 };
	std::vector<int> AdressePremierSuccesseur{ 0,4,6,9,12,14,15 };
	Graphe::FsAps testFsAps{ NbSommets, FileSuivant,NbArc,AdressePremierSuccesseur };
	Graphe::Distance testDist{ testFsAps };*/

	/*
	std::vector<std::vector<int>> M1= { {0,0,0,0,0,0,0},
										 {1,0,0,0,0,0,0},
										 {1,1,1,0,1,0,0},
										 {0,0,1,0,0,0,1},
										 {1,0,0,1,0,0,0},
										 {0,0,0,1,0,0,1},
										 {0,0,0,0,0,0,0} };


	std::vector<std::vector<int>> M2 = { {0,0,0,1,0,0,0,0},
										 {1,0,0,0,0,0,0,0},
										 {1,1,1,0,1,0,0,1},
										 {0,0,1,0,0,1,1,0},
										 {0,0,0,1,0,0,0,0},
										 {0,0,0,1,0,0,1,0},
										 {0,0,0,0,0,0,0,0},
										 {0,0,0,1,0,0,0,0}};
	Graphe::MatriceAdjacence MA1(M1,7,11);
	Graphe::MatriceAdjacence MA2(M2, 8, 14);
	Graphe::MatriceAdjacence MA3 = MA1 + MA2;
	MA3.affiche();*/

	Graphe::MatriceAdjacenceValuee M1(5);
	M1.affiche();
	system("pause");
	return 0;
}