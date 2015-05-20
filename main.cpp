/*
Alicja Majewska, algorytm Prima gotowy, algorytm Kruskala do dokonczenia
*/

#include <iostream>
#include <string>
#include "menu.h"




int main() {

/*	Graph graf(0, 20);
	graf.spanning_tree();
	graf.fill_adj_matrix();
	graf.print_adj_matrix(std::cout);*/
	

	//menu();

	std::cout << "Wczytanie danych z pliku i zapis posortowanych do pliku \n ";
	Graph graph;
	bool directed;
	std::cout << "Czy graf jest skierowany? Tak - wpisz 1, nie - wpisz 0.\n";
	std::cin >> directed;
	graph.change_directed(directed);


	std::cout << "Podaj nazwe pliku odczytu:\n";
	//std::string nazwa;
	//std::cin >> nazwa;
	try
	{
		//read_file(nazwa.c_str(), graph
		read_file("dij.txt", graph);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		exit(1);
	}

	std::cout << "Lista krawedzi:\n";
	std::cout << graph;
	graph.make_adj_matrix();
	graph.fill_adj_matrix();
	graph.print_adj_matrix(std::cout);


	graph.make_neigh_list();
	graph.fill_neigh_list();
	graph.print_neigh_list(std::cout);
	
	graph.Dij_alg_matrix();
	std::cout << "wyszedlem!\n";


}
