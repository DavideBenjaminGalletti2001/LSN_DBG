#include "city.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%city%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

city::city()
{
    m_x0 = 0;
    m_y0 = 0;
    m_rnd = new Random();
};
city:: city(double a, double b)
{
    m_x0 = a;
    m_y0= b;
    m_rnd = new Random();
};

city::city(double x,double y,  double x0, double y0) 
{
    
    m_rnd = new Random();
    m_x = x;
    m_y = y;
    m_x0 = x0;
    m_y0 = y0;
}

void city::set(double a, double b)
{
    m_x = a;
    m_y = b;
}


void city::set0(double x0, double y0)
{
    m_x = m_x0;
    m_y = m_y0;
}

void city::print()
{
    cout << "******************" << endl;
    cout << endl;
    cout << "X = " << getX() << endl;
    cout << "Y = " << getY() << endl;
    cout << endl;
    cout << "******************" << endl;
}
double city::distance()
{
    return sqrt(pow(m_x - m_x0,2) + pow(m_y - m_y0,2));
}

bool city::operator<(city& c)
{
    double a = distance();
    double b = c.distance();
    if (a<b)
        return true;
    else
        return false;
};

bool city::operator>(city& c)
{
    double a = distance();
    double b = c.distance();
    if (a>b)
        return true;
    else
        return false;
};

city& city:: operator=(const city& c)
{
    m_x = c.m_x;
    m_y = c.m_y;
    m_x0 = c.m_x0;
    m_y0 = c.m_y0;
    return *this;
}
city city::operator+(city& c)
{
    city ris = c;
    ris.m_x = m_x + c.m_x;
    ris.m_y = m_y + c.m_y; 

    return ris;
} 
city city::operator-(city& c)
{
    city ris = c;
    ris.m_x = m_x - c.m_x;
    ris.m_y = m_y - c.m_y; 

    return ris;
}  
city& city::operator+=(city& c)
{
    return *this = *this + c;
}

city& city::operator-=(city& c)
{
    return *this = *this - c;
} 
        
bool city::operator==(city& c)
{
    if(m_x == c.m_x and m_y ==c.m_y)
        return true;
    else
        return false;
}

bool city::operator!=(city& c)
{
    if(m_x == c.m_x and m_y ==c.m_y)
        return false;
    else
        return true;
}
   
        
double city::operator()(city& c)
{
    return sqrt(pow(m_x - c.m_x,2) + pow(m_y - c.m_y,2));
}        

