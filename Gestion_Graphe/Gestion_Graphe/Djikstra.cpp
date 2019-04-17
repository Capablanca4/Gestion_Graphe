#include "Djikstra.h"
#include "include/Distance.h"
#include "include/FsAps.h"
#include "include/MatriceAdjacenceValuee.h";
#include <iostream>
namespace Graphe {
	int const INFINI = INT_MAX;
	Djikstra::Djikstra(const MatriceAdjacenceValuee & M, Distance & D, std::vector<int>& predecesseur) {
		//Distance d(*this);
		FsAps fsETaps(M);
		fsETaps.affiche();
		int v, j, min, k;
		int n = fsETaps.nbSommets();
		std::vector<int>distance;
		distance.resize(n);
		predecesseur.resize(n);
		std::vector<bool> aFaire(n);
		std::vector<std::vector<int>> matriceDistance;
		for (int sommet = 0;sommet < n;sommet++) {
			for (int i = 0; i < n; i++) {
				distance[i] = M.valeurMatrice(sommet, i);

				if (distance[i] != INFINI) {
					predecesseur[i] = sommet;
				}
				else {
					predecesseur[i] = INFINI;
				}
				aFaire[i] = true;
			}
			for (int i = 0;i < distance.size();i++) {
				std::cout << distance[i] << " ";
			}
			std::cout << std::endl;
			aFaire[sommet] = false;
			predecesseur[0] = 0;
			distance[sommet] = 0;
			for (int cpt = 0; cpt < n; cpt++) {
				min = INFINI;
				j = 0;
				for (int i = 0; i < n; i++) {
					if (!aFaire[i] && distance[i] < min) {
						min = distance[i];
						j = i;
					}
				}
				if (min == INFINI) {
					aFaire[j] = false;
				}
				else
				{
					for (int l = fsETaps.adressePremierSuccesseur(j); (k = fsETaps.fileSuivant(l)) != 0; l++) {
						if (aFaire[k]) {
							v = distance[j] + M.valeurMatrice(j, k);
							if (v < distance[k]) {
								distance[k] = v;
								predecesseur[k] = j;
							}
						}
					}
				}
			}
			matriceDistance.push_back(distance);
		}
	}



	Djikstra::~Djikstra()
	{
	}

}