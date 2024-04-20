#include "derivati.h"

Derivati::Derivati(double prezzo_iniziale, double prezzo_concordato, double tasso_interesse, double vol)
{
    m_prezzo_iniziale = prezzo_iniziale;
    m_prezzo_concordato = prezzo_concordato;
    m_tasso_interesse = tasso_interesse;
    m_vol = vol;
    rnd = new Random();
}

Derivati::~Derivati(){;};

double Derivati::scont(double t)
{
    return m_prezzo_iniziale*exp(t*(m_tasso_interesse -((m_vol*m_vol)/2.))+m_vol*sqrt(t)*(rnd->Gauss(0.,1.)));
}

double Derivati::fmax(double a)
{
    if(a>0){
        return a; //Se ho profitto, ritorna il profitto.
    } else {
        return 0; //Non ho profitto.
    }	
}
DerivatiCall::DerivatiCall( double prezzo_iniziale, double prezzo_concordato, double tasso_interesse, double vol) :  Derivati( prezzo_iniziale, prezzo_concordato, tasso_interesse, vol){;}

double DerivatiCall::operator() (double t)
{
    return exp(-m_tasso_interesse*t)*fmax((scont(t)-m_prezzo_concordato));
}
double DerivatiCall::operator() (double t, double a)
{
    double s = m_prezzo_iniziale;
    unsigned int disc_tempo = static_cast<int>(t/a);
    for (unsigned int k = 0; k < disc_tempo; k++)
    {
        s=s*exp((m_tasso_interesse-((m_vol*m_vol)/2))*a+m_vol*(rnd->Gauss(0,1))*sqrt(a));
    }
    return exp(-m_tasso_interesse*t)*fmax(+s-m_prezzo_concordato);
}
DerivatiPutt::DerivatiPutt ( double prezzo_iniziale, double prezzo_concordato, double tasso_interesse, double vol) :  Derivati( prezzo_iniziale, prezzo_concordato, tasso_interesse, vol){;}
double DerivatiPutt::operator() (double t)
{
    return exp(-m_tasso_interesse*t)*fmax(-(scont(t)-m_prezzo_concordato));
}
double DerivatiPutt::operator() (double t, double a)
{
    double s = m_prezzo_iniziale;
    unsigned int disc_tempo = static_cast<int>(t/a);
    for (unsigned int k = 0; k < disc_tempo; k++)
    {
        s=s*exp((m_tasso_interesse-((m_vol*m_vol)/2))*a+m_vol*(rnd->Gauss(0,1))*sqrt(a));
    }
    return exp(-m_tasso_interesse*t)*fmax(-s+m_prezzo_concordato);
}


