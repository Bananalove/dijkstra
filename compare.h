#ifndef COMPARE_H
#define COMPARE_H
#include <tuple>

bool operator==(const std::tuple<int, int, int>& elem1, int elem2)
{
	return std::get<0>(elem1) == elem2;
}
/*
bool operator==( int elem2, const std::tuple<int, int, int>& elem1)
{
return std::get<0>(elem1) == elem2;
}*/





#endif