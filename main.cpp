/*

Nombre programa: Programa 7GC
Programador: Isaac Salas Carmona
NUA: 392976
Fecha: 24-feb-2023

Objetivo: Graficar cosas con teclas

*/


#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


//MANERA RARA

#define VK_W 0x57
#define VK_S 0x53

#define VK_UP 0x26
#define VK_DOWN 0x28



typedef struct {
     float x;
     float y;
} PUNTO;


typedef enum{
    NEGRO,
    AZUL,
    VERDE,
    CYAN,
    ROJO,
    MAGENTA,
    BLANCO,
    GRIS,
    GRIS_OSCURO,
    GRIS_CLARO,
    AMARILLO
}COLOR;


typedef struct{
PUNTO vert;
float base;
float altura;
COLOR color;
} RECTANGULO;



float PALETA_COLORES[11][3] =
{
    0,0,0, //Negro
    0,0,1, //Azul
    0,1,0, //Verde
    0,1,1, //Cyan
    1,0,0, //Rojo'
    1,0,1, //Magenta
    1,1,1, //Blanco
    0.5,0.5,0.5, //Gris
    0.25,0.25,0.25, //Gris obscuro
    0.8,0.8,0.8, //Gris claro
    1,1,0 //Amarillo
};


void rectangulo(RECTANGULO);

void asignaColor(COLOR c);
void display(void);

int alto = 600;
int ancho = 600;

float Y_inip1 = 0;
float Y_inip2 = 0;
float tbase = 1;
float taltura = 1;
float rbase = 2;
float raltura = 1;
int numlados = 3;
int trigg;


typedef struct{
    float ball_pos_x;
    float ball_pos_y;
    float ball_dir_x;
    float ball_dir_y;
    int ball_size;
    int ball_speed;
    COLOR color;
}BOLA;

void Pelota(float x, float y, float ancho, float alto);
void Actpelota();

RECTANGULO P1, P2;
BOLA b;

int inicio=0;

float ball_pos_x = 0;
float ball_pos_y = 2;
float ball_dir_x = -1.0f;
float ball_dir_y = 0.0f;
int ball_size = 1;
float ball_speed = 0.1;

//Variables puntos
int puntos_P1 = 0;
int puntos_P2 = 0;
char buff1[15];
char buff2[5];

void Puntuasao(float x, float y, const char *puntos, COLOR c);
const char *Pintchar(int puntos_P1, int puntos_P2);


void keyboard() {
    // PALETA IZQ
    if (GetAsyncKeyState(VK_UP)){
            inicio=1;
                glutPostRedisplay();
            if(Y_inip2<=7 && Y_inip2>=-7)
            {
               if(Y_inip2==7){
                    Y_inip2 += 0.0;
                    Y_inip2 -= 0.5;
                }
                else{
                    Y_inip2 += 0.5;
                }

            }
    };
    if (GetAsyncKeyState(VK_DOWN)){
            inicio=1;
                glutPostRedisplay();
          if(Y_inip2<=7 && Y_inip2>=-7)
            {
               if(Y_inip2==-7){
                    Y_inip2 -= 0.0;
                    Y_inip2 += 0.5;
                }
                else{
                    Y_inip2 -= 0.5;
                }

            }
    }

    // PALETA DERECHA
    if (GetAsyncKeyState(VK_W)){
            inicio=1;
           if(Y_inip1<=7 && Y_inip1>=-7)
            {
               if(Y_inip1==7){
                    Y_inip1 += 0.0;
                    Y_inip1 -= 0.5;
                }
                else{
                    Y_inip1 += 0.5;
                }

            }
            glutPostRedisplay();

    }
    if (GetAsyncKeyState(VK_S)){
            inicio=1;
        if(Y_inip1<=7 && Y_inip1>=-7)
            {
               if(Y_inip1==-7){
                    Y_inip1 -= 0.0;
                    Y_inip1 += 0.5;
                }
                else{
                    Y_inip1 -= 0.5;
                }

            }

            glutPostRedisplay();
    }
}

void display (void) {


    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Modificar color

    glPolygonMode(GL_BACK,GL_POINT);

    P1.vert.x=-9;
    P1.vert.y=Y_inip1;
    P2.vert.x=8;
    P2.vert.y=Y_inip2;
    P1.base=1;
    P1.altura=4;
    P2.base=1;
    P2.altura=4;
    P2.color=CYAN;
    P1.color=ROJO;

    b.ball_pos_x= ball_pos_x;
    b.ball_pos_y= ball_pos_y;
    b.ball_dir_x= ball_dir_x;
    b.ball_dir_y= ball_dir_y;
    b.ball_size = ball_size;
    b.ball_speed = ball_speed;

    b.color = BLANCO;

        //printf("posisao inicial de P1: y=%f, x=%f", P1.vert.y, P1.vert.x);
    rectangulo(P2);
    rectangulo(P1);
    Pelota(b.ball_pos_x - b.ball_size / 2, b.ball_pos_y - b.ball_size / 2, b.ball_size, b.ball_size);

    if (puntos_P1<=9 && puntos_P2<=9)
    {
         Puntuasao(-0.5, 9.5, Pintchar(puntos_P1, puntos_P2),BLANCO);
    }
    else
        {
            switch(puntos_P1)
            {
            case 10:
                Puntuasao(-0.5, 9.5, "Ganador:", BLANCO);
                Puntuasao(-0.5, 8.5, "ROJO", ROJO);
                break;
            }
            switch(puntos_P2)
            {
                case 10:
                Puntuasao(-0.5, 9.5, "Ganador:", BLANCO);
                Puntuasao(-0.5, 8.5, "AZUL", CYAN);
                break;
            }

        }



//    switch(puntos_P1)
//    {
//    case 0:
//        P1.color=BLANCO;
//        glutPostRedisplay();
//        break;
//    case 1:
//        P1.color=ROJO;
//        glutPostRedisplay();
//        break;
//            }


    glFlush();
}

