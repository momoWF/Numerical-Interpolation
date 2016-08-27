#include "LagrangeO.hpp"

LagrangeO::LagrangeO(int novoTamanho, double *novoVetorX, double *novoVetorY){
	setTamanho(novoTamanho);
	setVetorX(novoVetorX);
	setVetorY(novoVetorY);
}

void LagrangeO::setVetorX(double *novoVetorX){
	vetorX = novoVetorX;
}

void LagrangeO::setVetorY(double *novoVetorY){
	vetorY = novoVetorY;
}

double LagrangeO::getX(const int &i){
	if (i >=0 && i < getTamanho())
		return vetorX[i];
	else
		return 0.0;
}

double LagrangeO::getY(const int &i){
	if (i >=0 && i < getTamanho())
		return vetorY[i];
	else
		return 0.0;
}

int LagrangeO::getTamanho(){
	return tamanho;
}
void LagrangeO::setTamanho(int novoTamanho){
	tamanho = novoTamanho;
}

double LagrangeO::pi(const double &x){
	double resultado = 1;
	for (int c = 0; c < getTamanho(); c++)
		resultado *= (x - getX(c));
	return resultado;
}

double LagrangeO::D(const double &i){
	double resultado = 1;
	for (int c = 0; c < getTamanho(); c++)
		if (c != i)
			resultado *= (getX(i) - getX(c));
	return resultado;
}

double LagrangeO::interpolar(const double &x){
	//Polinomio *polinomio = new Polinomio(getTamanho());
	double resultado = 0;
	double Li = 0;
	for (int c = 0; c < getTamanho(); c++){
		Li = (1/((x-getX(c))*D(c)));
		resultado += (getY(c)/Li);
	}
	resultado *= pi(x);
	return resultado;
}
