#include "../include/MatriceAdjacence.h"
#include "../include/FsAps.h"
#include "../include/MatriceAdjacenceValuee.h"
#include"../include/alea.h"
#include <iostream>
#include <vector>
#include<string>
#include<fstream>

const int INFINI = INT_MAX;

namespace Graphe {

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets) :
		MatriceAdjacence(nbSommets),
		d_MatriceAvecValeur{} {
		dimensionnerAInfini();
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(const std::string & fichier) :
		MatriceAdjacence() {
		std::ifstream is(fichier + ".txt");
		recupererMatriceAdjacenceValuee(is);
		dimensionnerA0();
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				if (d_MatriceAvecValeur[i][j] != INFINI) {
					setValeurMatrice(i, j, 1);
				}
			}
		}
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets, int nbArcs, std::vector<std::vector<int>> Matrice) :
		MatriceAdjacence(nbSommets),
		d_MatriceAvecValeur{ Matrice } {
		for (int i = 0; i < nbSommets; i++) {
			for (int j = 0; j < nbSommets; j++) {
				if (d_MatriceAvecValeur[i][j] != INFINI) {
					setValeurMatrice(i, j, 1);
				}
			}
		}
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(alea aleatoire, int bornesup, int borneinf) :
		MatriceAdjacence(aleatoire) {
		dimensionnerAInfini();
		dimensionnerA0();
		for (int i = 0; i < this->nbSommets(); i++) {
			for (int j = 0; j < this->nbSommets(); j++) {
				if (rand() % 2) {
					d_MatriceAvecValeur[i][j] = alea(borneinf, bornesup).val_alea();
					setValeurMatrice(i, j, 1);
				}
			}
		}
	}

	bool MatriceAdjacenceValuee::SansValeurNegative() const {
		bool test = true;
		int i = 0, j = 0;
		while (i < nbSommets() && test == true) {
			while (j < nbSommets() && test == true) {
				if (d_MatriceAvecValeur[i][j] < 0) {
					test = false;
				}
				j++;
			}
			i++;
			j = 0;
		}
		return test;
	}

	void MatriceAdjacenceValuee::SetArc(int sommetDep, int sommetArriver, int valeur) {
		MatriceAdjacence::AjouteArc(sommetDep, sommetArriver);
		d_MatriceAvecValeur[sommetDep][sommetArriver] = valeur;
	}

	bool MatriceAdjacenceValuee::EstUnArc(int sommetDep, int sommetArriver) {
		return d_MatriceAvecValeur[sommetDep][sommetArriver] != INFINI;
	}

	void MatriceAdjacenceValuee::affiche() const {
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				if (d_MatriceAvecValeur[i][j] == INFINI) std::cout << "I";
				else std::cout << d_MatriceAvecValeur[i][j];
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	void MatriceAdjacenceValuee::enregistrerMatriceAdjacenceValuee(std::ofstream& os) {
		enregistrerMatriceAdjacence(os);
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				os << d_MatriceAvecValeur[i][j] << " ";
			}
			os << std::endl;
		}
	}

	void MatriceAdjacenceValuee::recupererMatriceAdjacenceValuee(std::ifstream& is) {
		recupererMatriceAdjacence(is);
		dimensionnerAInfini();
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				is >> d_MatriceAvecValeur[i][j];
			}
		}
	}

	void MatriceAdjacenceValuee::dimensionnerAInfini() {
		d_MatriceAvecValeur.resize(nbSommets());
		for (int i = 0; i < nbSommets(); i++) {
			d_MatriceAvecValeur[i].resize(nbSommets(), INFINI);
		}
	}
}