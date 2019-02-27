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
    d_nbSommets{nbSommets},
    d_nbArc{nbArc} {}

MatriceAdjacence::MatriceAdjacence():
    d_matrice{},
    d_nbSommets{0},
    d_nbArc{0} {}

MatriceAdjacence::MatriceAdjacence(int nbSommets):
    d_matrice{},
    d_nbSommets{nbSommets},
    d_nbArc{0}
{
    for(int i=0;i<nbSommets;i++){
        std::vector<int>* ptr = new std::vector<int>{};
        for(int j=0;j<nbSommets;j++)  ptr->push_back(0);
        d_matrice.push_back(*ptr);
    }
}

MatriceAdjacence::MatriceAdjacence(FsAps graph):
	d_nbSommets{graph.nbSommets()},
	d_nbArc{graph.NbArc()},
	d_matrice{}
{
	for (int i = 0; i < d_nbSommets; i++) {
		std::vector<int> B;
		for (int j = 0; j < d_nbSommets; j++)  B.push_back(0);
		int j = graph.AdressePremierSuccesseur(i);
		while (graph.FileSuivant(j) != 0) {
			B[graph.FileSuivant(j++)-1] = 1;
		}
		d_matrice.push_back(B);
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

const std::vector<int> MatriceAdjacence::Noeud(int noeud) const{
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
    for(int i=0;i<d_nbSommets;i++)  ptr->push_back(0);
    d_matrice.push_back(*ptr);
}

void MatriceAdjacence::inverseAdj(){
    std::vector<std::vector<int>> M{};
    for(int i=0;i<d_nbSommets;i++){
        M.push_back(std::vector<int>{});
        for(int j=0;j<d_nbSommets;j++){
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

void MatriceAdjacence::aleatoire()
{
	MatriceAdjacence M(rand() % (11 - 3) + 3);
	for (int i = 1; i <= M.nbSommets; i++) {
		for (int j = 1; j <= M.nbSommets; j++) {
			if ((rand() % (101))<10) {
				M.d_matrice[i][j] = 1;
			}
		}
	}
}

MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2)
{
	int tailleMin = static_cast<int>(fmin(M.nbSommets(), M2.nbSommets()));
	std::vector<std::vector<int>> matrice;
	matrice.resize(tailleMin);
	int nbArc = 0;
	for (int i = 0; i < tailleMin; i++) {
		matrice[i].resize(tailleMin);
	}
	for (int i = 0; i < tailleMin; i++) {
		for (int j = 0; j < tailleMin; j++) {
			if (M[i][j] == 1 && M2[i][j] == 1) {
				matrice[i][j] = 1;
				nbArc++;
			}
			else {
				if (M[i][j] == 1 && M2[i][j] == 1) {
					nbArc++;

				}
				matrice[i][j] = M[i][j] + M2[i][j];
			}
		}
	}
	return MatriceAdjacence(matrice, tailleMin, nbArc);
}

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
			if (M[i][j] == 0) {
				matrice[i][j] = 0;

			}
			else {
				if (M2[i][j] == 1) {
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
}

}
