#include "Djikstra.h"
#include "limits.h"
#include <iostream>

namespace Graphe {
	Djikstra::Djikstra(const FsAps& graph, const std::vector<std::vector<int>>& Poids, int sommet) :
		d_distance{}, d_predecesseur{}{
		//Initialisation des différents paramètres
		int n = graph.nbSommets();
		d_distance.resize(n + 1);
		d_distance[0] = n;
		d_predecesseur.resize(n + 1);
		d_predecesseur[0] = n;
		std::vector<bool> sommetTraite;
		sommetTraite.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			d_distance[i] = Poids[sommet][i-1];
			if (d_distance[i] != INT_MAX) d_predecesseur[i] = sommet+1;
			else d_predecesseur[i] = -1;
			sommetTraite[i] = false;
		}
		d_predecesseur[sommet+1] = 0;
		d_distance[sommet+1] = 0;
		sommetTraite[sommet+1] = true;
		int cpt = n;
		//calcul du minimum dans D pour les sommet non traités dans x
		while (--cpt > 0) {
			int min = INT_MAX, j;
			for (int i = 1; i <= n; i++) {
				if (!sommetTraite[i]) {
					if (d_distance[i] < min) {
						min = d_distance[i];
						j = i;
					}
				}
			}
			if (min == INT_MAX) {
				break;
			}
			sommetTraite[j] = true;
			int h;
			for (int k = graph.adressePremierSuccesseur(j - 1); (h = graph.fileSuivant(k)) != 0; k++) {
				if (!sommetTraite[h]) {
					if(Poids[j-1][h - 1]!= INT_MAX){
						int v = d_distance[j] + Poids[j-1][h-1];
						if (v < d_distance[h]) {
							d_distance[h] = v;
							d_predecesseur[h] = j;
						}
					}
				}
			}
		}
	}

	Djikstra::Djikstra(const MatriceAdjacenceValuee & M, int sommet) :
		d_distance{}, d_predecesseur{}{
		int n = M.nbSommets();
		d_distance.resize(n+1);
		d_distance[0] = n;
		d_predecesseur.resize(n+1);
		d_predecesseur[0] = n;
		std::vector<bool> sommetTraite;
		sommetTraite.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			d_distance[i] = M.valeurMatrice(sommet,i - 1);
			if (d_distance[i] != INT_MAX) d_predecesseur[i] = sommet + 1;
			else d_predecesseur[i] = -1;
			sommetTraite[i] = false;
		}
		d_predecesseur[sommet + 1] = 0;
		d_distance[sommet + 1] = 0;
		sommetTraite[sommet + 1] = true;
		int cpt = n;
		//calcul du minimum dans D pour les sommet non traités dans x
		while (--cpt > 0) {
			int min = INT_MAX, j;
			for (int i = 1; i <= n; i++) {
				if (!sommetTraite[i]) {
					if (d_distance[i] < min) {
						min = d_distance[i];
						j = i;
					}
				}
			}
			if (min == INT_MAX) {
				break;
			}
			sommetTraite[j] = true;
			for (int i = 0; i < n; i++) {
				if (!sommetTraite[i+1]) {
					if( M.valeurMatrice(j-1,i)!= INT_MAX) {
						int v = d_distance[j] + M.valeurMatrice(j - 1, i);
						if (v < d_distance[i+1]) {
							d_distance[i+1] = v;
							d_predecesseur[i+1] = j;
						}
					}
				}
			}
		}
	}

	int Djikstra::distance(int i) const {
		return d_distance[i];
	}

	int Djikstra::predecesseur(int i) const {
		return d_predecesseur[i];
	}

	void Djikstra::affiche() const {
		for (int i = 0; i <= d_distance[0]; i++) {
			std::cout << d_distance[i]<<" ";
		}
		std::cout <<  std::endl;
		for (int i = 0; i <= d_distance[0]; i++) {
			std::cout << d_predecesseur[i] << " ";
		}
		std::cout << std::endl;
	}
}