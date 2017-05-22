#ifndef _PIVOTING_H_
#define _PIVOTING_H_ 

#include <vector>
#include "pfspinstance.h"

using namespace std;

class Pivoting
{
public:
	Pivoting(PfspInstance & inst, std::vector< int > & initSol);
	~Pivoting();

	/*
	Returns true if the given neighbour is the one selected by this pivot rule.
	The index of the currently selected element for swapping is also passed, since Best improvement will require this to terminate and recompute WCT.
	*/
	virtual bool selectNeighbour(std::vector<int> & neigh, int sIndex, int eIndex) = 0;

	std::vector<int> & getCurrentSolution();
	long int getCurrentWCT();
	PfspInstance& getInstance();

protected:
	void setCurrentWCT(long int wct);
	long int recomputeWCT(vector< int > & sol, int offset);
	void setCompletionTimes(); //Sets the temp completion times to the current ones
	void setCurrentSolution(std::vector<int> sol);
	std::vector< std::vector<long int> > getCompletionTimeMatrix();
	std::vector< std::vector<long int> > getTmpCompletionTimeMatrix();
	std::vector< std::vector<long int> > completionTimeMatrix; // Matrix containing completion times for all jobs on all machines for the current solution.
	std::vector< std::vector<long int> > tmpCompletionTimeMatrix; //Recomputed completion times from neighbours are stored here.

private:
	PfspInstance instance;
	std::vector<int> currentSolution;
	long int currentWCT;
};


#endif

