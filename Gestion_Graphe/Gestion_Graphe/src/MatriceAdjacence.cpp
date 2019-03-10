#include "../include/MatriceAdjacence.h"
#include "../include/FsAps.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <fstream>
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
	dimensionnerA0();
}

MatriceAdjacence::MatriceAdjacence(std::string Fichier)
{
	recupererMatriceAdjacence(Fichier);
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

 int MatriceAdjacence::nbSommets() const {
    return d_nbSommets;
}

 int MatriceAdjacence::nbArc() const {
    return d_nbArc;
}

 std::vector<int> MatriceAdjacence::Sommet(int Sommet) const{
    return d_matrice[Sommet];
}

 int MatriceAdjacence::ValeurMatrice(int i, int j)const
{
	return d_matrice[i][j];
}

 void MatriceAdjacence::setValeurMatrice(int i, int j,int valeur)
 {
	  d_matrice[i][j]=valeur;
 }
void MatriceAdjacence::AjouteArc(int SommetDep,int SommetArr){
    if(!d_matrice[SommetDep][SommetArr]){
        d_matrice[SommetDep][SommetArr]=1;
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

void MatriceAdjacence::dimensionnerA0()
{
	d_matrice.resize(d_nbSommets);
	for (int i = 0; i < d_nbSommets; i++) {
		d_matrice[i].resize(d_nbSommets, 0);
	}
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
	/*MatriceAdjacence M(rand() % (11 - 3) + 3);
	for (int i = 1; i <= M.nbSommets; i++) {
		for (int j = 1; j <= M.nbSommets; j++) {
			if ((rand() % (101))<10) {
				M.d_matrice[i][j] = 1;
			}
		}
	}*/
}

void MatriceAdjacence::enregistrerMatriceAdjacence(const std::string& fichier) 
{
	std::ofstream os(fichier + ".txt");
	
	os <<d_nbSommets;
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

void MatriceAdjacence::recupererMatriceAdjacence(const std::string & fichier)
{
	std::ifstream is(fichier + ".txt");

	is>> d_nbSommets;
	is>> d_nbArc;
	dimensionnerA0();
	for (int i = 0; i < d_nbSommets; i++) {
		for (int j = 0; j < d_nbSommets; j++) {
			is >> d_matrice[i][j];
		}
	}
}

MatriceAdjacence MatriceAdjacence::operator=(const MatriceAdjacence& M)
{

	return MatriceAdjacence(M.d_matrice,M.d_nbSommets,M.d_nbArc);
}

MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2)
{	std::vector<std::vector<int>> matrice;
	int nbArc = 0;
	int nbSommets;
	std::cout<< M.nbSommets() << std::endl;
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

void MatriceAdjacence::setMatrice(std::vector<std::vector<int>>matrice) {
	d_matrice = matrice;
}
void MatriceAdjacence::setNbSommets(int nbSommets)
{
	d_nbSommets = nbSommets;
}
void MatriceAdjacence::setNbArcs(int nbArcs)
{
	d_nbArc = nbArcs;
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
