#include "../../Gestion_Graphe/include/FsAps.h"
#include"../../Gestion_Graphe/include/MatriceAdjacence.h"
#include <iostream>
namespace Graphe{

FsAps::FsAps(int nbNoeud):
    d_tailleAps{nbNoeud},
    d_tailleFs{nbNoeud},
    d_fs{},
    d_aps{}
{
    for(int i=0;i<nbNoeud;i++){
        d_fs.push_back(0);
        d_aps.push_back(i);
    }
}

FsAps::FsAps(int nbNoeud,const std::vector<int>& fs):
    d_tailleAps{nbNoeud},
    d_tailleFs{0},
    d_fs{fs},
    d_aps{}
{
    determiner_aps();
}

FsAps::FsAps(int nbNoeud, const std::vector<int>& fs, int nbArc, const std::vector<int>& aps):
	d_tailleAps{ nbNoeud },
	d_tailleFs{ nbArc },
	d_fs{ fs },
	d_aps{ aps } {}

FsAps::FsAps(MatriceAdjacence adj) :
	d_tailleFs{ adj.nbArc() },
	d_tailleAps{ adj.nbNoeud() },
	d_fs{},
	d_aps{}
{
	int k = 0;
	for (int i = 0; i < d_tailleAps; i++) {
		d_aps.push_back(k);
		for (int j = 0; j < d_tailleAps; j++) {
			if (adj.Noeud(i)[j] != 0) {
				d_fs.push_back(j+1);
				k++;
			}
		}
		d_fs.push_back(0);
		k++;
	}
}

FsAps::~FsAps(){
while(d_fs.size()!=0) d_fs.pop_back();
while(d_aps.size()!=0) d_aps.pop_back();
}

void FsAps::determiner_aps(){
   d_aps.push_back(0);
   d_tailleFs=d_fs.size();
   for(unsigned int i=1;i<d_fs.size()-1;i++){
       if(d_fs[i]==0) {
           d_aps.push_back(i+1);
       }
    }
}

const int FsAps::NbNoeud() const {
    return d_tailleAps;
}

const int FsAps::NbArc() const {
    return d_tailleFs;
}

const int FsAps::Fs(int i) const{
    return d_fs[i];
}

const int FsAps::Aps(int i)const{
    return d_aps[i];
}

void FsAps::AjouteArc(int noeudDep, int noeudArr) {
	if(noeudArr-1<d_tailleFs){
		int emplacementElt = d_aps[noeudDep-1];
		while (d_fs[emplacementElt] < noeudArr&&d_fs[emplacementElt] != 0) {
			emplacementElt++;
		}
		if (d_fs[emplacementElt] != noeudArr) {
			d_fs.push_back(noeudArr);
			for (int i = d_tailleAps; i > emplacementElt;i--) {
				d_fs[i] = d_fs[i - 1];
			}
			d_fs[emplacementElt] = noeudArr;
			d_tailleFs++;
		}
	}
	else {
		printf("Vous donnez un noeud d'arrivee trop grand !");
	}
}

void FsAps::AjouteNoeud() {
	d_fs.push_back(0);
	d_aps.push_back(d_tailleFs);
	d_tailleFs++;
	d_tailleAps++;
}

void FsAps::inverse()
{
	std::vector<std::vector<int>> mat{ };
	for (int i = 0; i < d_tailleAps; i++) {
		mat.push_back(std::vector<int>{});
	}
	int indicemat = 1, indice = 0;
	while (indice < d_tailleFs) { 
		if (d_fs[indice] == 0)  indicemat++;
		else  mat[d_fs[indice]-1].push_back(indicemat);
		indice++;
	}
	indice = 0;
	for (int i = 0; i < d_tailleAps; i++) {
		mat[i].push_back(0);
		d_aps[i] = indice;
		for (int j = 0; j < mat[i].size(); j++) {
			d_fs[indice++] = mat[i][j];
		}
	}
}

void FsAps::afficheFs(){
	std::cout << "Fs : ";
	for (int i =0; i < d_tailleFs; i++) {
		std::cout << d_fs[i] << " ";
	}
}

void FsAps::afficheAps()
{
	std::cout << "Aps : ";
	for (int i = 0; i < d_tailleAps; i++) {
		std::cout << d_aps[i] << " ";
	}
}

void FsAps::affiche()
{
	afficheFs();
	std::cout << std::endl;
	afficheAps();
}

}
