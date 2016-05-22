#pragma once
#include "function.h"
#include "simplified_matrix.h"
#include <vector>
#define VecD std::vector<double>
#define Mat simplified_matrix

class newton
{
public:
	function & func;
	newton(function & funct) : func(funct) {};
	VecD p;
	const double NEW_TOL = 1.0e-18;
	const int MAXIMUM_ITERATION_COUNT = 5;
	int dimension;
	VecD minimize(VecD & pp) {
		p.resize(pp.size());
		VecD pt(pp.size());

		pt = p;
		p = pp;
		dimension = pp.size();

		for (int index = 0; index < MAXIMUM_ITERATION_COUNT; index++) {

			Mat * H = generate_current_Hessian_matrix();
			std::cout << "iteration count" << index << std::endl;
			std::cout << H->str() << std::endl;
			std::cout << "break point 4" << std::endl;

			H->inverse();
			std::cout << H->str() << std::endl;
			std::cout << "break point 5" << std::endl;
			VecD dp(dimension);
			func.df(p, dp);
			pt = (*vec_minus(p, *(H->mul(dp))));

			if (vec_approximately_equals(pt, p))
				return pt;
			p = pt;
		}
		return p;
	}
	Mat * generate_current_Hessian_matrix() {

		/*Fxy=F(x+d,y+d)-F(x+2d,y)-F(x,y+2d)+F(x,y..)/d^2*/
		VecD dp(dimension);
		func.df(p,dp);
		std::cout <<"p" << p[0] << "," << p[1];
		Mat *H = new Mat(dimension,dimension);
		for (int indexa = 0; indexa < dimension; indexa++) {
			for (int indexb = 0; indexb < dimension; indexb++) {
				VecD tempa(dimension), tempb(dimension), tempc(dimension);
				for (int index = 0; index < dimension; index++)
					tempa[index] = tempb[index] = tempc[index] = p[index];
				tempa[indexa] += 0.001; tempa[indexb] += 0.001;
				tempb[indexa] += 0.001; tempc[indexb] += 0.001;
				std::cout << "tempa" << tempa[0] << ", " << tempa[1] << std::endl;
				std::cout << "function value of tempa" << func(tempa) << std::endl;
				std::cout << "function value of tempb" << func(tempb) << std::endl;
				std::cout << "function value of tempc" << func(tempc) << std::endl;
				std::cout << "my test of h" << (func(tempa) - func(tempb) - func(tempc) + func(p))  << std::endl;
				H->cell(indexa, indexb) = (func(tempa) - func(tempb) - func(tempc) +func(p))/(0.001*0.001);
			}
		}
		return H;
	}
	static VecD* vec_minus(VecD a, VecD b) {
		if (a.size() != b.size())
			std::cerr << "Optimizatioin: newton method: vec_minus: input vector size unmatch" << a.size() << ", " <<b.size() << std::endl;
		VecD * result = new VecD(a.size());
		for (int index = 0; index < a.size(); index++) {
			(*result)[index] = a[index] - b[index];
		}
		return result;
	}
	static bool vec_approximately_equals(VecD a, VecD b) {
		if (a.size() != b.size()) {
			std::cerr << "Optimization: newton method: vec_approximately_equals: input vector size unmatch" << a.size() << ", " <<b.size() <<std::endl;
			return false;
		}
		for (int index = 0; index < a.size(); index++) {
			if (abs(a[index] - b[index]) > 1.0e-18)
				return false;
		}
		return true;
	}
};

