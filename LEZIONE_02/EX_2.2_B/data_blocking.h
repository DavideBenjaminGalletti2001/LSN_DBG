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


#ifndef __DATABLOCKING_H__
#define __DATABLOCKING_H__

//LIBRERIE DI SISTEMA
#include <vector>
#include <string>
#include <fstream>

//USING
using namespace std;

//CLASSE DATABLOCKING
class DataBlocking 
{
    public:
        DataBlocking(unsigned int,unsigned int); //COSTRUTTORE
        ~DataBlocking(); //DISTRUTTORE

        void setParameters(unsigned int, unsigned int);
        void averagesBlocks(double);
        void computeProgMeansErrors();
        void print(string namefile);
        void print(string namefile, unsigned int num);
        void print_error(string namefile);
        vector<double> getMeans () const {return m_means;};
        vector<double> getProgMeans () const {return m_prog_means;};
        vector<double> getProgMeans2 () const {return m_prog_means2;};
        vector<double> getProgErrors () const {return m_prog_errors;};
        double getThrows() const {return m_num_throws;};
        double getBlocks() const {return m_num_blocks;};
        double getElementsPerBlock() const {return m_num_throws_per_block;};
        void printProgMeans () const ;
        void printProgErrors () const;
        void printProgMeansErrors () const;
        void reset() ;
	
    private:
        unsigned int m_num_throws; //numero di tentativi totali.
        unsigned int m_num_blocks; //numero di blocchi totali.
        unsigned int m_num_throws_per_block; //quanti tentativi nel blocco.
        vector<double> m_means;
        vector<double> m_prog_means;
        vector<double> m_prog_means2;
        vector<double> m_prog_errors;
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
