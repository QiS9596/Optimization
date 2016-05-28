#include "function.h"



function::function()
{
}

function::function(std::string equation) {
	//treat the input function as a polynomial
	//split it to +/- and every opearhand of sum or minus
	for (int index = 0; index < equation.size(); index++) {
		if (equation[index] == '+' || equation[index] == '-')
		{
			equation.insert(index, " ");
			equation.insert(index + 2, " ");
			index++;
		}
	}
	std::vector<std::string> frag = split(equation,std::string(" "));

	int carry = 1;
	//handle every element
	for (int index = 0; index < frag.size(); index++) {
		if (frag[index] == "+") {
			carry = 1;
		}
		else if (frag[index] == "-") {
			carry = -1;
		}
		/* if the total substring is all number
		 * we find this substring represent a constant
		 * so we push_back it to constant_factor vector
		 * and the exponetial of any variables for a constant element is 0
		 * so we push_back a 0.0 for both x_expo and y_expo
		 */
		else if (isNumirical(frag[index])) {
			double temp = std::stod(frag[index].c_str());
			constant_factor.push_back(temp*carry);
			x_expo.push_back(0.0);
			y_expo.push_back(0.0);
		}
		/* in the last case, the element must be in the form a*x^b*y^c
		 * we split this substring by *
		 * if the substring of current substring is all number, we think we find a
		 * otherwise it might be x/y/x^b/y^b
		 * then we handle x/y case, which simply push a 1 to the x/y_expo vector
		 * then we handle x^b/y^c case, we split it by ^
		 * we first find the variable to decide which vector to push_back
		 * and simply push the double to x/y_expo vector
		 * finally if we don't even discover one of the elements above, we should push_back a default value
		 * for a it's 1* carry, for x^b/y^c it should be x^0 or y^0
		 */
		else {
			std::vector<std::string> split_on_multi = split(frag[index], std::string("*"));
			for (int indexa = 0; indexa < split_on_multi.size(); indexa++) {
				if (isNumirical(split_on_multi[indexa])) {
					constant_factor.push_back(carry * std::stod(split_on_multi[indexa].c_str()));
				}
				else if(split_on_multi[indexa] == "x"){
					x_expo.push_back(1.0);
				}
				else if (split_on_multi[indexa] == "y") {
					y_expo.push_back(1.0);
				}
				else {
					std::vector<std::string> split_on_exponetial = split(split_on_multi[indexa], std::string("^"));
					int var_name = 0;
					for (int indexb = 0; indexb < split_on_exponetial.size(); indexb++) {
						if (split_on_exponetial[indexb] == "x")
							var_name = 1;
						else if (split_on_exponetial[indexb] == "y")
							var_name = 2;
						else if (isNumirical(split_on_exponetial[indexb])) {
							double tempa = std::stod(split_on_exponetial[indexb]);
							if (var_name == 1)
								x_expo.push_back(tempa);
							else if (var_name == 2)
								y_expo.push_back(tempa);
						}
					}
				}
			}
			if (x_expo.size() < y_expo.size()) {
				x_expo.push_back(0.0);
			}
			else if (y_expo.size() < x_expo.size())
				y_expo.push_back(0.0);
			if (constant_factor.size() < x_expo.size())
				constant_factor.push_back(carry);
		}
	}
}

double function::operator ()(vecD vec) {
	return 0.0;
}

void function::df(vecD & x, vecD & deriv) {
	deriv.clear();
	for (int index = 0; index < x.size(); index++) {
		vecD temp1(x);
		vecD temp2(x);
		temp1[index] += 0.01;
		temp2[index] -= 0.01;
		deriv.push_back( (((*this)(temp1) - (*this)(temp2)) / 0.02) );
	}
}