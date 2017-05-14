#include <iostream>
#include "helpers.h"
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
concrete algo is ACO2 from: 
C. Rajendran and H. Ziegler. Two ant-colony algorithms for minimizing total flowtime in permutation flowshops. Computers & Industrial Engineering, 48:789–797, 2005.
*/
std::vector<int> Experiments::runACO(Neighbourhood & iiNbh, Pivoting & iiPr, float trailPersistence, double runTime){
	PfspInstance instance = iiPr.getInstance();
	int nbJob = instance.getNbJob();
	std::clock_t start;
    double duration = 0;
    start = std::clock();

	//Find initial solution with Iterative improvement, current best solution initialized with this value
	std::vector<int> bestSol = this->runIterImprove(iiNbh, iiPr); 
	long int bestWCT =  instance.computeWCT(bestSol);

	//Initialize pheromone trails
	std::vector< std::vector<double> > pherTrails (nbJob, std::vector<double> (nbJob, 1/bestWCT)); //Pheromone trails indexed from 0, dimensions: [position][job]

	//Iterate until runtime is over
	while(duration <= runTime){
		std::vector<int> acoSol = buildACOSolution(bestSol, pherTrails); //Build new solution with ACO
		long int acoWCT = instance.computeWCT(acoSol);
		
		//First improve since we are mostly interested in seeing wether the solution can be improved and Best improve would take too long
		FirstImprove improvePivot = new FirstImprove (instance, acoSol); 
		std::vector<int> maybeImprovedSol = this->runIterImprove(iiNbhn improvePivot); //Try to improve with iterative improvement
		long int maybeBetterWCT = instance.computeWCT(maybeImprovedSol);

		updatePheromoneTrails(bestSol, maybeBetterWCT, maybeBetterWCT, trailPersistence, pherTrails);

		if (maybeBetterWCT < bestWCT) //At worst same as ACO solution, at best improved solution
		{
			bestSol = maybeImprovedSol;
			bestWCT = maybeBetterWCT;
		}

		delete improvePivot;//clean up pivot on every iteration

		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC; //Update duration
	}
}




