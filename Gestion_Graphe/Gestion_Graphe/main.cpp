#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/Distance.h"
#include "include/Rang.h"

int main() {
	int NbNoeud = 7,NbArc = 18;
	std::vector<std::vector<int>> M{ {0,1,1,0,1,0,0},
									 {0,0,1,0,0,0,0},
									 {0,0,1,1,0,0,0},
									 {0,0,0,0,1,1,0},
									 {0,0,1,0,0,0,0},
									 {0,0,0,0,0,0,0},
									 {0,0,0,1,0,1,0} };
	Graphe::MatriceAdjacence testMat{ M,NbNoeud,NbArc };
	Graphe::Rang TestRang{ testMat };
	TestRang.affiche();
	getchar();
	return 0;
}