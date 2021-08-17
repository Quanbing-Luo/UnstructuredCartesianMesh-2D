#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_set>
//#include <unordered_map>
#include <limits>
#include "CartesianMesh.h"


// Geometry input
void CartesianMesh::input()
{
	std::ifstream ist;
	ist.open("Geometry.txt");
	std::string sss;
	size_t n{ 0 };

	// input Points 
	std::getline(ist, sss);
	size_t np{ 0 }; ist >> np;
	double x{ 0.0 }, y{ 0.0 };
	for (size_t i = 0; i < np; i++)
	{
		ist >> n >> x >> y;
		ps.emplace_back(x, y);
	}
	ist >> std::ws;

	// input Edges
	std::getline(ist, sss);
	size_t ne{ 0 }; ist >> ne;
	size_t aa{ 0 }, bb{ 0 }, id{ 0 };
	bool be { true };
	for (size_t i = 0; i < ne; i++)
	{
		ist >> n >> aa >> bb >> id >> be;
		es.emplace_back(aa, bb, id, be);
	}
	ist >> std::ws;
	ist.close();
}


Square::Square(double xx, double yy, double hh, size_t ll, const Points& ps, const Edges& es)
	: x{ xx }, y{ yy }, h{ hh }, level{ ll } 
{
	// set de d isCrossed
	de = std::numeric_limits<double>::max();
	d = std::numeric_limits<double>::max();
	double xm{ 0.0 }, ym{ 0.0 };

	// the minimum distence between the center and a line segment (signed)
	//and the coordinates at the line segment
	double dd{ 0.0 }, xv{ 0.0 }, yv{0.0};
	for (auto& e : es)
	{
		auto& [xa, ya] { ps[e.a] };  auto& [xb, yb] { ps[e.b] };
		double lap{ std::hypot(xa - x, ya - y) };
		double lbp{ std::hypot(xb - x, yb - y) };
		double pra { (x - xa) * (xb - xa) + (y - ya) * (yb - ya) };
		double prb { (x - xb) * (xa - xb) + (y - yb) * (ya - yb) };

		//cross product
		double cp{ (xa - x) * (yb - y) - (xb - x) * (ya - y) };


		if ( (pra > 0.0) && (prb > 0.0) )
		{
			double lab{ std::hypot(xb - xa, yb - ya) };			
			dd = cp / lab;
			double lav{ std::sqrt(std::pow(lap,2) - std::pow(dd,2)) };
			double lbv{ std::sqrt(std::pow(lbp,2) - std::pow(dd,2)) };
			xv = (lav * xb + lbv * xa) / lab;
			yv = (lav * yb + lbv * ya) / lab;
		}
		else
		{
			if (lap > lbp) 
			{
				dd =  (cp>0)? lbp: (-lbp); xv = xb; 	yv = yb;
			}
			else
			{
				dd = (cp > 0) ? lap : (-lap); xv = xa; 	yv = ya;
			}			
		}			

		if (std::abs(dd) < std::abs(de))		
			de = dd;		

		if (e.berefined == true && std::abs(dd) < std::abs(d))
		{
			d = std::abs(dd); xm = xv; ym = yv;			
		}
	}

	//set isCrossed
	isCrossed = (std::abs(xm - x) < h && std::abs(ym - y) < h) ? true : false;
}



void CartesianMesh::initialization(size_t NN)
{
	const auto [pxmin, pxmax] = std::minmax_element(ps.begin(), ps.end(), 
		[](auto& pa, auto& pb) { return pa.x < pb.x; });
	const auto xmin{ pxmin->x };  const auto xmax{ pxmax->x };

	const auto [pymin, pymax] = std::minmax_element(ps.begin(), ps.end(),
		[](auto& pa, auto& pb) { return pa.y < pb.y; });
	const auto ymin{ pymin->y };  const auto ymax{ pymax->y };

	double dx{ (xmax - xmin) / NN  }, dy{ (ymax - ymin) / NN };

	double sl { 0.0 }; //Side length
	size_t NX{ 0 },  NY{ 0 };
	double hx{ 0.0 };	double hy{ 0.0 };


	if (dx > dy)
	{
		sl = dx;   
		double nyt{ (ymax - ymin) / sl };  size_t NYT{ static_cast<size_t> (nyt) };

		NX = NN;   NY =  ( nyt-NYT <1.0e-3) ? NYT : (NYT+1);
		hx =0.0;   hy = (NY * sl - (ymax - ymin)) / 2.0 ;
	}
	else
	{
		sl = dy; 
		double nxt{ (xmax - xmin) / sl };  size_t NXT{ static_cast<size_t> (nxt) };

		NX = (nxt - NXT < 1.0e-3) ? NXT : (NXT + 1) ; NY = NN;
		hx = (NX * sl - (xmax - xmin)) / 2.0;		hy = 0.0;
	}

	double h = sl / 2.0;

	bg.h = h;
	bg.xmin = xmin - hx; bg.ymin = ymin - hy;
	bg.NX = NX;  bg.NY = NY;


	for (size_t i = 0; i < NX; i++)
		for (size_t j = 0; j < NY; j++)
		{
			double x = xmin - hx + h + i * sl;
			double y = ymin - hy + h + j * sl;
			ss.emplace_back(x, y, h, 0, ps, es);
		}

	output();

}


