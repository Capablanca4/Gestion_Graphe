/*#include "doctest.h"
#include "MatriceAdjacence.h"
#include <iostream>

TEST_CASE("Test des methodes de MatriceAdjacence"){
    int nbNoeud=7;
    int nbArc=18;
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
    SUBCASE("La methode MatriceAdjacence() est correcte"){

        SUBCASE("La methode MatriceAdjacence(); est correcte"){
            Graphe::MatriceAdjacence Mat{};
            REQUIRE_EQ(Mat.nbNoeud(),0);
            REQUIRE_EQ(Mat.nbArc(),0);
        }

        SUBCASE("La methode MatriceAdjacence(int nbNoeud) est correcte"){
            Graphe::MatriceAdjacence Mat{nbNoeud};
            REQUIRE_EQ(Mat.nbNoeud(),nbNoeud);
            REQUIRE_EQ(Mat.nbArc(),0);
            std::vector<int>* ptr = new std::vector<int>{};
            for(int j=0;j<nbNoeud;j++)  ptr->push_back(0);
            for(int i=1;i<=nbNoeud;i++){
               REQUIRE_EQ(Mat.Noeud(i),*ptr);
            }
        }

        SUBCASE("La methode MatriceAdjacence(vector<vector<int>> matrice,int nbNoeud,int nbArc) est correcte"){
            Graphe::MatriceAdjacence Mat{M,nbNoeud,nbArc};
            REQUIRE_EQ(Mat.nbNoeud(),nbNoeud);
            REQUIRE_EQ(Mat.nbArc(),nbArc);
            for(int i =1;i<=nbNoeud;i++){
                REQUIRE_EQ(M[i-1],Mat.Noeud(i));
            }
        }
    }

    SUBCASE("La methode AjouteElement() est correcte"){

        SUBCASE("La methode AjouteElement() est correcte dans le cas general"){
            Graphe::MatriceAdjacence Mat{M,nbNoeud,nbArc};
            Mat.AjouteArc(1,1);
            REQUIRE_EQ(Mat.Noeud(1)[0],1);
        }

        SUBCASE("La methode AjouteElement() est correcte dans le cas ou l'element est deja present"){
            Graphe::MatriceAdjacence Mat{M,nbNoeud,nbArc};
            Mat.AjouteArc(1,2);
            REQUIRE_EQ(Mat.Noeud(1)[1],1);
        }
    }

    SUBCASE("La methode AjouteNoeud() est correcte"){
        Graphe::MatriceAdjacence Mat{M,nbNoeud,nbArc};
        Mat.AjouteNoeud();
        std::vector<int>* ptr = new std::vector<int>{0};
        for(int i=0;i<nbNoeud;i++){
            ptr->push_back(0);
            M[i].push_back(0);
            REQUIRE_EQ(M[i],Mat.Noeud(i+1));
        }
        REQUIRE_EQ(Mat.Noeud(nbNoeud+1),*ptr);
    }

    SUBCASE("La methode inverseAdj() est correcte"){
        Graphe::MatriceAdjacence Mat{M,nbNoeud,nbArc};
        Mat.inverseAdj();
        REQUIRE_EQ(Mat.nbNoeud(),nbNoeud);
        REQUIRE_EQ(Mat.nbArc(),nbArc);
        for(int i =1;i<=nbNoeud;i++){
            REQUIRE_EQ(inv_M[i-1],Mat.Noeud(i));
        }
    }
}
*/