#include "..\include\Rang.h"
#include <iostream>

namespace Graphe{

Rang::Rang(const FsAps& Graph):
	rang{}
{
	int n = Graph.nbSommets(),iter = -1;
	rang.resize(n+1, -1);
	rang[0] = 0;
	std::vector<int> DemiDegreInterne{};
	DemiDegreInterne.resize(n + 1, 0);
	det_ddi(Graph, DemiDegreInterne);/// Initialisation de ddi
	std::vector<int> pilch{};
	pilch.resize(n + 1, 0);/// Initialisation de pilch ( chaque sommet est à vide au départ)
	std::vector<int> prem{};
	prem.resize(n+1, 0);
	for (int i = 1; i <= n; i++) {
		if (DemiDegreInterne[i] == 0) {
			empiler(i, pilch);
		}
	}
	int sommet = pilch[0];
	prem[0] = sommet;
	while (pilch[0]>0){
		iter++;
		pilch[0] = 0;
		while (sommet > 0) {
			rang[sommet] = iter;
			int h = Graph.adressePremierSuccesseur(sommet-1);
			int t;
			while ((t = Graph.fileSuivant(h) )!=0)
			{
				DemiDegreInterne[t]--;
				if (DemiDegreInterne[t] == 0) {
					empiler(t,pilch);
				}
				h++;
			}
			sommet = pilch[sommet];
		}
		sommet = pilch[0];
		prem[iter + 1] = sommet;
	}
}

Rang::Rang(const MatriceAdjacence& Graph)
{
	int n = Graph.nbSommets(), iter = -1;
	rang.resize(n + 1, -1);
	rang[0] = 0;
	std::vector<int> DemiDegreInterne{};
	DemiDegreInterne.resize(n + 1, 0);
	det_ddi(Graph, DemiDegreInterne);/// Initialisation de ddi
	std::vector<int> pilch{};
	pilch.resize(n + 1, 0);/// Initialisation de pilch ( chaque sommet est à vide au départ)
	std::vector<int> prem{};
	prem.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (DemiDegreInterne[i] == 0) {
			empiler(i, pilch);
		}
	}
	int sommet = pilch[0];
	prem[0] = sommet;
	while (pilch[0] > 0) {
		iter++;
		pilch[0] = 0;
		while (sommet > 0) {
			rang[sommet] = iter;
			for (int i = 0; i < Graph.nbSommets(); i++) {
				if (Graph.sommet(sommet-1)[i] == 1) {
					DemiDegreInterne[i]--;
					if (DemiDegreInterne[i] == 0) {
						empiler(i, pilch);
					}
				}
			}
			sommet = pilch[sommet];
		}
		sommet = pilch[0];
		prem[iter + 1] = sommet;
	}
}

const int Rang::Sommet(int i) const
{
	return rang[i];
}

void Rang::det_ddi(const FsAps& fs, std::vector<int>& ddi) {
	for (int i = 0; i < fs.nbArc()+fs.nbSommets(); i++) ddi[fs.fileSuivant(i)]++;
}

void Rang::det_ddi(const MatriceAdjacence& mat, std::vector<int>& ddi) {
	ddi[0] = mat.nbArc();
	for (int i = 0; i < mat.nbSommets(); i++) {
		for (int j = 0; j < mat.nbSommets(); j++) {
			if (mat.sommet(i)[j] == 1) ddi[j + 1]++;
		}
	}
}

void Rang::empiler(int x, std::vector<int>& pilch) {
	pilch[x] = pilch[0];
	pilch[0] = x;
}

void Rang::affiche() {
	for (int i = 0; i < rang.size(); i++) {
		std::cout << rang[i] << ";";
	}
	std::cout << std::endl;
 }
}