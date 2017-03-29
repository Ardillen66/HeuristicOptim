#ifndef _NEIGH_H_
#define _NEIGH_H_

#include <utility>

using namespace std;

class Neighbourhood
{
public:
	Neighbourhood() {};
	~Neighbourhood() {};

	virtual std::list<std::vector<int>> getNeighbour(std::vector<int> & curSol, Pivoting & pivot) = 0;

protected:
	//Returns a new vector that is the given vector with elements at index x and y swapped
	std::vector<int> swapElements(std::vector<int> v, int x, int y){
		std::vector<int> swapped (v);
		std::swap(swapped[x], swapped[y]);
		return swapped; 
	}
};

#endif