#pragma once
namespace Graphe {
	class MatriceAdjacenceValuee;
	class Distance;
	class vector;
	class Djikstra
	{
	public:
		Djikstra(const MatriceAdjacenceValuee & M, Distance & D, std::vector<int>& predecesseur);
		~Djikstra();
	};

}