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
#include <iostream>
#include <cmath>
#include <fstream>
#include "data_blocking.h"
#include "random.h"

using namespace std;

DataBlocking :: DataBlocking(unsigned int num_throws,unsigned int num_blocks)
{
    m_num_throws= num_throws;
    m_num_blocks= num_blocks;
    m_num_throws_per_block=(int)m_num_throws/m_num_blocks;
}

DataBlocking :: ~DataBlocking(){;}

void DataBlocking :: setParameters(unsigned int num_throws, unsigned int num_blocks){
    m_num_throws = num_throws;
    m_num_blocks = num_blocks;
    m_num_throws_per_block=(int) m_num_throws/m_num_blocks;
}

void DataBlocking :: averagesBlocks(double sum)
{
    m_means.push_back(sum/static_cast<double>(m_num_throws_per_block));
}


void DataBlocking :: computeProgMeansErrors()
{

    for(int i=0; i<m_num_blocks; i++)
    {
        double appo_prog_sum = 0;
        double appo_prog_sum2 = 0;

        for(int j=0; j<i+1; j++)
        {
            appo_prog_sum+=m_means[j]; //sommo le medie
            appo_prog_sum2+=pow(m_means[j],2.); //sommo le medie al quadrato
        }
        m_prog_means.push_back(appo_prog_sum/(i+1)); //medie progressive	
        m_prog_means2.push_back(appo_prog_sum2/(i+1)); //media progressive sui quadrati	
        if(i==0)
        {
            m_prog_errors.push_back(0.);
        }else{
            m_prog_errors.push_back(sqrt((m_prog_means2[i]-pow(m_prog_means[i],2))/(double)i));
            m_prog_errors[i] = (0.5*m_prog_errors[i]*sqrt(m_prog_means[i]))/m_prog_means[i];
            
        } 
    }
}

void DataBlocking::reset()
{
    m_prog_errors.clear();
    m_prog_means2.clear();
    m_prog_means.clear();
    m_means.clear();
}


void DataBlocking::printProgMeans () const {
    for(auto x : m_prog_means) cout << x << " ";
}
void DataBlocking::printProgErrors () const {
    for(auto x : m_prog_errors) cout << x << " ";
}
void DataBlocking::printProgMeansErrors () const {
    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        cout << k << " " << m_prog_means[k] << " " << m_prog_errors[k] << endl;  
    }
}


void DataBlocking :: print(string namefile)
{
    ofstream fileout;
    fileout.open(namefile, ios::out);
	
    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        fileout << k << " " << m_prog_means[k] << " " << m_prog_errors[k] << endl;  
    }

    fileout.close();
};

void DataBlocking:: print(string namefile, unsigned int num)
{
    ofstream fileout;
    string fname = namefile + to_string(num) + ".dat";
    fileout.open(namefile, ios::out);

    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        fileout << k << " " << m_prog_means[k] << " " << m_prog_errors[k] << endl;
    }

    fileout.close();
}


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



