#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

float generaLlegada(float tlleg)
{
    float u = (float)random();         // o también rand() en lugar de random()
    u = (float)(u / (RAND_MAX + 1.0)); // RAND_MAX es una constante del sistema
    float lleg = -tlleg * log(1 - u);
    return round(lleg == 0 ? 1.0 : lleg);
}

float generaServicio(float tserv)
{
    float u = (float)random();         // o también rand() en lugar de random()
    u = (float)(u / (RAND_MAX + 1.0)); // RAND_MAX es una constante del sistema
    float serv = -tserv * log(1 - u);
    return round(serv == 0 ? 1.0 : serv);
}

float min(float a, float b)
{
    return a < b ? a : b;
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
    float totalPorcentajeOcio = 0.0, totalMediaEnCola = 0.0;

    for (int i = 0; i < num_veces; i++)
    {
        bool servidor_libre = true;
        long long int atendidos = 0;
        long long int encola = 0;
        long long int infinito = 10e30;
        float acum_cola = 0.0;
        float inicio_ocio = 0.0;
        float ocio = 0.0;
        float reloj = 0.0;
        float tiempo_llegada = reloj + generaLlegada(tlleg);
        float tiempo_salida = infinito;
        float tultsuc = 0.0;

        high_resolution_clock::time_point inicio, fin;
        inicio = high_resolution_clock::now();

        while (atendidos < total_a_atender)
        {
            reloj = min(tiempo_llegada, tiempo_salida); // una función que calcula el mínimo
            if (reloj == tiempo_llegada)
            {
                tiempo_llegada = reloj + generaLlegada(tlleg);
                if (servidor_libre)
                {
                    servidor_libre = false;
                    tiempo_salida = reloj + generaServicio(tserv);
                    ocio += reloj - inicio_ocio;
                }
                else
                {
                    acum_cola += (reloj - tultsuc) * encola;
                    tultsuc = reloj;
                    encola++;
                }
            }
            if (reloj == tiempo_salida)
            {
                atendidos++;
                if (encola > 0)
                {
                    acum_cola += (reloj - tultsuc) * encola;
                    tultsuc = reloj;
                    encola--;
                    tiempo_salida = reloj + generaServicio(tserv);
                }
                else
                {
                    servidor_libre = true;
                    inicio_ocio = reloj;
                    tiempo_salida = infinito;
                }
            }
        }

        fin = high_resolution_clock::now();

        float tiempoEjecucion = duration_cast<duration<float>>(fin - inicio).count();
        float porcentajeOcio = ocio * 100 / reloj; // calculamos el porcentaje de tiempo de ocio del servidor
        float mediaEnCola = acum_cola / reloj;     // calculamos el número medio de clientes en cola

        cout << porcentajeOcio << "," << mediaEnCola << "," << tiempoEjecucion << endl;
    }
}