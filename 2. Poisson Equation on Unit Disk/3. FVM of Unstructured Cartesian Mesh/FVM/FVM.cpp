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
	ist.open("CartesianMesh.txt");
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

	for (size_t i = 0; i < ne; i++)
	{
		ist >> n >> aa >> bb >> id;
		es.emplace_back(aa, bb, id);
	}
	ist >> std::ws;



	// input Squares 
	std::getline(ist, sss);
	size_t ns{ 0 }; ist >> ns;
	double xx{ 0.0 }, yy{ 0.0 }, rr{ 0.0 };
	for (size_t i = 0; i < ns; i++)
	{
		ist >> n >> xx >> yy >> rr;
		ss.emplace_back(xx, yy, rr);
	}
	ist >> std::ws;	


	// input BackGroundGrid
	std::getline(ist, sss);
	ist >> bg.h >> bg.xmin >> bg.ymin >> bg.NX >> bg.NY ;
	ist >> std::ws;

	ist.close();
}


//data initialization
void FVM::initialization()
{
	
	auto [h, xmin, ymin, NX, NY] {bg};

	double sl{ 2 * h };
	
	//Background_grids
	std::vector<std::vector<size_t>> bgs(NX*NY);
	for (size_t n=0; auto& s : ss)
	{
		size_t i{ static_cast<size_t>((s.xP - xmin) / sl) };
		size_t j{ static_cast<size_t>((s.yP - ymin) / sl) };

		bgs[i * NY + j].push_back(n);

		n++;
	}


	// Squares initialization
	for (size_t m = 0; auto & s : ss)
	{
		double xP{ s.xP }, yP{ s.yP }, rP{ s.rP };

		auto& isnbs{ s.isnbs }; auto& nnbs{ s.nnbs }; auto& lnbs{ s.lnbs };
		
		size_t i{ static_cast<size_t>((xP - xmin) / sl) };
		size_t j{ static_cast<size_t>((yP - ymin) / sl) };
		
		std::unordered_set<size_t> nbs;
		for (auto&& nn : bgs[i * NY + j])
			nbs.insert(nn);

		if (i > 0) 
		{
			for (auto&& nn : bgs[(i - 1) * NY + j])
				nbs.insert(nn);
		}
		
		if (i < NX - 1)
		{
			for (auto&& nn : bgs[(i + 1) * NY + j])
				nbs.insert(nn);
		}

		if (j > 0)
		{
			for (auto& nn : bgs[i * NY + j - 1])
				nbs.insert(nn);
		}

		if (j < NY - 1)
		{
			for (auto& nn : bgs[i * NY + j + 1])
				nbs.insert(nn);
		}

		nbs.erase(m);


		for (auto n : nbs)
		{
			double xA{ ss[n].xP }, yA{ ss[n].yP }, rA{ ss[n].rP };
			
			double ddx{ std::abs(xP - xA) };
			double ddy{ std::abs(yP - yA) };
			double ddr{ std::abs(rP + rA) };	
			double rrr{ ddr / 1e4 };

			if ((std::abs(ddx - ddr) < rrr && ddr - ddy > rrr) ||
				(std::abs(ddy - ddr) < rrr && ddr - ddx > rrr))
			{
				isnbs.push_back (false);
				nnbs.push_back(n);
				lnbs.push_back(std::min(2 * rP, 2 * rA));
			}
		}

		m++;
	}	



	// set boundaries of squares
	for (auto& s : ss)
	{
		double  rP{ s.rP };
		auto& isnbs{ s.isnbs }; auto& nnbs{ s.nnbs }; auto& lnbs{ s.lnbs };

		double ll{ 8 * rP };
		for (auto& lnb : lnbs)
		{
			ll -= lnb;
		}

		if (ll > 1e-8)
		{
			isnbs.push_back(true);
			nnbs.push_back(0);
			lnbs.push_back(ll);
		}
	}


	// set other parameters
	for (auto& s : ss)
	{
		const auto rP{ s.rP };		const auto& lnbs{ s.lnbs };

		auto& aP{ s.aP }; auto& dTP{ s.dTP };
		auto& anbs{ s.anbs }; 	auto& Tnbs{ s.Tnbs };

		aP = 0.0;
		for (size_t j = 0; j < lnbs.size(); j++)
		{
			double lnb{ lnbs[j] };
			double anb{ lnb / rP };
			anbs.push_back(anb);
			Tnbs.push_back(0.0);
			aP += anb;
		}
		dTP = std::pow(2 * rP, 2) / aP;
	}


	//percentage_of_error_area();
}

//
//
//void FVM::percentage_of_error_area()
//{
//	double area_error{ 0.0 }, area{ 0.0 };	
//	for (auto& s : ss)
//	{
//		auto& isnbs{ s.isnbs };
//		auto& nnbs{ s.nnbs };
//		double  rP{ s.rP };
//		double a{ std::pow(2.0 * rP,2) };
//		area += a;
//		for (size_t i = 0; i < isnbs.size(); i++)
//		{
//			bool is{ isnbs[i] };
//			size_t n{ nnbs[i] };
//
//			if (is == true)
//			{
//				area_error += a;
//				break;
//			}
//			else if (std::abs(rP - ss[n].rP) > 1e-8)
//			{
//				area_error += a;
//				break;
//			}
//			else
//				continue;
//		}
//	}
//
//	r_area= area_error / area ;
//}
//
//
//
//
//
//calculation
void FVM::calculation() 
{		
	for (size_t n = 0; n < 1e8; n++)
	{
		
		// Boundary conditions
		for (auto& s : ss)
		{
			const double rP{ s.rP }; const double aP{ s.aP }; auto& TP{ s.TP };
			const double dTP{ s.dTP }; auto& TP_pse{ s.TP_pse };

			const auto& isnbs{ s.isnbs }; const auto& nnbs{ s.nnbs }; const auto& lnbs{ s.lnbs };			
			const auto& anbs{ s.anbs }; 	auto& Tnbs{ s.Tnbs };

			TP_pse=0.0;		
			for (size_t j = 0; j < isnbs.size(); j++)
			{
				const bool is { isnbs[j] }; const size_t nn{ nnbs[j] }; const double lnb{ lnbs[j] };
				const double anb{ anbs[j] }; double& Tnb{ Tnbs[j] };

				if (is == true)
				{
					Tnb = 0.0;					
				}					
				else
				{
					auto TA{ ss[nn].TP }; auto rA{ ss[nn].rP };
					Tnb = (rA * TP + rP * TA) / (rP + rA);
				}
				TP_pse+=anb*Tnb;
			}
			TP_pse /= aP;
		}

		
		// Temperature calculation
		double err = 0.0;
		for (auto& s : ss)
		{
			auto& TP{ s.TP };	const double TP_pse{ s.TP_pse };
			const double dTP{ s.dTP };

			double TP_old{ TP };
			TP = TP_pse + dTP;
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


	// output Squares 
	ost << "Squares \n";
	ost << ss.size() << '\n';
	for (size_t i = 1; auto& s : ss)
	{
		ost << std::scientific << i << '\t'		
			<< s.xP << '\t' << s.yP << '\t' << s.rP << '\t' << s.TP << '\t';

		ost << '\n';
		i++;
	}

	ost.close();
}

