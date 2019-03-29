#ifndef MATRICEADJACENCE_H
#define MATRICEADJACENCE_H
#include <vector>
#include <string>
#include "alea.h"
namespace Graphe {

	class FsAps;

	class MatriceAdjacence
	{
	public:
		/// Construteur et destructeur
		MatriceAdjacence();
		MatriceAdjacence(alea aleatoire);
		MatriceAdjacence(int nbSommets);
		MatriceAdjacence(std::vector<std::vector<int>> matrice, int nbSommets, int nbArc);
		MatriceAdjacence(FsAps graph);
		MatriceAdjacence(std::string Fichier);
		~MatriceAdjacence();

		/// Getteur
		const int nbSommets() const;
		const int nbArc() const;
		const std::vector<int> Sommet(int Sommet) const;
		const int ValeurMatrice(int i, int j)const;

		/// Setteur
		void ajouteSommet();
		void setMatrice(std::vector<std::vector<int>>matrice);
		virtual void setArc(int sommetDep, int sommetArr, int valeur);

		/// Methode
		void inverseAdj();
		void affiche();

		void enregistrerMatriceAdjacence(std::ofstream& os);
		void recupererMatriceAdjacence(std::ifstream& is);

		friend MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2);
		MatriceAdjacence operator=(const MatriceAdjacence& M);
		//friend MatriceAdjacence operator-(const MatriceAdjacence & M, const MatriceAdjacence & M2);
	private:
		std::vector<std::vector<int>> d_matrice;
		int d_nbSommets;
		int d_nbArc;

		//Methode privée ?
	protected:
		void dimensionnerA0();
	};

}
#endif // MATRICEADJACENCE_H
