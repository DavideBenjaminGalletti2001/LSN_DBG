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
//LIBRERIE DI SISTEMA
#include <iostream>
#include <cmath>
#include <fstream>
//LIBRERIE PERSONALI
#include "data_blocking.h"
#include "random.h"
//USING NAMESPACE
using namespace std;


//DICHIARAIONE MEMBRI CLASSE DataBlocking:
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//COSTRUTTORE:
DataBlocking :: DataBlocking(unsigned int num_throws,unsigned int num_blocks)
{
    m_num_throws= num_throws;//NUMERO TOTALE DI GETTI = M
    m_num_blocks= num_blocks;//NUMERO TOTALE DI BLOCCHI = N
    m_num_throws_per_block=(int)m_num_throws/m_num_blocks;//NUMERO TOTALE DI GETTI PER BLOCCO = L
}

//DISTRUTTORE:
DataBlocking :: ~DataBlocking(){;}

//PRESENTAZIONE ANALISI DATA BLOCKING: TITOLO, AUTORE, NUMERO GETTI, NUMERO BLOCCHI, NUMERO GETTI PER BLOCCO
void DataBlocking:: printTitle(string title, string name)
{
    cout << "$-------------------------------------------$" << endl;
    cout << "TITOLO:  " <<  title << endl;
    cout << "AUTORE: " << name << endl;
    cout << "NUMERO GETTI: " << m_num_throws << endl;
    cout << "NUMERO_BLOCCHI: " << m_num_blocks << endl;
    cout << "NUMERO_GETTI_PER_BLOCCO: " << m_num_throws_per_block << endl;
    cout << "$-------------------------------------------$" << endl;   
 
}

//SETTAGGIO PARAMETRI: MODIFICA DEL NUMERO DI GETTI, NUMERO DI BLOCCHI
void DataBlocking :: setParameters(unsigned int num_throws, unsigned int num_blocks){
    m_num_throws = num_throws;
    m_num_blocks = num_blocks;
    m_num_throws_per_block=(int) m_num_throws/m_num_blocks;
}

//CALCOLO VALOR MEDIO SINGOLO BLOCCO E COSTRUZIONE DI UN VECTOR DI SIZE PARI AL NUMERO DI BLOCCO: 
void DataBlocking :: averagesBlocks(double sum )
{
    m_means.push_back(sum/static_cast<double>(m_num_throws_per_block));
}

//RESET DEI VECTOR
void DataBlocking::reset ()
{
    m_prog_means.clear();
    m_prog_means2.clear();
    m_prog_errors.clear();
    m_means.clear();
}

//CALCOLO MEDIE ED ERRORI PROGRESSIVI: 
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
        } 
    }
}

//PRINT SU DISPLAY: STAMPA MEDIE PROGRESSIVE, ERRORI PROGRESSIVI, ERRORI E MEDIE PROGRESSIVI INSIEME 
void DataBlocking::printProgMeans () const {
    for(auto x : m_prog_means) cout << x << " ";
}
void DataBlocking::printProgErrors () const {
    for(auto x : m_prog_errors) cout << x << " ";
}
void DataBlocking::printProgMeansErrors () const {
    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        cout << "***********************************************************" << endl;
        cout << " MISURA : " << k << endl;
        cout << " RIS : " << m_prog_means[k] << " ± " << m_prog_errors[k] << endl;
        cout << "***********************************************************" << endl;  
    }
}

//PRINT SU FILE: STAMPA SU FILE DI DEFAULT risulati.dat; STAMPA SU FILE CON NOME DI INPUT; STAMPA SU FILE CON NOME DI IMPUT E NUMERATI
void DataBlocking :: print()
{
    ofstream fileout;
    string ris;
    fileout.open("risultati.dat", ios::out);//APERTURA IN MODALITA' ios::out : IL FILE VIENE SOVRASCRITTO
    if (fileout.is_open())
    {
        cout << "VUOI SOVRASCRIVE IL FILE: y or n" << endl;
        cin >> ris;
        if(ris != "y") throw runtime_error("INTERRUZIONE FORZATA: NON SOVRASCRITTURA FILE");
    }
	
    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        fileout << k << " " << m_prog_means[k] << " " << m_prog_errors[k] << endl;  
    }

    fileout.close();
};

void DataBlocking:: print(string filename)
{
    ofstream fileout(filename.c_str());
    if(fileout.fail()) throw runtime_error("IL FILE NON SI TROVA: ERRORE!");

    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        fileout << k << " " << m_prog_means[k] << " " << m_prog_errors[k] << endl;
    }

    fileout.close();
}

void DataBlocking::print(string filename, unsigned int num)
{
    string fappo = filename + to_string(num) + ".dat";
    ofstream fileout(fappo.c_str());
    if (!fileout.good()) throw runtime_error("IL FILE NON SI TROVA: ERRORE!");

    for(unsigned int k = 0; k < m_num_blocks; k++)
    {
        fileout << k << " " << m_prog_means[k] << " " << m_prog_errors[k] << endl;
    }
    
    fileout.close();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//


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

