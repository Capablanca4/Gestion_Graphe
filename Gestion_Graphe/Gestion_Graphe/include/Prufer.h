#ifndef PRUFER_H
#define PRUFER_H
#include "MatriceAdjacence.h"
#include <vector>

namespace Graphe {

class Prufer {
	public:
		Prufer(MatriceAdjacence& mat);
		void decodage();
		int sommet(int i)const;
		void affiche()const;
	private:
		std::vector<int> d_codage;
};

}


#endif // PRUFER_H