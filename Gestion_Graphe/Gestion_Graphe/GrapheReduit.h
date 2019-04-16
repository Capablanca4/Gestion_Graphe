#pragma 
#include<iostream>
#include<vector>
using std::vector;
namespace Graphe {
	class CoeficientConnexe;
	class FsAps;
	class GrapheReduit
	{
	public:
		GrapheReduit(const CoeficientConnexe &C, const FsAps &FA);
		~GrapheReduit();
	private:
		vector<int> d_FileSuivantReduit;
		vector<int> d_AdressesPremiersSuccesseursReduit;

	};


}
