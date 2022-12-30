#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;

#define SUCESO_LLAMADA_A_B 0
#define SUCESO_LLAMADA_B_A 1
#define SUCESO_FIN_LLAMADA 2
#define SUCESO_FIN_SIMULACION 3

/* Variables de estado */
typedef struct
{
    int suceso;
    int duracion;
} suc;

int reloj;
int lineasLibres;
bool parar;
list<suc> lsuc;
suc nodo;

/* Variables estadisticas */
int numLlamadas;
int llamadasPerdidas;
int acumLineasOcupadas;

float **informe;
int numSimulaciones;

/* Parametros de entrada */
int tiempoParada = 43200;
int numLineas = 60;

void inicializacion();
void insertarSuc(suc nodo);
int generadorExponencial(int media);
void temporizacion();
void suceso();
void llamada(int media);
void finLlamada();
void finSimulacion();
void generadorInformes(int vecesSimuladas);