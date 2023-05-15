#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

//* Variables
GLUquadricObj *p = gluNewQuadric();
double windowHeight=800, windowWidth=600;
double alturaTrapecio = -0.081;
double rotate = 0, traX = 0, traY = 0;
bool toggleLuzAmbiental = false, toggleLuzPuntual = false;
float radioRueda = 0, radioBotones = 0, radioAntenaLv[] = {0,0,0}, radioRotateAntena = 0;
float radioSalto = 0, radioAllRotate = 0, radioTempSalto = 0.05, radioTempRotate = 2;

float dodecaedroRotacion[11] = {0};
float dodecaedroPath[20] = {0};
float dodecaedroSalto = 0, dodecaedroTempSalto = 0.05, dodecaedroVuelta = 0, dodecaedroTempVuelta = 10;
float temp = 0, aux;

static GLfloat v_cube[8][3] ={
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};
static GLubyte quadIndices[6][4] ={
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};
static GLfloat v_pyramid[5][3] ={
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};
static GLubyte p_Indices[4][3] ={
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};
static GLubyte PquadIndices[1][4] ={
    {0, 3, 2, 1}
};

float focoLuz = 1;

GLfloat PosLuzDireccional[4] = {1.0, 1.0, 1.0, 0.0};
GLfloat PosLuzPuntual[4] = {0.7, 2.5, 14.8, 1.0};
GLfloat spotDirection[3] = {0.3, -1, -0.8};
GLfloat LuzAmbiente[4] = {0.7, 0.7, 0.7, 0.0};
GLfloat LuzAmbiente2[4] = {0.02, 0.02, 0.02, 1.0};
GLfloat LuzEspecular[4] = {1, 1, 1, 1.0};
GLfloat LuzEspecularDirec[4] = {0.1, 0.1, 0.1, 1.0};
GLfloat LuzDifusa[4] = {1, 1, 1, 1.0};
GLfloat LuzDifusaDirec[4] = {0.1, 0.1, 0.1, 1.0};
GLfloat Material[4] = {0.5, 0.5, 0.5, 1.0};

//* Métodos complementarios
void drawCube(){
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}
void drawpyramid(){
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}
void polygon(){
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    //glVertex2f(0,0);

    glEnd();
}
void polygonLine(){
    glBegin(GL_LINE_STRIP);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
   glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    glVertex2f(0,0);

    glEnd();
}
void gluPrismaCuadrangular(float largo, float alto, float ancho){
    glBegin(GL_QUADS);
    // Cara frontal
    glVertex3f(-largo, -alto, ancho);
    glVertex3f(largo, -alto, ancho);
    glVertex3f(largo, alto, ancho);
    glVertex3f(-largo, alto, ancho);

    // Cara trasera
    glVertex3f(-largo, -alto, -ancho);
    glVertex3f(largo, -alto, -ancho);
    glVertex3f(largo, alto, -ancho);
    glVertex3f(-largo, alto, -ancho);

    // Cara izquierda
    glVertex3f(-largo, -alto, ancho);
    glVertex3f(-largo, alto, ancho);
    glVertex3f(-largo, alto, -ancho);
    glVertex3f(-largo, -alto, -ancho);

    // Cara derecha
    glVertex3f(largo, -alto, ancho);
    glVertex3f(largo, alto, ancho);
    glVertex3f(largo, alto, -ancho);
    glVertex3f(largo, -alto, -ancho);

    // Cara superior
    glVertex3f(-largo, alto, ancho);
    glVertex3f(largo, alto, ancho);
    glVertex3f(largo, alto, -ancho);
    glVertex3f(-largo, alto, -ancho);

    // Cara inferior
    glVertex3f(-largo, -alto, ancho);
    glVertex3f(largo, -alto, ancho);
    glVertex3f(largo, -alto, -ancho);
    glVertex3f(-largo, -alto, -ancho);

    glEnd();

}
void gluRectangulo(float largo, float alto, float ancho){
    glBegin(GL_QUADS);
        glVertex3f(-largo, -alto, ancho);
        glVertex3f(largo, -alto, ancho);
        glVertex3f(largo, alto, ancho);
        glVertex3f(-largo, alto, ancho);
    glEnd();
}
void gluCilindroTapado(float radius, float height, float slices, int stacks){
    gluQuadricDrawStyle(p, GLU_FILL);
    gluQuadricNormals(p, GLU_SMOOTH);
    gluDisk(p, 0.0f, radius, slices, 1);
    gluCylinder(p, radius, radius, height, slices, stacks);

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(p, 0.0f, radius, slices, 1);
    glPopMatrix();

    gluDeleteQuadric(p);
}
void gluPentagonoDelineado(float size) {
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.8f, 0.6f);
        for (int i = 0; i < 5; i++) {
            float x = 0.5f * size * sin(i * 2.0f * M_PI / 5.0f);
            float y = 0.5f * size * cos(i * 2.0f * M_PI / 5.0f);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < 5; i++) {
            float x = 0.5f * size * sin(i * 2.0f * M_PI / 5.0f);
            float y = 0.5f * size * cos(i * 2.0f * M_PI / 5.0f);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

}

