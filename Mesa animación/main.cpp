#include <GL/glut.h>
#include <stdio.h>
#include <functional>
#include <vector>
#include <math.h>

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

            glColor3f(RGB[0],RGB[1],RGB[2]); //Establecer el color ya parseado
            glBegin(GL_POLYGON);
                for(auto punto : puntos){ glVertex2f(punto[0], punto[1]);} //Ingresa los vertices del poligono
            glEnd();
        }
};

#pragma region Variables Globales

vector<Poligono> figura; //Para guardar los poligonos creados y dibujarlos
vector<Poligono> manzana;

//                                       Coordenada XY Pixeles    incremento Pixeles      incremento move         Movimiento OpenGL       Right/Left      Up/Down
vector<array<double,2>> infoManzana = {       {229,271},               {1,1},             {0.005,0.005},               {0,0},              {26,21},        {42,14}};

#pragma endregion

#pragma region Métodos del OpenGL default y agregado

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

//Función para facilitar  los colores exactos
void coloresExactosFondo(float R, float G, float B, float x, float y){
    glColor3f(R/255.0f, G/255.0f, B/255.0f); glVertex2f(x, y);
}

#pragma endregion

#pragma region Creación de objetos
void dibujadoMesa(){
    //base(parte alta)
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    figura.push_back(Poligono( {210,192,168} , {{45,159}, {97,128}, {97,159}} )); //1
    figura.push_back(Poligono( {240,194,171} , {{128,128}, {97,128}, {97,159}} )); //2
    figura.push_back(Poligono( {211,186,156} , {{128,128}, {97,159}, {159,159}} )); //3
    figura.push_back(Poligono( {200,174,149} , {{128,128}, {159,159}, {190,128}} )); //4
    figura.push_back(Poligono( {199,180,150} , {{190,159}, {159,159}, {190,128}} )); //5
    figura.push_back(Poligono( {200,179,150} , {{190,159}, {221,128}, {190,128}} )); //6
    figura.push_back(Poligono( {195,175,140} , {{190,159}, {221,128}, {252,159}} )); //7
    figura.push_back(Poligono( {211,178,147} , {{252,128}, {221,128}, {252,159}} )); //8
    figura.push_back(Poligono( {201,173,149} , {{268,144}, {252,128}, {252,159}} )); //9
    figura.push_back(Poligono( {204,171,140} , {{268,144}, {283,159}, {252,159}} )); //10
    figura.push_back(Poligono( {198,171,141} , {{252,128}, {283,159}, {314,128}} )); //11
    figura.push_back(Poligono( {197,173,137} , {{314,159}, {283,159}, {314,128}} )); //12
    figura.push_back(Poligono( {201,174,144} , {{314,159}, {344,159}, {314,128}} )); //13
    figura.push_back(Poligono( {194,171,139} , {{344,128}, {344,159}, {314,128}} )); //14
    figura.push_back(Poligono( {199,169,133} , {{344,128}, {344,159}, {374,159}} )); //15
    figura.push_back(Poligono( {199,170,138} , {{344,128}, {374,128}, {374,159}} )); //16
    figura.push_back(Poligono( {199,175,139} , {{374,128}, {404,128}, {374,159}} )); //17
    figura.push_back(Poligono( {199,170,138 } , {{404,159}, {404,128}, {374,159}} )); //18
    figura.push_back(Poligono( {197,170,140} , {{404,159}, {404,128}, {419,142}} )); //19
    figura.push_back(Poligono( {197,170,140} , {{433,128}, {404,128}, {419,142}} )); //20
    figura.push_back(Poligono( {197,170,140} , {{404,159}, {433,159}, {419,142}} )); //21
    figura.push_back(Poligono( {197,170,140} , {{433,128}, {433,159}, {419,142}} )); //22
    figura.push_back(Poligono( {199,175,141} , {{433,128}, {433,159}, {462,128}} )); //23
    figura.push_back(Poligono( {207,174,139} , {{490,159}, {433,159}, {462,128}} )); //24
    figura.push_back(Poligono( {203,180,148} , {{490,159}, {501,128}, {462,128}} )); //25
    figura.push_back(Poligono( {219,184,142} , {{490,159}, {501,128}, {558,159}} )); //26

    //base(parte media)
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------

    figura.push_back(Poligono( {172,134,95} , {{45,159}, {40,162}, {74,162}} )); //1
    figura.push_back(Poligono( {165,124,78} , {{45,159}, {97,159}, {74,162}} )); //2
    figura.push_back(Poligono( {167,123,78} , {{110,162}, {97,159}, {74,162}} )); //3
    figura.push_back(Poligono( {167,123,78} , {{110,162}, {97,159}, {126,159}} )); //4
    figura.push_back(Poligono( {167,123,78} , {{110,162}, {145,162}, {126,159}} )); //5
    figura.push_back(Poligono( {167,123,78} , {{159,159}, {145,162}, {126,159}} )); //6
    figura.push_back(Poligono( {167,123,78} , {{159,159}, {145,162}, {178,162}} )); //7
    figura.push_back(Poligono( {167,123,78} , {{159,159}, {190,159}, {178,162}} )); //8
    figura.push_back(Poligono( {167,123,78} , {{213,162}, {190,159}, {178,162}} )); //9
    figura.push_back(Poligono( {167,123,78} , {{213,162}, {190,159}, {227,159}} )); //10
    figura.push_back(Poligono( {167,123,78} , {{213,162}, {249,162}, {227,159}} )); //11
    figura.push_back(Poligono( {167,123,78} , {{252,159}, {249,162}, {227,159}} )); //12
    figura.push_back(Poligono( {167,123,78} , {{252,159}, {249,162}, {268,162}} )); //13
    figura.push_back(Poligono( {167,123,78} , {{252,159}, {283,159}, {268,162}} )); //14
    figura.push_back(Poligono( {167,123,78} , {{285,162}, {283,159}, {268,162}} )); //15
    figura.push_back(Poligono( {167,123,78} , {{285,162}, {283,159}, {314,159}} )); //16
    figura.push_back(Poligono( {167,123,78} , {{285,162}, {321,162}, {314,159}} )); //17
    figura.push_back(Poligono( {167,123,78} , {{332,159}, {321,162}, {314,159}} )); //18
    figura.push_back(Poligono( {167,123,78} , {{332,159}, {321,162}, {337,162}} )); //19
    figura.push_back(Poligono( {167,123,78} , {{332,159}, {344,159}, {337,162}} )); //20
    figura.push_back(Poligono( {167,123,78} , {{363,162}, {344,159}, {337,162}} )); //21
    figura.push_back(Poligono( {167,123,78} , {{363,162}, {344,159}, {374,159}} )); //22
    figura.push_back(Poligono( {167,123,78} , {{363,162}, {394,162}, {374,159}} )); //23
    figura.push_back(Poligono( {167,123,78} , {{404,159}, {394,162}, {374,159}} )); //24
    figura.push_back(Poligono( {167,123,78} , {{404,159}, {394,162}, {418,162}} )); //25
    figura.push_back(Poligono( {167,123,78} , {{404,159}, {433,159}, {418,162}} )); //26
    figura.push_back(Poligono( {167,123,78} , {{452,162}, {433,159}, {418,162}} )); //27
    figura.push_back(Poligono( {167,123,78} , {{452,162}, {433,159}, {469,159}} )); //28
    figura.push_back(Poligono( {167,123,78} , {{452,162}, {483,162}, {469,159}} )); //29
    figura.push_back(Poligono( {167,123,78} , {{490,159}, {483,162}, {469,159}} )); //30
    figura.push_back(Poligono( {167,123,78} , {{490,159}, {483,162}, {507,162}} )); //31
    figura.push_back(Poligono( {167,123,78} , {{490,159}, {525,159}, {507,162}} )); //32
    figura.push_back(Poligono( {167,123,78} , {{539,162}, {525,159}, {507,162}} )); //33
    figura.push_back(Poligono( {167,123,78} , {{539,162}, {525,159}, {558,159}} )); //34
    figura.push_back(Poligono( {167,123,78} , {{539,162}, {558,162}, {558,159}} )); //35

    //base(patas izquierda)
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------

     figura.push_back(Poligono( {129,97,55} , {{40,162}, {74,162}, {40,200}} )); //1
     figura.push_back(Poligono( {216,187,155} , {{74,234}, {74,162}, {40,200}} )); //2
     figura.push_back(Poligono( {201,175,140} , {{74,234}, {40,268}, {40,200}} )); //3
     figura.push_back(Poligono( {211,183,146} , {{74,234}, {40,268}, {74,302}} )); //4
     figura.push_back(Poligono( {195,166,126} , {{40,336}, {40,268}, {74,302}} )); //5
     figura.push_back(Poligono( {211,179,141} , {{40,336}, {74,370}, {74,302}} )); //6
     figura.push_back(Poligono( {180,137,73} , {{40,336}, {74,370}, {40,404}} )); //7
     figura.push_back(Poligono( {204,172,133} , {{74,438}, {74,370}, {40,404}} )); //8
     figura.push_back(Poligono( {146,112,61} , {{74,438}, {40,472}, {40,404}} )); //9
     figura.push_back(Poligono( {205,170,130} , {{74,438}, {40,472}, {74,472}} )); //10
     figura.push_back(Poligono( {180,139,84} , {{40,162}, {57,181}, {40,200}} ));
     figura.push_back(Poligono( {216,187,155} , {{57,181}, {61,221}, {40,200}} ));
     figura.push_back(Poligono( {183,143,89} , {{40,216}, {61,221}, {40,200}} ));
     figura.push_back(Poligono( {183,143,89} , {{74,234}, {53,255}, {74,265}} ));
     figura.push_back(Poligono( {183,143,89} , {{57,285}, {53,255}, {74,265}} ));

     figura.push_back(Poligono( {147,104,62} , {{92,198}, {119,198}, {119,218}} )); //12
     figura.push_back(Poligono( {177,145,106} , {{92,198}, {92,218}, {119,218}} )); //13
     figura.push_back(Poligono( {190,160,126} , {{119,245}, {92,218}, {119,218}} )); //14
     figura.push_back(Poligono( {192,159,124} , {{119,245}, {92,218}, {92,272}} )); //15
     figura.push_back(Poligono( {200,168,127} , {{119,245}, {119,299}, {92,272}} )); //16
     figura.push_back(Poligono( {178,146,105} , {{92,236}, {119,299}, {92,272}} )); //17
     figura.push_back(Poligono( {179,144,107} , {{92,236}, {119,299}, {119,353}} )); //18
     figura.push_back(Poligono( {191,156,114} , {{92,236}, {92,380}, {119,353}} )); //19
     figura.push_back(Poligono( {187,152,110} , {{119,380}, {92,380}, {119,353}} )); //20


     figura.push_back(Poligono( {195,183,167} , {{74,198}, {78,198}, {74,234}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,238}, {78,198}, {74,234}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,238}, {74,244}, {74,234}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,238}, {74,244}, {78,259}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,302}, {74,244}, {78,259}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,302}, {78,313}, {78,259}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,302}, {78,313}, {74,319}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,333}, {78,313}, {74,319}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,333}, {78,337}, {74,319}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,333}, {78,337}, {74,370}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,354}, {78,337}, {74,370}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,354}, {78,377}, {74,370}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,354}, {78,377}, {74,391}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,429}, {78,377}, {74,391}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,429}, {74,415}, {74,391}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,429}, {74,415}, {74,438}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,451}, {74,415}, {74,438}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,451}, {74,462}, {74,438}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,451}, {74,462}, {78,463}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,472}, {74,462}, {78,463}} ));
     figura.push_back(Poligono( {195,183,167} , {{74,370}, {78,377}, {74,391}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,429}, {74,438}, {78,451}} ));
     figura.push_back(Poligono( {195,183,167} , {{78,313}, {74,319}, {78,337}} ));


     figura.push_back(Poligono( {195,183,167} , {{119,198}, {122,198}, {119,218}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,229}, {122,198}, {119,218}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,229}, {119,245}, {119,218}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,229}, {119,245}, {122,243}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,265}, {119,245}, {122,243}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,265}, {122,280}, {122,243}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,265}, {122,280}, {119,299}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,313}, {122,280}, {119,299}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,313}, {119,324}, {119,299}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,313}, {119,324}, {122,321}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,338}, {119,324}, {122,321}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,338}, {122,347}, {122,321}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,338}, {122,347}, {122,334}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,338}, {122,347}, {119,353}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,366}, {122,347}, {119,353}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,366}, {122,347}, {122,364}} ));
     figura.push_back(Poligono( {195,183,167} , {{119,366}, {119,380}, {122,364}} ));
     figura.push_back(Poligono( {195,183,167} , {{122,375}, {119,380}, {122,364}} ));


    //base(parte media)
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------

    figura.push_back(Poligono( {198,165,124} , {{74,162}, {74,198}, {110,162}} )); //21
    figura.push_back(Poligono( {191,157,119} , {{110,198}, {74,198}, {110,162}} )); //22
    figura.push_back(Poligono( {192,157,115} , {{110,198}, {145,198}, {110,162}} )); //23
    figura.push_back(Poligono( {203,171,124} , {{145,162}, {145,198}, {110,162}} )); //24
    figura.push_back(Poligono( {194,160,115} , {{145,162}, {145,198}, {162,198}} )); //25
    figura.push_back(Poligono( {176,134,77} , {{145,162}, {178,162}, {162,198}} )); //26
    figura.push_back(Poligono( {184,145,92} , {{213,198}, {178,162}, {162,198}} )); //27
    figura.push_back(Poligono( {188,152,103} , {{213,198}, {178,162}, {213,162}} )); //28
    figura.push_back(Poligono( {197,164,120} , {{213,198}, {249,198}, {213,162}} )); //29
    figura.push_back(Poligono( {129,97,55} , {{249,162}, {249,198}, {213,162}} )); //30
    figura.push_back(Poligono( {121,92,53} , {{249,162}, {249,198}, {285,162}} )); //31
    figura.push_back(Poligono( {142,108,62} , {{321,198}, {249,198}, {285,162}} )); //32
    figura.push_back(Poligono( {157,119,68} , {{321,198}, {321,162}, {285,162}} )); //33
    figura.push_back(Poligono( {191,157,119} , {{321,198}, {321,162}, {357,198}} )); //34
    figura.push_back(Poligono( {180,139,84} , {{394,162}, {321,162}, {357,198}} )); //35
    figura.push_back(Poligono( {188,151,101} , {{394,162}, {431,198}, {357,198}} )); //36
    figura.push_back(Poligono( {197,165,122} , {{394,162}, {431,198}, {469,162}} )); //37
    figura.push_back(Poligono( {206,180,142} , {{469,198}, {431,198}, {469,162}} )); //38
    figura.push_back(Poligono( {169,129,73} , {{469,198}, {525,198}, {469,162}} )); //39
    figura.push_back(Poligono( {191,157,119} , {{525,162}, {525,198}, {469,162}} )); //40


    //base(patas derecha)
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    figura.push_back(Poligono( {218,189,149} , {{525,162}, {558,162}, {558,174}} )); //41
    figura.push_back(Poligono( {203,163,107} , {{525,162}, {525,206}, {558,174}} )); //42
    figura.push_back(Poligono( {151,115,66} , {{558,206}, {525,206}, {558,174}} )); //43
    figura.push_back(Poligono( {129,98,56} , {{558,206}, {525,206}, {541,223}} )); //44
    figura.push_back(Poligono( {191,157,119} , {{558,206}, {558,239}, {541,223}} )); //45
    figura.push_back(Poligono( {179,131,81} , {{525,206}, {558,239}, {542,239}} )); //46
    figura.push_back(Poligono( {169,129,73} , {{525,206}, {525,239}, {542,239}} )); //47
    figura.push_back(Poligono( {200,170,130} , {{525,272}, {525,239}, {558,239}} )); //48
    figura.push_back(Poligono( {183,143,89} , {{542,255}, {558,272}, {558,239}} )); //49
    figura.push_back(Poligono( {157,119,68} , {{542,255}, {558,272}, {525,272}} )); //50
    figura.push_back(Poligono( {91,70,40} , {{558,305}, {558,272}, {525,272}} )); //51
    figura.push_back(Poligono( {143,109,63} , {{558,305}, {525,305}, {525,272}} )); //52
    figura.push_back(Poligono( {108,80,46} , {{558,305}, {525,305}, {542,321}} )); //53
    figura.push_back(Poligono( {140,107,62} , {{525,338}, {525,305}, {542,321}} )); //54
    figura.push_back(Poligono( {96,73,43} , {{525,338}, {539,352}, {558,305}} )); //55
    figura.push_back(Poligono( {205,177,139} , {{558,371}, {539,352}, {558,305}} )); //56
    figura.push_back(Poligono( {182,141,86} , {{558,371}, {525,338}, {525,371}} )); //57
    figura.push_back(Poligono( {225,209,187} , {{558,371}, {525,371}, {525,404}} )); //58
    figura.push_back(Poligono( {151,115,66} , {{558,437}, {543,386}, {525,404}} )); //59
    figura.push_back(Poligono( {183,143,89} , {{558,437}, {543,386}, {558,371}} )); //60
    figura.push_back(Poligono( {159,121,70} , {{525,470}, {542,421}, {525,404}} )); //61
    figura.push_back(Poligono( {197,164,120} , {{525,470}, {542,421}, {558,437}} )); //62
    figura.push_back(Poligono( {169,129,73} , {{525,470}, {558,470}, {558,437}} )); //63

    figura.push_back(Poligono( {176,134,94} , {{480,198}, {495,198}, {480,224}} )); //64
    figura.push_back(Poligono( {150,112,73} , {{506,198}, {495,198}, {480,224}} )); //65
    figura.push_back(Poligono( {192,159,126} , {{506,198}, {498,242}, {480,224}} )); //66
    figura.push_back(Poligono( {167,124,82} , {{506,198}, {498,242}, {506,250}} )); //67
    figura.push_back(Poligono( {137,102,67} , {{506,250}, {480,250}, {480,224}} )); //68
    figura.push_back(Poligono( {172,130,87} , {{506,250}, {480,250}, {501,255}} )); //69
    figura.push_back(Poligono( {155,116,77} , {{506,250}, {496,260}, {506,302}} )); //70
    figura.push_back(Poligono( {159,121,70} , {{480,276}, {496,260}, {506,302}} )); //71
    figura.push_back(Poligono( {225,209,187} , {{480,276}, {480,328}, {506,302}} )); //72
    figura.push_back(Poligono( {143,109,63} , {{506,354}, {480,328}, {506,302}} )); //73
    figura.push_back(Poligono( {169,129,73} , {{506,354}, {480,328}, {485,375}} )); //74
    figura.push_back(Poligono( {91,70,40} , {{480,380}, {480,328}, {485,375}} )); //75
    figura.push_back(Poligono( {140,107,62} , {{480,380}, {506,354}, {506,380}} )); //76
    figura.push_back(Poligono( {207,182,156} , {{480,276}, {480,250}, {501,255}} )); //77


    figura.push_back(Poligono( {195,183,167} , {{476,198}, {480,198}, {476,204}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,212}, {480,198}, {476,204}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,212}, {476,219}, {476,204}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,212}, {476,219}, {480,224}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,231}, {476,219}, {480,224}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,231}, {476,219}, {476,239}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,231}, {480,240}, {476,239}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,251}, {480,240}, {476,239}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,251}, {480,240}, {480,250}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,251}, {480,261}, {480,250}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,251}, {480,261}, {476,281}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,251}, {480,261}, {476,281}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,276}, {480,261}, {476,281}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,276}, {480,296}, {476,281}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,293}, {480,296}, {476,281}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,293}, {480,296}, {476,312}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,328}, {480,296}, {476,312}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,328}, {476,346}, {476,312}} ));
    figura.push_back(Poligono( {195,183,167} , {{480,328}, {476,346}, {480,360}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,374}, {476,346}, {480,360}} ));
    figura.push_back(Poligono( {195,183,167} , {{476,374}, {480,380}, {480,360}} ));


    figura.push_back(Poligono( {195,183,167} , {{521,198}, {525,198}, {525,206}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,198}, {521,223}, {525,206}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,239}, {521,223}, {525,206}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,239}, {521,223}, {521,258}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,239}, {525,272}, {521,258}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,292}, {525,272}, {521,258}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,292}, {525,272}, {525,305}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,292}, {521,324}, {525,305}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,338}, {521,324}, {525,305}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,338}, {521,324}, {521,335}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,338}, {525,371}, {521,335}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,403}, {525,371}, {521,335}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,403}, {525,371}, {525,404}} ));
    figura.push_back(Poligono( {195,183,167} , {{521,403}, {521,428}, {525,404}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,443}, {521,428}, {525,404}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,443}, {521,428}, {521,462}} ));
    figura.push_back(Poligono( {195,183,167} , {{525,443}, {525,470}, {521,462}} ));
    
}

