#ifndef LAGRANGE_HPP_
#define LAGRANGE_HPP_
#include <cmath>
#include <iostream>
#include "Matriz.hpp"

using namespace std;

class Lagrange{
	private:
		Matriz *diferencas;
	public:
		Lagrange(Matriz *x);
		Lagrange(float *x, float *y,int n);
		~Lagrange();
		double pi(const double &x);
		double D(const int &i,const double &x);
		double S(const double &x);
		double interpolar(const double &x);
};

#endif /* LAGRANGE_HPP_ */


