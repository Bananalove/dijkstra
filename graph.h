#ifndef GRAPH_H
#define GRAPH_H

#include <list>

#include <tuple>// w tym moze byc wiecej niz 4 elementy, ale jest ok :)
#include <utility>
#include <queue>
#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <limits>
#include <algorithm> //min_elem
//#include "compare.h"
bool operator==(std::tuple<int, int, int>& elem1, int elem2);
bool operator==(int elem2, std::tuple<int, int, int>& elem1);


namespace constants {
	const int no_edge = -1;
	const char no_elem = '.';
	const int no_v = -1;
	const int infinit = std::numeric_limits<int>::max();
	//const double infinit = std::numeric_limits<double>::infinity();
	
}
/*
 * Funktor do sortowania kolejki krotkow - wyznaczenie najmniejszego z elementow
 */
class Compare_tuples
{
public:
bool operator() (std::tuple<int, int, int>& tp1, std::tuple<int, int, int>& tp2)
{
	return std::get<2>(tp1) > std::get<2>(tp2);

}
};

class Compare_tuples_cost
{
	public: 
	bool operator() (std::tuple<int, int>& tp1, std::tuple<int, int>& tp2)
	{
		return std::get<1>(tp1) > std::get<1>(tp2);

	}
};

/* klasa wyj¹tkowa  */

class Directed {
	std::string error;
public:
	Directed (std::string err = "Wystapil blad\n") : error(err)
	{	}
	std::string  what() const
	{
		return error;
	}
};

bool find_i(const std::vector<std::tuple<int, int, int> >& vec, int i);



class Graph {
	int numE;
	int numV;
	int Vstart;
	int Vend;
	std::list < std::tuple<int, int, int> > edge_list;
	int** adj_matrix;
	std::list<std::tuple<int, int> >* neigh_list;
	bool directed; // pole decyduje, czy klasa moze wykonywac algorytm Prima lub Kruskala 
	std::list <std::tuple<int, int, int> >  mst; // minimal spinning tree
	//std::shared_ptr<std::vector <std::tuple<int, int, int> > > mst_ptr;

public:
	Graph(int nE = 0, int nV = 0, int  Vs = 0, int Ve = 0, bool dir = false) : numE(nE), numV(nV), Vstart(Vs), Vend(Ve),
		adj_matrix(nullptr), neigh_list(nullptr), directed(dir)
	{}

	~Graph()
	{
		delete_adj_matrix();
		delete_neigh_list();
	}
	/********************************** access to basic values ***************************************/
	void change_set(int nE, int nV, int  Vs, int Ve);

	void Graph::change_directed(bool dir);
	
	int show_numE() const
	{
		return numE;
	}
	int show_numV() const
	{
		return numV;
	}
	int show_Vstart() const
	{
		return Vstart;
	}
	int show_Vend() const
	{
		return Vend;
	}
	void add_edge(int vert1, int vert2, int edge_l); // should add numE or add next variable ?

	int find_egde_edge_list(int v1, int v2)
	{
		for (auto iter = edge_list.begin(), stop = edge_list.end(); iter != stop; ++iter)
		{
			if (std::get<0>(*iter) == v1 && std::get<1>(*iter) == v2)
			{
				return std::get<2>(*iter);
			}
		}
		return constants::no_edge;
	}


	/******************************************** neighbourhood list ****************************************/
	void make_neigh_list();

	void fill_neigh_list();

	void delete_neigh_list();

	int find_edge_list(int v1, int v2);

	std::ostream& print_neigh_list(std::ostream& out) const;
	/**************************************** Generowanie grafow ********************************************/

	void fill_full();
	
	void fill( double level);

	void spanning_tree();
	/**************************************** Algorytm Dijkstry *******************************************/



