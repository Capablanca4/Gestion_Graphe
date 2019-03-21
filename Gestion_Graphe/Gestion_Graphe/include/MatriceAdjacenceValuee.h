#ifndef MATRICEADJACENCEVALUEE_H
#define	MATRICEADJACENCEVALUEE_H
#include <vector>
#include "MatriceAdjacence.h"

namespace Graphe {
	class MatriceAdjacenceValuee : public MatriceAdjacence {
	public:
		MatriceAdjacenceValuee(int nbSommets);
		MatriceAdjacenceValuee(const std::string & fichier);
		MatriceAdjacenceValuee(int nbSommets, int nbArcs, std::vector<std::vector<int>> Matrice);
		MatriceAdjacenceValuee(int nbSommets, int nbArcs, std::vector<std::vector<int>> Matrice,bool valuer=1);
		MatriceAdjacenceValuee(bool valeurAleatoirePositives);
		bool SansValeurNegative()const;
	   virtual void AjouteArc(int sommetDep, int sommetArriver, int valeur);
		void ModifierArc(int sommetDep, int sommetArriver, int valeur);
		bool EstUnArc(int sommmetDep, int sommetArriver);

		virtual void affiche()const ;
		void enregistrerMatriceAdjacenceValuee(const std::string & fichier);
		void recupererMatriceAdjacenceValuee(const std::string & fichier);
		void dimensionnerAInfini();
	private:
		std::vector<std::vector<int>> d_MatriceAvecValeur;
	};
}
#endif // !MATRICEADJACENCEVALUEE_H

