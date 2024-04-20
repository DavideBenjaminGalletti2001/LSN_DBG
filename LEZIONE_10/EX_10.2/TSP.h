#ifndef __TSP__
#define __TSP__

#include <vector>
#include <functional>
#include <numeric>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include "GAs.h"
#include "city.h"
#include "random.h"

template<typename T> void swap(int& a , int& b)
{
    int c ;
    c = a;
    a = b;
    b = c;
}





//template<typename T> class TSP;

template<typename T> class TSP : public GAs<T>
{
    public:
        
        TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen);
        TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen, string file);
        TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen, string file, string fileLbest, string fileLmeans, int r);

        TSP(int dim_chr, int dim_pop,  int dim_gen);
        TSP(int dim_chr, int dim_pop,  int dim_gen, string file);
        TSP(int dim_chr, int dim_pop,  int dim_gen, string file, string fileLbest, string fileLmeans, int r);
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
        void swap_strong_chr();
        void perm_strong_chr();
        void permutation_chr_elements(int a);
        void shuffle_chr_elements(int a);
        void crossover(int num_scambi,vector<int>& Ison, vector<int>& IIson );
        void crossover1(int num_scambi,vector<int>& Ison, vector<int>& IIson );
        void crossover2(int num_scambi,vector<int>& Ison, vector<int>& IIson );
        void crossover3(int num_scambi,vector<int>& Ison, vector<int>& IIson );
        void mutations(int a);
        void verify(vector<vector<int>>& v);
        double operator()(vector<int>& v);

        vector<int>& getGivenValuePop(int k){return m_pop[k];};
        vector<vector<int>> getPop(){return m_pop;};
        vector<vector<int>> getNextGen(){return m_next_gen;};
        vector<vector<int>> getPopPrimi(){return m_pop_primi;};
        vector<vector<int>> getPopRef() {return m_pop_ref;};
        vector<int> getChr() {return m_chr;};
        vector<T> getCities(){return m_cities;};

        void setPop(vector<int>& v, int k){m_pop[k] = v;};

        void print_cities(){for(auto x : m_cities) x.print();};
        
    
        
    protected:

        int m_dim_chr;
        int m_dim_pop;
        int m_dim_swap;
        int m_dim_gen;

        Random *m_rnd;

        vector<T> m_cities;

        vector<int> m_chr;

        vector<vector<int>> m_pop;
        vector<vector<int>> m_next_gen;
        vector<vector<int>> m_pop_primi;
        vector<vector<int>> m_pop_ref;

        vector<int> Ison ;
        vector<int> IIson ;

        ofstream of1, of2, of_conf;
        ifstream input;
     
        
};



template <typename T> double TSP<T>::operator()(vector<int>& v)
{
    double sum = 0;
    
    for(int k = 0; k < v.size() -1 ; k++)
    {
        sum += m_cities[(v[k])](m_cities[v[k+1]]);
    }
    sum+=m_cities[(v[v.size()-1])](m_cities[v[0]]);

    return sum;
}

template <typename T> void TSP<T>::verify(vector<vector<int>>& v)
{
    
    for (int k = 0; k < v.size(); k++)
    {
        
        for(int j = 1; j<v[k].size()-2; j++)
        {
            int conta = 0;
            for(int i = j+1; i < v[k].size();i++){
                if((m_cities[v[k][i]])==(m_cities[v[k][j]]))
                   throw runtime_error("ripetizione" + to_string(conta));
                
            }
            conta++;
        }
    }
}

//COSTRUTTORE TSP
template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen, string file) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_swap = dim_swap;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
   
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");
    input.open(file);
    if(input.fail()) throw runtime_error(file + " not found");
    T c ;

    for (int k = 0; k < m_dim_chr; k++)
    {
        double x,y;
        input >> x >> y;
        c.operator()(x,y);
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    conta = 0;
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ ){m_chr.push_back(conta);conta++;}//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(0);
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)
    {
        for(int j = 0; j < m_dim_swap; j++)
        {
            int a = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << a << endl;
            int b = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << b << endl;
            swap(m_pop[k][a], m_pop[k][b]);
        }
        
    } 

    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    
    sort(m_pop.begin(), m_pop.end(), myComp);
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));

};

template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop, int dim_gen, string file) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
   
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");
    input.open(file);
    if(input.fail()) throw runtime_error(file + " not found");
    T c ;

    for (int k = 0; k < m_dim_chr; k++)
    {
        double x,y;
        input >> x >> y;
        c.operator()(x,y);
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    conta = 0;
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ ){m_chr.push_back(conta);conta++;}//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(0);
    for (auto x : m_chr) cout << x << " ";
    cout << endl;
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)
    {
        random_shuffle(m_pop[k].begin()+1, m_pop[k].end()-1);
    } 

    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    
    sort(m_pop.begin(), m_pop.end(), myComp);
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));

};

