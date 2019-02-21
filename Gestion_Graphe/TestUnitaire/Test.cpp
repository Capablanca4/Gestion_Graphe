#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Graphe
{		
	TEST_CLASS(TestMatriceAdjacence)
	{
	private :
	int nbNoeud = 7;
		int nbArc = 18;
		std::vector<std::vector<int>> M{ {0,1,1,0,1,0,0},
										 {0,0,1,0,0,0,0},
										 {0,0,1,1,0,0,0},
										 {0,0,0,0,1,1,0},
										 {0,0,1,0,0,0,0},
										 {0,0,0,0,0,0,0},
										 {0,0,0,1,0,1,0} };
		std::vector<std::vector<int>> inv_M{ {0,0,0,0,0,0,0},
											 {1,0,0,0,0,0,0},
											 {1,1,1,0,1,0,0},
											 {0,0,1,0,0,0,1},
											 {1,0,0,1,0,0,0},
											 {0,0,0,1,0,0,1},
											 {0,0,0,0,0,0,0} };
	public:

		TEST_METHOD(TestMatriceAdjacence1){
			Graphe::MatriceAdjacence Mat{};
			Assert::AreEqual(Mat.nbNoeud(), 0);
			Assert::AreEqual(Mat.nbArc(), 0);
		}

		TEST_METHOD(TestMatriceAdjacence2){
			Graphe::MatriceAdjacence Mat{ nbNoeud };
			Assert::AreEqual(Mat.nbNoeud(), nbNoeud);
			Assert::AreEqual(Mat.nbArc(), 0);
			std::vector<int>* ptr = new std::vector<int>{};
			for (int j = 0; j < nbNoeud; j++)  ptr->push_back(0);
			for (int i = 1; i <= nbNoeud; i++) {
				Assert::AreEqual(Mat.Noeud(i), *ptr);
			}
			delete ptr;
		}

		TEST_METHOD(TestMatriceAdjacence3){
			Graphe::MatriceAdjacence Mat{ M,nbNoeud,nbArc };
			Assert::AreEqual(Mat.nbNoeud(), nbNoeud);
			Assert::AreEqual(Mat.nbArc(), nbArc);
			for (int i = 0; i < nbNoeud; i++) {
				Assert::AreEqual(M[i] ,Mat.Noeud(i) );
			}
		}

		TEST_METHOD(TestAjouteArc) {
			Graphe::MatriceAdjacence Mat{ M,nbNoeud,nbArc };
			Mat.AjouteArc(1, 1);
			Assert::AreEqual(Mat.Noeud(1)[1], 1);///On test si l'élément est bien ajouter
			Assert::AreEqual(Mat.nbArc(), nbArc + 1);
			Mat.AjouteArc(1, 1);
			Assert::AreEqual(Mat.nbArc(), nbArc + 1);/// On test pour voir si on n'incrémente pas nbArc
		}

		TEST_METHOD(TestAjouteNoeud) {
			Graphe::MatriceAdjacence Mat{ M,nbNoeud,nbArc };
			Mat.AjouteNoeud();
			std::vector<int>* ptr = new std::vector<int>{ 0 };
			for (int i = 0; i < nbNoeud; i++) {
				ptr->push_back(0);
				M[i].push_back(0);
				Assert::AreEqual(M[i], Mat.Noeud(i));
			}
			Assert::AreEqual(Mat.Noeud(nbNoeud + 1), *ptr);
			delete ptr;
		}

		TEST_METHOD(TestinverseAdj){
			Graphe::MatriceAdjacence Mat{ M,nbNoeud,nbArc };
			Mat.inverseAdj();
			Assert::AreEqual(Mat.nbNoeud(), nbNoeud);
			Assert::AreEqual(Mat.nbArc(), nbArc);
			for (int i = 0; i < nbNoeud; i++) {
				Assert::AreEqual(inv_M[i], Mat.Noeud(i));
			}
		}
		
	};

	TEST_CLASS(TestFsAps) {
	private :
		int nbNoeud = 7;
		int NbArc = 18;
		std::vector<int> fs{ 2,3,5,0,3,0,3,4,0,5,6,0,3,0,0,4,6,0 };
		std::vector<int> aps{ 0,4,6,9,12,14,15 };
	public :
		
		TEST_METHOD(TestFsAps1) {
			Graphe::FsAps test = Graphe::FsAps(nbNoeud);
			Assert::AreEqual(nbNoeud, test.NbNoeud());
			Assert::AreEqual(nbNoeud, test.NbArc());
			for (int i = 0; i < nbNoeud; i++) {
				Assert::AreEqual(test.Aps(i), i);
				Assert::AreEqual(test.Fs(i), 0);
			}
		}

		TEST_METHOD(TestFsAps2) {
			Graphe::FsAps test = Graphe::FsAps(nbNoeud, fs);
			Assert::AreEqual(nbNoeud, test.NbNoeud());
			Assert::AreEqual(NbArc, test.NbArc());
			for (int i = 0; i < nbNoeud; i++) {
				Assert::AreEqual(test.Aps(i), aps[i]);/// Aps est créer correctement 
				Assert::AreEqual(test.Fs(i), fs[i]);/// Fs est copier correctement
			}
			for (int i = nbNoeud; i < NbArc; i++) {
				Assert::AreEqual(test.Fs(i), fs[i]);
			}
		}

	};
}