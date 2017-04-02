#ifndef _INITSOL_H_
#define _INITSOL_H_

#include <vector>
#include "pfspinstance.h"


using namespace std;

/**
Abstract Class for generating initial solutions.
All subclasses must implement the getInitialSolution() method
*/
class Initialsolution
{
public:
	Initialsolution();
	~Initialsolution();

	virtual void getInitialSolution(PfspInstance & inst, std::vector <int> & initSol) = 0;
};

#endif