#include<GL/glew.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 900
#define windowW 1600

void reshape(GLsizei w, GLsizei h);
void display();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("cubo");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0f, aspect, 1.0f, 80.0f);

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(-1.0f, -0.9f, -7.5f);
	glBegin(GL_TRIANGLES);

	//frente
	glColor3f(1, 1, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);

	//direita
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(0, 1, 0);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);

	//atras
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(0, 1, 0);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);

	//esquerda
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(0, 1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();

	glTranslatef(3.9, -1.0, -3);

	glBegin(GL_QUADS);


	// (frente) 
	glColor3f(1, 0, 0);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, -1, 1);


	// (atrás)
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.4, -0.5, 1);
	glColor3f(0, 1, 0);
	glVertex3f(0.5, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(-1, -0.5, 1);


	// (direito)
	glColor3f(1, 0, 0);
	glVertex3f(1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, -1, 1);

	// (esquerdo)
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, -1);

	// (em cima) 
	glColor3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 1);
	glVertex3f(-1, 1, 1);

	// (embaixo)
	glColor3f(1, 0, 0);
	glVertex3f(1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(-1, -1, -1);

	glEnd();
	glutSwapBuffers();
}

