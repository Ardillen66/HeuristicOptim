#include "neighbourhoods.h"

using namespace std;

Neighbourhood::Neighbourhood() {}

Neighbourhood::~Neighbourhood() {}

std::vector<int> Neighbourhood::swapElements(std::vector<int> v, int x, int y){
	std::vector<int> swapped (v);
	std::swap(swapped[x], swapped[y]);
	return swapped; 
}