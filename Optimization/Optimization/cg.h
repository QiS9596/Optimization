#pragma once
#include "linemethod.h"
#include "newton.h"
#include <vector>
#include <iostream>
#include <sstream>
#define VecD std::vector<double>
/* conjugate gradient based on numrical recipes book
 * when using this method for optimization, user should set function when construct cg instance
 * then use minimize(VecD & p) to minimize.
 * p should be the initial point value
 * return value of minimize function is the point coordinate where the function is optimized
 */
const int MAXIMUM_ITERATION_COUNT = 300;	//maximum iteration count
const double CONJUGATE_GRADIENT_EPSILON = 1.0e-18;//tolerance
const double GRADIENT_TOLERENCE = 1.0e-18;//GRADIENT_TOLERENCE is the convergence criterion for the zero gradient test says the nr3 book

template <class T>
class cg : public linemethod<T>
{
public:
	std::stringstream buffer;
	int iter;
	double cgret;
	using linemethod<T>::func;
	using linemethod<T>::linmin;
	using linemethod<T>::p;
	using linemethod<T>::dxi;
	const double cgtol = 3.0e-8;
	cg(T & funcd) : linemethod<T>(funcd) {}
	VecD minimize(VecD & pp) {

		double delta_T_mul_delta = 0.0,xi_add_delta_mul_xi = 0.0;
		int dimension = pp.size();		p = pp;//get imformation to local variables
		VecD g(dimension), h(dimension);
		dxi.resize(dimension);
		double fp = func(p);
		func.df(p, dxi);//p is the current point.this function set f(vec)dvec[i] to dxi[i]
		for (int index = 0; index < dimension; index++) {
			g[index] = -dxi[index];	dxi[index] = g[index];h[index] = g[index];
		}
		for (int iterations = 0; iterations < MAXIMUM_ITERATION_COUNT; iterations++) {
			std::cout << "i " << iterations << std::endl; //OUT_PUT
			buffer << "i " << iterations << "\r\n";
			iter = iterations;
			VecD previous(dimension);
			for (int index = 0; index < dimension; index++)
				previous[index] = p[index];
			cgret = linmin();
			if (newton::vec_approximately_equals(previous, p)) {
				return p;
			}
			bool return_flag = false;

			return_flag = 2.0 * abs(cgret - fp) <= cgtol*(abs(cgret) + abs(fp) + CONJUGATE_GRADIENT_EPSILON);
			if (return_flag) {
				return p;
			}
			fp = linmin();
			func.df(p, dxi);
			double tempa,den;
			den = MAX(abs(fp), 1.0);
			xi_add_delta_mul_xi = delta_T_mul_delta = tempa =  0.0;
			for (int index = 0; index < dimension; index++) {
				delta_T_mul_delta += g[index] * g[index];//delta f(Xi)T* delta f(Xi)
				xi_add_delta_mul_xi += (dxi[index] + g[index])*dxi[index];
			}
			return_flag = delta_T_mul_delta == 0.0;
			if (return_flag) {
				return p;
			}

			for (int index = 0; index < dimension; index++) {
				double temp;
				temp = abs(dxi[index])*MAX(abs(p[index]), 1.0) ;
				temp /= den;
				tempa = (temp > tempa ? temp : tempa);

			}
			return_flag = tempa < GRADIENT_TOLERENCE;
			if (return_flag) {
				return p;
			}

			//std::cout << "delta x" << dxi[0] << std::endl;
			double ratio_temp = xi_add_delta_mul_xi / delta_T_mul_delta;//beita
			buffer << "Si ";
			for (int j = 0; j<n; j++) {
				g[j] = -dxi[j];
				std::cout << "Si" << g[j] << std::endl;//OUT_PUT
				buffer <<g[j] << " ";
				dxi[j] = h[j] = g[j] + ratio_temp*h[j];//Si
			}
			buffer << "\r\n";
			buffer << "Xi";
			for (int index = 0; index < n; index++) {
				std::cout << "Xi" << p[index] << std::endl;//OUT_PUT
				buffer << p[index] << " ";
			}
			buffer << "\r\n";
			
		}
		std::cerr << "too many iteration" << std::endl;
		return p;
	};//initial point pp, return value minimized point

	std::string out_put_data() {
		return buffer.str();
	}
};

