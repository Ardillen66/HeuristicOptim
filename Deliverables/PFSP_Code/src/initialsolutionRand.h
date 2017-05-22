#ifndef _INITRAND_H_
#define _INITRAND_H_

#include "initialsolution.h"

using namespace std;

/**
This class returns a random initial solution 
*/
class RandInitialsolution : public Initialsolution
{
public:
	RandInitialsolution();
	~RandInitialsolution();

	void getInitialSolution(PfspInstance & inst, std::vector<int> & initSol);
};

#endif