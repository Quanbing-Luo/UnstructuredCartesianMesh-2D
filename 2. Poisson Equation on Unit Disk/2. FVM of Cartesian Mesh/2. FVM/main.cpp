#include "FVM.h"

int main()
{		
		
	FVM	f;

	// mesh import 
	f.input();

	//calculation
	f.calculation();

	//mesh_topology output
	f.output();
}



