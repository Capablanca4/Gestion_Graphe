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

	MatriceAdjacenceValuee::MatriceAdjacenceValuee():
		MatriceAdjacence(),
		d_MatriceAvecValeur{} {}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets) :
		MatriceAdjacence(nbSommets),
		d_MatriceAvecValeur{} {
		dimensionnerAInfini();
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(const std::string & fichier) :
		MatriceAdjacence() {
		std::ifstream is(fichier + ".txt");
		MatriceAdjacenceValuee::recupererMatrice(is);
		dimensionnerA0();
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				if (d_MatriceAvecValeur[i][j] != INFINI) {
					setArc(i, j, 1);
				}
			}
		}
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(const std::vector<std::vector<int>>& Matrice,int nbSommets, int nbArcs) :
		MatriceAdjacence(nbSommets),
		d_MatriceAvecValeur{ Matrice } {
		for (int i = 0; i < nbSommets; i++) {
			for (int j = 0; j < nbSommets; j++) {
				if (d_MatriceAvecValeur[i][j] != INFINI&&i!=j) {
					MatriceAdjacence::setArc(i, j, 1);
				}
			}
		}
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(alea aleatoire, int valeurmin, int valeurmax) :
		MatriceAdjacence(aleatoire) {
		dimensionnerAInfini();
		for (int i = 0; i < this->nbSommets(); i++) {
			for (int j = 0; j < this->nbSommets(); j++) {
				if (MatriceAdjacence::valeurMatrice(i,j)==1) {
					d_MatriceAvecValeur[i][j] = alea(valeurmin, valeurmax).val_alea();
				}
			}
		}
	}

	bool MatriceAdjacenceValuee::sansValeurNegative() const {
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

	const std::vector<int> MatriceAdjacenceValuee::sommet(int Sommet) const {
		if(Sommet<nbSommets()){
			return d_MatriceAvecValeur[Sommet];
		}
	}

	const int MatriceAdjacenceValuee::valeurMatrice(int i, int j)const {
		return d_MatriceAvecValeur[i][j];
	}

	void MatriceAdjacenceValuee::ajouteSommet() {
		std::vector<int> newLigne{ INFINI };
		for (int i = 0; i < nbSommets(); i++) {
			d_MatriceAvecValeur[i].push_back(INFINI);
			newLigne.push_back(INFINI);
		}
		d_MatriceAvecValeur.push_back(newLigne);
		MatriceAdjacence::ajouteSommet();
	}

	void MatriceAdjacenceValuee::supprimeSommet(int sommet) {
		if (sommet < nbSommets()) {
			for (int i = sommet; i < nbSommets() - 1; i++) {
				d_MatriceAvecValeur[i] = d_MatriceAvecValeur[i + 1];
				for (int j = sommet; j < nbSommets() - 1; j++) {
					d_MatriceAvecValeur[i][j] = d_MatriceAvecValeur[i][j + 1];
				}
				d_MatriceAvecValeur[i].pop_back();
			}
			d_MatriceAvecValeur[nbSommets()-1].pop_back();
			MatriceAdjacence::supprimeSommet(sommet);
		}
	}
	
	void MatriceAdjacenceValuee::ajouterArc(int sommetDep, int sommetArriver,int valeur) {
		setArc(sommetDep, sommetArriver, valeur);
	}

	void MatriceAdjacenceValuee::supprimerArc(int sommetDep, int sommetArriver) {
		setArc(sommetDep, sommetArriver, INFINI);
	}

	void MatriceAdjacenceValuee::setMatrice(const std::vector<std::vector<int>>& matrice) {
		std::vector<std::vector<int>> newMatrice{};
		d_MatriceAvecValeur = matrice;
		for (int i = 0; i < matrice.size(); i++) {
			newMatrice.push_back({});
			for (int j = 0; j < matrice.size(); j++) {
				if (matrice[i][j] == INFINI) newMatrice[i].push_back(0);
				else newMatrice[i].push_back(1);
			}	
		}
		MatriceAdjacence::setMatrice(newMatrice);
	}

	void MatriceAdjacenceValuee::inverse() {
		MatriceAdjacence::inverse();
		std::vector<std::vector<int>> M{};
		for (int i = 0; i < nbSommets(); i++) {
			M.push_back(std::vector<int>{});
			for (int j = 0; j < nbSommets(); j++) {
				M[i].push_back(d_MatriceAvecValeur[j][i]);
			}
		}
		d_MatriceAvecValeur = M;
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

	void MatriceAdjacenceValuee::enregistrerMatrice(std::ofstream& os) const {
		MatriceAdjacence::enregistrerMatrice(os);
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				os << d_MatriceAvecValeur[i][j] << " ";
			}
			os << std::endl;
		}
	}

	void MatriceAdjacenceValuee::recupererMatrice(std::ifstream& is) {
		MatriceAdjacence::recupererMatrice(is);
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
	
	bool MatriceAdjacenceValuee::estUnArc(int sommetDep, int sommetArriver) const {
		return d_MatriceAvecValeur[sommetDep][sommetArriver] != INFINI;
	}

	void MatriceAdjacenceValuee::setArc(int sommetDep, int sommetArriver, int valeur) {
		if (valeur == INFINI) MatriceAdjacence::supprimerArc(sommetDep, sommetArriver);
		else MatriceAdjacence::ajouterArc(sommetDep, sommetArriver);
		d_MatriceAvecValeur[sommetDep][sommetArriver] = valeur;
	}
}