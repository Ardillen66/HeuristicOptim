#include <cstdlib>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>  
#include <iostream> 

#include "helpers.h"
#include "aco.h"

//--------------------------------------------------------------- ACO helper functions ----------------------------------------------------------------------

std::vector<int> buildACOSolution(std::vector<int> & curBest, std::vector< std::vector<long double> > & pherTrails){
  int solSize = curBest.size();
  std::vector<bool> scheduled (solSize, false);
  std::vector<int> curSol;
  curSol.push_back(0); //Add dummy job
  for (int i = 1; i < solSize; ++i)
  {
    double u = ((double) rand() / (RAND_MAX));//Generate random number between 0 and 1
    if (u <= 0.4)
    {
      cout << "Adding first unscheduled job" << endl;
      //Schedule first job from current solution
      int firstUnsched = getUnscheduled(scheduled);
      curSol.push_back(curBest[firstUnsched]);
      scheduled[firstUnsched] = true;
    } else {
      //Get first five or all remaining unscheduled jobs in current sequence with their trail intensities
      std::vector<int> firstUnsched;
      std::vector<long double> trails;
      int unschedIndex;
      cout << "Remaining unscheduled jobs: " << endl;
      for (int j = 0; j < scheduled.size(); ++j)
      {
        cout << scheduled[j];      
      }
      cout << endl;
      std::vector<bool> selectedScheduled(scheduled); //Keep track of which unscheduled jobs we already selected
      cout << "Retrieving first five unscheduled jobs" << endl;
      for (int j = 0; j < 5 && unschedIndex > 0; ++j)
        {
          unschedIndex = getUnscheduled(selectedScheduled);
          if(unschedIndex > 0 ){
            cout << "Add index to list: " << unschedIndex << endl;
            firstUnsched.push_back(unschedIndex);//Register index of unschedulued job
            long double trailIntensity = trailSum(curBest[unschedIndex], unschedIndex, pherTrails);
            trails.push_back(trailIntensity);
            selectedScheduled[unschedIndex] = true;
          }
        }
      cout << "Indexes for unscheduled jobs: " << endl;
      printSolution(firstUnsched);
      int selectedIndex;//Will contain index of selected job on current sequence
      if (u <= 0.8)
      {
        cout << "Adding highest intensity job from first unscheduled five" << endl;
        // Schedule job with highest intensity sum from first five in current solution
        std::vector<long double>::iterator max = max_element(trails.begin(),trails.end());
        int argMax = distance(trails.begin(), max);
        selectedIndex = firstUnsched[argMax];
        cout << "Selected index: " << selectedIndex << endl;
      } else {
        cout << "Scheduling with probability distribution" << endl;
        // Schedule job from first five with probability T(ik) / sum(T(il))
        // construct a trivial random generator engine from a time-based seed:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        cout << "Trails: ";
        printList(trails);
        std::discrete_distribution<int> distribution (trails.begin(), trails.end());
        cout << "distribution: ";
        //printList(distribution.probabilities());
        int selectedIndexUnsched = distribution(generator); //Indexing from 1
        selectedIndex = firstUnsched[selectedIndexUnsched];
        cout << "Selected index: " << selectedIndex << endl;
      }
      curSol.push_back(curBest[selectedIndex]);
      scheduled[selectedIndex] = true;
    }
    printSolution(curSol);
  }
  return curSol;
}

//Vector<bool> is apparently broken. No time left to fix this
int getUnscheduled(std::vector<bool> & scheduled){
  for (int i = 1; i < scheduled.size(); ++i)
  {
    if (!scheduled[i])
    {
      //cout << "Unscheduled job at index: " << i << endl;
      return i;
    }
  }
  return -1; //-1 if no unscheduled jobs left
}

long double trailSum(int job, int index, std::vector< std::vector<long double> > & pherTrails){
  double ts = 0;
  for (int i = 0; i < index; ++i)
  {
    ts += pherTrails[i][job-1]; //Pheromone trails index from 0!
  }
  cout << "Trail sum = " << ts << endl;
  return ts;
}

void updatePheromoneTrails(std::vector<int> & curBest, std::vector<int> & newBest, long int newWCT, 
                              float trailPersistence, std::vector< std::vector<long double> > & pherTrails){
  int solSize = newBest.size();
  for (int i = 1; i < solSize; ++i) //Positions in new best solution
  {
    int job = newBest[i];
    int jobIndex = job - 1; //Pheromone trails indexed from 0!
    std::vector<int>::iterator prevPosIt = find(curBest.begin(), curBest.end(), job); 
    int previousPos = distance(curBest.begin(), prevPosIt); //Position in best solution so far
    double diff = sqrt(fabs(previousPos - i) + 1); //diff from ACO paper, measure of distance between the previous position and new position of a job
    for (int j = 1; j < solSize; ++j)
    {
      if (j == i)
        pherTrails[j][jobIndex] = trailPersistence * pherTrails[j][jobIndex] + (10000.0 / (diff * (1.0 * newWCT)));
      else
        pherTrails[j][jobIndex] = trailPersistence * pherTrails[j][jobIndex];
    }
  }
}