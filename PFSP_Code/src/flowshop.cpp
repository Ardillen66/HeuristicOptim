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

std::vector< std::vector<double> > performSLSExperiment(string nbh, string pivot, string trail_pers, string iga_d, string iga_lambda){
  std::vector< std::vector<double> > results;
  results.resize(2); //We need 2 rows for wct and completion time

  float trail_persistence = std::stof (trail_pers);
  int d = std::stoi (iga_d);
  double lambda = std::stod (iga_lambda);

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

  // Initialize initial solution with RZ heuristic
  Initialsolution * initSol = new RZInitialsolution;

  cout << "Calculating total runtime" << endl;

  //Perform vnd on all instances and take average runtime per instance
  std::vector< std::vector<double> > vnd_results = performVNDExperiment("t_e_i", "rz"); //perform predetermined vnd experiment
  int nbInstances = vnd_results[0].size();
  int nbInstancesSize = nbInstances / 2; //assumes half instances are size 50 and other half 100
  double vnd_time_50 = 0;
  double vnd_time_100 = 0;
  //Average time for instance size 50 and 100
  for (int i = 0; i < nbInstances; ++i)
  {
    if (i < nbInstancesSize)
    {
      vnd_time_50 += vnd_results[1][i]; //Total time for instances of size 50
    } else {
      vnd_time_100 += vnd_results[1][i];
    }
  }
  double run_time_50 = vnd_time_50 / nbInstancesSize * 10; //get average and multiply by 10
  double run_time_100 = vnd_time_100 / nbInstancesSize * 5;
  
  cout << "Runtimes: 50=" << run_time_50 << ", 100=" << run_time_100 << endl;
  // Run first 10 of the 50_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/50_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);

    std::vector<int> initialSolution(instance.getNbJob() + 1);
  
    initSol->getInitialSolution(instance, initialSolution);


    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    //Target WCT 0, since we are only interested in solution quality after given runtime
    cout << "Running ACO on instance" << endl;
    std::vector<int> solution_aco = exper.runACO(*neighbourhood, *pivotRule, trail_persistence, run_time_50, 0); 

    //New pivot for IGA
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    cout << "Running IGA on instance" << endl;
    std::vector<int> solution_iga = exper.runIGA(*neighbourhood, *pivotRule, d, lambda, run_time_50, 0);

    long int wct_aco = instance.computeWCT(solution_aco);
    long int wct_iga = instance.computeWCT(solution_iga);
    results[0].push_back(wct_aco * 1.0); //Implicit cast
    results[1].push_back(wct_iga * 1.0); //Use second column for  second experiment WCT instead of runtime
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

    initSol->getInitialSolution(instance, initialSolution);

    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }
    
    cout << "Running ACO on instance" << endl;
    std::vector<int> solution_aco = exper.runACO(*neighbourhood, *pivotRule, trail_persistence, run_time_50, 0);

    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    cout << "Running IGA on instance" << endl;
    std::vector<int> solution_iga = exper.runIGA(*neighbourhood, *pivotRule, d, lambda, run_time_50, 0);

    long int wct_aco = instance.computeWCT(solution_aco);
    long int wct_iga = instance.computeWCT(solution_iga);
    results[0].push_back(wct_aco * 1.0); //Implicit cast
    results[1].push_back(wct_iga * 1.0); //Use second column for  second experiment WCT instead of runtime

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

    initSol->getInitialSolution(instance, initialSolution);

    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    cout << "Running ACO on instance" << endl;
    std::vector<int> solution_aco = exper.runACO(*neighbourhood, *pivotRule, trail_persistence, run_time_100, 0);

    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    cout << "Running IGA on instance" << endl;
    std::vector<int> solution_iga = exper.runIGA(*neighbourhood, *pivotRule, d, lambda, run_time_100, 0);

    long int wct_aco = instance.computeWCT(solution_aco);
    long int wct_iga = instance.computeWCT(solution_iga);
    results[0].push_back(wct_aco * 1.0); //Implicit cast
    results[1].push_back(wct_iga * 1.0); //Use second column for  second experiment WCT instead of runtime

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

    initSol->getInitialSolution(instance, initialSolution);


    Pivoting * pivotRule = NULL;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    cout << "Running ACO on instance" << endl;
    std::vector<int> solution_aco = exper.runACO(*neighbourhood, *pivotRule, trail_persistence, run_time_100, 0);

    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else if(pivot.compare("first") == 0) {
      pivotRule = new FirstImprove (instance, initialSolution);
    } else {
      cout << "Invalid pivot rule!" << endl;
    }

    cout << "Running IGA on instance" << endl;
    std::vector<int> solution_iga = exper.runIGA(*neighbourhood, *pivotRule, d, lambda, run_time_100, 0);

    long int wct_aco = instance.computeWCT(solution_aco);
    long int wct_iga = instance.computeWCT(solution_iga);
    results[0].push_back(wct_aco * 1.0); //Implicit cast
    results[1].push_back(wct_iga * 1.0); //Use second column for  second experiment WCT instead of runtime

    delete pivotRule;
  }

  delete neighbourhood;
  delete initSol;
  return results;

}