//* Elementos habitación | Entorno

void cupboard()
{
    //Cupboard/Almari ************************************************************
    glPushMatrix();
        glTranslatef(-6.93, -0.25 , 5.17);

        glPushMatrix();
        glRotatef(73, 0, 1, 0);
            //cupboard
            glColor3f(0.5,0.4,0.2);
            glPushMatrix();
            glTranslatef(4,0,4.4);
            //glRotatef(22, 0,0,1);
            glScalef(0.5, 1, 0.5);
            drawCube();
            glPopMatrix();

            //cupboard's 1st vertical stripline
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4,1,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.5, 0.01, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's 2nd vertical stripline
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4,0.5,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.5, 0.01, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's last stripline
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4,0,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.5, 0.01, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's lst horizontal stripline
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(5.5,0,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.01, 1, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's right side horizontal stripline
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4.75,1,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.01, 0.67, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's left side horizontal stripline
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4,0,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.01, 1, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's handle right
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(5,1.4,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.02, 0.18, 0.0001);
            drawCube();
            glPopMatrix();

            //cupboard's handle left
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4.5,1.4,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.02, 0.18, 0.01);
            drawCube();
            glPopMatrix();

            //cupboard's drawer's 1st handle
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4.5,0.7,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.16, 0.02, 0.01);
            drawCube();
            glPopMatrix();

            //cupboard's drawer's 2nd handle
            glColor3f(0.3,0.2,0.1);
            glPushMatrix();
            glTranslatef(4.5,0.25,5.9);
            //glRotatef(22, 0,0,1);
            glScalef(0.16, 0.02, 0.01);
            drawCube();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}
