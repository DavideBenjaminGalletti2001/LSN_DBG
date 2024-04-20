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
unsigned int const NUM_THROWS {10000};
unsigned int const NUM {1000};
unsigned int const NUM_BLOCKS {100};
unsigned int const NUM_THROWS_PER_BLOCK {NUM_THROWS/NUM_BLOCKS};
unsigned int const num_T {10};
//FUNZIONI
void temperature(unsigned int );

//********************************************MAIN*****************************************************//

int main(int argc, char** argv)
{
//*******************************************INPUT*******************************************************//
    //INPUT: LETTURA TEMPERATURE
    //temperature(num_T);
    ifstream myInput {"inputT.dat"};
    if(!myInput.is_open()) throw runtime_error("file inputT.dat non found. Error!!!");
    vector<double> myT ((std::istream_iterator<double> (myInput)), (std::istream_iterator<double>()));//CARICAMENTO TEMPRATURE DA FILE
    stringstream s;
    vector<string> myTitle;
    vector<string> myTitleSM;
    for(auto x : myT) 
    {
        s << setprecision(4) << x;
        string T = s.str();
        s.str("");
        myTitle.push_back("OUTPUT/ENERGIE/outputT"+ T + ".dat");
        myTitleSM.push_back("OUTPUT/SIGMA_MU/outputT" + T + "_SM.dat");
    }
//*******************************************INPUT*******************************************************//

//*******************************************OUTPUT*******************************************************//
    //OUTPUT:CREAZIONE FILE OUTPUT
    vector<fstream*> myOf;
    for(int c = 0; c < myT.size(); c=c+1)
    {
        fstream* f= new fstream {myTitle[c], ios::out};
        if(!f->good()) throw runtime_error (myTitle[c] + " doesn't exist. Error!");
        myOf.push_back(f);
    }
    vector<fstream*> mySM;
    for(int a = 0; a < myT.size(); ++a)
    {
        fstream* f = new fstream {myTitleSM[a], ios::out};
        if(f->fail()) throw runtime_error(myTitleSM[a] + " doesn't exist. Error!");
        mySM.push_back(f);
    }

//*******************************************OUTPUT*******************************************************//
    //GENERATORE NUMERI CASUALI
    Random rnd;
    //METROPOLIS
    Metropolis mt {0.,0.};
    //DATA BLOCKING
    DataBlocking bl {NUM_THROWS, NUM_BLOCKS};
    //DATI
    double sigma_old;
    double sigma = 0.7;
    double mu_old;
    double mu = 0.6;
    double sum = 0;
    double delta = 0.005;
    sigma_old = sigma;
    mu_old = mu;

    


//**********************************************LAMBDA FUNCTION*******************************************************//
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
//**********************************************LAMBDA FUNCTION*******************************************************//
    int accepted = 0;
    int attempted = 0;

    for(int k = 0; k < myT.size(); k++)//CICLO SU TEMPERATURE ESTRATTE DA inputT.dat
    {
        
        mt.equilibrazione(lambda);//EQUILIBRO IN MODO TALE DA AVERE ACCETTANZA ~50% E CAMPIONARE LA CORRETTA DISTRIBUZIONE.
        bl.reset();
        mt.reset();
        cout << "**********************" << endl;
        cout << " T = " << myT[k] << endl;

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
            }
            else
            {
                if (rnd.Rannyu() <= A)
                {
                    accepted++;
                    eold = e;
                    
                }
                else
                {
                    sigma = sigma_old;
                }
            }
            *myOf[k] << e <<" "<< bl.getFinalError() << endl;
            *mySM[k] << sigma << " " << mu << endl;

        }
        cout << endl;
        cout << "accepted/attempted = " << (double) accepted / attempted << endl;
        cout << "**********************" << endl; 
    }


    return 0;
}
//****************************************MAIN**************************************************//

void temperature(unsigned int num_T)
{
    ofstream myFile {"inputT.dat"};
    if(!myFile.is_open()) throw runtime_error("file inputT.dat non found. Error!!!");
    double T = 0.5;
    double td = 0.045;
    for(unsigned int k = 0; k < num_T; k++)
    {
        T = T - td;
        myFile << T << endl;
    }
    myFile.close();
}


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