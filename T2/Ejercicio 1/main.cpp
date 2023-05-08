#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

//Variables
GLUquadric *p = gluNewQuadric();
bool toggleEjes = false;
float spotX = 0;
float spotY = 0;
float spotZ = 0;

//* Variables de animación
//? change: [0] - Saludo | [1] - OK
float change = 0.5;
float rotacionSaludo = 0;
float rotacionOK = 0;
float dedoRotate[] = {0,0,0};

GLfloat PosLuz[4] = {5.0, 5.0, 5.0, 1.0};
GLfloat spotDirection[] = {-1.0 + spotX - PosLuz[0], -1.0 +spotY - PosLuz[1], -7.0, 0.0};

GLfloat LuzAmbiente[4] = {0.4, 0.4, 0.4, 1.0};
GLfloat LuzEspecular[4] = {1, 1, 1, 1.0};
GLfloat LuzDifusa[4] = {0.1, 0.1, 0.1, 1.0};
GLfloat Material[4] = {0.5, 0.5, 0.5, 1.0};

void inicializar()
{
    glClearColor(0,0,0,0.0);
    glEnable(GL_DEPTH_TEST);
    gluQuadricDrawStyle(p,GLU_LINE);

}

void graficarEjes()
{
  glColor3f(0,0,0);
  glBegin(GL_LINES);
      glColor3f(1,0,0);
      glVertex3f(0,0,0);
      glVertex3f(50,0,0);

      glColor3f(0,1,0);
      glVertex3f(0,0,0);
      glVertex3f(0,50,0);

      glColor3f(0,0,1);
      glVertex3f(0,0,0);
      glVertex3f(0,0,50);
  glEnd();
  
}

