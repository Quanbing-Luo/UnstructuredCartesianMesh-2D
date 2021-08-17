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
	constexpr size_t N{ 160 };
	constexpr double dtheta = 2.0 * pi / N;

	//double theta{ 0.0 }, x{ 0.0 }, y {0.0};
	for (size_t i = 0; i < N; i++)
	{
		double theta{ i * dtheta };
		double x{ std::cos(theta) };
		double y{ std::sin(theta) };
		ps.emplace_back(x, y);
		es.emplace_back(i, i + 1, 0, true);
	}
	es[N - 1].b = 0;
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




