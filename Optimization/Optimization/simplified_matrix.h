#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#define VecD std::vector<double>
using std::string;
using std::stringstream;
class simplified_matrix
{

private:
	double *data;

	void allocate_buffer() {
		this->data = new double[this->h * this->w];
		//debug({ fprintf(stderr, "[+] Matrix allocaed at %p, Buffer allocated at %p\n", this, this->data); })
	}

	void free_buffer() {
		delete[](char *)this->data;
		this->data = nullptr;
	}
public:
	const int h, w;
	simplified_matrix(int h, int w) : h(h), w(w) {
		this->allocate_buffer();
	};
	~simplified_matrix() { this->free_buffer(); }

	VecD * mul(VecD v) {
		VecD * result = new VecD(this->h);
		for (int index = 0; index < result->size(); index++) {
			(*result)[index] = 0;
		}
		for (int index = 0; index < this->h; index++) {
			for (int indexa = 0; indexa < this->w; indexa++)
			{
				(*result)[index] += this->cell(index, indexa)*v[indexa];
			}
		}
		return result;
	}
	double & cell(int x, int y) {
		return this->data[x * this->h + y];
	}
	
	void inverse() {
		VecD b(this->h);
		gauss_jordan_elimination(*this, b);
	}

	static void gauss_jordan_elimination(simplified_matrix &A, VecD &b) {
		std::cout << "gauss jordan" << std::endl;
		int i, j, k;
		int icol, irow;
		int l, ll, n = A.h, m = 1;
		double big, dum, pivinv;
		std::vector<int> indxc(n), indxr(n), ipiv(n);
		for (j = 0; j < n; j++) ipiv[j] = 0;
		for (i = 0; i < n; i++) {
			big = 0.0;
			for (j = 0; j < n; j++)
				if (ipiv[j] != 1) {
					for (k = 0; k < n; k++) {
						if (ipiv[k] == 0) {
							if (abs(A.cell(j, k)) >= big) {
								big = abs(A.cell(j, k));
								irow = j;
								icol = k;
							}//end of if(abs(A.cell(j,k)) >= big)
						}//end of if(ipiv[k] == 0){
					}//end of for (k = 0; k < n; k++)
				}//end of if (ipiv[j]!=1) && end of (j = 0; j < n; j++)
			++(ipiv[icol]);
			if (irow != icol) {
				for (l = 0; l < n; l++) {
					double _tempa = A.cell(irow, l);
					A.cell(irow, l) = A.cell(icol, l);
					A.cell(icol, l) = _tempa;
				}//end of for(l = 0; l < n; l++)
				double _tempb = b[irow];
				b[irow] = b[icol];
				b[icol] = _tempb;
			}//end of if(irow != icol)
			indxr[i] = irow;
			indxc[i] = icol;
			if (A.cell(icol, icol) == 0.0)
				std::cerr << "Gauss Jordan Elimination: Sigular Matrix" << std::endl;
			pivinv = 1.0 / A.cell(icol, icol);
			A.cell(icol, icol) = 1.0;
			for (l = 0; l < n; l++) A.cell(icol, l) *= pivinv;
			b[icol] *= pivinv;
			for (ll = 0; ll < n; ll++) {
				if (ll != icol) {
					dum = A.cell(ll, icol);
					A.cell(ll, icol) = 0.0;
					for (l = 0; l < n; l++) A.cell(ll, l) -= A.cell(icol, l)*dum;
					b[ll] -= b[icol] * dum;
				}
			}



		}//end of for for (i = 0; i < n; i++)
		for (l = n - 1; l >= 0; l--) {
			if (indxr[l] != indxc[l]) {
				for (k = 0; k < n; k++) {
					double _tempa = A.cell(k, indxr[l]);
					A.cell(k, indxr[l]) = A.cell(k, indxc[l]);
					A.cell(k, indxc[l]) = _tempa;
				}
			}
		}
	};

	string str() {
		stringstream buffer;
		buffer << "Matrix(" << h << ", " << w << ") {\n";
		for (auto x = 0; x < this->h; x++) {
			if (x) buffer << ",\n";
			buffer << "  (";
			for (auto y = 0; y < this->w; y++) {
				if (y) buffer << ", ";
				buffer << this->cell(x, y);
			}
			buffer << ")";
		}
		buffer << "\n}";

		return buffer.str();
	}
};

