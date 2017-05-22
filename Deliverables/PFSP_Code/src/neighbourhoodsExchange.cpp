#include <iostream>
#include "neighbourhoodsExchange.h"

using namespace std;

ExchangeNeigh::ExchangeNeigh() {}
ExchangeNeigh::~ExchangeNeigh() {}

std::vector<int> ExchangeNeigh::getNeighbour(Pivoting & pivot){
	std::vector<int> curSol = pivot.getCurrentSolution(); 
	bool done = false; //Variable set according to the pivot rule
	int nrJobs = curSol.size();
	std::vector<int> solution (nrJobs, -1); //Initialize solution with -1 in every element, if no improvement is found this is returned
	for (int i = 1; (i < (nrJobs - 1) && !done); ++i) //Last position was already considered for exchange with all previous
	{
		int next = i + 1;
		for (int j = next; (j < nrJobs && !done); ++j) 
		{
			std::vector<int> neigh = this->swapElements(curSol, i, j);
			//cout << "swapped jobs in positions " << i << " and " << j << endl;
			if(pivot.selectNeighbour(neigh, i, j)){
				solution = pivot.getCurrentSolution(); //Pivot now contains improving neighbor as current solution
				done = true;
			}
		}	
	}
	return solution;
}