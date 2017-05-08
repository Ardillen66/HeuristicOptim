#include <iostream>
#include "pivotingFirst.h"
#include "experiments.h"

using namespace std;

Experiments::Experiments(PfspInstance &inst) : instance(inst)
{
}

Experiments::~Experiments()
{
}

std::vector<int> Experiments::runIterImprove(Neighbourhood & nbh, Pivoting & pr){
	bool improves = true;
	std::vector<int> solution; // final solution
	while(improves){
		std::vector<int> neigh = nbh.getNeighbour(pr); //Get an improving neighbour that is accepted by both the neighbourhood and pivot rule
		if (neigh[1] <= 0) //If no improving neighbour, return vector of -1
		{
			improves = false;//If no more improving neighbours, terminate search
		} else{
			solution = neigh; //Save current solution
		}
	}
	return solution;
}

/**
Runs a VND algorithm given an initial solution and a vector of neighbourhoods in the order of evaluation
Note: neighbourhoods stored in smart pointers, need to be dereferenced
*/
std::vector<int> Experiments::runVND(std::vector<int> &initialSolution, std::vector< std::shared_ptr<Neighbourhood> > & nbh){
	bool improves = true;
	std::vector<int> solution;
	FirstImprove pivot (instance, initialSolution); //Make the first improve pivot
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
			solution = neigh; //Save solution
		}
	}
	return solution;
}

/**
Runs an Ant Colony algorithm using the given neighbourhood an pivoting rule for iterative improvement part
The trail persistence parameter is required to update the pheromone trails and the algorithm stops after the given runTime
*/
std::vector<int> Experiments::runACO(Neighbourhood & iiNbh, Pivoting & iiPr, float trailPersistence, double runTime){
	//Find initial solution with II or VND

	//Calculate initial pheromone trails

	//Construct new solution and update pheromone trails until runTime is over
}




