#ifndef __GAs__
#define __GAs__

#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <random>

#include "city.h"
#include "random.h"
#include "funtore.h"

using namespace std;




template<typename T> class GAs
{
    public:
        GAs(){;};
        virtual void reproduction(int) = 0;
        virtual void reproductionAll(int) = 0;
        virtual void compute_print_nextGen(int) = 0;
        virtual void print_best_config_nextGen(int) = 0;
        virtual void swap_chr_elements(int) = 0;
        virtual void shift_chr_elements(int ) =0;
        virtual void crossover(int ,vector<typename vector<T>::iterator>& , vector<typename vector<T>::iterator>&) = 0;
        virtual void mutations(int) = 0;
    protected:
        
        
};





//***************************************************GAs**********************************************************//


//***************************************************GAs**********************************************************//
//***************************************************TSP**********************************************************//







#endif