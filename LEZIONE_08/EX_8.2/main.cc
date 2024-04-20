//LIBRERIE DI SISTEMA
#include<iostream>
#include<fstream>
#include<functional>
#include<vector>
#include<cmath>
#include<string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <iomanip>

//LIBRERIE PERSONALI
#include "random.h"
#include "metropolis.h"
#include "data_blocking.h"

//USING 
using namespace std;

//COSTANTI
unsigned int const NUM_THROWS {100000};
unsigned int const NUM {70};
unsigned int const NUM_BLOCKS {50};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};
unsigned int const num_T {50};
//FUNZIONI
void temperature(unsigned int );
double* metropolis(function <double (double)> , function <double (double)>);

//-----------------------------------------------MAIN------------------------------------------------------//


int main(int argc, char** argv)
{
//*******************************************INPUT*******************************************************//
    //INPUT: LETTURA TEMPERATURE
    temperature(num_T);
    ifstream myInput {"inputB.dat"};
    if(!myInput.is_open()) throw runtime_error("file inputT.dat non found. Error!!!");
    vector<double> myB ((std::istream_iterator<double> (myInput)), (std::istream_iterator<double>()));//CARICAMENTO TEMPRATURE DA FILE
    stringstream s;
    vector<string> myTitle;
    vector<string> myTitleSM;
    for(auto x : myB) 
    {
        s << setprecision(4) << x;
        string B = s.str();
        s.str("");
        myTitle.push_back("OUTPUT/ENERGIE/outputB"+ B + ".dat");
        myTitleSM.push_back("OUTPUT/SIGMA_MU/outputB" + B + "_SM.dat");
    }

//*******************************************OUTPUT*******************************************************//
    //OUTPUT:CREAZIONE FILE OUTPUT
    fstream myE_B {"myE_B.dat", ios::out};
    fstream myMin {"myMin.dat",ios::out};
    fstream myMeans {"myMeans.dat", ios::out};
    vector<fstream*> myOf;
    for(int c = 0; c < myB.size(); c=c+1)
    {
        fstream* f= new fstream {myTitle[c], ios::out};
        if(!f->good()) throw runtime_error (myTitle[c] + " doesn't exist. Error!");
        myOf.push_back(f);
    }
    vector<fstream*> mySM;
    for(int a = 0; a < myB.size(); ++a)
    {
        fstream* f = new fstream {myTitleSM[a], ios::out};
        if(f->fail()) throw runtime_error(myTitleSM[a] + " doesn't exist. Error!");
        mySM.push_back(f);
    }


//*******************************************DICHIARAZIONI**************************************************//
    //GENERATORE NUMERI CASUALI
    Random rnd;
    //DATI
    double sigma_old;
    double sigma = 1;
    double mu_old;
    double mu = 0;
    double sum = 0;
    double delta = 0.2;

    


    sigma_old = sigma;
    mu_old = mu;

    
//*****************************************LAMBDA FUNCTION************************************************//
    auto lambda = [&] (double x) -> double {return  exp(-pow(x-mu,2)/pow(sigma,2))+exp(-pow(x+mu,2)/pow(sigma,2))+2.*exp(-(pow(x,2)+pow(mu,2))/pow(sigma,2));};
    auto funzione_onda = [&] (double x)-> double {return exp(-pow(x-mu,2)/(2.*pow(sigma,2)))+exp(-pow(x+mu,2)/(2.*pow(sigma,2)));};

    auto Pot = [&] (double x) -> double {return ((pow(x,4)-2.5*pow(x,2))*funzione_onda(x))/funzione_onda(x);};
    auto Ekin = [&] (double x) -> double {
        double p1= exp(-pow(x-mu,2)/(2.0*pow(sigma,2)));
        double p2= exp(-pow(x+mu,2)/(2.0*pow(sigma,2)));
        double p3= 1.0-(pow(x-mu,2)/pow(sigma,2));
        double p4= 1.0-(pow(x+mu,2)/pow(sigma,2));
        return ((1./(2.*pow(sigma,2)))*(p1*p3+p2*p4))/(double)funzione_onda(x);} ;
    auto E = [&] (double x) -> double {return Ekin(x) + Pot(x);};

//**********************************************SIMULATED ANNEALING*******************************************************//
    int accepted = 0;
    int attempted = 0;
    int accepted2 = 0;
    int accepted3 = 0;

    double* eold = metropolis(lambda, E);
    double* e;

    double min;
    double min_e;
    double min_sigma;
    double min_mu;

    for(int k = 0; k < myB.size(); k++)//CICLO SU TEMPERATURE ESTRATTE DA inputT.dat
    {

        cout << "**********************" << endl;
        cout << " B = " << myB[k] << endl;

        cout << "Eold = " <<eold[0] << " +-" << eold[1] << endl;

        accepted = 0;
        attempted = 0;
        accepted2 = 0;
        accepted3 = 0;

        double e_mean = 0;
        double error_mean = 0;
        double sigma_mean = 0;
        double mu_mean = 0;

        

        for( int j = 0; j < NUM; j++)
        {
            
            attempted++;
            //GENERO PASSO:
            sigma_old = sigma;//MEMORIZZO PASSO PRECEDENTE SIGMA
            mu_old = mu;//MEMORIZZO PASSO PRECEDENTE MU
            sigma = rnd.Rannyu(sigma - delta/sqrt(myB[k]), sigma +delta/sqrt(myB[k]));//GENERO MOSSA TENTATIVO
            mu = rnd.Rannyu(mu - delta/sqrt(myB[k]), mu + delta/sqrt(myB[k]));//GENERO MOSSA TENTATIVO
     
            e = metropolis(lambda,E);
            if (j == 0) min = e[0];
            //cout << e << endl; 
            double A = (double)exp((-myB[k])*(e[0]-eold[0]));
            if(A >= 1)
            {
                accepted++;
                accepted2++;
                
                eold[0] = e[0];
                eold[1] = e[1];
                
                
            }else{
                if (rnd.Rannyu() <= A)
                {
                    accepted++; 
                    accepted3++;
                    eold[0] = e[0];
                    eold[1] = e[1];
                    
                    
                }
                else
                {
                    sigma = sigma_old;
                    mu = mu_old;
                }
               
            }
            
            if (e[0] < min){
                min = e[0];
                min_e = e[1];
                min_sigma = sigma;
                min_mu = mu;
            }
            e_mean+=e[0];
            error_mean+=e[1];
            mu_mean+=mu;
            sigma_mean+=sigma;
            *myOf[k] << e[0] << " "<< e[1] << endl;
            *mySM[k] << sigma << " " << mu << endl;
            

        }
        myE_B << myB[k] << " " << e[0] << " "<< e[1] << " " << mu << " " << sigma << endl;
        myMin << myB[k] << " " << min << " "<< min_e << " " << min_mu << " " << min_sigma << endl;
        myMeans  << myB[k] << " " << e_mean/NUM << " "<< error_mean/NUM << " " << mu_mean/NUM << " " << sigma_mean/NUM << endl;

        cout << endl;
        cout << "accepted/attempted = " << (double) accepted / attempted << endl;
        cout << "accepted2/attempted = " << (double) accepted2 / attempted << endl;
        cout << "accepted3/attempted = " << (double) accepted3 / attempted << endl;
        cout << "delta = " << delta/sqrt(myB[k]) << endl;
        cout << "E = " <<e[0] << " +-" << e[1] << endl;
        cout << "**********************" << endl; 
    }

//**********************************************SIMULATED ANNEALING*******************************************************//
    return 0;
}


