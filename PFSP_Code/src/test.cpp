#include <vector>
#include <iostream>
#include <memory>

#include "experiments.h"
#include "pivotingFirst.h"
#include "pivotingBest.h"
#include "initialsolutionRand.h"
#include "initialsolutionRZ.h"
#include "neighbourhoodsTranspose.h"
#include "neighbourhoodsExchange.h"
#include "neighbourhoodsInsert.h"
#include "test.h"

using namespace std;

void testInit(PfspInstance & instance){
	vector< int > solution ( instance.getNbJob()+ 1 );
	RZInitialsolution ri;
	ri.getInitialSolution(instance, solution);

    cout << "Initial solution: " ;

	for (int i = 1; i <= instance.getNbJob(); ++i)
		cout << solution[i] << " " ;

	cout << endl;

	/* Compute the TWT of this solution */
	long int totalWeightedTardiness = instance.computeWCT(solution);
	cout << "Total weighted completion time: " << totalWeightedTardiness << endl;

}

void testPivot(PfspInstance & instance){
	vector< int > solution ( instance.getNbJob()+ 1 );
	RandInitialsolution ri;
	ri.getInitialSolution(instance, solution);

	FirstImprove pivot(instance, solution);

    cout << "Random solution: " ;

	for (int i = 1; i <= instance.getNbJob(); ++i)
		cout << solution[i] << " " ;

	cout << endl;

	/* Compute the TWT of this solution */
	long int totalWeightedTardiness = instance.computeWCT(solution);
	cout << "Total weighted completion time: " << totalWeightedTardiness << endl;

	long int wctPivot = pivot.getCurrentWCT();
	cout << "Total weighted completion time (Pivot): " << wctPivot << endl;

}

void testNeighbour(PfspInstance & instance){
	vector< int > solution ( instance.getNbJob()+ 1 );
	RandInitialsolution ri;
	ri.getInitialSolution(instance, solution);
	FirstImprove pivot(instance, solution);
	long int wctPivot = pivot.getCurrentWCT();
	cout << "Initial solution:" << endl;
	for (int i = 1; i <= instance.getNbJob(); ++i)
		cout << solution[i] << " " ;
  	cout << endl;
	cout << "Total weighted completion time Init: " << wctPivot << endl;
	InsertNeigh nbh;
	std::vector<int> improvingNeighBour = nbh.getNeighbour(pivot);

	cout << "Improved solution:" << endl;
	for (int i = 1; i <= instance.getNbJob(); ++i)
		cout << improvingNeighBour[i] << " " ;
  	cout << endl;
	wctPivot = pivot.getCurrentWCT();
	cout << "Total weighted completion time Improved: " << wctPivot << endl;

}

void testII(PfspInstance & instance){
	vector< int > solution ( instance.getNbJob()+ 1 );
	RandInitialsolution ri;
	ri.getInitialSolution(instance, solution);
	BestImprove pivot(instance, solution);
	TransposeNeigh nbh;

	Experiments exper(instance);

	std::vector< std::vector<int> > solutions = exper.runIterImprove(nbh, pivot);

	cout << "WCT's for solutions" << endl;

	for (int i = 0; i < solutions.size(); ++i)
	{
		cout << instance.computeWCT(solutions[i]) << endl;
	}

}

void testVND(PfspInstance & instance){
	vector< int > solution ( instance.getNbJob()+ 1 );
	RandInitialsolution ri;
	ri.getInitialSolution(instance, solution);
	shared_ptr<Neighbourhood> nbtp(new TransposeNeigh);
	shared_ptr<Neighbourhood> nbep(new ExchangeNeigh);
	shared_ptr<Neighbourhood> nbip(new InsertNeigh);
	std::vector< std::shared_ptr<Neighbourhood> > nbh ({nbtp, nbep, nbip});

	Experiments exper(instance);

	std::vector< std::vector<int> > solutions = exper.runVND(solution, nbh);

	cout << "WCT's for solutions" << endl;

	for (int i = 0; i < solutions.size(); ++i)
	{
		cout << instance.computeWCT(solutions[i]) << endl;
	}
}

void testAll(){
	PfspInstance instance;
	bool readOk = instance.readDataFromFile("../instances/50_20_01");
	//testInit(instance);
	//testPivot(instance);
	//testNeighbour(instance);
	//testII(instance);
	testVND(instance);

}


