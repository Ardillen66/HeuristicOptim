#ifndef _PIVOTING_H_
#define _PIVOTING_H_ 

using namespace std;

class Pivoting
{
public:
	Pivoting(){};
	~Pivoting(){};

	virtual std::vector<int> chooseNeighbour(std::list<std::vector<int>> neighs) = 0;
};


#endif

