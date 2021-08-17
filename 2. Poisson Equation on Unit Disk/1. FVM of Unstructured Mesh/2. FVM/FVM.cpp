//#include <algorithm>
//#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_set>
//#include <unordered_map>
#include "FVM.h"


// mesh input and initialization 
void FVM::input()
{		
	std::ifstream ist;
	ist.open("mesh.txt");
	std::string ss;
	size_t n{ 0 };

	// input Points 
	std::getline(ist,ss);
	size_t np{ 0 }; ist >> np;
	double x{ 0.0 }, y{ 0.0 };
	for (size_t i = 0; i < np; i++)
	{
		ist >> n >> x >> y;
		ps.emplace_back(x,y);
	}
	ist >> std::ws;

	// input Triangles 
	std::getline(ist, ss);
	size_t nt{ 0 }; ist >> nt;
	size_t a{ 0 }, b{ 0 }, c{ 0 };
	for (size_t i = 0; i < nt; i++)
	{
		ist >> n >> a >> b >> c;
		ts.emplace_back(a, b, c);
	}
	ist >> std::ws;

	// input Edges
	std::getline(ist, ss);
	size_t ne{ 0 }; ist >> ne;
	size_t aa{ 0 }, bb{ 0 }, id{ 0 };
	for (size_t i = 0; i < ne; i++)
	{
		ist >> n >> aa >> bb >> id;
		es.emplace_back(aa, bb, id);
	}
	ist >> std::ws;
	ist.close();
}






//data initialization
void FVM::initialization()
{
	//Line requires a < b  
	struct Line	{
		Line() = default;
		//Line constructor
		Line(size_t aa, size_t bb, bool BOOL, size_t nn)
			: isatboundary{ BOOL }, n{ nn }
		{
			if (aa < bb) { a = aa; b = bb; }
			else { a = bb; b = aa; }
		}

		size_t a{ 0 }, b{ 0 };
		bool isatboundary{ false };
		//if atboundary n is id, or n is nearby triangle 
		size_t n{ 0 };
	};
	
	struct Linehash {
		size_t operator()(const Line& l) const
		{
			return std::hash<size_t>{}(l.a) ^ std::hash<size_t>{}(l.b);
		}
	};

	struct Line_equal_to {
		bool operator()(const Line& l1, const Line& l2) const
		{
			return (l1.a == l2.a) && (l1.b == l2.b);
		}
	};

	using Lines = std::unordered_multiset<Line, Linehash, Line_equal_to>;

	Lines ls;

	//Lines initialization
	for (size_t i = 0; auto& t : ts)
	{
		for (size_t j = 0; j<3; j++)		
		ls.emplace(t.as[j], t.bs[j], false, i);

		i++;
	}

	for (auto& e : es)
		ls.emplace(e.a, e.b, true, e.n);	
	
	//set topological parameters
	for (size_t i = 0; auto& t : ts)
	{
		t.initialization(ps);
		
		for (size_t j = 0; j < 3;j++ )
		{
			Line l { t.as[j],t.bs[j], false, i };			
			
			auto [begin, end] = ls.equal_range(l);
			for (auto it = begin; it != end; it++)
			{
				bool isatboundary = it->isatboundary;
				size_t n = it->n;
				if (isatboundary == l.isatboundary && n == l.n)
					continue;
				else
				{
					t.isatboundaries[j] = isatboundary;
					t.ns[j] = n;
					break;
				}
			}
		}
		i++;
	}


	output();
}

void Triangle::initialization(const Points& ps)
{
	double xa{ ps[a].x }, xb{ ps[b].x }, xc{ ps[c].x };
	double ya{ ps[a].y }, yb{ ps[b].y }, yc{ ps[c].y };

	double la = std::hypot(xc - xb, yc - yb);
	double lb = std::hypot(xc - xa, yc - ya);
	double lc = std::hypot(xb - xa, yb - ya);
	double ll{ la + lb + lc };

	xP = (la * xa + lb * xb + lc * xc) / ll;
	yP = (la * ya + lb * yb + lc * yc) / ll;
	double AP = std::abs((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya)) / 2.0;
	rP = 2.0 * AP / ll;

	anbs[0] = la / rP; anbs[1] = lb / rP; anbs[2] = lc / rP;
	aP = anbs[0] + anbs[1] + anbs[2];
	dTP = AP/aP;
}



//calculation
void FVM::calculation() 
{	
	for (size_t n = 0; n < 1e8; n++)
	{
		double err = 0.0;
		// Boundary conditions
		for (auto& t : ts)
		{
			auto TP{ t.TP }; auto rP{ t.rP };
			for (size_t j = 0; j < 3; j++)
			{
				bool isatboundary{ t.isatboundaries[j] };
				size_t nn{ t.ns[j] };

				if (isatboundary)
					t.Tnbs[j] = 0.0;
				else
				{
					auto TA{ ts[nn].TP }; auto rA{ ts[nn].rP };
					t.Tnbs[j] = (rA * TP + rP * TA) / (rP + rA);
				}
			}
		}


		// Temperature calculation	
		for (auto& t : ts)
		{
			auto& anbs{ t.anbs }; auto& aP{ t.aP };
			auto& Tnbs{ t.Tnbs }; auto& TP{ t.TP };			
			auto& dTP{ t.dTP };

			double TP_old{ TP };

			TP = (anbs[0] * Tnbs[0] + anbs[1] * Tnbs[1] + anbs[2] * Tnbs[2]) / aP + dTP;

			err = std::max(err, abs(TP - TP_old));
		}

		if (n % 500 == 0)
		{
			output();
			//if (err < 0)
			if (err < 1e-10)
				break;
		}
	}
}



//data output
void FVM::output() const
{
	const std::string name{ "./Data/FVM.txt" };
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


	// output Triangles 
	ost << "Triangles\n";
	ost << ts.size() << '\n';
	for (size_t i = 1; auto & t : ts)
	{
		ost << std::scientific << i << '\t'
			<< t.a << '\t' << t.b << '\t' << t.c << '\t'
			<< t.xP << '\t' << t.yP << '\t' << t.TP << '\t';

		ost << '\n';
		i++;
	}

	ost.close();
}

