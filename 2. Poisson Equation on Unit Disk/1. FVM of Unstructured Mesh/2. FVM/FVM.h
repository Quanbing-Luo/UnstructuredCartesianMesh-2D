#pragma once
#include <vector>
#include <array>

// Point
struct Point
{
	Point(double xx, double yy)
		: x{ xx }, y{ yy }  {}
	double	x{ 0.0 }, y{ 0.0 };
};
using Points = std::vector<Point>;



//Triangle 
struct Triangle
{
	Triangle(size_t aa, size_t bb, size_t cc)
		: a{ aa }, b{ bb }, c{ cc }, as{ bb,cc,aa }, bs{cc,aa,bb}{}
	void initialization(const Points& ps);
	size_t a{ 0 }, b{ 0 }, c{ 0 };


	//topological parameters
	std::array<size_t, 3>  as{ 0,0,0 }, bs{ 0,0,0 };
	std::array<bool, 3>  isatboundaries {false, false, false};
	//if atboundary n is id, or n is nearby triangle 
	std::array<size_t, 3>  ns{ 0,0,0 };

	
	// initialization parameters
	double xP{ 0.0 }, yP{ 0.0 }, rP{0.0};
	std::array<double, 3> anbs{ 0.0,0.0,0.0 };
	double aP{ 0.0 };

	std::array<double, 3> Tnbs{ 0.0,0.0,0.0 };
	double TP{ 0.0 },  dTP{ 0.0 };	
};
using Triangles = std::vector<Triangle>;

//Edge   
struct Edge
{
	Edge() = default;

	Edge(size_t aa, size_t bb, size_t nn)
		: a{ aa }, b{ bb }, n{ nn }  { }
	size_t a{ 0 }, b{ 0 };
	// id of boundary lines 
	size_t n{ 0 };
};
using Edges = std::vector<Edge>;


class FVM
{
public:	

	// mesh input  
	void input();	

	//data initialization
	void initialization();

	//calculation
	void calculation();

	//data output
	void output() const;

private:		   	 	
	
	Points ps; Triangles ts; Edges es;
};