void graficar()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(20,20,20, 0,0,0, 0,1,0);

  //Iluminado
    {
    spotDirection[0] = -1.0 + spotX - PosLuz[0];
    spotDirection[1] = -1.0 + spotY - PosLuz[1];


    glEnable (GL_LIGHTING);
    glMaterialfv (GL_FRONT, GL_SPECULAR, LuzEspecular);
    glMaterialfv (GL_FRONT, GL_AMBIENT, LuzAmbiente);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, LuzDifusa);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);

    glLightfv(GL_LIGHT0, GL_POSITION, PosLuz);

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30 + spotZ); //angulo
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.2);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.15);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_COLOR_INDEXES);
    }


  if(toggleEjes) graficarEjes();

  glTranslatef(0,-16,0);
  gluQuadricDrawStyle(p, GLU_FILL);
  /*Nivel 1*/
  glPushMatrix();

    glColor3f(0.2f,0.2f,0.2f);
    glRotatef(rotacionSaludo,1,1,1);
    glutSolidSphere(1.5, 20,20); //*Codo
    glTranslatef(0,1.55,0);
    glRotatef(-90,1,0,0);
    gluCylinder(p, 3.5,3.5,10,20,20); //*Brazo
    glColor3f(0.3f,0.3f,0.3f);

    /*Nivel 2*/
    glPushMatrix();
      glRotatef(45,0,0,1);
      glScalef(1,0.3,1);
      glTranslatef(0,0,14);
      glRotatef(rotacionOK,0,1,0);
      glutSolidSphere(4.5, 80,80); //*Palma



      /*Nivel 3 -- Pulgar*/
      glPushMatrix();

        glColor3f(0.2f,0.2f,0.2f);
        glRotatef(-65,0,1,0);
        glTranslatef(0,0,4.3);
        glRotatef(dedoRotate[0], 1,0,0);
        glutSolidSphere(0.5,20,20);
        glTranslatef(0,0,0.2);
        glColor3f(0.3f,0.3f,0.3f);
        gluCylinder(p, 1,1,2,20,20);

        /*Nivel 4*/
        glPushMatrix();
          glColor3f(0.2f,0.2f,0.2f);
          glTranslatef(0,0,2.01f);
          glRotatef(dedoRotate[1], 1,0,0);
          glutSolidSphere(0.5,20,20);
          glTranslatef(0,0,0.5);
          glColor3f(0.3f,0.3f,0.3f);
          gluCylinder(p, 1,1,2.5,20,20);

        glPopMatrix();
            
      glPopMatrix();
      





      /*Nivel 3 -- Indice*/
      glPushMatrix();

        glColor3f(0.2f,0.2f,0.2f);
        glTranslatef(-2,0,3.9f);
        glRotatef(dedoRotate[0], 1,0,0);
        glutSolidSphere(0.5,20,20);
        glTranslatef(0,0,0.2);
        glColor3f(0.3f,0.3f,0.3f);
        gluCylinder(p, 1,1,2.5,20,20);

        /*Nivel 4*/
        glPushMatrix();
          glColor3f(0.2f,0.2f,0.2f);
          glTranslatef(0,0,2.8f);
          glRotatef(dedoRotate[1], 1,0,0);
          glutSolidSphere(0.5,20,20);
          glTranslatef(0,0,0.5);
          glColor3f(0.3f,0.3f,0.3f);
          gluCylinder(p, 1,1,2.5,20,20);

          /*Nivel 5*/
          glPushMatrix();
            glColor3f(0.2f,0.2f,0.2f);
            glTranslatef(0,0,2.60f);
            glRotatef(dedoRotate[2], 1,0,0);
            glutSolidSphere(0.5,20,20);
            glTranslatef(0,0,0.5);
            glColor3f(0.3f,0.3f,0.3f);
            gluCylinder(p, 1,1,1.7,20,20);
          glPopMatrix();

        glPopMatrix();  
            
      glPopMatrix();





      /*Nivel 3 -- Dedo medio*/
      glPushMatrix();
      
        glColor3f(0.2f,0.2f,0.2f);
        glRotatef(5,0,1,0);
        glTranslatef(-0.2,0,3.9f);
        glRotatef(dedoRotate[0], 1,0,0);
        glutSolidSphere(0.5,20,20);
        glTranslatef(0,0,0.2);
        glColor3f(0.3f,0.3f,0.3f);
        gluCylinder(p, 1,1,2.5,20,20);

        /*Nivel 4*/
        glPushMatrix();
          glColor3f(0.2f,0.2f,0.2f);
          glTranslatef(0,0,2.8f);
          glRotatef(dedoRotate[1], 1,0,0);
          glutSolidSphere(0.5,20,20);
          glTranslatef(0,0,0.5);
          glColor3f(0.3f,0.3f,0.3f);
          gluCylinder(p, 1,1,2.8,20,20);

          /*Nivel 5*/
          glPushMatrix();
            glColor3f(0.2f,0.2f,0.2f);
            glTranslatef(0,0,2.80f);
            glRotatef(dedoRotate[2], 1,0,0);
            glutSolidSphere(0.5,20,20);
            glTranslatef(0,0,0.5);
            glColor3f(0.3f,0.3f,0.3f);
            gluCylinder(p, 1,1,1.7,20,20);
          glPopMatrix();

        glPopMatrix();  
            
      glPopMatrix();



      /*Nivel 3 -- Dedo anular*/
      glPushMatrix();

        glColor3f(0.2f,0.2f,0.2f);
        glRotatef(10,0,1,0);
        glTranslatef(1.5,0,3.9f);
        glRotatef(dedoRotate[0], 1,0,0);
        glutSolidSphere(0.5,20,20);
        glTranslatef(0,0,0.2);
        glColor3f(0.3f,0.3f,0.3f);
        gluCylinder(p, 1,1,2.5,20,20);

        /*Nivel 4*/
        glPushMatrix();
          glColor3f(0.2f,0.2f,0.2f);
          glTranslatef(0,0,2.8f);
          glRotatef(dedoRotate[1], 1,0,0);
          glutSolidSphere(0.5,20,20);
          glTranslatef(0,0,0.5);
          glColor3f(0.3f,0.3f,0.3f);
          gluCylinder(p, 1,1,2.8,20,20);

          /*Nivel 5*/
          glPushMatrix();
            glColor3f(0.2f,0.2f,0.2f);
            glTranslatef(0,0,2.80f);
            glRotatef(dedoRotate[2], 1,0,0);
            glutSolidSphere(0.5,20,20);
            glTranslatef(0,0,0.5);
            glColor3f(0.3f,0.3f,0.3f);
            gluCylinder(p, 1,1,1.7,20,20);
          glPopMatrix();

        glPopMatrix();  
            
      glPopMatrix();




      /*Nivel 3 -- Meñique*/
      glPushMatrix();

        glColor3f(0.2f,0.2f,0.2f);
        glRotatef(30,0,1,0);
        glTranslatef(2.3,0,3.9f);
        glRotatef(dedoRotate[0], 1,0,0);
        glutSolidSphere(0.5,20,20);
        glTranslatef(0,0,0.2);
        glColor3f(0.3f,0.3f,0.3f);
        gluCylinder(p, 1,1,1.5,20,20);

        /*Nivel 4*/
        glPushMatrix();
          glColor3f(0.2f,0.2f,0.2f);
          glTranslatef(0,0,1.4f);
          glRotatef(dedoRotate[1], 1,0,0);
          glutSolidSphere(0.5,20,20);
          glTranslatef(0,0,0.5);
          glColor3f(0.3f,0.3f,0.3f);
          gluCylinder(p, 1,1,1.5,20,20);

          /*Nivel 5*/
          glPushMatrix();
            glColor3f(0.2f,0.2f,0.2f);
            glTranslatef(0,0,1.4f);
            glRotatef(dedoRotate[2], 1,0,0);
            glutSolidSphere(0.5,20,20);
            glTranslatef(0,0,0.5);
            glColor3f(0.3f,0.3f,0.3f);
            gluCylinder(p, 1,1,2.1,20,20);
          glPopMatrix();

        glPopMatrix();  
            
      glPopMatrix();


      glPopMatrix();
    
    glPopMatrix();
  


  glDisable(GL_COLOR_MATERIAL);
  glutSwapBuffers();
}

