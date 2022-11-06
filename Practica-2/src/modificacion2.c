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

int min(int a, int b) //Funci�n auxiliar para calcular el m�nimo
{
    if (a<b)
        return a;
    else
        return b;
}

int main(int argc, char* argv[]){

    if(argc < 6) {
        printf("Error en el numero de argumentos. Uso: ./%s <valor de x> <valor de y> <valor de z> <numero de simulaciones> <tipo de tabla a generar> \n", argv[0]);
        return 1;
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int z = atoi(argv[3]);
    int veces = atoi(argv[4]);
    char tipo_tabla = atoi(argv[5]);

    if(tipo_tabla != 1 && tipo_tabla != 2 && tipo_tabla != 3) {
        printf("Error en el tipo de tabla. Debe ser '1 -> a', '2 -> b' o '3 -> c'.\n");
        return 1;
    }

    srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
    double* tablabdemanda;

    //Construye la tabla de búsqueda en funcion del tipo de tabla
    if(tipo_tabla == 1) {
        tablabdemanda = construye_prop_a(100);
    } else if(tipo_tabla == 2) {
        tablabdemanda = construye_prop_b(100);
    } else {
        tablabdemanda = construye_prop_c(100);
    }

    int ganancia, demanda;
    double gananciaesperada, desviaciont;

    double best_gananciaesperada = 0.0, best_desviaciont = 0.0;
    int best_s = 0;

    clock_t inicio = clock();

    for(int s=0; s<100; s++) {

        demanda = genera_demanda(tablabdemanda,100); //Cada vez que se necesite un
                                                    //valor del generador de demanda
        
        double sum=0.0, sum2=0.0;
        for (int j=0; j<veces; j++) {
            demanda=genera_demanda(tablabdemanda, 100);
            if (s>demanda) {
                int valor_min = min(z, (s-demanda) * y);
                ganancia=x*demanda - valor_min;
            }
            else ganancia=x*s;
            sum+=ganancia;
            sum2+=ganancia*ganancia;
        }
        gananciaesperada=sum/veces;
        desviaciont=sqrt((sum2-veces*gananciaesperada*gananciaesperada)/(veces-1));
        // printf("Ganancia esperada: %f, Desviacion tipica: %f \n", gananciaesperada, desviaciont);

        // Calculamos la mejor ganancia esperada y la mejor desviacion tipica
        if(best_gananciaesperada < gananciaesperada) {
            best_gananciaesperada = gananciaesperada;
            best_desviaciont = desviaciont;
            best_s = s;
        }
    }

    clock_t fin = clock();

    // Cálculo del tiempo de ejecución
    double tiempo = (double) (fin - inicio) / CLOCKS_PER_SEC;

    printf("%d;%d;%d;%d;%d;%f;%f\n", x, y, z, veces, best_s, best_gananciaesperada, tiempo);

    free(tablabdemanda);
}