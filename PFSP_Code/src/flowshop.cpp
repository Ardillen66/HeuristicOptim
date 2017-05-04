/***************************************************************************
 *   Copyright (C) 2012 by Jérémie Dubois-Lacoste   *
 *   jeremie.dl@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include "pfspinstance.h"
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

/**
Performs iterative improvement using the requested neighbourhood, pivot rule and solution initialization for all instances
Returns Matrix of execution times (in seconds) and weighted completion times of the found solution
*/

std::vector< std::vector<double> > performIIExperiment(string nbh, string pivot, string init){
  std::vector< std::vector<double> > results;
  results.resize(2); //We need 2 rows for wct and completion time

  // Initialize neighbourhood
  Neighbourhood * neighbourhood = NULL;
  if (nbh.compare("exchange") == 0){
    neighbourhood = new ExchangeNeigh;
  } else if(nbh.compare("transpose") == 0){
    neighbourhood = new TransposeNeigh;
  } else if (nbh.compare("insert") == 0){
    neighbourhood = new InsertNeigh;
  } else{
    cout << "Invalid neighbourhood!" << endl;
  }

  // Initialize initial solution
  Initialsolution * initSol = NULL;
  if(init.compare("random") == 0){
    initSol = new RandInitialsolution;
  } else if(init.compare("rz") == 0)
  {
    initSol = new RZInitialsolution;
  } else {
    cout << "Invalid initialization!" << endl;
  }

  // Run first 10 of the 50_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/50_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);

    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    // Duration to find initial solution
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    start = std::clock();

    std::vector<int> solution = exper.runIterImprove(*neighbourhood, *pivotRule);

    duration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
    delete pivotRule;

  }

  //Run rest of 50_20 instances
  for (int i = 10; i <= 30; ++i)
  {
    string file = "../instances/50_20_" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    // Duration to find initial solution
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    start = std::clock();

    std::vector<int> solution = exper.runIterImprove(*neighbourhood, *pivotRule);
    
    duration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
    delete pivotRule;
  }

  // Run first 10 of the 100_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/100_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    // Duration to find initial solution
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    start = std::clock();

    std::vector<int> solution = exper.runIterImprove(*neighbourhood, *pivotRule);
    
    duration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
    delete pivotRule;
  }

  //Run rest of 100_20 instances
  for (int i = 10; i <= 30; ++i)
  {
    string file = "../instances/100_20_" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    // Duration to find initial solution
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    Pivoting * pivotRule = NULL;
   if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    start = std::clock();

    std::vector<int> solution = exper.runIterImprove(*neighbourhood, *pivotRule);
    
    duration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
    delete pivotRule;
  }
  delete neighbourhood;
  delete initSol;
  return results;

}

/**
Performs Variable neighbourhood descent using the requested neighbourhood, pivot rule and solution initialization for all instances
nbh string is the order of the neighbourhoods
*/

std::vector< std::vector<double> > performVNDExperiment(string nbh, string init){
  std::vector< std::vector<double> > results;
  results.resize(2); //We need 2 rows for wct and completion time

  // Initialize neighbourhoods
  shared_ptr<Neighbourhood> nbtp(new TransposeNeigh);
  shared_ptr<Neighbourhood> nbep(new ExchangeNeigh);
  shared_ptr<Neighbourhood> nbip(new InsertNeigh);
  std::vector< std::shared_ptr<Neighbourhood> > neighbourhoods;
  if (nbh.compare("t_e_i")){
    neighbourhoods = std::vector< std::shared_ptr<Neighbourhood> > ({nbtp, nbep, nbip});
  } else if(nbh.compare("t_i_e")) {
    neighbourhoods = std::vector< std::shared_ptr<Neighbourhood> > ({nbtp, nbip, nbep});
  } else {
    cout << "Invalid neighbourhood order!" <<endl;
  }

  // Initialize initial solution
  Initialsolution * initSol = NULL;
  if(init.compare("random") == 0){
    initSol = new RandInitialsolution();
  } else if (init.compare("rz") == 0) {
    initSol = new RZInitialsolution();
  } else {
    cout << "Invalid initialization!" << endl;
  }

  // Run first 10 of the 50_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/50_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    std::vector<int> solution = exper.runVND(initialSolution, neighbourhoods);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
  }

  //Run rest of 50_20 instances
  for (int i = 10; i <= 30; ++i)
  {
    string file = "../instances/50_20_" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    std::vector<int> solution = exper.runVND(initialSolution, neighbourhoods);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
  }

  // Run first 10 of the 100_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/100_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    std::vector<int> solution = exper.runVND(initialSolution, neighbourhoods);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
  }

  //Run rest of 100_20 instances
  for (int i = 10; i <= 30; ++i)
  {
    string file = "../instances/100_20_" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
    //We make our timer variables
    std::clock_t start;
    double duration;
    start = std::clock();

    initSol->getInitialSolution(instance, initialSolution);

    std::vector<int> solution = exper.runVND(initialSolution, neighbourhoods);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    long int wct = instance.computeWCT(solution);
    results[0].push_back(wct * 1.0 ); //Implicit cast
    results[1].push_back(duration);
  }
  delete initSol;
  return results;

}



/***********************************************************************/

int main(int argc, char *argv[])
{

  if (argc < 4)
  {
    cout << "Usage: ./flowshopWCT ii --<pivot_rule> --<neighbourhood> --<initialization>" << endl;
    cout << "Or: ./flowshopWCT vnd --<neighbourhood_order> --<initialization>" << endl;
    return 0;
  }

  std::vector< std::vector<double> > results;
  /* initialize random seed: */
  srand ( time(NULL) );

  if (string(argv[1]) == "ii")
  {
    // Remove -- from command line parameter and convert to string
    string pr = string(argv[2]).substr(2);
    string nbh = string(argv[3]).substr(2);
    string init = string(argv[4]).substr(2);
    results = performIIExperiment(nbh, pr, init);
  } else if (string(argv[1]) == "vnd"){
    string nbh = string(argv[2]).substr(2);
    string init = string(argv[3]).substr(2);
    results = performVNDExperiment(nbh, init);
  }

  int nrInstances = results[0].size();
  cout << "Problem , Solution , CT" << endl;
  int j = 0;
  for (int i = 1; i < 10; ++i)
  {
    cout << "50_20_0" << i << " , " << results[0][j] << " , " << results[1][j] << endl;
    j++;
  }
  for (int i = 10; i <= 30; ++i)
  {
    cout << "50_20_" << i << " , " << results[0][j] << " , " << results[1][j] << endl;
    j++;
  }
  for (int i = 1; i < 10; ++i)
  {
    cout << "100_20_0" << i << " , " << results[0][j] << " , " << results[1][j] << endl;
    j++;
  }
  for (int i = 10; i <= 30; ++i)
  {
    cout << "100_20_" << i << " , " << results[0][j] << " , " << results[1][j] << endl;
    j++;
  }

  //testAll();
  return 0;
}
