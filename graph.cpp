#include "graph.h"
#include <iostream>
#include <iomanip>

/*
plik definiuje klase Graph
*/
bool operator==( std::tuple<int, int, int>& elem1, int elem2)
{
	return std::get<0>(elem1) == elem2;
}
bool operator==(int elem2,  std::tuple<int, int, int>& elem1)
{
	return std::get<0>(elem1) == elem2;
}

bool find_i(const std::vector<std::tuple<int, int, int> >& vec, int i)
{
	for (auto iter = vec.begin(), stop = vec.end(); iter != stop; ++iter)
	{
		if (std::get<0>(*iter) == i)
		{
			return true;
		}
	}
	return false;
}

/***************************************************************************************************/
	void Graph::change_set(int nE, int nV, int  Vs, int Ve)
	{
		numE = nE;
		numV = nV;
		Vstart = Vs;
		Vend = Ve;
	}
	void Graph::change_directed(bool dir)
	{
		directed = dir;
	}
		/*************************************************************************************************************************/
	void Graph::add_edge(int vert1, int vert2, int edge_l)
	{
		if (numE == static_cast<int>(edge_list.size()))
		{
			++numE;
		}
		auto edge = std::make_tuple(vert1, vert2, edge_l);
		edge_list.push_back(edge);
	}
	/************************************************* neighbourhood list ********************/
	void Graph::make_neigh_list()
	{
			neigh_list = new std::list<std::tuple<int, int> >[numV];
	}
	/*************************************************************************************************************************/
	void Graph::fill_neigh_list()
	{
		if (neigh_list == nullptr)
		{
			neigh_list = new std::list<std::tuple<int, int> >[numV];
		}
		for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
		{
			neigh_list[std::get<0>(*iter)].push_back(std::make_tuple(std::get<1>(*iter), std::get<2>(*iter)));
			if(!directed)
			{
				neigh_list[std::get<1>(*iter)].push_back(std::make_tuple(std::get<0>(*iter), std::get<2>(*iter)));
			}
		}
	}

		/*************************************************************************************************************************/
	void Graph::delete_neigh_list()
	{
		if (neigh_list != nullptr)
		{
			delete[] neigh_list;
		}
	}
		/*************************************************************************************************************************/
	int Graph::find_edge_list(int v1, int v2)
	{
		//	for (auto iter : neigh_list[v1])
		for(auto iter = neigh_list[v1].begin(), stop = neigh_list[v1].end(); iter != stop; ++iter)
			{
				if (std::get<0>(*iter) == v2)
				{
					return std::get<1>(*iter);
				}
			}
		return constants::no_edge;
	}
		/*************************************************************************************************************************/



	std::ostream& Graph::print_neigh_list(std::ostream& out) const
	{
		out << "Neighbourhood list:\n";
		for (int i = 0; i < numV; ++i)
		{
			out << i << " : " << std::setw(2);

			for (auto iter = neigh_list[i].begin(), stop = neigh_list[i].end(); iter != stop; ++iter)
			{
				out << std::get<0>(*iter) << " (" << std::get<1>(*iter) << ")  "<< std::setw(3);
			}
			out << "\n";
		}
		return out;
	}

	std::ostream& Graph::print_mst(std::ostream& out) const
	{
		out << "Minimal spanning tree:\n";
		
			for (auto iter = mst.begin(), stop = mst.end(); iter != stop; ++iter)
			{
				out << std::get<0>(*iter) << "  " << std::get<1>(*iter) << "   " << std::get<2>(*iter) << "\n";
			}
			
		
		return out;
	}


		

	/********************************** Adjacency matrix ************************/
	void Graph::make_adj_matrix()
	{
		adj_matrix = new int*[numV];
		for (int i = 0; i < numV; ++i)
		{
			adj_matrix[i] = new int[numV];
		}

	}
	
	void Graph::fill_adj_matrix()
	{
		if (adj_matrix == nullptr)
		{
			make_adj_matrix();
		}
		for (int i = 0; i < numV; ++i)
		{
			for (int j = 0; j < numV; ++j)
			{
				adj_matrix[i][j] = constants::no_edge;
			}
		}
		for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
		{
			adj_matrix[std::get<0>(*iter)][std::get<1>(*iter)] = std::get<2>(*iter);
			if(!directed)
			{
				adj_matrix[std::get<1>(*iter)][std::get<0>(*iter)] = std::get<2>(*iter);
			}

			
		}
	}
	



	int Graph::find_edge_matrix(int v1, int v2)
	{
		return adj_matrix[v1][v2];
	}



	std::ostream& Graph::print_adj_matrix(std::ostream& out) const
	{
		out << "Adjacency matrix \n";
		out << ' ' << std::setw(8);
		for (int i = 0; i < numV; ++i)
		{
			out << i << std::setw(8);
		}
			out << "\n";
		for (int i = 0; i < numV; ++i)
		{
					out << i << std::setw(8);
			for (int j = 0; j < numV; ++j)
			{

				if ( adj_matrix[i][j] != constants::no_edge)
				{
					out << adj_matrix[i][j];
					out << std::setw(8);

				}
				else
				{
					out << constants::no_elem;
					out << std::setw(8);

				}

			}
		out << "\n";
		}
		return out;
	}
	void Graph::delete_adj_matrix()
	{
		if (adj_matrix != nullptr)
		{
			for (int i = 0; i < numV; ++i)
			{
				delete[]adj_matrix[i];
			}
			delete[] adj_matrix;
		}
	}

