#include "Polinomio.hpp"
Polinomio::Polinomio(int grau){
	if(grau>0){
		coeficientes = new double[grau+1];
		if(coeficientes)
			setGrau(grau);
		else{
			cout<<"Erro ao alocar polinomio"<<endl;
			exit(2);
		}
	}
	else{
		cout<<"Inicializacao invalida de polinomio"<<endl;
		exit(1);
	}
}
Polinomio::~Polinomio(){
	if(coeficientes)
		delete []coeficientes;
}

void	Polinomio::setGrau(int novoGrau){
	grau=novoGrau;
}
int		Polinomio::getGrau(){
	return grau;
}
void 	Polinomio::setCoeficiente(int i,double valor){
	coeficientes[i]=valor;
}
double	Polinomio::getCoeficiente(int i){
	return coeficientes[i];
}
double	Polinomio::getValor(double x){
	int c;
	double valor;

	for(c=grau,valor=coeficientes[c];c>0;c--){/*Aplica o metodo dos parenteses encaixados de horner para achar o valor do polinomio no ponto*/
		valor*=x;
		valor+=getCoeficiente(c-1);
	}

	return valor;
}
void	Polinomio::imprimir(){
	for(int c=getGrau();c>-1;c--){
		cout<<getCoeficiente(c)<<"*x^"<<c<<" ";
	}
}


