//--------------------------------------------------------------
// This program implements a simple drawing application
// using glut and openGL
//
// Written by: Edson L. Araújo
// October 24, 2006
//--------------------------------------------------------------
//#define _STDCALL_SUPPORTED
//#define _M_IX86

/*
 * Universidade Federal do Vale do São Francisco
 * Trabalho de Cálculo Numérico - Grupo 06 - Integração Numérica - 28/08/2016
 * Professor: Edson Leite Araújo
 * Alunos:	Rayssa Carvalho da Silva
 * 			Ricardo Figueiredo de Oliveira
 *			Ricardo Valério Teixeira de Medeiros Silva
 *			Ruan de Medeiros Bahia
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>
#include <GL\glut.h>

#include "list.h"
#include "points.h"
#include "picker.h"
#include "Matriz.hpp"
#include "Lagrange.hpp"
#include "Spline.hpp"

GLint antialiasing		  = 1;

picker Picker;

double *xMtx,*yMtx;
int n;

Polinomio *polinomio = NULL;
Lagrange *lagrange = NULL;
Spline *spline = NULL;

double *xAnterior = NULL;
double *yAnterior = NULL;

int nAnteriorLin = 0;
int nAnteriorL = 0;
int nAnteriorS = 0;
int seletor = 0;
int N_PONTOS_NO_GRAFICO = 1000;

double InterpolationLinearSystem(double *x,double *y, int N, double t);
double InterpolationLagrange(double *x,double *y, int N, double t);
double InterpolationSpline(double *x,double *y, int N, double t);
void DrawInterpolationLinearSystem(void);
void DrawInterpolationLagrange(void);
void DrawInterpolationSpline(void);
void menu_inicial();

//===== Global Variables ===========================================//

GLint		width		= 400;
GLint		height		= 400;

GLint		draw_yes	= 0;
GLint		take_points = 1;

//===================================================================//
double InterpolationLinearSystem(double *x,double *y, int N, double t){
	if (N == 1 || x != xAnterior || y != yAnterior){
		Matriz matriz(N,2);
		for (int c = 0 ; c < N ; c++){
			matriz.setElemento(c,0,x[c]);
			matriz.setElemento(c,1,y[c]);
		}
		matriz.interpolar(&polinomio);
		xAnterior = x;
		yAnterior = y;
		cout << endl << "Polinômio pela Forma Linear: ";
		polinomio->imprimir();
		cout << endl;
	}

	return polinomio->getValor(t);
}

double InterpolationLagrange(double *x,double *y, int N, double t){
	//if(N==1 || x != xAnterior || y != yAnterior){
		//xAnterior = x;
		//yAnterior = y;
		delete lagrange;
		lagrange = new Lagrange(x,y,N);
		nAnteriorL = N;
	//}
	return lagrange->interpolar((double) t);
}

double InterpolationSpline(double *x,double *y, int N, double t){
	double resultado;
	//if (N == 1 || x != xAnterior || y != yAnterior){
		//xAnterior = x;
		//yAnterior = y;
		//cout << "Entrou delete" << endl;
		delete spline;
	cout << "int 1" << endl;
		spline = new Spline(N,x,y);
	//}
		cout << "int 2" << endl;
	resultado = spline->interpolar(t);
	cout << "int 3" << endl;
	return resultado;
}
//===================================================================//
void DrawInterpolationLinearSystem(void){
	double dt = ( xMtx[n-1] - xMtx[0] )/1000;
	double x0,y0,x1,y1;

	x0 = xMtx[0];
	y0 = yMtx[0];

	glColor3f(0.0f, 1.0f, 0.0f);	// Verde
	glLineWidth(2.0f);

	for(int i=0; i<N_PONTOS_NO_GRAFICO; i++){

		x1 = x0 + dt;
		y1 = InterpolationLinearSystem(xMtx,yMtx,n,x1);

		glBegin(GL_LINES);
			glVertex2f(x0,y0);
			glVertex2f(x1,y1);
		glEnd();

		x0 = x1;
		y0 = y1;
	}

	glLineWidth(1.0f);
}

void DrawInterpolationLagrange(void){
	double dt = ( xMtx[n-1] - xMtx[0] )/1000;
	double x0,y0,x1,y1;

	x0 = xMtx[0];
	y0 = yMtx[0];

	glColor3f(1.0f, 0.0f, 0.0f);	// Vermelho
	glLineWidth(2.0f);

	for(int i=0; i<N_PONTOS_NO_GRAFICO; i++){

		x1 = x0 + dt;
		y1 = InterpolationLagrange(xMtx,yMtx,n,x1);

		glBegin(GL_LINES);
			glVertex2f(x0,y0);
			glVertex2f(x1,y1);
		glEnd();

		x0 = x1;
		y0 = y1;
	}

	glLineWidth(1.0f);
}
void DrawInterpolationSpline(void){
	double dt = ( xMtx[n-1] - xMtx[0] )/1000;
	double x0,y0,x1,y1;

	x0 = xMtx[0];
	y0 = yMtx[0];

	glColor3f(0.0f, 0.0f, 1.0f); // Azul
	glLineWidth(2.0f);

	for(int i=0; i<N_PONTOS_NO_GRAFICO; i++){

		x1 = x0 + dt;
		y1 = InterpolationSpline(xMtx,yMtx,n,x1);

		glBegin(GL_LINES);
			glVertex2f(x0,y0);
			glVertex2f(x1,y1);
		glEnd();

		x0 = x1;
		y0 = y1;
	}

	glLineWidth(1.0f);
}
//===================================================================//
int GetNumberOfPoints(void){

	DoublyLinkedList<Point> *list = Picker.GetPoints();

	return list->getSize();
}
//===================================================================//
double* GetXMatrix(void){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	double *x = new double[n];

	if(!x){
		printf("Insufficient memory for the X allocation!\n");
		exit(0);
	}

	for(int i=0; i<n; i++){

		x[i] = currNode->data[X];
		currNode = currNode->next;

	}

	return x;
}

//===================================================================//
double* GetYMatrix(void){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	double *y = new double[n];

	if(!y){
		printf("Insufficient memory for the Y allocation!\n");
		exit(0);
	}

	for(int i=0; i<n; i++){

		y[i] = currNode->data[Y];
		currNode = currNode->next;

	}

	return y;
}

//===================================================================//
void UpdateXMatrix(double *x){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	for(int i=0; i<n; i++){

		x[i] = currNode->data[X];
		currNode = currNode->next;

	}
}

//=====================================================================//
void UpdateYMatrix(double *y){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	for(int i=0; i<n; i++){

		y[i] = currNode->data[Y];
		currNode = currNode->next;

	}

}

//=====================================================================//
void myReshapeFunc(int w, int h){

	glViewport(0, 0, w, h);
	Picker.onReshape(w,h);

}

//==== The Mouse Clicks Function =======================================//
void myMouseFunc(int button, int state, int x, int y){

	Picker.onMouse(button,state,x,y);

	delete [] xMtx;
	delete [] yMtx;

	xMtx = GetXMatrix();
	yMtx = GetYMatrix();

	n = GetNumberOfPoints();
}
//======================================================================//
void myMotionFunc(int x, int y){

	Picker.onMotion(x,y);

	UpdateXMatrix(xMtx);
	UpdateYMatrix(yMtx);
}

//======================================================================//
void myKeyboardFunc(unsigned char key, int x, int y){

	switch (key) {
	  case 32:
	  case 13:
		  draw_yes    = 1;
		  take_points = 0;
		  glutPostRedisplay ();
	}
}
//======================================================================//
// myinit is used to set coordinate systems.
// Establish the coordinate system
void myinit () {
	glViewport(0, 0, width, height);
	gluOrtho2D (0, width, height, 0);
	glEnable(GL_SMOOTH);
}

//======================================================================//
// right_menu is called whenever an item is chosen
// from the menu associated with the right mouse button

// A simple menu function.
void MyRightMenu (int id) {
	switch(id){

	case 1:

		Picker.Reset();
		draw_yes = 0;
		take_points = 1;

		glutPostRedisplay ();
		break;

	case 2:
		exit (0);

	case 3:
		draw_yes = 1;
		take_points = 0;
		break;

	case 9:
		if (antialiasing) {
			glDisable(GL_BLEND);
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POINT_SMOOTH);
		} else {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POINT_SMOOTH);
		}

		antialiasing ^= 1;
		glutPostRedisplay();

		break;
	case 21:
		seletor = 1;
		glutPostRedisplay ();
		break;
	case 22:
		seletor = 2;
		glutPostRedisplay ();
		break;
	case 23:
		seletor = 3;
		glutPostRedisplay ();
		break;
	}
}

//======================================================================//
void myDisplayFunc(){

	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);

	Picker.DrawPoints();
	Picker.DrawPolygonal();

	if(draw_yes){
		switch(seletor){
			case 1:
				DrawInterpolationLagrange();
				break;
			case 2:
				DrawInterpolationSpline();
				break;
			case 3:
				DrawInterpolationLagrange();
				DrawInterpolationSpline();
				break;
			case 4:
				DrawInterpolationLinearSystem();
				break;
			case 5:
				DrawInterpolationLagrange();
				DrawInterpolationSpline();
				DrawInterpolationLinearSystem();
				break;
			default:
				DrawInterpolationLagrange();
		}
	}

	glFlush();
	glutSwapBuffers();
}
//======================================================================//
// The main program creates a window, associates
// menus and callback functions with the window,
// then starts glut's event processing loop

int main (int argc, char ** argv){
	menu_inicial();

	glutInit(&argc, argv);

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow ("Calculo Numerico (c) Edson L. Araujo");

	glutCreateMenu (MyRightMenu);

	glutAddMenuEntry ("Clear",  1);
	glutAddMenuEntry ("Exit",   2);
	glutAddMenuEntry ("Start",  3);
	glutAddMenuEntry ("Antialiasing",9);
	glutAddMenuEntry ("-Forma de Lagrange (vermelho)",21);
	glutAddMenuEntry ("-Spline Cubica Natural (azul)",22);
	glutAddMenuEntry ("-As duas ao mesmo tempo (experimental)",23);

	glutAttachMenu (GLUT_RIGHT_BUTTON);

	glutDisplayFunc ( myDisplayFunc  );
	glutMouseFunc   ( myMouseFunc    );
	glutMotionFunc  ( myMotionFunc   );
	glutKeyboardFunc( myKeyboardFunc );
	glutReshapeFunc ( myReshapeFunc  );

	Picker.SetBuffer();

	glutMainLoop();

	return 0;
}
//======================================================================//
void menu_inicial(){
	cout << "Trabalho de Cálculo Numérico - Grupo 06 - Integração Numérica - 28/08/2016" << endl;
	cout << "Alunos: 	Rayssa Carvalho da Silva" << endl <<
 			"		Ricardo Figueiredo de Oliveira" << endl <<
 			"		Ricardo Valério Teixeira de Medeiros Silva" << endl <<
 			"		Ruan de Medeiros Bahia" << endl;
	cout << "Problema 1: Interpolação utilizando a Forma de Lagrange." << endl;
	cout << "Problema 2: Interpolação utilizando Spline Cúbica Natural." << endl;
	cout << "Extra (3): Interpolação utilizando Forma de Lagrange e Spline Cúbica Natural ao mesmo tempo" << endl;
	cout << "Extra (4): Interpolação utilizando Sistema Linear - Força Bruta - Matriz de Vandermonde " << endl;
	cout << "Extra (5): Interpolação utilizando Todos acima" << endl;
	do {
		cout << "Digite o número do problema que deseja resolver: " ;
		cin >> seletor;
	} while (seletor > 5 || seletor < 1);

	cout << "O polinômio da Forma de Lagrange tem linha de cor vermelha." << endl;
	cout << "A Spline Cúbica Natural tem linha de cor azul." << endl;
	cout << "O polinômio da Matriz de Vandermonde tem linha de cor verde." << endl;
}
