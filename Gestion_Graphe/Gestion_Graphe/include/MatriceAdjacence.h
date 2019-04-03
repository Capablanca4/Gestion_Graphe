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
		virtual const std::vector<int> sommet(int Sommet) const;
		virtual const int valeurMatrice(int i, int j)const;

		/// Setteur
		virtual void ajouteSommet();
		virtual void supprimeSommet(int sommet);
		void ajouterArc(int sommetDep, int sommetArr);
		virtual void supprimerArc(int sommetDep, int sommetArr);
		virtual void setMatrice(const std::vector<std::vector<int>>& matrice);

		/// Methode
		virtual void inverse();
		virtual void affiche() const;

		virtual void enregistrerMatrice(std::ofstream& os)const;
		virtual void recupererMatrice(std::ifstream& is);

		friend MatriceAdjacence operator+(const MatriceAdjacence & M, const MatriceAdjacence & M2);
		MatriceAdjacence operator=(const MatriceAdjacence& M);
		//friend MatriceAdjacence operator-(const MatriceAdjacence & M, const MatriceAdjacence & M2);
	private:
		std::vector<std::vector<int>> d_matrice;
		int d_nbSommets;
		int d_nbArc;

	protected:
		void dimensionnerA0();
		virtual void setArc(int sommetDep, int sommetArr, int valeur);
	};

}
#endif // MATRICEADJACENCE_H
