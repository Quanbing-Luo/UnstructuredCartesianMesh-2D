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
	
	ps.emplace_back(-4, -2); // 0
	ps.emplace_back(4, -2);  // 1
	ps.emplace_back(4, 2);  // 2
	ps.emplace_back(-4, 2);  // 3
	es.emplace_back(0, 1, 0, false);
	es.emplace_back(1, 2, 1, false);
	es.emplace_back(2, 3, 2, false);
	es.emplace_back(3, 0, 3, false);

	constexpr size_t N{ 80 };
	constexpr double dtheta = 2.0 * pi / N;
	size_t np { ps.size() };
	//double theta{ 0.0 }, x{ 0.0 }, y {0.0};
	for (size_t i = 0; i < N; i++)
	{
		double theta{ 2.0 * pi - i * dtheta };
		double x{-2 + std::cos(theta) };
		double y{ std::sin(theta) };		
		ps.emplace_back(x, y);
		es.emplace_back(np + i, np + i + 1, 4, true);
	}
	es[np + N - 1].b = np;

	constexpr size_t N1{ 80 };
	constexpr double dtheta1 = 2.0 * pi / N;
	size_t np1{ ps.size() };
	//double theta{ 0.0 }, x{ 0.0 }, y {0.0};
	for (size_t i = 0; i < N1; i++)
	{
		double theta{ 2.0 * pi - i * dtheta1 };
		double x{2+ std::cos(theta) };
		double y{ std::sin(theta) };
		ps.emplace_back(x, y);
		es.emplace_back(np1 + i, np1 + i + 1, 5, true);
	}
	es[np1 + N1- 1].b = np1;
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




