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

	public:
		Experiments(PfspInstance &instance);
		~Experiments();

		//implements iterative improvement algorithm given a starting solution, a neighbour relation and a pivoting rule
		//Should return a sloution in vector form
		std::vector<int> runIterImprove(Neighbourhood & nbh, Pivoting & pr);

		//implements Variable Neighbour descent algorithm giiven a starting solution, a vector og neighbourhood relations
		std::vector<int> runVND(std::vector< int > & initialSolution, std::vector< std::shared_ptr<Neighbourhood> > & nbh);

		std::vector<int> runACO(Neighbourhood & iiNbh, Pivoting & iiPr, float trailPersistence, double runTime, long int targetWCT);

		std::vector<int> runIGA(Neighbourhood & iiNbh, Pivoting & iiPr, int d, double lambda, double runTime, long int targetWCT);
};

#endif