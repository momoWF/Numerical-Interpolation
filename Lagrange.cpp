#include "Lagrange.hpp"

Lagrange::Lagrange(int novoTamanho, double *novoVetorX, double *novoVetorY){
	setTamanho(novoTamanho);
	setVetorX(novoVetorX);
	setVetorY(novoVetorY);
}

void Lagrange::setVetorX(double *novoVetorX){
	vetorX = novoVetorX;
}

void Lagrange::setVetorY(double *novoVetorY){
	vetorY = novoVetorY;
}

double Lagrange::getX(const int &i){
	if (i >=0 && i < getTamanho())
		return vetorX[i];
	else
		return 0.0;
}

double Lagrange::getY(const int &i){
	if (i >=0 && i < getTamanho())
		return vetorY[i];
	else
		return 0.0;
}

int Lagrange::getTamanho(){
	return tamanho;
}
void Lagrange::setTamanho(int novoTamanho){
	tamanho = novoTamanho;
}

double Lagrange::pi(const double &x){
	double resultado = 1;
	for (int c = 0; c < getTamanho(); c++)
		resultado *= (x - getX(c));
	return resultado;
}

double Lagrange::D(const double &i){
	double resultado = 1;
	for (int c = 0; c < getTamanho(); c++)
		if (c != i)
			resultado *= (getX(i) - getX(c));
	return resultado;
}

double Lagrange::interpolar(const double &x){
	//Polinomio *polinomio = new Polinomio(getTamanho());
	double resultado = 0;
	double Li = 0;
	for (int c = 0; c < getTamanho(); c++){
		Li = (pi(x)/((x-getX(c))*D(c)));
		resultado += (getY(c)*Li);
	}
	return resultado;
}



