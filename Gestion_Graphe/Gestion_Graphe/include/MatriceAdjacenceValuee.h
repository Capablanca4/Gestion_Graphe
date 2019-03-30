#ifndef MATRICEADJACENCEVALUEE_H
#define	MATRICEADJACENCEVALUEE_H
#include <vector>
#include "MatriceAdjacence.h"

namespace Graphe {
	class MatriceAdjacenceValuee : public MatriceAdjacence {
	public:
		MatriceAdjacenceValuee();
		MatriceAdjacenceValuee(int nbSommets);
		MatriceAdjacenceValuee(const std::string & fichier);
		MatriceAdjacenceValuee(int nbSommets, int nbArcs, std::vector<std::vector<int>> Matrice);
		MatriceAdjacenceValuee(alea aleatoire, int valeurmax, int valeurmin);

		bool sansValeurNegative()const;

		//Fonction provenant de MatriceAjacence
		virtual void ajouteSommet()override;
		virtual void supprimeSommet(int sommet)override;
		void ajouterArc(int sommetDep, int sommetArriver,int valeur);// Ne peut pas etre virtuel car a une signature differente
		virtual void supprimerArc(int sommetDep, int sommetArriver)override;
		virtual void setMatrice(const std::vector<std::vector<int>>& matrice)override;
		virtual void inverse()override;
		virtual void affiche()const override;
		virtual void enregistrerMatrice(std::ofstream& os)const override;
		virtual void recupererMatrice(std::ifstream& is) override;

	private:
		std::vector<std::vector<int>> d_MatriceAvecValeur;

		//Methode privée
		bool estUnArc(int sommmetDep, int sommetArriver)const;
		void dimensionnerAInfini();
		virtual void setArc(int sommetDep, int sommetArriver, int valeur) override;	
	};
}
#endif // !MATRICEADJACENCEVALUEE_H
