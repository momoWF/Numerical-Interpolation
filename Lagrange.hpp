#ifndef LAGRANGE_HPP_
#define LAGRANGE_HPP_
#include <cmath>
#include <iostream>

using namespace std;

class Lagrange{
	private:
		double *vetorX;
		double *vetorY;
		int tamanho;
	public:
		Lagrange(int novoTamanho = 0, double *novoVetorX = NULL, double *novoVetorY = NULL);
		double pi(const double &x);
		double D(const double &i);
		void setVetorX(double *novoVetorX);
		void setVetorY(double *novoVetorY);
		double getX(const int &i);
		double getY(const int &i);
		int getTamanho();
		void setTamanho(int novoTamanho);

		double interpolar(const double &x);

};

#endif /* LAGRANGE_HPP_ */