template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen, string file, string fileLbest, string fileLmeans, int r) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_swap = dim_swap;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
    m_rnd->SetCouples(r);
    of1.open(fileLbest);
    of2.open(fileLmeans);
    input.open(file);
    if(input.fail()) throw runtime_error(file + " not found");
    T c ;

    for (int k = 0; k < m_dim_chr-1; k++)
    {
        double x,y;
        input >> x >> y;
        c.operator()(x,y);
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    conta = 0;
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ ){m_chr.push_back(conta);conta++;}//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(0);//lunghezza m_dim_chr
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)
    {
        
        for(int j = 0; j < m_dim_swap; j++)
        {
            int a = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << a << endl;
            int b = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << b << endl;
            swap(m_pop[k][a], m_pop[k][b]);
        }
        //random_shuffle(m_pop[k].begin()+1, m_pop[k].end()-1);
    } 

    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    
    sort(m_pop.begin(), m_pop.end(), myComp);
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));

};

template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop,  int dim_gen, string file, string fileLbest, string fileLmeans, int r) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
    m_rnd->SetCouples(r);
    of1.open(fileLbest);
    of2.open(fileLmeans);
    input.open(file);
    if(input.fail()) throw runtime_error(file + " not found");
    T c ;

    for (int k = 0; k < m_dim_chr-1; k++)
    {
        double x,y;
        input >> x >> y;
        c.operator()(x,y);
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    conta = 0;
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ ){m_chr.push_back(conta);conta++;}//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(0);//lunghezza m_dim_chr
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)
    {
       
        random_shuffle(m_pop[k].begin()+1, m_pop[k].end()-1);
    } 

    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    
    sort(m_pop.begin(), m_pop.end(), myComp);
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));

};


//COSTRUTTORE TSP
template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop, int dim_swap, int dim_gen) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_swap = dim_swap;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");

    T c ;

    for (int k = 0; k < m_dim_chr-1; k++)
    {
        c.operator();
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    sort(m_cities.begin(), m_cities.end());
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    conta = 0;
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ ){m_chr.push_back(conta);conta++;}//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(0);//lunghezza m_dim_chr
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)
    {
        for(int j = 0; j < m_dim_swap; j++)
        {
            int a = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << a << endl;
            int b = (int)(m_rnd->Rannyu() * (m_dim_chr-2))+1;
            //cout << b << endl;
            swap(m_pop[k][a], m_pop[k][b]);
        }
    } 

    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    
    sort(m_pop.begin(), m_pop.end(), myComp);

    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));

};


//COSTRUTTORE TSP
template<typename T> TSP<T>::TSP(int dim_chr, int dim_pop,  int dim_gen) 
{  
    m_dim_chr = dim_chr;
    m_dim_pop = dim_pop;
    m_dim_gen = dim_gen;
    m_rnd = new Random;
    of1.open("LBestPath.dat");
    of2.open("L-medie.dat");

    T c ;

    for (int k = 0; k < m_dim_chr-1; k++)
    {
        c.operator()();
        m_cities.push_back(c);//CREO vector DI CITTA' LUNGO m_dim_chr
    }
    sort(m_cities.begin(), m_cities.end());
    //m_cities.push_back(m_cities[0]);
    int conta = 1;
    for(auto x : m_cities) {cout << conta << endl; x.print();conta++;}
    conta = 0;
    for(typename vector<T>::iterator it = m_cities.begin(); it != m_cities.end(); it++ ){m_chr.push_back(conta);conta++;}//INIZIALIZZIAMO COME SUDDETTO vector ITERATORI
    m_chr.push_back(0);
    for(int k = 0; k < m_dim_pop; k++)
        m_pop.push_back(m_chr);
    m_pop_ref = m_pop;
    for(int k = 0; k < m_dim_pop; k++)
    {
        random_shuffle(m_pop[k].begin()+1, m_pop[k].end()-1);
    } 

    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    
    sort(m_pop.begin(), m_pop.end(), myComp);
    
    copy(m_pop.begin(), m_pop.end(), back_inserter(m_pop_primi));

    

};




