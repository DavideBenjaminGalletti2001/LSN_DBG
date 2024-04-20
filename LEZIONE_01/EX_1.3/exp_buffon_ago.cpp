#include <iostream>
#include <cmath>
#include <fstream>
#include "exp_buffon_ago.h"
#include "random.h"

using namespace std;

void ExpBuffonAgo :: setParameters(double a, double b, unsigned int throws)
{ 
    m_length_needle=a;
    m_distance_floorboards=b;
    m_throws=throws;
}

ExpBuffonAgo :: ExpBuffonAgo(double a, double b, unsigned int throws)
{
    rnd=new Random();
    m_length_needle=a;
    m_distance_floorboards=b;
    m_throws=throws;
}

ExpBuffonAgo :: ~ExpBuffonAgo(){};

void ExpBuffonAgo :: clean()
{
    delete rnd;
} 

double ExpBuffonAgo :: pigreco(){
    double x,theta;
    double conta=0;
		
    for(unsigned int i=0; i<m_throws; i++){
    //Lancio l'ago.
        x=rnd->Rannyu(0,m_distance_floorboards);
        theta=rnd->Unif();
    //Ha intersecato una riga del pavimento?
        if( x > m_distance_floorboards/2.){
            if( x + (m_length_needle/2.)*abs(cos(theta)) >= m_distance_floorboards) conta++;
        } else {
            if( x - (m_length_needle/2.)*abs(cos(theta)) <= 0) conta++;
        }	
    }			


return static_cast<double>((2.*m_length_needle*m_throws))/static_cast<double>((conta*static_cast<double>(m_distance_floorboards)));
}

