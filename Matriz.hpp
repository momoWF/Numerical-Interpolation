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
		Matriz(int l, int c);
		Matriz(int n,float*x,float*y);
		~Matriz();
		void setB(int,double);
		double getB(int);
		int getLinhas(void);
		int getColunas(void);
		void setElementos(int,int,double);
		double getElementos(int,int);
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
