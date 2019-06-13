#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<GL/freeglut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>

// keycodes
#define VK_W 0x57
#define VK_S 0x53
#define VK_C 0x43
#define VK_V 0x56

// raquetes
int larguraRaquete = 20;
int alturaRaquete = 80;
int velocidadeRaquete = 8;

// posicao da raquete esquerda
float raqueteEsquerda_x = 20;
float raqueteEsquerda_y = 300;

// decalaracao rgb

float r = 1;
float g = 1;
float b = 1;

// tamanho da janela
int largura = 800;
int altura = 700;
int intervalo = 1000 / 60;

// posicao da raquete direita
float raqueteDireita_x = largura - larguraRaquete - 10;
float raqueteDireita_y = 300;

// bola
float posBola_x = largura / 2;
float posBola_y = altura / 2;
float dirBola_x = 5.0f;
float dirBola_y = 5.0f;
int tamanhoBola = 12;
int velocidadeBola = 1;

// pontuação
int pontEsquerda = 0;
int pontDireita = 0;

//declaração funções
void atualizar(int value);
void desenhar();
void enable2D(int width, int height);
void desenhar(float x, float y, float width, float height);
void atualizarBola();
void keyboard();
void bolinha();



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(largura, altura);
	glutCreateWindow("Jogo do Pong");

	//chamando as funcoes 
	glutDisplayFunc(desenhar);
	glutTimerFunc(intervalo, atualizar, 0);

	enable2D(largura, altura);
	glColor3f(1.0f, 1.0f, 1.0f);


	glutMainLoop();
	return 0;
}

void keyboard() {
	// raquete esquerda
	if (GetAsyncKeyState(VK_W)) raqueteEsquerda_y += velocidadeRaquete;
	if (GetAsyncKeyState(VK_S)) raqueteEsquerda_y -= velocidadeRaquete;

	// raquete direita
	if (GetAsyncKeyState(VK_UP)) {
		raqueteDireita_y += velocidadeRaquete;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		raqueteDireita_y -= velocidadeRaquete;
	}

	if (GetAsyncKeyState(VK_C)) {
		r = 0;
		g = 0;
		b = 0;
	}
	if (GetAsyncKeyState(VK_V)) {
		r = 1;
		g = 1;
		b = 1;
	}

}

void desenhar() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// desenhar as raquetes
	desenhar(raqueteEsquerda_x, raqueteEsquerda_y, larguraRaquete, alturaRaquete);
	desenhar(raqueteDireita_x, raqueteDireita_y, larguraRaquete, alturaRaquete);

	// desenhar a bola
	bolinha();

	glutSwapBuffers();
}

void atualizar(int value) {
	keyboard();

	// atualizando a bola
	atualizarBola();

	// chamando o atualizar de novo no `intervalo` millisegundos
	glutTimerFunc(intervalo, atualizar, 0);

	glutPostRedisplay();
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void desenhar(float x, float y, float width, float height) {
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void bolinha() {
	float PI = 3.14;

	glTranslated((__int64)posBola_x, (__int64)posBola_y, 0);

	// Bolinha
	GLfloat  circ_pnt = 200;
	GLfloat  ang, raioX = 10, raioY = 10;

	glColor3f(r, g, b);

	glBegin(GL_POLYGON);
	for (int i = 0; i < (circ_pnt); i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();
}

void atualizarBola() {
	// voar a bola
	posBola_x += dirBola_x * velocidadeBola;
	posBola_y += dirBola_y * velocidadeBola;

	//  bater a raquete esquerda
	if (posBola_x > raqueteEsquerda_x &&
		posBola_x < raqueteEsquerda_x + larguraRaquete &&
		posBola_y < raqueteEsquerda_y + alturaRaquete &&
		posBola_y > raqueteEsquerda_y) {

		// adicionar uma direcao dependendo aonde a bola bater na raquete ( t será 0.5 se bater em cima, 0 no centro e -0.5 embaixo)
		float t = ((posBola_y - raqueteEsquerda_y) / alturaRaquete) - 0.5f;
		dirBola_x = fabs(dirBola_x); // usando o fabs para forçar a ser positivo
		dirBola_y = t;
	}

	// bater a raquete direita
	if (posBola_x > raqueteDireita_x &&
		posBola_x < raqueteDireita_x + larguraRaquete &&
		posBola_y < raqueteDireita_y + alturaRaquete &&
		posBola_y > raqueteDireita_y) {

		//adicionar uma direcao dependendo aonde a bola bater na raquete(t será 0.5 se bater em cima, 0 no centro e - 0.5 embaixo)
		float t = ((posBola_y - raqueteDireita_y) / alturaRaquete) - 0.5f;
		dirBola_x = -fabs(dirBola_x); // // usando o fabs para forçar a ser negativo
		dirBola_y = t;
	}

	//quando haver pontuacao e o hack tiver ligado, desligar.
	if (posBola_x > raqueteDireita_x + larguraRaquete) {
		r = 1;
		g = 1;
		b = 1;
	}

	//quando haver pontuacao e o hack tiver ligado, desligar.
	if (posBola_x < raqueteEsquerda_x + larguraRaquete) {
		r = 1;
		g = 1;
		b = 1;
	}

	// batendo na parede esquerda
	if (posBola_x < 0) {
		++pontDireita;
		posBola_x = largura / 2;
		posBola_y = altura / 2;
		dirBola_x = fabs(dirBola_x); // forçando para ser positivo a dirBola_x
		dirBola_y = 0;
	}

	// batendo na parede direita
	if (posBola_x > largura) {
		++pontEsquerda;
		posBola_x = largura / 2;
		posBola_y = altura / 2;
		dirBola_x = -fabs(dirBola_x); // forçando para ser negativo a dirBola_x
		dirBola_y = 0;
	}

	// batendo na parte de cima da parede
	if (posBola_y > altura) {
		dirBola_y = -fabs(dirBola_y); // forçando para ser negativo a dirBola_y

	}

	// batendo na parte debaixo da parede
	if (posBola_y < 0) {
		dirBola_y = fabs(dirBola_y); // forçando para ser positivo a dirBola_y
	}
}




sss