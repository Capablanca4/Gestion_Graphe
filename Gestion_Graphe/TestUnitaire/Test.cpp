#include "stdafx.h"
#include "SpecialisationTest.h"
#include "CppUnitTest.h"
#include "../Gestion_Graphe/include/MatriceAdjacence.h"
#include "../Gestion_Graphe/include/MatriceAdjacenceValuee.h"
#include "../Gestion_Graphe/include/FsAps.h"
#include "../Gestion_Graphe/include/Distance.h"
#include "../Gestion_Graphe/include/alea.h"
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Graphe
{
	/// Variable Globale pour les tests
	int NbNoeud = 7, NbArc = 11;
	std::vector<std::vector<int>> M{ {0,1,1,0,1,0,0},
									 {0,0,1,0,0,0,0},
									 {0,0,1,1,0,0,0},
									 {0,0,0,0,1,1,0},
									 {0,0,1,0,0,0,0},
									 {0,0,0,0,0,0,0},
									 {0,0,0,1,0,1,0} };
	std::vector<int> fs{ 2,3,5,0,3,0,3,4,0,5,6,0,3,0,0,4,6,0 };
	std::vector<int> aps{ 0,4,6,9,12,14,15 };

	bool compareFile(std::ifstream& fileRep, std::ifstream& fileAverifier) {
		///https://stackoverflow.com/questions/6163611/compare-two-files
		if (fileRep.fail() || fileAverifier.fail()) {
			return false; //file problem
		}
		if (fileRep.tellg() != fileAverifier.tellg()) {
			return false; //size mismatch
		}
		//seek back to beginning and use std::equal to compare contents
		fileRep.seekg(0, std::ifstream::beg);
		fileAverifier.seekg(0, std::ifstream::beg);
		return std::equal(std::istreambuf_iterator<char>(fileRep.rdbuf()),
			std::istreambuf_iterator<char>(),
			std::istreambuf_iterator<char>(fileAverifier.rdbuf()));
	}

	TEST_CLASS(TestFsAps) {
private:
	std::vector<int> fp{ 0,1,0,1,2,3,5,0,3,7,0,1,4,0,4,7,0,0 };
	std::vector<int> app{ 0,1,3,8,11,14,17 };
public:

	TEST_METHOD(TestFsApsSansArgument) {
		Graphe::FsAps test{};
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(0, test.nbSommets(),message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(0, test.nbArc(),message);
	}

	TEST_METHOD(TestFsApsAvecUnArgumentInt) {
		Graphe::FsAps test{ NbNoeud };
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, test.nbSommets(),message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(0, test.nbArc(),message);	
		for (int i = 0; i < NbNoeud; i++) {
			swprintf(message, L"Aps est faux à cet endroit: %d", i);
			Assert::AreEqual(i, test.adressePremierSuccesseur(i), message);
			swprintf(message, L"Fs est faux à cet endroit: %d", i);
			Assert::AreEqual(0, test.fileSuivant(i), message);
		}
	}

	TEST_METHOD(TestFsApsAvecUnArgumentAlea) {
		alea aleatoire(1, 10);
		Graphe::FsAps test{ aleatoire };
		int TestNbArc = 0;
		int NbSommet = 0;
		wchar_t message[512];
		for (int i = 0; i < test.nbArc() + test.nbSommets(); i++) {
			swprintf(message, L"la fonctionne génère des noeuds inexistant à cet endroit: %d", i);
			Assert::IsTrue(test.fileSuivant(i) <= test.nbSommets(), message);
			if (test.fileSuivant(i) == 0) NbSommet++;
			else TestNbArc++;
		}
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbSommet, test.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(TestNbArc, test.nbArc(), message);

	}

	TEST_METHOD(TestFsApsAvecDeuxArguments) {
		Graphe::FsAps test{ NbNoeud, fs };
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, test.nbSommets(),message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, test.nbArc(),message);
		for (int i = 0; i < NbArc; i++) {///Test si Fs est correct
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i], test.fileSuivant(i), message);
		}
		for (int i = 0; i < NbNoeud; i++) {///Test si Aps est correct
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i], test.adressePremierSuccesseur(i), message);
		}
	}

	TEST_METHOD(TestFsApsAvecQuatreArguments) {
		Graphe::FsAps test{ NbNoeud, fs,NbArc,aps };
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, test.nbSommets(),message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, test.nbArc(),message);
		for (int i = 0; i < NbArc; i++) {///Test si Fs est correct
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i], test.fileSuivant(i), message);
		}
		for (int i = 0; i < NbNoeud; i++) {///Test si Aps est correct
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i], test.adressePremierSuccesseur(i), message);
		}
	}

	TEST_METHOD(TestMatriceAdjacenceAvecFichier) {
		Graphe::FsAps test{ "ReponseFsAps" };
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, test.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, test.nbArc(), message);
		for (int i = 0; i < test.nbSommets() + test.nbArc(); i++) {
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i], test.fileSuivant(i), message);
		}
		for (int i = 0; i < test.nbSommets(); i++) {
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i], test.adressePremierSuccesseur(i), message);
		}
	}

	TEST_METHOD(TestFsApsAvecMatriceAdjacenceEnArgument) {
		Graphe::FsAps testMat{ NbNoeud, fs, NbArc, aps };
		Graphe::FsAps test{ testMat };
		wchar_t message[512];
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, test.nbArc(), message);
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, test.nbSommets(),message);
		for (int i = 0; i < NbArc; i++) {///Test si Fs est correct
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i], test.fileSuivant(i), message);
		}
		for (int i = 0; i < NbNoeud; i++) {///Test si Aps est correct
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i], test.adressePremierSuccesseur(i), message);
		}
	}

	TEST_METHOD(TestajouteArc) {
		Graphe::FsAps test{ NbNoeud, fs };
		test.ajouteArc(1, 4);
		wchar_t message[512];
		swprintf(message, L"L'arc a bien ete supprime");
		Assert::AreEqual(4, test.fileSuivant(2),message);/// La fonction insère au bon endroit l'élément
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc + 1, test.nbArc(),message);/// La fonction verifie que le nombre d'element de Fs reste correcte
		test.ajouteArc(1, 4);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc + 1, test.nbArc(),message);/// La fonction verifie que l'on n'insere bien aucun element si l'element est deja present
	}

	TEST_METHOD(TessupprimeArc) {
		Graphe::FsAps test{ NbNoeud, fs };
		test.supprimerArc(1, 3);
		wchar_t message[512];
		for (int i = 1; i < test.nbSommets() + test.nbArc();i++) {
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i+1], test.fileSuivant(i),message);/// La fonction supprime le bon endroit élément
		}
		for (int i = 1; i < test.nbSommets() ; i++) {
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i]-1, test.adressePremierSuccesseur(i),message);/// La fonction supprime le bon endroit élément
		}
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc - 1, test.nbArc(),message);/// La fonction verifie que le nombre d'element de Fs reste correcte
		test.supprimerArc(1, 3);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc - 1, test.nbArc(),message);/// La fonction verifie que l'on n'insere bien aucun element si l'element est deja present
		for (int i = 1; i < test.nbSommets() + test.nbArc(); i++) {
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i + 1], test.fileSuivant(i),message);/// La fonction supprime le bon endroit élément
		}
		for (int i = 1; i < test.nbSommets(); i++) {
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i] - 1, test.adressePremierSuccesseur(i),message);/// La fonction supprime le bon endroit élément
		}
	}

	TEST_METHOD(TestajouteSommet) {
		Graphe::FsAps test{ NbNoeud, fs };
		test.ajouteSommet();
		wchar_t message[512];
		swprintf(message, L"NbArc de Aps est faux");
		Assert::AreEqual(NbArc, test.nbArc(), message);
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud + 1, test.nbSommets(), message);
		swprintf(message, L"Le dernier element de FileSuivant est faux");
		Assert::AreEqual(0, test.fileSuivant(test.nbArc() + test.nbSommets() - 1), message);
		swprintf(message, L"Le dernier element de AdressePremierSuccesseur est faux");
		Assert::AreEqual(NbArc + NbNoeud, test.adressePremierSuccesseur(test.nbSommets() - 1), message);
	}

	TEST_METHOD(TestsupprimeSommet) {
		Graphe::FsAps test{ NbNoeud, fs };
		test.supprimeSommet(1);
		wchar_t message[512];
		for (int i = 4; i < NbArc; i++) {
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i], test.fileSuivant(i - 4),message);
		}
		for (int i = 0; i < NbNoeud - 1;i++) {
			swprintf(message, L"Aps est faux à l'iter: %d ", i);
			Assert::AreEqual(aps[i+1]-4, test.adressePremierSuccesseur(i),message);
		}
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud - 1, test.nbSommets(),message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc - 3, test.nbArc(),message);
	}

	TEST_METHOD(TestInverseFsAps) {
		Graphe::FsAps test{ NbNoeud, fs,NbArc,aps };
		test.inverse();
		wchar_t message[512];
		for (int i = 0; i < NbArc; i++) {/// Fp est cree correctement
			swprintf(message, L"Fp est faux à l'iter: %d ", i);
			Assert::AreEqual(fp[i], test.fileSuivant(i), message);
		}
		for (int i = 0; i < NbNoeud; i++) {/// App est cree correctement 
			swprintf(message, L"App est faux à l'iter: %d ", i);
			Assert::AreEqual(app[i], test.adressePremierSuccesseur(i), message);
		}
	}

	TEST_METHOD(TestenregistrerFsAps) {
		Graphe::FsAps test{ NbNoeud, fs,NbArc,aps };
		std::ofstream os("fichier.txt");
		test.enregistrerFsAps(os);
		os.close();
		std::ifstream fileRep("ReponseFsAps.txt");
		std::ifstream fileAverifier("fichier.txt");
		wchar_t message[512];
		swprintf(message, L"Le fichier généré est incorrect");
		Assert::IsTrue(compareFile(fileRep, fileAverifier), message);
	}

	TEST_METHOD(TestrecupererMatriceAdjacence) {
		Graphe::FsAps test{ };
		std::ifstream file("ReponseFsAps.txt");
		test.recupererFsAps(file);
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, test.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, test.nbArc(), message);
		for (int i = 0; i < test.nbSommets()+test.nbArc(); i++) {
			swprintf(message, L"Fs est faux à l'iter: %d ", i);
			Assert::AreEqual(fs[i],test.fileSuivant(i), message);
		}
		for (int i = 0; i < test.nbSommets(); i++) {
		swprintf(message, L"Aps est faux à l'iter: %d ", i);
		Assert::AreEqual(aps[i], test.adressePremierSuccesseur(i), message);
		}
	}

	};

	TEST_CLASS(TestMatriceAdjacence)
	{
	private:
		std::vector<std::vector<int>> inv_M{ {0,0,0,0,0,0,0},
											 {1,0,0,0,0,0,0},
											 {1,1,1,0,1,0,0},
											 {0,0,1,0,0,0,1},
											 {1,0,0,1,0,0,0},
											 {0,0,0,1,0,0,1},
											 {0,0,0,0,0,0,0} };
	public:

		TEST_METHOD(TestMatriceAdjacenceSansaArgument) {
			Graphe::MatriceAdjacence Mat{};
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(0, Mat.nbSommets(),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(0, Mat.nbArc(),message);
		}

		TEST_METHOD(TestMatriceAdjacenceAvecUnAlea) {
			alea aleatoire(1, 10);
			Graphe::MatriceAdjacence Mat{ aleatoire };
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(aleatoire.val_alea(), Mat.nbSommets(),message);
			int TestNbNoeud = 0;
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i,j);
					Assert::IsTrue(Mat.valeurMatrice(i, j) == 0 || Mat.valeurMatrice(i, j) == 1,message);
					if (Mat.valeurMatrice(i,j) == 1) TestNbNoeud++;
				}
			}
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(TestNbNoeud, Mat.nbArc());
		}

		TEST_METHOD(TestMatriceAdjacenceAvecUnInt) {
			Graphe::MatriceAdjacence Mat{ NbNoeud };
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud, Mat.nbSommets(),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(0, Mat.nbArc(),message);
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(0, Mat.valeurMatrice(i, j),message);
				}
			}
		}

		TEST_METHOD(TestMatriceAdjacenceAvecTroisArgument) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud, Mat.nbSommets(),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(),message);
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(M[i][j], Mat.valeurMatrice(i,j), message);
				}
			}
		}

		TEST_METHOD(TestMatriceAdjacenceAvecFsApsEnArgument) {
			Graphe::FsAps testFsAps{ NbNoeud, fs, NbArc, aps };
			Graphe::MatriceAdjacence Mat{ testFsAps };
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud, Mat.nbSommets(),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(),message);
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(M[i][j], Mat.valeurMatrice(i, j), message);
				}
			}
		}

		TEST_METHOD(TestMatriceAdjacenceAvecFichier) {
			Graphe::MatriceAdjacence Mat{"ReponseMatriceAdjacence"};
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(), message);
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(M[i][j], Mat.valeurMatrice(i, j), message);
				}
			}
		}

		TEST_METHOD(TestajouteSommet) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.ajouteSommet();
			wchar_t message[512];
			for (int i = 0; i < NbNoeud; i++) {
				for (int j = 0; j < NbNoeud; j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(M[i][j], Mat.valeurMatrice(i, j),message);
				}
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, NbNoeud);
				Assert::AreEqual(0, Mat.valeurMatrice(i, NbNoeud),message);
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d",NbNoeud, i);
				Assert::AreEqual(0, Mat.valeurMatrice(NbNoeud,i),message);
			}
			Assert::AreEqual(0, Mat.valeurMatrice(NbNoeud, NbNoeud));
		}

		TEST_METHOD(TestsupprimeSommet) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.supprimeSommet(0);
			wchar_t message[512];
			int TestNbArc = 0;
			for (int i = 0; i < NbNoeud - 1; i++) {
				for (int j = 0; j < NbNoeud - 1; j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(M[i + 1][j + 1], Mat.valeurMatrice(i, j), message);
					if (Mat.valeurMatrice(i, j) == 1) TestNbArc++;
				}
			}
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud-1, Mat.nbSommets(), message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(TestNbArc, Mat.nbArc(), message);
		}

		TEST_METHOD(TestajouterArc) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.ajouterArc(1, 1);
			wchar_t message[512];
			swprintf(message, L"L'arc n'a pas ete ajoute");
			Assert::AreEqual(1, Mat.valeurMatrice(1, 1),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc + 1, Mat.nbArc(),message);
			Mat.ajouterArc(1, 1);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc + 1, Mat.nbArc(),message);/// On test pour voir si on n'incrémente pas nbArc
			swprintf(message, L"L'arc a ete modifie");
			Assert::AreEqual(1, Mat.valeurMatrice(1, 1),message);
		}

		TEST_METHOD(TestsupprimerArc) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.ajouterArc(1, 1);/// On cree un arc pour etre sur de son existence puis on le supprime
			Mat.supprimerArc(1, 1);
			wchar_t message[512];
			swprintf(message, L"L'arc n'a pas ete supprimer");
			Assert::AreEqual(0, Mat.valeurMatrice(1, 1));
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(),message);/// On test pour voir si tout est à nouveau normal	
			Mat.supprimerArc(1, 1);
			swprintf(message, L"L'arc a ete modifie");
			Assert::AreEqual(0, Mat.valeurMatrice(1, 1));
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(), message);
		}

		TEST_METHOD(TestsetMatrice) {
			Graphe::MatriceAdjacence Mat{ NbNoeud };
			Mat.setMatrice(M);
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud, Mat.nbSommets(),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(),message);
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(M[i][j], Mat.valeurMatrice(i, j), message);
				}
			}
		}

		TEST_METHOD(Testinverse) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.inverse();
			wchar_t message[512];
			swprintf(message, L"Le nombre de sommet est faux");
			Assert::AreEqual(NbNoeud, Mat.nbSommets(),message);
			swprintf(message, L"Le nombre d'arc est faux");
			Assert::AreEqual(NbArc, Mat.nbArc(),message);
			for (int i = 0; i < Mat.nbSommets(); i++) {
				for (int j = 0; j < Mat.nbSommets(); j++) {
					swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
					Assert::AreEqual(inv_M[i][j], Mat.valeurMatrice(i, j), message);
				}
			}
		}

	TEST_METHOD(TestenregistrerMatriceAdjacence) {
		Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
		std::ofstream os("fichier.txt");
		Mat.enregistrerMatrice(os);
		os.close();
		std::ifstream fileRep("ReponseMatriceAdjacence.txt");
		std::ifstream fileAverifier("fichier.txt");
		wchar_t message[512];
		swprintf(message, L"Le fichier généré est incorrect");
		Assert::IsTrue(compareFile(fileRep, fileAverifier),message);
	}

	TEST_METHOD(TestrecupererMatriceAdjacence) {
		Graphe::MatriceAdjacence Mat{};
		std::ifstream file("ReponseMatriceAdjacence.txt");
		Mat.recupererMatrice(file);
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = 0; j < Mat.nbSommets(); j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(M[i][j], Mat.valeurMatrice(i, j), message);
			}
		}
	}

	};

	TEST_CLASS(TestMatriceAdjacenceValuee) {
private:
	const int INFINI = INT_MAX;
	std::vector<std::vector<int>> MValuee{ {INFINI,1,1,INFINI,1,INFINI,INFINI},
										   {INFINI,INFINI,1,INFINI,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,1,1,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,INFINI,INFINI,1,1,INFINI},
										   {INFINI,INFINI,1,INFINI,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,INFINI,INFINI,INFINI,INFINI,INFINI},
										   {INFINI,INFINI,INFINI,1,INFINI,1,INFINI} };
	std::vector<std::vector<int>> inv_M{ {0,0,0,0,0,0,0},
										 {1,0,0,0,0,0,0},
										 {1,1,1,0,1,0,0},
										 {0,0,1,0,0,0,1},
										 {1,0,0,1,0,0,0},
										 {0,0,0,1,0,0,1},
										 {0,0,0,0,0,0,0} };
	std::vector<std::vector<int>> inv_MValuee{ {INFINI,INFINI,INFINI,INFINI,INFINI,INFINI,INFINI},
											   {1,INFINI,INFINI,INFINI,INFINI,INFINI,INFINI},
											   {1,1,1,INFINI,1,INFINI,INFINI},
											   {INFINI,INFINI,1,INFINI,INFINI,INFINI,1},
											   {1,INFINI,INFINI,1,INFINI,INFINI,INFINI},
											   {INFINI,INFINI,INFINI,1,INFINI,INFINI,1},
											   {INFINI,INFINI,INFINI,INFINI,INFINI,INFINI,INFINI} };

public:
	TEST_METHOD(TestMatriceAdjacenceValueeSansArgument) {
		Graphe::MatriceAdjacenceValuee Mat{};
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(0, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(0, Mat.nbArc(), message);
	}

	TEST_METHOD(TestMatriceAdjacenceValueeAvecUnAlea) {
		alea aleatoire(1, 10);
		int borne = 2048;
		Graphe::MatriceAdjacenceValuee Mat{ aleatoire ,borne,-borne};
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(aleatoire.val_alea(), Mat.nbSommets(), message);
		int TestNbNoeud = 0;
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = 0; j < Mat.nbSommets(); j++) {
				swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, j);
				Assert::IsTrue((Mat.valeurMatrice(i,j)<=borne&& Mat.valeurMatrice(i, j) >= -borne && ((MatriceAdjacence)Mat).valeurMatrice(i, j) == 1)||(Mat.valeurMatrice(i,j)==INFINI && ((MatriceAdjacence)Mat).valeurMatrice(i, j) == 0), message);
				//Le test vérifie si l'arc de la matrice est crée dans le bon intervalle et si l'arc de la MaticeAdjacence associé a été crée ou si l'arc n'existe pas que l'arc de la MaticeAdjacence associé n'a pas été crée
				if (((MatriceAdjacence)Mat).valeurMatrice(i, j) == 1) TestNbNoeud++;
			}
		}
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(TestNbNoeud, Mat.nbArc());
	}

	TEST_METHOD(TestMatriceAdjacenceValueeAvecUnInt) {
		Graphe::MatriceAdjacenceValuee Mat{ NbNoeud };
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(0, Mat.nbArc(), message);
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = 0; j < Mat.nbSommets(); j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(0, ((MatriceAdjacence)Mat).valeurMatrice(i, j), message);
				swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(INFINI, Mat.valeurMatrice(i, j), message);
			}
		}
	}

	TEST_METHOD(TestMatriceAdjacenceAvecTroisArgument) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);
		for (int i = 0; i < NbNoeud; i++) {
			swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d", i);
			Assert::AreEqual(M[i],((MatriceAdjacence)Mat).sommet(i), message);
			swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d", i);
			Assert::AreEqual(MValuee[i], Mat.sommet(i), message);
		}
	}

	TEST_METHOD(TestsansValeurNegative) {
		Graphe::MatriceAdjacenceValuee Mat{NbNoeud};
		wchar_t message[512];
		swprintf(message, L"La matrice d'adjacence valuee doit ne pas contenir de valeurs négatives");
		Assert::IsTrue(Mat.sansValeurNegative(),message);
		Mat.ajouterArc(1, 1, -1);
		swprintf(message, L"La matrice d'adjacence valuee doit contenir des valeurs négatives");
		Assert::IsFalse(Mat.sansValeurNegative(), message);
	}

	TEST_METHOD(TestajouteSommet) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		Mat.ajouteSommet();
		wchar_t message[512];
		for (int i = 0; i < NbNoeud; i++) {
			for (int j = 0; j < NbNoeud; j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(M[i][j], ((MatriceAdjacence)Mat).valeurMatrice(i, j), message);
				swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(MValuee[i][j], Mat.valeurMatrice(i, j), message);
			}
			swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, NbNoeud);
			Assert::AreEqual(0, ((MatriceAdjacence)Mat).valeurMatrice(i, NbNoeud), message);
			swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, NbNoeud);
			Assert::AreEqual(INFINI, Mat.valeurMatrice(i, NbNoeud), message);
			swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", NbNoeud, i);
			Assert::AreEqual(0, ((MatriceAdjacence)Mat).valeurMatrice(NbNoeud, i), message);
			swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", NbNoeud, i);
			Assert::AreEqual(INFINI, Mat.valeurMatrice(NbNoeud, i), message);
		}
		swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", NbNoeud, NbNoeud);
		Assert::AreEqual(0, ((MatriceAdjacence)Mat).valeurMatrice(NbNoeud, NbNoeud),message);
		swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", NbNoeud, NbNoeud);
		Assert::AreEqual(INFINI, Mat.valeurMatrice(NbNoeud, NbNoeud), message);
	}

	TEST_METHOD(TestsupprimeSommet) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		Mat.supprimeSommet(0);
		wchar_t message[512];
		int TestNbArc = 0;
		for (int i = 0; i < NbNoeud - 1; i++) {
			for (int j = 0; j < NbNoeud - 1; j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(M[i + 1][j + 1], ((MatriceAdjacence)Mat).valeurMatrice(i, j), message);
				swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(MValuee[i + 1][j + 1], Mat.valeurMatrice(i, j), message);
				if (Mat.valeurMatrice(i, j) != INFINI) TestNbArc++;
			}
		}
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud - 1, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(TestNbArc, Mat.nbArc(), message);
	}

	TEST_METHOD(TestajouterArc) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		int valeur = 24;
		Mat.ajouterArc(1, 1,valeur);
		wchar_t message[512];
		swprintf(message, L"L'arc n'a pas ete ajoute à MatriceAdjacence");
		Assert::AreEqual(1, ((MatriceAdjacence)Mat).valeurMatrice(1, 1), message);
		swprintf(message, L"L'arc n'a pas la bonne valeur");
		Assert::AreEqual(valeur, Mat.valeurMatrice(1, 1), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc + 1, Mat.nbArc(), message);
		int newvaleur = 89;
		Mat.ajouterArc(1, 1,newvaleur);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc + 1, Mat.nbArc(), message);/// On test pour voir si on n'incrémente pas nbArc
		swprintf(message, L"L'arc a ete modifie");
		Assert::AreEqual(1, ((MatriceAdjacence)Mat).valeurMatrice(1, 1), message);
		swprintf(message, L"L'arc n'a pas la bonne valeur");
		Assert::AreEqual(newvaleur, Mat.valeurMatrice(1, 1), message);
		Mat.ajouterArc(1, 1, newvaleur);/// On test pour voir si en rajoutant un arc avec la même valeur provoque des dysfonctionnements
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc + 1, Mat.nbArc(), message);/// On test pour voir si on n'incrémente pas nbArc
		swprintf(message, L"L'arc a ete modifie");
		Assert::AreEqual(1, ((MatriceAdjacence)Mat).valeurMatrice(1, 1), message);
		swprintf(message, L"L'arc n'a pas la bonne valeur");
		Assert::AreEqual(newvaleur, Mat.valeurMatrice(1, 1), message);
	}

	TEST_METHOD(TestsupprimerArc) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		int valeur = 24;
		Mat.ajouterArc(1, 1,valeur);/// On cree un arc pour etre sur de son existence puis on le supprime
		Mat.supprimerArc(1, 1);
		wchar_t message[512];
		swprintf(message, L"L'arc n'a pas ete supprimer dans MatriceAdjacence");
		Assert::AreEqual(0, ((MatriceAdjacence)Mat).valeurMatrice(1, 1));
		swprintf(message, L"L'arc n'a pas ete supprimer dans MatriceAdjacenceValuee");
		Assert::AreEqual(INFINI, Mat.valeurMatrice(1, 1), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);/// On test pour voir si tout est à nouveau normal	
		Mat.supprimerArc(1, 1);
		swprintf(message, L"L'arc a ete modifie");
		Assert::AreEqual(0, ((MatriceAdjacence)Mat).valeurMatrice(1, 1));
		swprintf(message, L"L'arc n'a pas ete supprimer dans MatriceAdjacenceValuee");
		Assert::AreEqual(INFINI, Mat.valeurMatrice(1, 1), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);
	}

	TEST_METHOD(TestsetMatrice) {
		Graphe::MatriceAdjacenceValuee Mat{ NbNoeud };
		Mat.setMatrice(MValuee);
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = 0; j < Mat.nbSommets(); j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(M[i][j], ((MatriceAdjacence)Mat).valeurMatrice(i, j), message);
				swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(MValuee[i][j], Mat.valeurMatrice(i, j), message);
			}
		}
	}

	TEST_METHOD(Testinverse) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		Mat.inverse();
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = 0; j < Mat.nbSommets(); j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(inv_M[i][j], ((MatriceAdjacence)Mat).valeurMatrice(i, j), message);
				swprintf(message, L"La matrice d'adjacence valuee est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(inv_MValuee[i][j], Mat.valeurMatrice(i, j), message);
			}
		}
	}

	TEST_METHOD(TestenregistrerMatrice) {
		Graphe::MatriceAdjacenceValuee Mat{ MValuee,NbNoeud,NbArc };
		std::ofstream os("fichier.txt");
		Mat.enregistrerMatrice(os);
		os.close();
		std::ifstream fileRep("ReponseMatriceAdjacenceValuee.txt");
		std::ifstream fileAverifier("fichier.txt");
		wchar_t message[512];
		swprintf(message, L"Le fichier généré est incorrect");
		Assert::IsTrue(compareFile(fileRep, fileAverifier), message);
	}

	TEST_METHOD(TestrecupererMatrice) {
		Graphe::MatriceAdjacence Mat{};
		std::ifstream file("ReponseMatriceAdjacenceValuee.txt");
		Mat.recupererMatrice(file);
		wchar_t message[512];
		swprintf(message, L"Le nombre de sommet est faux");
		Assert::AreEqual(NbNoeud, Mat.nbSommets(), message);
		swprintf(message, L"Le nombre d'arc est faux");
		Assert::AreEqual(NbArc, Mat.nbArc(), message);
		for (int i = 0; i < Mat.nbSommets(); i++) {
			for (int j = 0; j < Mat.nbSommets(); j++) {
				swprintf(message, L"La matrice d'adjacence est fausse à la ligne %d, la colonne %d", i, j);
				Assert::AreEqual(M[i][j], Mat.valeurMatrice(i, j), message);
			}
		}
	}

};

	TEST_CLASS(TestDistance) {
private:
	std::vector<std::vector<int>> rep{ {NbNoeud,NbArc},
									  {NbNoeud, 0, 1, 1, 2, 1, 3,-1},
									  {NbNoeud,-1, 0, 1, 2, 3, 3,-1},
									  {NbNoeud,-1,-1, 0, 1, 2, 2,-1},
									  {NbNoeud,-1,-1, 2, 0, 1, 1,-1},
									  {NbNoeud,-1,-1, 1, 2, 0, 3,-1},
									  {NbNoeud,-1,-1,-1,-1,-1, 0,-1},
									  {NbNoeud,-1,-1, 3, 1, 2, 1, 0} };
public:
	TEST_METHOD(TestDistanceAvecFsAps) {
		Graphe::FsAps testFsAps{ NbNoeud, fs,NbArc,aps };
		Graphe::Distance testDist{ testFsAps };
		for (int i = 0; i < NbNoeud; i++) {
			wchar_t message[512];
			swprintf(message, L"la matrice est fausse à l'iter: %d ", i);
			Assert::AreEqual(rep[i], testDist.Sommet(i), message);
		}
	}

	TEST_METHOD(TestDistanceAvecMatriceAdjacence) {
		Graphe::MatriceAdjacence testMat{ M,NbNoeud,NbArc };
		Graphe::Distance testDist{ testMat };
		for (int i = 0; i < NbNoeud; i++) {
			wchar_t message[512];
			swprintf(message, L"la matrice est fausse à l'iter: %d ", i);
			Assert::AreEqual(rep[i], testDist.Sommet(i), message);
		}
	}
	};
}