#ifndef _PIVOTING_H_
#define _PIVOTING_H_ 

using namespace std;

class Pivoting
{
public:
	Pivoting(PfspInstance &inst, std::vector<int> & initSol);
	~Pivoting(){}

	/*
	Returns true if the given neighbour is the one selected by this pivot rule.
	The index of the currently selected element for swapping is also passed, since Best improvement will require this to terminate and recompute WCT.
	*/
	virtual std::vector<int> selectNeighbour(std::vector<int> neigh, int sIndex) = 0;

	std::vector<int> & getCurrentSolution();
	long int getCurrentWCT();

protected:
	long int recomputeWCT(vector< int > & sol, int offset, vector<long int> & previousWCT);
	void setCompletionTimes(); //Sets the temp completion times to the current ones
	void setCurrentSolution(std::vector<int> sol);

private:
	PfspInstance instance;
	std::vector<int> currentSolution;
	long int currentWCT;
	std::vector<std::vector<long int>> completionTimeMatrix; // Matrix containing completion times for all jobs on all machines for the current solution.
	std::vector<std::vector<long int>> tmpCompletionTimeMatrix; //Recomputed completion times from neighbours are stored here.

};


#endif

