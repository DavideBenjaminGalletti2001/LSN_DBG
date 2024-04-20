#ifndef __DATABLOCKING_H__
#define __DATABLOCKING_H__

//LIBRERIE DI SISTEMA
#include <vector>

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
        void print();
        void print(string file);
        vector<double> getMeans () const {return m_means;};
        vector<double> getProgMeans () const {return m_prog_means;};
        vector<double> getProgMeans2 () const {return m_prog_means2;};
        vector<double> getProgErrors () const {return m_prog_errors;};
        void printProgMeans () const ;
        void printProgErrors () const;
        void printProgMeansErrors () const;
	
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
