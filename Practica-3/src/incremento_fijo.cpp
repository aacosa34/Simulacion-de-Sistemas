#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

float generaLlegada(float tlleg)
{
    float u = (float)random();         // o también rand() en lugar de random()
    u = (float)(u / (RAND_MAX + 1.0)); // RAND_MAX es una constante del sistema
    float lleg = round(-tlleg * log(1 - u));
    return lleg == 0 ? 1.0 : lleg;
}

float generaServicio(float tserv)
{
    float u = (float)random();         // o también rand() en lugar de random()
    u = (float)(u / (RAND_MAX + 1.0)); // RAND_MAX es una constante del sistema
    float serv = round(-tserv * log(1 - u));
    return serv == 0 ? 1.0 : serv;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    long long int total_a_atender;
    float tlleg;
    float tserv;

    if (argc != 4)
    {
        cerr << "ERROR: número de argumentos inválido." << endl;
        cerr << "Uso correcto: ./" << argv[0] << " <clientes_a_atender> <tllegada> <tservicio>" << endl;
    }
    else
    {
        total_a_atender = atoi(argv[1]);
        tlleg = atof(argv[2]);
        tserv = atof(argv[3]);
    }

    int num_veces = 1000;

    for (int i = 0; i < num_veces; i++)
    {
        bool servidor_libre = true;
        long long int infinito = 10e30;
        long long int atendidos = 0;
        long long int reloj = 0;
        long long int encola = 0;
        long long int tultsuc = 0;
        long long int tiempo_llegada = reloj + (long long int)generaLlegada(tlleg);
        long long int tiempo_salida = infinito;
        float acum_cola = 0.0;
        float inicio_ocio = 0.0;
        float ocio = 0.0;

        high_resolution_clock::time_point inicio, fin;
        inicio = high_resolution_clock::now();

        while (atendidos < total_a_atender) // simularemos hasta que hayamos atendido a cierto
                                            // número de clientes, total_a_atender
        {
            if (reloj == tiempo_llegada) // si estamos en el instante en que llega alguien
            {
                tiempo_llegada = reloj + (long long int)generaLlegada(tlleg); // determinamos cuando llegará
                                                                              // el siguiente cliente
                if (servidor_libre)                                           // si el servidor está ocioso
                {
                    servidor_libre = false;                                       // deja de estarlo
                    tiempo_salida = reloj + (long long int)generaServicio(tserv); // determinamos cuando saldrá
                                                                                  // ese cliente que acaba de llegar
                    ocio += reloj - inicio_ocio;                                  // acumulamos el ocio hasta este momento
                }
                else
                {                                            // el servidor está ocupado
                    acum_cola += (reloj - tultsuc) * encola; // acumulamos el número de clientes en
                                                             // cola por el tiempo en que han estado en cola
                    tultsuc = reloj;                         // para saber en qué momento cambió el tamaño de la cola, en
                                                             // este caso aumentó en uno más
                    encola++;                                // hay un cliente más en cola
                }
            }
            if (reloj == tiempo_salida) // si estamos en el instante en que se va alguien
            {
                atendidos++;    // se ha atendido a un cliente más
                if (encola > 0) // si quedan clientes en cola
                {
                    acum_cola += (reloj - tultsuc) * encola;                      // acumulamos el número de clientes en
                                                                                  // cola por el tiempo en que han estado en cola
                    tultsuc = reloj;                                              // para saber en qué momento cambió el tamaño de la cola, en
                                                                                  // este caso disminuyó en uno
                    encola--;                                                     // hay un cliente menos en cola
                    tiempo_salida = reloj + (long long int)generaServicio(tserv); // determinamos cuando saldrá
                                                                                  // ese cliente que acaba de entrar
                }
                else
                {                             // no quedan clientes en cola
                    servidor_libre = true;    // el servidor se queda ocioso por falta de clientes
                    inicio_ocio = reloj;      // marcamos cuando empieza a estar ocioso
                    tiempo_salida = infinito; // nadie puede salir puesto que nadie hay
                }
            }
            reloj++; // el tiempo se incrementa en una unidad
        }

        fin = high_resolution_clock::now();

        float tiempoEjecucion = duration_cast<duration<float>>(fin - inicio).count();
        float porcentajeOcio = ocio * 100 / reloj; // calculamos el porcentaje de tiempo de ocio del servidor
        float mediaEnCola = acum_cola / reloj;     // calculamos el número medio de clientes en cola

        cout << porcentajeOcio << "," << mediaEnCola << "," << tiempoEjecucion << endl;
    }
}