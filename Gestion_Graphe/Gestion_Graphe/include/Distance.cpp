#include "Distance.h"
#include "FsAps.h"
#include "MatriceAdjacence.h"
#include <iostream>

namespace Graphe {

Distance::Distance(const MatriceAdjacence& graphe):
	d_matrice{}
{
	d_matrice.push_back(std::vector<int>{graphe.nbSommets(), graphe.nbArc() } );
	for (int i = 0; i < graphe.nbSommets(); i++) {
		std::vector<int> Ligne=distMat(graphe,i);
		d_matrice.push_back(Ligne);
	}
}

Distance::Distance(const FsAps& graphe) :
	d_matrice{}
{
	std::vector<int> avector = { graphe.nbSommets(), graphe.NbArc() };
	//d_matrice.push_back(std::vector<int>{graphe.NbNoeud(), graphe.NbArc() });
	d_matrice.push_back(avector);
	for (int i = 0; i < graphe.nbSommets(); i++) {
		std::vector<int> Ligne = distFsAps(graphe, i );
		d_matrice.push_back(Ligne);
	}
}

std::vector<int> Distance::distFsAps(const FsAps& graphe, int Sommet) {
	int t = 0, q = 1, p = 1, d = 0, nbSommet = graphe.nbSommets();
	std::vector<int> tdist{ nbSommet };
	int *fa = new int[nbSommet + 1];
	fa[0] = Sommet;
	for (int i = 1; i <= nbSommet; i++)  tdist.push_back(-1);
	tdist[Sommet+1] = 0;
	while (t < q) {
		d++;
		for (int i = t ; i < q ; i++) {
			int suiv = graphe.AdressePremierSuccesseur(fa[i]);
			while (graphe.FileSuivant(suiv) != 0) {
				if (tdist[graphe.FileSuivant(suiv)] == -1) {
					tdist[graphe.FileSuivant(suiv)] = d;
					fa[p++] = graphe.FileSuivant(suiv)-1;
				}
				suiv++;
			}
		}
		t = q;
		q = p;
	}
	delete fa;
	return tdist;
}

std::vector<int> Distance::distMat(const MatriceAdjacence& graphe, int Sommet) {
	int t = 0, q = 1, p = 1, d = 0, nbSommet = graphe.nbSommets();
	std::vector<int> tdist{ nbSommet };
	int *fa = new int[nbSommet + 1];
	fa[0] = Sommet;
	for (int i = 1; i <= nbSommet; i++)  tdist.push_back(-1);
	tdist[Sommet+1] = 0;
	while (t < q) {
		d++;
		for (int i = t ; i < q ; i++) {
			std::vector<int> suiv= graphe.Sommet(fa[i]);
			for (int j = 0; j < nbSommet; j++) {
				if (suiv[j] != 0) { 
					if (tdist[j+1] == -1) { 
						tdist[j+1] = d;
						fa[p++] = j;
					}
				}
			}
		}
		t = q;
		q = p;
	}
	delete fa;
	return tdist;
}

const std::vector<int> Distance::Sommet(int i) const
{
	return d_matrice[i];
}

void Distance::affiche()
{
	for (int i = 0; i < d_matrice.size(); i++) {
		for (int j = 0; j < d_matrice[i].size(); j++) {
			std::cout << d_matrice[i][j] << ",";
		}
		std::cout << std::endl;
	}
}

}