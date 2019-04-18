#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/Rang.h"
#include "include/alea.h"
#include <iostream>
#include <fstream>
using namespace std;
//on suppose que le graphe ne contient pas de cycles 
void Kruskal(FsAps f)
{
	int* v = new int[nbsommets + 1];
	for (int i = 1; i < nbsommets; i++)
	{
		for (j = i; (k = f[j]) != 0; j++)
		{
			v[i] = k;
		}
	}
}