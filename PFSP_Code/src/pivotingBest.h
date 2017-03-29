#ifndef _BESTIMPROVE_H_
#define _BESTIMPROVE_H_ 

#include "pivoting.h"

using namespace std;

class BestImprove : public Pivoting
{
public:
	BestImprove(){};
	~BestImprove(){};

	std::vector<int> selectNeighbour(std::vector<int> neighs, int sIndex);
};

#endif