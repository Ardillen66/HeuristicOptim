#ifndef _INITRZ_H_
#define _INITRZ_H_

#include <vector>
#include "initialsolution.h"
#include "pfspinstance.h"

using namespace std;

/**
This class constructs an initial solution with the RZ heuristic
*/
class RZInitialsolution : public Initialsolution
{
public:
	RZInitialsolution();
	~RZInitialsolution();

	void getInitialSolution(PfspInstance & inst, std::vector<int> & initSol);

private:
	std::vector<double> getWeightedProcTimes(PfspInstance & inst);
	std::vector<int> getStartSequence(PfspInstance & inst);
};

#endif