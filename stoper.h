#ifndef STOPER_H
#define STOPER_H
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>
#include <cassert>
#include "graph.h"

float time_calc(int size, double level, std::string alg, std::string rep)
{
	// generowanie 
	srand(time(NULL));
	std::vector<float> time_vec(100,0);
//	for (int tm = 0; tm < 100; ++tm)
	for (int tm = 0; tm < 10; ++tm)
	{
		
		auto start = std::clock(), end = std::clock();
		
		Graph graph(0, size);
		assert(level > 0);
		graph.fill(level);
		if (rep == "matrix")
		{
			graph.fill_adj_matrix();
			if (alg == "Kruskal")
			{
				start = std::clock();
			    graph.Kruskal_alg_matrix();
				end = std::clock();
			}
			if (alg == "Prim")
			{
				start = std::clock();
				graph.Prim_alg_matrix();
				end = std::clock();
			}

		}
		if (rep == "list")
		{
			graph.fill_neigh_list();
			if (alg == "Kruskal")
			{
				start = std::clock();
				graph.Kruskal_alg_list();
				end = std::clock();
			}
			if (alg == "Prim")
			{
				start = std::clock();
				graph.Prim_alg_list();
				end = std::clock();
			}
		}
		
		time_vec[tm] = (((float)(end - start)) / CLOCKS_PER_SEC);
	}

	float init(0);
	return std::accumulate(time_vec.begin(), time_vec.end(), init) * 100;
	
}










#endif