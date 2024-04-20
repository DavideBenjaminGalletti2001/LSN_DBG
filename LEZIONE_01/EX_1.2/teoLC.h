/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __TEOLC_H__
#define __TEOLC_H__

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#include "random.h"
class teoLC {

    private:
        Random* m_rnd;
        unsigned int m_num_throws;
        unsigned int m_num_bins;
        double m_a;
        vector<double> myVect;

    public:
    // Default constructor
        teoLC(unsigned int num_throws, unsigned int num_bins);
    // Destructor
        ~teoLC(){;};
        void uniLC(unsigned int num_random_vairables, double a);
        void expLC(unsigned int num_random_variables, double lambda, double a);
        void lorentzianaLC(unsigned int num_random_variables, double T, double m, double a);

};

#endif // __TEOLC_H__

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
