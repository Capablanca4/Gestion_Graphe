#include "CoeficientConnexe.h"


namespace Graphe {
	CoeficientConnexe::CoeficientConnexe(Distance D) {
		int coef = -1, sommet;
		int nbSommets = D.nbSommets();
		d_premiers.resize(nbSommets);
		d_pilchainer.resize(nbSommets);
		d_coeficientsConnexes.resize(nbSommets, 0);
		for (int i = 0;i < nbSommets;i++) {
			if (d_coeficientsConnexes[i] == 0) {
				coef++;
				d_coeficientsConnexes[i] = coef;
				d_premiers[coef] = i;
				sommet = i;
				for (int j = i + 1;j < nbSommets;j++) {
					if (d_coeficientsConnexes[j] == 0) {
						if (D.dist(i,j) == -1 && D.dist(j,i) != -1) {
							d_pilchainer[sommet] = j;
							d_coeficientsConnexes[j] = coef;
							sommet = j;
						}
					}
				}
				d_pilchainer[sommet] = 0;
			}
			d_premiers[sommet] = coef;
		}
	}

	int CoeficientConnexe::nbSommets()const {
		return d_coeficientsConnexes.size();
	}
	int CoeficientConnexe::premiers(int i)const {
		return d_premiers[i];
	}
	int CoeficientConnexe::coeficientConnexe(int i)const {
		return d_coeficientsConnexes[i];
	}
	CoeficientConnexe::~CoeficientConnexe()
{
}

}


