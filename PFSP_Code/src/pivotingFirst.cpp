
using namespace std;

std::vector<int> FirstImprove::selectNeighbour(std::vector<int> neigh, int sIndex){
	long int Nwct = this->recomputeWCT(neigh, sIndex);
	if (Nwct > this->getCurrentWCT())
	{
		this->setCompletionTimes();
		this->setCurrentSolution(neigh);
		return true;
	}
	return false;
}