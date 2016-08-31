#ifndef SPLINE_HPP_
#define SPLINE_HPP_
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "Matriz.hpp"

using namespace std;

double SMAX(const double &a, const double &b);
double SMIN(const double &a, const double &b);

class Spline{
	private:
		vector<double> a;	//	Coeficientes de grau 0 -	y ou f(x)
		vector<double> b;	//	Coeficientes de grau 1
		vector<double> c;	//	Coeficientes de grau 2
		vector<double> d;	//	Coeficientes de grau 3
		vector<double> x;	//	x
		vector<double> h;	//	Vetor de Diferenças
		Matriz *A;
	public:
		Spline(const int &n,const float *x,const float *y);
		Spline(const int &n,const double *x,const double *y);
		~Spline();
		double S(const int &i, const double &x);
		int localizar(const double x);
		double interpolar(const double &x);

		void calcularCoeficientesB();
		void calcularCoeficientesC();
		void calcularCoeficientesD();

		void triangularTridiagonal();
		void substituirTridiagonal();
};



#endif /* SPLINE_HPP_ */
