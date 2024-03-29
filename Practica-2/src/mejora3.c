#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. Lo utiliza el generador de demanda
{
    int t = random();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

double* construye_prop_a(int n) //Construye la tabla de b�squeda de
                               //tama�o n para la distribuci�n de
                               //la demanda del apartado (a).
{
    int i;
    double* temp;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador uniforme\n",stderr);
        exit(1);
    }
    temp[0] = 1.0/n;
    for (i=1;i<n;i++)
        temp[i] = temp[i-1]+1.0/n;
    return temp;
}


double* construye_prop_b(int n) //Construye la tabla de b�squeda de
                               //tama�o n para la distribuci�n de
                               //la demanda del apartado (b).
{
    int i, max;
    double* temp;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }
    max = (n+1)*n/2;
    temp[0] = 1.0/max;
    for (i=1;i<n;i++)
        temp[i] = temp[i-1]+(double)(i+1)/max;
    return temp;  
}

double* construye_prop_c(int n) //Construye la tabla de b�squeda de
                               //tama�o n para la distribuci�n de
                               //la demanda del apartado (c).
{
    int i, max;
    double* temp;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n",stderr);
        exit(1);
    }
    max = n*n/4;
    temp[0] = 0.0;
    for (i=1;i<(n/2);i++)
        temp[i] = temp[i-1]+(double)i/max;
    for (i=(n/2);i<n;i++)
        temp[i] = temp[i-1]+(double)(n-i)/max;
    return temp;
}

int genera_demanda(double* tabla,int tama) // Genera un valor de la 
        // distribuci�n de la demanda codificada en tabla, por el 
        // m�todo de tablas de b�squeda. 
        // tama es el tama�o de la tabla, 100 en nuestro caso particular
{
    int i;
    double u = uniforme();
    i = 0;
    while((i<tama) && (u>=tabla[i]))
        i++;
    return i;
}

int genera_demanda_tconst(){
    double u = uniforme();

    int i = (int)(u * 100);

    return i;
}

int main(int argc, char* argv[]){

    if(argc < 2) {
        printf("Error en el numero de argumentos. Uso: ./%s <numero de simulaciones> \n", argv[0]);
        return 1;
    }

    int veces = atoi(argv[1]);

    srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
    double* tablabdemanda;

    //Construye la tabla de búsqueda en funcion del tipo de tabla
    tablabdemanda = construye_prop_a(100);

    int demanda;

    clock_t inicio = clock();

    for(int s=0; s<veces; s++) {

        demanda = genera_demanda_tconst(); //Cada vez que se necesite un
                                            //valor del generador de demanda  
    }

    clock_t fin = clock();

    // Cálculo del tiempo de ejecución
    double tiempo = (double) (fin - inicio) / CLOCKS_PER_SEC;

    printf("\t%f\n", tiempo);

    free(tablabdemanda);
}