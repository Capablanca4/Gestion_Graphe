#ifndef KRUSKAL_H
#define KRUSKAL_H
#include <vector>
#include "include/MatriceAdjacenceValuee.h"

namespace Graphe {

	struct arrete {
		int sommetDep;
		int sommetArr;
		int poids;
	};

	struct arbreArrete {
		arrete arc;
		arbreArrete* filsDroit;
		arbreArrete* filsGauche;
	};

	class Kruskal
	{
	public:
		Kruskal(const MatriceAdjacenceValuee& Mat);
		void affiche()const;
		std::vector<int> sommet(int i)const;
		int valeurMatrice(int i, int j)const;
		~Kruskal();
	private:
		MatriceAdjacenceValuee arbre;
		void insererArrete(arbreArrete*& arbre, arrete inserer);
		void parcourirArbre(arbreArrete* abr, MatriceAdjacenceValuee& arbre, std::vector<int>& pilch, std::vector<int> cfc, std::vector<int> prem);
		void fusion(const arrete& abr, std::vector<int>& pilch, std::vector<int>& cfc, std::vector<int>& prem);
	};

}

#endif // KRUSKAL_H