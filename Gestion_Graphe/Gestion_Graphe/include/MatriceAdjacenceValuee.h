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
		MatriceAdjacenceValuee(alea aleatoire, int bornesup, int borneinf);
		bool SansValeurNegative()const;
		virtual void SetArc(int sommetDep, int sommetArriver, int valeur);

		virtual void affiche()const;
		void enregistrerMatriceAdjacenceValuee(std::ofstream& os);
		void recupererMatriceAdjacenceValuee(std::ifstream& is);
		void dimensionnerAInfini();
	private:
		std::vector<std::vector<int>> d_MatriceAvecValeur;
		bool EstUnArc(int sommmetDep, int sommetArriver);
	};
}
#endif // !MATRICEADJACENCEVALUEE_H
