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


#include "random_walk.h"

RandomWalk::RandomWalk(double a)
{
    m_a = a;
    m_rnd = new Random();


}
RandomWalk::RandomWalk(double a, unsigned int num_throws, unsigned int num_blocks, unsigned int num_path)
{
    m_a = a;
    m_rnd = new Random();
    m_b = new DataBlocking(num_throws, num_blocks);  
    m_path = num_path;  
    remove("random_walk_discrete.dat");
}

void RandomWalk::reset()
{
    m_result_errors.clear();
    m_result_errors.clear();
    delete m_rnd;
}

RandomWalk::~RandomWalk(){;};

void RandomWalk::moveDiscrete(unsigned int lenght)
{
    double result;
    double appo {0.};
    double sumx {0.};
    double sumy {0.};
    double sumz {0.};

    for(unsigned int m = 0; m < lenght; m++)
    {
        double dir = m_rnd->Rannyu(0., 3.);
        if(dir >= 0. and dir < 1.)
        {
            if(m_rnd->Rannyu()>=0.5)
            {
                sumx+=m_a;
            }else{
                sumx-=m_a;
            }

        }else{
            if(dir>= 1. and dir <2.)
            {
                if(m_rnd->Rannyu()>=0.5)
                {
                    sumy+=m_a;
                }else{
                    sumy-=m_a;
                }
            }else{
                if(dir>=2. and dir <=3)
                {
                    if(m_rnd->Rannyu()>=0.5)
                    {
                        sumz+=m_a;
                    }else{
                        sumz-=m_a;
                    }
                }else{
                    throw runtime_error("how is it possible???");
                }
            }
        }
    } 
    result = (pow(sumx,2) +pow(sumy,2) + pow(sumz,2));
    m_sum += result;
    fileout.close();
};

double RandomWalk::getRW_Discrete() const {return m_sum;};

void RandomWalk::computeDiscrete()
{
    

    for(unsigned int k = 0; k < m_path;k++)
    {
        m_b->reset();
        for(int i=0; i<m_b->getBlocks(); i++)
        {
            m_sum = 0;
            for(int j=0; j<m_b->getElementsPerBlock(); j++){
                moveDiscrete(k);    
            }
            m_b->averagesBlocks(m_sum);
                   
        }
        m_b->computeProgMeansErrors();
        vector<double> vMeans = m_b->getProgMeans();
        vector<double> vErrors = m_b->getProgErrors();
        m_result_means.push_back(sqrt(vMeans[m_b->getBlocks()-1]));
        if (k == 0)
            m_result_errors.push_back(0.);
        else 
            m_result_errors.push_back(sqrt(vErrors[m_b->getBlocks()-1]));
    }
}

void RandomWalk::printDiscrete()
{
    ofstream of("rw_discrete.dat");
    if(of.fail()) throw runtime_error("error");
 
	for(unsigned int k = 0; k < m_b->getBlocks(); ++k)
    {
        of << k << " " << m_result_means[k] << " " << m_result_errors[k] << endl; 
    }
    of.close();
}

void RandomWalk::moveContinue(unsigned int lenght)
{
    double result;
    double sumx {0.};
    double sumy {0.};
    double sumz {0.};

    for(unsigned int m = 0; m < lenght; m++)
    {
       double phi = m_rnd->Rannyu(0. , 2*M_PI);
       double theta = m_rnd->Rannyu(0. , M_PI);
       sumx += m_a*sin(theta)*cos(phi);
       sumy += m_a*sin(theta)*sin(phi);
       sumz += m_a*cos(theta);
    } 
    result = (pow(sumx,2) +pow(sumy,2) + pow(sumz,2));
    m_sum += result;
    fileout.close();
};

void RandomWalk::computeContinue()
{
    

    for(unsigned int k = 0; k < m_path;k++)
    {
        m_b->reset();
        for(int i=0; i<m_b->getBlocks(); i++)
        {
            m_sum = 0;
            for(int j=0; j<m_b->getElementsPerBlock(); j++){
                moveContinue(k);    
            }
            m_b->averagesBlocks(m_sum);
                   
        }
        m_b->computeProgMeansErrors();
        vector<double> vMeans = m_b->getProgMeans();
        vector<double> vErrors = m_b->getProgErrors();
        m_result_means.push_back(sqrt(vMeans[m_b->getBlocks()-1]));
        if (k == 0)
            m_result_errors.push_back(0.);
        else 
            m_result_errors.push_back(sqrt(vErrors[m_b->getBlocks()-1]));
    }
}

void RandomWalk::printContinue()
{
    ofstream of("rw_continue.dat");
    if(of.fail()) throw runtime_error("error");
 
	for(unsigned int k = 0; k < m_b->getBlocks(); ++k)
    {
        of << k << " " << m_result_means[k] << " " << m_result_errors[k] << endl; 
    }
    of.close();    
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