void run_time_dist(string nbh, string pivot, string trail_pers, string iga_d, string iga_lambda, string deviation){
  cout << "Running experiment on run time distributions" << endl;
  long int bestWCTs[] = {612023 , 640081 , 613147 , 681596 , 671406 }; //Target WCT for first 5 solutions of size 50

  float trail_persistence = std::stof (trail_pers);
  int d = std::stoi (iga_d);
  double lambda = std::stod (iga_lambda);
  float dev_from_best = std::stof (deviation) / 100; //Given devation is in percent

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

  // Initialize initial solution with RZ heuristic
  Initialsolution * initSol = new RZInitialsolution;
  //Perform vnd on all instances and take average runtime per instance
  cout << "Computing runtime" << endl;
  std::vector< std::vector<double> > vnd_results = performVNDExperiment("t_e_i", "rz"); //perform predetermined vnd experiment
  int nbInstances = vnd_results[0].size();
  int nbInstancesSize = nbInstances / 2; //assumes half instances are size 50 and other half 100
  double vnd_time_50 = 0;
  //Average time for instance size 50 and 100
  for (int i = 0; i < nbInstancesSize; ++i)
  {
    vnd_time_50 += vnd_results[1][i]; //Total time for instances of size 50
  }
  double run_time_50 = vnd_time_50 / nbInstancesSize * 100; //get average and multiply by 5000

  std::vector< std::vector<double> > runtTimesACO(5, std::vector<double>(25, 0.0));
  std::vector< std::vector<double> > runtTimesIGA(5, std::vector<double>(25, 0.0));
  cout << "Run time distribution" << endl;
  for (int i = 0; i < 5; ++i)
  {
    cout << "Instance " << i+1 << ": " << endl;
    

    string file = "../instances/50_20_0" + to_string(i+1);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(&file[0u]);
    Experiments exper(instance);
    long int targetWCT = bestWCTs[i] + dev_from_best * bestWCTs[i];

    for (int j = 0; j < 25; ++j)
    {

      std::vector<int> initialSolution(instance.getNbJob() + 1);

      cout << "Retrieving initial solution" << endl;
      initSol->getInitialSolution(instance, initialSolution);

      Pivoting * pivotRule = NULL;
      if(pivot.compare("best") == 0){
        pivotRule = new BestImprove(instance, initialSolution);
      } else if(pivot.compare("first") == 0) {
        pivotRule = new FirstImprove (instance, initialSolution);
      } else {
        cout << "Invalid pivot rule!" << endl;
      }

      //We make our timer variables
      std::clock_t start;
      start = std::clock();

      cout << "Run ACO" << endl;
      std::vector<int> solution_aco = exper.runACO(*neighbourhood, *pivotRule, trail_persistence, run_time_50, targetWCT);

      runtTimesACO[i][j] = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

      //New pivot for IGA
      if(pivot.compare("best") == 0){
        pivotRule = new BestImprove(instance, initialSolution);
      } else if(pivot.compare("first") == 0) {
        pivotRule = new FirstImprove (instance, initialSolution);
      } else {
        cout << "Invalid pivot rule!" << endl;
      }

      start = std::clock(); //Restart timer

      cout << "Run IGA" << endl;
      std::vector<int> solution_iga = exper.runIGA(*neighbourhood, *pivotRule, d, lambda, run_time_50, targetWCT);

      runtTimesIGA[i][j] = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

      delete pivotRule;
    }
    runtTimesACO[i] = runtTimesIGA[i] / 25;
    runtTimesIGA[i] = runtTimesIGA[i] / 25;//Average
  }

  delete neighbourhood;
  delete initSol;

  cout << "Max runtime: " << run_time_50 << endl;
  //Output run times
  cout << "ACO runtimes: " << endl;
  cout << "I1, I2, I3, I4, I5" << endl;
  for (int i = 0; i < 25; ++i)
   {
      cout << runtTimesACO[0][i] << ", " << runtTimesACO[1][i] << ", " << runtTimesACO[2][i] << ", " << runtTimesACO[3][i] << ", " << runtTimesACO[4][i] << endl;
   } 
  cout << "IGA runtimes: " << endl;
  cout << "I1, I2, I3, I4, I5" << endl;
  for (int i = 0; i < 25; ++i)
  {
    cout << runtTimesIGA[0][i] << ", " << runtTimesIGA[1][i] << ", " << runtTimesIGA[2][i] << ", " << runtTimesIGA[3][i] << ", " << runtTimesIGA[4][i] << endl;
  }

}


