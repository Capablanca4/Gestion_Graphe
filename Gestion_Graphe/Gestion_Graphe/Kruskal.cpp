#include "Kruskal.h"
#include <iostream>

namespace Graphe {

	//On suppose que Mat est une MatriceAdjacenceValuee non oriente
	Kruskal::Kruskal(const MatriceAdjacenceValuee& Mat) : arbre{ Mat.nbSommets() } {
		arbreArrete* rangementArrete{ nullptr };
		///initialisation du rangement des arretes triées
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = i; j < Mat.nbSommets(); j++) {
				if (Mat.valeurMatrice(i, j) != INT_MAX) {
					insererArrete(rangementArrete, arrete{ i,j,Mat.valeurMatrice(i, j) });
				}
			}
		}
		///Initialisation de cfc et de pilch
		std::vector<int> pilch;
		pilch.resize(Mat.nbSommets()+1);
		std::vector<int> cfc;
		cfc.resize(Mat.nbSommets()+1);
		std::vector<int> prem;
		prem.resize(Mat.nbSommets()+1);
		for (int i = 1; i <= Mat.nbSommets(); i++) {
			pilch[i] = 0;
			cfc[i] = i;
			prem[i] = i;
		}
		///Initialisation de l'arbre recouvrant minimal
		if (rangementArrete != nullptr) parcourirArbre(rangementArrete, arbre,pilch,cfc,prem);
	}

	std::vector<int> Kruskal::sommet(int i)const {
		return arbre.sommet(i);
	}

	int Kruskal::valeurMatrice(int i, int j)const {
		return arbre.valeurMatrice(i, j);
	}

	void Kruskal::affiche()const {
		arbre.affiche();
	}

	void Kruskal::insererArrete(arbreArrete*& arbre, arrete inserer) {
		if (arbre == nullptr) {
			arbre = new arbreArrete{ inserer,nullptr,nullptr };
		}
		else {
			if (arbre->arc.poids > inserer.poids) {
				insererArrete(arbre->filsGauche, inserer);
			}
			else {
				insererArrete(arbre->filsDroit, inserer);
			}
		}
	}

	void Kruskal::parcourirArbre(arbreArrete* abr, MatriceAdjacenceValuee& arbre, std::vector<int>& pilch, std::vector<int> cfc, std::vector<int> prem) {
		if (abr->filsGauche != nullptr) parcourirArbre(abr->filsGauche, arbre,pilch,cfc,prem);
		if (cfc[abr->arc.sommetDep+1] != cfc[abr->arc.sommetArr+1]) {
			arbre.ajouterArc(abr->arc.sommetDep, abr->arc.sommetArr, abr->arc.poids);
			arbre.ajouterArc(abr->arc.sommetArr, abr->arc.sommetDep, abr->arc.poids);
			fusion(abr->arc, pilch, cfc, prem);
		}
		if (abr->filsDroit != nullptr) parcourirArbre(abr->filsDroit, arbre, pilch, cfc, prem);
	}

	void Kruskal::fusion(const arrete& abr, std::vector<int>& pilch, std::vector<int>& cfc, std::vector<int>& prem) {
		int premierElt = prem[abr.sommetArr + 1];
		while (pilch[premierElt] != 0) {
			cfc[pilch[premierElt]] = cfc[abr.sommetDep + 1];
			prem[pilch[premierElt]] = prem[abr.sommetDep + 1];
			premierElt = pilch[premierElt];
		}
		int finPilch = abr.sommetDep + 1;
		while (pilch[finPilch] != 0)finPilch = pilch[finPilch];
		pilch[finPilch] = prem[abr.sommetArr + 1];
		cfc[abr.sommetArr + 1] = cfc[abr.sommetDep + 1];
		prem[abr.sommetArr + 1] = prem[abr.sommetDep + 1];
	}

	Kruskal::~Kruskal()
	{
	}

}