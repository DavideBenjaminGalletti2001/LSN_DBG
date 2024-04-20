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

#ifndef __RANDOM_WALK_H__
#define __RANDOM_WALK_H__

#include "random.h"
#include "data_blocking.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class RandomWalk
{   
    public:
        RandomWalk(double a);
        RandomWalk(double a, unsigned int num_throws, unsigned int num_blocks, unsigned int num_path);
        ~RandomWalk();

        void moveDiscrete(unsigned int lenght);
        void moveContinue(unsigned int lenght);
        void computeDiscrete();
        void computeContinue();
        double getRW_Discrete() const;
        void printDiscrete() ;
        void printContinue();
        void reset();

    private:
        double m_a;
        double m_sum;
        double m_path;
        ofstream fileout;
        Random *m_rnd;
        DataBlocking *m_b;
        vector<double> m_result_means;
        vector<double> m_result_errors;
};
    


#endif


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