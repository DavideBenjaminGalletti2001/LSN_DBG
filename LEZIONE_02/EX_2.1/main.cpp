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
#include <cmath>

using namespace std;

unsigned int const NUM_THROWS {100000};
unsigned int const NUM_BLOCKS {100};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};


int main (int argc, char *argv[]){

    Random rnd;
    double sum1, sum2;
    double const k = M_PI/2.;
    
    DataBlocking bl1 {NUM_THROWS, NUM_BLOCKS};
    DataBlocking bl2 {NUM_THROWS, NUM_BLOCKS};
    string nf1 {"unif.dat"};
    string nf2 {"imp.dat"};
    auto f1 = [k] (double x) -> double {return k*cos(k*x);};
    auto f2 = [k] (double x) -> double {return (k*cos(k*x))/(-2.*x+2.);};


    for(int i=0; i<NUM_BLOCKS; i++)
    {
        sum1=0.;
        sum2 = 0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++){
            sum1+=f1(rnd.Rannyu());
            sum2+=f2(1+sqrt(1-rnd.Rannyu()));
        }
        bl1.averagesBlocks(sum1);
        bl2.averagesBlocks(sum2);
    }
 
    bl1.computeProgMeansErrors();
    bl1.printTitle("Integrale uniforme", "Davide Benjamin Galletti");
    bl1.printProgMeansErrors();
	
    bl1.print(nf1);
  
    bl2.computeProgMeansErrors();
    bl2.printTitle("Integrale importance sampling", "Davide Benjamin Galletti");
    bl2.printProgMeansErrors();
	
    bl2.print(nf2);

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

