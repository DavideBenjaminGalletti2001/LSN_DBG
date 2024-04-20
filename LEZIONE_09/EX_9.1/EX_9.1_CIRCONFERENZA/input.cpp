#include "input.h"
void input(int& dim_chr, int& dim_pop, int& dim_swap, int& dim_gen, int& dim_scambi)
{
    fstream input {"input.dat", ios::in};
    input >> dim_chr;
    input >> dim_pop;
    input >> dim_swap;
    input >> dim_gen;
    input >> dim_scambi;
    input.close();
}