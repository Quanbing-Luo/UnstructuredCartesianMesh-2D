#pragma once
#include <vector>
//#include <list>
//#include <array>
//#include <unordered_set>
//#include <unordered_map>


//Square   
struct Square
{
	Square() = default;
	Square(double xx, double yy,bool BB)
		: x{ xx }, y{ yy }, is_in_geometry{BB}{}
	double	x{ 0.0 }, y{ 0.0 };
	bool is_in_geometry { false };
};
using Squares = std::vector<Square>;


class CartesianMesh
{
public:		

	//data initialization
	void initialization();

	//data output
	void output() const;

private:

	size_t I{ 0 }, J{ 0 };	double r { 0.0 };	
	Squares ss;
	std::vector<size_t> ns;
};

