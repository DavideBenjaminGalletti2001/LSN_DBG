#include "main.h"
using namespace std;


int main()
{
    int dim_chr, dim_pop, dim_swap, dim_gen, dim_scambi;

    input(dim_chr, dim_pop, dim_swap, dim_gen,dim_scambi); 

    TSP<city_quad> myTSL{dim_chr, dim_pop, dim_gen};

    //myTSL.reproductionAll(dim_scambi);
      
    for (int k = 0; k < dim_gen; k++)
    {
        myTSL.reproduction(dim_scambi);
        myTSL.compute_print_nextGen(k);
        if(k%10 == 0)
            myTSL.print_best_config_nextGen(k);
    } 
    
    
}