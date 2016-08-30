#include "Spline.hpp"

Spline::Spline(const int &n,const double *x,const double *y) :
	a(vector<double>(n)),
	b(vector<double>(n-1)),
	c(vector<double>(n)),
	d(vector<double>(n-1)),
	x(vector<double>(n)),
	h(vector<double>(n-1))
{
	for (int c = 0; c < n; c++){
		a[c] = y[c];					//	Definindo os coeficientes a[i]
		this->x[c] = x[c];				//	Guardando o vetor x[i]
	}
	if (n > 1) {
		for (int c = 0; c < (n-1); c++){	//	Calculando as diferenças h
			h[c] = x[c+1] - x[c];
		}

		A = new Matriz(n,n);

		A->setElemento(0,0,1.0);
		A->setElemento(A->getLinhas()-1,A->getColunas()-1,1.0);
		A->setB(0, 0.0);

		A->setElemento(1,0,h[0]);

		for (int c = 1; c < (n-1); c++) {
			A->setElemento(c+1,c,h[c]);
			A->setElemento(c,c+1,h[c]);

			A->setElemento(c,c,2*(h[c] + h[c-1]));

			A->setB(c, (3/h[c])*(a[c+1] - a[c]) - (3/h[c-1])*(a[c] - a[c-1]));
		}

		A->setElemento(0,1,0.0);
		A->setElemento(A->getLinhas()-1,A->getColunas()-2,0.0);
		A->setB(A->getLinhas()-1, 0.0);

		calcularCoeficientesC();
		calcularCoeficientesD();
		calcularCoeficientesB();
	}
}

Spline::~Spline(){
	if (this == NULL) {
		cout << "Splined 1" << endl;
		if (A)
			delete A;
		cout << "Splined 2" << endl;
	}
}
double Spline::S(const int &j, const double &x){
	if ((j >= 0) && (j < a.size())) {
		return (a[j] + (x-this->x[j])*(b[j] + (x-this->x[j])*(c[j] + (d[j]*(x-this->x[j])) )));
	}
	else
		return 0.0;
}

double Spline::interpolar(const double &x){
	if (a.size() == 1){
		return a[0];
	}
	else
		return (S(localizar(x),x));
}

int Spline::localizar(const double x){
	int jSuperior;
	int jInferior;
	int jm;
	if (a.size() < 2){
		cout << "ERRO! Não é possível localizar com somente um ponto." << endl;
		return 0;
	}
	bool ver=(this->x[this->x.size()-1] >= this->x[0]);
	jInferior=0;
	jSuperior=this->x.size()-1;
	while (jSuperior-jInferior > 1) {
		jm = (jSuperior+jInferior)/2;
		if ((x >= this->x[jm]) == ver)
			jInferior=jm;
		else
			jSuperior=jm;
	}
	return fmax(0,fmin(this->x.size()-2,jInferior));
}

void Spline::calcularCoeficientesB(){
	for (int j = 0; j < this->b.size(); j++)
		b[j] = ( (a[j+1] - a[j]) /h[j] ) - ( h[j]*(c[j+1] + 2*c[j])/ 3);
}
void Spline::calcularCoeficientesC(){
	triangularTridiagonal();
	substituirTridiagonal();
}
void Spline::calcularCoeficientesD(){
	for (int j = 0; j < this->d.size(); j++)
		d[j] = (this->c[j+1] - this->c[j])/ (3*h[j]) ;
}

void Spline::triangularTridiagonal(){
	double m;
	for(int j = 0; j !=  (A->getColunas() - 1); j++){
		if (A->getElemento(j,j) == 0){
			cout << "ERROR!" <<
					"Sistema impossível de ser resolvido pelo modo tridiagonal." << endl;
			exit(1);
		}

		m = ((A->getElemento(j+1,j)) / ((A->getElemento(j,j))));
		A->setElemento(j+1,j,0);

		A->setElemento(j+1,j+1, A->getElemento(j+1,j+1) - (m * A->getElemento(j,j+1)));
		A->setB(j+1, A->getB(j+1) - (m * A->getB(j)));
	}
}

void Spline::substituirTridiagonal(){
	int c = this->c.size();
	this->c[c] = A->getB(A->getLinhas()-1)/A->getElemento(A->getLinhas()-1,A->getColunas()-1);

	for (c--; c >= 0; c--)
		this->c[c] = (A->getB(c) - A->getElemento(c,c+1)*this->c[c+1])/A->getElemento(c,c);
}
