#ifndef _TRANSPOSENEIGH_H_
#define  _TRANSPOSENEIGH_H_

#include "neighbourhoods.h"

using namespace std;

class TransposeNeigh : public Neighbourhood{
public:
	TransposeNeigh();
	~TransposeNeigh();

	std::vector<int> getNeighbour(Pivoting & pivot);

};

#endif