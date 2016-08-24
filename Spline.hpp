#ifndef SPLINE_HPP_
#define SPLINE_HPP_
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

double maior(double A, double B);
double menor(double A, double B);

class Spline{
	private:
		int tamanho;
		const double *vetorX, *vetorY;
		vector<double> g;
	public:
		Spline(vector<double> &novoVetorX, vector<double> &novoVetorY, const int &novoTamanho);

		void setTamanho(double novoTamanho);
		int getTamanho();

		void calcularG();
		double interpolar(double xv);

		int localizar(const double x);
};

#endif /* SPLINE_HPP_ */
