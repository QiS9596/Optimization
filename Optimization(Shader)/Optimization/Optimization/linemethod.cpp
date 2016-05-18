#include "linemethod.h"

template<class T>
double linemethod<T>::linmin()
{
	double ax, cx, xmin;//the bracket
	n = p.size();
	F1dim<func> f1dim(p, xi, func);
	ax = 0.0;
	cx = 1.0;
	Brent br;
	br.bracket(ax, cx, f1dim);
	xmin = br.minimize(f1dim);
	for (int index = 0; index < n; index++) {
		xi[index] *= xmin;
		p[index] += xj[index];
	}
	return br.fmin;
}

