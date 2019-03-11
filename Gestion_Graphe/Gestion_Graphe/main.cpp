#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/alea.h"
#include <iostream>

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
	/*Graphe::FsAps F1(MA3);
	F1.afficheFileSuivant();
	std::vector<std::vector<int>> D=F1.MatriceDesDistances();
	for (int i = 0; i < D.size(); i++) {
		for (int j = 0; j < D.size(); j++) {
			std::cout << D[i][j] << " ";
		}
		std::cout << std::endl;
	}
	*/

	/*
	Graphe::MatriceAdjacenceValuee M1(5);
	//M1.affiche();
	M1.AjouteArc(2, 2,-5 );
	std::cout << std::endl;
	M1.affiche();
	std::cout << M1.SansValeurNegative() << std::endl;
	M1.enregistrerMatriceAdjacence("mamatrice");
	Graphe::MatriceAdjacence M("mamatrice");
	M.affiche();
	system("pause");
	*/
	alea A(100);
	for (int i = 0; i <= 100; i++) {
		A = alea(100);
		std::cout << A.val_alea() << " " << i << " "<< A.tirageAleatoire(i);
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}