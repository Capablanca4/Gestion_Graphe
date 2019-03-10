#include "../include/MatriceAdjacence.h"
#include "../include/FsAps.h"
#include "../include/MatriceAdjacenceValuee.h"
#include <iostream>
#include <vector>
#include<string>
#include<fstream>

int const INFINI = INT_MAX;
namespace Graphe {
	

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets) : MatriceAdjacence(nbSommets) {
		std::vector<std::vector<int>> matrice;
		matrice.resize(nbSommets);
		for (int i = 0; i < nbSommets; i++) {
			matrice[i].resize(nbSommets, INFINI);
		}
		d_MatriceAvecValeur = matrice;
	}
	MatriceAdjacenceValuee::MatriceAdjacenceValuee(const std::string & fichier) : MatriceAdjacence() {
		recupererMatriceAdjacenceValuee(fichier);
		dimensionnerA0();
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				if (d_MatriceAvecValeur[i][j] != INFINI) {
					setValeurMatrice(i, j, 1);
				}
			}
		}
	}
	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets,int nbArcs,std::vector<std::vector<int>> Matrice) : MatriceAdjacence(Matrice,nbSommets,nbArcs) {
		std::vector<std::vector<int>> matrice;
		matrice.resize(nbSommets);
		for (int i = 0; i < nbSommets; i++) {
			matrice[i].resize(nbSommets, INFINI);
		}
		for (int i = 0; i < nbSommets; i++) {
			for (int j = 0; j < nbSommets; j++) {
				if (ValeurMatrice(i, j) == 1) {
					d_MatriceAvecValeur[i][j] = 0;
				}
			}
		}
		d_MatriceAvecValeur = matrice;
	}

	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets, int nbArcs, std::vector<std::vector<int>> Matrice, bool valuer) : MatriceAdjacence(nbSommets),d_MatriceAvecValeur{Matrice}
	{
		for (int i = 0; i < nbSommets; i++) {
			for (int j = 0; j < nbSommets; j++) {
				if (d_MatriceAvecValeur[i][j] != INFINI) {
					setValeurMatrice(i, j, 1);
				}
			}
		}
		this->setNbArcs(nbArcs);
	}

	 
	bool MatriceAdjacenceValuee::SansValeurNegative() const
	{
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
	void MatriceAdjacenceValuee::AjouteArc(int sommetDep, int sommetArriver, int valeur)
	{
		if (!EstUnArc(sommetDep, sommetArriver)) {
			d_MatriceAvecValeur[sommetDep][sommetArriver]=valeur;
			MatriceAdjacence::AjouteArc(sommetDep, sommetArriver);
			}
		else {
			std::cout << "Cet arc existe déja";
		}

	}
	void MatriceAdjacenceValuee::ModifierArc(int sommetDep, int sommetArriver, int valeur)
	{
		if (EstUnArc(sommetDep, sommetArriver)) {
			d_MatriceAvecValeur[sommetDep][sommetArriver] = valeur;
		}
		else {
			std::cout << "Cet arc n'existe pas";
		}
	}
	bool MatriceAdjacenceValuee::EstUnArc(int sommetDep, int sommetArriver)
	{
		return d_MatriceAvecValeur[sommetDep][sommetArriver] != INFINI;
	}
	void MatriceAdjacenceValuee::affiche() const
	{
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				if (d_MatriceAvecValeur[i][j] == INFINI) {
					std::cout << "I";
				}
				else {
					std::cout << d_MatriceAvecValeur[i][j];
				}
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}

	void MatriceAdjacenceValuee::enregistrerMatriceAdjacenceValuee(const std::string& fichier)
	{
		std::ofstream os(fichier + ".txt");

		os << nbSommets();
		os << std::endl;
		os << nbArc();
		os << std::endl;
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				os << d_MatriceAvecValeur[i][j] << " ";
			}
			os << std::endl;
		}
	}

	void MatriceAdjacenceValuee::recupererMatriceAdjacenceValuee(const std::string& fichier)
	{
		std::ifstream is(fichier + ".txt");
		int valeur;
		is >> valeur;
		setNbSommets(valeur);
		is >> valeur;
		setNbArcs(valeur);
		dimensionnerAInfini();
		for (int i = 0; i < nbSommets(); i++) {
			for (int j = 0; j < nbSommets(); j++) {
				is>> d_MatriceAvecValeur[i][j];
			}
			
		}
	}

	void MatriceAdjacenceValuee::dimensionnerAInfini()
	{
		d_MatriceAvecValeur.resize(nbSommets());
		
		for (int i = 0; i < nbSommets(); i++) {
			d_MatriceAvecValeur[i].resize(nbSommets(), INFINI);
		}
	}
}