void update(int value) {//Funcion robada

   // input handling
   keyboard();
   switch(inicio){
   case 0:
    break;
   case 1:
       if(puntos_P1==10 || puntos_P2==10)
       {
           Sleep(1000);
           puntos_P1=0;
           puntos_P2=0;
       }
    Actpelota();
    break;
   }
   // Call update() again in 'interval' milliseconds
   glutTimerFunc(1000/60, update, 0);

   // Redisplay frame
   glutPostRedisplay();
}



int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(alto, ancho);
    glutCreateWindow("Programa PONGUS");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -7, 11, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(&display);
    glutTimerFunc(1000 / 60, update, 0);
    glutMainLoop(); // Enter GLUT's main loop

}



void vec2_norm(float& x, float &y) {
        // sets a vectors length to 1 (which means that x + y == 1)
        float length = sqrt((x * x) + (y * y));
        if (length != 0.0f) {
            length = 1.0f / length;
            x *= length;
            y *= length;
        }
    }

void Actpelota() {
    // fly a bit
    ball_pos_x += ball_dir_x * ball_speed;
    ball_pos_y += ball_dir_y * ball_speed;

    // hit by left racket?
    if (ball_pos_x < P1.vert.x + P1.base &&
        ball_pos_x > P1.vert.x &&
        ball_pos_y < P1.vert.y + P1.altura &&
        ball_pos_y > P1.vert.y) {
            ball_speed+=0.1;
        // set fly direction depending on where it hit the racket
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_pos_y - P1.vert.y) / P1.altura) - 0.5f;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = t;
    }

    // hit by right racket?
    if (ball_pos_x > P2.vert.x &&
        ball_pos_x < P2.vert.x + P2.base&&
        ball_pos_y < P2.vert.y + P2.altura &&
        ball_pos_y > P2.vert.y) {
            ball_speed+=0.1;
        // set fly direction depending on where it hit the racket
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball_pos_y - P2.vert.y) / P2.altura) - 0.5f;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = t;
    }

    // hit left wall?
    if (ball_pos_x < -10) {
            inicio=0;
        ++puntos_P2;
        ball_speed=0.1;
        ball_pos_x =  0;
        ball_pos_y = 2;
        ball_dir_x = fabs(ball_dir_x); // force it to be positive
        ball_dir_y = 0;
    }

    // hit right wall?
    if (ball_pos_x > 10) {
            inicio=0;
        ++puntos_P1;
        ball_speed=0.1;
        ball_pos_x = 0;
        ball_pos_y = 2;
        ball_dir_x = -fabs(ball_dir_x); // force it to be negative
        ball_dir_y = 0;
    }

    // hit top wall?
    if (ball_pos_y > 10) {
        ball_dir_y = -fabs(ball_dir_y); // force it to be negative
    }

    // hit bottom wall?
    if (ball_pos_y < -7) {
        ball_dir_y = fabs(ball_dir_y); // force it to be positive
    }

    // make sure that length of dir stays at 1
    vec2_norm(ball_dir_x, ball_dir_y);
}



void Pelota(float x, float y, float width, float height) {
    asignaColor(b.color);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

void rectangulo(RECTANGULO r) {
    asignaColor(r.color);
    glBegin(GL_QUADS);
        glVertex2f(r.vert.x, r.vert.y);
        glVertex2f(r.vert.x + r.base, r.vert.y);
        glVertex2f(r.vert.x + r.base, r.vert.y + r.altura);
        glVertex2f(r.vert.x, r.vert.y + r.altura);
    glEnd();
}

const char *Pintchar(int puntos_P1, int puntos_P2){ //convert integers scores into chars
	_itoa(puntos_P1, buff1, 10);
	_itoa(puntos_P2, buff2, 10);
	strcat(buff1, " : ");
	strcat(buff1, buff2);

	return buff1;
}



void Puntuasao(float x, float y, const char *puntos, COLOR c) {
	int t = strlen(puntos);
	asignaColor(c);
	glRasterPos2f(x, y);
	for (int i = 0; i < t; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, puntos[i]);
	}
}

void asignaColor (COLOR c){
    glColor3f(PALETA_COLORES[c][0], PALETA_COLORES[c][1], PALETA_COLORES[c][2]);
}


