#ifndef FSAPS_H
#define FSAPS_H
#include <vector>

namespace Graphe{

class MatriceAdjacence;

class FsAps
{
    public:
        /// Constructeur
        FsAps(int nbNoeud);
        FsAps(int nbNoeud,const std::vector<int>& fs);
		FsAps(int nbNoeud, const std::vector<int>& fs, int nbArc, const std::vector<int>& aps);
		FsAps(MatriceAdjacence adj);
        ~FsAps();

        ///Accesseur
        const int NbNoeud() const;
        const int NbArc() const;
        const int Fs(int i) const;
        const int Aps(int i) const;

		/// Setteur
		void AjouteArc(int noeudDep, int noeudArr);
		void AjouteNoeud();

		/// inverse le graphe
		void inverse();

		/// Methode d'affichage
		void afficheFs();
		void afficheAps();
		void affiche();

    private:
        int d_tailleFs;
        int d_tailleAps;
        std::vector<int> d_fs;
        std::vector<int> d_aps;

        /// Methode privee
        void determiner_aps();
};

}

#endif // FSAPS_H