//METODO RIPRODUZIONE: NEL MAIN, SI DOVRA' CICLARE SUL NUMERO DI GENERAZIONI
template <typename T> void TSP<T>::reproduction(int num_scambi)
{ 
    
    m_next_gen = m_pop_ref;
   
    
    for(int j = 0; j < m_dim_pop-1; j+=2)
    {
        // Seleziono due genitori a caso. La quarta potenza aiuta a selezionare i migliori genitori, CIOE' QUELLI
        // CON DISTANZA -FUNZIONE COSTO- MINORE
        int a, b;
        do{
        a = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 5));//SELEZIONO RANDOMICAMENTE UN PERCORSO(GENITORE)
        b = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 5));//SELEZIONE RANDOMICAMENTE UN PERCORSO(GENITORE)
        }while(a == b);
        int c = (int) m_rnd->Rannyu(0,num_scambi+1);
        Ison = m_pop[a];
  
        IIson = m_pop[b];
  
        crossover(c, Ison, IIson);
        
        //verify(m_pop);

        m_next_gen[j+1] = Ison;
      
        m_next_gen[j] = IIson;
            
        mutations(a);
        mutations(b);
  


    }
          
    m_next_gen[m_next_gen.size()-1] = m_pop[0];

    

}

//STAMPO SU FILE LA K-ESIMA GENERAZIONE
template <typename T> void TSP<T>::compute_print_nextGen(int k)
{
    double media = 0.;
    for (int i = 0; i < m_dim_gen / 2; i++)
        media += operator()(m_next_gen[i]);
    of2 << k << " " << media / ((double)m_dim_gen / 2.) << endl;


    auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;
    sort(m_next_gen.begin(), m_next_gen.end(), myComp);
        
    of1 << k << " " << operator()(m_next_gen[0]) << endl;
  
    swap_strong_chr();
    sort(m_next_gen.begin(), m_next_gen.end(), myComp);
    m_pop = m_next_gen;
}
//STAMPO MIGLIORE INDIVIDUO DELLA POPOLAZIONE APPARTENTE ALLA NUOVA GENERAZIONE:
template <typename T> void TSP<T>::print_best_config_nextGen(int k)
{
    of_conf.open("./Configurazioni/configurazione" + to_string(k) + ".dat");
    for (typename vector<int>::iterator it = m_next_gen[0].begin(); it != m_next_gen[0].end(); it++)
    {
        of_conf << m_cities[(*it)].getX() << " " << m_cities[(*it)].getY() << endl;
    }
    of_conf.close();
}

//METODO crossover

template<typename T> void TSP<T>::crossover1(int num_scambi,vector<int>& Ison, vector<int>& IIson )
{ 
    vector<int> v = IIson;
    if(m_rnd->Rannyu() < 0.8){
        int s = 0;
        for (int it = 1; it <Ison.size()-1; it++)
        {
            bool b = false;
            for (int id =1; id < IIson.size()  -num_scambi-1; id++)
            {
                if(Ison[it] ==IIson[id]) {b = true;}
            }
            if (b == false) {
    
                IIson[IIson.size()-1-num_scambi+s] = Ison[it];
                s++;
                //cout << " ciao" << endl;
                
                
            }
        }
        s = 0;
        for (int it = 1; it <IIson.size()-1; it++)
        {
            bool b = false;
            for (int id =1; id < IIson.size()  -num_scambi-1; id++)
            {
                if(v[it] ==Ison[id]) {b = true;}
            }
            if (b == false) {
    
                Ison[Ison.size()-1-num_scambi+s] = v[it];
                s++;
                
            }
        }
    }
}


template<typename T> void TSP<T>::crossover2(int num_scambi,vector<int>& Ison, vector<int>& IIson )
{ 
    if(m_rnd->Rannyu() < 0.5){
        for (int k = 0; k < num_scambi; k++){
        int app = (int)m_rnd->Rannyu(1,Ison.size());
        int a = IIson[app];
        int b = Ison[app];
        for (int i = 1; i < Ison.size()-1; i++)
        {
            if (Ison[i] == a) {swap(Ison[i],Ison[app]);}
            if (IIson[i] == b) {swap(IIson[i], IIson[app]);};
        }
        }
    }
}
template<typename T> void TSP<T>::crossover3(int num_scambi,vector<int>& Ison, vector<int>& IIson )
{ 
    if(m_rnd->Rannyu() < 0.5){
   vector<int> block;

   for(int j = 0; j < num_scambi; j++)
   {
      block.push_back(Ison[Ison.size()-1-num_scambi+j]);
      //block2[j] = parent2.Gen[Pbc(pos+j)];
   } 


   int count1 = 0;

   
   for(int j = 1; j < Ison.size()-1; j++)
   {
      // ciclo sui geni nei blocchi 
      for(int i = 0; i < num_scambi; i++){
         if(IIson[j] == block[i] ){
            Ison[Ison.size()-1-num_scambi+count1] = IIson[j];
            count1++;
         }
    }
   }
    }
}
template<typename T> void TSP<T>::crossover(int num_scambi,vector<int>& Ison, vector<int>& IIson )
{
    crossover1( num_scambi, Ison, IIson );
    //crossover2( num_scambi, Ison, IIson );
    //crossover3( num_scambi, Ison, IIson );
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
template<typename T> void TSP<T>::perm_strong_chr()
{
    double f,g;
    int r = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 1));
    
    
    m_next_gen[r] = m_next_gen[0];
    f = operator()(m_next_gen[r]);
   
    int conta = 0;
    do{
        m_next_gen[r] = m_next_gen[0];
        random_shuffle(m_next_gen[r].begin()+1, m_next_gen[r].end()-1);
        g = operator()(m_next_gen[r]);
    if(conta == 10000) {m_next_gen[r] = m_next_gen[0];g = operator()(m_next_gen[0]);break;}
    conta++;
    }while(f<=g);
  
}

