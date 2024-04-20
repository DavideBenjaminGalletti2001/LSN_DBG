#include "main.h"
using namespace std;


int main()
{
    int dim_chr, dim_pop, dim_swap, dim_gen, dim_scambi;

    input(dim_chr, dim_pop, dim_swap, dim_gen,dim_scambi); 

    TSP<city_circ> myTSP{dim_chr, dim_pop, dim_gen};

    //vector<typename vector<city_circ>::iterator> myV = myTSP.get_best_chr();
      
    for (int k = 0; k < dim_gen; k++)
    {
        myTSP.reproduction(dim_scambi);
        myTSP.compute_print_nextGen(k);
        if(k%10==0){
            myTSP.print_best_config_nextGen(k);
            //myV = myTSP.get_best_chr();
        }
    } 
    
    
}