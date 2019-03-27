#include "FsAps.h"
#include "MatriceAdjacence.h"

namespace Graphe{

class Rang
{
public:
	Rang(const FsAps& Graph);
	Rang(const MatriceAdjacence& Graph);

	//Accesseur
	const int Sommet(int i)const;
	void affiche();

private:
	std::vector<int> rang;
	
	///Methode privee
	void det_ddi(const FsAps& fs, std::vector<int>& ddi);
	void det_ddi(const MatriceAdjacence& mat, std::vector<int>& ddi);
	void empiler(int x, std::vector<int>& pilch);
};

}