/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

//LIBRERIE DI SISTEMA
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

//LIBRERIE PERSONALI
#include "Monte_Carlo_ISING_1D.h"

//USING
using namespace std;

//****************************************************************************************//
//BEGIN: INT MAIN
int main(int argc, char* argv[])
{
    Input(); //Inizialization. Setta il generatore di numeri casuali. 

    for(int iblk=1; iblk <= nblk; ++iblk) //Simulation. ciclo sul numero di blocchi (=> data blocking)
    {
        Reset(iblk);   //Reset block averages

        for(int istep=1; istep <= nstep; ++istep) // CICLO INTERNO SU NUMERO STEP DI UN BLOCCO
        {
            Move(metro); // IMPLEMENTAZIONE METODO DI GIBBS E METROPOLIS 
            Measure(); //CALCOLO GRANDEZZE TERMODINAMICHE
            Accumulate(); //UPDATE BLOCK AVARAGES
        }
        Averages(iblk);//Print results for current block
    }
    FillPlot();
    ConfFinal(); //Write final configuration

    return 0;
}
//END:INT MAIN
//****************************************************************************************//

//===========================================================//
//                IMPLEMENTAZIONE DELLE FUNZIONI             //
//===========================================================//

void Input(void)
{
    ifstream ReadInput;

    cout << endl;
    cout << "$-------------------------$" << endl;
    cout << "| Classic 1D Ising model  |" << endl;
    cout << "| Monte Carlo simulation  |" << endl;
    cout << "$-------------------------$" << endl;

    cout << "Nearest neighbour interaction      " << endl << endl;
    cout << "Boltzmann weight exp(- beta * H ), beta = 1/T " << endl << endl;
    cout << "The program uses k_B=1 and mu_B=1 units " << endl;

    //Read seed for random numbers
    int p1, p2;
    ifstream Primes("Primes");
    Primes >> p1 >> p2 ;
    Primes.close();

    ifstream input("seed.in");
    input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
    rnd.SetRandom(seed,p1,p2);
    input.close();
  
    //Read input informations
    ReadInput.open("input.dat");

    ReadInput >> temp;
    beta = 1.0/temp;
    ReadInput >> nspin;
    ReadInput >> J; // cost di accoppiamento tra spin primi vicini
    ReadInput >> h;
    ReadInput >> metro; // if=1 Metropolis (da implementare) else Gibbs (idem)
    ReadInput >> nblk;
    ReadInput >> nstep;
    ReadInput >> restart;

    cout << "$--------------------------------------$" << endl;
    if(metro==1) cout << "| The program perform Metropolis moves |" << endl;
    else         cout << "| The program perform Gibbs moves      |" << endl;
    cout << "$--------------------------------------$" << endl;


    cout << "Temperature                = " << temp << endl;
    cout << "Number of spins            = " << nspin << endl;
    cout << "Exchange interaction       = " << J << endl;
    cout << "External field             = " << h << endl << endl;
    cout << "Number of blocks           = " << nblk << endl;
    cout << "Number of steps per block  = " << nstep << endl << endl;
    cout << "restart = " << restart << endl; 
    ReadInput.close();

    //Prepare arrays for measurements
    iu = 0; //Energy
    ic = 1; //Heat capacity
    im = 2; //Magnetization
    ix = 3; //Magnetic susceptibility
 
    n_props = 4; //Number of observables


    //initial configuration
    if(!restart){
        for (int i=0; i<nspin; ++i)
        {
            if(rnd.Rannyu() >= 0.5) s[i] = 1;
            else s[i] = -1;
        } // tutto random >> temp infinita
    }
    else if(restart)
    {
        fstream ReadConfig;
        if(metro == 1){
            if (h == 0){
                print_input(ReadConfig, "METROPOLIS", "config.h", 1);
            }else{
                print_input(ReadConfig, "METROPOLIS", "config.h", 3);
            }
        }else{
            if (h == 0){
                print_input(ReadConfig, "GIBBS", "config.h", 1);
            }else{
                print_input(ReadConfig, "GIBBS", "config.h", 3);
            }
        }

        for (int i=0; i<nspin; ++i)
        {
            ReadConfig >> s[i];
            cout << s[i] << " " ;
        } // leggo configurazione >> temp equilibrata
        cout << endl;
    }
  
    //Evaluate energy etc. of the initial configuration
    Measure();

    //Print initial values for the potential energy and virial
    cout << "Initial energy             = " << walker[iu]/(double)nspin << endl;
    cout << "--------------------------------------" << endl << endl;
}

