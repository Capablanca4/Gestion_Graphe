#ifndef DJIKSTRA_H
#define DJIKSTRA_H
#include "include/FsAps.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include <vector>

namespace Graphe {
	class Djikstra
	{
	public:
		Djikstra(const FsAps& graph, const std::vector<std::vector<int>>& Poids,int sommet);
		Djikstra(const MatriceAdjacenceValuee & M, int sommet);
		int distance(int i)const;
		int predecesseur(int i)const;
		void affiche()const;
	private:
		std::vector<int> d_distance;
		std::vector<int> d_predecesseur;
	};

}

#endif // DJIKSTRA_H