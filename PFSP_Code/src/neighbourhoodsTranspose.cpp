#include <list>
#include <vector>
#include <iostream>
#include "neighbourhoodsTranspose.h"

using namespace std;

TransposeNeigh::TransposeNeigh() {}
TransposeNeigh::~TransposeNeigh() {}

std::vector<int> TransposeNeigh::getNeighbour(Pivoting & pivot){
	std::vector<int> curSol = pivot.getCurrentSolution(); 
	bool done = false; //Variable set according to the pivot rule
	int nrJobs = curSol.size();
	std::vector<int> solution (nrJobs, -1); //Initialize solution with -1 in every element, if no improvement is found this is returned
	for (int i = 1; (i < nrJobs && !done); ++i)
	{
		int next = (i >= nrJobs - 1) ? 1 : i + 1; //Last job is swapped with first
		std::vector<int> neigh = this->swapElements(curSol, i, next);
		if(pivot.selectNeighbour(neigh, i)){
			solution = neigh;
			done = true;
		}
	}
	return solution;
} 

