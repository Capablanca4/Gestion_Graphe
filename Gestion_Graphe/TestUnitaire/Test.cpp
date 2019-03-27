#include "stdafx.h"
#include "SpecialisationTest.h"
#include "CppUnitTest.h"
#include "../Gestion_Graphe/include/MatriceAdjacence.h"
#include "../Gestion_Graphe/include/FsAps.h"
#include "../Gestion_Graphe/include/Distance.h"
#include "../Gestion_Graphe/include/Rang.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Graphe
{		
	/// Variable Globale pour les tests
	int NbNoeud = 7,NbArc = 18;
	std::vector<std::vector<int>> M{ {0,1,1,0,1,0,0},
									 {0,0,1,0,0,0,0},
									 {0,0,1,1,0,0,0},
									 {0,0,0,0,1,1,0},
									 {0,0,1,0,0,0,0},
									 {0,0,0,0,0,0,0},
									 {0,0,0,1,0,1,0} };
	std::vector<int> fs{ 2,3,5,0,3,0,3,4,0,5,6,0,3,0,0,4,6,0 };
	std::vector<int> aps{ 0,4,6,9,12,14,15 };

	TEST_CLASS(TestMatriceAdjacence)
	{
	private :
		std::vector<std::vector<int>> inv_M{ {0,0,0,0,0,0,0},
											 {1,0,0,0,0,0,0},
											 {1,1,1,0,1,0,0},
											 {0,0,1,0,0,0,1},
											 {1,0,0,1,0,0,0},
											 {0,0,0,1,0,0,1},
											 {0,0,0,0,0,0,0} };
	public:

		TEST_METHOD(TestMatriceAdjacenceSansaArgument){
			Graphe::MatriceAdjacence Mat{};
			Assert::AreEqual(0,Mat.nbSommets());
			Assert::AreEqual(0,Mat.nbArc() );
		}

		TEST_METHOD(TestMatriceAdjacenceAvecUnArgument){
			Graphe::MatriceAdjacence Mat{ NbNoeud };
			Assert::AreEqual(NbNoeud,Mat.nbSommets());
			Assert::AreEqual(0,Mat.nbArc() );
			std::vector<int>* ptr = new std::vector<int>{};
			for (int j = 0; j < NbNoeud; j++)  ptr->push_back(0);
			for (int i = 0; i < NbNoeud; i++) Assert::AreEqual(*ptr,Mat.Sommet(i) );
			delete ptr;
		}

		TEST_METHOD(TestMatriceAdjacenceAvecTroisArgument){
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Assert::AreEqual(NbNoeud,Mat.nbSommets());
			Assert::AreEqual(NbArc,Mat.nbArc() );
			for (int i = 0; i < NbNoeud; i++) {
				Assert::AreEqual(M[i] ,Mat.Sommet(i) );
			}
		}

		TEST_METHOD(TestMatriceAdjacenceAvecFsApsEnArgument) { 
			Graphe::FsAps testFsAps{ NbNoeud, fs, NbArc, aps };
			Graphe::MatriceAdjacence Mat{ testFsAps };
			Assert::AreEqual(NbNoeud,Mat.nbSommets());
			Assert::AreEqual(NbArc,Mat.nbArc() );
			for (int i = 0; i < NbNoeud; i++) {
				wchar_t message[512];
				swprintf(message, L"M est faux à l'iter: %d", i );
				Assert::AreEqual(M[i], Mat.Sommet(i),message);
			}
		}

		TEST_METHOD(TestAjouteArc) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.AjouteArc(1, 1);
			Assert::AreEqual(1,Mat.Sommet(1)[1] );///On test si l'élément est bien ajouter
			Assert::AreEqual(NbArc + 1,Mat.nbArc() );
			Mat.AjouteArc(1, 1);
			Assert::AreEqual(NbArc + 1,Mat.nbArc() );/// On test pour voir si on n'incrémente pas nbArc
		}

		TEST_METHOD(TestAjouteNoeud) {
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.AjouteSommet();
			std::vector<int>* ptr = new std::vector<int>{ 0 };
			for (int i = 0; i < NbNoeud; i++) {
				ptr->push_back(0);
				M[i].push_back(0);
				Assert::AreEqual(M[i], Mat.Sommet(i));
			}
			Assert::AreEqual(*ptr,Mat.Sommet(NbNoeud) );
			delete ptr;
		}

		TEST_METHOD(TestInverseAdj){
			Graphe::MatriceAdjacence Mat{ M,NbNoeud,NbArc };
			Mat.inverseAdj();
			Assert::AreEqual(NbNoeud,Mat.nbSommets());
			Assert::AreEqual(NbArc, Mat.nbArc() );
			for (int i = 0; i < NbNoeud; i++) {
				Assert::AreEqual(inv_M[i], Mat.Sommet(i));
			}
		}
		
	};

	TEST_CLASS(TestFsAps) {
	private:
		std::vector<int> fp{ 0,1,0,1,2,3,5,0,3,7,0,1,4,0,4,7,0,0 };
		std::vector<int> app{ 0,1,3,8,11,14,17 };
	public :
		
		TEST_METHOD(TestFsApsAvecUnArgument) {
			Graphe::FsAps test{ NbNoeud };
			Assert::AreEqual(NbNoeud, test.nbSommets());
			Assert::AreEqual(NbNoeud, test.NbArc());
			for (int i = 0; i < NbNoeud; i++) {
				Assert::AreEqual(i,test.AdressePremierSuccesseur(i) );
				Assert::AreEqual(0,test.FileSuivant(i) );
			}
		}

		TEST_METHOD(TestFsApsAvecDeuxArguments) {
			Graphe::FsAps test{ NbNoeud, fs };
			Assert::AreEqual(NbNoeud, test.nbSommets());
			Assert::AreEqual(NbArc, test.NbArc());
			for (int i = 0; i < NbArc; i++) {///Test si Fs est correct
				wchar_t message2[512];
				swprintf(message2, L"Fs est faux à l'iter: %d ", i);
				Assert::AreEqual(fs[i], test.FileSuivant(i), message2);
			}
			for (int i = 0; i < NbNoeud; i++) {///Test si Aps est correct
				wchar_t message1[512];
				swprintf(message1, L"Aps est faux à l'iter: %d ", i);
				Assert::AreEqual(aps[i], test.AdressePremierSuccesseur(i), message1);
			}
		}

		TEST_METHOD(TestFsApsAvecQuatreArguments) {
			Graphe::FsAps test{ NbNoeud, fs,NbArc,aps };
			Assert::AreEqual(NbNoeud, test.nbSommets());
			Assert::AreEqual(NbArc, test.NbArc());
			for (int i = 0; i < NbArc; i++) {///Test si Fs est correct
				wchar_t message2[512];
				swprintf(message2, L"Fs est faux à l'iter: %d ", i);
				Assert::AreEqual(fs[i], test.FileSuivant(i), message2);
			}
			for (int i = 0; i < NbNoeud; i++) {///Test si Aps est correct
				wchar_t message1[512];
				swprintf(message1, L"Aps est faux à l'iter: %d ", i);
				Assert::AreEqual(aps[i], test.AdressePremierSuccesseur(i), message1);
			}
		}

		TEST_METHOD(TestFsApsAvecMatriceAdjacenceEnArgument) {
			Graphe::FsAps testMat{ NbNoeud, fs, NbArc, aps };
			Graphe::FsAps test{ testMat };
			Assert::AreEqual(NbArc,test.NbArc() );
			Assert::AreEqual(NbNoeud,test.nbSommets() );
			for (int i = 0; i < NbArc; i++) {///Test si Fs est correct
				wchar_t message2[512];
				swprintf(message2, L"Fs est faux à l'iter: %d ", i);
				Assert::AreEqual(fs[i], test.FileSuivant(i), message2);
			}
			for (int i = 0; i < NbNoeud; i++) {///Test si Aps est correct
				wchar_t message1[512];
				swprintf(message1, L"Aps est faux à l'iter: %d ", i);
				Assert::AreEqual(aps[i], test.AdressePremierSuccesseur(i), message1);
			}
		}

		TEST_METHOD(TestAjouteArc) {
			Graphe::FsAps test{ NbNoeud, fs };
			test.AjouteArc(1, 4);
			Assert::AreEqual(4,test.FileSuivant(2) );/// La fonction insère au bon endroit l'élément
			Assert::AreEqual(NbArc+1,test.NbArc() );/// La fonction verifie que le nombre d'element de Fs reste correcte
			test.AjouteArc(1, 4);
			Assert::AreEqual(NbArc + 1,test.NbArc() );/// La fonction verifie que l'on n'insere bien aucun element si l'element est deja present
		}

		TEST_METHOD(TestAjouterNoeud) {
			Graphe::FsAps test{ NbNoeud, fs };
			test.AjouteSommet();
			Assert::AreEqual(NbArc+1,test.NbArc() );
			Assert::AreEqual(NbNoeud+1, test.nbSommets() );
			Assert::AreEqual(0,test.FileSuivant(test.NbArc() - 1) );
			Assert::AreEqual(NbArc,test.AdressePremierSuccesseur(test.nbSommets() - 1) );
		}

		TEST_METHOD(TestInverseFsAps) {
			Graphe::FsAps test{ NbNoeud, fs,NbArc,aps };
			test.inverse();
			for (int i = 0; i < NbArc; i++) {/// Fp est cree correctement
			    wchar_t message2[512];				
				swprintf(message2, L"Fp est faux à l'iter: %d ",i);
				Assert::AreEqual(fp[i], test.FileSuivant(i),message2);
			}
			for (int i = 0; i < NbNoeud; i++) {/// App est cree correctement 
				wchar_t message1[512];
				swprintf(message1, L"App est faux à l'iter: %d ", i);
				Assert::AreEqual(app[i], test.AdressePremierSuccesseur(i), message1);
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
				Assert::AreEqual(rep[i], testDist.Sommet(i),message);
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

	TEST_CLASS(TestRang) {
	private:
		std::vector<int> rep{0,0,1,-1,-1,-1,-1,0};
	public:
		TEST_METHOD(TestRangAvecFsAps) {
			Graphe::FsAps testFsAps{ NbNoeud, fs,NbArc,aps };
			Graphe::Rang TestRang{ testFsAps };
			for (int i = 0; i < NbNoeud; i++) {
				wchar_t message[512];
				swprintf(message, L"le rang est faux à l'iter: %d ", i);
				Assert::AreEqual(rep[i], TestRang.Sommet(i), message);
			}
		}
		TEST_METHOD(TestRangAvecMatriceAdjacence) {
			Graphe::MatriceAdjacence testMat{ M,NbNoeud,NbArc };
			Graphe::Rang TestRang{ testMat };
			for (int i = 0; i < NbNoeud; i++) {
				wchar_t message[512];
				swprintf(message, L"le rang est faux à l'iter: %d ", i);
				Assert::AreEqual(rep[i], TestRang.Sommet(i), message);
			}
		}
	};
}