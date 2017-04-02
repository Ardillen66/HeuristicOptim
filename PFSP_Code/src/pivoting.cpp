#include <vector>
#include <iostream>
#include "pivoting.h"

using namespace std;

Pivoting::Pivoting(PfspInstance &inst, std::vector<int> & initSol) : instance(inst), currentSolution(initSol){
	//Init completion times matrix for given instance
	int nbM = instance.getNbMac();
	int nbJ = instance.getNbJob();
	completionTimeMatrix.resize(nbJ);          // 1st dimension

	for (int cpt = 0; cpt < nbJ; ++cpt)
		completionTimeMatrix[cpt].resize(nbM); // 2nd dimension

	cout << "Calculate initial WCT" << endl;
	currentWCT = this->recomputeWCT(currentSolution, 1); //Initialize completion time matrix
	cout << "Initialize completion times" << endl;
	this->setCompletionTimes();
	cout << completionTimeMatrix[0][0] << endl;
}

Pivoting::~Pivoting(){
}

std::vector<int> & Pivoting::getCurrentSolution(){
	return currentSolution;
}

long int Pivoting::getCurrentWCT(){
	return currentWCT;
}

std::vector< std::vector<long int> > Pivoting::getCompletionTimeMatrix(){
	return completionTimeMatrix;
}

std::vector< std::vector<long int> > Pivoting::getTmpCompletionTimeMatrix(){
	return tmpCompletionTimeMatrix;
}


void Pivoting::setCurrentWCT(long int wct){
	currentWCT = wct;	
}

void Pivoting::setCompletionTimes(){
	completionTimeMatrix.swap(tmpCompletionTimeMatrix);
}

void Pivoting::setCurrentSolution(std::vector<int> sol){
	currentSolution = sol;
}

/**
Recomputes WTC given a solution vector of length nbJobs + 1 and an offset starting from 1
The offset tells from where in the solution set the completion times need to be recomputed using the previous completion times.
It represents which job that was switched comes first.
*/
long int Pivoting::recomputeWCT(vector< int > & sol, int offset){
	long int wct = 0;
	int nbMac = instance.getNbMac();

	std::vector<std::vector<long int>> newCompletionTimeMatrix (completionTimeMatrix); //Completion times matrix index from 0 as usual!

	if (offset <= 1)
	{
		int jobNumber = sol[1];
		newCompletionTimeMatrix[0][0] = instance.getTime(jobNumber, 1);
		for (int i = 2; i <= nbMac; ++i)
		{
			newCompletionTimeMatrix[0][i-1] = newCompletionTimeMatrix[0][i-2] + instance.getTime(jobNumber, i);
		}

	}
	int nbJob = instance.getNbJob();
	
	int startJ = (offset > 1) ? offset : 2; //Skip first job if offset < 1, this has already been initialized previously 
	//1st Machine
	for (int i = startJ; i <= nbJob; ++i)
	{
		int jobNumber = sol[i];
		newCompletionTimeMatrix[i-1][0] = newCompletionTimeMatrix[i-2][0] + instance.getTime(jobNumber, 1);
	}
	/* others machines : */
	for (int m = 2; m <= nbMac; ++m )
	{
		int mIndex = m-1;
		for (int j = startJ; j <= nbJob; ++j )
		{
			int jobNumber = sol[j];
			int jIndex = j-1;

			if ( newCompletionTimeMatrix[jIndex][mIndex-1] > newCompletionTimeMatrix[jIndex-1][mIndex] )
			{
				newCompletionTimeMatrix[jIndex][mIndex] = newCompletionTimeMatrix[jIndex][mIndex-1] + instance.getTime(jobNumber, m);
			}
			else
			{
				newCompletionTimeMatrix[jIndex][mIndex] = newCompletionTimeMatrix[jIndex-1][mIndex] + instance.getTime(jobNumber, m);
			}
		}
	}
	for (int j = 0; j< nbJob; ++j ){
   	 wct += newCompletionTimeMatrix[j][nbMac-1] * instance.getPriority(sol[j+1]);
	}
	tmpCompletionTimeMatrix = newCompletionTimeMatrix;
	return wct;
}