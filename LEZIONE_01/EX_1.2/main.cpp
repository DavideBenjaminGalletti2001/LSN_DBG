
//LIBRERIE DI SISTEMA
#include <vector>
#include <fstream>  

//LIBRERIE PERSONALI
#include "random.h"
#include "teoLC.h"

unsigned int const NUM_THROWS {100000};
unsigned int const NUM_BINS {100};
double const A1 {0.01};
double const A2 {0.05};
double const A3 {0.1};
double const LAMBDA {5.};
double const T {1.};
double const M {5};

int main(int argc, char* argv[])
{
    teoLC myLC(NUM_THROWS, NUM_BINS);
    vector<unsigned int> myNum {1,2, 10,100};
    for(unsigned int r = 0; r < myNum.size(); r++)
    {
        myLC.uniLC(myNum[r], A1);
        myLC.expLC(myNum[r],LAMBDA, A2);
        myLC.lorentzianaLC(myNum[r], T, M, A3);
    }


    return 0;
}