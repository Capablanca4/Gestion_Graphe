#include "../include/MatriceAdjacence.h"
#include "../include/FsAps.h"
#include"../include/alea.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <utility>

namespace Graphe {

	MatriceAdjacence::MatriceAdjacence() :
		d_matrice{},
		d_nbSommets{ 0 },
		d_nbArc{ 0 } {}

	MatriceAdjacence::MatriceAdjacence(alea aleatoire) :
		d_matrice{},
		d_nbSommets{ aleatoire.val_alea() },
		d_nbArc{ 0 }
	{
		dimensionnerA0();
		for (int i = 0; i < d_nbSommets; i++) {
			for (int j = 0; j < d_nbSommets; j++) {
				if (rand() % 2) {
					d_matrice[i][j] = 1;
					d_nbArc++;
				}
			}
		}
	}

	MatriceAdjacence::MatriceAdjacence(int nbSommets) :
		d_matrice{},
		d_nbSommets{ nbSommets },
		d_nbArc{ 0 }
	{
		dimensionnerA0();
	}

	MatriceAdjacence::MatriceAdjacence(std::vector<std::vector<int>> matrice, int nbSommets, int nbArc) :
		d_matrice{ matrice },
		d_nbSommets{ nbSommets },
		d_nbArc{ nbArc } {}

	MatriceAdjacence::MatriceAdjacence(FsAps graph) :
		d_nbSommets{ graph.nbSommets() },
		d_nbArc{ graph.nbArc() },
		d_matrice{}
	{
		for (int i = 0; i < d_nbSommets; i++) {
			std::vector<int> B;
			for (int j = 0; j < d_nbSommets; j++)  B.push_back(0);
			int j = graph.adressePremierSuccesseur(i);
			while (graph.fileSuivant(j) != 0) {
				B[graph.fileSuivant(j++) - 1] = 1;
			}
			d_matrice.push_back(B);
		}
	}

	MatriceAdjacence::MatriceAdjacence(std::string fichier)
	{
		std::ifstream is(fichier + ".txt");
		MatriceAdjacence::recupererMatrice(is);
	}

	MatriceAdjacence::~MatriceAdjacence() {
		for (unsigned int i = 0; i < d_matrice.size(); i++) {
			while (d_matrice[i].size() != 0) {
				d_matrice[i].pop_back();
			}
		}
	}

	const int MatriceAdjacence::nbSommets() const {
		return d_nbSommets;
	}

	const int MatriceAdjacence::nbArc() const {
		return d_nbArc;
	}

	const std::vector<int> MatriceAdjacence::sommet(int Sommet) const {
		return d_matrice[Sommet];
	}

	const int MatriceAdjacence::valeurMatrice(int i, int j)const {
		return d_matrice[i][j];
	}

	void MatriceAdjacence::setArc(int sommetDep, int sommetArr, int valeur) {
		if (valeur != d_matrice[sommetDep][sommetArr]) {
			if (valeur == 0) d_nbArc--;
			else d_nbArc++;
			d_matrice[sommetDep][sommetArr] = valeur;
		}
	}

	void MatriceAdjacence::supprimerArc(int sommetDep, int sommetArr) {
		MatriceAdjacence::setArc(sommetDep, sommetArr, 0);
	}

	void MatriceAdjacence::ajouterArc(int sommetDep, int sommetArr) {
		MatriceAdjacence::setArc(sommetDep, sommetArr, 1);
	}

	void MatriceAdjacence::ajouteSommet() {
		for (int i = 0; i < d_nbSommets; i++)  d_matrice[i].push_back(0);
		d_nbSommets++;
		std::vector<int> nouvelleligne = std::vector<int>{};
		for (int i = 0; i < d_nbSommets; i++)  nouvelleligne.push_back(0);
		d_matrice.push_back(nouvelleligne);
	}

	void MatriceAdjacence::supprimeSommet(int sommet) {
		if(sommet<d_nbSommets){
			for (int i = 0; i < d_nbSommets; i++) {
				if (d_matrice[sommet][i] == 1) d_nbArc--;
			}
			for (int i = 0; i < sommet; i++) {
				if (d_matrice[i][sommet] == 1) d_nbArc--;
				for (int j = sommet; j < d_nbSommets - 1; j++) {
					d_matrice[i][j] = d_matrice[i][j + 1];
				}
				d_matrice[i].pop_back();
			}
			for (int i = sommet; i < d_nbSommets-1; i++) {
				d_matrice[i] = d_matrice[i + 1];
				if (d_matrice[i][sommet] == 1) d_nbArc--;
				for (int j = sommet; j < d_nbSommets - 1; j++) {
					d_matrice[i][j] = d_matrice[i][j + 1];
				}
				d_matrice[i].pop_back();
			}
			d_matrice[d_nbSommets-1].pop_back();
			d_nbSommets--;
		}
	}

	void MatriceAdjacence::dimensionnerA0() {
		d_matrice.resize(d_nbSommets);
		for (int i = 0; i < d_nbSommets; i++) {
			d_matrice[i].resize(d_nbSommets, 0);
		}
	}

	void MatriceAdjacence::inverse() {
		std::vector<std::vector<int>> M{};
		for (int i = 0; i < d_nbSommets; i++) {
			M.push_back(std::vector<int>{});
			for (int j = 0; j < d_nbSommets; j++) {
				M[i].push_back(d_matrice[j][i]);
			}
		}
		d_matrice = M;
	}

