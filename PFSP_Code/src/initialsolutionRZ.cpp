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
	std::vector<int> startSequence;
	double max = *max_element(wpt.begin(), wpt.end()); //Get largest weighted processing time
	for (int i = 0; i < wpt.size(); ++i)
	{
		std::vector<double>::iterator min = min_element(wpt.begin(),wpt.end());
		int argMin = distance(wpt.begin(), min);
		startSequence.push_back(argMin + 1); //Indexing at 0, +1 to get job number
		wpt[argMin] = max + 1;//Assign value larger than max to not select it anymore
	}
	return startSequence;
}

/* Compute the weighted tardiness of a given PARTIAL solution */
long int RZInitialsolution::computePartWCT(vector< int > & sol, PfspInstance & inst)
{
	int j, m;
	int jobNumber;
	long int wct;
	int nbJob = sol.size(); //Number of jobs in partial solution
	int nbMac = inst.getNbMac();

	/* We need end times on previous machine : */
	vector< long int > previousMachineEndTime (nbJob + 1);
	/* And the end time of the previous job, on the same machine : */
	long int previousJobEndTime;

	/* 1st machine : */
	previousMachineEndTime[0] = 0;
	for ( j = 1; j <= nbJob; ++j )
	{
		jobNumber = sol[j-1];
		previousMachineEndTime[j] = previousMachineEndTime[j-1] + inst.getTime(jobNumber, 1);
	}

	/* others machines : */
	for ( m = 2; m <= nbMac; ++m )
	{
		previousMachineEndTime[1] += inst.getTime(sol[0], m);
		previousJobEndTime = previousMachineEndTime[1];

		for ( j = 2; j <= nbJob; ++j )
		{
			jobNumber = sol[j-1];

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
	for ( j = 1; j<= nbJob; ++j )
	    wct += previousMachineEndTime[j] * inst.getPriority(sol[j-1]);

	return wct;
}

void RZInitialsolution::getInitialSolution(PfspInstance & inst, std::vector<int> & initSol){
	
	std::vector<int> startSequence = this->getStartSequence(inst);
	
	int solSize = initSol.size();
	std::vector<int> tmpSol; 
	tmpSol.push_back(startSequence[0]); //Insert first job from start sequence
	for (int i = 1; i < solSize - 1; ++i)
	{
		std::vector<int> bestInsert;
		long int bestWCT;
		int job = startSequence[i];
		tmpSol.push_back(0); //Grow partial solution for insert function
		
		//Try all inserts and select best
		for (int j = 0; j < i; ++j)
		{
			std::vector<int> tmpV = insertElement(tmpSol, j, job);
			long int partWCT = computePartWCT(tmpV, inst);
			if (j == 0 || partWCT < bestWCT)
			{
				bestWCT = partWCT;
				bestInsert = tmpV;
			}
		}
		tmpSol = bestInsert; //Current partial solution becomes best insertion
	}

	//Copy temporary solution and add offset
	for (int i = 1; i < solSize; ++i)
	{
		initSol[i] = tmpSol[i-1];
	}
}