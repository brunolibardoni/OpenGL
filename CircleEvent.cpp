#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 600
#define windowW 600

float PI = 3.14;

//structs
struct Vertices {
	int x = 50;
	int y = 150;
};

struct Vertices v1;
struct Vertices v2;

//variaveis do circulo
GLfloat circ_pnt = 200;
GLfloat eixo;

//cor rgb
float r = 1;
float g = 0;
float b = 0;

//variaveis para a colisao com o mouse
float valorA;
float valorB;
float valorC;
int flag = 0;


void display(void);
void screen(GLsizei w, GLsizei h);
void movimentarMouse(int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Colisão de esferas");
	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(movimentarMouse);
	glutMainLoop();

	return(0);
}

void movimentarMouse(int x, int y) {
	v1.x = x - (windowW / 2);
	v1.y = y - (windowH / 2);

	valorA = v1.x - v2.x;
	valorB = v1.y - v2.y;
	valorC = sqrt((valorA * valorA) + (valorB * valorB));

	if (valorC < (eixo * 2)) {
		flag = 1;
	}
}

void esfera() {

	glColor3f(r, g, b);
	eixo = 40;

	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		float ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * eixo, sin(ang) * eixo);
	}
	glEnd();
}

void desenhar() {

	glTranslatef((windowW) / 2, (windowH) / 2, 0);
	glScalef(1, -1, 1);
	glPushMatrix();
	glTranslatef(v2.x, v2.y, 1);
	esfera();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(v1.x, v1.y, 0);
	esfera();
	glPopMatrix();

	if (flag == 1) {
		exit(0);
	}
	glutPostRedisplay();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, windowW, windowH);
	desenhar();

	glutSwapBuffers();
}

void screen(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);

}

