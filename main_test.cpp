/*
 * main_test.cpp
 *
 *  Created on: 21 kwi 2015
 *      Author: compaq
 */

#include <iostream>
#include "graph.h"
#include "gtest/gtest.h"
#include "pliki.h"

int show_val(Graph graph)
{
	return graph.show_Vstart();
}

class Licz{
public:
	int val;
};
void PrintTo(const Licz& licz, std::ostream* ost)
{
	*ost << "Liczba: " << licz.val;
}

void PrintTo(const Graph& graph, std::ostream* ost)
{
	*ost << "Graf o danych: " << graph.show_numE() << graph.show_numV() << graph.show_Vstart() << graph.show_Vend();
}

class GraphTest :  public ::testing::Test
{
public:
	Graph graph1;
	Graph graph2;
	Graph graph3;
	virtual void SetUp ()
	{

	try
		{
			read_file("plik2.txt", graph1);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
			exit(1);
		}
			graph1.make_adj_matrix();
			graph1.fill_adj_matrix();
			graph1.make_neigh_list();
			graph1.fill_neigh_list();
			graph1.make_neigh_list();
			graph1.fill_neigh_list();

		try
		{
			read_file("plik3.txt", graph2);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
			exit(1);
		}
		graph2.make_adj_matrix();
		graph2.fill_adj_matrix();
		graph2.make_neigh_list();
		graph2.fill_neigh_list();
		graph2.make_neigh_list();
		graph2.fill_neigh_list();

	}

};




TEST_F(GraphTest, PrimeAlgoritm)
{
	EXPECT_EQ(30, graph1.Prim_alg_matrix ());
}


TEST_F(GraphTest, CanFindMatrixEdge)
{
	ASSERT_EQ(5, graph2.find_edge_matrix(3,0));
	ASSERT_EQ(3,graph2.find_edge_matrix(2, 0));

	ASSERT_EQ(10,graph1.find_edge_matrix(2, 0));
	ASSERT_EQ(graph1.find_edge_matrix(3, 1),graph1.find_edge_matrix(0, 1));
	ASSERT_EQ(graph1.find_edge_matrix(3, 1),graph1.find_edge_matrix(3, 1));
	ASSERT_EQ(graph2.find_edge_matrix(0, 3),graph1.find_edge_matrix(0, 1));
	ASSERT_EQ(graph2.find_edge_matrix(1, 2),graph2.find_edge_matrix(2, 0));
	ASSERT_EQ(graph2.find_edge_matrix(1, 2),graph2.find_edge_matrix(1, 2));
	ASSERT_EQ(0, graph2.find_edge_matrix(3, 3));

}
TEST_F(GraphTest, CanFindNeighEdge)
{
	//ASSERT_EQ(17, graph1.find_edge_matrix(3,1));
	ASSERT_EQ(10,graph1.find_edge_list(2, 0));
	ASSERT_EQ(graph1.find_edge_list(3, 1),graph1.find_edge_list(0, 1));
	ASSERT_EQ(graph1.find_edge_list(3, 1),graph1.find_edge_list(3, 1));
	ASSERT_EQ(graph2.find_edge_list(0, 3),graph1.find_edge_list(0, 1));
	ASSERT_EQ(graph2.find_edge_list(1, 2),graph2.find_edge_list(2, 0));
	ASSERT_EQ(graph2.find_edge_list(1, 2),graph2.find_edge_list(1, 2));
	ASSERT_EQ(0, graph2.find_edge_list(3, 3));
	////////////////////////////////////////////

}

TEST (TestingPrintTo, IsOk)
{
	Graph graph3;
	graph3.change_set(5,5,5,5);
	EXPECT_EQ(5, graph3.show_numE());
	EXPECT_EQ(6, graph3.show_numE());
	EXPECT_EQ(6, show_val(graph3));
	Licz licz;
	licz.val=5;
	EXPECT_EQ(6, licz.val);



}
namespace bar {
class Bar {
public:
	int val;
};

// It's important that PrintTo() is defined in the SAME
// namespace that defines Bar.  C++'s look-up rules rely on that.
void PrintTo(const Bar& bar, ::std::ostream* os) {
  *os << "BAR " << bar.val;  // whatever needed to print bar to os
}
TEST (TestingPrintTo, IsOk2)
{
Bar bar;
bar.val = 5;
ASSERT_EQ(6, bar.val);


}}

int main(int argc, char** argv)
{

	testing:: InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