void lamp()
{
    //Lamp *****************************************
    glPushMatrix();
        //lamp base
        glColor3f(0.4,0.5,0);
        glPushMatrix();
        glTranslatef(.6,0.5,9.1);
        glScalef(0.07, 0.02, 0.07);
        drawCube();
        glPopMatrix();

        //lamp stand
        glColor3f(0.7,0.7,0.7);
        glPushMatrix();
        glTranslatef(.7,0.35,9.2);
        glScalef(0.01, 0.2, 0.01);
        drawCube();
        glPopMatrix();

        //lamp shade
        glColor3f(1,0.7, 0);
        glPushMatrix();
        glTranslatef(.7,0.9,9.2);
        glScalef(0.08, 0.09, 0.08);
        drawCube();
        glPopMatrix();
    glPopMatrix();

}
void bedsideTable()
{
    //bedside drawer *************************************

      //side drawer
    glPushMatrix();
        glColor3f(0.2,0.1,0.1); //0.5,0.2,0.2
        glPushMatrix();
        glTranslatef(0.5,-0.1,8.7); //0.5,-0.1,9
        //glRotatef(22, 0,0,1);
        glScalef(0.12, 0.2, 0.23);
        drawCube();
        glPopMatrix();
        //side drawer's drawer
        glColor3f(0.3,0.2,0.2);
        glPushMatrix();
        glTranslatef(0.88,0,8.8);
        //glRotatef(22, 0,0,1);
        glScalef(0.0001, 0.11, 0.18);
        drawCube();
        glPopMatrix();
        //side drawer's knob
        glColor3f(0.3, 0.1, 0.0);
        glPushMatrix();
        glTranslatef(0.9,0.1,9);
        //glRotatef(22, 0,0,1);
        glScalef(0.0001, 0.04, 0.04);
        drawCube();
        glPopMatrix();

        lamp();

    glPopMatrix();
}
void bed()
{
    glPushMatrix();
        //bed headboard
        glColor3f(0.5,0.2,0.2);
        glPushMatrix();
        glScalef(0.1, 0.5, 0.9);
        glTranslatef(-2,-0.5,6);
        drawCube();
        glPopMatrix();

        //bed body
        glColor3f(0.824, 0.706, 0.549);
        glPushMatrix();
        glScalef(1, 0.2, 0.9); //1, 0.2, 0.9
        glTranslatef(0,-0.5,6.2);
        drawCube();
        glPopMatrix();

        //pillow right far
        glColor3f(0.627, 0.322, 0.176);
        glPushMatrix();
        glTranslatef(0.5,0.5,6);
        glRotatef(20, 0,0,1);
        glScalef(0.1, 0.15, 0.28);
        drawCube();
        glPopMatrix();

        //pillow left near
        glColor3f(0.627, 0.322, 0.176);
        glPushMatrix();
        glTranslatef(0.5,0.5,7.2);
        glRotatef(22, 0,0,1);
        glScalef(0.1, 0.15, 0.28);
        drawCube();
        glPopMatrix();

        //blanket
        glColor3f(0.627, 0.322, 0.176);
        glPushMatrix();
        glTranslatef(1.4,0.45,5.5);
        //glRotatef(22, 0,0,1);
        glScalef(0.5, 0.05, 0.95);
        drawCube();
        glPopMatrix();

        //blanket side left part
        glColor3f(0.627, 0.322, 0.176);
        glPushMatrix();
        glTranslatef(1.4,-0.3,8.15);
        //glRotatef(22, 0,0,1);
        glScalef(0.5, 0.25, 0.05);
        drawCube();
        glPopMatrix();
    glPopMatrix();

}
void base()
{
    glPushMatrix();
        // right wall
        glColor3f(1, 0.8, 0.5);
        glPushMatrix();
        glTranslatef(-1.5,-1,.5);
        glScalef(5, 2, 0.1);
        drawCube();
        glPopMatrix();

        // left wall
        glColor3f(1, 0.8, 0.7);
        glPushMatrix();
        glTranslatef(-4.5,-1,0);
        glScalef(1, 2, 5);
        drawCube();
        glPopMatrix();

        //ceiling
        glColor3f(1.0, 0.9, 0.8);
        glPushMatrix();
        //glScalef(5, 0.1, 7);
        glTranslatef(-2,5.1,0);
        glScalef(5, 0.1, 7);
        drawCube();
        glPopMatrix();

        // carpet
        glColor3f(0.8, 0.8, 0.4);
        glPushMatrix();
        //glScalef(5, 0.1, 7);
        glTranslatef(3,-0.2,7);
        glScalef(1.3, 0.01, 1.7);
        drawCube();
        glPopMatrix();
    glPopMatrix();
}
void wallshelf()
{   glPushMatrix();
        glTranslatef(1.36,1.23,0);
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(1.5,2.7,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.4, 0.03, 0.2);
        drawCube();
        glPopMatrix();

        //wall shelf two
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(1,2.3,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.4, 0.03, 0.2);
        drawCube();
        glPopMatrix();

        //wall shelf three
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(0.5,1.9,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.4, 0.03, 0.2);
        drawCube();
        glPopMatrix();

        //wall shelf four
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(1,1.5,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.4, 0.03, 0.2);
        drawCube();
        glPopMatrix();

        //wall shelf five
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(1.5,1.1,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.4, 0.03, 0.2);
        drawCube();
        glPopMatrix();

        //showpiece on the bottom shelf from left 1
        glColor3f(0.698, 0.133, 0.133);
        glPushMatrix();
        glTranslatef(1.5,1.2,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.04, 0.06, 0.2);
        drawCube();
        glPopMatrix();

        //showpiece on the bottom shelf from left 2
        glColor3f(0.729, 0.333, 0.827);
        glPushMatrix();
        glTranslatef(2,1.2,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.04, 0.06, 0.2);
        drawCube();
        glPopMatrix();

        //showpiece on the bottom shelf from left 3 lower portion
        glColor3f(0.098, 0.098, 0.439);
        glPushMatrix();
        glTranslatef(2.5,1.2,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.04, 0.06, 0.2);
        drawCube();
        glPopMatrix();

        //showpiece on the bottom shelf from left 3 upper portion
        glColor3f(.529, 0.808, 0.980);
        glPushMatrix();
        glTranslatef(2.51,1.35,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.01, 0.05, 0.2);
        drawCube();
        glPopMatrix();

        //showpiece on the top shelf  left 2
        glColor3f(0.502, 0.502, 0.000);
        glPushMatrix();
        glTranslatef(2.5,2.71,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.05, 0.16, 0.01);
        drawCube();
        glPopMatrix();

        //showpiece on the top shelf left 1
        glColor3f(0,0,.9);
        glPushMatrix();
        glTranslatef(1.8,2.71,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.16, 0.1, 0.01);
        drawCube();
        glPopMatrix();

        //showpiece on 2nd shelf
        glColor3f(.416, 0.353, 0.804);
        glPushMatrix();
        glTranslatef(1.3,2.4,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.16, 0.08, 0.01);
        drawCube();
        glPopMatrix();

        //showpiece on 3rd shelf left 1
        glColor3f(0.863, 0.078, 0.235);
        glPushMatrix();
        glTranslatef(0.4,1.9,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.05, 0.16, 0.01);
        drawCube();
        glPopMatrix();

        //showpiece on 3rd shelf left 2
        glColor3f(0.780, 0.082, 0.522);
        glPushMatrix();
        glTranslatef(0.7,1.9,3);
        //glRotatef(22, 0,0,1);
        glScalef(0.05, 0.12, 0.01);
        drawCube();
        glPopMatrix();

        //showpiece on 3rd shelf left 3
        glColor3f(0.600, 0.196, 0.800);
        glPushMatrix();
        glTranslatef(1,1.9,3);
        glScalef(0.05, 0.09, 0.01);
        drawCube();
        glPopMatrix();

        //showpiece on 4th shelf
        glColor3f(0.282, 0.239, 0.545);
        glPushMatrix();
        glTranslatef(1.8,1.5,3);
        glScalef(0.2, 0.1, 0.2);
        drawpyramid();
        glPopMatrix();

        //showpiece on 4th shelf
        glColor3f(0.251, 0.878, 0.816);
        glPushMatrix();
        glTranslatef(1.4,1.5,3);
        glScalef(0.15, 0.1, 0.2);
        drawpyramid();
        glPopMatrix();


    glPopMatrix();

        // floor
        glPushMatrix();
            glColor3f(0.8, 0.8, 0.6);
            glScalef(5, 0.1, 7);
            glTranslatef(-1,-5,0); //-1,-5,.5
            //glScalef(5, 0.1, 7);
            drawCube();
        glPopMatrix();
}
void table(float WIDTH, float HEIGHT, float LENGTH){
    glPushMatrix();

        glTranslatef(5.2,0,10.6);
        glRotatef(20, 0,1,0);
        glPushMatrix();
            glColor3f(0.45f, 0.38f, 0.05f);
            glTranslatef(0.0f, HEIGHT/2, 0.0f);
            glScalef(WIDTH, HEIGHT/4, LENGTH);
            glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(-(WIDTH/2-0.1), 0.0f, -(LENGTH/2-0.1));
            glScalef(0.2f, HEIGHT-0.1, 0.2f);
            glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(WIDTH/2-0.1, 0.0f, -(LENGTH/2-0.1));
            glScalef(0.2f, HEIGHT-0.1, 0.2f);
            glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(-(WIDTH/2-0.1), 0.0f, LENGTH/2-0.1);
            glScalef(0.2f, HEIGHT-0.1, 0.2f);
            glutSolidCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(WIDTH/2-0.1, 0.0f, LENGTH/2-0.1);
            glScalef(0.2f, HEIGHT-0.1, 0.2f);
            glutSolidCube(1.0f);
        glPopMatrix();
    glPopMatrix();

}
void foco(){
    glPushMatrix();
        glColor3f(focoLuz,focoLuz,focoLuz);
        glTranslatef (5, 5, 8);
        glScalef(0.2, 0.2, 0.2);
        glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}


