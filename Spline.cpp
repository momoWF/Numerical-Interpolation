#include "Spline.hpp"

using namespace std;

double maior(double A, double B){
	if (A > B)
		return A;
	else
		return B;
}

double menor(double A, double B){
	if (A < B)
		return A;
	else
		return B;
}

Spline::Spline(vector<double> &novoVetorX, vector<double> &novoVetorY, const int &novoTamanho){
	setTamanho(novoTamanho);
	vetorX = &novoVetorX[0];
	vetorY = &novoVetorY[0];
	g  = vector<double>(novoTamanho);
	calcularG();
}

void Spline::setTamanho(double novoTamanho){
	tamanho = novoTamanho;
}

int Spline::getTamanho(){
	return tamanho;
}

void Spline::calcularG(){
	int i,c,n=g.size();
	double p,un,qn,sig;
	vector<double> aux(n-1);
	g[0]=aux[0]=0.0;			//	Parâmetro do Spline Cúbico Natural
	for (i=1;i<n-1;i++) { 	//	Decomposição da matriz tridiagonal
		sig=(vetorX[i]-vetorX[i-1])/(vetorX[i+1]-vetorX[i-1]);
		p=sig*g[i-1]+2.0;
		g[i]=(sig-1.0)/p;
		aux[i]=(vetorY[i+1]-vetorY[i])/(vetorX[i+1]-vetorX[i]) - (vetorY[i]-vetorY[i-1])/(vetorX[i]-vetorX[i-1]);
		aux[i]=(6.0*aux[i]/(vetorX[i+1]-vetorX[i-1])-sig*aux[i-1])/p;
	}
	un = qn = 0; 			//	Parâmetro do Spline Cúbico Natural
	g[n-1]=(un-qn*aux[n-2])/(qn*g[n-2]+1.0);
	for (c=n-2;c>=0;c--) 	// Resolvendo a matriz tridiagonal
		g[c]=g[c]*g[c+1]+aux[c];
}

double Spline::interpolar(double x) {
	int loc = localizar(x);
	int kMenor=loc,kMaior=loc+1;
	double y,h,b,a;
	h=vetorX[kMaior]-vetorX[kMenor];
	if (h == 0.0){
		cout << "ERRO! Valores em x muito próximos.";
	}
	a=(vetorX[kMaior]-x)/h;
	b=(x-vetorX[kMenor])/h; // Calculando o Spline
	y=a*vetorY[kMenor]+b*vetorY[kMaior]+((a*a*a-a)*g[kMenor]+(b*b*b-b)*g[kMaior])*(h*h)/6.0;
	return y;
}

int Spline::localizar(const double x){
	int jSuperior;
	int jInferior;
	int jm;
	if (getTamanho() < 2){
		cout << "ERRO! Não é possível localizar com somente um ponto." << endl;
		return 0;
	}
	bool ver=(vetorX[getTamanho()-1] >= vetorX[0]);
	jInferior=0;
	jSuperior=getTamanho()-1;
	while (jSuperior-jInferior > 1) {
		jm = (jSuperior+jInferior)/2;
		if ((x >= vetorX[jm]) == ver)
			jInferior=jm;
		else
			jSuperior=jm;
	}
	return maior(0,menor(getTamanho()-2,jInferior));
}
