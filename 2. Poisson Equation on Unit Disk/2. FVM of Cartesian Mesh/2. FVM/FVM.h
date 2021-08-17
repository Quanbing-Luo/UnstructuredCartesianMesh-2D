#pragma once
#include <vector>
#include <array>


//Square   
struct Square
{
	Square() = default;
	Square(double xx, double yy, bool BB)
		: x{ xx }, y{ yy }, is_in_geometry{ BB }{}
	double	x{ 0.0 }, y{ 0.0 };
	bool is_in_geometry{ false };
	double Te{ 0.0 }, Tw{ 0.0 }, Ts{ 0.0 }, Tn{ 0.0 };
	double T{ 0.0 };
};
using Squares = std::vector<Square>;


class FVM
{
public:	

	// mesh input  
	void input();

	//calculation
	void calculation();

	//data output
	void output() const;

private:		   	 	
	
	double get_Te(double T, size_t i, size_t j);
	double get_Tw(double T, size_t i, size_t j);
	double get_Ts(double T, size_t i, size_t j);
	double get_Tn(double T, size_t i, size_t j);


	size_t I{ 0 }, J{ 0 }; double r{ 0.0 };
	Squares ss; 
	std::vector<size_t> ns;
};