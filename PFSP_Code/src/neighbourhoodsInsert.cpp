#include "neighbourhoodsInsert.h"
#include "helpers.h"

using namespace std;

InsertNeigh::InsertNeigh() {}
InsertNeigh::~InsertNeigh() {}

std::vector<int> InsertNeigh::getNeighbour(Pivoting & pivot){
	std::vector<int> curSol = pivot.getCurrentSolution(); 
	bool done = false; //Variable set according to the pivot rule
	int nrJobs = curSol.size();
	std::vector<int> solution (nrJobs, -1); //Initialize solution with -1 in every element, if no improvement is found this is returned
	for (int i = 1; (i < nrJobs && !done); ++i)
	{
		int job = curSol[i];
		std::vector<int> tmp = removeElement(curSol, i); //Temporary solution with 1 job removed
		for (int j = i+1; (j < nrJobs && !done); ++j)
		{
			std::vector<int> neigh = insertElement(tmp, j, job); //Insert job again
			if(pivot.selectNeighbour(neigh, i)){
				solution = neigh;
				done = true;
			}
		}	
	}
	return solution;
}