void Move(int metro) // SI BADI BENE, CI SI TROVA GIA' DENTRO IL CICLO DEL BLOCCO: WARNING!
{
    int o;
  // double p, energy_old, energy_new, sm; 
    // serviranno per Gibbs, che chiede l'energia. 
    // Nota: prendi l'energia vecchia e 
    // modificala secondo il deltaE calcolato con Boltzmann <<<<<<<<<<< CAPIRE!!!
  // double energy_up, energy_down;

    for(int i=0; i<nspin; ++i) // ciclo sul numero di spin totali
    {
        //Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)
        o = (int)(rnd.Rannyu()*nspin); 

        if(metro==1) //METROPOLIS: metro = 1
        {
            // propongo il flip
            int s_try = -s[o];
            attempted++; //INCREMENTO CONTATORE TENTATIVO

            // calcolo variazione energia DeltaE
            double DeltaE = 2*Boltzmann(s_try, o); // <<< 

            // cuore algoritmo metropolis
            double q = exp(-beta*DeltaE);
            double A = min(1,q);

            if (A==1) // ACCETTO DIRETTAMENTE
            {
                s[o] = s_try; 
                accepted++; //INCREMENTO CONTATORE ACCETTENZA
            }else{ // ACCETTO CON PROBABILITA' A
                if(rnd.Rannyu() < A)
                {
                    s[o] = s_try; 
                    accepted++;//INCREMENTO CONTATORE ACCETTANZA
                }
            }
            // LA DIFFERENZA PRIMARIA CON GIBBS E' RACCHIUSA QUI: SI POTREBBE NON ACCETTARE.
            //IN PRATICA, SE NEL FARE LA MOSSA -FLIP- L'ENERGIA DIMINUISCE, ACCETTO CON PROBABILITA' = 1; ALRIMENTI,
            //SE INVECE LA ENERGIA AUMENTA, ACCETTO LA MOSSA DATA CON UNA CERTA PROBABILITA' 
        //IN PRATICA, SI HA CHE accepted <= attempted
        }else{//GIBBS metro = 0
            attempted++; //INCREMENTO CONTATORE TENTATIVO     
            //**********************************//
            // SI ESTRAE IN MANIERA ALEATORIA UNO SPIN TRA GLI N = 50 SPIN TOTALI
            int snew = ((int)rnd.Rannyu(0,2))*2-1;

            // SI CALCOLA VARIAZIONE DI ENERGIA DeltaE E PROBABILITA' ASSOCIATA
            double DeltaE = -2*Boltzmann(snew, o); 
            double p = 1.0/(1.0+exp(-beta*DeltaE));

            // SI INPONE IL FLIP CON PROBABILITA' p
            if(rnd.Rannyu() < p)
            {
                s[o] = snew;
            }else s[o] = -snew;
        

            accepted++;
        } 
    }
}

void Measure()
{
    // int bin;
    double H = 0.0, u = 0.0, m = 0.0; // x = 0.0, c = 0.0;

    //cycle over spins
    for (int i=0; i<nspin; ++i) 
    {
        H = -J * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]);

        u += H; 
        //c += H*H; // prima era sbagliato!
        m += s[i];
        // x +=  s[i]*s[i]; // non serve, perchè h = 0
    } 
    // energy
     walker[iu] = u; // La media si fa in Averages
    // heat capacity
    walker[ic] = u*u; // 
    //walker[ic] = beta*beta*(c/(double)nspin-u*u/pow((double)nspin,2)); // prima era sbagliato!
    // magnetization
    walker[im] = m;                 
    // susceptivity
    walker[ix] = beta*(m*m); // non beta*(x - m*m), perché h = 0  
}

