#include "../include/MatriceAdjacence.h"
#include "../include/FsAps.h"
#include "../include/MatriceAdjacenceValuee.h"
#include <iostream>
#include <vector>;


namespace Graphe {
	const int INFINI = INT_MAX;

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets){
		std::vector<std::vector<int>> matrice;
		matrice.resize(nbSommets);
		for (int i = 0; i < nbSommets; i++) {
			matrice[i].resize(nbSommets, INFINI);
		}
		MatriceAdjacence M(matrice, nbSommets, 0);	
		M.affiche();
		//Probleme l'objet n'existe plus en dehors du constructeur , je vais surement devoir utiliser des setteurs
	}
}