//* Modelos jerarquicos

void radioGrafico(){
    glPushMatrix();//* Nivel 1
        glScalef(0.1,0.1,0.1);
        glTranslatef(50,15.5+radioSalto,120);
        glRotatef(45,0,1,0);
        glRotatef(radioAllRotate,0,1,0);
        glColor3f(0.4,0.4,0.4);
        gluPrismaCuadrangular(5,3,2);

        glPushMatrix(); //Decorativo, no se mueve
            glTranslatef(-2.18,0,0);
            glColor3f(0.2,0.2,0.2);
            gluRectangulo(2.8,3,2.05);
        glPopMatrix();

        glPushMatrix(); //Decorativo, no se mueve
            glTranslatef(2.2,0,0);
            glColor3f(0.28,0.28,0.28);
            gluRectangulo(2.8,3,2.04);
        glPopMatrix();

        glPushMatrix(); //Decorativo, no se mueve. PANTALLA
            glTranslatef(2.6,1.4,0);
            glColor3f(0.28,0.40,0.28);
            gluRectangulo(1.5,1,2.08);
        glPopMatrix();

        glColor3f(0.2,0.2,0.2); //Aplicar color a los botones

        for (size_t i = 0; i < 6; i++) //Botones
        {
            glPushMatrix();
                if(i < 3) glTranslatef(1.2 + (i + 0.5),-0.5,1.5+radioBotones);
                else      glTranslatef(1.2 + ((i-3) + 0.5),-2,1.5+radioBotones);
                gluCilindroTapado(0.5,1,20,20);
            glPopMatrix();
        }

        glPushMatrix(); // Rueda
            glRotatef(90,0,1,0);
            glColor3f(0.35,0.35,0.35);
            glTranslatef(0,0,5);
            glRotatef(radioRueda,0,0,1);
            gluCilindroTapado(1.5,1,7,7);

            glTranslatef(0,0,3);
            glColor3f(0,0,0);
            gluRectangulo(0.05,1,-1.95);
        glPopMatrix();

        glPushMatrix(); //Antena Nivel 2

            glColor3f(0.5,0.5,0.5);
            glTranslatef(3.5,3.09,0);
            glRotatef(radioRotateAntena,0,0,1);
            glRotatef(90,1,0,0);

            glutSolidSphere(0.2,20,20);
            glTranslatef(0,0,-2.19);
            gluCilindroTapado(0.4,2.2,40,40);

            glPushMatrix(); //* Nivel 3
                glColor3f(0.45,0.45,0.45);
                glTranslatef(0,0,-2.2+radioAntenaLv[0]);
                gluCilindroTapado(0.3,2.2,40,40);

                glPushMatrix(); //* Nivel 4
                    glColor3f(0.5,0.5,0.5);
                    glTranslatef(0,0,-2.2+radioAntenaLv[1]);
                    gluCilindroTapado(0.2,2.2,40,40);

                    glPushMatrix(); //* Nivel 5
                        glColor3f(0.4,0.4,0.4);
                        glTranslatef(0,0,-2.2+radioAntenaLv[2]);
                        gluCilindroTapado(0.1,2.2,40,40);
                        glColor3f(0.3,0.3,0.3);
                        glutSolidSphere(0.15,50,50);
                    glPopMatrix();

                glPopMatrix();

            glPopMatrix();

        glPopMatrix();


    glPopMatrix();
}

