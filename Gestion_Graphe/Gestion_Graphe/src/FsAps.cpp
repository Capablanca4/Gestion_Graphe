#include "../../Gestion_Graphe/include/FsAps.h"
#include"../../Gestion_Graphe/include/MatriceAdjacence.h"
#include <fstream>
#include <iostream>

namespace Graphe {

	FsAps::FsAps() :
		d_tailleAdressePremierSuccesseur{ 0 },
		d_tailleFileSuivant{ 0},
		d_FileSuivant{},
		d_AdressePremierSuccesseur{} {}

	FsAps::FsAps(int nbSommets) :
		d_tailleAdressePremierSuccesseur{ nbSommets },
		d_tailleFileSuivant{ nbSommets },
		d_FileSuivant{},
		d_AdressePremierSuccesseur{}
	{
		for (int i = 0; i < nbSommets; i++) {
			d_FileSuivant.push_back(0);
			d_AdressePremierSuccesseur.push_back(i);
		}
	}

	FsAps::FsAps(alea aleatoire) :
		d_tailleAdressePremierSuccesseur{ aleatoire.val_alea() }
	{
		int nbelement = 0;
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			d_AdressePremierSuccesseur.push_back(nbelement);
			for (int j = 1; j < d_tailleAdressePremierSuccesseur; j++) {
				if (rand() % 2) {
					d_FileSuivant.push_back(j);
					nbelement++;
				}
			}
			d_FileSuivant.push_back(0);
			nbelement++;
		}
		d_tailleFileSuivant = nbelement;
	}

	FsAps::FsAps(int nbSommets, const std::vector<int>& FileSuivant) :
		d_tailleAdressePremierSuccesseur{ nbSommets },
		d_tailleFileSuivant{ 0 },
		d_FileSuivant{ FileSuivant },
		d_AdressePremierSuccesseur{}
	{
		determiner_AdressePremierSuccesseur();
	}

	FsAps::FsAps(int nbSommets, const std::vector<int>& FileSuivant, int nbArc, const std::vector<int>& AdressePremierSuccesseur) :
		d_tailleAdressePremierSuccesseur{ nbSommets },
		d_tailleFileSuivant{ nbArc+nbSommets },
		d_FileSuivant{ FileSuivant },
		d_AdressePremierSuccesseur{ AdressePremierSuccesseur } {}

	FsAps::FsAps(const std::string& fichier)
	{
		std::ifstream is(fichier + ".txt");
		recupererFsAps(is);
	}

	FsAps::FsAps(const MatriceAdjacence& adj) :
		d_tailleFileSuivant{ adj.nbArc() + adj.nbSommets() },
		d_tailleAdressePremierSuccesseur{ adj.nbSommets() },
		d_FileSuivant{},
		d_AdressePremierSuccesseur{}
	{
		int k = 0;
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			d_AdressePremierSuccesseur.push_back(k);
			for (int j = 0; j < d_tailleAdressePremierSuccesseur; j++) {
				if (adj.valeurMatrice(i, j) == 1) {
					d_FileSuivant.push_back(j + 1);
					k++;
				}
			}
			d_FileSuivant.push_back(0);
			k++;
		}

	}

	FsAps::~FsAps() {
		while (d_FileSuivant.size() != 0) d_FileSuivant.pop_back();
		while (d_AdressePremierSuccesseur.size() != 0) d_AdressePremierSuccesseur.pop_back();
	}

	void FsAps::determiner_AdressePremierSuccesseur() {
		d_AdressePremierSuccesseur.push_back(0);
		d_tailleFileSuivant = d_FileSuivant.size();
		for (unsigned int i = 1; i < d_FileSuivant.size() - 1; i++) {
			if (d_FileSuivant[i] == 0) {
				d_AdressePremierSuccesseur.push_back(i + 1);
			}
		}
	}

	const int FsAps::nbSommets() const {
		return d_tailleAdressePremierSuccesseur;
	}

	const int FsAps::nbArc() const {
		return d_tailleFileSuivant-d_tailleAdressePremierSuccesseur;
	}

	const int FsAps::fileSuivant(int i) const {
		return d_FileSuivant[i];
	}

	const int FsAps::adressePremierSuccesseur(int i)const {
		return d_AdressePremierSuccesseur[i];
	}

	void FsAps::ajouteArc(int noeudDep, int noeudArr) {
		if (noeudArr < d_tailleAdressePremierSuccesseur && noeudDep < d_tailleAdressePremierSuccesseur) {
			int emplacementElt = d_AdressePremierSuccesseur[noeudDep];
			while (d_FileSuivant[emplacementElt] < noeudArr+1 && d_FileSuivant[emplacementElt] != 0) emplacementElt++;
			if (d_FileSuivant[emplacementElt] != noeudArr+1) {
				d_tailleFileSuivant++;
				d_FileSuivant.push_back(0);
				for (int i = d_tailleFileSuivant - 1; i > emplacementElt; i--) d_FileSuivant[i] = d_FileSuivant[i-1];
				for (int i = noeudDep + 1; i < d_tailleAdressePremierSuccesseur; i++) d_AdressePremierSuccesseur[i]++;
				d_FileSuivant[emplacementElt] = noeudArr + 1;
			}
		}
		else printf("Vous donnez un noeud d'arrivee ou un noeud de depart trop grand !");
	}


	void FsAps::supprimerArc(int noeudDep, int noeudArr) {
		if (noeudArr < d_tailleAdressePremierSuccesseur && noeudDep < d_tailleAdressePremierSuccesseur) {
			int emplacementElt = d_AdressePremierSuccesseur[noeudDep];
			while (d_FileSuivant[emplacementElt] != 0 && d_FileSuivant[emplacementElt] != noeudArr) emplacementElt++;
			if (d_FileSuivant[emplacementElt] == noeudArr) {
				for (int i = emplacementElt; i < d_tailleFileSuivant - 1; i++) d_FileSuivant[i] = d_FileSuivant[i + 1];
				d_FileSuivant.pop_back();
				d_tailleFileSuivant--;
				for (int i = noeudDep+1; i < d_tailleAdressePremierSuccesseur;i++) d_AdressePremierSuccesseur[i]--;
			}
		}
		else printf("Vous donnez un noeud d'arrivee ou un noeud de depart trop grand !");
	}

	void FsAps::ajouteSommet() {
		d_FileSuivant.push_back(0);
		d_AdressePremierSuccesseur.push_back(d_tailleFileSuivant);
		d_tailleFileSuivant++;
		d_tailleAdressePremierSuccesseur++;
	}
	
	void FsAps::supprimeSommet(int noeud) {
		int adresse = d_AdressePremierSuccesseur[noeud - 1];
		while (d_FileSuivant[adresse] != 0) {
			for (int i = adresse; i < d_tailleFileSuivant - 1; i++) d_FileSuivant[i] = d_FileSuivant[i + 1];
			for (int i = noeud; i < d_tailleAdressePremierSuccesseur; i++) d_AdressePremierSuccesseur[i]--;
			d_FileSuivant.pop_back();
			d_tailleFileSuivant--;
		}
		// derniere itération pour supprimer le dernier 0
		for (int i = adresse; i < d_tailleFileSuivant - 1; i++) d_FileSuivant[i] = d_FileSuivant[i + 1];
		for (int i = noeud; i < d_tailleAdressePremierSuccesseur; i++) d_AdressePremierSuccesseur[i]--;
		d_FileSuivant.pop_back();
		d_tailleFileSuivant--;

		for (int i = noeud - 1; i < d_tailleAdressePremierSuccesseur - 1; i++) d_AdressePremierSuccesseur[i] = d_AdressePremierSuccesseur[i + 1];
		d_AdressePremierSuccesseur.pop_back();
		d_tailleAdressePremierSuccesseur--;
	}

	void FsAps::inverse()
	{
		std::vector<std::vector<int>> mat{ };
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			mat.push_back(std::vector<int>{});
		}
		int indicemat = 1, indice = 0;
		while (indice < d_tailleFileSuivant) {
			if (d_FileSuivant[indice] == 0)  indicemat++;
			else  mat[d_FileSuivant[indice] - 1].push_back(indicemat);
			indice++;
		}
		indice = 0;
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			mat[i].push_back(0);
			d_AdressePremierSuccesseur[i] = indice;
			for (int j = 0; j < mat[i].size(); j++) {
				d_FileSuivant[indice++] = mat[i][j];
			}
		}
	}

	void FsAps::afficheFileSuivant() {
		std::cout << "FileSuivant : ";
		for (int i = 0; i < d_tailleFileSuivant; i++) {
			std::cout << d_FileSuivant[i] << " ";
		}
	}

	void FsAps::afficheAdressePremierSuccesseur()
	{
		std::cout << "AdressePremierSuccesseur : ";
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			std::cout << d_AdressePremierSuccesseur[i] << " ";
		}
	}

	void FsAps::affiche()
	{
		afficheFileSuivant();
		std::cout << std::endl;
		afficheAdressePremierSuccesseur();
	}

	void FsAps::enregistrerFsAps(std::ofstream& os)
	{
		os << d_tailleFileSuivant;
		os << std::endl;
		os << d_tailleAdressePremierSuccesseur;
		os << std::endl;
		for (int i = 0; i < d_tailleFileSuivant; i++) {
			os << d_FileSuivant[i] << " ";
		}
		os << std::endl;
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			os << d_AdressePremierSuccesseur[i] << " ";
		}
	}
	
	void FsAps::recupererFsAps(std::ifstream& is)
	{
		is >> d_tailleFileSuivant;
		is >> d_tailleAdressePremierSuccesseur;
		d_FileSuivant.resize(d_tailleFileSuivant);
		for (int i = 0; i < d_tailleFileSuivant; i++) {
			is >> d_FileSuivant[i];
		}
		d_AdressePremierSuccesseur.resize(d_tailleAdressePremierSuccesseur);
		for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
			is >> d_AdressePremierSuccesseur[i];
		}
	}
}