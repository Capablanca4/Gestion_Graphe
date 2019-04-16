#pragma once
#include "include/Distance.h"
using std::vector;
namespace Graphe {
	class CoeficientConnexe
	{
	public:
		int nbSommets() const;
		int premiers(int i) const;
		int coeficientConnexe(int i) const;
		~CoeficientConnexe();
		CoeficientConnexe(Distance D);
	private:
		vector<int>d_premiers;
		vector<int>d_pilchainer;
		vector<int>d_coeficientsConnexes;
	};
}