void dodecaedroDesplegableGrafico(){
    glPushMatrix(); //*Nivel 1
        glTranslatef(6.26,1.26 + dodecaedroSalto,10.95); // Y 1.26  X 6.14     y 5.14 X 2.26
        glRotatef(dodecaedroVuelta,0,1,0); // MOVE
        glRotatef(90,1,0,0); // 1 X

        glRotatef(88.5,0,0,1);
        gluPentagonoDelineado(0.5);

        //*Nivel 2
        glPushMatrix(); //*Completed
            glTranslatef(0.12,0.16,0);
            glRotatef(-35.5,0,0,1);
            glRotatef(-dodecaedroRotacion[0],1,0,0); //72
            gluSphere(p,0.005,20,20);
            glTranslatef(0,0.21,0);
            gluPentagonoDelineado(0.5);
        glPopMatrix();

        glPushMatrix(); //*Completed
            glTranslatef(-0.19,-0.07,0);
            glRotatef(0,0,1,0);
            glRotatef(-dodecaedroRotacion[0],0,1,0);

            gluSphere(p,0.005,20,20);
            glRotatef(-dodecaedroPath[5],1,0,0); //-15
            glRotatef(dodecaedroPath[6],0,0,1); //-9.5
            glTranslatef(-0.20,-0.05,0);
            glRotatef(180,1,0,0);
            gluPentagonoDelineado(0.5);
        glPopMatrix();

        glPushMatrix(); //*Completed
            glTranslatef(0,-0.2,0);
            glRotatef(-36.5,0,0,1);
            glRotatef(dodecaedroRotacion[0],1,0,0);

            gluSphere(p,0.005,20,20);
            glRotatef(-dodecaedroPath[3],0,1,0); //-35
            glRotatef(dodecaedroPath[4],0,0,1); //-19
            glTranslatef(0.12,-0.17,0);
            gluPentagonoDelineado(0.5);
        glPopMatrix();

        glPushMatrix(); //*Completed
            glTranslatef(0.2,-0.06,0);
            glRotatef(34.5,0,0,1);
            glRotatef(dodecaedroRotacion[0],1,0,0);

            gluSphere(p,0.005,20,20);
            glRotatef(-dodecaedroPath[1],0,1,0); //-30.5
            glRotatef(dodecaedroPath[2],0,0,1); //-17.5
            glTranslatef(0.12,-0.16,0);
            gluPentagonoDelineado(0.5);
        glPopMatrix();

        glPushMatrix(); //* Completed
            glTranslatef(-0.13,0.15,0);
            glRotatef(35.5,0,0,1);
            glRotatef(-dodecaedroRotacion[0],1,0,0);
            gluSphere(p,0.005,20,20);
            glTranslatef(0.01,0.21,0);
            gluPentagonoDelineado(0.5);

            //* Nivel 3
            glPushMatrix(); //*Completed
                glTranslatef(-0.12,0.16,0);
                glRotatef(-35.5,0,0,1);
                glRotatef(-dodecaedroRotacion[1],1,0,0);

                gluSphere(p,0.005,20,20);
                glRotatef(dodecaedroPath[7],0,1,0); //-59
                glRotatef(dodecaedroPath[8],0,0,1); //-25.5
                glTranslatef(-0.2,0.06,0);
                gluPentagonoDelineado(0.5);

                //* Nivel 4
                glPushMatrix(); //*Completed
                    glTranslatef(-0.13,0.15,0);
                    glRotatef(36,0,0,1);
                    glRotatef(-dodecaedroRotacion[0],1,0,0);
                    gluSphere(p,0.005,20,20);
                    glTranslatef(0.01,0.21,0);
                    gluPentagonoDelineado(0.5);

                    //* Nivel 5
                    glPushMatrix();//*Completed
                        glTranslatef(0.2,-0.05,0);
                        glRotatef(36.5,0,0,1);
                        glRotatef(dodecaedroRotacion[2],1,0,0);

                        gluSphere(p,0.005,20,20);
                        glRotatef(-dodecaedroPath[9],0,1,0); // 34.5
                        glRotatef(dodecaedroPath[10],0,0,1); // -20
                        glTranslatef(0.1,-0.17,0);
                        gluPentagonoDelineado(0.5);
                    glPopMatrix();

                    glPushMatrix();//*Completed
                        glTranslatef(0.1,0.18,0);
                        glRotatef(34,0,0,1);
                        glRotatef(-dodecaedroRotacion[3],1,0,0);

                        gluSphere(p,0.005,20,20);
                        glRotatef(-dodecaedroPath[11],0,1,0); //57
                        glRotatef(-dodecaedroPath[12],0,0,1); //-13
                        glTranslatef(0.2,0.05,0);
                        gluPentagonoDelineado(0.5);
                    glPopMatrix();

                    glPushMatrix();//*Completed
                        glTranslatef(-0.12,0.16,0);
                        glRotatef(36,0,0,1);
                        glRotatef(-dodecaedroRotacion[4],1,0,0);

                        gluSphere(p,0.005,20,20);
                        glRotatef(-dodecaedroPath[13],0,1,0); // -2
                        glRotatef(dodecaedroPath[14],0,0,1); // 0.5
                        glTranslatef(0,0.21,0);
                        gluPentagonoDelineado(0.5);
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef(-0.19,-0.05,0);
                        glRotatef(-36.5,0,0,1);
                        glRotatef(dodecaedroRotacion[0],1,0,0);

                        gluSphere(p,0.005,20,20);
                        glRotatef(dodecaedroPath[15],0,1,0); // -31
                        glRotatef(-dodecaedroPath[16],0,0,1); // 24
                        glTranslatef(-0.12,-0.17,0);
                        gluPentagonoDelineado(0.5);
                    glPopMatrix();

                glPopMatrix();

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

//* Metodos del OpenGL

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60,1,1,100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(7,2,15,  0,0,0,  0,1,0);

    //* Iluminación

    glEnable(GL_LIGHTING);

    //? Luz puntual
    if(toggleLuzPuntual) glEnable(GL_LIGHT2);
    else glDisable(GL_LIGHT2);

    glLightfv(GL_LIGHT2, GL_POSITION, PosLuzPuntual);

    glLightfv(GL_LIGHT2, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT2, GL_AMBIENT, LuzAmbiente2);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90); //angulo
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.05);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 6.5);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.35);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);



    //? Luz ambiental
    if(toggleLuzAmbiental) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_POSITION, PosLuzDireccional);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecularDirec);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusaDirec);


    //? Material Config
    glMaterialfv(GL_FRONT, GL_DIFFUSE, LuzDifusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, LuzEspecular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, LuzAmbiente);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_COLOR_INDEXES);



    glRotatef(3, 1,0,0);

    //?Entorno
    base();
    bedsideTable();
    bed();
    cupboard();
    //lamp();
    wallshelf();
    foco();
    table(3,2,3);

    //?Modelos jerarquicos
    radioGrafico();
    dodecaedroDesplegableGrafico();

    glutSwapBuffers();
}

