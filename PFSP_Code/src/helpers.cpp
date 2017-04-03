using namespace std;

#include "helpers.h"

/**
Removes the element at given index and shifts all folowing members  a position to the left
*/
std::vector<int> removeElement(std::vector<int> v, int index){
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
NOTE: assumes given vector is already the right size for insert
*/
std::vector<int> insertElement(std::vector<int> v, int index, int job){
  std::vector<int> res (v); 
  res[index] = job;
  for (int i = index + 1; i < res.size(); ++i)
  {
    res[i] = v[i-1];
  }
  return res;
}