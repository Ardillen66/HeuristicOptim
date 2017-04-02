#ifndef _EXPERIMENT_H_
#define _EXPERIMENT_H_

#include <vector>
#include <memory>
#include "pfspinstance.h"
#include "initialsolutionRand.h"
#include "initialsolutionRZ.h"
#include "pivoting.h"
#include "neighbourhoods.h"

using namespace std;

/**
Represents an experiment that attempts to solve a given Flow shop instance with 
the given initial solution, pivoting technique and neighborhood
*/
class Experiments{
	private:
		PfspInstance &instance;
		RandInitialsolution initRand; //Random initial solution
		RZInitialsolution initRZ; //Initial solution constructed with RZ

	public:
		Experiments(PfspInstance &instance);
		~Experiments();

		//implements iterative improvement algorithm given a starting solution, a neighbour relation and a pivoting rule
		//Should return a sloution in vector form
		std::vector< std::vector<int> > runIterImprove(Neighbourhood & nbh, Pivoting & pr);

		//implements Variable Neighbour descent algorithm giiven a starting solution, a vector og neighbourhood relations
		std::vector< std::vector<int> > runVND(std::vector< int > & initialSolution, std::vector< std::shared_ptr<Neighbourhood> > & nbh);

		//Run experiment with all iterative improvement configurations for this instance
		//Returns a matrix with different algorithms in the rows and name, deviation from best solution and computation time in the rows
		float * runIIExperiment();

		float * runVNDExperiment();

};

#endif