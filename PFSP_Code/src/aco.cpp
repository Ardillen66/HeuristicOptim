#include <cstdlib>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>   

#include "aco.h"

//--------------------------------------------------------------- ACO helper functions ----------------------------------------------------------------------

std::vector<int> buildACOSolution(std::vector<int> & curBest, std::vector< std::vector<double> > & pherTrails){
  int solSize = curBest.size();
  std::vector<bool> scheduled (solSize, false);
  std::vector<int> curSol;
  for (int i = 1; i < solSize; ++i)
  {
    double u = ((double) rand() / (RAND_MAX));//Generate random number between 0 and 1
    if (u <= 0.4)
    {
      //Schedule first job from current solution
      int firstUnsched = getUnscheduled(scheduled);
      curSol.push_back(curBest[firstUnsched]);
      scheduled[firstUnsched] = true;
    } else {
      //Get first five or all remaining unscheduled jobs in current sequence with their trail intensities
      std::vector<int> firstUnsched;
      std::vector<double> trails;
      int unschedIndex;
      for (int i = 0; i < 5 || unschedIndex > 0; ++i)
        {
          unschedIndex = getUnscheduled(scheduled);
          if(unschedIndex > 0 ){
            firstUnsched.push_back(unschedIndex);//Register index of unschedulued job
            double trailIntensity = trailSum(curBest[unschedIndex], unschedIndex, pherTrails);
            trails.push_back(trailIntensity);
          }
        }
      int selectedIndex;//Will contain index of selected job on current sequence
      if (u <= 0.8)
      {
        // Schedule job with highest intensity sum from first five in current solution
        std::vector<double>::iterator max = max_element(trails.begin(),trails.end());
        int argMax = distance(trails.begin(), max); 
        selectedIndex = firstUnsched[argMax];
      } else {
        // Schedule job from first five with probability T(ik) / sum(T(il))
        // construct a trivial random generator engine from a time-based seed:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        std::discrete_distribution<int> distribution (trails.begin(), trails.end());
        selectedIndex = distribution(generator);
      }
      curSol.push_back(curBest[selectedIndex]);
      scheduled[selectedIndex] = true;
    }
  }
  return curSol;
}

int getUnscheduled(std::vector<bool> & scheduled){
  for (int i = 1; i < scheduled.size(); ++i)
  {
    if (! scheduled[i])
    {
      return i;
    }
  }
  return -1; //-1 if no unscheduled jobs left
}

double trailSum(int job, int index, std::vector< std::vector<double> > & pherTrails){
  double ts = 0;
  for (int i = 0; i < index; ++i)
  {
    ts += pherTrails[i][job-1]; //Pheromone trails index from 0!
  }
  return ts;
}

void updatePheromoneTrails(std::vector<int> & curBest, std::vector<int> & newBest, long int newWCT, 
                              float trailPersistence, std::vector< std::vector<double> > & pherTrails){
  int solSize = newBest.size();
  for (int i = 1; i < solSize; ++i) //Positions in new best solution
  {
    int job = newBest[i];
    int jobIndex = job - 1; //Pheromone trails indexed from 0!
    std::vector<int>::iterator prevPosIt = find(curBest.begin(), curBest.end(), job); 
    int previousPos = distance(curBest.begin(), prevPosIt); //Position in best solution so far
    double diff = sqrt(fabs(previousPos - i) + 1); //diff from ACO paper, measure of distance between the previous position and new position of a job
    for (int j = 1; j < solSize; ++i)
    {
      if (j == i)
        pherTrails[j][jobIndex] = trailPersistence * pherTrails[j][jobIndex] + (1 / (diff * newWCT));
      else
        pherTrails[j][jobIndex] = trailPersistence * pherTrails[j][jobIndex];
    }
  }
}