#ifndef DISTANCE_H
#define DISTANCE_H
#include <vector>

namespace Graphe {

class FsAps;
class MatriceAdjacence;

class Distance {
	public:
		Distance(const FsAps& graphe);
		Distance(const MatriceAdjacence& graphe);

		/// Accesseur
		const std::vector<int> Sommet(int i)const;
		int valeurMatrice(int i, int j)const;
		void affiche();
		
	private:
		std::vector<std::vector<int>> d_matrice;

		/// Methode privee
		std::vector<int> distFsAps(const FsAps& graphe, int Sommet);
		std::vector<int> distMat(const MatriceAdjacence& graphe, int Sommet);
};
}


#endif // DISTANCE_H