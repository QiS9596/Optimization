/*
template <class T>
struct Frprmn : Linemethod<T> {
	Int iter;
	Doub fret;
	using Linemethod<T>::func;
	using Linemethod<T>::linmin;
	using Linemethod<T>::p;
	using Linemethod<T>::xi;
	const Doub ftol;
	Frprmn(T &funcd, const Doub ftoll = 3.0e-8) : Linemethod<T>(funcd),
		ftol(ftoll) {}
	VecDoub minimize(VecDoub_I &pp)	//pp is X1
	{
		const Int ITMAX = 200	//number of iterations N
		const Doub EPS = 1.0e-18;//tolerance
		const Doub GTOL = 1.0e-8;
		Doub gg, dgg;
		Int n = pp.size();
		p = pp;
		VecDoub g(n), h(n);
		xi.resize(n);
		Doub fp = func(p);//fs = f(X1);
		func.df(p, xi); 
		for (Int j = 0; j<n; j++) {
			g[j] = -xi[j];
			xi[j] = h[j] = g[j];
		}
		for (Int its = 0; its<ITMAX; its++) {
			iter = its;
			fret = linmin();
			if (2.0*abs(fret - fp) <= ftol*(abs(fret) + abs(fp) + EPS))
				return p;
			fp = fret;
			func.df(p, xi);
			Doub test = 0.0;
			Doub den = MAX(abs(fp), 1.0);
			for (Int j = 0; j<n; j++) {
				Doub temp = abs(xi[j])*MAX(abs(p[j]), 1.0) / den;
				if (temp > test) test = temp;
			}
			if (test < GTOL) return p;
			dgg = gg = 0.0;
			for (Int j = 0; j<n; j++) {
				gg += g[j] * g[j];//delta f(Xi)T* delta f(Xi)
				//			  dgg += xi[j]*xi[j];
				dgg += (xi[j] + g[j])*xi[j];
			}
			if (gg == 0.0)
				return p;
			Doub gam = dgg / gg;//beita
			for (Int j = 0; j<n; j++) {
				g[j] = -xi[j];
				xi[j] = h[j] = g[j] + gam*h[j];//Si
			}
		}
		throw("Too many iterations in frprmn");
	}
};*/