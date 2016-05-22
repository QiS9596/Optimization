#pragma once
#include "linemethod.h"
#include <vector>
#include <iostream>
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
	cg(T & funcd) : linemethod<T>(funcd) {}
	VecD minimize(VecD & pp) {
		const int MAXIMUM_ITERATION_COUNT = 300;	//maximum iteration count
		const double EPS = 1.0e-18;//tolerance
		const double GTOL = 1.0e-8;//GTOL is the convergence criterion for the zero gradient test says the nr3 book
		double gg, dgg;
		int dimension = pp.size();
		//p.resize(dimension);
		p = pp;
		VecD g(dimension), h(dimension);
		xi.resize(dimension);
		double fp = func(p);
		std::cout << "fp" << fp << std::endl;
		func.df(p, xi);//p is the current point.this function set f(vec)dvec[i] to xi[i]
		for (int index = 0; index < dimension; index++) {
			g[index] = -xi[index];
			xi[index] = h[index] = g[index];
		}
		for (int iterations = 0; iterations < MAXIMUM_ITERATION_COUNT; iterations++) {
			iter = iterations;
			cgret = linmin();
			//std::cout << "cgret" << cgret << std::endl;

			if (2.0 * abs(cgret - fp) <= cgtol*(abs(cgret) + abs(fp) + EPS)) {
				std::cout << "fp" << fp << std::endl;
				std::cout << cgret << std::endl;
				std::cout << "first flag" << 2.0 * abs(cgret - fp) << std::endl;
				std::cout << "other tolerence" << cgtol*(abs(cgret) + abs(fp) + EPS) << std::endl;
				std::cout << "return 1" << std::endl;
				return p;
			}
			fp = cgret;
			func.df(p, xi);
			double test = 0.0;
			double den = MAX(abs(fp), 1.0);
			for (int index = 0; index < dimension; index++) {
				double temp = abs(xi[index])*MAX(abs(p[index]), 1.0) / den;
				if (temp > test)test = temp;
			}
			if (test < GTOL) { 
				std::cout << "return 2" << std::endl;
				return p;
			}
			dgg = gg = 0.0;
			for (int index = 0; index < dimension; index++) {
				gg += g[index] * g[index];//delta f(Xi)T* delta f(Xi)
				dgg += (xi[index] + g[index])*xi[index];
			}
			if (gg == 0.0) {
				std::cout << "return 3" << std::endl;
				return p;
			}
			double gram = dgg / gg;
			for (int j = 0; j<n; j++) {
				g[j] = -xi[j];
				xi[j] = h[j] = g[j] + gram*h[j];//Si
			}
		}
		std::cerr << "too many iteration" << std::endl;
	};//initial point pp, return value minimized point
};

