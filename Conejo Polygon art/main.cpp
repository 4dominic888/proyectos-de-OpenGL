#include <GL/glut.h>
#include <stdio.h>
#include <functional>
#include <vector>

using namespace std;

//TODO: IMPORTANTE:
//! A la hora de ejecutar este codigo, el compilador necesitará de una configuración adicional
//! Esto es debido a que se usan estructuras de datos nuevas de los includes colocados

//* Codeblocks > Settings > Compiler...
//* Select Compiler: GNU GCC Compiler
//* Compiler settings > Compiler Flags > Have g++ follow the C++11 ISO C++ Language Standar [-std=c++11] (activar)

void createPoligon(array<float,3> _RGB, vector<array<float,2>> _puntos){
    for(int i = 0; i < 3; i++) _RGB[i] /=255.0f;
    for(int j = 0; j < _puntos.size(); j++){
        //400 es un valor que sale de la resolución, cambiar a una variable a futur
        //X
        _puntos[j][0] -= 400;
        _puntos[j][0] /= 400;
        //Y
        _puntos[j][1] -= 400;
        _puntos[j][1] *= -1; // El paint su eje y lo tiene invertido
        _puntos[j][1] /= 400;
    }
    glColor3f(_RGB[0],_RGB[1],_RGB[2]); //Establecer el color ya parseado
    glBegin(GL_POLYGON);
        for(auto punto : _puntos){ glVertex2f(punto[0], punto[1]);} //Ingresa los vertices del poligono
    glEnd();
    
}
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

