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
#include "test.h"

using namespace std;

/**
Performs iterative improvement using the requested neighbourhood, pivot rule and solution initialization for all instances
*/

performIIExperiment(string nbh, string pivot, string init){
  // Initialize neighbourhood
  Neighbourhood neighbourhood;
  if (nbh.compare("exchange") == 0){
    neighbourhood = new ExchangeNeigh();
  } else if(nbh.compare("transpose") == 0){
    neighbourhood = new TransposeNeigh();
  } else {
    neighbourhood = new InsertNeigh();
  }

  // Initialize initial solution
  Initialsolution initSol;
  if(nbh.compare("random") == 0){
    initSol = new RandInitialsolution();
  } else {
    initSol = new RZInitialsolution();
  }

  // Run first 10 of the 50_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/50_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(file);
    Experiments exper(instance);

    std::vector<int> initialSolution;
    initSol.getInitialSolution(instance, initialSolution);

    Pivoting pivotRule;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else {
      pivotRule = new FirstImprove(instance, initialSolution);
    }

    std::vector< std::vector<int> > solutions = exper.runIterImprove(neighbourhood, pivotRule);
  }

  //Run rest of 50_20 instances
  for (int i = 10; i <= 30; ++i)
  {
    string file = "../instances/50_20_" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(file);
    Experiments exper(instance);

    std::vector<int> initialSolution;
    initSol.getInitialSolution(instance, initialSolution);

    Pivoting pivotRule;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else {
      pivotRule = new FirstImprove(instance, initialSolution);
    }

    std::vector< std::vector<int> > solutions = exper.runIterImprove(neighbourhood, pivotRule);
  }

  // Run first 10 of the 100_20 instances
  for (int i = 1; i < 10; ++i)
  {
    string file = "../instances/100_20_0" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(file);
    Experiments exper(instance);

    std::vector<int> initialSolution;
    initSol.getInitialSolution(instance, initialSolution);

    Pivoting pivotRule;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else {
      pivotRule = new FirstImprove(instance, initialSolution);
    }

    std::vector< std::vector<int> > solutions = exper.runIterImprove(neighbourhood, pivotRule);
  }

  //Run rest of 100_20 instances
  for (int i = 10; i <= 30; ++i)
  {
    string file = "../instances/100_20_" + to_string(i);
    PfspInstance instance;
    bool readOk = instance.readDataFromFile(file);
    Experiments exper(instance);

    std::vector<int> initialSolution;
    initSol.getInitialSolution(instance, initialSolution);

    Pivoting pivotRule;
    if(pivot.compare("best") == 0){
      pivotRule = new BestImprove(instance, initialSolution);
    } else {
      pivotRule = new FirstImprove(instance, initialSolution);
    }

    std::vector< std::vector<int> > solutions = exper.runIterImprove(neighbourhood, pivotRule);
  }

}



/***********************************************************************/

int main(int argc, char *argv[])
{

  if (argc == 1)
  {
    cout << "Usage: ./flowshopWCT <algorithm> --<pivot_rule> --<neighbourhood> --<initialization>" << endl;
    return 0;
  }




  testAll();


  return 0;
}
