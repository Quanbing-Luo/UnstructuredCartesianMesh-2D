#pragma once
#include <cmath>
#include <vector>
//#include <list>
#include <string>
//#include <unordered_set>


// Point and Points
struct Point
{
	//Point() = default;
	Point(double xx, double yy) :x{ xx }, y{ yy }{};

	double x{ 0.0 }, y{ 0.0 };
};
using Points = std::vector<Point>;



//Edge and Edges 
struct Edge
{
	//Edge() = default;
	//Edge constructor
	Edge(size_t aa, size_t bb, size_t ID, bool BOOL) 
		:a{ aa }, b{ bb }, id{ ID }, berefined { BOOL }  {}
	size_t a{ 0 }, b{ 0 }, id{ 0 };
	bool berefined { true };
};
using Edges = std::vector<Edge>;



class Geometry
{
public:
	
	//// Geometry create 
	void create();
	
	//// data initialization. 
	//void initialization();

	// output 
	void output() const;	

private:
	   	  
	Points ps;
	Edges es;
};


