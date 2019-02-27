#pragma once
#include "CppUnitTest.h"
#include "../Gestion_Graphe/include/FsAps.h"
#include "../Gestion_Graphe/include/MatriceAdjacence.h"
#include "../Gestion_Graphe/include/Distance.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Graphe::FsAps>(const class Graphe::FsAps& t) { return L"ReferenceFsAps"; };
			template<> static std::wstring ToString<Graphe::MatriceAdjacence>(const class Graphe ::MatriceAdjacence& t) { return L"ReferenceMatriceAdjacence"; };
			template<> static std::wstring ToString<Graphe::Distance>(const class Graphe::Distance& t) { return L"ReferenceDistance"; };
			template<> static std::wstring ToString<Graphe::FsAps>(const class Graphe::FsAps* t) { return L"PointeurFsAps"; }
			template<> static std::wstring ToString<Graphe::MatriceAdjacence>(const class Graphe::MatriceAdjacence* t) { return L"PointeurMatriceAdjacence"; };
			template<> static std::wstring ToString<Graphe::Distance>(const class Graphe::Distance* t) { return L"PointeurDistance"; };
			template<> static std::wstring ToString<std::vector<int, class std::allocator<int> > >(const class std::vector<int,class std::allocator<int> >& t) { return L"ReferenceVectorInt"; };
			

		}
	}
}
