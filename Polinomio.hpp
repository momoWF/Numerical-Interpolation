#ifndef POLINOMIO_HPP_
#define POLINOMIO_HPP_
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <iostream>

using namespace std;

class Polinomio{
	private:
		double	*coeficientes;
		int		grau;
	public:
		Polinomio(int grau);
		~Polinomio();
		void	setGrau(int novoGrau);
		int		getGrau();
		void 	setCoeficiente(int i,double valor);
		double	getCoeficiente(int i);
		double	getValor(double x);

		void	imprimir();
};

#endif /* POLINOMIO_HPP_ */
