#ifndef __funtore__
#define __funtore__
#include <vector>
#include "city.h"

using namespace std;
template <typename T> class Funtore
{
    public:
        Funtore() {;};
        double operator()(vector<typename vector<T>::iterator>& v);
    protected:
};

template <typename T> bool myComp(vector<typename vector<T>::iterator> v, vector<typename vector<T>::iterator> w);



template<typename T> double Funtore<T>::operator()(vector<typename vector<T>::iterator>& v)
{
    double sum = 0;
    
    for(int k = 0; k < v.size() -1 ; k++)
    {
        sum += (*v[k])(*v[k+1]);
    }
    sum+=(*v[v.size()-1])(*v[0]);

    return sum;

}
//ORDINAMENTO CRESCENTE: TRUE SE IL I VECTOR E' MINORE DEL II
//AVRO' NELLE PRIME POSIZIONE I VECTOR CON FUNZIONE COSTO PIù BASSE
//MENTRE NELLE ALTRE QUELLE CON FUNZIONI COSTO PIU' ALTA.
template <typename T> bool myComp(vector<typename vector<T>::iterator> v, vector<typename vector<T>::iterator> w)
{
    Funtore<T> f ;
    double a = f(v);
    double b = f(w);

    if(a<b)
        return true;
    else
        return false;

}
#endif


/*
double FunzioneCosto::operator()(vector<city>::iterator it)
{
    double sum = 0;
    vector<city>::iterator ii = it;
    vector<city>::iterator io = it;
    for(int k = 0; k < m_dim -1; k++)
    {
        ii = it + 1;
        sum += (*it)(*ii);
        it++;
    }
    sum+=(*io)(*it);

    return sum;

}
*/




