using namespace std;

#include <iostream>
#include "helpers.h"

//------------------------------------------------------------------ Insert helpers -----------------------------------------------------------------------

/**
Removes the element at given index and shifts all folowing members  a position to the left
*/
std::vector<int> removeElement(std::vector<int> & v, int index){
  std::vector<int> res (v); 
  int lastJob = res.size() - 1;
  for (int i = index; i < lastJob; ++i)
  {
    res[i] = v[i+1];
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
  for (int i = res.size()-1 ; i > index ; --i) 
  {
    res[i] = v[i-1];
  }
  res[index] = job;
  return res;
}

/* Compute the weighted tardiness of a given PARTIAL solution and current size of solution */
long int computePartWCT(vector< int > & sol, int size, PfspInstance & inst)
{
  int j, m;
  int jobNumber;
  long int wct;
  int nbMac = inst.getNbMac();

  /* We need end times on previous machine : */
  vector< long int > previousMachineEndTime (size + 1);
  /* And the end time of the previous job, on the same machine : */
  long int previousJobEndTime;

  /* 1st machine : */
  previousMachineEndTime[0] = 0;
  for ( j = 1; j <= size; ++j )
  {
    jobNumber = sol[j];
    //cout << "Retrieve time for job " << jobNumber << endl;
    previousMachineEndTime[j] = previousMachineEndTime[j-1] + inst.getTime(jobNumber, 1);
  }

  /* others machines : */
  for ( m = 2; m <= nbMac; ++m )
  {
    previousMachineEndTime[1] += inst.getTime(sol[1], m);
    previousJobEndTime = previousMachineEndTime[1];

    for ( j = 2; j <= size; ++j )
    {
      jobNumber = sol[j];

      if ( previousMachineEndTime[j] > previousJobEndTime )
      {
        previousMachineEndTime[j] = previousMachineEndTime[j] + inst.getTime(jobNumber, m);
        previousJobEndTime = previousMachineEndTime[j];
      }
      else
      {
        previousJobEndTime += inst.getTime(jobNumber, m);
        previousMachineEndTime[j] = previousJobEndTime;
      }
    }
  }

  wct = 0;
  for ( j = 1; j<= size; ++j )
      wct += previousMachineEndTime[j] * inst.getPriority(sol[j]);

  return wct;
}

/*
Generate number in range [min, max]
*/
int generateRndPosition(int min, int max)
{
  return ( rand() % max + min );
}

void printSolution(std::vector<int> & sol){
  cout << "[";
  for (int i = 0; i < sol.size(); ++i)
  {
    cout << sol[i] << ", ";
  }
  cout << "]" << endl;
}

void printList(std::vector<long double> & sol){
  cout << "[";
  for (int i = 0; i < sol.size(); ++i)
  {
    cout << sol[i] << ", ";
  }
  cout << "]" << endl;
}
