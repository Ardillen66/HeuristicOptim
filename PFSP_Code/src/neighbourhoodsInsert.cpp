#include "neighbourhoodsInsert.h"

using namespace std;

InsertNeigh::InsertNeigh() {}
InsertNeigh::~InsertNeigh() {}

std::vector<int> InsertNeigh::removeElement(std::vector<int> v, int index){
	std::vector<int> res (v); 
	int lastJob = res.size() - 1;
	for (int i = index; i < lastJob; ++i)
	{
		res[i] = res[i+1];
	}
	res[lastJob] = -1; // -1 indicates a temporary solution where a job was removed
	return res;
}

std::vector<int> InsertNeigh::insertElement(std::vector<int> v, int index, int job){
	std::vector<int> res (v); 
	res[index] = job;
	for (int i = index + 1; i < res.size(); ++i)
	{
		res[i] = v[i-1];
	}
	return res;
}

std::vector<int> InsertNeigh::getNeighbour(Pivoting & pivot){
	std::vector<int> curSol = pivot.getCurrentSolution(); 
	bool done = false; //Variable set according to the pivot rule
	int nrJobs = curSol.size();
	std::vector<int> solution (nrJobs, -1); //Initialize solution with -1 in every element, if no improvement is found this is returned
	for (int i = 1; (i < nrJobs && !done); ++i)
	{
		int job = curSol[i];
		std::vector<int> tmp = this->removeElement(curSol, i); //Temporary solution with 1 job removed
		for (int j = i+1; (j < nrJobs && !done); ++j)
		{
			std::vector<int> neigh = this->insertElement(tmp, j, job); //Insert job again
			if(pivot.selectNeighbour(neigh, i)){
				solution = neigh;
				done = true;
			}
		}	
	}
	return solution;
}