void redimensionar(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(float)w/(float)h,1,100);
}

void timer(int i){

  if(i < 127){ //Saludar
    if(rotacionSaludo > 19 || rotacionSaludo < -11) change *= -1;
    rotacionSaludo+=change; 
  }
  else if(i > 127 && i < 258){ //Rotar mano
    if(rotacionOK < 64) rotacionOK+=0.5;
  }
  else if(i > 258 && i < 570){
    if(dedoRotate[0] < 50) dedoRotate[0]+=0.5;
    else if (dedoRotate[1] < 50) dedoRotate[1] += 0.5;
    else if (dedoRotate[2] < 50) dedoRotate[2]+=0.5;
  }
  else if(i > 570 && i < 724){
    if(dedoRotate[0] > 0){
      dedoRotate[0]-=0.5;
      dedoRotate[1]-=0.5;
      dedoRotate[2]-=0.5;
    }
    if(rotacionOK > 0){
      rotacionOK-=0.5;
    }
  }
  else if(i > 724){
    i = 0; // loop
  }

  graficar();
  glutTimerFunc(10,timer,i+1);
}

void teclas(unsigned char key, int x, int y){
  switch (key)
  {
  case 't':
    toggleEjes = (toggleEjes == true) ? false : true;
    graficar();
    break;

  case 27: //Tecla Esc
    exit(0);
    break;

  default:
    break;
  }
}

void special(int key, int x, int y){
  switch (key)
  {
  case GLUT_KEY_UP:
    spotY+=0.1;
    break;

  case GLUT_KEY_DOWN:
    spotY-=0.1;
    break;

  case GLUT_KEY_LEFT:
    spotX-=0.1;
    break;

  case GLUT_KEY_RIGHT:
    spotX+=0.1;
    break;

  case GLUT_KEY_PAGE_UP:
    spotZ+=0.3;
    break;

  case GLUT_KEY_PAGE_DOWN:
    spotZ-=0.3;
    break;
  
  default:
    break;
  }
  graficar();
}

int main(int argc, char** argv)
{

  printf("Con las flechas del teclado manejas la posición de la linterna (Spotlight)\n");
  printf("Presiona 't' para activar o desactivar los ejes de coordenada\n");
  printf("Con 'Re Pag' y 'Av Pag' controlas el ángulo de apertura de la linterna (Spotlight)\n");
  

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600,400);
  glutInitWindowPosition(100,200);
  glutCreateWindow("Mano Robótica");
  inicializar();
  glutSpecialFunc(special);
  glEnable(GL_DEPTH);
  glutDisplayFunc(graficar);
  glutReshapeFunc(redimensionar);
  glutTimerFunc(10,timer,1);
  glutKeyboardFunc(teclas);
  glutMainLoop();
  return 0;
}