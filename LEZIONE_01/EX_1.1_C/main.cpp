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
#include <string>
#include <cmath>
#include <vector>
//LIBRERIE PERSONALI
#include "random.h" //GENERATORE NUMERI CASUALI
//USING
using namespace std;
//COSTANTI
unsigned int const NUM_SUB_INTERVALS {100};
unsigned int const NUM_EXP {100};
unsigned int const NUM_THROWS {10000};
double const SUB_INTERVAL {(double)1/NUM_SUB_INTERVALS};
double const EXPECTED_VALUE {NUM_THROWS*SUB_INTERVAL};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
int main (int argc, char *argv[])
{
    //DICHIARAZIONE VARIABILI:

    //GENERATORE NUMERI CASUALI
    Random rnd; 
    //VARIABILE DOUBLE DI APPOGGIO	
    double sum=0.;
    double mean = 0.;
    //VECTOR
    vector<double> myTest;//DI DIMENSIONE PARI AL NUMERO DI ESPERIMENTI, CONTIENE LE STIME DI CHI2
    vector<double> myVect;//DI DIMENSIONE PARI AL NUMERO DI SOTTOINTERVALLI, CONTIENE LA QUANTITA' DI NUMERI CAUSALI CHE ESTRATTI CASUALMENTE VI
    //CADONO ALL'INTERNO

    ofstream fileout;
    fileout.open("test.dat");
    if(fileout.fail()) throw runtime_error("error");

    for(int k=0; k<NUM_EXP; k++) //CICLO SUL NUMERO DI ESPERIMENTI, CIOE' SULLE VALUTAZIONE DI CHI2
    {
        //AZZERAMENTO sum E myVect
        sum=0.;
        //DUE OPZIONI:
        //1)CREO AD OGNI CICLO UN NUOVE VETTORE DI LUNGHEZZA PARI AL NUMERO DI SOTTOINTERVALLI(BIN) E VALORE ZERO
        //vector<double> myVect(NUM_SUB_INTERVALS, 0);
        //2)ALTRIMENTI, AD OGNI CICLO PULISCO IL VECTOR, LO RIDIMENTISONE E SETTO I VALORI A ZERO
        myVect.clear();
        myVect.resize(NUM_SUB_INTERVALS);
        std::fill(myVect.begin(), myVect.end(), 0);

        for(int i=0; i<NUM_THROWS; i++) //NUMERI RANDOM GENERATI, CIOE' IL NUMERO DI GETTI
        {
            double appo = rnd.Rannyu();
            for(int j=0; j<NUM_SUB_INTERVALS; j++) 
            { 
                bool cond = appo>=j*SUB_INTERVAL && appo<(j+1)*SUB_INTERVAL; 
                if(cond == true) myVect[j]+=1;
            }
        } 

        for(int i=0; i<NUM_SUB_INTERVALS; i++) sum+=pow(myVect[i]-EXPECTED_VALUE,2);//myVect[i] INDICA NUMERO DI ESTRAZIONE SUB-INT i-ESIMO
	
        myTest.push_back((double)sum/EXPECTED_VALUE);//STIMA CHI2
        cout << k << " " << myTest[k] << endl;
        fileout << k+1 << " " << myTest[k] << endl;

        mean += myTest[k]/NUM_SUB_INTERVALS;
    }

    cout << "MEDIA = " << mean << endl;

  

    fileout.close();
	
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