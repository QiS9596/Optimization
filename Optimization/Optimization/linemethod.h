#pragma once
#include <vector>
#define VecD std::vector<double>
//to use NR3's conjugete gradient algorithm, we need these fundamental methods
template<class T>
inline const T &MAX(const T &a, const T &b)
{
	bool flag = b > a;
	if (flag)return b;
	return a;
}

template<class T>
inline const T &MIN(const T &a, const T &b) {
	bool flag = a < b;
	if (flag)return a;
	return b;
}

template<class T>
inline T SIGN(const T &a, const T &b)
{
	bool flag1 = b >= 0, flag2 = a >= 0;
	if (flag1) {
		if (flag2)return a;
		return -a;
	}
	if (flag2) return -a;
	return a;
}

template<class T>
inline void SWAP(T &a, T &b)
{
	T temp = a; a = b; b = temp;
}


struct GoldenBracket {
	double xmin, fmin;
	const double tolerence;
	double ax, bx, cx, fa, fb, fc;
	GoldenBracket(const double toll = 3.0e-8) : tolerence(toll) {
		//set default boundary of the bracket
		ax = -100;
		cx = 100;
	}

	template <class T>
	void bracket(const double a, const double b, T &func)
	{
		const double golden_ratio = 1.618034;
		const double golden_limit = 100.0;
		const double golden_tiny = 1.0e-20;
		ax = a; bx = b;
		double fu;
		fa = func(ax);
		fb = func(bx);
		if (fb > fa) {
			SWAP(ax, bx);
			SWAP(fb, fa);
		}
		cx = bx + golden_ratio*(bx - ax);
		fc = func(cx);
		while (fb > fc) {
			double r = (bx - ax)*(fb - fc);
			double q = (bx - cx)*(fb - fa);
			double u = bx - ((bx - cx)*q - (bx - ax)*r) /
				(2.0*SIGN(MAX(abs(q - r), golden_tiny), q - r));
			double ulim = bx + golden_limit*(cx - bx);
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
				u = cx + golden_ratio*(cx - bx);
				fu = func(u);
			}
			else if ((cx - u)*(u - ulim) > 0.0) {
				fu = func(u);
				if (fu < fc) {
					br_shft(bx, cx, u, u + golden_ratio*(u - cx));
					br_shft(fb, fc, fu, func(u));
				}
			}
			else if ((u - ulim)*(ulim - cx) >= 0.0) {
				u = ulim;
				fu = func(u);
			}
			else {
				u = cx + golden_ratio*(cx - bx);
				fu = func(u);
			}
			br_shft(ax, bx, cx, u);
			br_shft(fa, fb, fc, fu);
		}
	}

	template <class T>
	double minimize(T &func)
	{
		const int MAXIMUM_ITERATION_COUNT = 100;//maximum iteration number
		const double golden_ratio_conter = 0.3819660;//golden ratio, used in nr3
		const double tol_TINY = 1.0e-30;//small tolerence
		double a, b, d = 0.0, etemp, fu, fv, fw, fx;
		double p, q, r, tola, tolb, u, v, w, x, xm;
		double e = 0.0;
		a = (ax < cx ? ax : cx);//switch the left and right boundary of the bracket
		b = (ax > cx ? ax : cx);//to ensure that the left boundary is smaller than the right one
		x = w = v = bx;
		fw = fv = fx = func(x);
		for (int iter = 0; iter<MAXIMUM_ITERATION_COUNT; iter++) {
			xm = 0.5*(a + b);
			tolb = 2.0*(tola = tolerence*abs(x) + tol_TINY);
			if (abs(x - xm) <= (tolb - 0.5*(b - a))) {
				fmin = fx;
				return xmin = x;
			}
			if (abs(e) > tola) {
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
					d = golden_ratio_conter*(e = (x >= xm ? a - x : b - x));
				else {
					d = p / q;
					u = x + d;
					if (u - a < tolb || b - u < tolb)
						d = SIGN(tola, xm - x);
				}
			}
			else {
				d = golden_ratio_conter*(e = (x >= xm ? a - x : b - x));
			}
			u = (abs(d) >= tola ? x + d : x + SIGN(tola, d));
			fu = func(u);
			if (fu <= fx) {
				(u >= x ? a : b) = x;
				br_shft(v, w, x, u);
				br_shft(fv, fw, fx, fu);
			}
			else {
				(u < x ? a : b) = u;
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

	inline void br_shft(double &a, double &b, double &c, const double d)
	{
		a = b;
		b = c;
		c = d;
	}

};

template <class T>
struct F1dim {
	const VecD &p;
	const VecD &dxi;
	int n;
	T &func;
	VecD xt;
	F1dim(VecD &pp, VecD &xii, T &funcc) : p(pp),
		dxi(xii), n(pp.size()), func(funcc), xt(n) {}
	double operator() (const double x)
	{
		for (int j = 0; j<n; j++)
			xt[j] = p[j] + x*dxi[j];
		return func(xt);
	}
};

//using brent method to minimize the multidimensional function in one dimension
template <class T>
class linemethod
{
private:
	const double l;
public:
	std::vector<double> p;//the point
	std::vector<double> dxi;
	T & func;
	int n;
	linemethod(T & funct,const double ll = 1.0) :func(funct),l(ll) {
		
	};
	double linmin() {

		double ax, cx, xmin;//the bracket
		n = p.size();
		F1dim<T> f1dim(p, dxi, func);
		ax = 0.0;
		cx = ax + l;
		GoldenBracket br;
		br.bracket(ax, cx, f1dim);
		xmin = br.minimize(f1dim);
		move(xmin);

		return br.fmin;
	};

	void move(double xmin) {
		for (int index = 0; index < p.size(); index++) {
			dxi[index] *= xmin;
			p[index] += dxi[index];
		}
	}
};