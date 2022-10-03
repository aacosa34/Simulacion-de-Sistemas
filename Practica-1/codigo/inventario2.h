
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;

#define DEMANDA 0
#define EVALUACION 1
#define LLEGADA_PEDIDO 2
#define FIN_SIMULACION 3

typedef struct {
	int tipo;
	float tiempo;
	} suc;

   // Variables exogenas:
//   int spequena;
//   int sgrande;
   float mediademanda = 0.1;
   float tpedidomin = 0.5; 
   float tpedidomax = 1.0;
   float tevaluacion = 1.0;
   int   tparada = 120; //meses a simular
   float h = 1;
   float pi = 5;
   float k = 32;
   float i = 3;
   
   // Variables de estado:
   float reloj;
   int nivel;
   int pedido;
   float tultsuc;
   int gastado;
   bool parar;
   list<suc> lsuc;
   suc nodo;
   
   // Contadores estadisticos
   float acummas;
   float acummenos;
   float acumpedido;
   
   int veces; //numero de simulaciones
   float acum_costototal = 0.0;
   float acum_costopedido = 0.0;
   float acum_costomantenimiento = 0.0;
   float acum_costodeficit = 0.0;
   float acum2_costototal = 0.0;
   float acum2_costopedido = 0.0;
   float acum2_costomantenimiento = 0.0;
   float acum2_costodeficit = 0.0;
   
   /* Funciones y procedimientos */
void inicializacion();
// gestion de lista de sucesos
int temporizacion();
bool compare(const suc &s1, const suc &s2);
void insertar_lsuc(suc n);
// sucesos
void suceso(int suc_sig);
void demanda();
void evaluacion();
void llegadapedido();
void generadorInformes();
void informe();
// generadores de datos
float generademanda(float media);
float generapedido(float min, float max);
int   generatamano();

