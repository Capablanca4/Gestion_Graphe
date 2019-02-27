#include "Distance.h"
#include "FsAps.h"
#include "MatriceAdjacence.h"

namespace Graphe {

Distance::Distance(const MatriceAdjacence& graphe):
	d_matrice{}
{
	d_matrice.push_back(std::vector<int>{graphe.nbNoeud(), graphe.nbArc() } );
	for (int i = 0; i < graphe.nbNoeud(); i++) {
		std::vector<int> Ligne=distMat(graphe,i+1);
		d_matrice.push_back(Ligne);
	}
}

Distance::Distance(const FsAps& graphe) :
	d_matrice{}
{
	std::vector<int> avector = { graphe.NbNoeud(), graphe.NbArc() };
	//d_matrice.push_back(std::vector<int>{graphe.NbNoeud(), graphe.NbArc() });
	d_matrice.push_back(avector);
	for (int i = 0; i < graphe.NbNoeud(); i++) {
		std::vector<int> Ligne = distFsAps(graphe, i );
		d_matrice.push_back(Ligne);
	}
}

std::vector<int> Distance::distFsAps(const FsAps& graphe, int Sommet) {
	int t = 0, q = 1, p = 1, d = 0, nbSommet = graphe.NbNoeud();
	std::vector<int> tdist{ nbSommet };
	int *fa = new int[nbSommet + 1];
	fa[0] = Sommet;
	for (int i = 1; i <= nbSommet; i++)  tdist.push_back(-1);
	tdist[Sommet] = 0;
	while (t < q) {
		d++;
		for (int i = t ; i < q ; i++) {
			int suiv = graphe.Aps(fa[i]);
			while (graphe.Fs(suiv) != 0) {
				if (tdist[graphe.Fs(suiv)] == -1) {
					tdist[graphe.Fs(suiv)] = d;
					fa[p++] = graphe.Fs(suiv);
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
	int t = 0, q = 1, p = 1, d = 0, nbSommet = graphe.nbNoeud();
	std::vector<int> tdist{ nbSommet };
	int *fa = new int[nbSommet + 1];
	fa[0] = Sommet;
	for (int i = 1; i <= nbSommet; i++)  tdist.push_back(-1);
	tdist[Sommet] = 0;
	while (t < q) {
		d++;
		for (int i = t + 1; i < q + 1; i++) {
			std::vector<int> suiv{graphe.Noeud(fa[i])};
			for (int j = 0; j < nbSommet; j++) {
				if (suiv[j] != 0) {
					if (tdist[suiv[j]] == -1) {
						tdist[suiv[j]] = d;
						fa[++p] = suiv[j];
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
}

}