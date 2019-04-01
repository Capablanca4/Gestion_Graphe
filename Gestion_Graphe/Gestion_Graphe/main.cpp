#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/alea.h"
#include <iostream>
#include <fstream>

bool compareFile(std::ifstream& fileRep, std::ifstream& fileAverifier) {
	///https://stackoverflow.com/questions/6163611/compare-two-files
	if (fileRep.fail() || fileAverifier.fail()) {
		return false; //file problem
	}
	if (fileRep.tellg() != fileAverifier.tellg()) {
		return false; //size mismatch
	}
	//seek back to beginning and use std::equal to compare contents
	fileRep.seekg(0, std::ifstream::beg);
	fileAverifier.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(fileRep.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(fileAverifier.rdbuf()));
}

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

	Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
	std::ofstream os("ReponseMatriceAdjacenceValuee2.txt");
	Mat.enregistrerMatrice(os);
	os.close();
	std::ifstream fileRep("ReponseMatriceAdjacenceValuee.txt");
	std::ifstream fileAverifier("ReponseMatriceAdjacenceValuee2.txt");
	std::cout << compareFile(fileRep, fileAverifier) << std::endl;
	getchar();
}