void city::operator()(double x, double y)
{
    m_x = x;
    m_y = y;
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%city_circ%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
city_circ ::city_circ () : city()
{
    m_ray = 1;
    m_theta =m_rnd->Rannyu(0,2*M_PI);
    m_x=m_ray*cos(m_theta);
    m_y=m_ray*sin(m_theta);
        
};

city_circ :: city_circ (double theta) : city()
{
    m_theta=theta;
    m_ray = 1.;
    m_x=m_ray*cos(theta);
    m_y=m_ray*sin(theta);     
}
city_circ :: city_circ (double theta, double ray) : city()
{
    m_theta=theta;
    m_ray = ray;
    m_x=m_ray*cos(theta);
    m_y=m_ray*sin(theta);    
}

void city_circ :: set(double theta, double ray){
    m_theta=theta;
    m_ray = ray;
    m_x=m_ray*cos(theta);
    m_y=m_ray*sin(theta);
}

void city_circ :: setAngle(double theta){
    m_theta = theta;
}

void city_circ :: setRay(double ray)
{
    m_ray = ray;
}
void city_circ :: setRan()
{
    m_theta = m_rnd->Rannyu(0,2*M_PI);
    m_x = m_ray*cos(m_theta);
    m_y = m_ray*sin(m_theta);
}
void city_circ :: computeCart()
{
    m_x=m_ray*cos(m_theta);
    m_y=m_ray*sin(m_theta);
}


double const city_circ :: getAngle(){
    return m_theta;
}

double const city_circ :: getRay(){
    return m_ray;
}
city_circ& city_circ :: pbc(){
    while(m_theta < 0 || m_theta > 2*M_PI){
        if(m_theta > 2*M_PI)
            m_theta = m_theta - 2*M_PI;
        else
            if (m_theta < 0)
                m_theta = m_theta +2*M_PI;
    }
    return *this;
}

bool city_circ :: operator<(city_circ& c){
    pbc();
    c.pbc();
    if (m_theta < c.m_theta )
        return true;
    else
        return false;
};
bool city_circ:: operator==(city_circ& c)
{
    pbc();
    c.pbc();
    if(m_theta == c.m_theta and m_ray == c.m_ray)
        return true;
    else
        return false;
};

bool city_circ::operator!=(city_circ& c)
{
    if(m_x == c.m_x and m_y ==c.m_y)
        return false;
    else
        return true;
}

bool city_circ :: operator>(city_circ& c){
    pbc();
    c.pbc();
    if (m_theta > c.m_theta )
        return true;
    else
        return false;    
};
double city_circ::operator()(city_circ&c)
{
    double ris;
    ris = sqrt(pow(m_x - c.m_x,2) + pow(m_y - c.m_y,2));
    return ris;
}
city_circ& city_circ:: operator=(const city_circ& c)
{
    m_theta = c.m_theta;
    m_ray = c.m_ray;
    m_x = c.m_x;
    m_y = c.m_y;

    return *this;
};
city_circ city_circ:: operator+(city_circ& c)
{
    pbc();
    c.pbc();
    city_circ ris;
    if(m_ray == c.m_ray){
        ris.m_theta = m_theta + c.m_theta;
        ris.m_ray = m_ray;
        ris.computeCart();
    }else{
        throw runtime_error("RAGGI DI DIMENSIONE DIVERSA");
    }

    return ris;

}

city_circ city_circ:: operator-(city_circ& c)
{
    pbc();
    c.pbc();
    city_circ ris;
    if(m_ray == c.m_ray){
        ris.m_theta = m_theta - c.m_theta;
        ris.m_ray = m_ray;
        ris.computeCart();
    }else{
        throw runtime_error("RAGGI DI DIMENSIONE DIVERSA");
    }
    return ris;
}

city_circ& city_circ::operator+=(city_circ& c)
{
    return *this = *this + c;
}
city_circ& city_circ :: operator-=(city_circ& c)
{
    return *this = *this - c;
}
void city_circ::print ()
{
    cout << "******************" << endl;
    cout << endl;
    cout << "ANGOLO = " << getAngle() << endl;
    cout << "RAGGIO = " << getRay() << endl;
    cout << "X = " << getX() << endl;
    cout << "Y = " << getY() << endl;
    cout << endl;
    cout << "******************" << endl;
}


void city_circ::operator()()
{
    m_theta = m_rnd->Rannyu(0,2*M_PI);
    m_x = m_ray*cos(m_theta);
    m_y = m_ray*sin(m_theta); 
}





//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%city_quad%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

   
      


city_quad::city_quad() : city()
{
    m_l = 1.;
    m_a = 1.;
    m_b = 1.;
    m_x = m_rnd->Rannyu(-m_l/2, m_l/2);
    m_y = m_rnd->Rannyu(-m_l/2, m_l/2);
};
city_quad::city_quad(double l) : city()
{
    m_l = l;
    m_a = l;
    m_b = l;
    m_x = m_rnd->Rannyu(-m_l/2, m_l/2);
    m_y = m_rnd->Rannyu(-m_l/2, m_l/2);
}
city_quad::city_quad(double a, double b) : city()
{
    m_a = a;
    m_b = b;
    m_x = m_rnd->Rannyu(-m_a/2, m_a/2);
    m_y = m_rnd->Rannyu(-m_b/2, m_b/2);
};

city_quad::city_quad(double l, double x0, double y0) : city()
{
    m_l = l;
    m_a = l;
    m_b = l;
    m_x = m_rnd->Rannyu(-m_l/2, m_l/2);
    m_y = m_rnd->Rannyu(-m_l/2, m_l/2);
    m_x0 = x0;
    m_y0 = y0;
}

void city_quad::set(double a, double b)
{
    m_a = a;
    m_b = b;
}

void city_quad::setL(double l)
{
    m_l = l;
    m_a = l;
    m_b =l;
}
void city_quad::set0(double x0, double y0)
{
    m_x = m_x0;
    m_y = m_y0;
}
void city_quad::setRan()
{
    m_x = m_rnd->Rannyu(-m_a/2, m_a/2);
    m_y = m_rnd->Rannyu(-m_b/2, m_b/2);
}

void city_quad::print()
{
    cout << "******************" << endl;
    cout << endl;
    cout << "LATO = " << m_l << endl;
    cout << "X = " << getX() << endl;
    cout << "Y = " << getY() << endl;
    cout << endl;
    cout << "******************" << endl;
}
double city_quad::distance()
{
    return sqrt(pow(m_x - m_x0,2) + pow(m_y - m_y0,2));
}

bool city_quad::operator<(city_quad& c)
{
    double a = distance();
    double b = c.distance();
    if (a<b)
        return true;
    else
        return false;
};

bool city_quad::operator>(city_quad& c)
{
    double a = distance();
    double b = c.distance();
    if (a>b)
        return true;
    else
        return false;
};

city_quad& city_quad:: operator=(const city_quad& c)
{
    m_x = c.m_x;
    m_y = c.m_y;
    m_x0 = c.m_x0;
    m_y0 = c.m_y0;
    return *this;
}
city_quad city_quad::operator+(city_quad& c)
{
    city_quad ris = c;
    ris.m_x = m_x + c.m_x;
    ris.m_y = m_y + c.m_y; 

    return ris;
} 
city_quad city_quad::operator-(city_quad& c)
{
    city_quad ris = c;
    ris.m_x = m_x - c.m_x;
    ris.m_y = m_y - c.m_y; 

    return ris;
}  
city_quad& city_quad::operator+=(city_quad& c)
{
    return *this = *this + c;
}

city_quad& city_quad::operator-=(city_quad& c)
{
    return *this = *this - c;
} 
        
bool city_quad::operator==(city_quad& c)
{
    if(m_x == c.m_x and m_y ==c.m_y)
        return true;
    else
        return false;
}

bool city_quad::operator!=(city_quad& c)
{
    if(m_x == c.m_x and m_y ==c.m_y)
        return false;
    else
        return true;
}
   
        
double city_quad::operator()(city_quad& c)
{
    return sqrt(pow(m_x - c.m_x,2) + pow(m_y - c.m_y,2));
} 

void city_quad::operator()()
{
    m_x = m_rnd->Rannyu(-m_a/2, m_a/2);
    m_y = m_rnd->Rannyu(-m_b/2, m_b/2);
}

