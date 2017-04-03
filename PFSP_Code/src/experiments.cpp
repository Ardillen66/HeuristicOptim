#include <iostream>
#include "pivotingFirst.h"
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

/**
Runs a VND algorithm given an initial solution and a vector of neighbourhoods in the order of evaluation
Note: neighbourhoods stored in smart pointers, need to be dereferenced
*/
std::vector< std::vector<int> > Experiments::runVND(std::vector<int> &initialSolution, std::vector< std::shared_ptr<Neighbourhood> > & nbh){
	bool improves = true;
	std::vector< std::vector<int> > solutions; //vector of all solutions that where visited
	FirstImprove pivot (instance, initialSolution); //Make the first improve pivot
	solutions.push_back(initialSolution); //Retrieve initial solution conatined in pivot
	int ni = 0; //Keeps track of which neighbourhood is currently being used
	while(improves){
		std::vector<int> neigh = nbh[ni]->getNeighbour(pivot); //Get an improving neighbour that is accepted by both the neighbourhood and pivot rule
		if (neigh[1] <= 0) //If no improving neighbour, return vector of -1
		{
			ni++;//Try a different neighbourhood
			if (ni >= nbh.size())
			{
				improves = false;//If no more improving neighbours and no other neighbourhood to try, terminate search
			}
			
		} else{
			solutions.push_back(neigh); //Add solution to list
		}
	}
	return solutions;
}