void Averages(int iblk) //Print results for current block
{
    fstream Ene, Heat, Mag, Chi;//VARIABILI ofstream PER UN TOALE DI 4: UNA PER L'ENERGIA INTERNA, UNA PER IL CALORE
                                 //SPECIFICO, UNA PER LA MAGNETIZZAZIONE,ED INFINE UNA PER LA SUSCETTIBILITA' 
   
    //OUTPUT NUMERO BLOCCO ED ACCETTANZA RATE DEL BLOCCO
    cout << "Block number " << iblk << "  |  ";
    cout << "Acceptance rate " << accepted/attempted << endl;
    if(metro == 1){
        // ENERGIA 
        if (h == 0){
        print_output(Ene, "METROPOLIS/", "/output.ene_h", 1);
        }else{
            print_output(Ene, "METROPOLIS/", "/output.ene_h", 3);

        }
        stima_u = blk_av[iu]/blk_norm/(double)nspin;
        glob_av[iu]  += stima_u; // accu globale
        glob_av2[iu] += stima_u*stima_u; // accu quadratico

        err_u=Error(glob_av[iu],glob_av2[iu],iblk);
        Ene << iblk <<  " " << stima_u << " " << glob_av[iu]/(double)iblk << " " << err_u << endl;
        Ene.close();

        // CAPACITÀ TERMICA
        if (h == 0){
        print_output(Heat, "METROPOLIS/", "/output.heat_h",1);
        }else{
            print_output(Heat, "METROPOLIS/", "/output.heat_h",3);
        }
    
        stima_c = beta*beta * (blk_av[ic]/blk_norm - pow(blk_av[iu]/blk_norm, 2))/(double)nspin; 
        //stima_c = blk_av[ic]/blk_norm; // prima era sbagliato!
        glob_av[ic]  += stima_c; // accu globale
        glob_av2[ic] += stima_c*stima_c; // accu quadratico

        err_c=Error(glob_av[ic],glob_av2[ic],iblk);
        Heat << iblk  <<  " " << stima_c << " " << glob_av[ic]/(double)iblk << " " << err_c << endl;
        Heat.close();

        // MAGNETIZZAZIONE

        if (h == 0){
            print_output(Mag, "METROPOLIS/", "/output.mag_h",1);
        }else{
            print_output(Mag, "METROPOLIS/", "/output.mag_h",3);
        } 
        stima_m = blk_av[im]/blk_norm/(double)nspin; 
        glob_av[im]  += stima_m; // accu globale
        glob_av2[im] += stima_m*stima_m; // accu quadratico

        err_m=Error(glob_av[im],glob_av2[im],iblk);
        Mag << iblk <<  " " << stima_m << " " << glob_av[im]/(double)iblk << " " << err_m << endl;
        Mag.close();

        // SUSCETTIVITÀ
        if (h == 0){
            print_output(Chi, "METROPOLIS/", "/output.chi_h",1);
        }else{
            print_output(Chi, "METROPOLIS/", "/output.chi_h",3);
        }
    
        stima_x = blk_av[ix]/blk_norm/(double)nspin;
        glob_av[ix]  += stima_x; // accu globale
        glob_av2[ix] += stima_x*stima_x; // accu quadratico

        err_x=Error(glob_av[ix],glob_av2[ix],iblk);
        Chi << iblk <<  " " << stima_x << " " << glob_av[ix]/(double)iblk << " " << err_x << endl;
        Chi.close();
    }else{
        // ENERGIA 
        if (h == 0){
            print_output(Ene, "GIBBS/", "/output.ene_h", 1);
        }else{
            print_output(Ene, "GIBBS/", "/output.ene_h", 3);

        }
        stima_u = blk_av[iu]/blk_norm/(double)nspin;
        glob_av[iu]  += stima_u; // accu globale
        glob_av2[iu] += stima_u*stima_u; // accu quadratico

        err_u=Error(glob_av[iu],glob_av2[iu],iblk);
        Ene << iblk <<  " " << stima_u << " " << glob_av[iu]/(double)iblk << " " << err_u << endl;
        Ene.close();

        // CAPACITÀ TERMICA
        if (h == 0){
        print_output(Heat, "GIBBS/", "/output.heat_h",1);
        }else{
            print_output(Heat, "GIBBS/", "/output.heat_h",3);
        }
    
        stima_c = beta*beta * (blk_av[ic]/blk_norm - pow(blk_av[iu]/blk_norm, 2))/(double)nspin; 
        //stima_c = blk_av[ic]/blk_norm; // prima era sbagliato!
        glob_av[ic]  += stima_c; // accu globale
        glob_av2[ic] += stima_c*stima_c; // accu quadratico

        err_c=Error(glob_av[ic],glob_av2[ic],iblk);
        Heat << iblk  <<  " " << stima_c << " " << glob_av[ic]/(double)iblk << " " << err_c << endl;
        Heat.close();

        // MAGNETIZZAZIONE

        if (h == 0){
            print_output(Mag, "GIBBS/", "/output.mag_h",1);
        }else{
            print_output(Mag, "GIBBS/", "/output.mag_h",3);
        } 
        stima_m = blk_av[im]/blk_norm/(double)nspin; 
        glob_av[im]  += stima_m; // accu globale
        glob_av2[im] += stima_m*stima_m; // accu quadratico

        err_m=Error(glob_av[im],glob_av2[im],iblk);
        Mag << iblk <<  " " << stima_m << " " << glob_av[im]/(double)iblk << " " << err_m << endl;
        Mag.close();

        // SUSCETTIVITÀ
        if (h == 0){
            print_output(Chi, "GIBBS/", "/output.chi_h",1);
        }else{
            print_output(Chi, "GIBBS/", "/output.chi_h",3);
        }
    
        stima_x = blk_av[ix]/blk_norm/(double)nspin;
        glob_av[ix]  += stima_x; // accu globale
        glob_av2[ix] += stima_x*stima_x; // accu quadratico

        err_x=Error(glob_av[ix],glob_av2[ix],iblk);
        Chi << iblk <<  " " << stima_x << " " << glob_av[ix]/(double)iblk << " " << err_x << endl;
        Chi.close();        
    }
}

