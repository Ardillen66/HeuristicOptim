#ifndef _NEIGH_H_
#define _NEIGH_H_

#include <vector>
#include "pivoting.h"

using namespace std;

class Neighbourhood
{
public:
	Neighbourhood();
	~Neighbourhood();

	virtual std::vector<int> getNeighbour(Pivoting & pivot) = 0;

protected:
	//Returns a new vector that is the given vector with elements at index x and y swapped
	std::vector<int> swapElements(std::vector<int> v, int x, int y);
};

#endif