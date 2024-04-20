#ifndef __Ago__
#define __Ago__

#include "random.h"

class ExpBuffonAgo {
	public:
	ExpBuffonAgo(double, double, unsigned int); //costruttore
	~ExpBuffonAgo(); //distruttore
	void setParameters(double, double, unsigned int);
	double pigreco();
    void clean();

	double m_length_needle; //lunghezza ago.
	double m_distance_floorboards; //distanza tra le due assi del pavimento.
	unsigned int m_throws; //numero dilanci per ottenere una stima di pigreco.
	Random *rnd;
};
#endif
