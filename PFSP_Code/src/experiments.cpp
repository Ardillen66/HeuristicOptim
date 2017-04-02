#include <iostream>
#include "experiments.h"

using namespace std;

Experiments::Experiments(PfspInstance &inst) : instance(inst)
{
	//Classes containing a method to get either a random or RZ initial solution
	initRand = RandInitialsolution();
	initRZ = RZInitialsolution();
}

Experiments::~Experiments()
{
}

std::vector< std::vector<int> > Experiments::runIterImprove(Neighbourhood & nbh, Pivoting & pr){
	bool improves = true;
	std::vector< std::vector<int> > solutions; //vector of all solutions that where visited
	std::vector<int> initSol =  pr.getCurrentSolution();
	solutions.push_back(initSol); //Retrieve initial solution conatined in pivot
	while(improves){
		std::vector<int> neigh = nbh.getNeighbour(pr); //Get an improving neighbour that is accepted by both the neighbourhood and pivot rule
		if (neigh[1] <= 0) //If no improving neighbour, return vector of -1
		{
			improves = false;//If no more improving neighbours, terminate search
		} else{
			solutions.push_back(neigh); //Add solution to list
		}

	}
	return solutions;
}

std::vector< std::vector<int> > Experiments::runVND(std::vector<int> &initialSolution, std::vector< std::shared_ptr<Neighbourhood> > & nbh){
	//TODO
}

float * Experiments::runIIExperiment(){
	//TODO
}

float * runVNDExperiment(){
	//TODO
}