	void MatriceAdjacence::affiche() const {
		for (int i = 0; i < d_nbSommets; i++) {
			for (int j = 0; j < d_nbSommets; j++) {
				std::cout << d_matrice[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void MatriceAdjacence::enregistrerMatrice(std::ofstream& os)const
	{
		os << d_nbSommets;
		os << std::endl;
		os << d_nbArc;
		os << std::endl;
		for (int i = 0; i < d_nbSommets; i++) {
			for (int j = 0; j < d_nbSommets; j++) {
				os << d_matrice[i][j] << " ";
			}
			os << std::endl;
		}
	}

	void MatriceAdjacence::recupererMatrice(std::ifstream& is)
	{
		is >> d_nbSommets;
		is >> d_nbArc;
		dimensionnerA0();
		for (int i = 0; i < d_nbSommets; i++) {
			for (int j = 0; j < d_nbSommets; j++) {
				is >> d_matrice[i][j];
			}
		}
	}

	MatriceAdjacence MatriceAdjacence::operator=(const MatriceAdjacence& M) {
		return MatriceAdjacence(M.d_matrice, M.d_nbSommets, M.d_nbArc);
	}

	MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2)
	{
		std::vector<std::vector<int>> matrice;
		int nbArc = 0;
		int nbSommets;
		std::cout << M.nbSommets() << std::endl;
		std::cout << M2.nbSommets() << std::endl;
		if (M.nbSommets() < M2.nbSommets()) {
			matrice.resize(M2.nbSommets());
			nbSommets = M2.nbSommets();
			for (int i = 0; i < M2.nbSommets(); i++) {
				matrice[i].resize(M2.nbSommets());
			}
			for (int i = 0; i < M.nbSommets(); i++) {
				for (int j = 0; j < M.nbSommets(); j++) {

					if (M.d_matrice[i][j] == 1 && M2.d_matrice[i][j] == 1) {
						matrice[i][j] = 1;
						nbArc++;

					}
					else if (M.d_matrice[i][j] == 1 || M2.d_matrice[i][j] == 1) {
						nbArc++;
						matrice[i][j] = M.d_matrice[i][j] + M2.d_matrice[i][j];
					}
					else {
						matrice[i][j] = 0;
					}
				}
				for (int j2 = M.nbSommets(); j2 < M2.nbSommets(); j2++) {
					if (M2.d_matrice[i][j2] == 1) {
						nbArc++;
					}

					matrice[i][j2] = M2.d_matrice[i][j2];
				}
			}

			for (int i = M.nbSommets(); i < M2.nbSommets(); i++) {
				for (int j = 0; j < M2.nbSommets(); j++) {
					if (M2.d_matrice[i][j] == 1) {
						nbArc++;
					}

					matrice[i][j] = M2.d_matrice[i][j];
				}
			}
		}
		else
		{
			matrice.resize(M.nbSommets());
			nbSommets = M.nbSommets();
			for (int i = 0; i < M.nbSommets(); i++) {
				matrice[i].resize(M.nbSommets());
			}
			for (int i = 0; i < M2.nbSommets(); i++) {
				for (int j = 0; j < M2.nbSommets(); j++) {
					if (M.d_matrice[i][j] == 1 && M2.d_matrice[i][j] == 1) {
						matrice[i][j] = 1;
						nbArc++;
					}
					else if (M.d_matrice[i][j] == 1 || M2.d_matrice[i][j] == 1) {
						nbArc++;
						matrice[i][j] = M.d_matrice[i][j] + M2.d_matrice[i][j];
					}
					else {
						matrice[i][j] = 0;
					}

				}
				for (int j2 = M2.nbSommets(); j2 < M.nbSommets(); j2++) {
					if (M.d_matrice[i][j2] == 1) {
						nbArc++;
					}
					matrice[i][j2] = M.d_matrice[i][j2];
				}
			}
			for (int i = M2.nbSommets(); i < M.nbSommets(); i++) {
				for (int j = 0; j < M.nbSommets(); j++) {
					if (M.d_matrice[i][j] == 1) {
						nbArc++;
					}
					matrice[i][j] = M.d_matrice[i][j];
				}
			}
		}
		return MatriceAdjacence(matrice, nbSommets, nbArc);
	}

	void MatriceAdjacence::setMatrice(const std::vector<std::vector<int>>& matrice) {
		d_matrice = matrice;
		d_nbSommets = matrice.size();
		d_nbArc = 0;
		for (int i = 0; i < d_nbSommets; i++) {
			for (int j = 0; j < d_nbSommets; j++) {
				if (d_matrice[i][j] == 1) {
					d_nbArc++;
				}
			}
		}
	}

	/*
	MatriceAdjacence operator-(const MatriceAdjacence & M, const MatriceAdjacence & M2)
	{
		int tailleMin = static_cast<int>(fmin(M.nbSommets(), M2.nbSommets()));
		std::vector<std::vector<int>> matrice(tailleMin);
		int nbArc = 0;
		for (int i = 0; i < tailleMin; i++) {
			matrice[i].resize(tailleMin);
		}
		for (int i = 0; i < tailleMin; i++) {
			for (int j = 0; j < tailleMin; j++) {
				if (M.d_matrice[i][j] == 0) {
					matrice[i][j] = 0;

				}
				else {
					if (M2.d_matrice[i][j] == 1) {
						matrice[i][j] = 0;
					}
					else {
						matrice[i][j] = 1;
						nbArc++;
					}
				}
			}
		}
		return MatriceAdjacence(matrice, tailleMin, nbArc);
	}*/

}
