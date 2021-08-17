#include "FVM.h"

int main()
{		
		
	FVM	f;

	// mesh import and initialization
	f.input();

	//data initialization
	f.initialization();
	//calculation
	f.calculation();

	//mesh_topology output
	f.output();

}



