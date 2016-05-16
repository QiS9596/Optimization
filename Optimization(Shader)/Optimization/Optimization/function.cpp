#include "function.h"



function::function()
{
}

double function::operator ()(vecD vec) {
	std::cout << "hello,world" << std::endl;
	return 0.0;
}

void function::df(vecD & x, vecD & deriv) {
	for (int index = 0; index < x.size(); index++) {
		vecD temp1(x);
		vecD temp2(x);
		temp1[index] += 1;
		temp2[index] -= 1;
		deriv.push_back(((*this)(temp1) - (*this)(temp2)) / 2);
	}
}