#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/alea.h"
#include <iostream>
#include <fstream>

int main() {
	int NbNoeud = 7, NbArc = 11;
	std::vector<std::vector<int>> M{ {0,1,1,0,1,0,0},
									 {0,0,1,0,0,0,0},
									 {0,0,1,1,0,0,0},
									 {0,0,0,0,1,1,0},
									 {0,0,1,0,0,0,0},
									 {0,0,0,0,0,0,0},
									 {0,0,0,1,0,1,0} };
	const int INFINI = INT_MAX;
	std::vector<std::vector<int>> MValuee{ {INFINI,1,1,INFINI,1,INFINI,INFINI},
										   {INFINI,INFINI,1,INFINI,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,1,1,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,INFINI,INFINI,1,1,INFINI},
										   {INFINI,INFINI,1,INFINI,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,INFINI,INFINI,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,INFINI,1,INFINI,1,INFINI} };
	Graphe::MatriceAdjacenceValuee Mat{ NbNoeud };
	std::cout<<Mat.sansValeurNegative()<<std::endl;
	Mat.ajouterArc(1, 1, -1);
	std::cout << Mat.sansValeurNegative() << std::endl;
	getchar();
}