void timer(int i){
    temp+=0.3;
    //* Radio Animación Bucle
    {
        if(radioRueda > 360) radioRueda = 0; radioRueda+=0.5;
        if(radioBotones < -0.32) radioBotones = 0; radioBotones-=0.005;

        if(i < 192){
            if(radioRotateAntena < 90){
                radioRotateAntena+=0.5;
                for (size_t i = 0; i < 3; i++) if(radioAntenaLv[i] < 1.83) radioAntenaLv[i] +=0.02;
            }
        }
        else if(i > 192 && i < 400){
            radioSalto+=radioTempSalto;
            radioAllRotate+=radioTempRotate;
            if(radioAllRotate > 360) radioTempRotate = 0;
            if(radioSalto > 4) radioTempSalto*=-1;
            else if(radioSalto < 0) radioTempSalto = 0;
        }
        else if (i > 400 && i < 605){
            if(radioRotateAntena > 0){
                radioRotateAntena-=0.5;
                for (size_t i = 0; i < 3; i++) if(radioAntenaLv[i] > 0) radioAntenaLv[i] -=0.02;
            }
        }
        else if(i > 605) {
            i = 0;
            radioTempRotate = 2;
            radioTempSalto = 0.05;
            radioAllRotate = 0;
            dodecaedroTempSalto = 0.05;
            dodecaedroTempVuelta = 10;
            dodecaedroVuelta = 0;
        }
    }

    //* Dodecaedro Animación Bucle
    {
        if(i > 100 && i < 277){ //Armado
            if(dodecaedroRotacion[0] < 60) dodecaedroRotacion[0]   += 0.5;
            if(dodecaedroRotacion[1] < 40) dodecaedroRotacion[1]   += 0.5;
            if(dodecaedroRotacion[2] < 55.5) dodecaedroRotacion[2] += 0.5;
            if(dodecaedroRotacion[3] < 29.5) dodecaedroRotacion[3] += 0.5;
            if(dodecaedroRotacion[4] < 65) dodecaedroRotacion[4]   += 0.5;


            if(dodecaedroPath[1] > -30.5 )  dodecaedroPath[1]  -=0.5;
            if(dodecaedroPath[2] > -17.5 )  dodecaedroPath[2]  -=0.5;
            if(dodecaedroPath[3] > -35   )  dodecaedroPath[3]  -=0.5;
            if(dodecaedroPath[4] > -19   )  dodecaedroPath[4]  -=0.5;
            if(dodecaedroPath[5] > -15   )  dodecaedroPath[5]  -=0.5;
            if(dodecaedroPath[6] > -9.5  )  dodecaedroPath[6]  -=0.5;
            if(dodecaedroPath[7] > -59   )  dodecaedroPath[7]  -=0.5;
            if(dodecaedroPath[8] > -25.5 )  dodecaedroPath[8]  -=0.5;
            if(dodecaedroPath[9] > -34.5 )  dodecaedroPath[9]  -=0.5;
            if(dodecaedroPath[10] > -20  )  dodecaedroPath[10] -=0.5;
            if(dodecaedroPath[11] > -57  )  dodecaedroPath[11] -=0.5;
            if(dodecaedroPath[12] > -13  )  dodecaedroPath[12] -=0.5;
            if(dodecaedroPath[13] > -2   )  dodecaedroPath[13] -=0.5;
            if(dodecaedroPath[14] > -0.5 )  dodecaedroPath[14] -=0.5;
            if(dodecaedroPath[15] > -31  )  dodecaedroPath[15] -=0.5;
            if(dodecaedroPath[16] > -24  )  dodecaedroPath[16] -=0.5;
        }
        else if (i > 277 && i < 342){
            dodecaedroSalto+=dodecaedroTempSalto;
            dodecaedroVuelta+=dodecaedroTempVuelta;
            if(dodecaedroVuelta > 360) dodecaedroTempVuelta = 0;
            if(dodecaedroSalto > 1) dodecaedroTempSalto*=-1;
            else if(dodecaedroSalto < 0) dodecaedroTempSalto = 0;
        }
        else if(i > 342 && i < 605){
            for (size_t i = 0; i < 5; i++) if(dodecaedroRotacion[i] > 0) dodecaedroRotacion[i] -= 0.3;
            for (size_t i = 0; i < 17; i++) if(dodecaedroPath[i] < 0) dodecaedroPath[i] +=0.3;
        }
        else if (i > 605){
        }
    }

    graficar();
    glutTimerFunc(10,timer,i+1);

    //printf("Tick: %i\n", i);
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: exit(1);
    case 'o': {
        toggleLuzAmbiental = (toggleLuzAmbiental == true) ? false : true;
        focoLuz = (toggleLuzAmbiental == true) ? 1 : 0.5;
        break;
    }

    case 'p': {toggleLuzPuntual = (toggleLuzPuntual == true) ? false : true; break;}
    }
    glutPostRedisplay();
}

