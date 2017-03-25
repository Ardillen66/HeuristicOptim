#ifndef _EXPERIMENT_H_
#define _EXPERIMENT_H_

#include <vector>
#include "pfpinstance.h"

using namespace std;

/**
Represents an experiment that attempts to solve a given Flow shop instance with 
the given initial solution, pivoting technique and neighborhood
*/
class Experiments{
	private:
		PfspInstance &instance;
		RandInit initRand; //Random initial solution
		RZInit initRZ; //Initial solution constructed with RZ

	public:
		Experiments(PfspInstance &instance);
		~Experiments();

		//implements iterative improvement algorithm given a starting solution, a neighbour relation and a pivoting rule
		//Should return a sloution in vector form
		std::vector<int> runIterImprove(std::vector<int> &initialSolution, Neighbourhood &nbh, Pivot &pr);

		//implements Variable Neighbour descent algorithm giiven a starting solution, a vector og neighbourhood relations
		std::vector<int> runVND(std::vector<int> &initialSolution, std::vector<&Neighbourhood> &nbh);

		//Run experiment with all iterative improvement configurations for this instance
		//Returns a matrix with different algorithms in the rows and name, deviation from best solution and computation time in the rows
		float * runIIExperiment();

		float * runVNDExperiment();

};

#endif