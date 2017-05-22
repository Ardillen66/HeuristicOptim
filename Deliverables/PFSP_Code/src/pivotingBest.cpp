#include <iostream>
#include "helpers.h"
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

bool BestImprove::selectNeighbour(std::vector<int> & neigh, int sIndex, int eIndex){
	long int Nwct;
	if (sIndex < eIndex)
	 {
	 	Nwct = this->recomputeWCT(neigh, sIndex);
	 } 
	 else {
	 	Nwct = this->getInstance().computeWCT(neigh);
	 }

	if(Nwct < curBestWCT){
		currentBestImprove = neigh;
		curBestWCT = Nwct;
		curBestCTMatrix = this->getTmpCompletionTimeMatrix();
	}
	int lastJob = (neigh.size() - 1) * 2; //Last pivot element
	// If all possible neighbours considered and solution improved
	if (sIndex + eIndex >= lastJob && curBestWCT < this->getCurrentWCT())
	{
		//cout << "Best improvement: " << curBestWCT << " Solution: ";
		//printSolution(currentBestImprove);
		this->setCompletionTimes();
		this->setCurrentSolution(currentBestImprove);
		this->setCurrentWCT(curBestWCT);
		return true;
	}
	return false;
}