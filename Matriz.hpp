#ifndef MATRIZ_HPP_
#define MATRIZ_HPP_

#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <iostream>

#include "Polinomio.hpp"

using namespace std;

class Matriz{
	private:
		int linhas;
		int colunas;
		double **elementos;
		void setLinhas(int);
		void setColunas(int);
		void pivoteamento(int**,char modo);
		double decressimoDoJaCalculado(int l,double *x,char modo);
		void LmLY(int l1,int l2,double m,char modo);//linha1 - linha2 * m apartir de linha2+1
	public:
		double *b;
		Matriz(const int nLinhas, const int nColunas);
		Matriz(int n,float*x,float*y);
		Matriz(int n,double *x,double *y);
		~Matriz();
		void setB(int,double);
		double getB(int);
		int getLinhas(void) const;
		int getColunas(void) const;
		void setElemento(const int linha,const int coluna,const double elemento);
		double getElemento(const int linha,const int coluna) const;
		void trocaLinhas(int,int);
		double LU(int modo,int *b,int *p);
		void imprimirMatriz(void);
		void setMatriz(void);
		void setVetorB(void);
		int* fatoracaoLU(char modo,int *p);
		void eliminacaoDeGauss(void);
		void gaussJacobi(void);
		double alfa(void);
		void  resolveSistemaTriangular(char modo);
		void mostraSolucaoMatriz();
		void copiaMatriz(Matriz*);
		void copiaVetorMatriz(Matriz*);
		void interpolar(Polinomio **px);
};
#endif
