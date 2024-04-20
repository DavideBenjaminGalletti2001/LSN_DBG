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
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

//LIBRERIE PERSONALI
#include "random.h"
#include "data_blocking.h"

//USING
using namespace std;

//COSTANTI
unsigned int const NUM_THROWS {10000000};
unsigned int const NUM_BLOCKS {100};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

int main (int argc, char *argv[]){

    Random rnd;//GENERATORE NUMERI CASUALI
    double sum=0.;
    DataBlocking bl {NUM_THROWS, NUM_BLOCKS};//CLASSE DATABLOCKING

    bl.printTitle("Calcolo Integrale", "Davide Benjamin Galletti");

    for(int i=0; i<NUM_BLOCKS; i++)//CICLO NUMERO BLOCCHI
    {
        sum=0.;
        for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) sum+=rnd.Rannyu();//CICLO ELEMENTI PER BLOCCO
        bl.averagesBlocks(sum);//CALCOLO VALORE SINGOLO BLOCCO
        
    }
 
    bl.computeProgMeansErrors();//CALCOLO MEDIE ED ERRORI PROGRESSIVI
    bl.printProgMeansErrors();//PRINT SU TERMINALE
	
    bl.print();//PRINT SU FILE risultati.dat
  
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
