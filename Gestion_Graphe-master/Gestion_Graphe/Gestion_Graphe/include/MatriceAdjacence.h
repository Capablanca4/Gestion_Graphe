#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H
#include <vector>

namespace Graphe{

class FsAps;

class MatriceAdjacence
{
    public:
        /// Construteur et destructeur
        MatriceAdjacence();
        MatriceAdjacence(std::vector<std::vector<int>> matrice,int nbSommets,int nbArc);
        MatriceAdjacence(int nbSommets);
		MatriceAdjacence(FsAps graph);
        ~MatriceAdjacence();

        /// Getteur
        const int nbSommets() const;
        const int nbArc() const;
        const std::vector<int> Sommet(int Sommet) const;

        /// Setteur
        void AjouteArc(int sommetDep,int sommetArr);
        void AjouteSommet();

        /// Methode
        void inverseAdj();
		void affiche();
		void aleatoire();

		
		

		friend MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2);
		MatriceAdjacence operator=(const MatriceAdjacence& M);
		friend MatriceAdjacence operator-(const MatriceAdjacence & M, const MatriceAdjacence & M2);
    private:
        std::vector<std::vector<int>> d_matrice;
        int d_nbSommets;
        int d_nbArc;
};

}
#endif // MATRICEADJACENCE_H
