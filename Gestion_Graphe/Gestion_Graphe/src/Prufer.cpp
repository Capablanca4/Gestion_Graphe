#include "../include/Prufer.h"
#include <iostream>

namespace Graphe {

	///On suppose que la Matrice d'adjacence contient au moins 2 sommets et est un arbre
	Prufer::Prufer(MatriceAdjacence& mat) :
		d_codage{} {
		int nbSommets = mat.nbSommets();
		d_codage.resize(nbSommets-1);
		d_codage[0] = nbSommets - 2;
		std::vector<int> nbArcParLigne{};
		nbArcParLigne.resize(nbSommets, 0);
		for (int i = 0; i < nbSommets; i++) {
			for (int j = 0; j < nbSommets; j++) {
				if (mat.valeurMatrice(i, j) == 1) nbArcParLigne[i]++;
			}
		}
		for (int k = 1; k < nbSommets-1; k++) {
			int i = 0, j = 0;
			while (nbArcParLigne[i] != 1)i++;
			for (; mat.valeurMatrice(i, j) != 1; j++);
			d_codage[k] = j+1;
			mat.supprimerArc(i, j);
			mat.supprimerArc(j, i);
			nbArcParLigne[i] = 0;
			nbArcParLigne[j]--;
		}
	}

	void Prufer::decodage() {
		std::vector<int> nbOc;
		int nbSommets = d_codage[0];
		nbOc.resize(nbSommets + 3,0);		
		std::vector<bool> I;
		I.resize(nbSommets + 3,true);
		for (int i = 1; i <= nbSommets ; i++) nbOc[d_codage[i]]++;
		for (int i = 1; i <= nbSommets; i++) {
			int sommet = d_codage[i];
			std::cout << "(" << sommet << ",";
			int t = 1;
			while (!I[t] || nbOc[t] != 0) t++;
			std::cout << t << ")" << std::endl;
			I[t] = false;
			nbOc[sommet]--;
		}
		int s = 1;
		while (!I[s])s++;
		std::cout << "(" << s << ",";
		s++;
		while (!I[s])s++;
		std::cout  << s << ")"<<std::endl;
	}

	int Prufer::sommet(int i)const {
		return d_codage[i];
	}

	void Prufer::affiche()const {
		for (int i = 0; i < d_codage.size(); i++) {
			std::cout << d_codage[i] << ";";
		}
		std::cout << std::endl;
	}
}