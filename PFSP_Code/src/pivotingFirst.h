#ifndef _FIRSTIMPROVE_H_
#define _FIRSTIMPROVE_H_ 

#include "pivoting.h"

using namespace std;

class FirstImprove : public Pivoting
{
public:
	FirstImprove(){}
	~FirstImprove(){}

	std::vector<int> selectNeighbour(std::vector<int> neigh, int sIndex);
};

#endif