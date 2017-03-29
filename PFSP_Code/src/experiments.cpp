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

std::vector<int> Experiments::runIterImprove(Neighbourhood& nbh, Pivot& pr){
	bool improves = true;
	while(improves){
		//Pointers to vectors are returned
		std::vector<int> neigh = nbh.getNeighbour(pr); //Get an improving neighbour that is accepted by both the neighbourhood and pivot rule
		if (neigh[0] <= 0) //If no improving neighbour, return vector of -1
		{
			improves = false;//If no more improving neighbours, terminate search
		} else{
			curSol = neigh;
		}

	}
	return curSol;
}

std::vector<int> Experiments::runVND(std::vector<int> &initialSolution, std::vector<Neighbourhood&> &nbh){
	//TODO
}

float * Experiments::runIIExperiment(){
	//TODO
}

float * runVNDExperiment(){
	//TODO
}



