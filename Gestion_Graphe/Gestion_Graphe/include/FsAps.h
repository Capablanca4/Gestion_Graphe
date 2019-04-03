#ifndef FSAPS_H
#define FSAPS_H
#include <vector>
#include "alea.h"

namespace Graphe {

	class MatriceAdjacence;

	class FsAps
	{
	public:
		/// Constructeur
		FsAps();
		FsAps(int nbSommets);
		FsAps(alea aleatoire);
		FsAps(int nbSommets, const std::vector<int>& FileSuivant);
		FsAps(int nbSommets, const std::vector<int>& FileSuivant, int nbArc, const std::vector<int>& AdressePremierSuccesseur);
		FsAps(const std::string& fichier);
		FsAps(const MatriceAdjacence& adj);
		~FsAps();

		///Accesseur
		const int nbSommets() const;
		const int nbArc() const;
		const int fileSuivant(int i) const;
		const int adressePremierSuccesseur(int i) const;

		/// Setteur
		void ajouteArc(int noeudDep, int noeudArr);
		void supprimerArc(int noeudDep, int noeudArr);
		void ajouteSommet();
		void supprimeSommet(int noeud);

		/// inverse le graphe
		void inverse();

		/// Methode d'affichage
		void afficheFileSuivant();
		void afficheAdressePremierSuccesseur();
		void affiche();

		void enregistrerFsAps(std::ofstream& os);
		void recupererFsAps(std::ifstream& is);

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
