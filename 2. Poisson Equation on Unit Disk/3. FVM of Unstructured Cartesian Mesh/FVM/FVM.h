#pragma once
#include <vector>


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
	Edge(size_t aa, size_t bb, size_t ID)
		: a{ aa }, b{ bb }, id{ ID }  { 	}
	size_t a{ 0 }, b{ 0 }, id{ 0 };
};
using Edges = std::vector<Edge>;



//Square   
struct Square
{
	Square() = default;
	Square(double xx, double yy, double rr)
		: xP{ xx }, yP{ yy }, rP{ rr } {}

	double	xP{ 0.0 }, yP{ 0.0 }, rP{ 0.0 }, TP{ 0.0 }, aP{ 0.0 }, dTP{0.0}, TP_pse{ 0.0 };;

	//whether square edge is at boundary or not 
	std::vector<bool>  isnbs;
	//if at boundary n is id(0), or n is nearby
	std::vector<size_t>  nnbs;

	//length 
	std::vector<double>  lnbs;

	std::vector<double>  anbs, Tnbs;
};
using Squares = std::vector<Square>;


//BackGroundGrid  
struct BackGroundGrid
{
	double h{ 0.0 };
	double xmin{ 0.0 }, ymin{ 0.0 };
	size_t NX{ 0 }, NY{ 0 };
};

class FVM
{
public:	

	// mesh input  
	void input();	

	//data initialization
	void initialization();

	//

	//calculation
	void calculation();

	//data output
	void output() const;

private:		   	 	
	
	//void percentage_of_error_area();


	//double xmin{ 0 };  double xmax{ 0 };
	//double ymin{ 0 };  double ymax{ 0 };
	//double sl{ 0.0 }; size_t I{ 0 }, J{ 0 };
	//double r_area{0.0};
	
	Points ps; 	Edges es;  Squares ss; BackGroundGrid bg;
};