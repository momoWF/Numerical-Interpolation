#ifndef SPLINEO_HPP_
#define SPLINEO_HPP_
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

using namespace std;

class SplineO{
	private:
		int tamanho;
		const double *vetorX, *vetorY;
		vector<double> g;
	public:
		SplineO(vector<double> &novoVetorX, vector<double> &novoVetorY, const int &novoTamanho);

		void setTamanho(double novoTamanho);
		int getTamanho();

		void calcularG();
		double interpolar(double xv);

		int localizar(const double x);
};

#endif /* SPLINEO_HPP_ */
