#include "picker.h"

//--------------------------------------------------------------//
void picker::Ortho(void){
	//viewport[2] = width;
	//viewport[3] = height;

	if (viewport[2] < viewport[3]){
		gluOrtho2D(-4.0, 4.0, -4.0 * (GLfloat) viewport[3] / (GLfloat) viewport[2],
			4.0 * viewport[3] / (GLfloat) viewport[2]);

		side = 8.0f/viewport[2];
	}else{
		gluOrtho2D(-4.0 * (GLfloat) viewport[2] / (GLfloat) viewport[3],
			4.0 * (GLfloat) viewport[2] / (GLfloat) viewport[3], -4.0, 4.0);

		side = 8.0f/viewport[3];
	}
}

//--------------------------------------------------------------//
void picker::DrawString(GLfloat x, GLfloat y, char* format, ...){

	va_list args;
	char buffer[255], *s;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glRasterPos2f(x + 4*side, y + 3*side);

	for (s = buffer; *s; s++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *s);

}

//--------------------------------------------------------------//
void picker::onReshape(GLint w,GLint h){

	viewport[0] = 0;
	viewport[1] = 0;
	viewport[2] = w;
	viewport[3] = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Ortho();
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
}

//--------------------------------------------------------------//
void picker::onMouse(GLint button, GLint state, GLint x, GLint y){

	Point *pt;

	if (button == GLUT_LEFT_BUTTON) {

		if (state == GLUT_DOWN) {

			selectedPoint = GetSelectedPoint(x,y);

			if(selectedPoint == ~0){

				GLdouble objx, objy, objz;

				gluUnProject(
					x,  viewport[3] - y,  0.00f,
					modelMatrix, 
					projMatrix, 
					viewport,
					&objx, &objy, &objz
				);

				pt = new Point;
				pt->set(objx,objy);
				//points.insertBack(pt);
				points.insert(pt);

				glutPostRedisplay();

			}

		} else {

			selectedPoint = ~0; 
			onNode = NULL;

			glutPostRedisplay();

		}
	}
}
//--------------------------------------------------------------//
void picker::onMotion(GLint x, GLint y){

	GLdouble objx, objy, objz;

	if (selectedPoint != ~0) {

		gluUnProject(
			x,  viewport[3] - y,  0.00f,
			modelMatrix, 
			projMatrix, 
			viewport,
			&objx, &objy, &objz
		);

		MovePoint(selectedPoint,objx,objy);
		glutPostRedisplay();

	}
}

//--------------------------------------------------------------//
void picker::MovePoint(GLuint n, GLfloat x, GLfloat y){
	
	Node<Point> *head, *tail, *currNode;

	head = points.getHead();
	tail = points.getTail();

	currNode = head;

	for(GLuint i=0; i<n; i++){
		currNode = currNode->next;
	}

	if(currNode == head){
		if(currNode->next->data[X] > x ){
			currNode->data.set(x,y);
			onNode = currNode;
		}

		return;

	}

	if(currNode == tail){

		if(currNode->prev->data[X] < x ){
			currNode->data.set(x,y);
			onNode = currNode;
		}

		return;

	}


	if(currNode->prev->data[X] < x &&
		currNode->next->data[X] > x ){
			currNode->data.set(x,y);
			onNode = currNode;
	}

}

//--------------------------------------------------------------//
void picker::RegisterPoints(GLuint start){

	GLuint	n = points.getSize();
	Point	currData;
	Node<Point>*	currNode = points.getHead();

	if(!currNode){
		//printf("There is nothing in the list !!! \n");
		return;
	}

	for(GLuint i = start; i < start + n; i++){

		currData = currNode->data;
		glLoadName(i);
		glBegin(GL_POINTS);
		glVertex2f( currData[X], currData[Y] );
		glEnd();

		currNode = currNode->next;
	}

}

//--------------------------------------------------------------//
GLuint picker::GetSelectedPoint(GLint x, GLint y){

	int hits;

	(void) glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(~0);
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(x, viewport[3] - y, 8.0, 8.0, viewport);
		Ortho();
		glMatrixMode(GL_MODELVIEW);
		RegisterPoints(0);
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);

	if (hits) {
		return selectBuffer[3];
	} else {
		return ~0;
	}
}

//--------------------------------------------------------------//
void picker::Square(GLenum mode, GLfloat x, GLfloat y, GLfloat r){

	glBegin(mode);
		glVertex2f(x-r*side,y-r*side);
		glVertex2f(x-r*side,y+r*side);
		glVertex2f(x+r*side,y+r*side);
		glVertex2f(x+r*side,y-r*side);
	glEnd();

}
//======================================================================//
void picker::DrawPoints(void){

	GLint	i = 0;
	Node<Point>	*currNode = points.getHead();
	Point	p;
	
	glColor4f(1.0f,1.0f,0.4f,1.0f);

	glPushMatrix();
		glLoadIdentity();

		while(currNode){
			p = currNode->data;
			DrawString(p[X],p[Y],"%d",i);
			currNode = currNode->next;
			i++;
		}

	glPopMatrix();

	currNode = points.getHead();

	while (currNode) {	
		p = currNode->data;
		Square(GL_POLYGON,p[X],p[Y],3); 

		currNode = currNode->next;
	}

	if(onNode){
		Square(GL_LINE_LOOP, onNode->data[X], onNode->data[Y],6);
	}
}

//--------------------------------------------------------------//
void picker::DrawPolygonal(void){

	Node<Point> *currNode = points.getHead();
	Point p,q;

	if(!currNode) return;

	glColor4f(0.0f, 0.64f, 0.64f,0.75f);
	glBegin(GL_LINES);

	p = currNode->data;
	while (currNode->next) {

		q = currNode->next->data;

		glVertex2f(p[X], p[Y]);
		glVertex2f(q[X], q[Y]);

		p = q;
		currNode = currNode->next;
	}

	glEnd();    
}
//--------------------------------------------------------------//
void picker::SetBuffer(void){
	glSelectBuffer(sizeof(selectBuffer), selectBuffer);
}
//--------------------------------------------------------------//