void FillPlot() // Fill files for plotting
{
    fstream Ene, Heat, Chi, Mag;
    if(h==0)
    {
        // ENERGY
        if(metro) Ene.open("PLOT_METRO/ene0",ios::app);
        else Ene.open("PLOT_GIBBS/ene0",ios::app);
        Ene << temp << " " << glob_av[iu]/(double)nblk << " " << err_u << endl;
        Ene.close();

        // HEAT CAPACITY
        if(metro) Heat.open("PLOT_METRO/heat0",ios::app);
        else Heat.open("PLOT_GIBBS/heat0",ios::app);
        Heat << temp << " " << glob_av[ic]/(double)nblk << " " << err_c << endl;
        Heat.close();

        // MAGN SUSCEPTIBILITY
        if(metro) Chi.open("PLOT_METRO/chi0",ios::app);
        else Chi.open("PLOT_GIBBS/chi0",ios::app);
        Chi << temp << " " << glob_av[ix]/(double)nblk << " " << err_x << endl;
        Chi.close();
    }

    if(h!=0)
    {
        // MAGNETIZATION
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << h;
        string hh = stream.str();
        //string hh = to_string(h);
        if(metro) Mag.open("PLOT_METRO/mag"+hh,ios::app);
        else Mag.open("PLOT_GIBBS/mag"+hh,ios::app);
        Mag << temp << " " << glob_av[im]/(double)nblk << " " << err_m << " " << h << endl;
        Mag.close();
    }

}


// qui sotto le funzioni che non ho dovuto modificare in modo sostanziale

double min(double s, double t)
{
    if (s <= t) return s;
    else return t;
}



double Boltzmann(int sm, int ip) // sm è lo spin considerato
{
    double ene = -J * sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm;
    return ene;
}

void Reset(int iblk) //Reset block averages
{
   
    if(iblk == 1)
    {
        for(int i=0; i<n_props; ++i)
        {
            glob_av[i] = 0;
            glob_av2[i] = 0;
        }
    }

    for(int i=0; i<n_props; ++i)
    {
        blk_av[i] = 0;
    }
    blk_norm = 0;
    attempted = 0;
    accepted = 0;
}

void Accumulate(void) //Update block averages
{
    for(int i=0; i<n_props; ++i) //LOOP SU NUMERO DI OSSERVABILI PER UN TOT DI 5:
    {
        blk_av[i] = blk_av[i] + walker[i];
    }
    blk_norm = blk_norm + 1.0;
}

void ConfFinal(void)
{  
    fstream WriteConf;
    cout << endl << "Print final configuration to file of form: config. " << endl << endl;
    if (h == 0){
        print_output(WriteConf, "config.h",1);
    }else{
        print_output(WriteConf, "config.h",3);
    }
    for (int i=0; i<nspin; ++i)
    {
        WriteConf << s[i] << endl;
    }
    WriteConf.close();

    rnd.SaveSeed();
}

int Pbc(int i)  //Algorithm for periodic boundary conditions
{
    if(i >= nspin) i = i - nspin;
    else if(i < 0) i = i + nspin;
    return i;
}

double Error(double sum, double sum2, int iblk)
{
    if(iblk==1) return 0.0;
    else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
}
void print_input(fstream& of, string dir,  string s, int i)
{
    ostringstream oss;
    oss << setprecision(i)<< h; 
    string a_h = oss.str();
    oss.str("");
    oss << setprecision(2) << temp;
    string a_t = oss.str();
    oss.str("");
    of.open("OUTPUT_FILE/EQUILIBRAZIONE/"+ dir+"/h" + a_h +"/T" + a_t +"/" + s + a_h + "T"+ a_t + ".out", ios::in);  
    if(of.fail()) throw runtime_error("error");   
}
void print_output(fstream& of,  string s, int i)
{
    ostringstream oss;
    oss << setprecision(i)<< h; 
    string a_h = oss.str();
    oss.str("");
    oss << setprecision(2) << temp;
    string a_t = oss.str();
    oss.str("");
    of.open("OUTPUT_FILE/" + s  + a_h + "T"+ a_t + ".out", ios::out);  
}

void print_output(fstream& of, string dir, string s, int i)
{
    ostringstream oss;
    oss << setprecision(i)<< h; 
    string a_h = oss.str();
    oss.str("");
    oss << setprecision(2) << temp;
    string a_t = oss.str();
    oss.str("");
    of.open("OUTPUT_FILE/"+ dir +"h" + a_h + s  + a_h + "T"+ a_t, ios::app);    
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/