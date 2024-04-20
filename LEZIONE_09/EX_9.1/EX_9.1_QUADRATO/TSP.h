#ifndef __TSP__
#define __TSP__

#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <random>
#include "GAs.h"
#include "city.h"
#include "random.h"
#include "funtore.h"
template<typename T> void swap(typename vector<T>::iterator &ia, typename vector<T>::iterator &ib)
{
    typename vector<T>::iterator ic;
    ic = ia;
    ia = ib;
    ib = ic;
}


//template<typename T> class TSP;

template<typename T> class TSP : public GAs<T>
{
    public:
        
        TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen);
        TSP(int dim_chr, int dim_pop, int dim_gen);
        //void setProblem();
        void reproduction(int);
        void reproductionAll(int);
        void compute_print_nextGen(int);
        void print_best_config_nextGen(int);
        void swap_chr_elements(int a);
        void shift2_chr_elements(int a);
        void shift3_chr_elements(int a);
        void shift4_chr_elements(int a);
        void shift5_chr_elements(int a);
        void shift6_chr_elements(int a);
        void reverse_chr_elements(int a);
        void permutation_chr_elements(int a);
        void shuffle_chr_elements(int a);
        void crossover(int num_scambi,vector<typename vector<T>::iterator>& Ison, vector<typename vector<T>::iterator>& IIson );
        void mutations(int a);
        void verify(vector<vector<typename vector<T>::iterator>>& v);
    
        
    protected:
        int m_dim_chr;
        int m_dim_pop;
        int m_dim_swap;
        int m_dim_gen;
        int c = 0;
        int d = 0;
        Random *m_rnd;
        vector<T> m_cities;
        vector<typename vector<T>::iterator> m_chr;
        vector<vector<typename vector<T>::iterator>> m_pop;
        vector<vector<typename vector<T>::iterator>> m_next_gen;
        vector<vector<typename vector<T>::iterator>> m_pop_primi;
        vector<vector<typename vector<T>::iterator>> m_pop_ref;
        vector<typename vector<T>::iterator> Ison ;
        vector<typename vector<T>::iterator> IIson ;
        Funtore<T>* m_fun;
        ofstream of1, of2, of_conf;
       
      
   
};

template <typename T> void TSP<T>::verify(vector<vector<typename vector<T>::iterator>>& v)
{
    
    for (int k = 0; k < v.size(); k++)
    {
        
        for(int j = 1; j<v[k].size()-2; j++)
        {
            int conta = 0;
            for(int i = j+1; i < v[k].size();i++){
                if(*(v[k][i])==*(v[k][j])) 
                   throw runtime_error("ripetizione" + to_string(conta));
                
            }
            conta++;
        }
    }
}


//COSTRUTTORE TSP
template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop, int dim_gen) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");

    m_fun = new Funtore<T>{};

    T c ;

    for (int k = 0; k < m_dim_chr-1; k++)
    {
        c.setRan();
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ )
        m_chr.push_back(it);//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(m_cities.begin());//lunghezza m_dim_chr+1
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)//CICLO SU NUMERO vector DI ITERATORI
    {  
        random_shuffle(m_pop[k].begin()+1, m_pop[k].end()-1);
    } 
    
    sort(m_pop.begin(), m_pop.end(), myComp<T>);//ORDINO IN MODO CRESCENTE LA POPOLAZIONE
                                             //VALUTANDO LA FUNZIONE COSTO PER CIASCUNO
                                             //CROMOSOMA(PERCORSO).
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));//COPIO LA POPOLAZIONE IN VARIABILE FISSA

};

template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_gen = dim_gen;
    m_dim_swap = dim_swap;
    m_rnd = new Random;
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");

    m_fun = new Funtore<T>{};

    T c ;

    for (int k = 0; k < m_dim_chr-1; k++)
    {
        c.setRan();
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ )
        m_chr.push_back(it);//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(m_cities.begin());//lunghezza m_dim_chr+1
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)//CICLO SU NUMERO vector DI ITERATORI
    {
        
        for(int j = 0; j < m_dim_swap; j++)//CICLO PER OGNUNO vector DI ITERATORI
        {                                  //E SI MODIFICA L'ORDINE DEGLI ITERATORI
                                           //AL SUO INTERNO
            int a = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << a << endl;
            int b = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << b << endl;
            swap(m_pop[k][a], m_pop[k][b]);
        }
        //IN PRATICA, CONSIDERANDO PER ESEMPIO CHE L'ITERATORE CHE PUNTAVA INIZIALMENTE 
        //IN POSIZIONE 2 VIENE SCAMBIATO CON QUELLO CHE ERA IN POSIZIONE 3, ALLORA
        //SI HA CHE IL COMMESSO VIAGGIATORE E' COME SE PASSASSE PRIMA DALLA
        //CITTA' TRE CHE DALLA CITTA' 1.
        
    } 
    
    sort(m_pop.begin(), m_pop.end(), myComp<T>);//ORDINO IN MODO CRESCENTE LA POPOLAZIONE
                                             //VALUTANDO LA FUNZIONE COSTO PER CIASCUNO
                                             //CROMOSOMA(PERCORSO).
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));//COPIO LA POPOLAZIONE IN VARIABILE FISSA

};


