#ifndef _BESTIMPROVE_H_
#define _BESTIMPROVE_H_ 

#include <vector>
#include "pfspinstance.h"
#include "pivoting.h"

using namespace std;

class BestImprove : public Pivoting
{
public:
	BestImprove(PfspInstance & inst, std::vector< int > & initSol);
	~BestImprove();

	bool selectNeighbour(std::vector<int> & neighs, int sIndex);

private:
	std::vector<int> currentBestImprove;
	long int curBestWCT;
	std::vector< std::vector<long int> > curBestCTMatrix; // Matrix containing completion times for current best solution
	void setCompletionTimes();
};

#endif