//-----------------------------------------------MAIN------------------------------------------------------//

//**********************************IMPLEMENTAZIONE FUNZIONI****************************************//
void temperature(unsigned int num_T)
{
    ofstream myFile {"inputB.dat"};
    if(!myFile.is_open()) throw runtime_error("file inputT.dat non found. Error!!!");
    double b = 1;
    double bd = 10;
    for(unsigned int k = 0; k < num_T; k++)
    {
        myFile << b << endl;
        b = b + bd;
    }
    myFile.close();
}

double* metropolis(function <double (double)> f, function <double (double)> g)
{
    double sum;
    Metropolis mt {0.,0.};
    //DATA BLOCKING
    DataBlocking bl {NUM_THROWS, NUM_BLOCKS};
    mt.equilibrazione(f);//EQUILIBRO IN MODO TALE DA AVERE ACCETTANZA ~50% E CAMPIONARE LA CORRETTA DISTRIBUZIONE.
    bl.reset();
    mt.reset();
    for (int i = 0; i < 10; i++) mt.move(f);

    for(int i = 0; i < NUM_BLOCKS; i ++)
    {
        sum = 0;
        for(int l = 0; l < NUM_THROWS_PER_BLOCK; l++)
        {
            mt.move(sum, f, g);
        }
        bl.averagesBlocks(sum);   
    }
    bl.computeProgMeansErrors();
    double* e = new double[2];
    e[0] = bl.getFinalValue();
    e[1] = bl.getFinalError();
    return e;
}
//**********************************IMPLEMENTAZIONE FUNZIONI****************************************//

/*
do{
            delta+=0.01;
            conta = 0;
            for (int r = 0; r < B; r++)
            {
                mt.equilibrazione(lambda);//EQUILIBRO IN MODO TALE DA AVERE ACCETTANZA ~50% E CAMPIONARE LA CORRETTA DISTRIBUZIONE.
                bl.reset();
                mt.reset();
                std::cout << "**********************" << endl;
                std::cout << " T = " << myT[k] << endl;

                for(int i = 0; i < NUM_BLOCKS; i ++)
                {
                    sum = 0;
                    for(int l = 0; l < NUM_THROWS_PER_BLOCK; l++)
                    {
                        mt.move(sum, lambda, E);
                    }
                    bl.averagesBlocks(sum);   
                }
                bl.computeProgMeansErrors();
                double eold = bl.getFinalValue();
                double e;
                accepted = 0;
                attempted = 0;

    
                for( int j = 0; j < NUM; j++)
                {
                    attempted++;
                    //GENERO PASSO:
                    sigma_old = sigma;//MEMORIZZO PASSO PRECEDENTE SIGMA
                    mu_old = mu;//MEMORIZZO PASSO PRECEDENTE MU
                    sigma = rnd.Rannyu(sigma - delta, sigma +delta);
                    mu = rnd.Rannyu(mu - delta, mu + delta);
                    bl.reset();
                    mt.reset();

                    for(int i = 0; i < NUM_BLOCKS; i ++)
                    {
                        sum = 0;
                        for(int l = 0; l < NUM_THROWS_PER_BLOCK; l++)
                        {
                            mt.move(sum, lambda, E);
                        }
                        bl.averagesBlocks(sum);   
                    }
                    bl.computeProgMeansErrors();
                    e = bl.getFinalValue();
                    //cout << e << endl; 
                    double A = (double)exp(-1/myT[k]*e)/exp(-1/myT[k]*eold);
                    if(A >= 1)
                    {
                        accepted++;
                        eold = e;
                        conta++;
                    }
                    else
                    {
                        if (rnd.Rannyu() <= A)
                        {
                            accepted++;
                            eold = e;
                            conta++;
                        }
                        else
                        {
                            sigma = sigma_old;
                        }
                    }

                }
            }
            accettanza = (double) conta/B;

        }while(accettanza > 0.52 || accettanza < 0.47);
*/