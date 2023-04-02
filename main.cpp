#include <GL/glut.h>
#include <stdio.h>
#include <functional>
#include <vector>

using namespace std;

class Poligono{
    public:
        array<float, 3> RGB; //Color del poligono
        vector<array<float,2>> puntos; // Sus vertices

        Poligono(array<float,3> _RGB, vector<array<float,2>> _puntos){
            for(int i = 0; i < 3; i++){_RGB[i] /=255.0f;}

            for(int j = 0; j < _puntos.size(); j++){
                //400 es un valor que sale de la resolución, cambiar a una variable a futuro

                //X
                _puntos[j][0] -= 400;
                _puntos[j][0] /= 400;

                //Y
                _puntos[j][1] -= 400;
                _puntos[j][1] *= -1; // El paint su eje y lo tiene invertido
                _puntos[j][1] /= 400;
            }
            
            this->RGB = _RGB;
            this->puntos = _puntos;
        }
        void graficar(){

            glColor3f(RGB[0],RGB[1],RGB[2]); //Establecer el color ya parseado
            glBegin(GL_POLYGON);
                for(auto punto : puntos){ glVertex2f(punto[0], punto[1]);} //Ingresa los vertices del poligono
            glEnd();
        }

};

//Esto era para el fondo pero ya no se usa porque ha sido reemplazada por fondoGradiente();
void inicializar()
{
    //BackGround
    float R,G,B;

    R = 243;
    G = 246;
    B = 218;

    //Lambda expresion
    auto ajustarColor = [&]() {
        R/=255.0f;
        G/=255.0f;
        B/=255.0f;
    };
    ajustarColor();

    glClearColor(R, G, B, 1.0f);
}

// La o es para poder ajusta el zoom
void redimensionar(int w, int h){
    int o = 0;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-o,o,-o,o,    -1,1);
}

vector<Poligono> figura; //Para guardar los poligonos creados.

//Crea los polígonos y los almacena en la variable figura
void creacionPoligonos(){
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    figura.push_back(Poligono( {168,130,111} , {{431,133}, {496,142}, {424,170}} ));
    figura.push_back(Poligono( {184,152,129} , {{496,142}, {486,146}, {506,166}} ));
}

//Función para facilitar  los colores exactos
void coloresExactosFondo(float R, float G, float B, float x, float y){
    glColor3f(R/255.0f, G/255.0f, B/255.0f); glVertex2f(x, y);
}

//Para el fondo con glow
void fondoGradiente(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS);
        //                   R    G    B      Vertice
        //                  ---  ---  ---    ----------
        coloresExactosFondo(254, 234, 255,   1.0, -1.0);
        coloresExactosFondo(223, 215, 204,   1.0, 1.0 );
        coloresExactosFondo(191, 195, 181,  -1.0, 1.0 );
        coloresExactosFondo(222, 214, 203,  -1.0, -1.0);
    glEnd();
}

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT);
    fondoGradiente(); // fondo con interpolación de colores
    creacionPoligonos(); //Instacia los poligonos
    for (auto &&i : figura) i.graficar(); //Los dibuja en pantalla

    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,200);
    glutCreateWindow("Polygon Art CONEJO");

    //inicializar();

    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);

    glutMainLoop();

    return 0;
}
