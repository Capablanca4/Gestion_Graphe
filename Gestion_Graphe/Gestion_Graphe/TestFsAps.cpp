#include "../Gestion_Graphe/include/FsAps.h"
#include "../Gestion_Graphe/include/MatriceAdjacence.h"
#include "iostream"

/*TEST_CASE("Les methodes de FsAps sont correctes"){
    int nbNoeud=7;
    int NbArc=18;
    std::vector<int> fs{2,3,5,0,3,0,3,4,0,5,6,0,3,0,0,4,6,0};
    std::vector<int> aps{0,4,6,9,12,14,15};

    SUBCASE("Les constructeurs sont correctes"){

        SUBCASE("Le constructeur FsAps(int nbNoeud) est correcte"){
            Graphe::FsAps test = Graphe::FsAps(nbNoeud);
            REQUIRE_EQ(nbNoeud,test.NbNoeud());
            REQUIRE_EQ(nbNoeud,test.NbArc());
            for(int i=0;i<nbNoeud;i++){
                REQUIRE_EQ(test.Aps(i),i);
                REQUIRE_EQ(test.Fs(i),0);
            }
        }

        SUBCASE("Le constructeur FsAps(int nbNoeud,const std::vector<int>& fs) est correcte"){
            Graphe::FsAps test = Graphe::FsAps(nbNoeud,fs);
            REQUIRE_EQ(nbNoeud,test.NbNoeud());
            REQUIRE_EQ(NbArc,test.NbArc());
            for(int i=0;i<nbNoeud;i++){
                REQUIRE_EQ(test.Aps(i),aps[i]);
            }
            for(int i=0;i<NbArc;i++){
                REQUIRE_EQ(test.Fs(i),fs[i]);
            }
        }

    }

}*/
