#include "discreto.h"

bool compare(const suc &s1, const suc &s2)
{
    return s1.duracion < s2.duracion;
}

/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertarSuc(suc n)
{
    lsuc.push_back(n);

    // Mantener ordenada la lista por el tiempo de los sucesos
    lsuc.sort(compare);
}

int generadorExponencial(int media)
{
    float u;
    u = (float)random();
    u = (float)(u / (RAND_MAX + 1.0));
    return (-media * log(1 - u));
}

void inicializacion()
{
    // Inicializacion de variables de estado
    reloj = 0;
    lineasLibres = numLineas;

    // Inicializamos la lista de sucesos
    lsuc.clear();

    // Nodo para indicar el fin de la simulacion
    nodo.suceso = SUCESO_FIN_SIMULACION;
    nodo.duracion = reloj + tiempoParada;

    // Insertamos el nodo en la lista de sucesos
    insertarSuc(nodo);

    // Nodo para el primer suceso, en este caso, de llamadas de A a B y de B a A
    // Llamada de A a B
    nodo.suceso = SUCESO_LLAMADA_A_B;
    nodo.duracion = reloj + generadorExponencial(12);
    insertarSuc(nodo);

    // Llamada de B a A
    nodo.suceso = SUCESO_LLAMADA_B_A;
    nodo.duracion = reloj + generadorExponencial(10);
    insertarSuc(nodo);

    numLlamadas = 0;
    llamadasPerdidas = 0;
    acumLineasOcupadas = 0;

    parar = false;
}

void temporizacion()
{
    nodo = lsuc.front();
    lsuc.pop_front();
    reloj = nodo.duracion;
}

void suceso()
{
    switch (nodo.suceso)
    {
    case SUCESO_LLAMADA_A_B:
        llamada(12);
        break;
    case SUCESO_LLAMADA_B_A:
        llamada(10);
        break;
    case SUCESO_FIN_LLAMADA:
        finLlamada();
        break;
    case SUCESO_FIN_SIMULACION:
        finSimulacion();
        break;
    }
}

void llamada(int media)
{
    if (media == 10)
        nodo.suceso = SUCESO_LLAMADA_B_A;
    else
        nodo.suceso = SUCESO_LLAMADA_A_B;

    nodo.suceso = SUCESO_LLAMADA_A_B;
    nodo.duracion = reloj + generadorExponencial(media);
    insertarSuc(nodo);
    if (lineasLibres > 0)
    {
        lineasLibres--;
        nodo.suceso = SUCESO_FIN_LLAMADA;
        nodo.duracion = reloj + generadorExponencial(240);
        insertarSuc(nodo);
    }
    else
    {
        llamadasPerdidas++;
    }
}

void finLlamada()
{
    numLlamadas++;
    lineasLibres++;
    acumLineasOcupadas += numLineas - lineasLibres;
}

void finSimulacion()
{
    parar = true;
    informe[numSimulaciones][0] = (acumLineasOcupadas / (float)numLlamadas);
    informe[numSimulaciones][1] = ((acumLineasOcupadas / (float)numLlamadas) / (float)numLineas) * 100;
    informe[numSimulaciones][2] = numLlamadas;
    informe[numSimulaciones][3] = llamadasPerdidas;
    informe[numSimulaciones][4] = (llamadasPerdidas / (float)numLlamadas) * 100;
}

void generadorInformes(int vecesSimuladas)
{
    float media[5];
    for (int j = 0; j < 5; j++)
    {
        media[j] = 0;
        for (int i = 0; i < vecesSimuladas; i++)
            media[j] += informe[i][j];
        media[j] /= vecesSimuladas;
    }

    cout << "Numero medio de lineas ocupadas: " << media[0] << endl;
    cout << "Porcentaje medio de lineas ocupadas: " << media[1] << "%" << endl;
    cout << "Numero medio de llamadas atendidas: " << media[2] << endl;
    cout << "Numero medio de llamadas perdidas: " << media[3] << endl;
    cout << "Porcentaje medio de llamadas perdidas: " << media[4] << "%" << endl;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <num_veces>" << endl;
    }

    int num_veces = atoi(argv[1]);

    informe = new float *[num_veces];
    for (int i = 0; i < num_veces; i++)
    {
        informe[i] = new float[5];
    }

    for (numSimulaciones = 0; numSimulaciones < num_veces; numSimulaciones++)
    {
        inicializacion();
        while (!parar)
        {
            temporizacion();
            suceso();
        }
    }

    generadorInformes(num_veces);
}