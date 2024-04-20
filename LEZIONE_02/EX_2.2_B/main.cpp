/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Stud. Davide Benjamin Galletti
_/    _/  _/_/_/  _/_/_/_/ email: davidebenjamin.galletti@studenti.unimi.it
                          ultima modifica: 13/02/2024
*****************************************************************
*****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "random.h"
#include "data_blocking.h"
#include "random_walk.h"
#include <cmath>

using namespace std;

unsigned int const NUM_THROWS {10000};
unsigned int const NUM_BLOCKS {100};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};
unsigned int const NUM_PATH {100};
double const A {1.0};


int main (int argc, char *argv[]){

    RandomWalk myRW {A, NUM_THROWS, NUM_BLOCKS, NUM_PATH};

    myRW.computeContinue();
    myRW.printContinue();

    return 0;
}


/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Stud. Davide Benjamin Galletti
_/    _/  _/_/_/  _/_/_/_/ email: davidebenjamin.galletti@studenti.unimi.it
                          ultima modifica: 13/02/2024
*****************************************************************
*****************************************************************/
