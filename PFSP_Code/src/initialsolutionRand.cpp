#include <iostream>
#include "initialsolutionRand.h"


using namespace std;

int RandInitialsolution::generateRndPosition(int min, int max)
{
  return ( rand() % max + min );
}

/* Fill the solution with numbers between 1 and nbJobs, shuffled */
void RandInitialsolution::getInitialSolution(PfspInstance & inst, vector< int > & sol)
{
  int nbJobs = inst.getNbJob();
  vector<bool> alreadyTaken(nbJobs+1, false); // nbJobs elements with value false
  vector<int > choosenNumber(nbJobs+1, 0);

  int nbj;
  int rnd, i, j, nbFalse;

  nbj = 0;
  for (i = nbJobs; i >= 1; --i)
  {
    rnd = generateRndPosition(1, i);
    nbFalse = 0;

    /* find the rndth cell with value = false : */
    for (j = 1; nbFalse < rnd; ++j)
      if ( ! alreadyTaken[j] )
        ++nbFalse;
    --j;

    sol[j] = i;

    ++nbj;
    choosenNumber[nbj] = j;

    alreadyTaken[j] = true;
  }
}