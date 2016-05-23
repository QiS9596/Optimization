#pragma once
#include <vector>
#define vecD std::vector<double>
#include <iostream>
class function
{
public:
	function();
	virtual double operator()(vecD);
	void df(vecD & x, vecD & deriv);
};

class testFunc2 : public function {
public:
	double operator()(vecD x) {
		return x[0] * x[0] -2 * x[0] * x[1] + 4*x[1]*x[1];
	}
	void standardDF(vecD &x, vecD & deriv) {
		deriv.push_back(2.0*x[0]);
		deriv.push_back(2.0*x[1]);
	}
};

class testFunc1 : public function {
public:
	double operator()(vecD x) { return x[0]*x[0] + x[0] -2* pow(x[0],0.5); };
};

class testFunc3 : public function {
	double operator()(vecD x) { return 7 + pow((x[0]), 2) - 3* x[0] * x[1] +3.25* pow(x[1], 2)-4*x[1]; };
};