#ifndef _TRANSPOSENEIGH_H_
#define  _TRANSPOSENEIGH_H_

#include "neighbourhoods.h"

using namespace std;

class TransposeNeigh : public Neighbourhood{
public:
	TransposeNeigh() {};
	~TransposeNeigh() {};

	std::list<std::vector<int>> getNeighbours(std::vector<int> & curSol) ;

};

#endif