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
			template<> static std::wstring ToString<FsAps>(const class FsAps& t) { RETURN_WIDE_STRING(t); };
			template<> static std::wstring ToString<MatriceAdjacence>(const class MatriceAdjacence& t) { RETURN_WIDE_STRING(t); };
			template<> static std::wstring ToString<FsAps>(const class FsAps* t) { RETURN_WIDE_STRING(*t); }
			template<> static std::wstring ToString<MatriceAdjacence>(const class MatriceAdjacence* t) { RETURN_WIDE_STRING(*t) };
		}
	}
}
