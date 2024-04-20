#ifndef __METROPOLIS_H__
#define __METROPOLIS_H__
//LIBRERIE PERSONALI
#include "random.h"
//LIBRERIA DI SISTEMA

#include <functional>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
//USING
using namespace std;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
class Metropolis
{
    public:
        Metropolis(double x, double y, double z, double delta, string file);
        Metropolis(double x, double y,double delta,  string file);
        Metropolis(double x, double delta, string file);
        Metropolis(double x, string file);

        Metropolis(double x);
        Metropolis(double x, double y);
        Metropolis(double x, double y, double z);

        ~Metropolis(){;};
        void move(double &sum, std::function <double (double, double, double)> f );
        void moveGauss(double &sum, std::function <double (double, double, double)> f );

        void move(std::function <double (double)> f);
        void move(std::function <double (double,double,double)> f);

        void move(double &sum, std::function <double (double)> f, std::function <double (double)> g);
        void move(double &sum, std::function <double (double,double,double)> f, std::function <double (double,double,double)> g);

        void equilibrazione(std::function <double (double)> f);
        void equilibrazione(unsigned int app, std::function <double (double)> f);
        void equilibrazione(std::function <double (double,double,double)> f);
        void equilibrazione(unsigned int app, std::function <double (double,double,double)> f);

        double getDelta() const {return m_delta;};

        double getX() const{return m_x;}; 
        double getY() const{return m_y;};
        double getZ() const{return m_z;};

        void setX(double x) {m_x = x;};
        void setY(double y) {m_y = y;};
        void setZ(double z) {m_z = z;};

        void setDelta(double delta){m_delta = delta;};

        unsigned int getCounter() const {return m_conta;};
        void setUnifParameters(double vmin, double vmax);

        void reset();
        
    private:
        double m_x, m_y, m_z;
        double m_x_fix, m_y_fix, m_z_fix;
        double m_xnew, m_ynew, m_znew;
        double m_delta;
        double m_temp;
        double m_min = -1;
        double m_max = +1;
        unsigned int m_conta;
        double m_accettanza;
        Random *rnd;
        string m_file;
        ofstream m_fileout;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

#endif