//Crea los polígonos y los almacena en la variable figura
void creacionPoligonos(){
    // Cabeza
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    createPoligon( {168,130,111} , {{431,133}, {496,142}, {424,170}}    );
    createPoligon( {184,152,129} , {{496,142}, {483,147}, {506,166}}    );//
    createPoligon( {177,145,134} , {{424,170}, {439,225}, {462,207}}    );
    createPoligon( {178,145,128} , {{452,159}, {424,170}, {452,169}}    );
    createPoligon( {153,107,96} , {{452,169}, {484,147}, {452,158}}     );
    createPoligon( {136,95,93} , {{452,169}, {484,147}, {506,166}}      );
    createPoligon( {205,168,149} , {{496,142}, {518,167}, {506,166}}    );
    createPoligon( {169,129,117} , {{424,170}, {462,207}, {452,169}}    );
    createPoligon( {157,98,92} , {{462,207}, {506,166}, {452,169}}      );
    createPoligon( {127,74,70} , {{462,207}, {506,166}, {511,188}}      );
    createPoligon( {168,133,129} , {{517,189}, {506,166}, {511,188}}    );
    createPoligon( {150,117,112} , {{506,166}, {517,166}, {517,190}}    );
    createPoligon( {156,123,116} , {{517,188}, {511,250}, {511,188}}    );
    createPoligon( {117,72,79} , {{511,188}, {511,250}, {487,238}}      );
    createPoligon( {147,96,92} , {{511,188}, {462,207}, {487,238}}      );
    createPoligon( {215,170,151} , {{511,250}, {543,258}, {544,233}}    );
    createPoligon( {221,190,185} , {{511,250}, {543,258}, {518,265}}    );
    createPoligon( {180,125,118} , {{511,250}, {501,254}, {518,265}}    );
    createPoligon( {180,125,118} , {{511,250}, {501,254}, {487,238}}    );
    createPoligon( {197,163,153} , {{480,263}, {501,254}, {518,265}}    );
    createPoligon( {183,143,133} , {{480,263}, {501,254}, {462,207}}    );
    createPoligon( {192,161,156} , {{480,263}, {439,225}, {462,207}}    );
    createPoligon( {212,183,177} , {{480,263}, {542,296}, {518,265}}    );
    createPoligon( {181,151,141} , {{480,263}, {542,296}, {505,311}}    );
    createPoligon( {148,115,98} , {{480,263}, {472,278}, {505,311}}     );
    createPoligon( {167,151,151} , {{460,304}, {472,278}, {505,311}}    );
    createPoligon( {197,182,179} , {{460,304}, {475,328}, {505,311}}    );
    createPoligon( {239,226,233} , {{460,304}, {475,328}, {339,417}}    );
    createPoligon( {253,239,238} , {{479,483}, {475,328}, {339,417}}    );
    createPoligon( {241,224,216} , {{479,483}, {475,328}, {513,375}}    );
    createPoligon( {252,254,251} , {{479,483}, {513,375}, {529,379}}    );
    createPoligon( {255,242,241} , {{479,483}, {604,490}, {529,379}}    );
    createPoligon( {255,255,255} , {{623,391}, {604,490}, {529,379}}    );
    createPoligon( {230,215,218} , {{526,369}, {475,328}, {505,311}}    );
    createPoligon( {255,240,235} , {{526,369}, {542,296}, {505,311}}    );
    createPoligon( {255,247,246} , {{543,258}, {542,296}, {573,314}}    );
    createPoligon( {255,255,255} , {{526,369}, {542,296}, {573,314}}    );
    createPoligon( {255,251,239} , {{526,369}, {606,388}, {573,314}}    );
    createPoligon( {255,255,244} , {{622,328}, {606,388}, {573,314}}    );
    createPoligon( {255,238,228} , {{622,328}, {606,388}, {623,391}}    );
    createPoligon( {255,238,228} , {{622,328}, {623,391}, {666,382}}    );
    createPoligon( {254,255,250} , {{622,328}, {676,341}, {666,382}}    );
    createPoligon( {255,255,247} , {{622,328}, {676,341}, {640,286}}    );
    createPoligon( {249,232,225} , {{526,369}, {475,328}, {513,375}}    );
    createPoligon( {201,166,172} , {{526,369}, {529,379}, {513,375}}    );
    createPoligon( {222,197,193} , {{526,369}, {529,379}, {554,382}}    );
    createPoligon( {255,238,231} , {{526,369}, {623,391}, {554,382}}    );
    createPoligon( {251,217,205} , {{625,293}, {622,328}, {640,286}}    );
    createPoligon( {255,250,244} , {{625,293}, {601,248}, {640,286}}    );
    createPoligon( {255,250,244} , {{613,270}, {601,248}, {574,275}}    );
    createPoligon( {255,250,244} , {{543,258}, {601,248}, {560,290}}    );
    createPoligon( {255,250,244} , {{543,258}, {601,248}, {544,233}}    );
    createPoligon( {209,189,178} , {{585,296}, {560,290}, {574,275}}    );
    createPoligon( {226,207,201} , {{585,296}, {560,290}, {573,314}}    );
    createPoligon( {196,157,158} , {{585,296}, {594,309}, {573,314}}    );
    createPoligon( {245,217,213} , {{597,318}, {594,309}, {573,314}}    );
    createPoligon( {195,167,156} , {{585,296}, {603,296}, {574,275}}    );
    createPoligon( {233,184,167} , {{613,270}, {603,296}, {574,275}}    );
    createPoligon( {215,170,141} , {{613,270}, {603,296}, {625,293}}    );
    createPoligon( {251,217,205} , {{625,293}, {622,328}, {616,307}}    );
    createPoligon( {221,200,207} , {{605,308}, {622,328}, {616,307}}    );
    createPoligon( {200,168,173} , {{597,318}, {594,309}, {605,308}}    );
    createPoligon( {216,165,134} , {{597,318}, {622,328}, {605,308}}    );
    createPoligon( {59,49,56} , {{585,296}, {594,309}, {603,296}}       );
    createPoligon( {59,49,56} , {{605,308}, {594,309}, {603,296}}       );
    createPoligon( {59,49,56} , {{616,307}, {605,308}, {603,296}}       );
    createPoligon( {59,49,56} , {{616,307}, {612,295}, {603,296}}       );
    createPoligon( {247,217,207} , {{616,307}, {612,295}, {625,293}}    );

    // Cuerpo
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    createPoligon( {144,118,105} , {{229,645}, {294,643}, {301,608}}                        );
    createPoligon( {182,162,155} , {{294,643}, {301,608}, {343,605}}                        );
    createPoligon( {120,94,79} , {{229,645}, {294,643}, {300,656}}                          );
    createPoligon( {145,114,96} , {{294,643}, {300,656}, {343,605}}                         );
    createPoligon( {92,72,65} , {{230,645}, {300,656}, {310,667}}                           );
    createPoligon( {103,81,68} , {{300,656}, {310,667}, {343,605}}                          );
    createPoligon( {197,177,168} , {{310,667}, {343,605}, {369,666}}                        );
    createPoligon( {207,184,176} , {{343,605}, {369,666}, {402,608}}                        );
    createPoligon( {225,210,207} , {{369,666}, {402,608}, {424,606}, {421,659}}             );
    createPoligon( {251,234,227} , {{421,659}, {424,606}, {450,601}}                        );
    createPoligon( {421,226,223} , {{421,659}, {450,601}, {464,659}}                        );
    createPoligon( {254,240,229} , {{464,659}, {450,601}, {492,604}}                        );
    createPoligon( {229,209,176} , {{464,659}, {492,604}, {500,647}}                        );
    createPoligon( {239,216,202} , {{500,647}, {492,604}, {521,631}}                        );
    createPoligon( {228,199,185} , {{492,604}, {521,631}, {524,619}}                        );
    createPoligon( {238,219,212} , {{343,605}, {439,584}, {494,540}, {480,483}, {340,417}}  );
    createPoligon( {219,192,185} , {{343,605}, {402,608}, {424,606}, {439,584}}             );
    createPoligon( {209,191,177} , {{439,584}, {494,540}, {494,591}}                        );
    createPoligon( {213,193,186} , {{480,483}, {494,540}, {558,558}}                        );
    createPoligon( {224,205,198} , {{480,483}, {558,558}, {602,490}}                        );
    createPoligon( {195,175,168} , {{494,591}, {494,540}, {558,558}}                        );
    createPoligon( {184,166,144} , {{494,591}, {558,558}, {540,618}}                        );
    createPoligon( {243,229,226} , {{540,618}, {558,558}, {582,587}}                        );
    createPoligon( {201,186,183} , {{540,618}, {582,587}, {575,634}}                        );
    createPoligon( {246,220,207} , {{582,587}, {575,634}, {618,627}}                        );
    createPoligon( {242,211,190} , {{582,587}, {618,627}, {622,592}}                        );
    createPoligon( {168,116,77} , {{618,627}, {622,592}, {637,612}}                         );
    createPoligon( {169,146,140} , {{229,645}, {301,608}, {181,552}}                        );
    createPoligon( {108,81,70} , {{229,645}, {181,552}, {178,629}}                          );
    createPoligon( {177,151,138} , {{178,629}, {181,552}, {124,546}}                        );
    createPoligon( {200,186,185} , {{124,546}, {181,552}, {223,448}}                        );
    createPoligon( {205,188,181} , {{301,608}, {181,552}, {223,448}}                        );
    createPoligon( {207,197,187} , {{301,608}, {223,448}, {338,417}}                        );
    createPoligon( {182,156,141} , {{301,608}, {343,605}, {338,417}}                        );
    createPoligon( {203,184,177} , {{124,546}, {223,448}, {147,415}}                        );
    createPoligon( {200,186,186} , {{147,415}, {223,448}, {219,325}}                        );
    createPoligon( {246,234,238} , {{223,448}, {338,417}, {219,325}}                        );
    createPoligon( {255,254,255} , {{219,325}, {338,417}, {367,286}, {286,291}}             );
    createPoligon( {254,245,248} , {{338,417}, {367,286}, {460,305}}                        );
    createPoligon( {239,226,233} , {{338,417}, {460,305}, {474,327}}                        );
    createPoligon( {253,239,238} , {{338,417}, {480,483}, {474,327}}                        );
    createPoligon( {241,224,216} , {{480,483}, {474,327}, {514,375}}                        );
    createPoligon( {240,240,240} , {{480,483}, {514,375}, {528,380}}                        );
    createPoligon( {255,242,241} , {{480,483}, {528,380}, {602,490}}                        );
    createPoligon( {255,255,255} , {{602,490}, {528,380}, {623,391}}                        );
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