void special(int key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_UP:
        traY+=0.01;
        break;

    case GLUT_KEY_DOWN:
        traY-=0.01;
        break;

    case GLUT_KEY_RIGHT:
        traX-=0.01;
        break;

    case GLUT_KEY_LEFT:
        traX+=0.01;
        break;

    case GLUT_KEY_PAGE_UP:
        rotate+=0.5;
        break;

    case GLUT_KEY_PAGE_DOWN:
        rotate-=0.5;
        break;

    case GLUT_KEY_F2:
        dodecaedroPath[0]+=0.5;
        break;

    case GLUT_KEY_F1:
        dodecaedroPath[0]-=0.5;
        break;

    case GLUT_KEY_F3:
        aux+=0.5;
        break;

    case GLUT_KEY_F4:
        aux-=0.5;
        break;

    default:
        break;
    }
    //PosLuzPuntual[1] += traX;
    //PosLuzPuntual[2] += traY;

    //spotDirection[1] += traX - PosLuzPuntual[1];
    //spotDirection[2] += traY - PosLuzPuntual[1];
    //printf("rotate: %f | X: %f | Y: %f | dodePath: %f | aux: %f\n",rotate,traX,traY, dodecaedroPath[0], aux);
    graficar();
}

int main (int argc, char **argv)
{
    printf("Presionar la tecla 'o' para activar y desactivar la luz direccional\n");
    printf("Presionar la tecla 'P' para activar y desactivar la luz puntual");


    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Radio y dodecaedro desplegable");

    glEnable(GL_NORMALIZE);
    glEnable( GL_DEPTH_TEST );
    glutDisplayFunc(graficar);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(special);
    glutTimerFunc(10, timer, 1);
    glutMainLoop();

    return 0;
}
