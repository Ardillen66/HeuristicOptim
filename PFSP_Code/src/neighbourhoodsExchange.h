#ifndef _EXCHANGENEIGH_H_
#define  _EXCHANGENEIGH_H_

#include "neighbourhoods.h"

using namespace std;

class ExchangeNeigh : public Neighbourhood{
public:
	ExchangeNeigh() {};
	~ExchangeNeigh() {};

	std::list<std::vector<int>> getNeighbours(std::vector<int> & curSol) ;

};

#endif