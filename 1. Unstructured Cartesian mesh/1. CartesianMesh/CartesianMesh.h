#pragma once
#include <vector>
#include <list>
//#include <array>
//#include <unordered_set>
//#include <unordered_map>

// Point
struct Point
{
	Point(double xx, double yy)
		: x{ xx }, y{ yy }  {}
	double	x{ 0.0 }, y{ 0.0 };
};
using Points = std::vector<Point>;


//Edge   
struct Edge
{
	Edge() = default;
	//Edge constructor
	Edge(size_t aa, size_t bb, size_t ID, bool BOOL)
		: a{ aa }, b{ bb }, id{ ID }, berefined{ BOOL }	{ 	}
	size_t a{ 0 }, b{ 0 }, id{ 0 };
	bool berefined{ true };
};
using Edges = std::vector<Edge>;


//Edge   
struct BackGroundGrid
{
	double h{ 0.0 };
	double xmin{ 0.0 }, ymin{ 0.0 };
	size_t NX{ 0 }, NY{ 0 };
};


//Square   
struct Square
{
	Square(double xx, double yy, double hh, size_t ll, const Points& ps, const Edges& es);

	double	x{ 0.0 }, y{ 0.0 }, h{ 0.0 }; 
	size_t level{ 0 };

	//signed distance to edges
	double de{ 0.0 };

	//distance to refined edges
	double d{ 0.0 };

	//whether the square is crossed with refined edges
	bool isCrossed{ false };		
};
using Squares = std::list<Square>;


class CartesianMesh
{
public:	

	// Geometry input  
	void input();	

	//mesh initialization, please provide maximum element number in each row or column 
	void initialization(size_t NN);

	//initial refinement, please provide the level of refinement
	void initial_refinement(size_t LEVEL0);

	//interior_refinement, please provide alpha to control the width of refined mesh
	void interior_refinement(double alpha);

	//data output
	void output() const;

private:

 


	Points ps; 	Edges es;  Squares ss; BackGroundGrid bg;

	size_t LEVEL { 0 };

	//double hmin{ 0.0 }, hmax{ 0.0 };
};

