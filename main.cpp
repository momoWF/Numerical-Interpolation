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
 * Trabalho de Cálculo Numérico - Integração Numérica
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
#include "Spline.hpp"
#include "Lagrange.hpp"

GLint antialiasing		  = 1;

picker Picker;

float *xMtx,*yMtx;
int n;

Polinomio *polinomio = NULL;
Lagrange *lagrange = NULL;
Spline *spline = NULL;
int nAnteriorLin = 0;
int nAnteriorL = 0;
int nAnteriorS = 0;
int seletor = 0;
int N_PONTOS_NO_GRAFICO = 1000;

float InterpolationLinearSystem(float *x,float *y, int N, float t);
float InterpolationLagrange(float *x,float *y, int N, float t);
float InterpolationSpline(float *x,float *y, int N, float t);
void DrawInterpolationLinearSystem(void);
void DrawInterpolationLagrange(void);
void DrawInterpolationSpline(void);

//===== Global Variables ===========================================//

GLint		width		= 640;
GLint		height		= 480;

GLint		draw_yes	= 0;
GLint		take_points = 1;

//===================================================================//
float InterpolationLinearSystem(float *x,float *y, int N, float t){
	if (N == 1 || N != nAnteriorLin){
		Matriz matriz(N,2);
		for (int c = 0 ; c < N ; c++){
			matriz.setElementos(c,0,x[c]);
			matriz.setElementos(c,1,y[c]);
		}
		matriz.interpolar(&polinomio);
		nAnteriorLin = N;
		cout << endl;
		cout << "Polinômio pela Forma Linear: ";
		polinomio->imprimir();
		cout << endl;
	}

	return polinomio->getValor(t);
}

float InterpolationLagrange(float *x,float *y, int N, float t)
{
	if(N==1 || N != nAnteriorL)
	{
		delete lagrange;
		lagrange = new Lagrange(x,y,N);
		nAnteriorL = N;
	}
	return lagrange->interpolar((double) t);
}

float InterpolationSpline(float *x,float *y, int N, float t){
	double resultado;
	if (N == 1 || N != nAnteriorS){
		vector<double> vetorX(N), vetorY(N);
		for (int c = 0; c < N; c++){
			vetorX[c] = x[c];
			vetorY[c] = y[c];
		}
		nAnteriorS = N;
		delete spline;
		spline = new Spline(vetorX, vetorY, N);
	}
	resultado = spline->interpolar(t);
	return resultado;
}
//===================================================================//
void DrawInterpolationLinearSystem(void){
	float dt = ( xMtx[n-1] - xMtx[0] )/1000;
	float x0,y0,x1,y1;

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
	float dt = ( xMtx[n-1] - xMtx[0] )/1000;
	float x0,y0,x1,y1;

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
	float dt = ( xMtx[n-1] - xMtx[0] )/1000;
	float x0,y0,x1,y1;

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
float* GetXMatrix(void){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	float *x = new float[n];

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
float* GetYMatrix(void){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	float *y = new float[n];

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
void UpdateXMatrix(float *x){

	DoublyLinkedList<Point> *list = Picker.GetPoints();
	Node<Point> *currNode = list->getHead();
	int n = list->getSize();

	for(int i=0; i<n; i++){

		x[i] = currNode->data[X];
		currNode = currNode->next;

	}
}

//=====================================================================//
void UpdateYMatrix(float *y){

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
	cout << "Problema 1: Interpolação utilizando a Forma de Lagrange" << endl;
	cout << "Problema 2: Interpolação utilizando Spline Cúbica Natural" << endl;
	cout << "Extra (3): Interpolação utilizando Forma de Lagrange e Spline Cúbica Natural ao mesmo tempo" << endl;
	cout << "Extra (4): Interpolação utilizando Sistema Linear - Força Bruta - Matriz" << endl;
	cout << "Extra (5): Interpolação utilizando Todos acima" << endl;
	do {
		cout << "Digite o número do problema que deseja resolver: " ;
		cin >> seletor;
	} while (seletor > 5 || seletor < 1);

	cout << "A Forma de Lagrange tem linha de cor vermelha." << endl;
	cout << "A Spline Cúbica Natural tem linha de cor azul." << endl;

	glutInit(&argc, argv);

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow ("Calculo Numerico (c) Edson L. Araujo");

	glutCreateMenu (MyRightMenu);

	glutAddMenuEntry ("Clear",  1);
	glutAddMenuEntry ("Exit",   2);
	glutAddMenuEntry ("Start",  3);
	glutAddMenuEntry ("Antialiasing",9);

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
