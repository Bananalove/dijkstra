#include "graph.h"
#include <iostream>
#include <iomanip>

/*
plik definiuje algorytmy Prim i Kruskal
*/
	/************************************* Algorytm Prima ********************************************************************/

	void Graph::Prim_alg_list()
{
	if (directed)
	{
		throw Directed("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
	}
	mst.clear();

	std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;

	
	std::vector<bool> visited(numV, false);
	int Vnow = Vstart;
	visited[Vnow] = true;
	for (int i = 1; i < numV; ++i)
	{

		for (auto iter = neigh_list[Vnow].begin(), stop = neigh_list[Vnow].end(); iter != stop; ++iter)
		{

			if (visited[std::get<0>(*iter)] == false)
			{
				queue.push(std::make_tuple(Vnow, std::get<0>(*iter), std::get<1>(*iter)));
			}
		}
		auto shortest = queue.top();
		queue.pop();
		while (visited[std::get<1>(shortest)] == true && !queue.empty())
		{
			shortest = queue.top();
			queue.pop();
		}
		mst.push_back(shortest);
		visited[std::get<1>(shortest)] = true;
		visited[std::get<0>(shortest)] = true;
		Vnow = std::get<1>(shortest);
	}

}

	int Graph::min_span_tree_weight()
	{
		if (mst.empty())
		{
			return 0;
		}
		int mstw = 0;
		for (auto iter = mst.begin(), stop = mst.end(); iter != stop; ++iter)
		{
			mstw += std::get<2>(*iter);
		}
	
		return mstw;
	}

	/*************************************************************************************************************************/
	void Graph::Prim_alg_matrix()
	{

	if (directed) 
	{
		throw Directed ("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
	}
	mst.clear();
	std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;

		
	std::vector<bool> visited(numV, false);
	int Vnow = 0;
	visited[Vnow] = true;

	for (int i = 1; i < numV; ++i)
	{

		for (int u = 0; u < numV; ++u) // dla wszystkich sasiadow danego wierzcholka
		{
			if (adj_matrix[Vnow][u] != constants::no_edge)
			{
				if (visited[u] == false)
				{
					queue.push(std::make_tuple(Vnow, u, adj_matrix[Vnow][u]));
				}
			}
		}
		auto shortest = queue.top();
		queue.pop();
		while (visited[std::get<1>(shortest)] == true && !queue.empty())
		{
			shortest = queue.top();
			queue.pop();
		}
		mst.push_back(shortest);
		visited[std::get<1>(shortest)] = true;
		
	//	std::cout << "Krawedz :" << std::get<0>(shortest) << " " << std::get<1>(shortest) << " " << std::get<2>(shortest) << " \n";
		
		visited[std::get<0>(shortest)] = true;
		Vnow = std::get<1>(shortest);
	}

}

	/**************************************** Algorytm Kruskala **************************************************************/

	void Graph::Kruskal_alg_list()
	{
		if (directed)
		{
			throw Directed("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
		}
		mst.clear();
		// wektor bazy zbiorow rozlacznch
		std::vector<int> zbior(numV);
		// kolejka krawedzi
		std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;
		for (int i = 0; i < numV; ++i) /* umieszczenie krawedzi w kolejce */
		{
			zbior[i] = i;
			for (auto iter = neigh_list[i].begin(), stop = neigh_list[i].end(); iter != stop; ++iter)
			{
				queue.push(std::make_tuple(i, std::get<0>(*iter), std::get<1>(*iter)));
			}
		}



		for (int i = 1; i < numV; ++i) // przegladanie kolejnych wierzcholkow
		{
			auto edge = queue.top();
			queue.pop();
			while (zbior[std::get<0>(edge)] == zbior[std::get<1>(edge)] && !queue.empty()) // czy zbiory sa rozlaczne?
			{
				edge = queue.top();
				queue.pop();
			}
			mst.push_back(edge);
			int zmien = zbior[std::get<0>(edge)];  // numer podzbioru, ktory bedzie zmieniany
			for (int i = 0; i < numV; ++i) // laczenie zbiorow rozlacznych
			{
				if (zbior[i] == zmien)
				{
					zbior[i] = zbior[std::get<1>(edge)];
				}
			}
		}
	}
	
	/*************************************************************************************************************************/
		
	void Graph::Kruskal_alg_matrix()
	{

		if (directed)
		{
			throw Directed("Graf jest skierowany - nie mozna uruchomic algorytmu.\n");
		}
		mst.clear();
		// wektor bazy zbiorow rozlacznch
		std::vector<int> zbior(numV);
		// kolejka krawedzi
		std::priority_queue< std::tuple<int, int, int>, std::vector< std::tuple<int, int, int> >, Compare_tuples > queue;
		for (int i = 0; i < numV; ++i) /* umieszczenie krawedzi w kolejce */
		{
			zbior[i] = i;
			for (int u = 0; u < numV; ++u)
			{
				if (adj_matrix[i][u] != constants::no_edge)
				{
					queue.push(std::make_tuple(i, u, adj_matrix[i][u]));

				}
			}
		}



		for (int i = 1; i < numV; ++i) // przegladanie kolejnych wierzcholkow
		{
			auto edge = queue.top();
			queue.pop();
			while (zbior[std::get<0>(edge)] == zbior[std::get<1>(edge)] && !queue.empty()) // czy zbiory sa rozlaczne?
			{
				edge = queue.top();
				queue.pop();
			}
			mst.push_back(edge);
			int zmien = zbior[std::get<0>(edge)];  // numer podzbioru, ktory bedzie zmieniany
			for (int i = 0; i < numV; ++i) // laczenie zbiorow rozlacznych
			{
				if (zbior[i] == zmien)
				{
					zbior[i] = zbior[std::get<1>(edge)];
				}
			}
		}
	}


