#include "pivotingFirst.h"

using namespace std;

FirstImprove::FirstImprove(PfspInstance & inst, std::vector< int > & initSol) : Pivoting(inst, initSol){}

FirstImprove::~FirstImprove(){}

bool FirstImprove::selectNeighbour(std::vector<int> neigh, int sIndex){
	long int Nwct = this->recomputeWCT(neigh, sIndex);
	if (Nwct < this->getCurrentWCT())
	{
		this->setCompletionTimes();
		this->setCurrentSolution(neigh);
		this->setCurrentWCT(Nwct);
		return true;
	}
	return false;
}