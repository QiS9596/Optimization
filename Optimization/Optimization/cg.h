#pragma once
#include "linemethod.h"
#include <vector>
#define VecD std::vector<double>
template <class T>
class cg : public linemethod<T>
{
public:
	int iter;
	double cgret;
	using linemethod<T>::func;
	using linemethod<T>::linmin;
	using linemethod<T>::p;
	using linemethod<T>::xi;
	const double cgtol = 3.0e-8;
	//	Frprmn(T &funcd, const Doub ftoll = 3.0e-8) : Linemethod<T>(funcd),
		//ftol(ftoll) {}
	cg(T & funcd) : linemethod<T>(funcd) {}
	VecD minimize(VecD & pp);//initial point pp, return value minimized point
};

