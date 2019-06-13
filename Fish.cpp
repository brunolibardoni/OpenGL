#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void animacao(int value);
void keyboard(unsigned char key, int x, int y);

//variaveis globais


float r = 1;
float g = 0.0;
float b = 0.0;

float tx = 0.0;
float xStep = 1;
float PI = 3.14;


GLfloat circ_pnt = 500;
GLfloat ang, raioX, raioY;

void display(void);
void screen(GLsizei w, GLsizei h);


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Peixin");

	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(40, animacao, 1);
	glutMainLoop();

	return(0);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		r = 1.0;
		g = 1.0;
		b = 1.0;
		break;

	case '2':
		r = 1.0;
		g = 1.0;
		b = 0.0;
		break;

	case '3':
		r = 0.8;
		g = 0.0;
		b = 0.6;
		break;

	case '4':
		r = 1.0;
		g = 0.0;
		b = 0.0;
		break;

	}
}

void animacao(int value) {

	if (tx > 80 || tx < -80) {
		xStep = -xStep;

	}

	tx += xStep;

	glutPostRedisplay();
	glutTimerFunc(20, animacao, 0);
}

void peixe() {

	if (xStep == 1) {
		glScaled(1, 1.5, 0);
	}

	if (xStep == -1) {
		glScaled(-(1), 1.5, 0);
	}

	//parte de cima
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(5, 5);
	glColor3f(r, g, b);
	glVertex2f(10, 7.5);
	glVertex2f(15, 8);
	glVertex2f(14, 11);
	glVertex2f(9, 9);
	glEnd();

	//nadadeira
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(1, 1);
	glColor3f(r, g, b);
	glVertex2f(-5, 10);
	glVertex2f(-5, 0);
	glVertex2f(-5, -10);
	glEnd();

	//corpo
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex2f(0, 0);
	glVertex2f(5, 5);
	glVertex2f(10, 7.5);
	glVertex2f(15, 8);
	glVertex2f(20, 6);
	glVertex2f(23, 3);
	glVertex2f(24, 0);
	glVertex2f(23, -3);
	glVertex2f(20, -6);
	glVertex2f(15, -8);
	glVertex2f(10, -7.5);
	glVertex2f(5, -5);
	glEnd();

	//olhos
	raioX = 1.0f;

	glTranslatef(21, 2, 0);
	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 100; i++) {
		ang = (2 * PI * i) / 20;
		glVertex2f(cos(ang)*raioX, sin(ang)*raioX);
	}

	glEnd();
}

void aquario() {

	raioX = 120;
	raioY = 75;
	glPushMatrix();

	glColor4f(0.0f, 1.0f, 1.0f, 0.0f);

	glBegin(GL_POLYGON);

	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();
}

void display() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);


	glViewport(0, 0, 1000, 700);
	glPushMatrix();
	glTranslated((1000) / 2, (700) / 2, 0);
	glScaled(2, 2, 2);

	aquario();

	//mover o peixe
	glPushMatrix();
	glTranslated(tx, 0, 0);
	peixe();
	glPopMatrix();

	glFlush();
}

void screen(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, 1000, 0, 700);
	glMatrixMode(GL_MODELVIEW);
}