//METODO RIPRODUZIONE: NEL MAIN, SI DOVRA' CICLARE SUL NUMERO DI GENERAZIONI
template <typename T> void TSP<T>::reproduction(int num_scambi)
{ 
    
    m_next_gen = m_pop_ref;
    
       
    for(int j = 0; j < m_dim_pop-1; j+=2)
    {
        // Seleziono due genitori a caso. La quarta potenza aiuta a selezionare i migliori genitori, CIOE' QUELLI
        // CON DISTANZA -FUNZIONE COSTO- MINORE
        int a = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 3.));//SELEZIONO RANDOMICAMENTE UN PERCORSO(GENITORE)
        int b = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 3.));//SELEZIONE RANDOMICAMENTE UN PERCORSO(GENITORE)

       
        Ison = m_pop[a];
  
        IIson = m_pop[b];
        
       crossover(num_scambi, Ison, IIson);

        //cout << j << endl; 
        //verify(m_pop);

        m_next_gen[j+1] = Ison;
      
        m_next_gen[j] = IIson;
            
        mutations(j);

    }
   
    m_next_gen[0] = m_pop[0];

    

    //sort(m_pop.begin(), m_pop.end(), myComp<T>);
    
    // SI DISTRUGGE LA VECCHIA POPOLAZIONE
    

}

//STAMPO SU FILE LA K-ESIMA GENERAZIONE
template <typename T> void TSP<T>::compute_print_nextGen(int k)
{
    double media = 0.;
    for (int i = 0; i < m_dim_gen / 2; i++)
        media += m_fun->operator()(m_next_gen[i]);
    of2 << k << " " << media / ((double)m_dim_gen / 2.) << endl;


    sort(m_next_gen.begin(), m_next_gen.end(), myComp<T>);
        
    of1 << k << " " << m_fun->operator()(m_next_gen[0]) << endl;
    m_pop = m_next_gen;
}
//STAMPO MIGLIORE INDIVIDUO DELLA POPOLAZIONE APPARTENTE ALLA NUOVA GENERAZIONE:
template <typename T> void TSP<T>::print_best_config_nextGen(int k)
{
    of_conf.open("./Configurazioni/configurazione" + to_string(k) + ".dat");
    for (typename vector<typename vector<T>::iterator>::iterator it = m_next_gen[0].begin(); it != m_next_gen[0].end(); it++)
    {
        of_conf << (*it)->getX() << " " << (*it)->getY() << endl;
    }
    of_conf.close();
}

//METODO crossover
template<typename T> void TSP<T>::crossover(int num_scambi,vector<typename vector<T>::iterator>& Ison, vector<typename vector<T>::iterator>& IIson )
{ 
    if(m_rnd->Rannyu() > 0.5){
        vector<typename vector<T>::iterator> v = IIson;
        typename vector<T>::iterator i;
        i = *(IIson.end() -1 -num_scambi);
        int s = 0;
        for (auto it = Ison.begin()+1; it != Ison.end()  -1; it++)
        {
            bool b = false;
            for (auto id = IIson.begin()+1; id != IIson.end()  -num_scambi-1; id++)
            {
                if(*(*it) == *(*id)) {b = true;}
            }
            if (b == false) {
                    i = *it;
                    s++;
                    i=i+s;
                }
        }
        
        i = *(Ison.end() -1 -num_scambi);
        s = 0;
        for (auto it = IIson.begin()+1; it != IIson.end()  -1; it++)
        {
            bool b = false;
            for (auto id = Ison.begin()+1; id != Ison.end()  -num_scambi-1; id++)
            {
                if(*(*it) == *(*id)) {b = true;}
            }
            if (b == false) {
                    i = *it;
                    s++;
                    i=i+s;
                }
        }
        

        
    }

}
//METODO MUTAZIONE: SWAP ELEMENTI
template<typename T> void TSP<T>::swap_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        int i=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1 ;
        int j=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1;
        std::swap(m_next_gen[a][i], m_next_gen[a][j]);
      
        
        
    } 
}

