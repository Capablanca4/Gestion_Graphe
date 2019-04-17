#pragma 
#include<iostream>
#include<vector>
#include"include/FsAps.h"
using std::vector;
namespace Graphe {
	class CoeficientConnexe;
	
	class GrapheReduit
	{
	public:
		GrapheReduit(const CoeficientConnexe &C, const FsAps &FA);
		~GrapheReduit();
		FsAps getFsAps()const;
	private:
		FsAps d_FsApsReduit;
		vector<int> d_FileSuivantReduit;
		vector<int> d_AdressesPremiersSuccesseursReduit;

	};


}
