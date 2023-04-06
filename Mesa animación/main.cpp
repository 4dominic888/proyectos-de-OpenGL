#include <GL/glut.h>

float angulo=0;
float trasX=0;
float dir=1;

void inicializar()

{
  glClearColor(0.8,0.8,0.8,0.0);
}

void graficarEjes()
{
  glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2f(-15,0);
    glVertex2f(15,0);
    glColor3f(0,0,1);
    glVertex2f(0,-10);
    glVertex2f(0,10);
  glEnd();

}

void graficar()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


   graficarEjes();


   glBegin(GL_POLYGON);
    glColor3f(0.5,0,0);
    glVertex2f(-10,6);
    glColor3f(0.2,0,0);
    glVertex2f(10,6);
    glColor3f(0.5,0,0);
    glVertex2f(5,-6);
    glColor3f(1,0,0);
    glVertex2f(-15,-6);
   glEnd();

   ///glTranslatef(trasX,0,0);
   ///glScalef(0.5,2,1);
   glTranslatef(5,1,0);
   glRotatef(angulo,0,0,1);
   glTranslatef(-5,-1,0);
   glColor3f(0,1,0);

   glBegin(GL_TRIANGLES);
    glVertex2f(0,7);
    glVertex2f(10,0);
    glVertex2f(0,-5);
   glEnd();
   glFlush();
}
void redimensionar(int w, int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-1,1, -1,1,    -1,1);
  glOrtho(-20,20, -20,20,    -1,1);
}
void manejarTeclado(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 'a':
          angulo=angulo+2;
          break;
    case 'b':
          angulo=angulo-2;
          break;
  }
  glutPostRedisplay();
}
void mover(int i)
{
  trasX=trasX+0.2*dir;
  if(trasX>10){
    dir=-1;
  }
  if(trasX<-20)
  {
    dir=1;
  }
  glutPostRedisplay();
  glutTimerFunc(20,mover,1);
}

void rotar(int i)
{
  angulo++;
  glutPostOverlayRedisplay();
  glutTimerFunc(5,rotar,2);
}

int main(int argc, char** argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(100,200);
  glutCreateWindow("Hola Mundo");

  inicializar();

  glutDisplayFunc(graficar);
  glutReshapeFunc(redimensionar);
  glutKeyboardFunc(manejarTeclado);
  glutTimerFunc(20,mover,1);
  glutTimerFunc(5,rotar,2);
  glutMainLoop();
  return 0;

}