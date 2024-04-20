

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
//LIBRERIE DI SISTEMA
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
//LIBRERIE PERSONALI
#include "random.h"
#include "data_blocking.h"
#include "metropolis.h"
//USING 
using namespace std;
//COSTANTI
unsigned int const NUM_THROWS {100000};



unsigned int const NUM_BLOCKS {150};


unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};
double const X {0.};
double  const MU {-0.803921};
double const SIGMA {0.618992};




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

int main (int argc, char *argv[]){

    Random rnd;
    remove("energia.dat");

    double sum=0.;
    DataBlocking bl {NUM_THROWS, NUM_BLOCKS};
    Metropolis mt {X, "funzione_onda.dat"};

    auto lambda = [] (double x) -> double {return  exp(-pow(x-MU,2)/pow(SIGMA,2))+exp(-pow(x+MU,2)/pow(SIGMA,2))+2.*exp(-(pow(x,2)+pow(MU,2))/pow(SIGMA,2));};
    auto funzione_onda = [] (double x)-> double {return exp(-pow(x-MU,2)/(2.*pow(SIGMA,2)))+exp(-pow(x+MU,2)/(2.*pow(SIGMA,2)));};

    auto Pot = [&] (double x) -> double {return ((pow(x,4)-2.5*pow(x,2))*funzione_onda(x))/funzione_onda(x);};
    auto Ekin = [&] (double x) -> double {
        double p1= exp(-pow(x-MU,2)/(2.0*pow(SIGMA,2)));
        double p2= exp(-pow(x+MU,2)/(2.0*pow(SIGMA,2)));
        double p3= 1.0-(pow(x-MU,2)/pow(SIGMA,2));
        double p4= 1.0-(pow(x+MU,2)/pow(SIGMA,2));
        return ((1./(2.*pow(SIGMA,2)))*(p1*p3+p2*p4))/(double)funzione_onda(x);} ;
    auto E = [&] (double x) -> double {return Ekin(x) + Pot(x);};

    bl.reset();
    mt.reset();
    mt.equilibrazione(lambda);
    for(int i=0; i<NUM_BLOCKS; i++)
    {
        sum=0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) mt.move(sum, lambda, E);
        bl.averagesBlocks(sum);
    } 
    bl.computeProgMeansErrors();
    bl.print("energia.dat");
             
    

  
    return 0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

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

