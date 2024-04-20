#ifndef __city__
#define __city__

#include <iostream>
#include <fstream>
#include <cmath>

#include "random.h"

using namespace std;
//Una sola città.
class city
{
    public:

        city();
        city(double,double);
        city(double, double,double,double);
        
        double const getX() {return m_x;};
        double const getY() {return m_y;};

        void set(double, double);
        void set0(double,double);

        void print();
        double distance();

        bool operator<(city& c);
        bool operator>(city& c);
        city& operator=(const city& c);
        city operator+(city& c);
        city operator-(city& c);
        city& operator+=(city& c);
        city& operator-=(city& c);
        bool operator==(city& c);
        bool operator!=(city& c);
        double operator()(city& c);
        void operator()(double, double);


    protected:
        double m_x,m_y; 
        double m_x0, m_y0;
        Random *m_rnd;
};
class city_quad : public city{
    public:

        city_quad();
        city_quad(double);
        city_quad(double, double);
        city_quad(double, double, double);

        void set(double, double);
        void setL(double);
        void set0(double, double);
        void setRan();

        void print();
        double distance();

        bool operator<(city_quad& c);
        bool operator>(city_quad& c);
        city_quad& operator=(const city_quad& c);
        city_quad operator+(city_quad& c);
        city_quad operator-(city_quad& c);
        city_quad& operator+=(city_quad& c);
        city_quad& operator-=(city_quad& c);
        bool operator==(city_quad& c);
        bool operator!=(city_quad& c);
        double operator()(city_quad& c);
        void operator()();

    private:
        double m_l;
        double m_a, m_b;
};
class city_circ: public city{	
    public:

        city_circ();
        city_circ(double);
        city_circ (double , double);

        void set(double,double); 
        double const getAngle();
        double const getRay();
        void setAngle(double theta);
        void setRay(double ray);
        void setRan();

        void computeCart();
        void print();

        bool operator<(city_circ& c);
        bool operator>(city_circ& c);
        city_circ& operator=(const city_circ& c);
        city_circ operator+(city_circ& c);
        city_circ operator-(city_circ& c);
        //city_circ operator*(double m);
        city_circ& operator+=(city_circ& c);
        city_circ& operator-=(city_circ&c);
        bool operator==(city_circ&c);
        bool operator!=(city_circ&c);
        double operator()(city_circ&c);
        void operator()();

        city_circ& pbc();

    private:
        double m_theta;
        double m_ray;
         
};

#endif