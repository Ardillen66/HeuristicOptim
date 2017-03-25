#ifndef _BESTIMPROVE_H_
#define _BESTIMPROVE_H_ 

#include "pivoting.h"

using namespace std;

class BestImprove : public Pivoting
{
public:
	BestImprove(){};
	~BestImprove(){};

	std::vector<int> chooseNeighbour(std::list<std::vector<int>> neighs);
};

#endif