#ifndef _PICKER_H_
#define _PICKER_H_

#include <GL/glut.h>

#include <stdlib.h>
#include <stdarg.h>
#include "list.h"
#include "points.h"


class picker{

private:
	DoublyLinkedList<Point> points;
	Node<Point> *onNode;

	GLint		viewport[4];
	GLdouble	side;
	GLuint		selectedPoint;
	GLuint		selectBuffer[64];
	GLdouble	modelMatrix[16];
	GLdouble	projMatrix[16];

	void		Ortho(void);
	void		MovePoint(GLuint n, GLdouble x, GLdouble y);
	void		DrawString(GLdouble x, GLdouble y, char* format, ...);
	void		Square(GLenum mode, GLdouble x, GLdouble y, GLdouble r);

public:

	picker(void){
		onNode = NULL; 
		selectedPoint = (GLuint) ~0; 
		viewport[2] = viewport[3] = 400;
	};

	DoublyLinkedList<Point> *GetPoints(void){ return &points; };

	void		onReshape(GLint w,GLint h);
	void		onMouse(GLint button, GLint state, GLint x, GLint y);
	void		onMotion(GLint x, GLint y);

	void		DrawPoints(void);
	void		DrawPolygonal(void);
	void		RegisterPoints(GLuint start);
	GLuint		GetSelectedPoint(GLint x, GLint y);
	void		SetBuffer(void);
	void		Reset(void){ points.reset(); };

	~picker(void){points.reset();};
};
#endif
