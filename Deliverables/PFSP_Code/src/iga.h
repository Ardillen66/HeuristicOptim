#ifndef _IGA_H_
#define _IGA_H_

#include <vector>
#include "pfspinstance.h"

std::vector<int> destruction_construction(std::vector<int> & curSol, int d, PfspInstance & instance);

double simulated_annealing(long int bestWCT, long int maybeBetterWCT, double temperature);

double annealing_temperature(double lambda, PfspInstance & instance);

#endif