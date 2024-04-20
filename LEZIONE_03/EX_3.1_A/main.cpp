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
#include "random.h"
#include "data_blocking.h"
#include "derivati.h"
#include <cmath>

using namespace std;

unsigned int const NUM_THROWS {10000};
unsigned int const NUM_BLOCKS {100};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};
double const PREZZO_INIZIALE=100.; //Prezzo iniziale.
double const TEMPO_SCADENZA=1.;       //Tempo dopo la quale scade l'opzione.
double const PREZZO_CONCORDATO=100.;     //Prezzo concordato.
double const TASSO_INTERESSE=0.1;      //Tasso d'interesse.
double const VOL=0.25;   //Volatilità.

int main (int argc, char *argv[]){

    Random rnd;

    string file1="call.dat";
    double sum1=0.;
    DataBlocking bl1 {NUM_THROWS, NUM_BLOCKS};
    DerivatiCall f1 {PREZZO_INIZIALE, PREZZO_CONCORDATO, TASSO_INTERESSE, VOL};

    for(int i=0; i<NUM_BLOCKS; i++)
    {
        sum1=0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) sum1+=f1(TEMPO_SCADENZA);
        bl1.averagesBlocks(sum1);
    }
 
    bl1.computeProgMeansErrors();
    bl1.printProgMeansErrors();
	
    bl1.print("call.dat");

    string file2 = "put.dat";
    double sum2=0.;
    DataBlocking bl2 {NUM_THROWS, NUM_BLOCKS};
    DerivatiPutt f2 {PREZZO_INIZIALE, PREZZO_CONCORDATO, TASSO_INTERESSE, VOL};

    for(int i=0; i<NUM_BLOCKS; i++)
    {
        sum2=0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) sum2+=f2(TEMPO_SCADENZA);
        bl2.averagesBlocks(sum2);
    }
 
    bl2.computeProgMeansErrors();
    bl2.printProgMeansErrors();
	
    bl2.print("put.dat");
  
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