	void Dij_alg_matrix()
	{
		std::vector<bool> counted(numV, false);
		std::vector<bool> uncounted(numV, true); // if true - present 
		std::vector<int> cost(numV, constants::infinit);
		std::vector<int> previous(numV, constants::no_v);
		std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, Compare_tuples_cost> cost_q; // index, cost
		cost[Vstart] = 0;
		cost_q.push(std::make_tuple(Vstart,cost[Vstart]));
		

		for (int k = 0; k < numV ; ++k)
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




	/*void Dij_alg_matrix()
	{
		
		std::vector<int> counted;
		std::vector<int> uncounted(numV, 0);
		std::cout << "Tutaj jestem!\n";
		std::vector<int> cost(numV, constants::infinit);
		std::vector<int> previous(numV, constants::no_v);
		std::vector<std::tuple<int, int, int>> uncount_v(numV);
		std::vector<std::tuple<int, int, int>> count_v;
		{
			int fill = 0;
			for (auto iter = uncount_v.begin(), stop = uncount_v.end(); iter != stop; ++iter, ++fill)
			{
				*iter = std::make_tuple(fill, constants::infinit, constants::no_v);
			}
		}*/
	/*	for (int i = 0; i < numV; ++i)
		{
			uncount_v[i] = i;
		}
		for (auto iter : uncounted)
		{
			std::cout << iter << " ";
		}*/
		//std::get<1>(uncount_v[Vstart]) = 0;
		//cost[Vstart] = 0;
		//std::cout << "Tutaj jeszcze jest ok!\n";
		/*
		for (auto iter = uncounted.begin(), stop = uncounted.end(); iter != stop; ++iter)
		{
			*iter = 
		}
		*/
		
		/*while (!uncounted.empty())
		{
		
		//	*std::min_element(cost.begin(), cost.end()); //iterator
			auto minim = std::min_element(uncount_v.begin(), uncount_v.end(), Compare_tuples_cost());
			auto added = *minim;
			std::cout << "added " << std::get<1>(added) << "\n";
			count_v.push_back(added);
			
			//uncounted.erase(minim);
			//std::swap(uncounted[added], uncounted[uncounted.size()-1]);
			std::swap(added, uncount_v.back());
			uncount_v.pop_back();
			std::cout << "Tutaj jeszcze jest ok!\n";
			// counted.back();
			
			for (int i = 0; i < numV; ++i)
			{
				if (adj_matrix[std::get<0>(added)][i] != constants::no_edge)
				{
					std::cout << "Tutaj jeszcze jest ok!\n";
					//if (std::find(uncount_v.begin(), uncount_v.end(), i) != uncount_v.end())
					if (find_i(uncount_v, i) )
					{
						std::cout << "Tutaj jeszcze jest ok!\n";
						if (std::get<1>(uncount_v[i]) > std::get<1>(added) + adj_matrix[std::get<0>(added)][i])
						{
							std::cout << "Tutaj jeszcze jest ok!\n";
							//std::cout << "i " << i <<  "\n";
							//std::cout << "matrix " << adj_matrix[added][i] << "\n";
							//std::cout << "cost " << cost[i] << "\n";
							//std::cout << "cost added " << cost[added] << "\n";
							std::get<1>(uncount_v[i]) = std::get<1>(added) +adj_matrix[std::get<0>(added)][i];
							std::cout << "Tutaj jeszcze jest ok!\n";
							//cost[i] = cost[added] + adj_matrix[added][i];
						//	std::cout << "cost po zmianie " << cost[i] << "\n";
							std::get<2>(uncount_v[i]) = std::get<2>(added);
							std::cout << "Tutaj jeszcze jest ok!\n";
						}

					}

				}

			}

			
		}*/
	/*	std::cout << "Wektor indeksow  "; // warto posortowac?
		for (auto iter : count_v)
		{
			std::cout << std::get<0>(iter) << " ";
		}
		std::cout << "Wektor kosztow ";
		for (auto iter : count_v)
		{
			std::cout << std::get<1>(iter) << " ";
		}
		std::cout << "\n";
		std::cout << "Wektor poprzednikow ";
		for (auto iter : count_v)
		{
			std::cout << std::get<2>(iter) << " ";
		}
		std::cout << "\n";*/




	//}



	/**************************************** Algorytm Prima *********************************************/
	void Prim_alg_list();

	void Prim_alg_matrix();
		
	/**************************************** Algorytm Kruskala ******************************************/
	void Kruskal_alg_matrix();

	void Kruskal_alg_list();

	std::ostream& print_mst(std::ostream& out) const;

	int min_span_tree_weight();
	/*************************************** Adjacency matrix ********************************************/
	void make_adj_matrix();

	void fill_adj_matrix();

	int find_edge_matrix(int v1, int v2);

	std::ostream& print_adj_matrix(std::ostream& out) const;

	void delete_adj_matrix();

	friend std::ostream& operator<< (std::ostream& out, Graph graph);
};


#endif
