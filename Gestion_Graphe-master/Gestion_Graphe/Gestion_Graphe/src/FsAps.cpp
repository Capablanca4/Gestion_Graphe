#include "../../Gestion_Graphe/include/FsAps.h"
#include"../../Gestion_Graphe/include/MatriceAdjacence.h"


#include <iostream>
namespace Graphe{

FsAps::FsAps(int nbSommets):
    d_tailleAdressePremierSuccesseur{nbSommets},
    d_tailleFileSuivant{nbSommets},
    d_FileSuivant{},
    d_AdressePremierSuccesseur{}
{
    for(int i=0;i<nbSommets;i++){
        d_FileSuivant.push_back(0);
        d_AdressePremierSuccesseur.push_back(i);
    }
}

FsAps::FsAps(int nbSommets,const std::vector<int>& FileSuivant):
    d_tailleAdressePremierSuccesseur{nbSommets},
    d_tailleFileSuivant{0},
    d_FileSuivant{FileSuivant},
    d_AdressePremierSuccesseur{}
{
    determiner_AdressePremierSuccesseur();
}

FsAps::FsAps(int nbSommets, const std::vector<int>& FileSuivant, int nbArc, const std::vector<int>& AdressePremierSuccesseur):
	d_tailleAdressePremierSuccesseur{ nbSommets },
	d_tailleFileSuivant{ nbArc },
	d_FileSuivant{ FileSuivant },
	d_AdressePremierSuccesseur{ AdressePremierSuccesseur } {}

FsAps::FsAps(MatriceAdjacence adj) :
	d_tailleFileSuivant{ adj.nbArc() },
	d_tailleAdressePremierSuccesseur{ adj.nbSommets() },
	d_FileSuivant{},
	d_AdressePremierSuccesseur{}
{
	int k = 0;
	for (int i = 0; i < d_tailleAdressePremierSuccesseur; i++) {
		d_AdressePremierSuccesseur.push_back(k);
		for (int j = 0; j < d_tailleAdressePremierSuccesseur; j++) {
			if (adj.Sommet(i)[j] != 0) {
				d_FileSuivant.push_back(j+1);
				k++;
			}
		}
		d_FileSuivant.push_back(0);
		k++;
	}
}

FsAps::~FsAps(){
while(d_FileSuivant.size()!=0) d_FileSuivant.pop_back();
while(d_AdressePremierSuccesseur.size()!=0) d_AdressePremierSuccesseur.pop_back();
}

void FsAps::determiner_AdressePremierSuccesseur(){
   d_AdressePremierSuccesseur.push_back(0);
   d_tailleFileSuivant=d_FileSuivant.size();
   for(unsigned int i=1;i<d_FileSuivant.size()-1;i++){
       if(d_FileSuivant[i]==0) {
           d_AdressePremierSuccesseur.push_back(i+1);
       }
    }
}

const int FsAps::nbSommets() const {
    return d_tailleAdressePremierSuccesseur;
}

const int FsAps::NbArc() const {
    return d_tailleFileSuivant;
}

const int FsAps::FileSuivant(int i) const{
    return d_FileSuivant[i];
}

const int FsAps::AdressePremierSuccesseur(int i)const{
    return d_AdressePremierSuccesseur[i];
}

void FsAps::AjouteArc(int noeudDep, int noeudArr) {
	if(noeudArr-1<d_tailleFileSuivant){
		int emplacementElt = d_AdressePremierSuccesseur[noeudDep-1];
		while (d_FileSuivant[emplacementElt] < noeudArr&&d_FileSuivant[emplacementElt] != 0) {
			emplacementElt++;
		}
		if (d_FileSuivant[emplacementElt] != noeudArr) {
			d_FileSuivant.push_back(noeudArr);
			for (int i = d_tailleAdressePremierSuccesseur; i > emplacementElt;i--) {
				d_FileSuivant[i] = d_FileSuivant[i - 1];
			}
			d_FileSuivant[emplacementElt] = noeudArr;
			d_tailleFileSuivant++;
		}
	}
	else {
		printf("Vous donnez un noeud d'arrivee trop grand !");
	}
}

void FsAps::AjouteNoeud() {
	d_FileSuivant.push_back(0);
	d_AdressePremierSuccesseur.push_back(d_tailleFileSuivant);
	d_tailleFileSuivant++;
	d_tailleAdressePremierSuccesseur++;
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
		else  mat[d_FileSuivant[indice]-1].push_back(indicemat);
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

void FsAps::afficheFileSuivant(){
	std::cout << "FileSuivant : ";
	for (int i =0; i < d_tailleFileSuivant; i++) {
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

}