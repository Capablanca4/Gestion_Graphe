#include "GrapheReduit.h"
#include "CoeficientConnexe.h"
#include "include/FsAps.h"

namespace Graphe {
	GrapheReduit::GrapheReduit(const CoeficientConnexe &C,const FsAps &FA) {

		int nbSommets = FA.nbSommets(), kr = 0, sommet;
		vector<int> deja_mis(nbSommets);
	
		d_FileSuivantReduit.resize(FA.nbArc() + nbSommets);
		d_AdressesPremiersSuccesseursReduit.resize(nbSommets);

		for (int c = 0;c < nbSommets;c++) {
			d_AdressesPremiersSuccesseursReduit[c] = kr;
			for (int i = 0;i < nbSommets;i++) {
				deja_mis[i] = false;
			}
			deja_mis[c] = true;
			sommet = C.premiers(c);
		//	while (sommet != 0) {
				for (int t = FA.adressePremierSuccesseur(sommet);FA.fileSuivant(t) != 0;t++) {
					if ( deja_mis[C.coeficientConnexe(FA.fileSuivant(t))]== false) {
						
						d_FileSuivantReduit[kr] == C.coeficientConnexe(FA.fileSuivant(t));
						kr++;
						deja_mis[C.coeficientConnexe(FA.fileSuivant(t))]=true;
					}
				}
		//	}
			d_FileSuivantReduit[kr] = 0;
			kr++;
		}
		d_FileSuivantReduit.resize(kr-1);
		d_FsApsReduit = FsAps(nbSommets, d_FileSuivantReduit, kr - 1 - nbSommets, d_AdressesPremiersSuccesseursReduit);
	}



	GrapheReduit::~GrapheReduit()
	{
	}
	FsAps GrapheReduit::getFsAps() const
	{
		return d_FsApsReduit;
	}
}