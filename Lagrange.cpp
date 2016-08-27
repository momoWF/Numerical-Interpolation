#include "Lagrange.hpp"

Lagrange::Lagrange(Matriz *x)
{
	if(x->getLinhas()>0 && x->getColunas() ==2)
	{
		diferencas = new Matriz(x->getLinhas(),x->getLinhas());

		for(int l=0;l<diferencas->getLinhas();l++)
			for(int c=0;c<diferencas->getColunas();c++)
			{
				if(l-c)//aka as l!=c
					diferencas->setElementos(l,c,x->getElementos(l,0)-x->getElementos(c,0));
				else
					diferencas->setElementos(l,c,x->getElementos(c,0));

				diferencas->setB(c,x->getElementos(c,1));
			}

	}
}
Lagrange::~Lagrange()
{
	delete diferencas;
}
double Lagrange::pi(const double &x)
{
	double pi=1;

	for(int c=0,pi=1 ;c<diferencas->getLinhas(); c++)
		pi*=(x-diferencas->getElementos(c,c));

	return pi;
}
double Lagrange::D(const int &i,const double &x)
{
	double D=(x-diferencas->getElementos(i,i));

	for(int c=0;c<diferencas->getColunas(); c++)
		if(i!=c)
			D*=diferencas->getElementos(i,c);

	return D;
}
double Lagrange::S(const double &x)
{
	int S=0;

	for(int c=0;c<diferencas->getLinhas();c++)
	{
		S+=(diferencas->getB(c)/D(c,x));
	}

	return S;
}
double Lagrange::interpolar(const double &x)
{
	return pi(x)*S(x);
}



