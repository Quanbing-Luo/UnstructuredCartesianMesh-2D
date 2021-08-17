#include "CartesianMesh.h"

int main()
{			
	CartesianMesh cm;

	
	cm.input();

	cm.initialization(50);

	
	cm.initial_refinement(3);

	//interior_refinement
	cm.interior_refinement(4.2);

	//output
	cm.output();

}