//METODO MUTAZIONE SHIFT

template<typename T> void TSP<T>::shift2_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+2, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}
template<typename T> void TSP<T>::shift3_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+3, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::shift4_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+3, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}
template<typename T> void TSP<T>::shift5_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+5, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::shift6_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+5, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::shuffle_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        random_shuffle(vec.begin()+1, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::permutation_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        next_permutation(vec.begin()+1, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::reverse_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <typename vector<T>::iterator> vec = m_next_gen[a];
        reverse(vec.begin()+1, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

//METODO MUTAZIONE: CONTIENE TUTTE LE MUTAZIONI
template<typename T> void TSP<T>::mutations(int a)
{    
    //Prima mutazione: scambio di due elementi.
    swap_chr_elements(a);

    //Seconda mutazione: shift.
    
    shift2_chr_elements(a);

    //shift3_chr_elements(a);

    //shift4_chr_elements(a);

    //shift5_chr_elements(a);

    //shift6_chr_elements(a);

    shuffle_chr_elements(a);

    permutation_chr_elements(a);

    reverse_chr_elements(a);

}

//METODO RIPRODUZIONE: RIASSUME TUTTO
template <typename T> void TSP<T>::reproductionAll(int num_scambi)
{
    
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");
    for(int k = 0; k < m_dim_gen; k++)
    {
        //pr1 << m_fun->operator()(m_next_gen[0]) << endl;  
        m_next_gen = m_pop_ref; 
        for(int j = 0; j < m_dim_pop-1; j+=2)
        {
            // Seleziono due genitori a caso. La quarta potenza aiuta a selezionare i migliori genitori, CIOE' QUELLI
            // CON DISTANZA -FUNZIONE COSTO- MINORE
            
            int a = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 3.));//SELEZIONO RANDOMICAMENTE UN PERCORSO(GENITORE)
            int b = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 3.));//SELEZIONE RANDOMICAMENTE UN PERCORSO(GENITORE)
       
            Ison = m_pop[a];
  
            IIson = m_pop[b];
            

            crossover(num_scambi, Ison, IIson);

            
            

            m_next_gen[j+1] = Ison;
      
            m_next_gen[j] = IIson;

            //pr2 << m_fun->operator()(m_next_gen[0]) << endl;  
            
            mutations(j);
            

        }
        
        
        
        m_next_gen[0] = m_pop[0];
        
        
        //m_next_gen[k] = m_pop[k];

        double media = 0.;
        for (int i = 0; i < m_dim_gen / 2; i++)
            media += m_fun->operator()(m_next_gen[i]);
        of2 << k << " " << media / ((double)m_dim_gen / 2.) << endl;

        sort(m_next_gen.begin(), m_next_gen.end(), myComp<T>);
        
        of1 << k << " " << m_fun->operator()(m_next_gen[0]) << endl;

        if (k % 10 == 0)//OGNI 10 GENERAZIONI MEMORIZZO LA CONFIGURAZIONE FINALE CHE IN QUELLA GENERAZIONE-POPOLAZIONE MINIMIZZA LA FUNZIONE COSTO:
        {
        // cout << k << endl;
            of_conf.open("./Configurazioni/configurazione" + to_string(k) + ".dat");
            for (typename vector<typename vector<T>::iterator>::iterator it = m_next_gen[0].begin(); it != m_next_gen[0].end(); it++)
            {
                of_conf << (*it)->getX() << " " << (*it)->getY() << endl;
            }
            //of_conf << m_next_gen[0][0]->getX() << " " << m_next_gen[0][0]->getY()<< endl;
            of_conf.close();
        }

        // SI DISTRUGGE LA VECCHIA POPOLAZIONE
        m_pop = m_next_gen;
    }

    cout << "Configurazione finale " << endl;

    for (int i = 0; i < m_dim_pop; i++)
    {
        // popolazione[i].Print();
        cout << i << " " << m_fun->operator()(m_pop[i]) << endl;
    }

    of1.close();
    of2.close();
    of_conf.close();
}


#endif