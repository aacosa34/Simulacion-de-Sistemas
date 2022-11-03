#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

long long int gen_aritmetica_entera(int a, long long int xn, int m){
    return (a*xn)%m;
}

long long int gen_aritmetica_real(int a, long long int xn, int m){
    float x = (a*(float)xn)/m;
    x = (x-(long long int)x)*m;
    return (long long int) x;
}

long long int gen_aritmetica_real_corregida(int a, long long int xn, int m){
    float x = (a * (float) xn) / m;
	x = (x - (int) x) * m;
	
	return (long long int)(x + 0.5);
}

long long int gen_aritmetica_real_fmod(int a, long long int xn, int m){
    float x = fmod(a*xn,m);
    return (long long int) x;
}

int isRepetido(long long int *array, int size, int num){
    int i;
    for(i=0; i<size; i++){
        if(array[i] == num){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]){

    if(argc < 2) {
        printf("Error: Numero de parametros incorrecto.\n");
        printf("Uso: %s <generador a usar>\n", argv[0]);
        printf("Generadores disponibles:\n1 -> aritmetica entera\n2 -> aritmetica real\n3 -> aritmetica real 'corregida'\n4 -> aritmetica real con 'fmod'\n");
        exit(-1);
    }

    int tipo = atoi(argv[1]);

    if(tipo < 1 || tipo > 4) {
        printf("Error: Tipo de generador incorrecto.\n");
        printf("Generadores disponibles:\n1 -> aritmetica entera\n2 -> aritmetica real\n3 -> aritmetica real 'corregida'\n4 -> aritmetica real con 'fmod'\n");
        exit(-1);
    }

    long long int (*generador)(int, long long int, int);

    if(tipo == 1) {
        generador = gen_aritmetica_entera;
    } else if(tipo == 2) {
        generador = gen_aritmetica_real;
    } else if(tipo == 3) {
        generador = gen_aritmetica_real_corregida;
    } else {
        generador = gen_aritmetica_real_fmod;
    }

    long long int* valores_generados;
    int x0 = 1;
    int a = 1013;
    long long int m = pow(2,12);

    if((valores_generados = (long long int *) malloc(m * sizeof(long long int))) == NULL) {
        
        printf("Error: No se ha podido reservar memoria para los valores generados.\n");
        exit(-1);
    }

    long long int x = generador(a, x0, m);
    long long int cantidad_valores = 0;

    while(!isRepetido(valores_generados, cantidad_valores, x)) {
        valores_generados[cantidad_valores] = x;
        cantidad_valores++;

        x = generador(a, x, m);
    }

    printf("Periodo del generador: %d", cantidad_valores);

    free(valores_generados);
}