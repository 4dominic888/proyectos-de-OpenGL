#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include "glm.h"
#include "Texture.h"
#include <stdarg.h>
#include <vector>
#include <windows.h>
#include <GL/glui.h>

//?Variables

//* Variables de estado de la cámara
float cameraX = -28.816996;
float cameraY = 5.0f;
float cameraZ = 34.327492f;

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

//* Variables auxiliares
float tempx;
float tempy;
float l = 0.05;
float excavadora_animacion[5] = {0};
int tick;

//*Variables de textura|
GLMmodel* skybox = NULL;
GLMmodel* excavadora1 = NULL;
GLMmodel* excavadora2 = NULL;
GLMmodel* excavadora3_1= NULL;
GLMmodel* excavadora3_2= NULL;
GLMmodel* excavadora4 = NULL;
GLMmodel* excavadora5 = NULL;
GLMmodel* excavadora6 = NULL;
GLMmodel* excavadora7 = NULL;
GLMmodel* excavadora8 = NULL;
GLMmodel* excavadora9 = NULL;
GLMmodel* excavadora10 = NULL;
GLMmodel* excavadora11 = NULL;
GLMmodel* terreno01 = NULL;
GLMmodel* terreno02 = NULL;

//*Variables camara
float vista;
float vistay;
float vistaz;

//* variables GUI
int main_windows = 0;
int active_grilla = 0;
int velocidad_animacion = 1;
int colorExcavadora = 0;
bool parar_excavadora = false;
GLUI_Button * boton;
const char * boton_texto;


//* Extras
GLuint	texture;
std::vector<Texture> treeTextureAr;
int avanzar = 1;

void guiIdle(){
    if(glutGetWindow() != main_windows)
        glutSetWindow(main_windows);

    glutPostRedisplay();
}

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
	LoadTextures(8, "modelos/felorcmale_Body.tga",
                    "modelos/skybox.tga",
                    "modelos/Excavadora_Texture_02.tga",
                    "modelos/terreno/terreno_01.tga",
                    "modelos/terreno/terreno_02.tga",
					"modelos/Excavadora_Texture_01 amarillo.tga",
					"modelos/Excavadora_Texture_01 verde.tga",
					"modelos/Excavadora_Texture_01 morado.tga"
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

void animate(int i)
{	if (!parar_excavadora){
		tick += i;

		if(tick > 0 && tick < 615){
			if (excavadora_animacion[0] < 2.5 * avanzar) excavadora_animacion[0] += 0.005;
		}
		else if(tick > 615 && tick < 1494) {
			if (excavadora_animacion[1] > - 40) excavadora_animacion[1] -= 0.05;
		}
		else if (tick > 1494 && tick < 2075) {
			if (excavadora_animacion[2] > - 2)excavadora_animacion[2] -= 0.005;
		}
		else if (tick > 2075 && tick < 2544){
    	    if (excavadora_animacion[3] > - 18) excavadora_animacion[3] -= 0.05;
		}
		else if (tick > 2544 && tick < 3200){
			if (excavadora_animacion[4] > - 40) excavadora_animacion[4] -= 0.1;
		}
		else if (tick > 3200 && tick < 4100) {
			for (size_t i = 1; i < 5; i++)
			{
				if (excavadora_animacion[i] < 0) excavadora_animacion[i] += 0.05;
			}
		}
		else if (tick > 4100){
			tick = 1;
			avanzar++;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(11-velocidad_animacion, animate, 1);
}

void graficado(GLMmodel * modelo, int texture){
	glBindTexture(GL_TEXTURE_2D, treeTextureAr[texture].texID);
	glmDraw(modelo, GLM_SMOOTH | GLM_TEXTURE);
}

void graficar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    vista =cameraX + sin(cameraAngleX);
    vistay= cameraY + sin(cameraAngleY);
    vistaz=cameraZ - cos(cameraAngleX);
	gluLookAt(cameraX, cameraY, cameraZ, vista,vistay ,vistaz, 0.0f, 1.0f, 0.0f);

	if(active_grilla) grilla();


	//glRotatef(ypoz, 0, 1, 0);

	glTranslatef(0,-4,0);



	////////Excavadora//////////
	glPushMatrix();
		glScalef(4,4,4);

		glPushMatrix();
			glTranslatef(-10 + excavadora_animacion[0], 0,0); //* <--
			graficado(excavadora11, 5+colorExcavadora);

			glPushMatrix();
				glRotatef(excavadora_animacion[1], 0,1,0);//* <--
				graficado(excavadora10, 5+colorExcavadora);
				graficado(excavadora8, 5+colorExcavadora);
				graficado(excavadora9, 2);

				glPushMatrix();
					glRotatef(excavadora_animacion[2], 0,0,1);//* <--
					graficado(excavadora6, 5+colorExcavadora);
					graficado(excavadora7, 5+colorExcavadora);
					graficado(excavadora5, 5+colorExcavadora);
					graficado(excavadora4, 5+colorExcavadora);
					graficado(excavadora3_2, 2);

					glPushMatrix();
						glTranslatef(5.490030, 3.75999,0);
						glRotatef(excavadora_animacion[3], 0,0,1);//* <--
						glutSolidCube(0.05);
						glTranslatef(-5.490030, -3.75999,0);
						graficado(excavadora3_1, 2);
						graficado(excavadora2, 5+colorExcavadora);

						glPushMatrix();
							glTranslatef(6.200006,1.15,0);
							glRotatef(excavadora_animacion[4], 0,0,1); //* <--
							glutSolidCube(0.05);
							glTranslatef(-6.200006,-1.15,0);
							graficado(excavadora1, 2);
						glPopMatrix();

					glPopMatrix();

				glPopMatrix();

			glPopMatrix();
		glPopMatrix();


	glPopMatrix();

    //graficado(terreno01, 3); //? Vias de tren
	graficado(terreno02, 4);

	glScalef(8,8,8);

	graficado(skybox, 1);

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

		case 'j':
			tempx-=l;
			break;
		case 'l':
			tempx+=l;
			break;
		case 'i':
			tempy+=l;
			break;
		case 'k':
			tempy-=l;
			break;
    }

	//printf("x: %f | y: %f\n",tempx, tempy);
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
	int l = 0.05;
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

    	if (cameraAngleY > 1.8) {
    	    cameraAngleY = 1.8;
    	}
		else if (cameraAngleY < -1.8) cameraAngleY = -1.8;

    	lastMouseX = x;
    	lastMouseY = y;
	}
}


