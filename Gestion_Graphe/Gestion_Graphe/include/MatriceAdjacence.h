#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H
#include <vector>

namespace Graphe{

class MatriceAdjacence
{
    public:
        /// Construteur et destructeur
        MatriceAdjacence();
        MatriceAdjacence(std::vector<std::vector<int>> matrice,int nbNoeud,int nbArc);
        MatriceAdjacence(int nbNoeud);
        ~MatriceAdjacence();

        /// Getteur
        int nbNoeud();
        int nbArc();
        std::vector<int> Noeud(int noeud);

        /// Setteur
        void AjouteArc(int noeudDep,int noeudArr);
        void AjouteNoeud();

        /// Methode
        void inverseAdj();

    private:
        std::vector<std::vector<int>> d_matrice;
        int d_nbNoeud;
        int d_nbArc;
};

}
#endif // MATRICEADJACENCE_H
