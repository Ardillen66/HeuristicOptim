#include <vector>
#include "pivoting.h"

using namsepace std;

Pivoting::Pivoting(PfspInstance &inst, std::vector<int> & initSol) : instance(inst), currentSolution(initSol){
		currentWCT = instance.computeWCT(currentSolution);
}

std::vector<int> & Pivoting::getCurrentSolution(){
	return currentSolution
}

long int Pivoting::getCurrentWCT(){
	return currentWCT;
}

void setCompletionTimes(){
	completionTimeMatrix.swap(tmpCompletionTimeMatrix);
}

void setCurrentSolution(std::vector<int> sol){
	currentSolution = sol;
}

long int Pivoting::recomputeWCT(vector< int > & sol, int offset){
	long int wct = 0;
	int nbMac = instance.getNbMac();
	std::vector<std::vector<long int>> newCompletionTimeMatrix (completionTimeMatrix);
	if (offset <= 0)
	{
		int jobNumber = sol[0];
		newCompletionTimeMatrix[0][0] = instance.getTime(jobNumber, 1);
		for (int i = 1; i < nbMac; ++i)
		{
			newCompletionTimeMatrix[0][i] = newCompletionTimeMatrix[0][i-1];
		}

	}
	int nbJob = instance.getNbJob();
	
	//1st Machine
	for (int i = offset; i < sol.size(); ++i)
	{
		int jobNumber = sol[i];
		newCompletionTimeMatrix[i][0] = newCompletionTimeMatrix[i-1][0] + instance.getTime(jobNumber, 1);
	}
	/* others machines : */
	for ( m = 1; m < nbMac; ++m )
	{
		for ( j = offset; j < nbJob; ++j )
		{
			jobNumber = sol[j];

			if ( newCompletionTimeMatrix[j][m] > newCompletionTimeMatrix[j-1][m] )
			{
				newCompletionTimeMatrix[j][m] = newCompletionTimeMatrix[j-1][m] + instance.getTime(jobNumber, m);
			}
			else
			{
				newCompletionTimeMatrix[j][m] = newCompletionTimeMatrix[j][m-1] + instance.getTime(jobNumber, m);
			}
		}
	}
	for ( j = 1; j<= nbJob; ++j ){
   	 wct += newCompletionTimeMatrix[j][nbMac-1] * instance.getPriority(sol[j]);
	}

	return wct;
}