void dibujadoManzana(){
    //                           Color RGB                Coordenadas
    //                         ------------    -----------------------------------
    manzana.push_back(Poligono( {227,192,150} , {{101,38}, {110,33}, {122,31}} )); //1
    manzana.push_back(Poligono( {220,156,84} , {{134,31}, {123,48}, {122,31}} )); //2
    manzana.push_back(Poligono( {237,127,74} , {{101,38}, {123,48}, {122,31}} )); //3
    manzana.push_back(Poligono( {167,107,53} , {{101,38}, {91,52}, {110,42}} )); //4
    manzana.push_back(Poligono( {175,92,58} , {{101,62}, {91,52}, {110,42}} )); //5
    manzana.push_back(Poligono( {192,138,76} , {{101,62}, {91,52}, {88,73}} )); //6
    manzana.push_back(Poligono( {185,78,62} , {{101,62}, {115,74}, {88,73}} )); //7
    manzana.push_back(Poligono( {195,103,78} , {{92,91}, {115,74}, {88,73}} )); //8
    manzana.push_back(Poligono( {204,120,83} , {{92,91}, {115,74}, {118,110}} )); //9
    manzana.push_back(Poligono( {181,72,51} , {{92,91}, {111,118}, {118,110}} )); //10
    manzana.push_back(Poligono( {129,36,18} , {{130,121}, {111,118}, {118,110}} )); //11
    manzana.push_back(Poligono( {180,74,48} , {{130,121}, {111,118}, {143,106}} )); //12
    manzana.push_back(Poligono( {177,48,29} , {{130,121}, {152,121}, {146,101}} )); //13
    manzana.push_back(Poligono( {208,83,63} , {{165,117}, {152,121}, {146,101}} )); //14
    manzana.push_back(Poligono( {214,106,93} , {{165,117}, {178,107}, {146,101}} )); //15
    manzana.push_back(Poligono( {223,95,86} , {{146,101}, {178,107}, {172,96}} )); //16
    manzana.push_back(Poligono( {179,60,62} , {{163,79}, {178,107}, {192,79}} )); //17
    manzana.push_back(Poligono( {164,54,55} , {{146,101}, {163,79}, {172,96}} )); //18
    manzana.push_back(Poligono( {157,37,47} , {{133,74}, {163,79}, {142,107}} )); //19
    manzana.push_back(Poligono( {172,72,38} , {{133,74}, {111,118}, {143,106}} )); //20
    manzana.push_back(Poligono( {194,70,60} , {{133,74}, {111,118}, {115,74}} )); //21
    manzana.push_back(Poligono( {143,49,47} , {{101,62}, {115,74}, {110,42}} )); //22
    manzana.push_back(Poligono( {126,39,22} , {{123,48}, {115,74}, {110,42}} )); //23
    manzana.push_back(Poligono( {129,33,9} , {{123,48}, {115,74}, {133,74}} )); //35
    manzana.push_back(Poligono( {159,36,3} , {{123,48}, {134,31}, {133,74}} )); //24
    manzana.push_back(Poligono( {112,12,0} , {{149,59}, {134,31}, {133,74}} )); //25
    manzana.push_back(Poligono( {138,23,16} , {{133,74}, {163,79}, {159,49}} )); //26
    manzana.push_back(Poligono( {180,10,0} , {{183,60}, {163,79}, {159,49}} )); //27
    manzana.push_back(Poligono( {167,26,32   } , {{183,60}, {163,79}, {189,73}} )); //28
    manzana.push_back(Poligono( {209,82,89} , {{192,79}, {163,79}, {189,73}} )); //29
    manzana.push_back(Poligono( {201,17,25} , {{192,79}, {192,57}, {177,47}} )); //30
    manzana.push_back(Poligono( {233,113,115} , {{159,49}, {183,60}, {177,47}} )); //31
    manzana.push_back(Poligono( {255,251,245} , {{159,49}, {166,40}, {177,47}} )); //32
    manzana.push_back(Poligono( {227,159,146} , {{159,49}, {145,41}, {160,38}} )); //33
    manzana.push_back(Poligono( {255,221,209} , {{159,49}, {166,40}, {160,38}} )); //34
    manzana.push_back(Poligono( {194,34,10} , {{149,59}, {134,31}, {159,49}} )); //35
    manzana.push_back(Poligono( {223,79,53} , {{144,41}, {134,31}, {160,38}} )); //36
    manzana.push_back(Poligono( {181,145,67} , {{134,31}, {133,37}, {168,32}} )); //37
    manzana.push_back(Poligono( {219,124,102} , {{182,42}, {133,37}, {168,32}} )); //38
    manzana.push_back(Poligono( {215,72,68} , {{182,42}, {192,57}, {166,40}} )); //39
    manzana.push_back(Poligono( {109,94,75} , {{127,20}, {127,22}, {131,20}} )); //40
    manzana.push_back(Poligono( {114,90,26} , {{132,25}, {127,22}, {131,20}} )); //41
    manzana.push_back(Poligono( {148,126,53} , {{132,25}, {131,20}, {131,20}} )); //42
    manzana.push_back(Poligono( {114,90,26} , {{132,25}, {137,33}, {131,20}} )); //43
    manzana.push_back(Poligono( {101,59,21} , {{140,33}, {137,33}, {131,20}} )); //44
    manzana.push_back(Poligono( {175,178,73} , {{140,33}, {143,28}, {160,22}} )); //45
    manzana.push_back(Poligono( {117,128,8} , {{145,28}, {148,17}, {157,10}} )); //46
    manzana.push_back(Poligono( {119,127,15} , {{145,28}, {160,22}, {157,10}} )); //46
    manzana.push_back(Poligono( {108,121,7} , {{185,12}, {157,10}, {160,22}} )); //47
    manzana.push_back(Poligono( {66,74,0} , {{185,12}, {157,10}, {185,5}} )); //48
    manzana.push_back(Poligono( {88,98,1} , {{166,5}, {157,10}, {185,5}} )); //49
    manzana.push_back(Poligono( {87,111,1} , {{185,12}, {197,9}, {185,5}} )); //50
    manzana.push_back(Poligono( {102,120,0} , {{185,12}, {197,9}, {180,24}} )); //51
    manzana.push_back(Poligono( {112,127,0} , {{185,12}, {162,27}, {160,22}} )); //52
    manzana.push_back(Poligono( {124,141,1} , {{185,12}, {180,24}, {162,27}} )); //53
    manzana.push_back(Poligono( {101,114,0} , {{150,27}, {162,27}, {160,22}} )); //54
}

