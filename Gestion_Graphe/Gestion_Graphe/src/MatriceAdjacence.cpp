#include "../include/MatriceAdjacence.h"
#include "../include/FsAps.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <utility>
namespace Graphe{

MatriceAdjacence::MatriceAdjacence(std::vector<std::vector<int>> matrice,int nbSommets,int nbArc):
    d_matrice{matrice},
	d_nbSommets{ nbSommets },
    d_nbArc{nbArc} {}

MatriceAdjacence::MatriceAdjacence():
    d_matrice{},
	d_nbSommets{0},
    d_nbArc{0} {}

MatriceAdjacence::MatriceAdjacence(int nbSommets):
    d_matrice{},
	d_nbSommets{ nbSommets },
    d_nbArc{0}
{
	d_matrice.resize(nbSommets);
	for (int i = 0; i < nbSommets; i++) {
		d_matrice[i].resize(nbSommets, 0);
	}
}

MatriceAdjacence::MatriceAdjacence(FsAps graph):
	d_nbSommets{graph.nbSommets()},
	d_nbArc{graph.NbArc()},
	d_matrice{}
{
	d_matrice.resize(d_nbSommets);
	for (int i = 0; i < d_nbSommets; i++) {
		d_matrice[i].resize(d_nbSommets,0);
		int j = graph.AdressePremierSuccesseur(i);
		while (graph.FileSuivant(j) != 0) {
			d_matrice[i][graph.FileSuivant(j++)-1] = 1;
		}
		
	}
}

MatriceAdjacence::~MatriceAdjacence(){
    for(unsigned int i=0;i<d_matrice.size();i++){
        while(d_matrice[i].size()!=0){
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

const std::vector<int> MatriceAdjacence::Sommet(int noeud) const{
    return d_matrice[noeud];
}

void MatriceAdjacence::AjouteArc(int noeudDep,int noeudArr){
    if(!d_matrice[noeudDep][noeudArr]){
        d_matrice[noeudDep][noeudArr]=1;
        d_nbArc++;
    }
}

void MatriceAdjacence::AjouteSommet(){
    for(unsigned int i=0;i<d_matrice.size();i++)  d_matrice[i].push_back(0);
	d_nbSommets++;
    std::vector<int>* ptr = new std::vector<int>{};
    for(int i=0;i< d_nbSommets;i++)  ptr->push_back(0);
    d_matrice.push_back(*ptr);
}

void MatriceAdjacence::inverseAdj(){
    std::vector<std::vector<int>> M{};
    for(int i=0;i< d_nbSommets;i++){
        M.push_back(std::vector<int>{});
		for (int j = 0; j < d_nbSommets; j++) {
            M[i].push_back(d_matrice[j][i]);
        }
    }
    d_matrice=M;
}

void MatriceAdjacence::affiche(){
	for (int i = 0; i < d_nbSommets; i++) {
		for (int j = 0; j < d_nbSommets; j++) {
			std::cout<<d_matrice[i][j]<<" ";
		}
		std::cout << std::endl;
	}
}

}
