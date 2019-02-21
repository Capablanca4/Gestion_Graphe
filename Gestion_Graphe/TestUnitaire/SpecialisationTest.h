#pragma once
#include "CppUnitTest.h"
#include "../Gestion_Graphe/include/FsAps.h"
#include "../Gestion_Graphe/include/MatriceAdjacence.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Graphe::FsAps>(const class Graphe::FsAps& t) { return L"referenceFsAps"; };
			template<> static std::wstring ToString<Graphe::MatriceAdjacence>(const class Graphe::MatriceAdjacence& t) { return L"pointeurFsAps"; };
			template<> static std::wstring ToString<Graphe::FsAps>(const class Graphe::FsAps* t) { return L"referenceMatriceAdjacence"; }
			template<> static std::wstring ToString<Graphe::MatriceAdjacence>(const class Graphe::MatriceAdjacence* t) { return L"pointeurMatriceAdjacence"; };
			template<> static std::wstring ToString<std::vector<int>>(const class std::vector<int>* t) { return L"pointeurVector"; }
			template<> static std::wstring ToString<std::vector<int>>(const class std::vector<int>& t) { return L"referenceVector"; };
		}
	}
}