#pragma endregion

#pragma region Movimientos

double psx;
double psy;

void movimientoObjeto(vector<array<double, 2>>& infoObjeto){
    //Borde pantalla
    //X
    if(infoObjeto[0][0] > 800-infoObjeto[4][0] || infoObjeto[0][0] < 0+infoObjeto[4][1]) {infoObjeto[1][0] *= -1; infoObjeto[2][0] *= -1;}
    infoObjeto[0][0] += infoObjeto[1][0];
    infoObjeto[3][0] += infoObjeto[2][0];
    
    //Y
    if(infoObjeto[0][1] > 800-infoObjeto[5][0] || infoObjeto[0][1] < 0+infoObjeto[5][1]) {infoObjeto[1][1] *= -1; infoObjeto[2][1] *= -1;}
    infoObjeto[0][1] -= infoObjeto[1][1];
    infoObjeto[3][1] += infoObjeto[2][1];
}

void move(int x){
    glutPostRedisplay();
    printf("x:%f | y:%f\n", psx, psy);
    movimientoObjeto(infoManzana); //Manzana

    glutTimerFunc(10, move, 1); //Repite el proceso
}

#pragma endregion

void graficar()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Instacia los poligonos
    glTranslatef(0.25,-0.4,0); //centrar la mesa
    dibujadoMesa();

    glScalef(0.5,0.5,0.5);
    glTranslatef(-0.7,0.53,0); //bajar la manzana
    glTranslatef(infoManzana[3][0],infoManzana[3][1],0);
    dibujadoManzana();

    glFlush();
}

void temp(int btn, int state, int x, int y){
    psx = x;
    psy = y;
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,200);
    glutCreateWindow("Mesa Animación");

    inicializar();

    glutDisplayFunc(graficar);
    glutReshapeFunc(redimensionar);
    glutMouseFunc(temp);
    glutTimerFunc(10, move, 1); //Bucle para realizar los movimentos hasta el infinito

    glutMainLoop();

    return 0;
}
