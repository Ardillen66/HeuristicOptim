#ifndef _INSERTNEIGH_H_
#define  _INSERTNEIGH_H_

#include "neighbourhoods.h"

using namespace std;

class InsertNeigh : public Neighbourhood{
public:
	InsertNeigh() {};
	~InsertNeigh() {};

	std::list<std::vector<int>> getNeighbours(std::vector<int> & curSol) ;

};

#endif