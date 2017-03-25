#ifndef _NEIGH_H_
#define _NEIGH_H_

using namespace std;

class Neighbourhood
{
public:
	Neighbourhood() {};
	~Neighbourhood() {};

	virtual std::list<std::vector<int>> getNeighbours(std::vector<int> & curSol) = 0;
};

#endif