void CartesianMesh::initial_refinement(size_t LEVEL0)
{
	LEVEL = LEVEL0 ; 
	double hmin = bg.h / std::pow(2, LEVEL);

	size_t i = 0;
	for (auto its = ss.begin(); its != ss.end(); )
	{
		auto x{ its->x }; auto y{ its->y };
		auto h{ its->h }; auto level{ its->level };

		if (its->isCrossed == true && level < LEVEL)
		{
			its = ss.erase(its);
			double hh = h / 2.0; size_t ll = level + 1;			
			ss.emplace_back(x - hh, y - hh, hh, ll, ps, es);
			ss.emplace_back(x + hh, y - hh, hh, ll, ps, es);
			ss.emplace_back(x + hh, y + hh, hh, ll, ps, es);
			ss.emplace_back(x - hh, y + hh, hh, ll, ps, es);
			
		}
		else
			its++;			

				
		//if ( (i++) % 100 == 0)
		//{
		//	output();
		//	continue;
		//	//if (err < 0)
		//}
	}

	output();


	for (auto its = ss.begin(); its != ss.end();)
	{
		if ( its->de < 0 )		
			its = ss.erase(its);		
		else
			its++;
	}

	output();
}


void CartesianMesh::interior_refinement(double alpha)
{
	double hmin = bg.h / std::pow(2, LEVEL);
	
	size_t i = 0;
	for (auto its = ss.begin(); its != ss.end(); )
	{
		
		auto x{ its->x }; auto y{ its->y };
		auto h{ its->h }; auto level{ its->level }; auto d{ its->d };		

				
		if (level < LEVEL && 
			//d < hmin * (alpha * 2 * (std::pow(2, LEVEL - level) -1) + std::pow(2, LEVEL - level) ) )
			d < hmin * alpha *  (std::pow(2, LEVEL - level + 1) - 1)   )
			
			
		{
			its = ss.erase(its);
			double hh = h / 2.0; size_t ll = level + 1;
			ss.emplace_back(x - hh, y - hh, hh, ll, ps, es);
			ss.emplace_back(x + hh, y - hh, hh, ll, ps, es);
			ss.emplace_back(x + hh, y + hh, hh, ll, ps, es);
			ss.emplace_back(x - hh, y + hh, hh, ll, ps, es);
		}
		else
			its++;
	
		
		//if ( (i++) % 100 == 0)
		//{
		//	output();
		//	continue;
		//	//if (err < 0)
		//}
	}	
}







//data output
void CartesianMesh::output() const
{
	const std::string name{ "./Data/CartesianMesh.txt" };
	std::ofstream ost;
	ost.open(name);

	// output Points 
	ost << "Points\n";
	ost << ps.size() << '\n';
	for (size_t i = 1;auto& p: ps )
	{		
		ost << std::scientific << i  << '\t'
			<< p.x << '\t' << p.y << '\t' ;
		ost << '\n';
		i++;
	}

	// output Edges 
	ost << "Edges\n";
	ost << es.size() << '\n';
	for (size_t i = 1; auto & e: es)
	{
		ost << std::scientific << i << '\t'
			<< e.a << '\t' << e.b << '\t' << e.id << '\t';
		ost << '\n';
		i++;
	}


	// output Squares 
	ost << "Squares\n";
	ost << ss.size() << '\n';
	for (size_t i = 1; auto& s : ss)
	{	
		ost << std::scientific << i << '\t'
			<< s.x << '\t' << s.y << '\t' << s.h << '\t' ;

		ost << '\n';
		i++;
	}

	// output BackGroundGrid
	ost << "BackGroundGrid\n";
	ost << bg.h << '\t' 
		<< bg.xmin << '\t' << bg.ymin << '\t'
		<< bg.NX << '\t' << bg.NY << '\n';


	ost.close();
}

