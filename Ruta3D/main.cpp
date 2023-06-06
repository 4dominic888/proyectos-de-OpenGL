#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include "glm.h"
#include "Texture.h"
#include <stdarg.h>
#include <vector>
#include <windows.h>

//?Variables

//* Variables de estado de la cámara
float cameraX = 5.0f;
float cameraY = 5.0f;
float cameraZ = 5.0f;

//* Variables de control de movimiento teclado
bool moveForward = false;
bool moveBackward = false;
bool moveLeft = false;
bool moveRight = false;
bool moveUp = false;
bool moveDown = false;

//* Variables de control de movimiento mouse
const float moveSpeed = 0.1f;
const float rotateSpeed = 0.0025f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
int lastMouseX = 0;
int lastMouseY = 0;
int buttonMouse;



//*Variables de textura
GLMmodel* pista = NULL;
GLMmodel* skybox = NULL;




GLuint	texture;

std::vector<Texture> treeTextureAr;

//* Extras


bool LoadTextures(int numArgs, ...){
	va_list args;
    va_start(args, numArgs);
	//Texture textura;
	treeTextureAr.resize(numArgs);

    for (int i = 0; i < numArgs; i++)
    {
        char* arg = va_arg(args, char*);
		if (!LoadTGA(&treeTextureAr[i], arg)) return false;
		glGenTextures(1, &treeTextureAr[i].texID);
			glBindTexture(GL_TEXTURE_2D, treeTextureAr[i].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, treeTextureAr[i].bpp / 8, treeTextureAr[i].width, treeTextureAr[i].height, 0, treeTextureAr[i].type, GL_UNSIGNED_BYTE, treeTextureAr[i].imageData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_2D);
			if (treeTextureAr[i].imageData)
			{
				free(treeTextureAr[i].imageData);
			}
    }
    va_end(args);
	return true;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	gluPerspective(45.0, (double)500 / (double)500, 0.1, 100.0);
	LoadTextures(2, "modelos/pistas/carretera.tga",
					"modelos/skybox/tarde.tga"



	);
}

void grilla(){
	glPushMatrix();
	glTranslatef(-250.0f, 0.0f, -250.0f);

	glColor3f(.4f, .4f, .4f);
    glBegin(GL_LINES);
    	for (int i = 0; i <= 500; i += 1) {
    	    glVertex3f(0.0f, 0.0f, i);
    	    glVertex3f(500.0f, 0.0f, i);
    	}

    	for (int i = 0; i <= 500; i += 1) {
    	    glVertex3f(i, 0.0f, 0.0f);
    	    glVertex3f(i, 0.0f, 500.0f);
    	}
	glEnd();
	glPopMatrix();
	glColor3f(1.0,1.0,1.0);
}

void graficar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cameraX, cameraY, cameraZ, cameraX + sin(cameraAngleX), cameraY + sin(cameraAngleY), cameraZ - cos(cameraAngleX), 0.0f, 1.0f, 0.0f);



	//grilla();

	glTranslatef(0,-1,0);

	glBindTexture(GL_TEXTURE_2D, treeTextureAr[0].texID);
	glmDraw(pista, GLM_SMOOTH | GLM_TEXTURE);



	glScalef(200,200,200);

    glBindTexture(GL_TEXTURE_2D, treeTextureAr[1].texID);
	glmDraw(skybox, GLM_SMOOTH | GLM_TEXTURE);


	glBindTexture(GL_TEXTURE_2D, 0);

	glutSwapBuffers();


}

void redimensionar(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);

}

//? Keyboard Func
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            moveForward = true;
            break;
        case 's':
        case 'S':
            moveBackward = true;
            break;
        case 'a':
        case 'A':
            moveLeft = true;
            break;
        case 'd':
        case 'D':
            moveRight = true;
            break;
        case 32: // Tecla Espacio
            moveUp = true;
            break;
        case 27: // Tecla ESC para salir
            exit(0);
            break;
    }
}
void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            moveForward = false;
            break;
        case 's':
        case 'S':
            moveBackward = false;
            break;
        case 'a':
        case 'A':
            moveLeft = false;
            break;
        case 'd':
        case 'D':
            moveRight = false;
            break;
        case 32: // Tecla Espacio
            moveUp = false;
            break;
    }
}
void specialKeyBoard(int key, int x, int y){
	switch (key)
	{
		case 112:
			moveDown = true;
			break;
	}
}
void specialKeyBoardUp(int key, int x, int y){
	switch (key)
	{
		case 112:
    	    moveDown = false;
    	    break;
	}
}
void updateMovement(int value) {
    // Movimiento hacia adelante
    if (moveForward) {
        cameraX += moveSpeed * sin(cameraAngleX);
        cameraZ -= moveSpeed * cos(cameraAngleX);
    }

    // Movimiento hacia atrás
    if (moveBackward) {
        cameraX -= moveSpeed * sin(cameraAngleX);
        cameraZ += moveSpeed * cos(cameraAngleX);
    }

    // Movimiento hacia la izquierda
    if (moveLeft) {
        cameraX -= moveSpeed * cos(cameraAngleX);
        cameraZ -= moveSpeed * sin(cameraAngleX);
    }

    // Movimiento hacia la derecha
    if (moveRight) {
        cameraX += moveSpeed * cos(cameraAngleX);
        cameraZ += moveSpeed * sin(cameraAngleX);
    }

    // Movimiento hacia arriba
    if (moveUp) {
        cameraY += moveSpeed;
    }

    // Movimiento hacia abajo
    if (moveDown) {
        cameraY -= moveSpeed;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateMovement, 0); // Actualizar cada 16 ms (aproximadamente 60 FPS)
}

//? Mouse func
void mouse(int button, int state, int x, int y) {
    lastMouseX = x;
    lastMouseY = y;
	buttonMouse = button;

}
void motion(int x, int y) {
	if (buttonMouse == GLUT_LEFT_BUTTON) {
    	int deltaX = x - lastMouseX;
    	int deltaY = y - lastMouseY;
    	cameraAngleX -= rotateSpeed * deltaX;
    	cameraAngleY += rotateSpeed * deltaY;

    	if (cameraAngleY > 1.2) {
    	    cameraAngleY = 1.2;
    	}
		else if (cameraAngleY < -1.2) cameraAngleY = -1.2;

    	lastMouseX = x;
    	lastMouseY = y;
	}
}


void animate(int i)
{

}

void maximizeWindow() {
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Prueba");
	maximizeWindow();

	init();


    skybox = glmReadOBJ("modelos/skybox/tarde.obj");

	pista = glmReadOBJ("modelos/pistas/pista_plana.obj");



	glutReshapeFunc(redimensionar);
	glutDisplayFunc(graficar);


	glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKeyBoard);
	glutSpecialUpFunc(specialKeyBoardUp);
	glutTimerFunc(0, updateMovement, 0);

	glutMotionFunc(motion);
	glutMouseFunc(mouse);


	glutTimerFunc(2, animate, 1);
	glutMainLoop();
	return 0;
}
