#ifndef _FIRSTIMPROVE_H_
#define _FIRSTIMPROVE_H_ 

#include "pivoting.h"

using namespace std;

class FirstImprove : public Pivoting
{
public:
	FirstImprove(PfspInstance & inst, std::vector< int > & initSol);
	~FirstImprove();

	bool selectNeighbour(std::vector<int> & neigh, int sIndex, int eIndex);
};

#endif