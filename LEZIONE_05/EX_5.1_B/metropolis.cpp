#include "metropolis.h"


Metropolis::Metropolis(double x, double y, double z, double delta, string file)
{
    //CONDIZIONE INZIALE
    m_x = x;
    m_y = y;
    m_z = z;

    //MEMORIZZAZIONE CONDIZIONE INZIALE
    m_x_fix =x ;
    m_y_fix = y;
    m_z_fix = z;

    //INCREMENTO
    m_delta = delta;

    //GENERATORE NUMERI CASUALI
    rnd = new Random();

    //ACCETTENZA E NUMERO TENTATIVI
    m_conta = 0;
    m_temp = 0;

    //FILE CONFIGURAZIONE:
    remove(file.c_str());
    m_file = file;
    m_fileout.open(m_file, ios::app);
    
};

Metropolis::Metropolis(double x,double y,double delta, string file)
{
    //CONDIZIONE INIZIALE
    m_x = x;
    m_y = y;

    //MEMORIZZAZIONE CONDIZIONE INIZIALE
    m_x_fix =x ;
    m_y_fix = y;

    //INCREMENTO
    m_delta = delta;

    //GENERATORE DI NUMERI CASUALI
    rnd = new Random();

    //ACCETTAMZA E NUMERO TENTATIVI
    m_conta = 0;
    m_temp = 0;

    //FILE CONFIGURAZIONE:
    remove(file.c_str());
    m_file = file; 
    m_fileout.open(m_file, ios::app);   
}

Metropolis::Metropolis(double x, double delta, string file)
{
    //CONDIZIONE INIZIALE
    m_x = x;

    //MEMORIZZAZIONE CONDIZIONE INZIALE
    m_x_fix =x ;

    //INCREMENTO
    m_delta = delta;

    //GENERATORE NUMERI CASUALI
    rnd = new Random();

    //ACCETTANZA E NUMERO TENTATIVI
    m_conta = 0;
    m_temp = 0;

    //FILE CONFIGURAZIONE:
    remove(file.c_str());
    m_file = file;
    m_fileout.open(m_file, ios::app);
    
};

Metropolis::Metropolis(double x, string file)
{
    //CONDIZIONE INIZIALE
    m_x = x;

    //MEMORIZZAZIONE CONDIZIONE INZIALE
    m_x_fix =x ;

    //GENERATORE NUMERI CASUALI
    rnd = new Random();

    //ACCETTANZA E NUMERO TENTATIVI
    m_conta = 0;
    m_temp = 0;

    //FILE CONFIGURAZIONE:
    remove(file.c_str());
    m_file = file;
    m_fileout.open(m_file, ios::app);
    
};

Metropolis::Metropolis(double x)
{
    //CONDIZIONE INIZIALE
    m_x = x;

    //MEMORIZZAZIONE CONDIZIONE INIZIALE
    m_x_fix =x ;

    //GENERATORE NUMERI CASUALI
    rnd = new Random();

    //ACCETTANZA E NUMERO TENTATIVI
    m_conta = 0;
    m_temp = 0;    
}
Metropolis::Metropolis(double x,double y)
{
    //CONDIZIONE INIZIALE
    m_x = x;
    m_y = y;

    //MEMORIZZAZIONE CONDIZIONE INIZIALE
    m_x_fix =x ;
    m_y_fix = y;

    //GENERATORE DI NUMERI CASUALE
    rnd = new Random();

    //ACCETTANZA E NUMERO TENTATIVI
    m_conta = 0;
    m_temp = 0;
}
Metropolis::Metropolis(double x, double y, double z)
{
    //CONDIZIONE INIZIALE
    m_x = x;
    m_y = y;
    m_z = z;

    //MEMORIZZAZIONE CONDIZIONE INIZIALE
    m_x_fix =x ;
    m_y_fix = y;
    m_z_fix = z;

    //GENERATORE DI NUMERI CASUALE
    rnd = new Random();

    //ACCETTANZA E NUMERO TENATIVI:
    m_conta = 0;
    m_temp = 0;   
};

void Metropolis::reset()
{
    m_conta = 0;
    m_temp = 0;
}


void Metropolis::setUnifParameters(double vmin, double vmax)
{
    m_min = vmin;
    m_max = vmax;
}

void Metropolis::equilibrazione(std::function <double (double)> f)
{
    unsigned int appo = 100;
   

    m_delta = 0;

    do{
        m_delta+=0.01;
        m_conta= 0;
        for (int i = 0; i < appo; i++)
        {
            move(f);
        }
        m_accettanza = (double) m_conta/appo;

    }while(m_accettanza > 0.52 || m_accettanza < 0.47);
}

void Metropolis::equilibrazione(unsigned int app,std::function <double (double)> f)
{
    unsigned int appo = app;
   

    m_delta = 0;

    do{
        m_delta+=0.01;
        m_conta= 0;
        for (int i = 0; i < appo; i++)
        {
            move(f);
        }
        m_accettanza = (double) m_conta/appo;

    }while(m_accettanza > 0.52 || m_accettanza < 0.47);
}

void Metropolis::equilibrazione(std::function <double (double, double, double)> f)
{
    unsigned int appo = 100;
   

    m_delta = 0;

    do{
        m_delta+=0.01;
        m_conta= 0;
        for (int i = 0; i < appo; i++)
        {
            move(f);
        }
        m_accettanza = (double) m_conta/appo;

    }while(m_accettanza > 0.52 || m_accettanza < 0.47);
}

void Metropolis::equilibrazione(unsigned int app,std::function <double (double, double, double)> f)
{
    unsigned int appo = app;
   

    m_delta = 0;

    do{
        m_delta+=0.01;
        m_conta= 0;
        for (int i = 0; i < appo; i++)
        {
            move(f);
        }
        m_accettanza = (double) m_conta/appo;

    }while(m_accettanza > 0.52 || m_accettanza < 0.47);
}