template<typename T> void TSP<T>::swap_strong_chr()
{
    double f,g;
    int r = (int)(m_dim_pop * pow(m_rnd->Rannyu(), 1));
  

    m_next_gen[r] = m_next_gen[0];
    f = operator()(m_next_gen[r]);
    int conta = 0;
    do{
        m_next_gen[r] = m_next_gen[0];
        int i=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1 ;
        int j=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1;
        std::swap(m_next_gen[r][i], m_next_gen[r][j]);
        i=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1 ;
        j=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1;
        std::swap(m_next_gen[r][i], m_next_gen[r][j]);
        i=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1 ;
        j=(int)((m_dim_chr-2)*m_rnd->Rannyu())+1;
        std::swap(m_next_gen[r][i], m_next_gen[r][j]);
        g = operator()(m_next_gen[r]);
    if(conta == 10000) {m_next_gen[r] = m_next_gen[0];g = operator()(m_next_gen[0]);break;}
    conta++;
    }while(f<=g);
  
    
}
//METODO MUTAZIONE SHIFT

template<typename T> void TSP<T>::shift2_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <int> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+2, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}
template<typename T> void TSP<T>::shift3_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <int> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+3, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::shift4_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <int> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+3, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}
template<typename T> void TSP<T>::shift5_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.2){
        vector <int> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+5, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::shift6_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.1){
        vector <int> vec = m_next_gen[a];
        rotate(vec.begin()+1,vec.begin()+5, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::shuffle_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.1){
        vector <int> vec = m_next_gen[a];
        random_shuffle(vec.begin()+1, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::permutation_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.1){
        vector <int> vec = m_next_gen[a];
        next_permutation(vec.begin()+1, vec.end()-1);
        m_next_gen[a]=vec; 
      
        
    }
}

template<typename T> void TSP<T>::reverse_chr_elements(int a)
{
    if(m_rnd->Rannyu() < 0.1){
        vector <int> vec = m_next_gen[a];
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
    
    shift6_chr_elements(a);

    permutation_chr_elements(a);

    reverse_chr_elements(a);
    
    shuffle_chr_elements(a);

    
    
    
}

//METODO RIPRODUZIONE: RIASSUME TUTTO
template <typename T> void TSP<T>::reproductionAll(int num_scambi)
{
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
 
            
            mutations(j);
            

        }
        
        
        
        m_next_gen[0] = m_pop[0];
        
        
        //m_next_gen[k] = m_pop[k];

        double media = 0.;
        for (int i = 0; i < m_dim_gen / 2; i++)
            media += operator()(m_next_gen[i]);
        of2 << k << " " << media / ((double)m_dim_gen / 2.) << endl;

        auto myComp = [&] (vector<int>& v, vector<int>& w){double a = this->operator()(v);double b = this->operator()(w);if(a<b)return true;else return false;} ;

        sort(m_next_gen.begin(), m_next_gen.end(), myComp);
        
        of1 << k << " " << operator()(m_next_gen[0]) << endl;

        if (k % 10 == 0)//OGNI 10 GENERAZIONI MEMORIZZO LA CONFIGURAZIONE FINALE CHE IN QUELLA GENERAZIONE-POPOLAZIONE MINIMIZZA LA FUNZIONE COSTO:
        {
        // cout << k << endl;
            of_conf.open("./Configurazioni/configurazione" + to_string(k) + ".dat");
            for (typename vector<int>::iterator it = m_next_gen[0].begin(); it != m_next_gen[0].end(); it++)
            {
                of_conf << m_cities[(*it)].getX() << " " << m_cities[(*it)].getY() << endl;
            }
            of_conf.close();
        }

        // SI DISTRUGGE LA VECCHIA POPOLAZIONE
        m_pop = m_next_gen;
    }

    cout << "Configurazione finale " << endl;

    for (int i = 0; i < m_dim_pop; i++)
    {
        // popolazione[i].Print();
        cout << i << " " << operator()(m_pop[i]) << endl;
    }

    of1.close();
    of2.close();
    of_conf.close();
}


#endif