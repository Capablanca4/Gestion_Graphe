#ifndef FSAPS_H
#define FSAPS_H
#include <vector>

namespace Graphe{

class MatriceAdjacence;

class FsAps
{
    public:
        /// Constructeur
        FsAps(int nbSommets);
        FsAps(int nbSommets,const std::vector<int>& FileSuivant);
		FsAps(int nbSommets, const std::vector<int>& FileSuivant, int nbArc, const std::vector<int>& AdressePremierSuccesseur);
		FsAps(std::string fichier);
		FsAps(MatriceAdjacence adj);
        ~FsAps();

        ///Accesseur
        const int nbSommets() const;
        const int NbArc() const;
        const int FileSuivant(int i) const;
        const int AdressePremierSuccesseur(int i) const;

		/// Setteur
		void AjouteArc(int noeudDep, int noeudArr);
		void AjouteNoeud();

		/// inverse le graphe
		void inverse();

		/// Methode d'affichage
		void afficheFileSuivant();
		void afficheAdressePremierSuccesseur();
		void affiche();

		std::vector<int> TableauDesDistances(int sommet);
		std::vector<std::vector<int>> MatriceDesDistances();

		void enregistrerFsAps(const std::string & fichier);

		void recupererFsAps(const std::string & fichier);

    private:
        int d_tailleFileSuivant;//nbArc+nbSommets
        int d_tailleAdressePremierSuccesseur;//nbSommets
        std::vector<int> d_FileSuivant;
        std::vector<int> d_AdressePremierSuccesseur;

        /// Methode privee
        void determiner_AdressePremierSuccesseur();
};

}

#endif // FSAPS_H
