#include "neighbourhoodsExchange.h"

using namespace std;

ExchangeNeigh::ExchangeNeigh() {}
ExchangeNeigh::~ExchangeNeigh() {}

std::vector<int> ExchangeNeigh::getNeighbour(Pivoting & pivot){
	std::vector<int> curSol = pivot.getCurrentSolution(); 
	bool done = false; //Variable set according to the pivot rule
	int nrJobs = curSol.size();
	std::vector<int> solution (nrJobs, -1); //Initialize solution with -1 in every element, if no improvement is found this is returned
	for (int i = 1; (i < nrJobs && !done); ++i)
	{
		int next = i + 1;
		for (int j = next; (j < nrJobs && !done); ++j)
		{
			std::vector<int> neigh = this->swapElements(curSol, i, j);
			if(pivot.selectNeighbour(neigh, i)){
				solution = neigh;
				done = true;
			}
		}	
	}
	return solution;
}