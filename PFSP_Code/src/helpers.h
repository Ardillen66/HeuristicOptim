#ifndef _HELPERS_H_
#define _HELPERS_H_ 

#include <vector>

/**
Removes the element at given index and shifts all folowing members  a position to the left
*/
std::vector<int> removeElement(std::vector<int> & v, int index);

/**
Inserts element at given position in vector and shifts all folowing elements 1 position to the right
NOTE: assumes given vector is already the right size for insert
*/
std::vector<int> insertElement(std::vector<int> & v, int index, int job);

#endif

