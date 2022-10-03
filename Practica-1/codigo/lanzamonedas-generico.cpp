#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// #include <list>

using namespace std;

// calcula por montecarlo el beneficio esperado de un juego en el que el que lanza monedas paga x euros por lanzamiento, el juego continua hasta que la diferencia entre el n�mero de caras y de cruces (en valor absoluto) es igual a dif, y el otro jugador le paga al primero y euros al finalizar


float prob; //probabilidad de obtener cara
int dif; //diferencia entre el numero de caras y de cruces para parar los lanzamientos
int lanzamientos; //lanzamientos de moneda realizados
float esperado; //beneficio medio obtenido
float medialanzamientos; //numero medio de lanzamientos
int i;
int veces; //numero de repeticiones del juego
int caras, cruces; //numero de caras y cruces obtenidas
float pagoporlanzamiento,pagoalfinalizar;

int lanza(){
float u;
  u = (float) random();
  u = u/(float)(RAND_MAX+1.0);
  if (u<prob)
   return 0;
  else return 1;
}


/* Programa principal */
int main(int argc, char *argv[])
{
  if(argc == 1)
   {
    veces=100000;
    prob=0.5;
    dif=3;
    pagoporlanzamiento=10.0;
    pagoalfinalizar=100.0;
   }
   else if(argc == 4)
   {
    sscanf(argv[1],"%d",&veces);
    sscanf(argv[2],"%f",&pagoporlanzamiento);
    sscanf(argv[3],"%f",&pagoalfinalizar);
    prob=0.5;
    dif=3;
   }
   else if(argc != 6)
	{
         printf("\nFormato Argumentos -> <numero de iteraciones> <pago por lanzamiento> <pago al finalizar> <probabilidad de cara> <diferencia entre caras y cruces\n");
	 exit(1);
	}
       else
          {
           sscanf(argv[1],"%d",&veces);
           sscanf(argv[2],"%f",&pagoporlanzamiento);
           sscanf(argv[3],"%f",&pagoalfinalizar);
           sscanf(argv[4],"%f",&prob);
           sscanf(argv[5],"%d",&dif);
	  }

//srandom(123456);
srandom(time(NULL));
esperado=0.0;
medialanzamientos=0;

for (int vez=0; vez<veces; vez++) {
   lanzamientos = 0;
   caras = 0;
   cruces = 0;
   while (abs(caras-cruces) != dif) {
     i=lanza();
     lanzamientos++;
     if (i==0) caras++;
     else cruces++;
   }
   esperado += pagoalfinalizar-lanzamientos*pagoporlanzamiento;
   medialanzamientos += lanzamientos;
}
esperado=esperado/veces;
medialanzamientos = medialanzamientos/veces;

// printf("\nNumero de partidas: %d ",veces);
// printf("\nProbabilidad de cara: %f ",prob);
// printf("\ndiferencia entre caras y cruces: %d ",dif);
// printf("\nPago por lanzamiento: %f ",pagoporlanzamiento);
// printf("\nPago al finalizar: %f ",pagoalfinalizar);
// printf("\n");

// printf("\nBeneficio esperado: %f ",esperado);
//printf("\n");
// printf("\nNumero medio de lanzamientos: %f ",medialanzamientos);
printf("%f, %f", esperado, medialanzamientos);
printf("\n");
}
