#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H
#include <vector>
#include <string>
namespace Graphe{

class FsAps;

class MatriceAdjacence
{
    public:
        /// Construteur et destructeur
        MatriceAdjacence();
        MatriceAdjacence(std::vector<std::vector<int>> matrice,int nbSommets,int nbArc);
        MatriceAdjacence(int nbSommets);
		MatriceAdjacence(std::string Fichier);
		MatriceAdjacence(FsAps graph);
        ~MatriceAdjacence();

        /// Getteur
         int nbSommets() const;
         int nbArc() const;
         std::vector<int> Sommet(int Sommet) const;
		 int ValeurMatrice(int i, int j)const;

        /// Setteur
        virtual void AjouteArc(int sommetDep,int sommetArr);
        void AjouteSommet();
		void setMatrice(std::vector<std::vector<int>>matrice);
		void setNbSommets(int nbSommets);
		void setNbArcs(int nbArcs);
		void setValeurMatrice(int i, int j, int valeur);

        /// Methode
		void dimensionnerA0();
        void inverseAdj();
		void affiche();
		void aleatoire();

		
		
		void enregistrerMatriceAdjacence(const std::string& fichier);
		void recupererMatriceAdjacence(const std::string& fichier);
		friend MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2);
		MatriceAdjacence operator=(const MatriceAdjacence& M);
		//friend MatriceAdjacence operator-(const MatriceAdjacence & M, const MatriceAdjacence & M2);
    private:
        std::vector<std::vector<int>> d_matrice;
        int d_nbSommets;
        int d_nbArc;
};

}
#endif // MATRICEADJACENCE_H
