#ifndef __DERIVATI_H__
#define __DERIVATI_H__

#include <cmath>
#include "random.h"

using namespace std;

class Derivati{
    public:
        Derivati( double prezzo_iniziale, double prezzo_concordato, double tasso_interesse, double vol);
        ~Derivati();
        virtual double operator()(double t) = 0;
        virtual double operator ()(double t, double a) = 0;
        double scont(double t);
        double fmax(double a);


    protected:
        Random *rnd;
        double m_prezzo_iniziale;
        double m_prezzo_concordato;
        double m_tasso_interesse;
        double m_vol;

};
class DerivatiCall : public Derivati{
    public:
        DerivatiCall( double prezzo_iniziale, double prezzo_concordato, double tasso_interesse, double vol);
        ~DerivatiCall(){;};
        
        double operator()(double t);
        double operator()(double t, double a);
};
class DerivatiPutt : public Derivati{
    public:
        DerivatiPutt( double prezzo_iniziale, double prezzo_concordato, double tasso_interesse, double vol);
        ~DerivatiPutt(){;};

        double operator()(double t);
        double operator()(double t, double a);
};

#endif