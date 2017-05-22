#ifndef _EXCHANGENEIGH_H_
#define  _EXCHANGENEIGH_H_

#include "neighbourhoods.h"

using namespace std;

class ExchangeNeigh : public Neighbourhood{
public:
	ExchangeNeigh();
	~ExchangeNeigh();

	std::vector<int> getNeighbour(Pivoting & pivot);

};

#endif