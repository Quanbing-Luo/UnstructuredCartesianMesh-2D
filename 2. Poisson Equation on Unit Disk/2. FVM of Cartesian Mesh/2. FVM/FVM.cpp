//#include <algorithm>
//#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <unordered_set>
//#include <unordered_map>
#include "FVM.h"


// mesh input 
void FVM::input()
{		
	std::ifstream ist;
	ist.open("CartesianMesh.txt");
	std::string text;	

	// input Parameters 
	std::getline(ist,text);
	ist >> I >> J >> r;	
	ist >> std::ws;

	// input Squares 
	std::getline(ist, text);
	static size_t II { 0 };
	ist >> II ;
	for (size_t i = 0; i < II; i++)
	{
		static size_t n{ 0 };
		static double x{ 0.0 }, y{ 0.0 };
		static bool is {false};
		ist >> n >> x >> y >>is;
		ss.emplace_back(x,y,is);
	}
	ist >> std::ws;

	// input mesh numbers 
	std::getline(ist, text);
	static size_t III{ 0 };
	ist >> III;
	for (size_t i = 0; i < III; i++)
	{
		static size_t n{ 0 };
		static double nn{ 0 };

		ist >> n >> nn ;
		ns.emplace_back(nn);
	}
	ist >> std::ws;

	ist.close();
}




//calculation
void FVM::calculation() 
{
	double bT{std::pow(r,2)/2.0};	
	
	for (size_t nn = 0; nn < 1e8; nn++)
	{
		double err = 0.0;
		// Temperature calculation	
		for (auto n:ns)
		{
			auto& s{ ss[n] };
			auto& Te{ s.Te }, Tw{ s.Tw }, Ts{ s.Ts }, Tn{ s.Tn };
			auto& T{ s.T };		

			double T_old{ T };
		
			size_t i{ n / I }, j{ n % J };
			Te = get_Te(T, i, j);	Tw = get_Tw(T, i, j);
			Ts = get_Ts(T, i, j);	Tn = get_Tn(T, i, j);
			T = (Te + Tw + Ts + Tn) / 4.0 + bT;			
			err = std::max(err, abs(T- T_old));
		}	

		if (nn % 500 == 0)
		{
			output();
			//if (err < 0)
			if (err < 1e-10)
				break;
		}
	}
}

double FVM::get_Te(double T, size_t i, size_t j)
{
	auto& sE { ss[(i - 1) * J + j] };
	if (sE.is_in_geometry == true)
		return (T + sE.T) / 2.0;		
	else
		return 0.0;
}

double FVM::get_Tw(double T, size_t i, size_t j)
{
	auto& sW{ ss[(i + 1) * J + j] };
	if (sW.is_in_geometry == true)
		return (T + sW.T) / 2.0;		
	else
		return 0.0;
}

double FVM::get_Ts(double T, size_t i, size_t j)
{
	auto& sS{ ss[i * J + j - 1] };
	if (sS.is_in_geometry == true)
		return (T + sS.T) / 2.0;
	else
		return 0.0;
}

double FVM::get_Tn(double T, size_t i, size_t j)
{
	auto& sN{ ss[i * J + j + 1] };
	if (sN.is_in_geometry == true)
		return (T + sN.T) / 2.0;
	else
		return 0.0;
}


//data output
void FVM::output() const
{
	const std::string name{ "./Data/FVM.txt" };
	std::ofstream ost;
	ost.open(name);
	
	// output Parameters 
	ost << "Parameters\n";
	ost << std::scientific << I << '\t' << J << '\t' << r  << '\n';

	// output Squares 
	ost << "Squares\n";
	ost << ss.size() << '\n';
	for (size_t i = 1; auto & s : ss)
	{
		ost << std::scientific << i << '\t'
			<< s.x << '\t' << s.y << '\t' << s.T << '\t' << s.is_in_geometry << '\t';

		ost << '\n';
		i++;
	}

	// output mesh numbers 
	ost << "Mesh numbers\n";
	ost << ns.size() << '\n';
	for (size_t i = 1; auto & n : ns)
	{
		ost << std::scientific << i << '\t'
			<< n << '\t';
		ost << '\n';
		i++;
	}	

	ost.close();
}

