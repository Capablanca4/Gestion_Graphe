#include "include/MatriceAdjacence.h"
#include "include/FsAps.h"
#include "include/MatriceAdjacenceValuee.h"
#include <iostream>

namespace Graphe {
	const int INFINI = INT_MAX;
	MatriceAdjacenceValuee::MatriceAdjacenceValuee(int nbSommets) :
		d_matrice{},
		d_nbSommets{ nbSommets },
		d_nbArc{ 0 }
	{
		d_matrice.resize(nbSommets);
		for (int i = 0; i < nbSommets; i++) {
			d_matrice[i].resize(nbSommets, INFINI);
		}
	}
}