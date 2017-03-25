#ifndef _INITRZ_H_
#define _INITRZ_H_

#include "initialsolution.h"

using namespace std;

/**
This class constructs an initial solution with the RZ heuristic
*/
class RZInitialsolution : public Initalsolution
{
public:
	RZInitialsolution() {};
	~RZInitialsolution() {};

	void getInitialSolution(PfspInstance & inst, std::vector<int> & initSol);
};

#endif