#include <cmath>
#include <iostream>
#include "helpers.h"
#include "iga.h"

std::vector<int> destruction_construction(std::vector<int> & curSol, int d, PfspInstance & instance){
	std::vector<int> removedJobs;
	std::vector<int> result (curSol);
	// //destruction
	// cout << "Destructing solution" << endl;
	for (int i = 0; i < d; ++i)
	{
		int removeIndex = generateRndPosition(1, instance.getNbJob() - i); //generate random position in remaining sequence
		result = removeElement(result, removeIndex);
		removedJobs.push_back(curSol[removeIndex]);
	}
	// cout << "Destructed result: ";
	// printSolution(result);
	// //construction
	// cout << "Reconstructing solution" << endl;
	for (int i = d-1; i >= 0; --i)
	{	
		//No need to grow result here, result still has original size, but only conrains unremoved jobs
		int resultSize = instance.getNbJob() - i;
		int job = removedJobs[i];
		std::vector<int> bestInsert = insertElement(result, 1, job);
		long int bestWCT = computePartWCT(bestInsert, resultSize, instance);
		//Try all inserts and select best
		for (int j = 2; j < resultSize; ++j)
		{
			std::vector<int> tmpV = insertElement(result, j, job);
			long int partWCT = computePartWCT(tmpV, resultSize, instance);
			if (partWCT < bestWCT)
			{
				bestWCT = partWCT;
				bestInsert = tmpV;
			}
		}
		result = bestInsert; //Current partial solution becomes best insertion
	}
	// cout << "Reconstructed result: ";
	// printSolution(result);
	return result;
}

double simulated_annealing(long int bestWCT, long int maybeBetterWCT, double temperature){
	double accept_prob = 1.0;
	double accept = exp((bestWCT - maybeBetterWCT) / temperature);
	if (accept < 1.0)
	{
		accept_prob = accept;
	}
	//cout << "Simulated annealing acceptance probability: " << accept_prob << endl;
	return accept_prob;
}

double annealing_temperature(double lambda, PfspInstance & instance){
	//cout << "Calculating annealing temperature" << endl;
	int n = instance.getNbJob();
	int m = instance.getNbMac();

	long int totalTime = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			totalTime += instance.getTime(i, j);
		}
		
	}
	return lambda * (totalTime / (10 * m * n));
}
