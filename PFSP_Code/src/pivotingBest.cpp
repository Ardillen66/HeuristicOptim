#include "pivotingBest.h"

using namespace std;

BestImprove::BestImprove(PfspInstance & inst, std::vector< int > & initSol) : Pivoting(inst, initSol) {
	currentBestImprove = this->getCurrentSolution();
	curBestWCT = this->getCurrentWCT();
	curBestCTMatrix = this->getCompletionTimeMatrix();
}
BestImprove::~BestImprove(){}

void BestImprove::setCompletionTimes(){
	completionTimeMatrix.swap(curBestCTMatrix);
}

bool BestImprove::selectNeighbour(std::vector<int> neigh, int sIndex){
	long int Nwct = this->recomputeWCT(neigh, sIndex);

	if(Nwct < curBestWCT){
		currentBestImprove = neigh;
		curBestWCT = Nwct;
		curBestCTMatrix = this->getTmpCompletionTimeMatrix();
	}
	int lastJob = neigh.size() - 1; //Last pivot element
	// If all possible neighbours considered and solution improved
	if (sIndex >= lastJob && curBestWCT < this->getCurrentWCT())
	{
		this->setCompletionTimes();
		this->setCurrentSolution(currentBestImprove);
		this->setCurrentWCT(curBestWCT);
		return true;
	}
	return false;
}