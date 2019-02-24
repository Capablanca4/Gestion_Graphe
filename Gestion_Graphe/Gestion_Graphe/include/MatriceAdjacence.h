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
        MatriceAdjacence(std::vector<std::vector<int>> matrice,int nbNoeud,int nbArc);
        MatriceAdjacence(int nbNoeud);
		MatriceAdjacence(FsAps graph);
        ~MatriceAdjacence();

        /// Getteur
        const int nbNoeud() const;
        const int nbArc() const;
        const std::vector<int> Noeud(int noeud) const;

        /// Setteur
        void AjouteArc(int noeudDep,int noeudArr);
        void AjouteNoeud();

        /// Methode
        void inverseAdj();
		void affiche();

    private:
        std::vector<std::vector<int>> d_matrice;
        int d_nbNoeud;
        int d_nbArc;
};

}
#endif // MATRICEADJACENCE_H
