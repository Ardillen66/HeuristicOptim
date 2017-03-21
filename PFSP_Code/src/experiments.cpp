#include <iostream>
#include "experiments.h"


using namespace std;

Experiments::Experiments(PfspInstance &inst) : instance(inst)
{
	//Classes containing a method to get either a random or RZ initial solution
	initRand = RandInit();
	initRZ = RZInit();
}

Experiments::~Experiments()
{
}

std::vector<int> Experiments::runIterImprove(std::vector<int> &initialSolution, Neighbourhood &nbh, Pivot &pr){
	//TODO
}

std::vector<int> Experiments::runVND(std::vector<int> &initialSolution, std::vector<&Neighbourhood> &nbh){
	//TODO
}

float * Experiments::runIIExperiment(){
	//TODO
}

float * runVNDExperiment(){
	//TODO
}



