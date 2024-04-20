#include "teoLC.h"

teoLC::teoLC(unsigned int num_throws, unsigned int num_bins)
{
    m_num_throws = num_throws;
    m_num_bins = num_bins;
    m_rnd = new Random;
}
void teoLC::uniLC(unsigned int num_random_variables, double a)
{
    m_a = a;
    ofstream fout("uni" + to_string(num_random_variables)+ ".dat");
    if(!fout.is_open()) throw runtime_error("error");
    
    myVect.clear();
    myVect.resize(m_num_bins);
    std::fill(myVect.begin(), myVect.end(), 0);

    for(int i=0; i<m_num_throws; i++) //devo lanciare n numeri random.
    {

        double appo = 0;
        for(unsigned int l=0; l < num_random_variables; l++) appo+=m_rnd->Rannyu();
        for(int j=0; j<m_num_bins; j++) 
        {    bool cond = appo/num_random_variables>(double)j*m_a && appo/num_random_variables<=(double)(j+1)*m_a; 
            if(cond == true) myVect[j]+=1;
        }
    } 
    for(int k=0; k<m_num_bins; k++) fout << k*m_a << " " << myVect[k] << endl;
    fout.close();

}


void teoLC::expLC(unsigned int num_random_variables, double lambda, double a)
{
    double m_a = a;
    ofstream fout("exp" + to_string(num_random_variables)+ ".dat");
    if(!fout.is_open()) throw runtime_error("error");
    
    myVect.clear();
    myVect.resize(m_num_bins);
    std::fill(myVect.begin(), myVect.end(), 0);

    for(int i=0; i<m_num_throws; i++) //devo lanciare n numeri random.
    {
        double appo = 0;
        for(unsigned int l = 0; l < num_random_variables; l++) appo+=m_rnd->Exp(lambda);
        for(int j=0; j<m_num_bins; j++) 
        {   
            bool cond = appo/num_random_variables>(double)j*m_a && appo/num_random_variables<=(double)(j+1)*m_a;  
            if(cond == true) myVect[j]+=1;
        }
    } 
    for(int k=0; k<m_num_bins; k++) fout << k*m_a << " " << myVect[k] << endl;
    fout.close();

}
void teoLC::lorentzianaLC(unsigned int num_random_variables, double T, double m, double a)
{
    m_a = a;
    ofstream fout("lorentziana" + to_string(num_random_variables)+ ".dat");
    if(!fout.is_open()) throw runtime_error("error");
    
    myVect.clear();
    myVect.resize(m_num_bins);
    std::fill(myVect.begin(), myVect.end(), 0);

    for(int i=0; i<m_num_throws; i++) //devo lanciare n numeri random.
    {
       
        double appo = 0;
        for(unsigned int l = 0; l < num_random_variables; l++) appo+=m_rnd->Lorentziana(T, m);
        for(int j=0; j<m_num_bins; j++) 
        { 
            bool cond = appo/num_random_variables>(double)j*m_a && appo/num_random_variables<=(double)(j+1)*m_a; 
            if(cond == true) myVect[j]+=1;
        }
        
    } 
    for(int k=0; k<m_num_bins; k++) fout << k*m_a << " " << myVect[k] << endl;
    fout.close();

}