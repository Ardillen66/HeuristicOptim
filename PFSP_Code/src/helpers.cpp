using namespace std;

#include "helpers.h"
#include <cstdlib>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>   

//------------------------------------------------------------------ Insert helpers -----------------------------------------------------------------------

/**
Removes the element at given index and shifts all folowing members  a position to the left
*/
std::vector<int> removeElement(std::vector<int> & v, int index){
  std::vector<int> res (v); 
  int lastJob = res.size() - 1;
  for (int i = index; i < lastJob; ++i)
  {
    res[i] = res[i+1];
  }
  res[lastJob] = -1; // -1 indicates a temporary solution where a job was removed
  return res;
}

/**
Inserts element at given position in vector and shifts all folowing elements 1 position to the right
NOTE: assumes given vector is already the right size for insert with the last position empty
*/
std::vector<int> insertElement(std::vector<int> & v, int index, int job){

  std::vector<int> res (v); 
  for (int i = res.size()-2 ; i >= index ; --i) //Start at second to last position, as last position should be empty
  {
    res[i] = v[i-1];
  }
  res[index] = job;
  return res;
}


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
            firstUnsched.push_back(unschedIndex)//Register index of unschedulued job
            double trailIntensity = trailSum(curBest[unschedIndex], unschedIndex, pherTrails);
            trails.push_back(trailIntensity);
          }
        }
      int selectedIndex;//Will contain index of selected job on current sequence
      if (u <= 0.8)
      {
        // Schedule job with highest intensity sum from first five in current solution
        std::vector<double>::iterator mew = max_element(trails.begin(),trails.end());
        int argMax = distance(trails.begin(), max); 
        selectedIndex = firstUnsched[argMax];
      } else {
        // Schedule job from first five with probability T(ik) / sum(T(il))
        std::vector<double> probabilities(firstUnsched.size());
        for (int i = 0; i < probabilities.size(); ++i)
        {
          probabilities[i] = trails[i] / trailTotal;
        }
        // construct a trivial random generator engine from a time-based seed:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        discrete_distribution<int> distribution (probabilities.begin(), probabilities.end());
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
    ts += pherTrails[i][job-1] //Pheromone trails index from 0!
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
    std::vector<double>::iterator prevPosIt = find(curBest.begin(), curBest.end(), job); 
    int previousPos = distance(curBest.begin(), prevPosIt); //Position in best solution so far
    double diff = sqrt(fabs(previousPos - i) + 1); //diff from ACO paper, measure of distance between the previous position and new position of a job
    for (int j = 1; j < count; ++i)
    {
      if (j == i)
        pherTrails[j][jobIndex] = trailPersistence * pherTrails[j][jobIndex] + (1 / (diff * newWCT));
      else
        pherTrails[j][jobIndex] = trailPersistence * pherTrails[j][jobIndex];
    }
  }
}

