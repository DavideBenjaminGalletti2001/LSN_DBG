/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "random.h"
#include "data_blocking.h"
#include "metropolis.h"

using namespace std;

unsigned int const NUM_THROWS {1000000};
unsigned int const NUM_BLOCKS {100};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};
double const rb {1.};
double const X1 {0.};
double const Y1 {0.};
double const Z1 {1.};
double const DELTA1 {1.2};
double const X2 {1.};
double const Y2 {1.};
double const Z2 {1.};
double const DELTA2 {3.0};

int main (int argc, char *argv[]){

    Random rnd;

    string file1="mt1.dat";
    string file_1s = "orbitale1s.dat";
    double sum1=0.;
    DataBlocking bl1 {NUM_THROWS, NUM_BLOCKS};
    Metropolis mt1 {X1,Y1,Z1,DELTA1, file_1s};
    auto lambda1 = [] (double x, double y, double z) -> double {return (pow(rb,-3)/(3.14))*exp((-2*sqrt(x*x+y*y+z*z))/rb);};

    mt1.equilibrazione(lambda1);


    for(int i=0; i<NUM_BLOCKS; i++)
    {
        sum1=0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) mt1.moveGauss(sum1, lambda1);
        bl1.averagesBlocks(sum1);
    }
 
    bl1.computeProgMeansErrors();
    bl1.printProgMeansErrors();
	
    bl1.print(file1);

    string file2="mt2.dat";
    string file_2p = "orbitale2p.dat";
    double sum2=0.;
    DataBlocking bl2 {NUM_THROWS, NUM_BLOCKS};
    Metropolis mt2 {X2,Y2,Z2,DELTA2, file_2p};
    auto lambda2 = [] (double x, double y, double z) -> double {return (pow(rb,-5)/(M_PI*32.0))*pow(z,2)*exp(-sqrt(x*x + y*y+z*z)/rb);};

    mt2.equilibrazione(lambda2);

    for(int i=0; i<NUM_BLOCKS; i++)
    {
        sum2=0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) mt2.moveGauss(sum2, lambda2);
        bl2.averagesBlocks(sum2);
    }
 
    bl2.computeProgMeansErrors();
    bl2.printProgMeansErrors();
	
    bl2.print(file2);


  
    return 0;
}


/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

