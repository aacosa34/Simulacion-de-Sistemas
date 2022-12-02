#include <iostream>
#include <cmath>

using namespace std;

int generaLlegada(int tlleg)
{
    float u = (float)random();         // o también rand() en lugar de random()
    u = (float)(u / (RAND_MAX + 1.0)); // RAND_MAX es una constante del sistema
    float lleg = -tlleg * log(1 - u);
    return round(lleg == 0 ? 1.0 : lleg);
}

int generaServicio(int tserv)
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

int main()
{
    long long int infinito = 10e30;
    int atendidos = 0;
    float inicio_ocio = 0.0;
    float acum_cola = 0.0;
    float reloj = 0.0;
    bool servidor_libre = true;
    int encola = 0;
    int tlleg = 0;
    int tserv = 0;
    float tiempo_llegada = reloj + generaLlegada(tlleg);
    long long int tiempo_salida = infinito;
    int total_a_atender = 0;
    float ocio = 0.0;
    float tultsuc = 0.0;

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
        if (reloj = tiempo_salida)
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

    float porcent_ocio = ocio * 100 / reloj;
    cout << porcent_ocio << endl;
    float media_encola = acum_cola / reloj;
    cout << media_encola;
}