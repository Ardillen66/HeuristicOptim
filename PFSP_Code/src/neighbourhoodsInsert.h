#ifndef _INSERTNEIGH_H_
#define  _INSERTNEIGH_H_

#include "neighbourhoods.h"

using namespace std;

class InsertNeigh : public Neighbourhood{
public:
	InsertNeigh();
	~InsertNeigh();

	std::vector<int> getNeighbour(Pivoting & pivot);

};

#endif