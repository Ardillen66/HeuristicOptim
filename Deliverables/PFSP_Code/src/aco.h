
#ifndef _ACO_H_
#define _ACO_H_

std::vector<int> buildACOSolution(std::vector<int> & curBest, std::vector< std::vector<long double> > & pherTrails);

int getUnscheduled(std::vector<bool> & scheduled);

long double trailSum(int job, int index, std::vector< std::vector<long double> > & pherTrails);

void updatePheromoneTrails(std::vector<int> & curBest, std::vector<int> & newBest, long int newWCT, 
                              float trailPersistence, std::vector< std::vector<long double> > & pherTrails);

#endif