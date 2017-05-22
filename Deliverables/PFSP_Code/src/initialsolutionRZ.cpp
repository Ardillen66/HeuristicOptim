#include <iostream>
#include <algorithm>
#include <iterator>
#include "initialsolutionRZ.h"
#include "helpers.h"


using namespace std;

RZInitialsolution::RZInitialsolution(){}
RZInitialsolution::~RZInitialsolution(){}

std::vector<double> RZInitialsolution::getWeightedProcTimes(PfspInstance & inst){
	int nbJob = inst.getNbJob();
	int nbMac = inst.getNbMac();
	std::vector<double> weightedProcessTimes (nbJob);
	for (int i = 0; i < nbJob; ++i)
	{
		int job = i + 1;
		double jobTime = 0;
		for (int j = 0; j < nbMac; ++j)
		{
			int machine = j+1;
			jobTime += inst.getTime(job, machine);
		}
		weightedProcessTimes[i] = jobTime / inst.getPriority(job);
	}
	return weightedProcessTimes;
}

std::vector<int> RZInitialsolution::getStartSequence(PfspInstance & inst){
	std::vector<double> wpt = this->getWeightedProcTimes(inst);
	int nbJob = inst.getNbJob();
	std::vector<int> startSequence (nbJob+1, 0); //fill with invalid job 0
	double max = *max_element(wpt.begin(), wpt.end()); //Get largest weighted processing time
	for (int i = 1; i <= nbJob; ++i)
	{
		std::vector<double>::iterator min = min_element(wpt.begin(),wpt.end());
		int argMin = distance(wpt.begin(), min);
		startSequence[i] =  argMin + 1; //Indexing at 0, +1 to get job number
		wpt[argMin] = max + 1;//Assign value larger than max to not select it anymore
	}
	return startSequence;
}

void RZInitialsolution::getInitialSolution(PfspInstance & inst, std::vector<int> & initSol){
	
	std::vector<int> startSequence = this->getStartSequence(inst);
	int nbJob = inst.getNbJob();
	std::vector<int> tmpSol;
	tmpSol.push_back(0); //Initial dummy job
	tmpSol.push_back(startSequence[1]);
	
	for (int i = 2; i <= nbJob; ++i)
	{
		int job = startSequence[i];
		tmpSol.push_back(-1); //Grow tmpSol for job insertion
		//Initialize best to inert at first position
		std::vector<int> bestInsert = insertElement(tmpSol, 1, job);
		long int bestWCT = computePartWCT(bestInsert, i, inst);
		//Try all inserts and select best
		for (int j = 2; j <= i; ++j)
		{
			//cout << "Insert job " << job << " at position " << j << endl;
			std::vector<int> tmpV = insertElement(tmpSol, j, job);
			//cout << "Job inserted ";
			//printSolution(tmpV);
			long int partWCT = computePartWCT(tmpV, i, inst);
			if (partWCT < bestWCT)
			{
				bestWCT = partWCT;
				bestInsert = tmpV;
			}
		}
		tmpSol = bestInsert; //Current partial solution becomes best insertion
	}

	for (int i = 1; i <= nbJob; ++i)
	{
		initSol[i] = tmpSol[i];
	}

}