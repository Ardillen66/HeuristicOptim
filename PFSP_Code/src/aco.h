
#ifndef _ACO_H_
#define _ACO_H_

std::vector<int> buildACOSolution(std::vector<int> & curBest, std::vector< std::vector<double> > & pherTrails);

int getUnscheduled(std::vector<bool> & scheduled);

double trailSum(int job, int index, std::vector< std::vector<double> > & pherTrails);


void updatePheromoneTrails(std::vector<int> & curBest, std::vector<int> & newBest, std::vector< std::vector<double> > & pherTrails);

#endif