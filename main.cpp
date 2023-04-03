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
    // Cabeza
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    figura.push_back(Poligono( {168,130,111} , {{431,133}, {496,142}, {424,170}} ));
    figura.push_back(Poligono( {184,152,129} , {{496,142}, {483,147}, {506,166}} ));//
    figura.push_back(Poligono( {177,145,134} , {{424,170}, {439,225}, {462,207}} ));
    figura.push_back(Poligono( {178,145,128} , {{452,159}, {424,170}, {452,169}} ));
    figura.push_back(Poligono( {153,107,96} , {{452,169}, {484,147}, {452,158}} ));
    figura.push_back(Poligono( {136,95,93} , {{452,169}, {484,147}, {506,166}} ));
    figura.push_back(Poligono( {205,168,149} , {{496,142}, {518,167}, {506,166}} ));
    figura.push_back(Poligono( {169,129,117} , {{424,170}, {462,207}, {452,169}} ));
    figura.push_back(Poligono( {157,98,92} , {{462,207}, {506,166}, {452,169}} ));
    figura.push_back(Poligono( {127,74,70} , {{462,207}, {506,166}, {511,188}} ));
    figura.push_back(Poligono( {168,133,129} , {{517,189}, {506,166}, {511,188}} ));
    figura.push_back(Poligono( {150,117,112} , {{506,166}, {517,166}, {517,190}} ));
    figura.push_back(Poligono( {156,123,116} , {{517,188}, {511,250}, {511,188}} ));
    figura.push_back(Poligono( {117,72,79} , {{511,188}, {511,250}, {487,238}} ));
    figura.push_back(Poligono( {147,96,92} , {{511,188}, {462,207}, {487,238}} ));
    figura.push_back(Poligono( {215,170,151} , {{511,250}, {543,258}, {544,233}} ));
    figura.push_back(Poligono( {221,190,185} , {{511,250}, {543,258}, {518,265}} ));
    figura.push_back(Poligono( {180,125,118} , {{511,250}, {501,254}, {518,265}} ));
    figura.push_back(Poligono( {180,125,118} , {{511,250}, {501,254}, {487,238}} ));
    figura.push_back(Poligono( {197,163,153} , {{480,263}, {501,254}, {518,265}} ));
    figura.push_back(Poligono( {183,143,133} , {{480,263}, {501,254}, {462,207}} ));
    figura.push_back(Poligono( {192,161,156} , {{480,263}, {439,225}, {462,207}} ));
    figura.push_back(Poligono( {212,183,177} , {{480,263}, {542,296}, {518,265}} ));
    figura.push_back(Poligono( {181,151,141} , {{480,263}, {542,296}, {505,311}} ));
    figura.push_back(Poligono( {148,115,98} , {{480,263}, {472,278}, {505,311}} ));
    figura.push_back(Poligono( {167,151,151} , {{460,304}, {472,278}, {505,311}} ));
    figura.push_back(Poligono( {197,182,179} , {{460,304}, {475,328}, {505,311}} ));
    figura.push_back(Poligono( {239,226,233} , {{460,304}, {475,328}, {339,417}} ));
    figura.push_back(Poligono( {253,239,238} , {{479,483}, {475,328}, {339,417}} ));
    figura.push_back(Poligono( {241,224,216} , {{479,483}, {475,328}, {513,375}} ));
    figura.push_back(Poligono( {252,254,251} , {{479,483}, {513,375}, {529,379}} ));
    figura.push_back(Poligono( {255,242,241} , {{479,483}, {604,490}, {529,379}} ));
    figura.push_back(Poligono( {255,255,255} , {{623,391}, {604,490}, {529,379}} ));
    figura.push_back(Poligono( {230,215,218} , {{526,369}, {475,328}, {505,311}} ));
    figura.push_back(Poligono( {255,240,235} , {{526,369}, {542,296}, {505,311}} ));
    figura.push_back(Poligono( {255,247,246} , {{543,258}, {542,296}, {573,314}} ));
    figura.push_back(Poligono( {255,255,255} , {{526,369}, {542,296}, {573,314}} ));
    figura.push_back(Poligono( {255,251,239} , {{526,369}, {606,388}, {573,314}} ));
    figura.push_back(Poligono( {255,255,244} , {{622,328}, {606,388}, {573,314}} ));
    figura.push_back(Poligono( {255,238,228} , {{622,328}, {606,388}, {623,391}} ));
    figura.push_back(Poligono( {255,238,228} , {{622,328}, {623,391}, {666,382}} ));
    figura.push_back(Poligono( {254,255,250} , {{622,328}, {676,341}, {666,382}} ));
    figura.push_back(Poligono( {255,255,247} , {{622,328}, {676,341}, {640,286}} ));
    figura.push_back(Poligono( {249,232,225} , {{526,369}, {475,328}, {513,375}} ));
    figura.push_back(Poligono( {201,166,172} , {{526,369}, {529,379}, {513,375}} ));
    figura.push_back(Poligono( {222,197,193} , {{526,369}, {529,379}, {554,382}} ));
    figura.push_back(Poligono( {255,238,231} , {{526,369}, {623,391}, {554,382}} ));
    figura.push_back(Poligono( {251,217,205} , {{625,293}, {622,328}, {640,286}} ));
    figura.push_back(Poligono( {255,250,244} , {{625,293}, {601,248}, {640,286}} ));
    figura.push_back(Poligono( {255,250,244} , {{613,270}, {601,248}, {574,275}} ));
    figura.push_back(Poligono( {255,250,244} , {{543,258}, {601,248}, {560,290}} ));
    figura.push_back(Poligono( {255,250,244} , {{543,258}, {601,248}, {544,233}} ));
    figura.push_back(Poligono( {209,189,178} , {{585,296}, {560,290}, {574,275}} ));
    figura.push_back(Poligono( {226,207,201} , {{585,296}, {560,290}, {573,314}} ));
    figura.push_back(Poligono( {196,157,158} , {{585,296}, {594,309}, {573,314}} ));
    figura.push_back(Poligono( {245,217,213} , {{597,318}, {594,309}, {573,314}} ));
    figura.push_back(Poligono( {195,167,156} , {{585,296}, {603,296}, {574,275}} ));
    figura.push_back(Poligono( {233,184,167} , {{613,270}, {603,296}, {574,275}} ));
    figura.push_back(Poligono( {215,170,141} , {{613,270}, {603,296}, {625,293}} ));
    figura.push_back(Poligono( {251,217,205} , {{625,293}, {622,328}, {616,307}} ));
    figura.push_back(Poligono( {221,200,207} , {{605,308}, {622,328}, {616,307}} ));
    figura.push_back(Poligono( {200,168,173} , {{597,318}, {594,309}, {605,308}} ));
    figura.push_back(Poligono( {216,165,134} , {{597,318}, {622,328}, {605,308}} ));
    figura.push_back(Poligono( {59,49,56} , {{585,296}, {594,309}, {603,296}} ));
    figura.push_back(Poligono( {59,49,56} , {{605,308}, {594,309}, {603,296}} ));
    figura.push_back(Poligono( {59,49,56} , {{616,307}, {605,308}, {603,296}} ));
    figura.push_back(Poligono( {59,49,56} , {{616,307}, {612,295}, {603,296}} ));
    figura.push_back(Poligono( {247,217,207} , {{616,307}, {612,295}, {625,293}} )); 

    // Cuerpo
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    figura.push_back(Poligono( {144,118,105} , {{229,645}, {294,643}, {301,608}} ));
    figura.push_back(Poligono( {182,162,155} , {{294,643}, {301,608}, {343,605}} ));
    figura.push_back(Poligono( {120,94,79} , {{229,645}, {294,643}, {300,656}} ));
    figura.push_back(Poligono( {145,114,96} , {{294,643}, {300,656}, {343,605}} ));
    figura.push_back(Poligono( {92,72,65} , {{230,645}, {300,656}, {310,667}} ));
    figura.push_back(Poligono( {103,81,68} , {{300,656}, {310,667}, {343,605}} ));
    figura.push_back(Poligono( {197,177,168} , {{310,667}, {343,605}, {369,666}} ));
    figura.push_back(Poligono( {207,184,176} , {{343,605}, {369,666}, {402,608}} ));
    figura.push_back(Poligono( {225,210,207} , {{369,666}, {402,608}, {424,606}, {421,659}} ));
    figura.push_back(Poligono( {251,234,227} , {{421,659}, {424,606}, {450,601}} ));
    figura.push_back(Poligono( {421,226,223} , {{421,659}, {450,601}, {464,659}} ));
    figura.push_back(Poligono( {254,240,229} , {{464,659}, {450,601}, {492,604}} ));
    figura.push_back(Poligono( {229,209,176} , {{464,659}, {492,604}, {500,647}} ));
    figura.push_back(Poligono( {239,216,202} , {{500,647}, {492,604}, {521,631}} ));
    figura.push_back(Poligono( {228,199,185} , {{492,604}, {521,631}, {524,619}} ));
    figura.push_back(Poligono( {238,219,212} , {{343,605}, {439,584}, {494,540}, {480,483}, {340,417}} ));
    figura.push_back(Poligono( {219,192,185} , {{343,605}, {402,608}, {424,606}, {439,584}} ));
    figura.push_back(Poligono( {209,191,177} , {{439,584}, {494,540}, {494,591}} ));
    figura.push_back(Poligono( {213,193,186} , {{480,483}, {494,540}, {558,558}} ));
    figura.push_back(Poligono( {224,205,198} , {{480,483}, {558,558}, {602,490}} ));
    figura.push_back(Poligono( {195,175,168} , {{494,591}, {494,540}, {558,558}} ));
    figura.push_back(Poligono( {184,166,144} , {{494,591}, {558,558}, {540,618}} ));
    figura.push_back(Poligono( {243,229,226} , {{540,618}, {558,558}, {582,587}} ));
    figura.push_back(Poligono( {201,186,183} , {{540,618}, {582,587}, {575,634}} ));
    figura.push_back(Poligono( {246,220,207} , {{582,587}, {575,634}, {618,627}} ));
    figura.push_back(Poligono( {242,211,190} , {{582,587}, {618,627}, {622,592}} ));
    figura.push_back(Poligono( {168,116,77} , {{618,627}, {622,592}, {637,612}} ));
    figura.push_back(Poligono( {169,146,140} , {{229,645}, {301,608}, {181,552}} ));
    figura.push_back(Poligono( {108,81,70} , {{229,645}, {181,552}, {178,629}} ));
    figura.push_back(Poligono( {177,151,138} , {{178,629}, {181,552}, {124,546}} ));
    figura.push_back(Poligono( {200,186,185} , {{124,546}, {181,552}, {223,448}} ));
    figura.push_back(Poligono( {205,188,181} , {{301,608}, {181,552}, {223,448}} ));
    figura.push_back(Poligono( {207,197,187} , {{301,608}, {223,448}, {338,417}} ));
    figura.push_back(Poligono( {182,156,141} , {{301,608}, {343,605}, {338,417}} ));
    figura.push_back(Poligono( {203,184,177} , {{124,546}, {223,448}, {147,415}} ));
    figura.push_back(Poligono( {200,186,186} , {{147,415}, {223,448}, {219,325}} ));
    figura.push_back(Poligono( {246,234,238} , {{223,448}, {338,417}, {219,325}} ));
    figura.push_back(Poligono( {255,254,255} , {{219,325}, {338,417}, {367,286}, {286,291}} ));
    figura.push_back(Poligono( {254,245,248} , {{338,417}, {367,286}, {460,305}} ));
    figura.push_back(Poligono( {239,226,233} , {{338,417}, {460,305}, {474,327}} ));
    figura.push_back(Poligono( {253,239,238} , {{338,417}, {480,483}, {474,327}} ));
    figura.push_back(Poligono( {241,224,216} , {{480,483}, {474,327}, {514,375}} ));
    figura.push_back(Poligono( {240,240,240} , {{480,483}, {514,375}, {528,380}} ));
    figura.push_back(Poligono( {255,242,241} , {{480,483}, {528,380}, {602,490}} ));
    figura.push_back(Poligono( {255,255,255} , {{602,490}, {528,380}, {623,391}} ));
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
