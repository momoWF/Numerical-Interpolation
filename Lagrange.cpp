#include "Lagrange.hpp"

Lagrange::Lagrange(Matriz *x){
	if(x->getLinhas()>0 && x->getColunas() ==2){
		diferencas = new Matriz(x->getLinhas(),x->getLinhas());

		for(int l=0;l<diferencas->getLinhas();l++){
			for(int c=0;c<diferencas->getColunas();c++){
				if(l != c)
					diferencas->setElemento(l,c,x->getElemento(l,0)-x->getElemento(c,0));
				else
					diferencas->setElemento(l,c,x->getElemento(c,0));
			}
			diferencas->setB(l,x->getElemento(l,1));
		}
	}
}
Lagrange::Lagrange(float *x, float *y, int n){
	diferencas = new Matriz(n,n);
	for(int l=0;l<diferencas->getLinhas();l++){
		for(int c=0;c<diferencas->getColunas();c++){
			if(l != c)
				diferencas->setElemento(l,c,x[l]-x[c]);
			else
				diferencas->setElemento(l,c,x[c]);
		}
		diferencas->setB(l,y[l]);
	}
}

Lagrange::~Lagrange(){
	delete diferencas;
}

double Lagrange::pi(const double &x){
	double pi=1;

	for (int c=0; c < diferencas->getLinhas() ; c++)
		pi*=(x-diferencas->getElemento(c,c));

	return pi;
}

double Lagrange::D(const int &i,const double &x){
	double D=(x-diferencas->getElemento(i,i));

	for(int c=0;c<diferencas->getColunas(); c++)
		if(i!=c)
			D*=diferencas->getElemento(i,c);

	return D;
}

double Lagrange::S(const double &x){
	double S=0;

	for(int c=0; c <diferencas->getLinhas() ;c++){
		S+=(diferencas->getB(c)/D(c,x));
	}

	return S;
}

double Lagrange::interpolar(const double &x){
	return pi(x)*S(x);
}
