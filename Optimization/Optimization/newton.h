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
	const int MAXIMUM_ITERATION_COUNT = 50;
	int dimension;
	VecD minimize(VecD & pp) {
		p.resize(pp.size());
		VecD pt(pp.size());

		pt = p;
		p = pp;
		dimension = pp.size();

		for (int index = 0; index < MAXIMUM_ITERATION_COUNT; index++) {

			Mat * H = generate_current_Hessian_matrix();
			std::cout << "iteration count" << index << std::endl;//OUT_PUT
			std::cout << "Hessian" << H->str() << std::endl;//OUT_PUT

			H->inverse();
			std::cout << "Hessian inverse" << H->str() << std::endl;//OUT_PUT
			std::cout << "x ";//OUT_PUT
			for (int subidx = 0; subidx < dimension; subidx++) {
				std::cout << p[subidx] << " ";
			}
			std::cout << std::endl;
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
		Mat *H = new Mat(dimension,dimension);
		for (int indexa = 0; indexa < dimension; indexa++) {
			for (int indexb = 0; indexb < dimension; indexb++) {
				VecD tempa(dimension), tempb(dimension), tempc(dimension);
				for (int index = 0; index < dimension; index++)
					tempa[index] = tempb[index] = tempc[index] = p[index];
				tempa[indexa] += 0.001; tempa[indexb] += 0.001;
				tempb[indexa] += 0.001; tempc[indexb] += 0.001;
				//std::cout << "tempa" << tempa[0] << ", " << tempa[1] << std::endl;
				//std::cout << "function value of tempa" << func(tempa) << std::endl;
				//std::cout << "function value of tempb" << func(tempb) << std::endl;
				//std::cout << "function value of tempc" << func(tempc) << std::endl;
				//std::cout << "my test of h" << (func(tempa) - func(tempb) - func(tempc) + func(p))  << std::endl;
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
			if (abs(a[index] - b[index]) > 1.0e-5)
				return false;
		}
		return true;
	}
};

class Qnewton :public newton {
public:
	using newton::p;
	using newton::func;
	Qnewton(function & funct) : newton(funct) {};

	using newton::NEW_TOL;
	using newton::MAXIMUM_ITERATION_COUNT ;
	using newton::dimension;

	void dfpmin(VecD &p, double gtol, int &iter, double &fret, function &funcd)
	{
		const int ITMAX = 200;
		const double EPS = 1.0e-18;
		const double TOLX = 4 * EPS, STPMX = 100.0;
		bool check;
		double den, fac, fad, fae, fp, stpmax, sum = 0.0, sumdg, sumxi, temp, test;
		int n = p.size();
		VecD dg(n), g(n), hdg(n), pnew(n), xi(n);
		Mat hessin(n, n);
		fp = funcd(p);
		funcd.df(p, g);
		for (int i = 0; i<n; i++) {
			for (int j = 0; j < n; j++) {
				hessin.cell(i, j) = 0.0;
				hessin.cell(i, j) = 1.0;
				xi[i] = -g[i];
				sum += p[i] * p[i];
			}
		}
		stpmax = STPMX*(sqrt(sum)+ double(n));
		for (int its = 0; its<ITMAX; its++) {
			iter = its;
			fp = fret;
			for (int i = 0; i<n; i++) {
				xi[i] = pnew[i] - p[i];
				p[i] = pnew[i];
			}
			test = 0.0;
			for (int i = 0; i<n; i++) {
				temp = abs(xi[i]) / (abs(p[i])+ 1.0);
				if (temp > test) test = temp;
			}
			if (test < TOLX)
				return;
			for (int i = 0; i<n; i++) dg[i] = g[i];
			funcd.df(p, g);
			test = 0.0;
			den = (abs(fret)+ 1.0);
			for (int i = 0; i<n; i++) {
				temp = abs(g[i])*(abs(p[i])+ 1.0) / den;
				if (temp > test) test = temp;
			}
			if (test < gtol)
				return;
			for (int i = 0; i<n; i++)
				dg[i] = g[i] - dg[i];
			for (int i = 0; i<n; i++) {
				hdg[i] = 0.0;
				for (int j = 0; j<n; j++) hdg[i] += hessin.cell(i,j) * dg[j];
			}
			fac = fae = sumdg = sumxi = 0.0;
			for (int i = 0; i<n; i++) {
				fac += dg[i] * xi[i];
				fae += dg[i] * hdg[i];
				sumdg += dg[i]*dg[i];
				sumxi += xi[i]*xi[i];
			}
			if (fac > sqrt(EPS*sumdg*sumxi)) {
				fac = 1.0 / fac;
				fad = 1.0 / fae;
				for (int i = 0; i<n; i++) dg[i] = fac*xi[i] - fad*hdg[i];
				for (int i = 0; i<n; i++) {
					for (int j = i; j<n; j++) {
						hessin.cell(i,j) += fac*xi[i] * xi[j]
							- fad*hdg[i] * hdg[j] + fae*dg[i] * dg[j];
						hessin.cell(i,j) = hessin.cell(i,j);
					}
				}
			}
			for (int i = 0; i<n; i++) {
				xi[i] = 0.0;
				for (int j = 0; j<n; j++) xi[i] -= hessin.cell(i,j) * g[j];
			}
		}
		throw("too many iterations in dfpmin");
	}

	VecD minimize(VecD & pp) {
		p.resize(pp.size());
		VecD pt(pp.size());

		pt = p;
		p = pp;
		dimension = pp.size();

		for (int index = 0; index < MAXIMUM_ITERATION_COUNT; index++) {

			Mat * H = generate_current_Hessian_matrix();
			if (index == 0) {
				std::cout << "Initial Hessian: ";//OUT_PUT
			}
			else {

				std::cout << "Hessian: ";//OUT_PUT
			}
			std::cout << H->str() << std::endl;//OUT_PUT

			H->inverse();
			if(index == 0)
				std::cout << "Initial Hessian inverse" << H->str() << std::endl;//OUT_PUT


			VecD dp(dimension);
			func.df(p, dp);
			pt = (*vec_minus(p, *(H->mul(dp))));

			if (vec_approximately_equals(pt, p))
				return pt;
			p = pt;

			std::cout << "x ";//OUT_PUT
			for (int subidx = 0; subidx < dimension; subidx++) {
				std::cout << p[subidx] << " ";
			}
			std::cout << std::endl;
		}
		return p;
	}
};

