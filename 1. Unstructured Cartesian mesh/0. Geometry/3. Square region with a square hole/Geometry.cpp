#include<algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <set>
#include <numbers>
#include "Geometry.h"

using std::numbers::pi;

void Geometry::create()
{	
	ps.emplace_back(-2, -2); // 0
	ps.emplace_back(2, -2);  // 1
	ps.emplace_back(2, 2);  // 2
	ps.emplace_back(-2, 2);  // 3
	es.emplace_back(0, 1, 1, false);
	es.emplace_back(1, 2, 1, false);
	es.emplace_back(2, 3, 1, false);
	es.emplace_back(3, 0, 1, false);

	ps.emplace_back(-1, -1); // 4
	ps.emplace_back(-1, 1);  // 5
	ps.emplace_back(1, 1);  // 6
	ps.emplace_back(1, -1);  // 7
	es.emplace_back(4, 5, 2, true);
	es.emplace_back(5, 6, 2, true);
	es.emplace_back(6, 7, 2, true);
	es.emplace_back(7, 4, 2, true);	
}



//Initial mesh output 
void Geometry::output() const
{
	
	const std::string name {"./Data/Geometry.txt" };

	std::ofstream ost;
	ost.open(name);

	// output Points 
	ost << "Points\n";
	ost << ps.size() << '\n';
	for (auto& p : ps)
	{
		static size_t i = 1;
		ost << std::scientific << i << '\t'
			<< p.x << '\t' << p.y <<  '\n';
		i++;
	}

	// output Edges 
	ost << "Edges\n";
	ost << es.size() << '\n';
	for (auto& e : es)
	{
		static size_t i = 1;
		ost << std::scientific << i << '\t'
			<< e.a << '\t' << e.b << '\t' << e.id << '\t' 
			<< e.berefined << '\t' << '\n';
		i++;
	}

	ost.close();
}




