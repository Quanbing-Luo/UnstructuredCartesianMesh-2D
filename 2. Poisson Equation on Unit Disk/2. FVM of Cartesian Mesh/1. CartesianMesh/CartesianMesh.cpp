#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
//#include <unordered_set>
//#include <unordered_map>
//#include <limits>
#include "CartesianMesh.h"


void CartesianMesh::initialization()
{
	double sl{ 0.034 }; //Side length
	r= sl / 2.0 ;
	double xmin{ -1.0 }, ymin {-1.0}, xmax{ 1.0 }, ymax{ 1.0 };

	I = static_cast<size_t> ((xmax - xmin) / sl) + 3;
	J = static_cast<size_t> ((ymax - ymin) / sl) + 3;
	double hx{ (I * sl - (xmax - xmin)) / 2.0 };
	double hy{ (J * sl - (ymax - ymin)) / 2.0 };

	for (size_t i = 0; i < I; i++)
		for (size_t j = 0; j < J; j++)
		{
			double x = xmin + r - hx  + i * sl;
			double y = ymin + r - hy  + j * sl;
			bool is_in_geometry = (std::hypot(x, y) < 1.0);
			ss.emplace_back(x, y, is_in_geometry);
			if (is_in_geometry == true)
				ns.push_back(ss.size() - 1);
		}
}



//data output
void CartesianMesh::output() const
{
	const std::string name{ "./Data/CartesianMesh.txt" };
	std::ofstream ost;
	ost.open(name);


	// output Parameters 
	ost << "Parameters\n";
	ost << std::scientific << I << '\t' << J << '\t' << r << '\n';

	// output Squares 
	ost << "Squares\n";
	ost << ss.size() << '\n';
	for (size_t i = 1; auto& s : ss)
	{	
		ost << std::scientific << i << '\t'
			<< s.x << '\t' << s.y << '\t'    << s.is_in_geometry << '\t';

		ost << '\n';
		i++;
	}

	// output mesh numbers 
	ost << "Mesh numbers\n";
	ost << ns.size() << '\n';
	for (size_t i = 1; auto& n : ns)
	{
		ost << std::scientific << i << '\t'
			<< n << '\t' ;
		ost << '\n';
		i++;
	}

	ost.close();
}

