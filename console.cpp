#include "include/FsAps.h"
#include "include/MatriceAdjacence.h"
#include "include/MatriceAdjacenceValuee.h"
#include "include/Distance.h"
#include "include/Rang.h"
#include "include/alea.h"
#include <iostream>
#include <fstream>
using namespace std;
void console()
{
	char c;
	cout << "Choisissez un nombre parmi les suivants: " << endl;
	cout << "0: Matrice d'ajacence " << endl;
	cout << "1: Fs et Aps" << endl;
	cout << "2: Distance" << endl;
	cout << "3: Rang " << endl;

	cin >> c;

	if (c == '0')
		fopen("src\MatriceAdjacence.cpp".c_str);
	else
	{
		if (c == '1')
			fopen("src\FsAps.cpp".c_str());
		if (c == '2')
			fopen("src\Distance.cpp".c_str());
		if (c == '3')
			fopen("src\Rang.cpp".c_str());
	}
	
}