void maximizeWindow() {
    HWND hwnd = GetForegroundWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

void buttonCallback(int id) {
    if (id == 1) {
		parar_excavadora = parar_excavadora ? false : true;
		boton_texto = !parar_excavadora ? "Parar" : "Continuar";
		boton->set_name(boton_texto);
    }
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	main_windows = glutCreateWindow("T3");
	//maximizeWindow();

	init();



	skybox = glmReadOBJ("modelos/skybox.obj");
	excavadora1=glmReadOBJ("modelos/Excavadora_01.obj");
	excavadora2=glmReadOBJ("modelos/Excavadora_02.obj");
	excavadora3_1=glmReadOBJ("modelos/Excavadora_3_1.obj");
	excavadora3_2=glmReadOBJ("modelos/Excavadora_3_2.obj");
	excavadora4=glmReadOBJ("modelos/Excavadora_04.obj");
	excavadora5=glmReadOBJ("modelos/Excavadora_05.obj");
	excavadora6=glmReadOBJ("modelos/Excavadora_06.obj");
	excavadora7=glmReadOBJ("modelos/Excavadora_07.obj");
	excavadora8=glmReadOBJ("modelos/Excavadora_08.obj");
	excavadora9=glmReadOBJ("modelos/Excavadora_09.obj");
	excavadora10=glmReadOBJ("modelos/Excavadora_10.obj");
	excavadora11=glmReadOBJ("modelos/Excavadora_11.obj");
	terreno01 = glmReadOBJ("modelos/terreno/terreno_01.obj");
	terreno02 = glmReadOBJ("modelos/terreno/terreno_02.obj");





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

	GLUI *glui = GLUI_Master.create_glui("T3");

	new GLUI_Checkbox(glui, "Grilla", &active_grilla);

	glui->set_main_gfx_window(glutGetWindow());

	GLUI_Panel * panel = new GLUI_Panel(glui, "Velocidad de Animacion");
	GLUI_Scrollbar * scrollbar = new GLUI_Scrollbar(panel, "Velocidad de Animacion", GLUI_SCROLL_HORIZONTAL, &velocidad_animacion);
	scrollbar->set_int_limits(1, 10);
	GLUI_StaticText * textLabel = new GLUI_StaticText(panel, "  1-------------10");

	GLUI_Listbox * listbox = new GLUI_Listbox(glui, "Seleccionar", &colorExcavadora);
	listbox->add_item(0, "Amarillo");
	listbox->add_item(1, "Verde");
	listbox->add_item(2, "Morado");

	boton = new GLUI_Button(glui, "Parar",1, buttonCallback);

	glui->set_main_gfx_window(glutGetWindow());
	glui->set_main_gfx_window(main_windows);
	GLUI_Master.set_glutIdleFunc(guiIdle);

	glutMainLoop();
	return 0;
}
