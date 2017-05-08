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

/* Compute the weighted tardiness of a given PARTIAL solution and current size of solution */
long int RZInitialsolution::computePartWCT(vector< int > & sol, int size, PfspInstance & inst)
{
	int j, m;
	int jobNumber;
	long int wct;
	int nbMac = inst.getNbMac();

	/* We need end times on previous machine : */
	vector< long int > previousMachineEndTime (size + 1);
	/* And the end time of the previous job, on the same machine : */
	long int previousJobEndTime;

	/* 1st machine : */
	previousMachineEndTime[0] = 0;
	for ( j = 1; j <= size; ++j )
	{
		jobNumber = sol[j];
		previousMachineEndTime[j] = previousMachineEndTime[j-1] + inst.getTime(jobNumber, 1);
	}

	/* others machines : */
	for ( m = 2; m <= nbMac; ++m )
	{
		previousMachineEndTime[1] += inst.getTime(sol[1], m);
		previousJobEndTime = previousMachineEndTime[1];

		for ( j = 2; j <= size; ++j )
		{
			jobNumber = sol[j];

			if ( previousMachineEndTime[j] > previousJobEndTime )
			{
				previousMachineEndTime[j] = previousMachineEndTime[j] + inst.getTime(jobNumber, m);
				previousJobEndTime = previousMachineEndTime[j];
			}
			else
			{
				previousJobEndTime += inst.getTime(jobNumber, m);
				previousMachineEndTime[j] = previousJobEndTime;
			}
		}
	}

	wct = 0;
	for ( j = 1; j<= size; ++j )
	    wct += previousMachineEndTime[j] * inst.getPriority(sol[j]);

	return wct;
}

void RZInitialsolution::getInitialSolution(PfspInstance & inst, std::vector<int> & initSol){
	
	std::vector<int> startSequence = this->getStartSequence(inst);
	int nbJob = inst.getNbJob();
	std::vector<int> tmpSol;
	tmpSol.push_back(0); //Initial job
	tmpSol.push_back(startSequence[1]);
	
	for (int i = 2; i <= nbJob; ++i)
	{
		std::vector<int> bestInsert;
		long int bestWCT;
		int job = startSequence[i];
		tmpSol.push_back(-1); //Grow tmpSol for job insertion
		//Try all inserts and select best
		for (int j = 1; j <= i; ++j)
		{

			std::vector<int> tmpV = insertElement(tmpSol, j, job);
			long int partWCT = computePartWCT(tmpV, i+1, inst);
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