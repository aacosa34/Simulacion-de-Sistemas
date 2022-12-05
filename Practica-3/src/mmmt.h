#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;

#define SUCESO_LLEGADA_TRABAJO 0
#define SUCESO_FIN_CARGA 1
#define SUCESO_FIN_PROCESAMIENTO 2
#define SUCESO_FIN_DESCARGA 3
#define SUCESO_FIN_SIMULACION 4

/* Variables de estado */

typedef struct
{
	int suceso;
	float tiempo;
	float tllego;
} suc;
float reloj;
int maquinas_libres;
int encola_lleg;
int operarios_libres;
list<float> cola_llegadas;
int encola_sal;
list<float> cola_salidas;
float tdus_lleg;
float tdus_sal;
float comienzo_ocio;
list<suc> lsuc;
bool parar;
suc nodo;

/* Contadores estadisticos */
float acum_lleg;
float acum_sal;
float acum_ocio;
float total_procesados;
float acum_estancia;

float **informe;
int cont_simu;

/* Parametros de entrada */
int num_operarios = 5;
int num_maquinas = 10;
float tllegada = 6;
float tcarga = 5;	   // 0.6; // 1.5;
float tdescarga = 4;   // 2;   // 0.4; // 1; ;
float tproceso = 0.8;  // 8;
float tparada = 480.0; // 8 horas

/* Funciones y procedimientos */
void inicializacion();
void temporizacion();
void suceso();
void llegada_trabajo();
void fin_carga();
void fin_procesamiento();
void fin_descarga();
void fin_simulacion();
float genera_trabajo(float tllegada);
float genera_carga(float tcarga);
float genera_descarga(float tdescarga);
float genera_procesamiento(float tprocesamiento);
float generador_exponencial(float media);
bool compare(const suc &s1, const suc &s2);
void insertar_lsuc(suc n);
bool busca_suceso(int tipo);
void generador_informes(int simulaciones);
