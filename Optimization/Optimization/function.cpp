#include "function.h"



function::function()
{
}

double function::operator ()(vecD vec) {
	return 0.0;
}

void function::df(vecD & x, vecD & deriv) {
	deriv.clear();
	for (int index = 0; index < x.size(); index++) {
		vecD temp1(x);
		vecD temp2(x);
		temp1[index] += 0.1;
		temp2[index] -= 0.1;
		deriv.push_back(((*this)(temp1) - (*this)(temp2)) / 0.2);
	}
}