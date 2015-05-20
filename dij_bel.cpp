

#include "graph.h"
void Graph::Dij_alg_matrix()

{
	std::vector<bool> counted(numV, false);
	std::vector<bool> uncounted(numV, true); // if true - present 
	std::vector<int> cost(numV, constants::infinit);
	std::vector<int> previous(numV, constants::no_v);
	std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, Compare_tuples_cost> cost_q; // index, cost
	cost[Vstart] = 0;
	cost_q.push(std::make_tuple(Vstart, cost[Vstart]));


	for (int k = 0; k < numV; ++k)
	{
		auto closest = cost_q.top();
		cost_q.pop();
		auto closest_ind = std::get<0>(closest);
		auto closest_cost = std::get<1>(closest);
		counted[closest_ind] = true;
		uncounted[closest_ind] = false;

		for (int i = 0; i < numV; ++i)
		{

			if (adj_matrix[closest_ind][i] != constants::no_edge)
			{
				if (uncounted[i] == true) // if present in uncounted
				{
					if (cost[i] > cost[closest_ind] + adj_matrix[closest_ind][i])
					{
						cost[i] = cost[closest_ind] + adj_matrix[closest_ind][i];
						cost_q.push(std::make_tuple(i, cost[i]));
						previous[i] = closest_ind;



					}



				}

			}




		}




	}
	std::cout << "Wektor indeksow  "; // warto posortowac?
	for (auto iter : counted)
	{
		std::cout << iter << " ";
	}
	std::cout << "Wektor kosztow ";
	for (auto iter : cost)
	{
		std::cout << iter << " ";
	}
	std::cout << "\n";
	std::cout << "Wektor poprzednikow ";
	for (auto iter : previous)
	{
		std::cout << iter << " ";
	}
	std::cout << "\n";


}
