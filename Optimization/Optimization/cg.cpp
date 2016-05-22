#include "cg.h"


template<class T>
VecD cg<T>::minimize(VecD & pp) {
	const int MAXIMUM_ITERATION_COUNT = 300;	//maximum iteration count
	const double EPS = 1.0e-18;//tolerance
	const double GTOL = 1.0e-8;//GTOL is the convergence criterion for the zero gradient test says the nr3 book
	double gg, dgg;
	int dimension = pp.size();
	this.p = pp;
	VecD g(dimension), h(dimension);
	this.xi.resize(dimension);
	double fp = func(p);
}

