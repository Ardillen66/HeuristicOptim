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

std::vector<int> Experiments::runIterImprove(std::vector<int>& initialSolution, Neighbourhood& nbh, Pivot& pr){
	bool improves = true;
	std::vector<int> curSol = initialSolution;
	while(improves){
		//Pointers to vectors are returned
		std::list<std::vector<int>>  neighs = nbh.getNeighbours(curSol); //Get all neighbours according to given neighbourhood
		std::vector<int> bestNeigh = pr.chooseNeighbour(neighs); //Choose a neighbour according to the pivot rule
		if (bestNeigh[0] <= 0) //If no improving neighbour, return vector of -1
		{
			improves = false;//If no more improving neighbours, terminate search
		} else{
			curSol = bestNeigh;
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



