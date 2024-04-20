#include "main.h"
using namespace std;


int main(int argc, char* argv[])
{
    int dim_chr, dim_pop, dim_swap, dim_gen, dim_scambi, migration, dim_migration;
    Random rnd;
    //rnd.SetSeed();
    //rnd.SetCouples(27);

    input(dim_chr, dim_pop, dim_swap, dim_gen,dim_scambi, migration, dim_migration); 

   
    
    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    cout << "size = " << size << " rank = " << rank << endl; 
    MPI_Status stat;
    
    TSP<city> myTSL{dim_chr, dim_pop, dim_gen,"American_capitals.dat", "LBestPath"+to_string(rank)+ ".dat", "L-medie"+to_string(rank)+ ".dat", rank};

    // inizializzo su coppie di semi diversi ciascun nodo
    rnd.SetCouples(rank);
    for (int k = 0; k < dim_gen; k++)
    {
        rnd.SetCouples(rank); 
        if(migration==0 || (migration!=0 && k%dim_migration!=0) || k==0){ // continenti indipendenti -> no migrazioni
            myTSL.reproduction(dim_scambi);
            myTSL.compute_print_nextGen(k);
            
        }else if(migration==1 && k%dim_migration==0){ // continenti connessi -> migrazioni
            // ogni tau_migr generazioni un chr di una
            // popolazione in un *core casuale* dev'essere 
            // mandato in un'altro *core casuale*
            // --- migrare è analogo a mutare ---
            
            int h = 0;
            int sender = 0;
            int receiver = 1;
            vector<int> migrator;
            int itag=1;
            int exp = 10; //expon;

            // solo il core 0 fa le estrazioni
            if(rank == 0){
                h = (int)(dim_pop*(pow(rnd.Rannyu(),exp))); // scelgo un individuo in modo casuale
                sender = (int)rnd.Rannyu(0,size);             // scelgo il core di partenza
                receiver = (int)rnd.Rannyu(0,size);          // scelgo il core di arrivo... 
                while(receiver== sender){                        // ... diverso dal sender
                    receiver = (int)rnd.Rannyu(0,size);      
                }
                cout << endl << "Migration (h, sender, receiver): " << h << ", " << sender << ", " << receiver << endl;
            }

            MPI_Bcast(&h, 1, MPI_INTEGER, 0, MPI_COMM_WORLD); // il core 0 manda a tutti gli altri
            MPI_Bcast(&sender, 1, MPI_INTEGER, 0, MPI_COMM_WORLD); 
            MPI_Bcast(&receiver, 1, MPI_INTEGER, 0, MPI_COMM_WORLD); 
            
            // se sono il sender, salvo su migrator e lo spedisco al receiver
            migrator = myTSL.getGivenValuePop(h);
            if(rank == sender){
                
                
                MPI_Send(&migrator[0],dim_chr,MPI_INTEGER,receiver,itag,MPI_COMM_WORLD);

            }
            // se sono il ricevitore lo salvo
            if(rank == receiver){
               
                MPI_Recv(&migrator[0],dim_chr,MPI_INTEGER, sender,itag,MPI_COMM_WORLD,&stat);
                
                myTSL.setPop(migrator, h);     
            }
            
            // dopo è uguale
            myTSL.reproduction(dim_scambi);
        
            myTSL.compute_print_nextGen(k); 
            
        }
        
        if(k%100 == 0) myTSL.print_best_config_nextGen(rank+k);
    }

    MPI_Finalize();
    
    
    
    
}