/***********************************************************************/

int main(int argc, char *argv[])
{

  if (argc < 4)
  {
    cout << "Usage: flowshopWCT ii --<pivot_rule> --<neighbourhood> --<initialization>" << endl;
    cout << "Or: flowshopWCT vnd --<neighbourhood_order> --<initialization>" << endl;
    cout << "Or: flowshopWCT sls --<initial_ls_pivot_rule> --<neighbourhood> --<aco_trail_persistence> --<iga_d> --<iga_lambda> --<deviation>" << endl;
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
  } else if (string(argv[1]) == "sls"){
    string pr = string(argv[2]).substr(2);
    string nbh = string(argv[3]).substr(2);
    string trail_pers = string(argv[4]).substr(2);
    string iga_d = string(argv[5]).substr(2);
    string iga_lambda = string(argv[6]).substr(2);
    results = performSLSExperiment(nbh, pr, trail_pers, iga_d, iga_lambda);
    //run_time_dist(nbh, pr, trail_pers, iga_d, iga_lambda, deviation);
  } else if (string(argv[1]) == "runtime"){
    string pr = string(argv[2]).substr(2);
    string nbh = string(argv[3]).substr(2);
    string trail_pers = string(argv[4]).substr(2);
    string iga_d = string(argv[5]).substr(2);
    string iga_lambda = string(argv[6]).substr(2);
    string deviation = string(argv[7]).substr(2); //Only for run time distribution experiment
    run_time_dist(nbh, pr, trail_pers, iga_d, iga_lambda, deviation);
  }

  int nrInstances = results[0].size();
  //Same structure of CSV file, but different meaning of collumns
  if (string(argv[1]) == "sls")
  {
    cout << "Problem, ACO, IGA" << endl;
  } else if(string(argv[1]) == "vnd" || string(argv[1]) == "ii"){
    cout << "Problem , Solution , CT" << endl;
  }
  if(string(argv[1]) != "runtime"){
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
  } 
  
  

  //testAll();
  return 0;
}