void Metropolis::move(double &sum, std::function <double (double,double,double)> f)
{ 
    m_xnew=m_x+m_delta*(rnd->Rannyu(m_min, m_max));
    m_ynew=m_y+m_delta*(rnd->Rannyu(m_min, m_max));
    m_znew=m_z+m_delta*(rnd->Rannyu(m_min, m_max));

    double appo=(double)f(m_xnew,m_ynew,m_znew)/f(m_x,m_y,m_z);
    if(appo >= 1)
    {
        if(m_fileout)
            m_fileout << m_xnew << " " << m_ynew << " " << m_znew << endl;
        m_x=m_xnew;
        m_y=m_ynew;
        m_z=m_znew;
        sum+=sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));
        m_conta++;
    } else {
        if(rnd->Rannyu() <= appo)
        { 
            if(m_fileout)
                m_fileout << m_xnew << " " << m_ynew << " " << m_znew << endl;		
            m_x=m_xnew;
            m_y=m_ynew;
            m_z=m_znew;
            sum+=sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));	
            m_conta++;
        } else {//non mi muovo.
            
            sum+=sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));
        }
    }

} 
void Metropolis::moveGauss(double &sum, std::function <double (double,double,double)> f)
{ 
    m_xnew=(rnd->Gauss(m_x, m_delta));
    m_ynew=(rnd->Gauss(m_y, m_delta));
    m_znew=(rnd->Gauss(m_z, m_delta));

    double appo=(double)f(m_xnew,m_ynew,m_znew)/f(m_x,m_y,m_z);
    if(appo >= 1)
    {
        if(m_fileout)
            m_fileout << m_xnew << " " << m_ynew << " " << m_znew << endl;
        m_x=m_xnew;
        m_y=m_ynew;
        m_z=m_znew;
        sum+=sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));
        m_conta++;
    } else {
        if(rnd->Rannyu() <= appo)
        {
            if(m_fileout) 
                m_fileout << m_xnew << " " << m_ynew << " " << m_znew << endl;		
            m_x=m_xnew;
            m_y=m_ynew;
            m_z=m_znew;
            sum+=sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));	
            m_conta++;
        } else {//non mi muovo.
            sum+=sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));
        }
    }
    
}

void Metropolis::move(std::function <double (double)> f)
{
    m_xnew = rnd->Rannyu(m_x-m_delta, m_x + m_delta);
    double appo = (double) f(m_xnew)/f(m_x);
    if(appo>=1)
    {
        m_x = m_xnew;
        m_conta++;
    }else{
        if(rnd->Rannyu()<= appo)
        {
            m_x = m_xnew;
            m_conta++;
        }
    }
}

void Metropolis::move(std::function <double (double, double,double)> f)
{
    m_xnew = rnd->Rannyu(m_x-m_delta, m_x + m_delta);
    m_ynew = rnd->Rannyu(m_y-m_delta,m_y + m_delta);
    m_znew = rnd->Rannyu(m_z-m_delta,m_z + m_delta);
    double appo = (double) f(m_xnew, m_ynew, m_znew)/f(m_x, m_y, m_z);
    if(appo>=1)
    {
        m_x = m_xnew;
        m_y = m_xnew;
        m_z = m_znew;
        m_conta++;
    }else{
        if(rnd->Rannyu()<= appo)
        {
            m_x = m_xnew;
            m_y = m_xnew;
            m_z = m_znew;
            m_conta++;
        }
    }
}
void Metropolis::move(double &sum, std::function <double (double)> f, std::function <double (double)> g)
{
    m_xnew = rnd->Rannyu(m_x-m_delta, m_x + m_delta);
    double appo = (double) f(m_xnew)/f(m_x);
    m_temp ++;
    if(appo>=1)
    {
        if(m_fileout) 
                m_fileout << m_xnew << " "  << endl;
        m_x = m_xnew;
        m_conta++;
        sum+=g(m_x);
    }else{
        if(rnd->Rannyu()<= appo)
        {
            if(m_fileout) 
                m_fileout << m_xnew << " "  << endl;
            m_x = m_xnew;
            m_conta++;
            sum+=g(m_x);
        }else{
            if(m_fileout) 
                m_fileout << m_x << " "  << endl;
            sum+=g(m_x);
        }
    }
}

void Metropolis::move(double &sum, std::function <double (double, double, double)> f, std::function <double (double, double, double)> g)
{
    m_xnew = rnd->Rannyu(m_x-m_delta, m_x + m_delta);
    m_ynew = rnd->Rannyu(m_y-m_delta,m_y + m_delta);
    m_znew = rnd->Rannyu(m_z-m_delta,m_z + m_delta);
    double appo = (double) f(m_xnew, m_ynew, m_znew)/f(m_x, m_y, m_z);
    m_temp ++;
    if(appo>=1)
    {
        if(m_fileout) 
                m_fileout << m_xnew << " " << m_ynew << " " << m_znew << endl;	
        m_x = m_xnew;
        m_conta++;
        sum+=g(m_x,m_y,m_z);
    }else{
        if(rnd->Rannyu()<= appo)
        {
            if(m_fileout) 
                m_fileout << m_xnew << " " << m_ynew << " " << m_znew << endl;	
            m_x = m_xnew;
            m_conta++;
            sum+=g(m_x,m_y,m_z);
        }else{
            if(m_fileout) 
                m_fileout << m_x << " " << m_y << " " << m_z << endl;	
            sum+=g(m_x,m_y,m_z);
        }
    }
}
