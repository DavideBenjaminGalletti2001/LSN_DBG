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
#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "random.h"
#include "data_blocking.h"
#include "metropolis.h"

using namespace std;

unsigned int const NUM_THROWS {10000};
unsigned int const NUM_BLOCKS {10};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};


int main (int argc, char *argv[]){


    Random rnd;

    string file1="ris.dat";
    string file_1s = "rw.dat";
    double sum1=0.;
    DataBlocking bl1 {NUM_THROWS, NUM_BLOCKS};
    Metropolis mt1 {X, file_1s};
    Metropolis mt2 {MU,SIGMA,file_1s}:

    fstream of {"energia.dat", ios::app};
   
    vector<double> myE;
    bl1.reset();
    mt1.reset();
    mt1.equilibrazione(lambda);

    vector<double> myT;
    int num_T;
    for( int t = 0; t < num_T; t++) myT.push_back(1-0.1*t);
    cout << "NUM T:" << num_T << endl;
    double SIGMA, MU;
    fstream of("output_e.dat", ios::out);
    for (int k = 0; k < myT.size(); k++)
    {
        auto lambda = [] (double x) -> double {return  exp(-pow(x-MU,2)/pow(SIGMA,2))+exp(-pow(x+MU,2)/pow(SIGMA,2))+2.*exp(-(pow(x,2)+pow(MU,2))/pow(SIGMA,2));};
        auto funzione_onda = [] (double x)-> double {return exp(-pow(x-MU,2)/(2.*pow(SIGMA,2)))+exp(-pow(x+MU,2)/(2.*pow(SIGMA,2)));};

        auto Pot = [&] (double x) -> double {return ((pow(x,4)-2.5*pow(x,2))*funzione_onda(x))/funzione_onda(x);};
        auto Ekin = [&] (double x) -> double {
        double pezzo1= exp(-pow(x-MU,2)/(2.0*pow(SIGMA,2)));
        double pezzo2= exp(-pow(x+MU,2)/(2.0*pow(SIGMA,2)));
        double pezzo3= 1.0-(pow(x-MU,2)/pow(SIGMA,2));
        double pezzo4= 1.0-(pow(x+MU,2)/pow(SIGMA,2));
        return ((1./(2.*pow(SIGMA,2)))*(pezzo1*pezzo3+pezzo2*pezzo4))/(double)funzione_onda(x);} ;
        auto E = [&] (double x) -> double {return Ekin(x) + Pot(x);};
        auto Boltz = [&] (double e) -> double {return exp(-b*e);};
        
        for(int i=0; i<NUM_BLOCKS; i++)
        {
            sum1=0.;
            for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) mt1.move(sum1, lambda, E);
            bl1.averagesBlocks(sum1);
        }  
        bl1.computeProgMeansErrors();
        double app = bl1.getFinalValue();
        aSIGMA = SIGMA;
        aMU = MU;
        SIGMA = rnd.rannyu(SIGMA - DELTA, SIGMA +DELTA);
        MU = rnd.rannyu(MU - DELTA, MU +DELTA);
        bl1.reset();
        mt1.reset();
        mt1.equilibrazione(lambda);
        for(int i=0; i<NUM_BLOCKS; i++)
        {
            sum1=0.;
            for(int j=0; j<NUM_THROWS_PER_BLOCK; j++) mt1.move(sum1, lambda, E);
            bl1.averagesBlocks(sum1);
        }  
        bl1.computeProgMeansErrors();
        double appo = bl1.getFinalValue();
        
        double A = Boltz(app)/Boltz(appo);
        attempted++;
        s = 0;
        if(A >=1)
        {
            accepted++;
            s = 1;
        }else if(rnd.Rannyu()<=A){
            accepted++;
            s=1;
            }else{
                SIGMA =nSIGMA;
                MU=nMU;
                
            }
        if (s == 1)
            of << SIGMA << " " << MU << " " << endl;  
        
        
        

    }
    
    
    //bl1.printProgMeansErrors();
    bl1.print_final(file1, MU, SIGMA);
  


  
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

