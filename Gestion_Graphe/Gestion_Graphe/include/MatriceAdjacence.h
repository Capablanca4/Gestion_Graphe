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
        const std::vector<int> Sommet(int noeud) const;

        /// Setteur
        void AjouteArc(int noeudDep,int noeudArr);
        void AjouteSommet();

        /// Methode
        void inverseAdj();
		void affiche();

    private:
        std::vector<std::vector<int>> d_matrice;
		int d_nbSommets;
        int d_nbArc;
};

}
#endif // MATRICEADJACENCE_H
