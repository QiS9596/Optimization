#pragma once
#include <vector>
#define VecD std::vector<double>
template<class T>
inline const T &MAX(const T &a, const T &b)
{
	return b > a ? (b) : (a);
}

template<class T>
inline T SIGN(const T &a, const T &b)
{
	return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

template<class T>
inline void SWAP(T &a, T &b)
{
	T dum = a; a = b; b = dum;
}

struct Bracketmethod {
	double ax, bx, cx, fa, fb, fc;
	template <class T>
	void bracket(const double a, const double b, T &func)
	{
		const double GOLD = 1.618034, GLIMIT = 100.0, TINY = 1.0e-20;
		ax = a; bx = b;
		double fu;
		fa = func(ax);
		fb = func(bx);
		if (fb > fa) {
			SWAP(ax, bx);
			SWAP(fb, fa);
		}
		cx = bx + GOLD*(bx - ax);
		fc = func(cx);
		while (fb > fc) {
			double r = (bx - ax)*(fb - fc);
			double q = (bx - cx)*(fb - fa);
			double u = bx - ((bx - cx)*q - (bx - ax)*r) /
				(2.0*SIGN(MAX(abs(q - r), TINY), q - r));
			double ulim = bx + GLIMIT*(cx - bx);
			if ((bx - u)*(u - cx) > 0.0) {
				fu = func(u);
				if (fu < fc) {
					ax = bx;
					bx = u;
					fa = fb;
					fb = fu;
					return;
				}
				else if (fu > fb) {
					cx = u;
					fc = fu;
					return;
				}
				u = cx + GOLD*(cx - bx);
				fu = func(u);
			}
			else if ((cx - u)*(u - ulim) > 0.0) {
				fu = func(u);
				if (fu < fc) {
					shft3(bx, cx, u, u + GOLD*(u - cx));
					shft3(fb, fc, fu, func(u));
				}
			}
			else if ((u - ulim)*(ulim - cx) >= 0.0) {
				u = ulim;
				fu = func(u);
			}
			else {
				u = cx + GOLD*(cx - bx);
				fu = func(u);
			}
			shft3(ax, bx, cx, u);
			shft3(fa, fb, fc, fu);
		}
	}

	inline void shft2(double &a, double &b, const double c)
	{
		a = b;
		b = c;
	}
	inline void shft3(double &a, double &b, double &c, const double d)
	{
		a = b;
		b = c;
		c = d;
	}
	inline void mov3(double &a, double &b, double &c, const double d, const double e,
		const double f)
	{
		a = d; b = e; c = f;
	}
};

struct Brent : Bracketmethod {
	double xmin, fmin;
	const double tolerence;
	Brent(const double toll = 3.0e-8) : tolerence(toll) {
		//set default boundary of the bracket
		ax = -100;
		cx = 100;
	}
	template <class T>
	double minimize(T &func)
	{
		const int ITMAX = 100;//maximum iteration number
		const double CGOLD = 0.3819660;//golden ratio, used in nr3
		const double ZEPS = 1.0e-30;//small tolerence
		double a, b, d = 0.0, etemp, fu, fv, fw, fx;
		double p, q, r, tol1, tol2, u, v, w, x, xm;
		double e = 0.0;
		a = (ax < cx ? ax : cx);//switch the left and right boundary of the bracket
		b = (ax > cx ? ax : cx);//to ensure that the left boundary is smaller than the right one
		x = w = v = bx;
		fw = fv = fx = func(x);
		for (int iter = 0; iter<ITMAX; iter++) {
			xm = 0.5*(a + b);
			tol2 = 2.0*(tol1 = tolerence*abs(x) + ZEPS);
			if (abs(x - xm) <= (tol2 - 0.5*(b - a))) {
				fmin = fx;
				return xmin = x;
			}
			if (abs(e) > tol1) {
				r = (x - w)*(fx - fv);
				q = (x - v)*(fx - fw);
				p = (x - v)*q - (x - w)*r;
				q = 2.0*(q - r);
				if (q > 0.0) p = -p;
				q = abs(q);
				etemp = e;
				e = d;
				if (abs(p) >= abs(0.5*q*etemp) || p <= q*(a - x)
					|| p >= q*(b - x))
					d = CGOLD*(e = (x >= xm ? a - x : b - x));
				else {
					d = p / q;
					u = x + d;
					if (u - a < tol2 || b - u < tol2)
						d = SIGN(tol1, xm - x);
				}
			}
			else {
				d = CGOLD*(e = (x >= xm ? a - x : b - x));
			}
			u = (abs(d) >= tol1 ? x + d : x + SIGN(tol1, d));
			fu = func(u);
			if (fu <= fx) {
				if (u >= x) a = x; else b = x;
				shft3(v, w, x, u);
				shft3(fv, fw, fx, fu);
			}
			else {
				if (u < x) a = u; else b = u;
				if (fu <= fw || w == x) {
					v = w;
					w = u;
					fv = fw;
					fw = fu;
				}
				else if (fu <= fv || v == x || v == w) {
					v = u;
					fv = fu;
				}
			}
		}
		std::cerr << "too many interations" << std::endl;
	}
};

template <class T>
struct F1dim {
	const VecD &p;
	const VecD &xi;
	int n;
	T &func;
	VecD xt;
	F1dim(VecD &pp, VecD &xii, T &funcc) : p(pp),
		xi(xii), n(pp.size()), func(funcc), xt(n) {}
	double operator() (const double x)
	{
		for (int j = 0; j<n; j++)
			xt[j] = p[j] + x*xi[j];
		return func(xt);
	}
};

//using brent method to minimize the multidimensional function in one dimension
template <class T>
class linemethod
{
public:
	std::vector<double> p;//the point
	std::vector<double> xi;
	T & func;
	int n;
	linemethod(T & funct) :func(funct) {
		
	};
	double linmin() {

		double ax, cx, xmin;//the bracket
		n = p.size();
		F1dim<T> f1dim(p, xi, func);
		ax = 0.0;
		cx = 1.0;
		Brent br;
		br.bracket(ax, cx, f1dim);
		xmin = br.minimize(f1dim);
		for (int index = 0; index < n; index++) {
			xi[index] *= xmin;
			p[index] += xi[index];
		}

		return br.fmin;
	};
};